#!/usr/bin/env python3
"""Side-by-side disassembly of a compiled scratch symbol against retail.

Patches relocations against a caller-supplied symbol map the way
tools/build.py:compile_function does, then prints the two listings with a
marker on every line whose encoding differs, plus the differing byte offsets.

Usage: sidebyside.py <scratch.cpp> <symbol> <rva> <size> [name=addr ...]
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402
from variant import resolve_bytes  # noqa: E402

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
import importlib
em = importlib.import_module("tools.explain_mismatch")  # noqa: E402

ROOT = build.ROOT


def main():
    src = (ROOT / sys.argv[1]).resolve()
    wanted = sys.argv[2]
    rva = int(sys.argv[3], 16)
    size = int(sys.argv[4])
    symbol_map = {}
    for item in sys.argv[5:]:
        name, addr = item.rsplit("=", 1)
        symbol_map.setdefault(name, []).append(int(addr, 16))

    out = ROOT / "build" / "scratch" / (src.stem + ".obj")
    if not out.exists():
        raise SystemExit(f"{out} missing -- run tools/variant.py first")
    if wanted.startswith("="):
        matches = [s for s in build.defined_code_symbols(out) if s == wanted[1:]]
    else:
        matches = [s for s in build.defined_code_symbols(out) if wanted in s]
    if len(matches) != 1:
        raise SystemExit(f"{wanted!r} -> {matches}")

    compiled, relocs = build.read_object_symbol_bytes(out, matches[0], code_only=True)
    retail = build.read_target_bytes(rva, size)
    pad = bytes(max(0, size - len(compiled)))
    resolved, unresolved = resolve_bytes(
        (compiled + pad)[:size], relocs, retail, rva, size, symbol_map)
    if unresolved:
        print("UNRESOLVED:", sorted(set(unresolved)))

    diffs = [i for i in range(size) if resolved[i] != retail[i]]
    print(f"{matches[0]}: {len(compiled)}B vs {size}B, {len(diffs)} differing, "
          f"offsets {[hex(d) for d in diffs[:16]]}")
    left = em.disassemble(retail, rva)
    right = em.disassemble(resolved, rva)
    for i in range(max(len(left), len(right))):
        a = left[i] if i < len(left) else ""
        b = right[i] if i < len(right) else ""
        addr = a.split(":")[0] if a else (b.split(":")[0] if b else "")
        base = int(addr, 16) if addr else 0
        bad = any(base <= rva + d < rva + size + 16 for d in diffs)
        # only mark lines whose own bytes contain a differing byte
        if a and b:
            off = base - rva
            nxt = left[i + 1].split(":")[0] if i + 1 < len(left) else None
            ln = (int(nxt, 16) - base) if nxt else len(a)
            bad = any(off <= d < off + ln for d in diffs)
        print(f"{'!!' if bad else '  '} {a:<44s} | {b}")


if __name__ == "__main__":
    main()
