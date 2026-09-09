#!/usr/bin/env python3
"""Separate real divergence from relocation noise in a near-miss body.

A first-difference report is useless once the two streams desync, and a raw
byte diff drowns the signal: every `push 0` against `push 0xbd2098` and every
`call 0x2a` against `call 0x4e5420` is a relocation site that `build.py` fills
from retail at claim time. Those are NOT differences. Reading them as
differences is how DX8Caps::Vendor_Specific_Hacks looked like 625 defects when
it had two, and both were findable in a minute once the noise was filtered.

The method, in the order the answers are worth having:

  1. Align the two instruction streams on MNEMONICS ONLY, so operand noise
     cannot desync the alignment.
  2. Inside aligned runs, report operand differences -- and CLASSIFY them.
     A repeated `[reg+disp]` difference of one constant delta is a class laid
     out differently in BFME, and is worth the whole unit rather than one body.
     A branch-target difference is a consequence of a length difference
     elsewhere, never a cause. A push/call immediate difference is a relocation.
  3. Report structural insert/replace regions. A region where retail simply
     ENDS EARLIER is a behaviour difference (code the reference tree has and
     BFME does not), not a codegen difference.
  4. Report the per-instruction SIZE delta, which says whether the remaining
     excess is one region or spread across the body.

  python3 tools/align_diff.py <source.cpp> <mangled-name> <rva-hex> [size]

Size defaults to where retail's `cc` padding starts, NOT to the emitted length
and NOT to whatever a queue recorded -- reloc_names.csv has been wrong (it
records DX8Caps::Check_Depth_Stencil_Support as 122 bytes when the real
boundary is 146, the 24 bytes between being the function's own jump table).
"""
import sys
import difflib
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
import capstone
from locate import object_functions

# Immediates this big are addresses the linker chose, so a difference in one is
# a relocation the gate fills from retail rather than a defect in our source.
RELOC_IMM = 0x400000


def find_boundary(rva, hint):
    """Where retail's cc padding starts, searching out from the size hint."""
    window = build.read_target_bytes(rva, hint + 0x400)
    for i in range(max(0, hint - 64), len(window) - 4):
        if window[i:i + 4] == b"\xcc\xcc\xcc\xcc":
            return i
    return None


def disasm(md, blob):
    return [(i.address, i.mnemonic, i.op_str, i.size) for i in md.disasm(blob, 0)]


def classify(a_ops, b_ops):
    """Why do these two operand strings differ?"""
    if "ptr [" in b_ops and "ptr [" in a_ops:
        return "memory"
    for tok in b_ops.replace(",", " ").replace("[", " ").replace("]", " ").split():
        if tok.startswith("0x"):
            try:
                value = int(tok, 16)
            except ValueError:
                continue
            if value >= RELOC_IMM:
                return "reloc"
    if b_ops.startswith("0x") and a_ops.startswith("0x"):
        return "branch"
    return "register"


def displacement(ops):
    """The [reg+disp] displacement in an operand string, if there is one.

    Bases esp and ebp are EXCLUDED. A uniform delta across stack slots is a
    frame that is one spill wider, which is the allocator wall; a uniform delta
    across member accesses is a class laid out differently, which is worth the
    whole unit. Reporting the first as the second sends the reader to shim a
    header over what is really a register-allocation difference.
    """
    if "ptr [" not in ops:
        return None
    inner = ops.split("ptr [", 1)[1].split("]", 1)[0]
    base = inner.split()[0] if inner.split() else ""
    if base in ("esp", "ebp"):
        return None
    if "+ 0x" not in inner:
        return None
    try:
        return int(inner.rsplit("+ ", 1)[1], 16)
    except ValueError:
        return None


