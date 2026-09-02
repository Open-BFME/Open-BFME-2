"""Identify an unnamed body from the vtable it sits in.

A virtual has no caller to trace - every call to it goes through a vtable
slot - so callers_of.py reports nothing and the usual identification routes
stop there. But the slot itself is evidence: a body found in a vtable is a
virtual of that class, its slot index says which one, and any neighbouring
slot that is already named identifies the class.

For each address given, this searches the image for a DIR32 word holding its
VA, then prints the surrounding words with their ledger names. Read the run
as a vtable only when the words around it are plausible code addresses; the
scan is a raw word search and will also hit relocation tables and constant
pools. The number of consecutive code words is itself informative - three
slots of destructor plus two functions is the money_get shape, eight or more
is a num_get.

Usage: python3 tools/vtable_owner.py 0xC000 0xDAA0 ...
"""
import sys, csv, struct, pathlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import build

BASE = 0x400000
SPAN = 8


def ledger_names():
    names = {}
    for path in ("reverse/functions.csv", "reverse/symbols.csv"):
        for row in csv.DictReader(open(path, newline="", encoding="utf-8-sig")):
            text = row.get("target_rva") or row.get("address")
            try:
                names.setdefault(int(text, 16), row["name"])
            except (TypeError, ValueError):
                continue
    return names


def main():
    if len(sys.argv) < 2:
        raise SystemExit(__doc__)
    names = ledger_names()
    data, _ = build.exe_image()
    for text in sys.argv[1:]:
        rva = int(text, 16)
        needle = struct.pack("<I", BASE + rva)
        hit = data.find(needle)
        if hit < 0:
            print(f"{rva:#010x}: no word in the image holds this address")
            continue
        print(f"{rva:#010x}")
        for k in range(-SPAN, SPAN + 1):
            off = hit + 4 * k
            if off < 0 or off + 4 > len(data):
                continue
            word = struct.unpack("<I", data[off : off + 4])[0] - BASE
            here = "<<<" if k == 0 else "   "
            print(f"  {k:+3d} {word:#010x} {here} {names.get(word, '')[:70]}")


if __name__ == "__main__":
    main()
