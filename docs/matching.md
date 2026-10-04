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
- Pointer/index loops are unstable. `Matrix4D::IsExactlyEqualTo` needed the four-dword xor/or block
  written out literally - four `*a++ ^ *b++` folded into one `diff` with `|=`, tested once per row,
  over `const int *` casts of the float array, behind an early `this == &that` return. **Solved.**
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

A seventh: **a global that retail schedules around stores is file-static.** MSVC 7.1 keeps a
store to an `extern` (or plain global) byte ahead of a later load through `this` (the vptr, a
member pointer), and keeps its test after unrelated stores, because the byte could alias them. A
`static` global whose address is never taken cannot, so retail's `mov eax,[ecx]` before
`mov byte ptr [g],0`, or `cmp byte ptr [g],0` hoisted above two stores, means the byte was
file-static. Making it `static` landed the reload notices 0x0031E7F0, 0x00289812 and 0x001E51AC
after locals, reordering and branch duplication had all failed. Every reader and writer of that
byte then belongs in the same unit (the static has no cross-unit name).

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

1. **Open-BFME-1's converted game** (`reference/open-bfme-1/game/`) — the nearest ancestor,
   already ZH→BFME-reconciled, and still growing. Prefer it for anything BFME 1 has landed;
   calibration measured 756 of its bodies transferring to game.dat verbatim.
2. **Zero Hour** (`reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/`). **Always port
   from `GeneralsMD/` (= ZH), never `Generals/`.**

Many functions match verbatim. Reconcile against the binary (the source of truth). game.dat's
assert strings keep the original tree layout (`C:\projects\bfme2patch103\bfme2\Code\...`) —
place each conversion at that exact `Code/` path.

### Donor files BFME 1 has already converted

`tools/bfme1_sweep.py` compares `lotrbfme.exe` against `game.dat` directly and serves the
BFME 1 source files whose bodies are **byte-identical** here, so the conversion is a copy.
`scan` (~3 min) writes `build/bfme1_sweep/match.json`; `ranked`, `show` and `packets` serve
from it instantly, and each packet carries the donor path, its copy difficulty, the
`symbols.csv` pins its call sites need and the exact `add_match.py` lines. `land <file>` runs
those steps and reverts cleanly if the gate refuses. Claim and pin state are re-read at serve
time, not cached, so a scan does not go stale as rows land around it.

Three commit gates hold a donor out of the served queue, because a file can build and byte-match
and still not be committable (`ranked --include-held` lists them): **L** the donor is itself a
`__declspec(naked)`/`__emit` lift (the anti-lift gate); **P** its path is outside the roots
`.githooks/pre-commit` allows for a new source (`Code/stlport/` is not one); **S** it defines
functions the sweep never placed, and `find_declared_unmatched` refuses a source with any
definition the ledger lacks. Wave 1 found all three by landing into them; the tiers agreed with
31 of 31 of that wave's files.

**S is a bundling rule, not a byte difference, and it yields.** The way past it is to carry ONLY
the placed bodies into a new `Code/` TU: keep the class declarations, because the member offsets
are what the body's shape depends on, and omit the bodies the sweep never placed, so the gate has
nothing left to refuse. Landed that way: 5 donors, 67 bodies, 1,512 bytes —
`Rva0090C280Ctor.cpp` (20B), `Rva0089CompactHelpers.cpp` (145B/7),
`AddressTinyBodiesD0083FDF0.cpp` (84B/3), `SmallGaps/Rva0083ED40StreamStateReport.cpp` (53B) and
`StaticTagInitializers.cpp` (1210B/55, the largest donor the queue holds). The last needed no pins
at all: its 62 tag-slot globals are reached through DIR32 data slots, so the file resolves with
zero unresolved symbols — reading its `extern` declarations suggests a pin cost the build never
charges. Test one body before declining a donor on how it looks.