def main():
    if len(sys.argv) < 4:
        print(__doc__)
        return 2
    src_rel, name, rva_hex = sys.argv[1], sys.argv[2], sys.argv[3]
    rva = int(rva_hex, 16)

    src = build.ROOT / src_rel
    obj = build.obj_path(src)
    if not obj.exists():
        build.compile_source(src, obj)
    emitted = {n: (s, r) for n, s, r in object_functions(obj)}
    if name not in emitted:
        print(f"NOT EMITTED by {src_rel}: {name}")
        print("A marker naming a symbol the object file does not use is common;")
        print("match by emitted body LENGTH instead, then use the exact name the")
        print("object gives. Also delete the .obj first -- it may be stale.")
        for n, span, _ in sorted(object_functions(obj), key=lambda t: -len(t[1]))[:12]:
            print(f"    {len(span.rstrip(chr(0xcc).encode())):6d}  {n[:88]}")
        return 1

    ours = emitted[name][0].rstrip(b"\xcc")
    hint = int(sys.argv[4]) if len(sys.argv) > 4 else len(ours)
    size = find_boundary(rva, hint)
    if size is None:
        size = hint
        print(f"note: no cc run within 0x400 of the hint -- using {size}. The body "
              f"may abut its neighbour (common) or the address may not be a "
              f"boundary (not fine).")
    target = build.read_target_bytes(rva, size)

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    A, B = disasm(md, ours), disasm(md, target)
    print(f"ours {len(ours)} B / {len(A)} insns   retail {size} B / {len(B)} insns"
          f"   (retail cc padding starts at +{size})")

    sm = difflib.SequenceMatcher(a=[x[1] for x in A], b=[x[1] for x in B],
                                 autojunk=False)
    kinds = Counter()
    deltas = Counter()
    structural = []
    size_delta = 0
    operand_lines = []

    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != "equal":
            d = sum(x[3] for x in A[i1:i2]) - sum(x[3] for x in B[j1:j2])
            size_delta += d
            structural.append((tag, B[j1][0] if j1 < len(B) else -1, d,
                               B[j1:j2], A[i1:i2]))
            continue
        for k in range(i2 - i1):
            a, b = A[i1 + k], B[j1 + k]
            if a[3] != b[3]:
                size_delta += a[3] - b[3]
            if a[2] == b[2]:
                continue
            kind = classify(a[2], b[2])
            kinds[kind] += 1
            if kind == "memory":
                da, db = displacement(a[2]), displacement(b[2])
                if da is not None and db is not None and da != db:
                    deltas[db - da] += 1
            if kind in ("memory", "register"):
                operand_lines.append(
                    f"  [{kind:8s}] retail +0x{b[0]:04x}  {b[1]} {b[2]}"
                    f"\n{'':14s}ours              {a[1]} {a[2]}")

    print("\n== operand differences by cause ==")
    for k in ("reloc", "branch", "memory", "register"):
        note = {"reloc": "filled from retail by the gate -- NOT defects",
                "branch": "a consequence of a length difference, never a cause",
                "memory": "member offsets -- a repeated constant delta is a LAYOUT find",
                "register": "allocation choices -- the wall, unless few and local"}[k]
        print(f"  {kinds[k]:5d}  {k:9s} {note}")

    if deltas:
        print("\n== [reg+disp] deltas (retail minus ours) ==")
        print("  (esp/ebp bases excluded: a uniform delta over STACK slots is a"
              " wider frame,\n   i.e. the allocator wall, not a layout finding)")
        for d, n in deltas.most_common(6):
            flag = "  <-- LAYOUT FINDING" if n >= 2 else ""
            print(f"  {n:5d} site(s)  {d:+#x}{flag}")

    if operand_lines:
        print("\n== memory/register operand differences ==")
        for line in operand_lines[:24]:
            print(line)
        if len(operand_lines) > 24:
            print(f"  ... {len(operand_lines) - 24} more")

    print(f"\n== structural regions: {len(structural)} ==")
    for tag, at, d, bs, as_ in structural:
        print(f"  [{tag}] retail +0x{at:x}  size delta {d:+d}"
              f"  (retail {len(bs)} insns / ours {len(as_)} insns)")
        for b in bs[:8]:
            print(f"      retail 0x{b[0]:04x}  {b[1]} {b[2]}")
        for a in as_[:8]:
            print(f"      ours   0x{a[0]:04x}  {a[1]} {a[2]}")

    print(f"\ntotal size delta: {size_delta:+d}  (ours {len(ours)}, retail {size})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
