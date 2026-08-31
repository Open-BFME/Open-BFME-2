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
     or look it up in the Ghidra inventory (`tools/ghidra/`). Append with canonical LF: the
     file is `merge=union`, so a pin that differs from its twin only by a `\r` is a new line
     to the merge driver and duplicates on the next rebase. `check_csv` rejects any other
     terminator; `python3 tools/dedup_csv.py` repairs one.

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
  needed both the target condition flags and the target raw float-copy shape; **solved** - see the
  lvalue-ternary note below.
- Pointer/index loops are unstable. `Matrix4D::IsExactlyEqualTo` compiled to a different loop shape
  from the target's four-dword xor/or block.
- Virtual-call wrappers may match semantically while saving registers or branching differently.
  `Xfer::XferRawBytes` was a near-match until the guard was read literally: retail bails out only
  when the size is non-zero AND the pointer is null, so a zero size falls through into both
  transfers. `size != 0 && data != 0` is the obvious guard and the wrong one. **Solved.**

Use these as negative patterns: once a diff shows one of these traps, prefer another function family
or first find a source pattern that proves the exact instruction shape in a targeted build.

A second positive pattern: **bind a reference to the ternary, do not assign its value.**
`const T &low = b > a ? a : b; x = low;` makes MSVC 7.1 conditional-move the ADDRESS of the
selected operand and then copy through it - a raw dword copy even for `float`, with no x87 and
no `movss` store. Assigning the ternary's value instead moves the value and, for `float`, changes
the whole shape. Which side each ternary is written from then decides the compare operand order
and the cmov condition; the operands are not interchangeable even where the value is. This is
what landed `RealRange::combine` (0x000062AD, `that.min > min ? min : that.min` then
`that.max < max ? max : that.max`) and `IntRange::combine` (0x000062D8).

A third: **a class returned by value needs a user-written copy constructor before MSVC 7.1
will apply NRV to it.** With the implicit trivial one the named return value is built in a
stack temporary and block-copied through the hidden pointer, which drags in an `ebp` frame and
an `esi`/`edi` pair; write the copy constructor out member by member and the same source writes
straight through the return pointer with no frame at all. `operator-(Coord3D)` at 0x00003FEE
is the case that shows it.

A fourth, and the one that carried the most bodies: **a compiler-generated `operator=` never
coalesces loose members, so its shape IS the class layout.** A `movsd` run always means a
sub-object; a lone `mov` means a loose scalar; a byte move means a flag. `WindModuleInfo`
(0x001F3654) proves it - seventeen adjacent members, seventeen separate moves. The generated
COPY CONSTRUCTOR behaves differently: it expands the leading members one at a time and switches
to blocks for the rest, so the two generated functions cross-check each other. Neither is emitted
unless something uses it; force one with a pointer-to-member for `operator=`, and with a
placement-new helper for the copy constructor.

A fifth: **what the caller can SEE of its callee decides the register save set.** With the callee
defined in the same unit MSVC 7.1 proves which registers it leaves alone and parks values there;
with only a declaration it saves esi/edi like retail. This is a translation-unit question, not an
ordering one - moving the definition later in the same file changes nothing. It moved
`expandRange` out of `region.cpp`, split the FXParticleSystem module wrappers away from the module
templates, and is why `??0RGBColor@@QAE@H@Z` cannot live in `color.cpp`.

A sixth: **the same library is built at two optimization levels.** `string_base.cpp` and
`ascii_string.cpp` are /O1; a set of their members only match at /O2 and live in
`string_base_inline.cpp` and `string_inline.cpp`. The tells are `mov eax, 1` rather than xor/inc
for a true, a duplicated `ret` in each arm rather than a jump to a shared epilogue, a full-width
`movsx`/`movzx` rather than an 8-bit move, a tail `jmp` into a sibling overload rather than
push/call, `mov dword ptr [reg], 0` rather than the three-byte `and dword ptr [reg], 0`, and a
`rep cmpsb` rather than a `memcmp` call (/O2 implies /Oi). Recompiling a whole unit at the other
level and counting what breaks is a cheap, decisive test.

Two smaller ones. **`inline` is a lever in both directions**: MSVC will not auto-inline a 93-byte
`SetIdentity` however the file is ordered, and marking it `inline` (with its address taken to keep
the standalone copy) is what lets two constructors absorb it; conversely a base constructor that
retail folds in has to be marked `inline` or it is called out of line. And **an empty
non-polymorphic base of a polymorphic class is not folded away** - MSVC gives it offset 4, behind
the vptr - so a stub base has to be modelled with its real vtable count or every member shifts.

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
