"""Which ledger rows resolve a DIR32 symbol to which base address.

The gate's DIR32 consistency check (build.verify_dir32_consistency) reports that
one symbol resolved to two different bases without saying who disagreed. This
lists the rows, so the offending translation unit can be found instead of
guessed.

This must compute the base exactly the way the gate does, or it lies. It used
to read the retail image as a flat file (`data[rva + off]`), which only works
where a PE's raw file offset happens to equal its RVA -- true near the front of
.text and false everywhere alignment padding or another section has pushed the
two out of step. That produced `0xcccccccc`-style fill bytes and raw opcode
bytes reported as "bases", on freshly rebuilt objects, including on the
__real@447a0000 whitelist entry that is supposed to be the easy case. Fixed by
reading through build.read_target_bytes (proper PE section translation) — the
same call the gate itself uses — instead of a raw file slice. It also now
applies the same skip list as the gate (compiler-local labels, EH handler
thunks, literal constants, IMAGE_SYM_CLASS_STATIC scoping) so a row this tool
shows as "disagreeing" is a row the gate would actually flag, not filtered
noise.

Run from the repo root: python3 tools/dir32.py <symbol>
"""
import csv
import re
import struct
import sys

sys.path.insert(0, "tools")
import build

want = sys.argv[1]

# Exempt up front, not per-site, so a query against one of these prints an
# explanation instead of silently matching zero rows -- indistinguishable
# from "this symbol appears nowhere" otherwise, which is its own way of
# looking like the tool is still broken.
if re.fullmatch(r"\$[A-Za-z]+\d+", want):
    raise SystemExit(f"{want}: a compiler-local label ($L/$T/$SG-style). These are TU-scoped "
                     "-- the gate never checks them for a single address, so this tool has "
                     "nothing to report.")
if want.startswith("__ehhandler$"):
    raise SystemExit(f"{want}: an EH handler thunk. The compiler emits one per TU alongside "
                     "the COMDAT it guards, so N claimed addresses legitimately resolve to N "
                     "different thunks; not a gate check.")
if build.REAL_LITERAL_RE.fullmatch(want):
    raise SystemExit(f"{want}: a literal float/double constant. The gate's string/float "
                     "verifier checks these bits independently and does not require one "
                     "address; not a DIR32 consistency check.")

static_symbols = {}


def is_static_scoped(obj, sym):
    if obj not in static_symbols:
        stat = obj.stat()
        _, _, symbols = build._object_layout(str(obj), stat.st_mtime_ns, stat.st_size)
        static_symbols[obj] = {s["name"] for s in symbols
                               if s.get("storage") == 3 and s["section"] > 0}
    return sym in static_symbols[obj]


hits = 0
with (build.ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8") as fh:
    for r in csv.DictReader(fh):
        if r["status"] != "matched":
            continue
        src = r["source"]
        o = build.obj_path(build.ROOT / src)
        if not o.exists():
            continue
        rva, sz = int(r["target_rva"], 16), int(r["target_size"])
        try:
            body, relocs = build.read_object_symbol_bytes(o, build.ledger_object_symbol(r), sz)
        except Exception:
            continue
        for off, rtype, sym in relocs:
            if rtype != 0x0006 or sym != want or off + 4 > sz or off + 4 > len(body):
                continue
            try:
                final = struct.unpack_from("<I", build.read_target_bytes(rva + off, 4), 0)[0]
            except Exception as exc:
                print(f"  ! could not read retail bytes at {rva + off:#x}: {exc}")
                continue
            add = struct.unpack_from("<I", bytes(body), off)[0]
            base = (final - add) & 0xFFFFFFFF
            identity = f"{src}::{sym}" if is_static_scoped(o, sym) else sym
            hits += 1
            print(f"  base {base:#010x}  <- {r['name'][:58]:60} @{rva:#x}")
            print(f"        {src}" + (f"  (static-scoped: {identity})" if identity != sym else ""))

if hits == 0:
    print(f"# no matched row's compiled object holds a DIR32 relocation to {want!r} -- "
          "either no row references it, or its object is missing/stale (run ./build.sh first)")
