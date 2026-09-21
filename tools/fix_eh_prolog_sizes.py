#!/usr/bin/env python3
"""Repair inventory sizes cut off at `call __EH_prolog`.

C++-unwind functions open with `mov eax, <funcinfo>; call __EH_prolog`, and the
helper returns via `push eax; ret`. The committed Ghidra export treated it as
non-returning, so reverse/ghidra_functions.csv sized each such function at 10
bytes: just those two instructions.

A row is changed only if it is size 10, its call target is byte-for-byte
__EH_prolog, and a trace of its body reaches a `ret`, a direct `jmp` or int3
padding before the next inventoried function. Everything else is left as is.

Usage:
  python3 tools/fix_eh_prolog_sizes.py [--root DIR] [--check]
"""
import argparse
import bisect
import struct
import sys
from pathlib import Path

import capstone

DEFAULT_ROOT = Path(__file__).resolve().parents[1]
BINARY = "baselines/bfme2/workshop-vanilla-1.06/files/game.dat"
INVENTORY = "reverse/ghidra_functions.csv"

PROLOG_CALL = 10                      # mov eax, imm32 + call rel32
EH_PROLOG = bytes.fromhex(
    "6aff" "50" "64a100000000" "50" "8b44240c" "648925000000" "00"
    "896c240c" "8d6c240c" "50" "c3")
MAX_SCAN = 0x20000
CONDITIONAL = frozenset((
    "je", "jne", "jg", "jge", "jl", "jle", "ja", "jae", "jb", "jbe",
    "js", "jns", "jo", "jno", "jp", "jnp", "jecxz", "loop", "loope", "loopne"))


def fail(message):
    print(f"fix_eh_prolog_sizes: {message}", file=sys.stderr)
    sys.exit(2)


class Image:
    """Just enough PE to read bytes by RVA."""

    def __init__(self, path):
        try:
            self.raw = path.read_bytes()
        except OSError as exc:
            fail(f"cannot read {path}: {exc}")
        head = struct.unpack_from("<I", self.raw, 0x3C)[0]
        if self.raw[head:head + 4] != b"PE\0\0":
            fail(f"{path} has no PE signature")
        count = struct.unpack_from("<H", self.raw, head + 6)[0]
        optional = struct.unpack_from("<H", self.raw, head + 20)[0]
        self.sections = []
        at = head + 24 + optional
        for _ in range(count):
            vsize, rva, rsize, raw_at = struct.unpack_from("<IIII", self.raw, at + 8)
            self.sections.append((rva, min(vsize, rsize), raw_at))
            at += 40

    def read(self, rva, count):
        for start, size, raw_at in self.sections:
            if start <= rva < start + size:
                at = raw_at + rva - start
                return self.raw[at:at + count]
        return None


def eh_prolog_target(image, rva):
    """Call target if `rva` opens with `mov eax, imm32; call rel32`, else None."""
    head = image.read(rva, PROLOG_CALL)
    if head is None or len(head) < PROLOG_CALL or head[0] != 0xB8 or head[5] != 0xE8:
        return None
    return rva + PROLOG_CALL + struct.unpack_from("<i", head, 6)[0]


def trace(image, disasm, rva, limit):
    """Body size, or None if it has no provable end before `limit`."""
    body = image.read(rva, min(MAX_SCAN, limit - rva))
    if not body:
        return None
    furthest = rva
    for ins in disasm.disasm(body, rva):
        end = ins.address + ins.size
        target = None
        if ins.mnemonic in CONDITIONAL or ins.mnemonic == "jmp":
            try:
                target = int(ins.op_str, 16)
            except ValueError:
                pass
            if target is not None and rva < target < limit:
                furthest = max(furthest, target)
        if ins.address < furthest:
            continue
        # Nothing branches past here, so a ret or jmp (either direction) ends it.
        if ins.mnemonic in ("ret", "retn"):
            return end - rva
        if ins.mnemonic == "jmp":
            return None if target is None else end - rva   # None: switch dispatch
        if ins.mnemonic == "int3":
            return ins.address - rva  # inter-function padding
    return None


def repair(image, rows):
    """[(rva, size, name)] -> (rows, [(rva, old, new)], skipped)."""
    starts = sorted(rva for rva, _size, _name in rows)
    disasm = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    is_helper = {}
    out, changed, skipped = [], [], 0
    for rva, size, name in rows:
        target = eh_prolog_target(image, rva) if size == PROLOG_CALL else None
        if target is not None and target not in is_helper:
            is_helper[target] = image.read(target, len(EH_PROLOG)) == EH_PROLOG
        if target is None or not is_helper[target]:
            out.append((rva, size, name))
            continue
        index = bisect.bisect_right(starts, rva)
        limit = starts[index] if index < len(starts) else rva + MAX_SCAN
        real = trace(image, disasm, rva, limit)
        if real is None or real <= PROLOG_CALL:
            skipped += 1
            out.append((rva, size, name))
            continue
        changed.append((rva, size, real))
        out.append((rva, real, name))
    return out, changed, skipped


def read_inventory(path):
    """Rows as the Ghidra exporter writes them; not csv, so names stay verbatim."""
    with open(path, newline="") as handle:
        lines = handle.read().split("\n")
    if lines[0] != "rva,size,name":
        fail(f"{path} header is {lines[0]!r}, expected rva,size,name")
    rows = []
    for line in lines[1:]:
        if line:
            rva, size, name = line.split(",", 2)
            rows.append((int(rva, 16), int(size), name))
    return rows


def write_inventory(path, rows):
    with open(path, "w", newline="") as handle:
        handle.write("rva,size,name\n")
        for rva, size, name in rows:
            handle.write(f"0x{rva:X},{size},{name}\n")


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--root", type=Path, default=DEFAULT_ROOT)
    parser.add_argument("--check", action="store_true",
                        help="report only; exit 1 if any row needs repair")
    args = parser.parse_args()
    root = args.root.resolve()
    image = Image(root / BINARY)
    rows = read_inventory(root / INVENTORY)
    out, changed, skipped = repair(image, rows)
    before = sum(old for _rva, old, _new in changed)
    after = sum(new for _rva, _old, new in changed)
    print(f"{len(changed)} rows repaired: {before:,} -> {after:,} bytes; "
          f"{skipped} left unchanged, no provable end")
    if args.check:
        sys.exit(1 if changed else 0)
    if changed:
        write_inventory(root / INVENTORY, out)


if __name__ == "__main__":
    main()
