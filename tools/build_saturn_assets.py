#!/usr/bin/env python3
import argparse
import os
import shutil
import subprocess
import struct
import tempfile
import zlib
from pathlib import Path

try:
    from PIL import Image
except ImportError as exc:
    raise SystemExit("Pillow is required: pip install pillow") from exc

PALETTE_OPAQUE_COLORS = 15
ALPHA_THRESHOLD = int(os.environ.get("VG_ASSET_ALPHA_THRESHOLD", "64"))
PNGQUANT_DITHER_ARGS = os.environ.get("VG_ASSET_PNGQUANT_DITHER", "--nofs").split()

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


def require_tool(name):
    path = shutil.which(name)
    if path is None:
        raise SystemExit(
            f"Missing required asset tool: {name}. "
            "Build via build_saturn.ps1 so the YAUL asset Docker image provides it."
        )
    return path


def run_tool(args):
    subprocess.run(args, check=True)


def rgb_to_argb1555(r, g, b, alpha=1):
    return (alpha << 15) | ((int(b) >> 3) << 10) | ((int(g) >> 3) << 5) | (int(r) >> 3)


def external_quantized_png(src_file, resized_file, quantized_file):
    magick = require_tool("magick")
    pngquant = require_tool("pngquant")

    with Image.open(src_file) as image:
        width = max(1, image.width // 2)
        height = max(1, image.height // 2)

    run_tool([
        magick,
        str(src_file),
        "-alpha",
        "on",
        "-filter",
        "Mitchell",
        "-resize",
        f"{width}x{height}!",
        f"PNG32:{resized_file}",
    ])
    run_tool([
        pngquant,
        "--force",
        "--speed",
        "1",
        "--quality",
        "0-100",
        *PNGQUANT_DITHER_ARGS,
        "--output",
        str(quantized_file),
        str(PALETTE_OPAQUE_COLORS),
        str(resized_file),
    ])


def quantized_png_to_4bpp_bytes(png_file):
    image = Image.open(png_file).convert("RGBA")
    pixels = image.load()

    palette_rgb = []
    palette_index = {}
    indices = []

    for y in range(image.height):
        row = []
        for x in range(image.width):
            r, g, b, a = pixels[x, y]
            if a < ALPHA_THRESHOLD:
                row.append(0)
                continue

            rgb = (r, g, b)
            index = palette_index.get(rgb)
            if index is None:
                if len(palette_rgb) >= PALETTE_OPAQUE_COLORS:
                    raise SystemExit(
                        f"{png_file} has more than {PALETTE_OPAQUE_COLORS} opaque colors "
                        "after pngquant; cannot pack as Saturn 4bpp with index 0 transparent"
                    )
                palette_rgb.append(rgb)
                index = len(palette_rgb)
                palette_index[rgb] = index
            row.append(index)
        indices.append(row)

    palette = [0x0000]
    palette.extend(rgb_to_argb1555(r, g, b, 1) for r, g, b in palette_rgb[:15])
    while len(palette) < 16:
        palette.append(0x0000)

    out = bytearray()
    for row in indices:
        for x in range(0, len(row), 2):
            hi = row[x] & 0x0F
            lo = row[x + 1] & 0x0F if (x + 1) < len(row) else 0
            out.append((hi << 4) | lo)

    palette_bytes = b"".join(struct.pack(">H", color) for color in palette[:16])
    return image.width, image.height, palette_bytes, bytes(out)


def lower_relative(path):
    return Path(*(part.lower() for part in path.parts))


def convert_png(src_file, src_root, out_root):
    rel = lower_relative(src_file.relative_to(src_root)).with_suffix(".sat")
    dst_file = out_root / rel
    dst_file.parent.mkdir(parents=True, exist_ok=True)

    if sat_file_current(src_file, dst_file):
        return False

    with tempfile.TemporaryDirectory(prefix="vg_saturn_asset_") as tmp_dir:
        resized = Path(tmp_dir) / "resized.png"
        quantized = Path(tmp_dir) / "quantized.png"
        external_quantized_png(src_file, resized, quantized)
        width, height, palette, pixels = quantized_png_to_4bpp_bytes(quantized)

    tmp_file = dst_file.with_suffix(dst_file.suffix + ".tmp")
    with tmp_file.open("wb") as out:
        out.write(struct.pack(">4sHHI", b"VG4P", width, height, len(pixels)))
        out.write(palette)
        out.write(pixels)
    tmp_file.replace(dst_file)
    return True


def sat_file_current(src_file, dst_file):
    if not dst_file.exists():
        return False
    if dst_file.stat().st_mtime < Path(__file__).stat().st_mtime:
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
