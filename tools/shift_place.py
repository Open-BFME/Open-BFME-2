#!/usr/bin/env python3
"""Masked whole-.text search with every member offset shifted by a delta.

place_bodies.py is structurally blind to a class laid out differently in BFME
than in the header a unit compiles against.  Its search masks the four bytes
under each relocation and compares everything else -- including the
displacement in every `[this + disp]` -- so if the class is four bytes out,
every body in the unit misses, and the unit reports zero placements no matter
how many of its bodies are otherwise byte-perfect.  part_buf.cpp reported zero
while holding 9,267 bytes of exact ParticleBufferClass code.

This re-encodes the displacements by a candidate delta before searching.  A
unique hit says two things at once: where that body lives, and that the class it
reaches through `this` is that many bytes different from the one being compiled.
The second is worth far more than the first, because one header correction
unblocks every sibling -- correcting sizeof(RenderObjClass) from 0xC8 to 0xC4
took part_buf.cpp from 27 rows to 73 and hlod.cpp from 47 to 63.

What is moved, and what is not:

  * only displacements off a base register that is NOT esp or ebp, so stack
    slots stay put and only member accesses move;
  * only |disp| >= 0x18, because small displacements are as likely to be a
    local struct as a class member;
  * only forms that keep their encoded width, so the body keeps its length and
    every other byte still has to match.

A hit is a lead, not a landing.  Confirm it the way any layout claim has to be
confirmed -- find a SECOND body the corrected layout renames or re-homes, then
make the header change and let ./build.sh judge the unit as a whole.  Expect a
correction to invalidate rows that were placed by single-hit search under the
old layout; a seven-byte getter at an unaligned address with nothing claimed
near it was never that function.

  python3 tools/shift_place.py <source.cpp> [...]
  python3 tools/shift_place.py --deltas -4,4 <source.cpp>

Reads objects a build already produced; compiles nothing.
"""
import argparse
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
from locate import object_functions

DEFAULT_DELTAS = (-4, 4, -8, 8, -12, 12, -16, 16)


def member_sites(md, mem_op, esp, ebp, body, floor):
    """(byte offset, encoded width, value) for each [reg+disp] member access."""
    out = []
    for ins in md.disasm(body, 0):
        if ins.disp_size not in (1, 4) or ins.disp_offset == 0:
            continue
        for op in ins.operands:
            if op.type != mem_op or op.mem.base in (0, esp, ebp):
                continue
            if abs(op.mem.disp) < floor:
                continue
            out.append((ins.address + ins.disp_offset, ins.disp_size, op.mem.disp))
            break
    return out


def shifted(body, sites, delta):
    """The body with every member displacement moved, or None if it would grow."""
    buf = bytearray(body)
    for offset, width, value in sites:
        moved = value + delta
        if width == 1:
            if not -128 <= moved <= 127:
                return None
            buf[offset] = moved & 0xFF
        else:
            struct.pack_into("<i", buf, offset, moved)
    return bytes(buf)


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("sources", nargs="+")
    parser.add_argument("--deltas", default=",".join(str(d) for d in DEFAULT_DELTAS),
                        help="comma-separated byte deltas to try")
    parser.add_argument("--min", type=int, default=40, dest="minimum",
                        help="ignore bodies shorter than this")
    parser.add_argument("--min-sites", type=int, default=3,
                        help="ignore bodies touching fewer members than this; one "
                             "or two sites is not evidence of a layout")
    parser.add_argument("--floor", type=lambda s: int(s, 0), default=0x18,
                        help="smallest displacement treated as a class member")
    args = parser.parse_args()

    try:
        import capstone
        from capstone.x86 import X86_OP_MEM, X86_REG_ESP, X86_REG_EBP
    except ImportError:
        raise SystemExit("this needs capstone; see tools/drift_classify.py for the "
                         "same dependency")
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True

    deltas = [int(d) for d in args.deltas.split(",") if d.strip()]

    image, sections = build.exe_image()
    text = next(s for s in sections if s["name"] == ".text")
    blob = image[text["raw_pointer"]:text["raw_pointer"] + text["size"]]
    text_rva = text["rva"]

    rows = build.load_all_function_rows()
    claimed = sorted((int(r["target_rva"], 16),
                      int(r["target_rva"], 16) + int(r["target_size"]), r["name"])
                     for r in rows)
    held = {r["name"] for r in rows}

    def owner(rva):
        for start, end, name in claimed:
            if start <= rva < end:
                return name
        return None

    total = 0
    for source in args.sources:
        obj = build.obj_path(build.ROOT / source)
        if not obj.exists():
            print(f"# no object on disk for {source}", file=sys.stderr)
            continue
        try:
            emitted = list(object_functions(obj))
        except Exception as exc:
            print(f"# {source}: unreadable object ({exc})", file=sys.stderr)
            continue
        found = []
        for name, span, relocs in emitted:
            if name in held or not name.startswith("?"):
                continue
            body = span.rstrip(b"\xcc")
            if len(body) < args.minimum:
                continue
            sites = member_sites(md, X86_OP_MEM, X86_REG_ESP, X86_REG_EBP,
                                 body, args.floor)
            if len(sites) < args.min_sites:
                continue
            mask = bytearray(b"\x01" * len(body))
            for offset, _kind, _symbol in relocs:
                for step in range(4):
                    if offset + step < len(mask):
                        mask[offset + step] = 0
            for delta in deltas:
                probe = shifted(body, sites, delta)
                if probe is None:
                    continue
                pattern = b"".join(re.escape(bytes([byte])) if mask[i] else b"."
                                   for i, byte in enumerate(probe))
                hits = [m.start() + text_rva
                        for m in re.finditer(pattern, blob, re.DOTALL)]
                hits = [h for h in hits if not owner(h)]
                if len(hits) == 1:
                    found.append((len(body), delta, hits[0], len(sites), name))
                    break
        if found:
            print(f"\n== {source} ==")
            for size, delta, rva, nsites, name in sorted(found, reverse=True):
                print(f"  delta {delta:+3d}  0x{rva:08X}  {size:6d}B  "
                      f"{nsites} member site(s)")
                print(f"      {name}")
                total += size
    if total:
        print(f"\n{total} bytes behind a layout difference")


if __name__ == "__main__":
    main()
