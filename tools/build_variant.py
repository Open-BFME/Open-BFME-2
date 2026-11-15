#!/usr/bin/env python3
"""Inspect the isolated modern build layout; never write verifier artifacts.

Called by build.sh --variant modern. This entry point deliberately has no
implicit action: a plan is not a compile, link, or verification result.
"""
import argparse
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFINES = ("BFME2_MODERN=1",)


def variant_paths(root, variant):
    """Validate every output directory, without creating or changing anything."""
    if variant != "modern":
        raise ValueError("only the explicit modern variant is supported here")
    root = Path(root).resolve(strict=True)
    paths = {name: root / "build" / "modern" / name
             for name in ("objects", "link", "reports")}
    for path in paths.values():
        for directory in (root / "build", root / "build/modern", path):
            # resolve follows Windows junctions as well as POSIX symlinks.
            if directory.resolve() != directory or directory.is_symlink():
                raise ValueError(f"redirected variant directory: {directory}")
            if directory.exists() and not directory.is_dir():
                raise ValueError(f"variant directory is a file: {directory}")
    return paths


def main(argv=None, *, root=ROOT):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--plan", action="store_true", required=True,
                        help="print validated output layout without compiling or writing")
    args = parser.parse_args(argv)
    try:
        paths = variant_paths(root, "modern")
    except (OSError, RuntimeError, ValueError) as error:
        parser.error(str(error))
    print(json.dumps({"variant": "modern", "action": "plan", "compiled": False,
                      "defines": list(DEFINES),
                      "paths": {key: str(value) for key, value in paths.items()}}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
