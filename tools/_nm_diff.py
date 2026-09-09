#!/usr/bin/env python3
"""Ad-hoc helper: dump side-by-side disassembly for one near-miss candidate.

Usage: py -3 tools\_nm_diff.py <source.cpp> <mangled-name> <rva-hex>
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
from locate import object_functions
import capstone

def main():
    src_rel, name, rva_hex = sys.argv[1], sys.argv[2], sys.argv[3]
    rva = int(rva_hex, 16)
    src = build.ROOT / src_rel
    obj = build.obj_path(src)
    if not obj.exists():
        build.compile_source(src, obj)
    emitted = dict((n, (span, relocs)) for n, span, relocs in object_functions(obj))
    if name not in emitted:
        print("NOT EMITTED:", name)
        print("available:", list(emitted.keys())[:20])
        return
    span, relocs = emitted[name]
    ours = span.rstrip(b"\xcc")
    size = len(ours)
    target = build.read_target_bytes(rva, size + 16)
    body = target[:size]
    print(f"size={size} rva=0x{rva:08x}")
    print("ours  :", ours.hex())
    print("retail:", body.hex())
    print("tail16:", target[size:size+16].hex())
    diffs = [k for k in range(size) if ours[k] != body[k]]
    print("diff offsets:", diffs)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    print("--- ours ---")
    for ins in md.disasm(ours, 0):
        print(f"{ins.address:04x} {ins.bytes.hex():<20} {ins.mnemonic} {ins.op_str}")
    print("--- retail ---")
    for ins in md.disasm(body, 0):
        print(f"{ins.address:04x} {ins.bytes.hex():<20} {ins.mnemonic} {ins.op_str}")

if __name__ == "__main__":
    main()