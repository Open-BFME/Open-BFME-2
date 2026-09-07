#!/usr/bin/env python3
"""Rank what the tree could land RIGHT NOW from bodies it already compiles.

Both `place_bodies.py` and the `next_work.py` queues answer "where might this
function be?".  This answers the cheaper question that sits beside it: for every
function some unit already EMITS and some ledger already gives an ADDRESS to,
how close are those bytes to retail?  A body that is already exact has been
sitting there costing nothing but an add_match call, and one that is close in a
specific, named way tells you which lever it wants.

Addresses come from `reverse/symbols.csv` (pins) and `reverse/reloc_names.csv`
(names recovered from call sites).  A symbol is skipped when functions.csv
already claims the name, or already claims that address under another name --
that second case is an ICF fold, and choosing which of the folded names owns the
body would be inventing an identity.

Two reports:

  exact    the emitted bytes equal retail's everywhere the linker did not choose
           them, i.e. ignoring the four bytes under each relocation.  Hand these
           to add_match; it does the real check with addresses resolved.
  layout   the instruction stream agrees but the memory displacements are all
           off by ONE CONSTANT.  That is a class laid out differently in BFME
           than in the headers being compiled, and it is worth far more than the
           one body: CameraClass was found this way and fixing its layout took
           camera.cpp from 17 rows to 31.

Neither report is proof.  `exact` masks relocations, so a row whose only defect
is a wrong callee address still shows as exact -- add_match will refuse it and
name the callee, which is how you learn the pin.  `layout` cannot tell you WHICH
member moved, only that the ones this body touches are shifted; find a second
body the corrected layout renames before believing it.

  python3 tools/unclaimed_scan.py                 # both reports
  python3 tools/unclaimed_scan.py --mode exact
  python3 tools/unclaimed_scan.py --mode layout
  python3 tools/unclaimed_scan.py --compile        # build missing objects first

Reads whatever objects a build already produced, so it is safe to run beside
other work unless --compile is given.
"""
import argparse
import collections
import csv
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
from locate import object_functions

ROOT = build.ROOT
REL32, DIR32 = 0x0014, 0x0006


def believed_addresses(claimed_name, claimed_rva):
    """name -> rva, for every unclaimed function either ledger gives a home."""
    want = {}
    reloc = ROOT / "reverse" / "reloc_names.csv"
    if reloc.exists():
        with reloc.open(newline="", encoding="utf-8") as fh:
            for row in csv.DictReader(fh):
                want.setdefault(row["name"], int(row["target_rva"], 16))
    for line in (ROOT / "reverse" / "symbols.csv").read_text(
            encoding="utf-8", errors="replace").splitlines()[1:]:
        parts = line.split(",")
        if len(parts) >= 2 and parts[1].startswith("0x"):
            want.setdefault(parts[0], int(parts[1], 16))
    return {n: a for n, a in want.items()
            if n not in claimed_name and a not in claimed_rva}


def masked_offsets(relocs):
    out = set()
    for off, rtype, _ in relocs:
        if rtype in (REL32, DIR32):
            out.update(range(off, off + 4))
    return out


def disp_list(md, buf):
    """(mnemonic, size, displacements) per instruction."""
    out = []
    for ins in md.disasm(buf, 0):
        disps = tuple(op.mem.disp for op in ins.operands
                      if op.type == 3 and op.mem.base != 0)   # X86_OP_MEM
        out.append((ins.mnemonic, ins.size, disps))
    return out


def constant_shift(md, target, ours):
    """The single delta every differing displacement shares, or None."""
    a, b = disp_list(md, target), disp_list(md, ours)
    n = min(len(a), len(b))
    if n < 8:
        return None
    if sum(1 for x, y in zip(a, b) if x[0] != y[0]) > n * 0.15:
        return None                       # not the same code, so not a shift
    deltas, sites = collections.Counter(), 0
    for x, y in zip(a, b):
        if len(x[2]) != len(y[2]):
            return None
        for dx, dy in zip(x[2], y[2]):
            if dx != dy:
                deltas[dy - dx] += 1
                sites += 1
    if sites < 2 or not deltas:
        return None
    delta, hits = deltas.most_common(1)[0]
    return (delta, hits, sites) if hits >= sites * 0.7 else None


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--mode", choices=("both", "exact", "layout"), default="both")
    ap.add_argument("--compile", action="store_true",
                    help="build any missing object instead of skipping it")
    ap.add_argument("--min-size", type=int, default=1,
                    help="ignore bodies smaller than this many bytes")
    args = ap.parse_args()

    md = None
    if args.mode in ("both", "layout"):
        try:
            import capstone
            md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
            md.detail = True
        except ImportError:
            print("# capstone not installed - layout report skipped",
                  file=sys.stderr)

    rows = build.load_all_function_rows()
    claimed_name = {r["name"] for r in rows}
    claimed_rva = {int(r["target_rva"], 16) for r in rows}
    want = believed_addresses(claimed_name, claimed_rva)
    sources = sorted({r["source"] for r in rows
                      if r["source"].endswith((".c", ".cc", ".cpp"))
                      and "gen_asm" not in r["source"]
                      and "gen_small" not in r["source"]})

    exact, layout = [], []
    for src_rel in sources:
        src = ROOT / src_rel
        obj = build.obj_path(src)
        if not obj.exists():
            if not args.compile:
                continue
            try:
                build.compile_source(src, obj)
            except BaseException:
                continue
        try:
            emitted = list(object_functions(obj))
        except Exception:
            continue
        for name, span, relocs in emitted:
            rva = want.get(name)
            if rva is None:
                continue
            ours = span.rstrip(b"\xcc")
            size = len(ours)
            if size < args.min_size:
                continue
            try:
                target = build.read_target_bytes(rva, size + 1)
            except Exception:
                continue
            body = target[:size]
            if ours == body:
                exact.append((size, rva, name, src_rel, target[size] == 0xCC))
                continue
            masked = masked_offsets(relocs)
            if not any(k not in masked and ours[k] != body[k] for k in range(size)):
                exact.append((size, rva, name, src_rel, target[size] == 0xCC))
                continue
            if md is not None:
                shift = constant_shift(md, body, ours)
                if shift:
                    layout.append((shift[1], shift[0], size, rva, name, src_rel))

    if args.mode in ("both", "exact"):
        exact.sort(reverse=True)
        print("== exact modulo relocations ==")
        for size, rva, name, src_rel, padded in exact:
            print(f"{size:7d}B  0x{rva:08X}  {'cc-padded' if padded else 'abuts   '}"
                  f"  {src_rel}")
            print(f"           {name}")
        print(f"{len(exact)} candidate(s), {sum(e[0] for e in exact)} bytes\n")

    if args.mode in ("both", "layout") and md is not None:
        layout.sort(reverse=True)
        print("== constant member-offset shift (a class layout difference) ==")
        for hits, delta, size, rva, name, src_rel in layout:
            print(f"{hits:5d} site(s) {delta:+d}  {size}B  0x{rva:08X}  {src_rel}")
            print(f"           {name}")
        print(f"{len(layout)} candidate(s)")


if __name__ == "__main__":
    main()
