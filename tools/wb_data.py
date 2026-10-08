#!/usr/bin/env python3
"""Committed WorldBuilder analysis data, so seats need no Ghidra or re-extraction.

The WorldBuilder tools read their inputs from build/wb/ (ignored). Producing
them takes a Ghidra install and minutes of analysis, so the results are
committed, xz-compressed, under reverse/wb/:

  wb_functions.jsonl.xz   tools/pe_features.py on worldbuilder.exe (--wb-names)
  gd_functions.jsonl.xz   tools/pe_features.py on game.dat (--augment-starts)
  matches_full.jsonl.xz   tools/wb_match.py, gold-seeded
  wb_decomp.jsonl.xz      tools/wb_decompile.py: {"wb_va", "c"} per function

ensure(name) unpacks one into build/wb/ when it is missing or older than its
archive; ensure_decomp() unpacks the decompiled bodies into build/wb/decomp/.
A locally regenerated file newer than the archive is left alone.

    wb_data.py unpack        unpack everything (what the tools do on demand)
    wb_data.py pack          re-pack build/wb/ into reverse/wb/ after a refresh
"""
import argparse
import json
import lzma
import os
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ARCHIVE_DIR = ROOT / "reverse" / "wb"
WB_DIR = ROOT / "build" / "wb"
DECOMP_DIR = WB_DIR / "decomp"
FILES = ("wb_functions.jsonl", "gd_functions.jsonl", "matches_full.jsonl")
DECOMP_ARCHIVE = ARCHIVE_DIR / "wb_decomp.jsonl.xz"
DECOMP_STAMP = DECOMP_DIR / ".unpacked"


def _stale(target, archive):
    return archive.exists() and (not target.exists()
                                 or target.stat().st_mtime < archive.stat().st_mtime)


def ensure(name):
    """Path of build/wb/<name>, unpacked from reverse/wb/<name>.xz if needed."""
    target, archive = WB_DIR / name, ARCHIVE_DIR / f"{name}.xz"
    if _stale(target, archive):
        WB_DIR.mkdir(parents=True, exist_ok=True)
        tmp = target.with_suffix(target.suffix + ".tmp")
        with lzma.open(archive, "rb") as src, open(tmp, "wb") as dst:
            while chunk := src.read(1 << 20):
                dst.write(chunk)
        os.replace(tmp, target)
    return target


def ensure_decomp():
    """build/wb/decomp/, filled from the committed decompiles if not yet done."""
    if _stale(DECOMP_STAMP, DECOMP_ARCHIVE):
        DECOMP_DIR.mkdir(parents=True, exist_ok=True)
        with lzma.open(DECOMP_ARCHIVE, "rt", encoding="utf-8") as src:
            for line in src:
                rec = json.loads(line)
                path = DECOMP_DIR / f"{rec['wb_va']}.c"
                if not path.exists():
                    path.write_text(rec["c"], encoding="utf-8")
        DECOMP_STAMP.touch()
    return DECOMP_DIR


def pack():
    """Write build/wb/ results into reverse/wb/ for committing."""
    ARCHIVE_DIR.mkdir(parents=True, exist_ok=True)
    for name in FILES:
        with open(WB_DIR / name, "rb") as src, lzma.open(ARCHIVE_DIR / f"{name}.xz", "wb", preset=9) as dst:
            while chunk := src.read(1 << 20):
                dst.write(chunk)
    with lzma.open(DECOMP_ARCHIVE, "wt", encoding="utf-8", preset=9) as dst:
        for path in sorted(DECOMP_DIR.glob("*.c")):
            dst.write(json.dumps({"wb_va": path.stem, "c": path.read_text(encoding="utf-8", errors="replace")}) + "\n")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=("unpack", "pack"))
    args = ap.parse_args(argv)
    if args.action == "pack":
        pack()
    else:
        for name in FILES:
            ensure(name)
        ensure_decomp()
    print(f"{args.action}: done")


if __name__ == "__main__":
    sys.exit(main())
