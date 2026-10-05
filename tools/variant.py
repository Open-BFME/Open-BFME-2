#!/usr/bin/env python3
"""Isolated scratch-TU variant driver.

Compiles a scratch source under build/ with the project's own MSVC 7.1
compiler command -- never compile_source(), which writes the shared match
cache -- patches its relocations against a caller-supplied symbol map exactly
the way tools/build.py:compile_function does, and reports compiled size and the
first differing byte against retail.

A scratch TU declares its globals in an anonymous namespace, so MSVC hashes the
absolute source path into each name (?A0x........). The map therefore keys on
the readable source prefix: a key that is a PREFIX of the COFF symbol matches.

Usage: variant.py <scratch.cpp> <symbol-substr> <rva> <size> [name=addr ...]
"""
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

ROOT = build.ROOT


def resolve_bytes(compiled, relocs, target, target_rva, size, symbol_map):
    resolved = bytearray(compiled[:size])
    unresolved = []
    for offset, rtype, sym_name in relocs:
        if offset >= size:
            continue
        if rtype == 0x0006:
            resolved[offset : offset + 4] = target[offset : offset + 4]
        elif rtype == 0x0014:
            if offset + 4 > size:
                raise SystemExit(f"REL32 at +0x{offset:X} runs past the claimed size")
            next_address = target_rva + offset + 4
            candidates = symbol_map.get(sym_name)
            if not candidates:
                unresolved.append(sym_name)
                continue
            disp = struct.pack("<i", candidates[0] - next_address)
            for addr in candidates[1:]:
                if target[offset : offset + 4] == disp:
                    break
                disp = struct.pack("<i", addr - next_address)
            resolved[offset : offset + 4] = disp
    return bytes(resolved), unresolved


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
    out.parent.mkdir(parents=True, exist_ok=True)
    if out.exists():
        out.unlink()
    command, env = build.compiler_command(src, out)
    proc = subprocess.run(command, cwd=ROOT, env=env, capture_output=True, text=True)
    if proc.returncode != 0:
        sys.stdout.write(proc.stdout or "")
        sys.stderr.write(proc.stderr or "")
        raise SystemExit(f"compile failed for {src}")

    defined = build.defined_code_symbols(out)
    if wanted.startswith("="):
        exact = [s for s in defined if s == wanted[1:]]
        matches = exact
    else:
        matches = [s for s in defined if s.startswith("?") and wanted in s]
    if not matches:
        raise SystemExit(f"no defined code symbol matching {wanted!r} in {src.name}")
    if len(matches) > 1:
        raise SystemExit(f"{wanted!r} matches {len(matches)} symbols: {matches}")

    compiled, relocs = build.read_object_symbol_bytes(out, matches[0], code_only=True)
    retail = build.read_target_bytes(rva, size)
    span = min(len(compiled), size)
    if len(compiled) < size:
        pad = bytes(size - len(compiled))
        compiled_cmp, retail_cmp = compiled + pad, retail
    else:
        compiled_cmp, retail_cmp = compiled[:size], retail
    resolved, unresolved = resolve_bytes(
        compiled_cmp, relocs, retail, rva, size, symbol_map)
    diffs = [i for i in range(size) if resolved[i] != retail_cmp[i]]
    label = matches[0]
    if unresolved:
        print(f"{label}: UNRESOLVED {sorted(set(unresolved))}")
    if diffs:
        print(f"{label}: {len(compiled)}B vs {size}B retail, {len(diffs)} differing, "
              f"first at +0x{diffs[0]:X}")
    else:
        print(f"{label}: EXACT MATCH ({size}B)")


if __name__ == "__main__":
    main()