**A donor's inline immediates are not relocation slots.** The sweep derives DIR32 windows from the
byte stream and blanks them, but the compiler emits no relocation for a source literal, so
`mov DWORD PTR [ecx],0x0113A56C` is a blanked window to the sweep and a plain immediate to the
linker, and the build's copy-from-retail cannot reach it. A donor that hardcodes BFME 1's vtable or
a member offset therefore reports a clean transfer and then fails on exactly those four bytes. Both
instances so far are one-constant repairs read off retail: `releaseResource0090C2D0` (0x001310CF,
donor 0x0113A56C against this game's 0x00BD25C8) and `Rva0088D990Owner::set` (0x0003CD10, donor pad
0x9F48 against 0x9F54) — 2 of the 67 bodies above. Treat T1 "clean transfer" as a hypothesis:
compile the donor and diff it.

**T3 byte counts overstate the yield.** A T3 donor is one whose name is an ICF guess, and its rows
usually collapse onto a SINGLE BFME 2 address: `S1LazyPointerFieldReads` places 5 rows at one,
`BfmeTwoHundredFifteen` 2 at one, `VirtualSlot5CallThunk` 3 at one. Count the packet's distinct
`b2` addresses, not its rows, before costing the file — and where several BFME 1 names share one
address, land a single row under an address-derived name rather than several real-looking ones.

`bfme1_sweep.py ambiguous` resolves donors by WHERE they should be rather than by more
bytes. The two images lay the same code out in the same order: order the placed bodies by
BFME 1 address and 84% sit in ascending runs of five or more (longest 248), with 76% of
neighbouring pairs spaced within 16 bytes of each other in both images. Between two anchors
the map is affine. Across a region boundary it is worthless, because BFME 2 dropped and
reordered whole objects -- leave-one-out error over 4,696 anchors is 16 bytes at the median
and 1.9 MB at p90, two distributions rather than a tail. The gate separates them and is
checkable before the answer is used: if the bracketing anchors span the same distance in both
images, everything between them transferred intact. At a 16-byte tolerance it covers 41% of
placed bodies and predicts 99% to within 64 bytes, p99 11 bytes.

Measured yield is small and the precision is the point. On the recorded ambiguous pool (1,460
donors, 65,032B) it resolves 49 donors, 3,901B; on the 737 donors with no usable needle -- the
only tier nothing else can reach, since there is nothing long enough to search for -- it
declines 708 times and commits 29, of which 27 byte-match. Use it where searching cannot go,
not as a way to move bulk. A resolution needs the runner-up OUTSIDE the window too: two
candidates equally close to the prediction is the question restated.

`bfme1_sweep.py drain` runs `land` over the whole served queue and keeps going past a
refusal, which is the way to spend the queue without spending attention on it. `land` is
still the unit of work and owns its own unwind; drain adds the loop and a verdict. Each file
goes through a fresh `land` because every row that lands changes what `body_tier` decides
about the next one, so a queue planned once up front is stale after the first file. It skips
what `land` would refuse anyway — held copy-tiers, tier D, a refused policy, an import alias —
rather than counting files it is about to drop.

`bfme1_sweep.py near` serves the donors that *almost* match: the same function either side
of a BFME 1 -> BFME 2 change, where the difference is the agent's work. A candidate has to
clear every one of: at least 90% of the bytes outside the relocation slots BOTH images accept,
an unclaimed address, and positive boundary evidence (a Ghidra start, or a preceding `int3`
run). An address interior to a known function is refused outright. Only `immediate-only` and
`imm+reg` are queued; `register-swap` is the MSVC-regalloc wall `drift_classify.py` documents,
and `structural` is reconstruction rather than a copy and a tweak. A near candidate is an
unverified identity claim, which is why it never enters `ranked` -- that queue's worth is the
promise "copy it and it byte-matches" -- and why `land` refuses one. Nothing is claimed until
`add_match` byte-verifies it, so a wrong candidate costs a look and never a bad match.

Score a near miss only against the relocation fields the two images BOTH accept. The DIR32
pass claims any four-byte window addressing the image, and some straddle an opcode:
`add ecx,0x120` is `81 C1 20 01 00 00`, whose window at the modrm byte reads `0x0120C181`.
Mask that and the body scores 100% against `add ecx,0x17c` -- a struct field that moved, which
is precisely what the tier exists to surface.

