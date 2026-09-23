#!/usr/bin/env python3
"""Write the seed list for tools/ghidra/seed_ledger.java (`rva<TAB>size<TAB>name`).

Sources: functions.csv rows (with extents), symbols.csv pins, code exports and
reloc_names.csv (starts only). One row per address; a sized row wins.

Usage: python3 tools/ghidra_seed.py > build/ghidra/seeds.tsv
"""
import csv
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
REV = ROOT / "reverse"


def main():
    seeds = {}

    def add(rva, size, name):
        old = seeds.get(rva)
        if old is None or (old[0] == 0 and size > 0):
            seeds[rva] = (size, name)

    with (REV / "functions.csv").open(newline="") as f:
        for row in csv.DictReader(f):
            if row["target_rva"]:
                add(int(row["target_rva"], 16), int(row["target_size"]), row["name"])
    with (REV / "symbols.csv").open(newline="") as f:
        for row in csv.reader(f):
            if len(row) >= 2 and row[1].startswith("0x"):
                add(int(row[1], 16), 0, row[0])
    with (REV / "exports.csv").open(newline="") as f:
        for row in csv.reader(f):
            if len(row) >= 6 and row[1].startswith("0x") and row[4] == "code":
                add(int(row[1], 16), 0, row[5])
    names = REV / "reloc_names.csv"
    if names.exists():
        with names.open(newline="") as f:
            for row in csv.DictReader(f):
                add(int(row["target_rva"], 16), 0, row["name"])

    out = sys.stdout
    out.write("# rva\tsize\tname\n")
    for rva in sorted(seeds):
        size, name = seeds[rva]
        out.write(f"0x{rva:X}\t{size}\t{name.replace(chr(9), ' ')}\n")
    print(f"{len(seeds)} seeds", file=sys.stderr)


if __name__ == "__main__":
    main()
