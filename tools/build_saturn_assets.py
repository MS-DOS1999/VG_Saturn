#!/usr/bin/env python3
import argparse
import math
import shutil
import struct
import zlib
from pathlib import Path

try:
    from PIL import Image
except ImportError as exc:
    raise SystemExit("Pillow is required: pip install pillow") from exc

try:
    import numpy as np
except ImportError:
    np = None


MITCHELL_B = 1.0 / 3.0
MITCHELL_C = 1.0 / 3.0

COPY_EXTENSIONS = {
    ".bg",
    ".cfg",
    ".col",
    ".dat",
    ".nde",
    ".pt",
    ".txt",
    ".txd",
}


def mitchell_weight(x):
    x = abs(x)
    b = MITCHELL_B
    c = MITCHELL_C
    if x < 1.0:
        return (
            ((12.0 - 9.0 * b - 6.0 * c) * x * x * x)
            + ((-18.0 + 12.0 * b + 6.0 * c) * x * x)
            + (6.0 - 2.0 * b)
        ) / 6.0
    if x < 2.0:
        return (
            ((-b - 6.0 * c) * x * x * x)
            + ((6.0 * b + 30.0 * c) * x * x)
            + ((-12.0 * b - 48.0 * c) * x)
            + (8.0 * b + 24.0 * c)
        ) / 6.0
    return 0.0


def axis_contrib(src_len, dst_len):
    scale = float(src_len) / float(dst_len)
    contrib = []
    for dst in range(dst_len):
        center = (dst + 0.5) * scale - 0.5
        first = int(math.floor(center)) - 1
        indices = []
        weights = []
        total = 0.0
        for tap in range(4):
            idx = first + tap
            clamped = min(max(idx, 0), src_len - 1)
            weight = mitchell_weight(center - idx)
            indices.append(clamped)
            weights.append(weight)
            total += weight
        if total != 0.0:
            weights = [w / total for w in weights]
        contrib.append((indices, weights))
    return contrib


def resize_mitchell_numpy(image, width, height):
    src = np.asarray(image, dtype=np.float32)
    src_h, src_w, channels = src.shape

    x_contrib = axis_contrib(src_w, width)
    tmp = np.zeros((src_h, width, channels), dtype=np.float32)
    for dst_x, (indices, weights) in enumerate(x_contrib):
        idx = np.asarray(indices, dtype=np.intp)
        w = np.asarray(weights, dtype=np.float32)
        tmp[:, dst_x, :] = (src[:, idx, :] * w[None, :, None]).sum(axis=1)

    y_contrib = axis_contrib(src_h, height)
    out = np.zeros((height, width, channels), dtype=np.float32)
    for dst_y, (indices, weights) in enumerate(y_contrib):
        idx = np.asarray(indices, dtype=np.intp)
        w = np.asarray(weights, dtype=np.float32)
        out[dst_y, :, :] = (tmp[idx, :, :] * w[:, None, None]).sum(axis=0)

    return np.clip(out + 0.5, 0.0, 255.0).astype(np.uint8)


def resize_mitchell_python(image, width, height):
    src_w, src_h = image.size
    src = image.load()
    x_contrib = axis_contrib(src_w, width)
    y_contrib = axis_contrib(src_h, height)

    tmp = []
    for y in range(src_h):
        row = []
        for indices, weights in x_contrib:
            acc = [0.0, 0.0, 0.0, 0.0]
            for idx, weight in zip(indices, weights):
                pixel = src[idx, y]
                for channel in range(4):
                    acc[channel] += pixel[channel] * weight
            row.append(acc)
        tmp.append(row)

    out = Image.new("RGBA", (width, height))
    dst = out.load()
    for y, (indices, weights) in enumerate(y_contrib):
        for x in range(width):
            acc = [0.0, 0.0, 0.0, 0.0]
            for idx, weight in zip(indices, weights):
                pixel = tmp[idx][x]
                for channel in range(4):
                    acc[channel] += pixel[channel] * weight
            dst[x, y] = tuple(max(0, min(255, int(v + 0.5))) for v in acc)
    return out


