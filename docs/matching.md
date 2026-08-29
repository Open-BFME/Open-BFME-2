# Matching a function

1. Write the C++ under `Code/` at its official-tree path (see below), add a row to
   `reverse/functions.csv`, then verify.
   - `./build.sh Code/path/to/file.cpp` (or a function name) compiles and byte-compares that source.
   - The commit hook runs the full gate for header/reference changes; run it once after a
     resolved merge. Normal commits and pushes gate their delta.
   Builds use MSVC 7.1 and fail on any mismatch.

2. Relocations the patcher fills in for you (so don't worry about matching these bytes):
   - **DIR32** (constants, vtables, string literals): the address slot is copied from the target
     binary, but the full build independently VERIFIES what you reference: a string literal must
     byte-equal the string at the referenced address (`verify_string_refs` — so `"%S"` vs `"%ls"`
     fails), and a global/vtable symbol must resolve to one consistent address across all its
     references (`verify_dir32_consistency`). Write the real literal, not a lookalike.
   - **REL32** (calls/jumps): resolved to the callee's address. A matched callee resolves
     automatically; for anything else (CRT helpers like `__ftol2`, not-yet-matched functions)
     add `name,address` to `reverse/symbols.csv`. The build prints the unresolved name on
     failure. Find the address by disassembling the target and computing the call destination,
     or look it up in the Ghidra inventory (`tools/ghidra/`). Append with the file's own line
     terminator (CRLF today): it is `merge=union`, so a pin that differs from its twin only by
     a `\r` is a new line to the merge driver and duplicates on the next rebase. `check_csv`
     rejects a mixed file; `python3 tools/dedup_csv.py` repairs one.

Leaf functions (no calls) are easiest; `reverse/symbols.csv` is what makes call-using functions matchable.

Useful iteration tools:

- `python3 tools/explain_mismatch.py <decorated-symbol>` compiles that function's source and prints
  the first byte difference, byte windows, and side-by-side target/compiled disassembly.
- `python3 tools/list_naked_candidates.py Code` selects one tracked naked-asm block and prints its
  exact `./build.sh '<symbol>'` command. Add `--ranked --groups` for repeated byte patterns or
  `--all` for untracked functions.

## MSVC 7.1 shaping notes

Near-matches are still failures. If a candidate differs only by register choice, branch layout, or
x87 operand order, revert it unless the exact decorated-symbol check passes.

Observed traps:

- `register` did not force MSVC 7.1 to preload constants. In `Matrix4D::Set(const Coord3D&)`,
  C++ kept `0x3f800000` near first use instead of matching the target's early `mov edx, 0x3f800000`.
- Equivalent x87 expressions can compile differently. `Coord3D::CrossProduct` commuted
  multiplication operands, changing `fld`/`fmul` order while preserving behavior.
- Ternary min/max forms can switch between integer bit copies and x87 stores. `RealRange::combine`
  needs both the target condition flags and the target raw float-copy shape.
- Pointer/index loops are unstable. `Matrix4D::IsExactlyEqualTo` compiled to a different loop shape
  from the target's four-dword xor/or block.
- Virtual-call wrappers may match semantically while saving registers or branching differently.
  `Xfer::XferRawBytes` was a near-match but not byte-identical.

Use these as negative patterns: once a diff shows one of these traps, prefer another function family
or first find a source pattern that proves the exact instruction shape in a targeted build.

One positive pattern: MSVC 7.1 groups overloaded virtual operators at the first overload slot and
emits them in reverse declaration order. The `Debug` shim intentionally declares stream overloads
so `float`, `unsigned int`, `int`, and `const char *` land at the target vtable slots `0x20`,
`0x30`, `0x34`, and `0x38`.

## Reference source

BFME 2 is the SAGE engine — two ancestor trees ride in via the `reference/open-bfme-1`
submodule (GPLv3, same license as this repo):

1. **Open-BFME-1's converted `Code/`** (`reference/open-bfme-1/Code/`) — the nearest ancestor,
   already ZH→BFME-reconciled, and still growing. Prefer it for anything BFME 1 has landed;
   calibration measured 756 of its bodies transferring to game.dat verbatim.
2. **Zero Hour** (`reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/`). **Always port
   from `GeneralsMD/` (= ZH), never `Generals/`.**

Many functions match verbatim. Reconcile against the binary (the source of truth). game.dat's
assert strings keep the original tree layout (`C:\projects\bfme2patch103\bfme2\Code\...`) —
place each conversion at that exact `Code/` path.

For exact function sizes, the full function inventory, and the bulk-port pipeline, see
`tools/ghidra/README.md`.

### Rows sourced from the vendored tree

A ledger row may name a `reference/` file directly, and `./build.sh <that file>` builds it.
The tree stays pristine — being unmodified upstream is its whole value — so its files carry
neither the `// stlport` marker nor the `// cl:` line a `Code/` source uses to declare its
build settings. `build.py` derives both from the path instead: the ZH include set, and
STLport for everything outside `Libraries/Source/WWVegas/`. `tools/zh_sweep.py` measured
that split over 420 translation units, with no exceptions either way.

Do not spend another pass trying to string-anchor the sweep's ICF-ambiguous exact matches.
It was measured: of 2,908 bodies that place at more than one address, only 268 reference a
string literal at all, and following each candidate's DIR32 to the string it points at
leaves 252 with no consistent copy and 16 with exactly one — every one of which is already
claimed. The anchor lands nothing, because the functions distinctive enough to anchor are
the ones earlier passes already identified.

`tools/conversion_gate.py` scans added lines under `Code/` only, so these rows fall outside
its Rule A, and that is deliberate. Rule A stops a contributor deleting authored C++ and
committing an `__emit` byte dump in its place; nobody authors the vendored tree, and nine of
its files legitimately contain `__emit` already, so scanning it would fire on the next
re-vendor rather than on any real regression. Rule B — a matched RVA that had a clean C++
source must still have one — reads whatever path a row names, so a `reference/` row can
never be swapped out from under a live clean claim.

## Third-party code the binary links, and where each one stands

These are Open-BFME-1's findings about the SAME third-party stack (game.dat links FESL,
Miles, GameSpy-era netcode, d3dx9, STLport, zlib, EAC codecs). BFME 2 spans have not been
sized yet — sweep before citing any numbers.

**GameSpy SDK (Chat + Peer included) — permitted.** The owner confirmed on 2026-08-18 for
Open-BFME-1 and on 2026-08-29 that the grant extends to this project. The SDK's own files
carry no grant text (the circulating BSD-3-Clause copy is a 2014 republisher's file), so an
agent reading only the tree will conclude "refused" — read
`reference/open-bfme-1/.../PROVENANCE.txt` for the scope statement first, and mirror it into
this repo's own `PROVENANCE.txt` when the sources are first vendored here.

**nbench / BYTEmark — refused on the merits** (in BFME 1; check whether game.dat links it at
all before spending time). The distribution contains no permission grant of any kind — every
file carries a BYTE/McGraw-Hill *disclaimer* of warranty, and the README ships the BSD
warranty paragraph with the permission clause absent. A BSD licence minus its grant is not a
licence. If game.dat contains it, hold it as `gen_asm` dump only.
