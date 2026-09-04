#!/usr/bin/env python3
"""Place a source file's *unnamed* bodies by masked byte search, and harvest the
callee addresses their call sites read.

harvest.py can only speak about a function the export table gives an address to.
That is a small fraction of what a translation unit emits: a unit compiled to
land one named function also emits every template body, helper and inline it
needed, and those were discarded because nothing knew where to look for them.

They are findable. Compile the unit, take one emitted body, and blank the four
bytes under each of its relocations - those are the only bytes the linker was
free to choose. What is left is a fixed pattern, and searching the whole of
.text for it either finds nothing, finds several places (the body is too
generic to identify, or the linker kept several copies), or finds exactly one.
Exactly one is a placement: that address holds that body.

A placement pays twice. Every REL32 in the placed body is now a byte-true call
site, so the displacement retail wrote there IS the callee's address - for a
callee nothing else in the ledger may know about. Those become symbols.csv
pins, which unblock the next body, which pins more callees. Run it to a
fixpoint.

What keeps it honest:

  * One name per address. Several names placing at one address means the linker
    folded them, and picking one would be inventing an identity, so all are
    dropped. A pin is the exception - a folded name has no body of its own to
    claim, only an address, and symbols.csv is additive for exactly that.
  * Placements must agree. If a body's call site reads an address that
    contradicts where that callee placed itself, or contradicts the ledger,
    both are dropped. The surviving set is mutually consistent.
  * The gate is the proof, not this. A wrong placement fails ./build.sh with the
    displacement it could not reproduce. Prune to a fixpoint: dropping a row
    can unresolve a caller that was green.
  * A re-run has no memory, so what the gate refused goes in
    reverse/place_denylist.txt with its reason and is not proposed again.

Usage:
  python3 tools/place_bodies.py [--apply] [--min N] <source.cpp> [<source.cpp> ...]

Without --apply it reports and writes nothing.
"""
import argparse
import collections
import csv
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build
import harvest

IMAGE_REL_I386_REL32 = 20
DENYLIST = "reverse/place_denylist.txt"
BODY_NOTE = "placed by masked whole-.text search of the compiled body - single hit"
PIN_NOTE = "address read from the REL32 displacement at a placed body"
PIN_NOTE_FOLD = (PIN_NOTE + "; the body there is held under another "
                 "instantiation name and the two folded")


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("sources", nargs="+")
    parser.add_argument("--apply", action="store_true",
                        help="write the pins and append the rows (default: report only)")
    parser.add_argument("--min", type=int, default=20, dest="minimum",
                        help="ignore bodies shorter than this; a short body is "
                             "generic enough that a single hit means little")
    args = parser.parse_args()

    image, sections = build.exe_image()
    text = next(s for s in sections if s["name"] == ".text")
    blob = image[text["raw_pointer"]:text["raw_pointer"] + text["size"]]
    text_rva = text["rva"]

    rows = build.load_all_function_rows()
    claimed = sorted((int(r["target_rva"], 16),
                      int(r["target_rva"], 16) + int(r["target_size"]),
                      r["name"]) for r in rows)
    ledger = {r["name"]: int(r["target_rva"], 16) for r in rows}
    pinned = {}
    with (build.ROOT / "reverse" / "symbols.csv").open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            pinned.setdefault(row["name"], int(row["address"], 16))

    def owner(rva):
        for start, end, name in claimed:
            if start <= rva < end:
                return name
        return None

    def call_target(rva, offset):
        displacement = struct.unpack_from("<i", blob, rva - text_rva + offset)[0]
        return rva + offset + 4 + displacement

    denied = set()
    denylist = build.ROOT / DENYLIST
    if denylist.exists():
        for line in denylist.read_text(encoding="utf-8").splitlines():
            line = line.strip()
            if line and not line.startswith("#"):
                denied.add(line)

    placed = {}
    by_address = collections.defaultdict(set)
    for source in args.sources:
        try:
            obj = harvest.compile_obj(build.Path(source), [])
        except SystemExit:
            print("## COMPILE FAILED", source, file=sys.stderr)
            continue
        data = obj.read_bytes()
        emitted = sorted({s["name"] for s in build.read_object_symbols(data)
                          if s["section"] > 0 and s["name"].startswith("?")})
        for name in emitted:
            if name in ledger or name in placed or name in denied:
                continue
            try:
                body, relocs = build.read_object_symbol_bytes(obj, name)
            except ValueError:
                continue
            body = body.rstrip(b"\xcc")
            if len(body) < args.minimum:
                continue
            fixed = bytearray(b"\x01" * len(body))
            for offset, kind, symbol in relocs:
                for step in range(4):
                    if offset + step < len(fixed):
                        fixed[offset + step] = 0
            pattern = b"".join(re.escape(bytes([byte])) if fixed[index] else b"."
                               for index, byte in enumerate(body))
            hits = [m.start() + text_rva for m in re.finditer(pattern, blob, re.DOTALL)]
            if len(hits) != 1 or owner(hits[0]):
                continue
            placed[name] = (hits[0], len(body), source,
                            [(o, k, s) for o, k, s in relocs if k == IMAGE_REL_I386_REL32])
            by_address[hits[0]].add(name)

    for address, names in by_address.items():
        if len(names) > 1:
            for name in names:
                placed.pop(name, None)

    changed = True
    while changed:
        changed = False
        for name in list(placed):
            rva, size, source, relocs = placed[name]
            for offset, kind, symbol in relocs:
                known = ledger.get(symbol, pinned.get(symbol, placed.get(symbol, (None,))[0]))
                if known is not None and known != call_target(rva, offset):
                    del placed[name]
                    changed = True
                    break

    pins = {}
    for name, (rva, size, source, relocs) in placed.items():
        for offset, kind, symbol in relocs:
            if symbol in ledger or symbol in placed or symbol in pinned:
                continue
            pins.setdefault(symbol, set()).add(call_target(rva, offset))
    pins = {symbol: addresses.pop() for symbol, addresses in pins.items()
            if len(addresses) == 1}

    print("## %d bodies, %d pins" % (len(placed), len(pins)))
    if args.apply and pins:
        symbols = build.ROOT / "reverse" / "symbols.csv"
        content = symbols.read_text(encoding="utf-8")
        if not content.endswith("\n"):
            content += "\n"
        for symbol, address in sorted(pins.items()):
            note = PIN_NOTE_FOLD if owner(address) else PIN_NOTE
            content += "%s,0x%08X,%s\n" % (symbol, address, note)
        with symbols.open("w", encoding="utf-8", newline="") as handle:
            handle.write(content)

    for name, (rva, size, source, relocs) in sorted(placed.items(), key=lambda kv: -kv[1][1]):
        print("BODY\t0x%08X\t%d\t%s\t%s" % (rva, size, source, name))
        if args.apply:
            result = subprocess.run(
                [sys.executable, str(build.ROOT / "tools" / "add_match.py"), name,
                 "0x%08X" % rva, str(size), source, "--notes", BODY_NOTE, "--no-verify"],
                cwd=build.ROOT, capture_output=True, text=True)
            if result.returncode:
                print("   REFUSED:", result.stdout.strip().splitlines()[-1][:200])
    if args.apply:
        print("## rows are UNVERIFIED - run ./build.sh and prune what it refuses, "
              "to a fixpoint")


if __name__ == "__main__":
    main()
