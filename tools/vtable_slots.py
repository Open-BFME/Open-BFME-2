#!/usr/bin/env python3
"""List every vftable the image's own RTTI names, and say which slots are free.

vtable_gaps.py finds vtables by shape - runs of words that look like .text
addresses - which is cheap and gives no identity, so its output has to be read
before it can be used. The image can do better than that. MSVC writes a
complete object locator immediately before each vftable, the locator points at
a type descriptor, and the descriptor carries the decorated class name. Walk
that chain and every vftable comes with the class it belongs to.

That identity is worth more than a byte search for exactly the functions a
byte search cannot reach. A three-byte `mov al, '.'; ret` places in a hundred
spots and identifies nothing; the same body sitting in slot 1 of numpunct<char>
is do_decimal_point and nothing else. Slot order is the evidence, so it pays to
know the rule MSVC follows: within one name, overloads go into the vtable in
REVERSE declaration order. num_put, ctype and messages all confirm it.

Slots the ledger already holds are printed with their names, which is how you
check a mapping: if the slots you can name land where the declaration order
says they should, the ones you cannot name are pinned by elimination.

Usage:
  python3 tools/vtable_slots.py [PATTERN] [--free-only] [--max-slots N]

PATTERN is a regular expression matched against the decorated class name
(default: every class). Nothing is written.
"""
import argparse
import csv
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build

# A vftable slot must land inside .text to be a function at all; anything else
# is the next locator, a data pointer, or the end of the table.
NAME_PATTERN = rb"\.\?A[VU][^\x00]{2,300}\x00"


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("pattern", nargs="?", default=".",
                        help="regex over the decorated class name")
    parser.add_argument("--free-only", action="store_true",
                        help="print only classes that have an unclaimed slot")
    parser.add_argument("--max-slots", type=int, default=32)
    args = parser.parse_args()
    wanted = re.compile(args.pattern)

    image, sections = build.exe_image()
    base = struct.unpack_from("<I", image, struct.unpack_from("<I", image, 0x3C)[0] + 24 + 28)[0]
    text = next(s for s in sections if s["name"] == ".text")
    text_lo, text_hi = text["rva"], text["rva"] + text["size"]

    def read(rva, count):
        return image[build.rva_to_file_offset(sections, rva):
                     build.rva_to_file_offset(sections, rva) + count]

    rows = build.load_all_function_rows()
    claimed = sorted((int(r["target_rva"], 16),
                      int(r["target_rva"], 16) + int(r["target_size"]),
                      r["name"]) for r in rows)

    def owner(rva):
        for start, end, name in claimed:
            if start <= rva < end:
                return name
        return None

    # Type descriptors and the locators/vftables that reference them can live in
    # different sections - in this image the names are in .data and the tables in
    # .rdata - so both are searched for both.
    blobs = [(s["rva"], image[s["raw_pointer"]:s["raw_pointer"] + s["size"]])
             for s in sections if s["name"] in (".data", ".rdata")]

    descriptors = {}
    for section_rva, blob in blobs:
        for match in re.finditer(NAME_PATTERN, blob):
            name = match.group(0)[:-1].decode("latin1")
            if wanted.search(name):
                descriptors[section_rva + match.start() - 8] = name

    def references(rva):
        needle = struct.pack("<I", rva + base)
        for section_rva, blob in blobs:
            for match in re.finditer(re.escape(needle), blob):
                yield section_rva + match.start()

    seen = set()
    for descriptor, name in sorted(descriptors.items(), key=lambda kv: kv[1]):
        for locator_field in references(descriptor):
            locator = locator_field - 12          # pTypeDescriptor is at +12
            for slot_field in references(locator):
                vftable = slot_field + 4          # the locator sits at [vftable-4]
                if (name, vftable) in seen:
                    continue
                seen.add((name, vftable))
                slots = []
                for index in range(args.max_slots):
                    try:
                        target = struct.unpack("<I", read(vftable + 4 * index, 4))[0] - base
                    except (ValueError, struct.error):
                        break
                    if not text_lo <= target < text_hi:
                        break
                    slots.append((index, target, owner(target)))
                if not slots:
                    continue
                if args.free_only and all(held for _, _, held in slots):
                    continue
                free = sum(1 for _, _, held in slots if not held)
                print("=== %s" % name)
                print("    vftable 0x%08X  %d slots, %d free" % (vftable, len(slots), free))
                for index, target, held in slots:
                    print("  %2d 0x%08X  %s" % (index, target, held or "FREE"))


if __name__ == "__main__":
    main()