def resize_half_mitchell(image):
    width = max(1, image.width // 2)
    height = max(1, image.height // 2)
    rgba = image.convert("RGBA")
    if np is not None:
        return Image.fromarray(resize_mitchell_numpy(rgba, width, height), "RGBA")
    return resize_mitchell_python(rgba, width, height)


def rgb_to_argb1555(r, g, b, alpha=1):
    return (alpha << 15) | ((int(r) >> 3) << 10) | ((int(g) >> 3) << 5) | (int(b) >> 3)


def quantize_palette_15(image):
    rgba = image.convert("RGBA")
    if np is not None:
        arr = np.asarray(rgba, dtype=np.uint8)
        opaque = arr[:, :, 3] >= 128
        opaque_rgb = arr[:, :, :3][opaque]
        if opaque_rgb.size == 0:
            return [(0, 0, 0)] * 15, np.zeros((rgba.height, rgba.width), dtype=np.uint8)

        max_sample = 65536
        if len(opaque_rgb) > max_sample:
            step = max(1, len(opaque_rgb) // max_sample)
            sample = opaque_rgb[::step][:max_sample]
        else:
            sample = opaque_rgb

        sample_w = min(1024, len(sample))
        sample_h = int(math.ceil(len(sample) / float(sample_w)))
        padded = np.zeros((sample_h * sample_w, 3), dtype=np.uint8)
        padded[: len(sample)] = sample
        if len(sample) < len(padded):
            padded[len(sample) :] = sample[-1]
        sample_img = Image.fromarray(padded.reshape((sample_h, sample_w, 3)), "RGB")
        quantized = sample_img.quantize(colors=15, dither=Image.Dither.NONE)
        raw_palette = quantized.getpalette()[: 15 * 3]
        palette = [
            tuple(raw_palette[i : i + 3])
            for i in range(0, len(raw_palette), 3)
        ]
        while len(palette) < 15:
            palette.append((0, 0, 0))

        pal = np.asarray(palette, dtype=np.int16)
        src = arr[:, :, :3].astype(np.int16)
        indices = np.zeros((rgba.height, rgba.width), dtype=np.uint8)
        opaque_pos = np.where(opaque)
        colors = src[opaque]
        best = np.zeros((colors.shape[0],), dtype=np.uint8)
        best_dist = np.full((colors.shape[0],), 1 << 30, dtype=np.int32)
        for pal_index in range(15):
            diff = colors - pal[pal_index]
            dist = (diff[:, 0] * diff[:, 0]) + (diff[:, 1] * diff[:, 1]) + (diff[:, 2] * diff[:, 2])
            mask = dist < best_dist
            best_dist[mask] = dist[mask]
            best[mask] = pal_index + 1
        indices[opaque_pos] = best
        return palette, indices

    opaque_pixels = [p[:3] for p in rgba.getdata() if p[3] >= 128]
    if not opaque_pixels:
        return [(0, 0, 0)] * 15, [[0 for _ in range(rgba.width)] for _ in range(rgba.height)]

    sample = opaque_pixels[:: max(1, len(opaque_pixels) // 65536)]
    sample_w = min(1024, len(sample))
    sample_h = int(math.ceil(len(sample) / float(sample_w)))
    sample += [sample[-1]] * ((sample_w * sample_h) - len(sample))
    sample_img = Image.new("RGB", (sample_w, sample_h))
    sample_img.putdata(sample)
    quantized = sample_img.quantize(colors=15, dither=Image.Dither.NONE)
    raw_palette = quantized.getpalette()[: 15 * 3]
    palette = [tuple(raw_palette[i : i + 3]) for i in range(0, len(raw_palette), 3)]
    while len(palette) < 15:
        palette.append((0, 0, 0))

    indices = []
    src = rgba.load()
    for y in range(rgba.height):
        row = []
        for x in range(rgba.width):
            r, g, b, a = src[x, y]
            if a < 128:
                row.append(0)
                continue
            best = 1
            best_dist = 1 << 30
            for pal_index, (pr, pg, pb) in enumerate(palette, start=1):
                dist = ((r - pr) * (r - pr)) + ((g - pg) * (g - pg)) + ((b - pb) * (b - pb))
                if dist < best_dist:
                    best_dist = dist
                    best = pal_index
            row.append(best)
        indices.append(row)
    return palette, indices


def rgba_to_4bpp_bytes(image):
    palette_rgb, indices = quantize_palette_15(image)
    palette = [0x0000]
    palette.extend(rgb_to_argb1555(r, g, b, 1) for r, g, b in palette_rgb[:15])
    while len(palette) < 16:
        palette.append(0x0000)

    if np is not None and hasattr(indices, "shape"):
        h, w = indices.shape
        if (w & 1) != 0:
            indices = np.pad(indices, ((0, 0), (0, 1)), constant_values=0)
            w += 1
        packed = ((indices[:, 0:w:2] << 4) | indices[:, 1:w:2]).astype(np.uint8)
        pixel_bytes = packed.tobytes()
    else:
        out = bytearray()
        for row in indices:
            for x in range(0, len(row), 2):
                hi = row[x] & 0x0F
                lo = row[x + 1] & 0x0F if (x + 1) < len(row) else 0
                out.append((hi << 4) | lo)
        pixel_bytes = bytes(out)

    palette_bytes = b"".join(struct.pack(">H", color) for color in palette[:16])
    return palette_bytes, pixel_bytes


def lower_relative(path):
    return Path(*(part.lower() for part in path.parts))


def convert_png(src_file, src_root, out_root):
    rel = lower_relative(src_file.relative_to(src_root)).with_suffix(".sat")
    dst_file = out_root / rel
    dst_file.parent.mkdir(parents=True, exist_ok=True)

    if sat_file_current(src_file, dst_file):
        return False

    with Image.open(src_file) as image:
        resized = resize_half_mitchell(image)
    palette, pixels = rgba_to_4bpp_bytes(resized)

    tmp_file = dst_file.with_suffix(dst_file.suffix + ".tmp")
    with tmp_file.open("wb") as out:
        out.write(struct.pack(">4sHHI", b"VG4P", resized.width, resized.height, len(pixels)))
        out.write(palette)
        out.write(pixels)
    tmp_file.replace(dst_file)
    return True


def sat_file_current(src_file, dst_file):
    if not dst_file.exists():
        return False
    if dst_file.stat().st_mtime < src_file.stat().st_mtime:
        return False

    try:
        with dst_file.open("rb") as existing:
            header = existing.read(12)
        if len(header) != 12:
            return False
        magic, width, height, data_size = struct.unpack(">4sHHI", header)
        if magic != b"VG4P" or width == 0 or height == 0 or data_size == 0:
            return False
        return dst_file.stat().st_size == 12 + 32 + data_size
    except OSError:
        return False


def copy_data(src_file, src_root, out_root):
    rel = lower_relative(src_file.relative_to(src_root))
    dst_file = out_root / rel
    dst_file.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(src_file, dst_file)


def iso83_name(name):
    stem = Path(name).stem.upper()[:8]
    suffix = Path(name).suffix.upper()
    if suffix.startswith("."):
        suffix = suffix[1:4]
    if suffix:
        return f"{stem}.{suffix}"
    return stem


def is_iso83_component(name):
    return iso83_name(name) == name.upper()


def rel_upper(path):
    return "/".join(part.upper() for part in path.parts)


def alias_name_for(rel):
    crc = zlib.crc32(rel_upper(rel).encode("ascii", errors="ignore")) & 0x00FFFFFF
    suffix = rel.suffix.upper()
    if suffix.startswith("."):
        suffix = suffix[1:4]
    if suffix:
        return f"A{crc:06X}.{suffix}"
    return f"A{crc:06X}"


def write_saturn_aliases(out_root, header_path):
    alias_root = out_root / "sa"
    if alias_root.exists():
        shutil.rmtree(alias_root)

    files = [
        path for path in sorted(out_root.rglob("*"))
        if path.is_file() and "sa" not in path.relative_to(out_root).parts
    ]

    groups = {}
    for path in files:
        rel = lower_relative(path.relative_to(out_root))
        parent = rel.parent
        key = (parent, iso83_name(rel.name))
        groups.setdefault(key, []).append(path)

    collision_paths = set()
    for paths in groups.values():
        if len(paths) > 1:
            collision_paths.update(paths)

    mappings = []
    used_aliases = set()
    for path in files:
        rel = lower_relative(path.relative_to(out_root))
        unsafe = path in collision_paths
        unsafe = unsafe or any(not is_iso83_component(part) for part in rel.parts)
        if not unsafe:
            continue

        alias_name = alias_name_for(rel)
        while alias_name in used_aliases:
            stem, dot, ext = alias_name.partition(".")
            value = (int(stem[1:], 16) + 1) & 0x00FFFFFF
            alias_name = f"A{value:06X}.{ext}" if dot else f"A{value:06X}"
        used_aliases.add(alias_name)

        alias_rel = Path("sa") / alias_name.lower()
        alias_file = out_root / alias_rel
        alias_file.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(path, alias_file)
        mappings.append((rel_upper(rel), rel_upper(alias_rel)))

    header_path.parent.mkdir(parents=True, exist_ok=True)
    with header_path.open("w", encoding="ascii", newline="\n") as out:
        out.write("#ifndef VG_SATURN_ASSET_ALIASES_H\n")
        out.write("#define VG_SATURN_ASSET_ALIASES_H\n\n")
        out.write("typedef struct SaturnAssetAlias {\n")
        out.write("    const char *source;\n")
        out.write("    const char *alias;\n")
        out.write("} SaturnAssetAlias;\n\n")
        out.write("static const SaturnAssetAlias kSaturnAssetAliases[] = {\n")
        for source, alias in mappings:
            out.write(f"    {{\"{source}\", \"{alias}\"}},\n")
        out.write("};\n\n")
        out.write(
            "static const unsigned int kSaturnAssetAliasCount = "
            "sizeof(kSaturnAssetAliases) / sizeof(kSaturnAssetAliases[0]);\n\n"
        )
        out.write("#endif\n")

    return len(mappings)


def build_assets(src_root, out_root):
    png_count = 0
    png_skipped = 0
    copy_count = 0
    for src_file in sorted(src_root.rglob("*")):
        if not src_file.is_file():
            continue
        ext = src_file.suffix.lower()
        if ext == ".png":
            if convert_png(src_file, src_root, out_root):
                png_count += 1
                if (png_count % 25) == 0:
                    print(f"Converted {png_count} PNG textures...")
            else:
                png_skipped += 1
        elif ext in COPY_EXTENSIONS:
            copy_data(src_file, src_root, out_root)
            copy_count += 1
    return png_count, png_skipped, copy_count


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--src", default="data/dc", type=Path)
    parser.add_argument("--out", default="cd", type=Path)
    args = parser.parse_args()

    src_root = args.src.resolve()
    out_root = args.out.resolve()
    if not src_root.exists():
        raise SystemExit(f"Missing source asset directory: {src_root}")

    png_count, png_skipped, copy_count = build_assets(src_root, out_root)
    repo_root = Path(__file__).resolve().parents[1]
    alias_count = write_saturn_aliases(out_root, repo_root / "source/saturn/saturn_asset_aliases.h")
    print(f"Converted PNG textures: {png_count}")
    print(f"Skipped current PNG textures: {png_skipped}")
    print(f"Copied data files: {copy_count}")
    print(f"Generated ISO 8.3 aliases: {alias_count}")
    print(f"Output: {out_root}")


if __name__ == "__main__":
    main()