Both tiers still work by placing donor BYTES in game.dat, and that is narrower than it
sounds even with the near tier. The BFME1-verbatim rows already in this ledger — `getBrightness` (0x002E4A47), `hasGotOnline`,
`getRemainingAmmo` — are *source*-verbatim and byte-**divergent**: BFME 1's bodies are three
to six bytes longer and only 15–31 of ~90–105 bytes agree. No binary comparison can reach
them -- not even as near misses, because the needle they are searched by never matches.
They need a compile-based sweep like `zh_sweep.py`. Do not re-derive this.

Neither image has a `.reloc` directory, so the sweep derives relocation slots from the
instruction stream and forgives a difference only where both images independently place the
same kind of slot at the same offset. `scan` prints a control figure — the number of its
placements that reproduce a boundary this repo matched independently — and refuses the run
if it falls. Treat that number, not the candidate count, as the health check.

The walk reads bytes, not instructions, so it has to be told that an `E8`/`E9` inside DATA is
not an opcode: the immediate of a vftable store, an entry in a switch jump table, a character
in a string. The target is the test — a call that leaves `.text` was never a call — and the
walk now refuses a rel32 whose displacement does not land there. Costlier than it sounds to
get wrong: the bogus claim also blocks the DIR32 window that really holds the relocation, and
every later field shifts with it, so a byte-identical body reads as a near miss.
`??0__Named_exception` (0x0082C180) is the worked example — `mov DWORD PTR [eax],0x0112e8b8`
stole its own slot and the body scored 96.1%. Fixing it moved CONTROL 4112 -> 4212 and 105
near misses into exact placements, +5498 bytes on free ground.

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

`place_bodies` is a worked-out seam, and one family wide. Measured: the 669 `stlport_*`
shards yielded 5 bodies (315B), and **1,711 further ledger sources yielded 0** — 395
non-stlport `WWLib`, all 316 of the `FamilyDeletingDtors_*` / `GlobalFlagClearers_*` /
`INI_*` shards, a 160-file `Common` probe, and 840 sources walked alphabetically from the
top of the ledger list. The zero is not noise: at the stlport rate (0.75% of files) the
expected count over that sample was ~13, and the walk is compile-bound at roughly 1.5
minutes per 120 sources, so a full pass over the 7,649 untouched sources costs ~100 minutes
to find single-digit bodies. The reason is structural rather than incidental —
`place_bodies` pays only where a unit emits more than the ledger captured, which is a
property of generated per-instantiation shards, not of ordinary source. It returns nothing
on a file with many `present-unmatched` markers either, and that is consistent: those
bodies are unmatched precisely because they do not place uniquely.

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

## Compiler flags: what a whole-tree sweep actually found (2026-09-06)

Every flag below was swept across every unit that lacked it, keeping it only
where all existing rows still verified AND `place_bodies` then placed something
new. The counts are units, out of the whole tree.

| flag | pays in | regresses | verdict |
|---|---|---|---|
| `/arch:SSE` | 39 | 6 | the big one -- 179 bodies, ~32 KB |
| `/arch:SSE2` | 5 | 14 | separate question from SSE; both are per-unit |
| `/Ob2` | 6 | 0 | safe everywhere, pays rarely |
| `/G7` | 4 | 14 | mostly the wrong answer |
| `/Oi` | 0 | 10 | destructive |
| `/Op` | 0 | 14 | destructive |
| `/GS` | 0 | 10 | destructive |
| `/GF` `/Gy` `/GB` | 0 | 0 | inert |

Two units reject BOTH `/arch` levels -- `matrix3d.cpp` and `vehiclecurve.cpp` --
which is positive evidence that they really were built with x87.

The STLport block is not where the flags are wrong: `/Ob2` and `/arch:SSE` over
all 219 of those units gained nothing (and SSE broke four).

So: retail was built a unit at a time and neighbours in the same directory
disagree. Sweep per unit, keep per unit, and do not look for a tree-wide
setting.
