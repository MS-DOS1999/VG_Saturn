#!/usr/bin/env python3
import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path


REQUIRED_MARKERS = ("[BOOT]", "[PASS]")
FAIL_MARKERS = (
    "[FAIL]",
    "[FATAL]",
    "Address Error",
    "Illegal Instruction",
    "Unhandled",
    "assert",
    "segmentation fault",
)


def repo_root() -> Path:
    return Path(__file__).resolve().parents[1]


def find_mednafen(root: Path, override: str | None) -> Path | None:
    if override:
        candidate = Path(override)
        return candidate if candidate.exists() else None

    for name in ("mednafen", "mednafen.exe"):
        found = shutil.which(name)
        if found:
            return Path(found)

    local = root / "Emulators" / "mednafen" / "mednafen.exe"
    if local.exists():
        return local

    return None


def docker_work_path(root: Path, path: Path) -> str | None:
    try:
        rel = path.relative_to(root)
    except ValueError:
        return None
    return "/work/" + rel.as_posix()


def read_text_if_exists(path: Path) -> str:
    if not path.exists():
        return ""
    return path.read_text(encoding="utf-8", errors="replace")


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Run a Saturn CUE in Mednafen and validate debug markers."
    )
    parser.add_argument("cue", help="Path to the Saturn .cue file")
    parser.add_argument("--timeout", type=float, default=45.0)
    parser.add_argument("--mednafen", help="Path to mednafen or mednafen.exe")
    parser.add_argument(
        "--docker-image",
        default=os.environ.get("MEDNAFEN_DOCKER_IMAGE"),
        help="Docker image containing /opt/mednafen-ss-dev/bin/mednafen",
    )
    parser.add_argument("--log", default="logs/mednafen.txt")
    args = parser.parse_args()

    root = repo_root()
    cue = Path(args.cue)
    if not cue.is_absolute():
        cue = root / cue
    cue = cue.resolve()
    if not cue.exists():
        print(f"Missing CUE: {cue}", file=sys.stderr)
        return 1

    log_path = Path(args.log)
    if not log_path.is_absolute():
        log_path = root / log_path
    log_path.parent.mkdir(parents=True, exist_ok=True)

    env = os.environ.copy()
    env["MEDNAFEN_NOPOPUPS"] = "1"
    env["MEDNAFEN_NOSTDREDIR"] = "1"

    redirected_logs: list[Path] = []
    runner_label = ""

    common_args = [
        "-force_module",
        "ss",
        "-ss.midi",
        "stdout",
        "-sound",
        "0",
        "-video.driver",
        "softfb",
        "-cd.image_memcache",
        "1",
    ]

    firmware_dir = root / "Emulators" / "mednafen" / "firmware"
    if args.docker_image:
        cue_in_container = docker_work_path(root, cue)
        if cue_in_container is None:
            print("Docker mode requires the CUE to be inside the repository", file=sys.stderr)
            return 1

        firmware_in_container = docker_work_path(root, firmware_dir)
        mednafen_args = [*common_args]
        if firmware_dir.exists() and firmware_in_container:
            mednafen_args.extend(["-filesys.path_firmware", firmware_in_container])
        mednafen_args.append(cue_in_container)

        env["SDL_VIDEODRIVER"] = env.get("SDL_VIDEODRIVER", "dummy")
        env["SDL_AUDIODRIVER"] = env.get("SDL_AUDIODRIVER", "dummy")
        env["XDG_RUNTIME_DIR"] = env.get("XDG_RUNTIME_DIR", "/tmp")

        cmd = [
            "docker",
            "run",
            "--rm",
            "--entrypoint",
            "/usr/bin/timeout",
            "-v",
            f"{root}:/work",
            "-w",
            "/work",
            "-e",
            "SDL_VIDEODRIVER",
            "-e",
            "SDL_AUDIODRIVER",
            "-e",
            "XDG_RUNTIME_DIR",
            "-e",
            "MEDNAFEN_NOPOPUPS=1",
            "-e",
            "MEDNAFEN_NOSTDREDIR=1",
            "-e",
            "MEDNAFEN_HOME=/tmp/mednafen-home",
            args.docker_image,
            f"{args.timeout:g}s",
            "/opt/mednafen-ss-dev/bin/mednafen",
            *mednafen_args,
        ]
        runner_label = f"docker_image={args.docker_image}"
        subprocess_timeout = args.timeout + 10.0
    else:
        mednafen = find_mednafen(root, args.mednafen)
        if mednafen is None:
            print("Missing mednafen/mednafen.exe", file=sys.stderr)
            return 1
        mednafen = mednafen.resolve()

        mednafen_home = root / ".mednafen-home"
        mednafen_home.mkdir(parents=True, exist_ok=True)

        exe_dir = mednafen.parent
        redirected_logs = [exe_dir / "stdout.txt", exe_dir / "stderr.txt"]
        for redirected in redirected_logs:
            try:
                redirected.unlink()
            except FileNotFoundError:
                pass
            except OSError:
                pass

        env["MEDNAFEN_HOME"] = str(mednafen_home)

        cmd = [str(mednafen), *common_args]
        if firmware_dir.exists():
            cmd.extend(["-filesys.path_firmware", str(firmware_dir)])
        cmd.append(str(cue))
        runner_label = f"mednafen={mednafen}"
        subprocess_timeout = args.timeout

    timed_out = False
    return_code = 0
    try:
        completed = subprocess.run(
            cmd,
            cwd=root,
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            errors="replace",
            timeout=subprocess_timeout,
        )
        output = completed.stdout or ""
        return_code = completed.returncode
        timed_out = return_code == 124
    except subprocess.TimeoutExpired as exc:
        timed_out = True
        output = exc.stdout or ""
        if isinstance(output, bytes):
            output = output.decode("utf-8", errors="replace")
        return_code = 124

    redirected_output = ""
    for redirected in redirected_logs:
        text = read_text_if_exists(redirected)
        if text:
            redirected_output += f"\n--- {redirected.name} ---\n{text}"

    combined = output + redirected_output
    log_path.write_text(combined, encoding="utf-8", errors="replace")

    combined_lower = combined.lower()
    failed = [marker for marker in FAIL_MARKERS if marker.lower() in combined_lower]
    has_boot = REQUIRED_MARKERS[0] in combined
    has_pass = REQUIRED_MARKERS[1] in combined

    print(runner_label)
    print(f"cue={cue}")
    print(f"log={log_path}")
    print(f"returncode={return_code} timed_out={timed_out}")

    if failed:
        print("failure_markers=" + ", ".join(failed), file=sys.stderr)
        return 1
    if not has_boot:
        print("missing [BOOT]", file=sys.stderr)
        return 1
    if not has_pass:
        if timed_out:
            print("timeout before [PASS]", file=sys.stderr)
        else:
            print("missing [PASS]", file=sys.stderr)
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
