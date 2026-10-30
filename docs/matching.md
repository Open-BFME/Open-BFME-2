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
     pin it with `python3 tools/pin_admission.py --add NAME 0xRVA` (or `add_match.py --pin
     NAME=0xRVA`): the tool checks the pin and admits it in the escape-hatch register, which
     refuses hand-typed pins once enforced. The build prints the unresolved name on
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

The default compiler remains 13.10.3077. A source may explicitly select
`// compiler: vc71-sp1` for the hash-pinned 13.10.6030 optimizing compiler in
`vendor/vc71-sp1/`, using the same submodule headers and libraries. This supports
`/hotpatch` for SDK bodies whose retail archive was built by a later 13.10
compiler. Record the retail evidence before selecting it; all normal byte,
identity and relocation checks still apply. Its executable and runtime DLLs
are part of object-cache fingerprints and dependency receipts.

`// compiler: vc71-ddk-4035` selects the similarly pinned Windows Server 2003
SP1 DDK compiler, 13.10.4035. Retail's DXErr object records that version; it
emits the older `/GS` cookie shape required by DXTrace. Both profiles retain
the default compiler's headers and libraries.

`// compiler: clang23-x86` explicitly selects the pinned Clang 23.1.1 package
under `vendor/clang23-x86/`, targeting the x86 MSVC ABI. It supports clean C++
leaf reconstructions where the older compiler cannot emit retail's instruction
layout; it does not assert that retail used Clang. Sources without the directive
still use MSVC 7.1. Legacy G5/G6/G7 region tuning is translated to the matching
Clang `-mtune` option; other flags pass through. The package contains the compiler and its runtime DLLs, with
no replacement game headers or libraries; see its provenance and license.
First use expands the hash-verified archive into `build/compiler_profiles/`.
Every selection verifies the archive and all expanded binaries; a changed or
missing existing binary refuses rather than being repaired. All these inputs
enter object receipts and fingerprints. Native Windows x64 or 64-bit Wine is
required for this optional compiler. Normal whole-body, identity, relocation,
data and hook checks remain required.

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

An eighth: **retail's `operator delete[]` is nothrow.** A destructor whose inlined member
teardown calls `delete[]` (a `VectorClass`/`DynamicVectorClass` member) carries no EH state store
between its body and that teardown in retail; we emit `mov [esp+N],0` there, and usually cache 0
in `ebx` for it, a few bytes long. Declaring `void __cdecl operator delete[](void *) throw();`
before the unit's first `#include` lets the compiler drop the store. It closed ~HLodClass
(0x0019EF70), ~AggregateDefClass (0x001A3C90) and ~NamedPivotMapClass (0x001976F0) with every
existing row of their units still matching; the constructors' funclet `$L` labels can shift.

Commutative SSE operand order is not set by source order (cl canonicalizes it), but it does move
with the surrounding IL: reading a member directly instead of through an inline accessor
(`IsTreeValid` for `Is_Hierarchy_Valid()`, Simple_Evaluate_Bone 0x001A5A60) or binding the operand
to a local reference before an inline call (the plane clip at 0x00100362) flipped the operands
where no spelling of the product did.

**What decides it** (controlled `/FAsc` trials, identical at `/O1` and `/O2` with `/G7
/arch:SSE`). For `x = A op B` with both operands in memory, one is loaded (`movss xmm,A`) and
the other folded (`mulss xmm,B`). Within one expression tree, source order is irrelevant for
operands reached through a pointer: `a*b`, `b*a`, inline `mul(a,b)`/`mul(b,a)` and even
`x+y+z` against `z+y+x` (cl re-associates float chains) compile identically. Only operand
identity decides, in this order:

1. An operand that is the assignment's own destination (`v->x += f->x`, `a->x = a->x * b->y`)
   is folded. This beats every rule below.
2. A pointer dereference is loaded before a global, and a global before a stack parameter or
   spilled local. Two plain globals are never swapped: the right operand is loaded.
3. Between dereferences, the deeper address is loaded (`p->q->x` before `p->x`), then a base
   plus displacement before a bare `[reg]` (displacement 0 behaves like a leaf).
4. Same base: the higher displacement is loaded.
5. Different bases: locals rank above parameters. Among locals, the variable **first assigned**
   later is loaded first. Declaration order and later reassignments do not count. Parameters
   rank by position, the first parameter highest. `this` ranks below a stack parameter.

So flipping one site means changing which variable the address hangs off. A pointer cached in
a local (first assigned before or after another), a different base for one row, or reading
through the destination all work; respelling the arithmetic does not. Copies that CSE folds
back into an address expression (`V *p = a->n`, `Coord3D *f = &m_p->force`, inline-function
parameters) create no new variable and change nothing. The ranks are numbered per function, so
unrelated locals can move them: HordeContain 0x0046BEAC's first centre add (retail loads the
stack accumulator and folds the member, against rule 2) flipped only when the `pos`/`delta`
locals of two later loops were declared once and shared.

**Across statements there is no canonicalization.** Separate statements keep their order, so
writing per-element updates in retail's element order is a real lever. Whether `m.X += t`
folds `m.X` (`addss t,[m.X]`) or loads it (`movss r,[m.X]; addss r,t`) depends on how `t`
was produced, not on operand order. `t` = a product written in the same statement folds; `t`
= an element of a scalar-replaced local (`last *= u; m += last`) loads, unless the allocator
coalesces. In Calculate_Texture_Matrix (0x00186380) retail folds row 0 in Y,Z,W,X order,
which the per-element `m[0].Y += last.Y * u; ... X last` form reproduces; Zero Hour's
`last *= u; m[0] += last` does not.

A ninth: **retail's `pop esi; mov fs:[0],ecx; pop ebx` epilogue (the SEH restore between the
last two pops) means the function passes an object of a class with a user-written copy constructor
by value**; without one, cl sinks the restore below the last pop. Building the argument in place (an
esp save `mov [ebp-x],esp`) and an inline callee taking the object by value from an lvalue both
count; a temporary whose copy is elided does not. STLport iterators qualify, so this is usually
`erase(it)`, `insert(hint, v)` or a constructor taking an iterator by value. Measured on the matched
rows: none of the 2,002 with the late restore saves esp; 591 of the 842 with the early one do.
`addHotKey` (0x00359302) landed by giving its result's constructor the iterator by value.

**How callee-saved registers are assigned** (controlled `/O1 /G7` trials, 2026-10-18). Variables
are coloured greedily in priority order; each takes the first of esi, edi, ebx not already held by
a variable it interferes with. Priority grows with the number of references after CSE and copy
propagation (so a redundant load or an alias of the same value adds nothing), each weighted by its
block: 1 in straight-line code and after an early `return`, about 0.55 in one arm of an `if`, a
`&&`/`||` operand or a ternary, about 0.67 in a loop body (trip count is ignored), and less again
when nested. Ties go to the variable assigned first, which is why `this` wins an even contest. A
live range that spans branchy code pays a small flat penalty, about 0.15 of a use per `if` it
crosses whatever the variable's weight (straight-line length costs nothing), so a `this` used
throughout a branchy function can lose esi to a local with fewer uses. **Measure the gap before
hunting a spelling**: add N throwaway straight-line uses of the variable that should win
(`g_sink = (int)this;` at the top, in a scratch copy) and find the N that flips the allocation.
N = 1 means the levers below can close it; parseUserList (0x004D1616) is N = 1 and still did not
yield to 130 combinations of statement-level respellings (guard and loop forms, accessor or
member, locals for each `new`, `throw()` on every callee): those compile to identical IL, so do
not spend trials on them. The levers that change a weight without
changing the code are spellings that move a reference into or out of a conditional region: a use
under `cond && x->f` weighs about half of the same use on its own, and a value read in both arms of
a ternary weighs slightly more than one plain read. That is the whole effect behind the equal-arm
`c ? x : x` hacks some banks carry; prefer a natural spelling with the same shape.

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

**Superseded (2026-10): flags come from the retail region.** Fingerprinting the
image (research/25) shows a per-project build after all: BFME2 GameEngine and
GameEngineDevice are `/O1 /arch:SSE /G7`, WW3D2 `/O2 /arch:SSE /G7`, WWLib and
the third-party block `/O2` blend. `/G7` looked "mostly wrong" above only
because the gate never compared `.text$x`: retail's static-guard funclets are
`and al,0FEh`, which only `/G7` emits. `tools/flag_defaults.py` now gives
every `Code/` TU the `/O`, `/arch` and `/G` of the region holding most of its
rows (`reverse/retail_inventory/flag_regions.csv`); every other `// cl:` token
still counts. A file's own codegen flags count only when
`reverse/flag_overrides.csv` lists it. Never edit that file or an overridden
file's codegen flags by hand: run `python3 tools/flag_defaults.py propose
<source>`, which compiles both ways and records an override only when the
region default loses a row.

## Reference lanes and donor sweeps (moved from AGENTS.md, 2026-10)

Byte matching of `.text` is complete (`tools/progress.py`), so these lanes now
serve as source leads for verified regressions, link repairs and gen-* repoints.
Coverage alone does not identify every function or prove a candidate lost its
row: check current owners, aliases, boundaries and input freshness first.
They were AGENTS.md's work-selection steps 3–6
and its sections on coverage-first sweeps and BFME 1 donor compiles; every rule
below still holds when you use them.

### The reference lanes

Run them before dump or structural reconstruction. They are separate from the
default picker; a zero result in one is no reason to skip the others.

a. `python3 tools/bfme1_sweep.py scan` when its image, BFME 1 pointer or BFME 2
   ledger changed (otherwise reuse the scan), then
   `python3 tools/bfme1_sweep.py ranked` (byte-identical BFME 1 sources) and
   `python3 tools/bfme1_sweep.py near` (source leads for repair). `ranked` does
   not read `reverse/re_attempts.log` and re-serves candidates earlier seats
   refused (`0x0003CCE0` in `Rva0089CompactHelpers.cpp`, a folded T3 guess,
   was re-served after a rescan): check the log for a candidate's RVA before
   treating it as work.
b. Ensure the committed BFME 1 pointer includes `tools/lift_lane.py`, then run
   `python3 reference/open-bfme-1/tools/lift_lane.py --limit 1000` at the start
   of the reference pass. It lists BFME 1's named lifted bodies with proven
   boundaries, same-name ZH definitions first: use each ZH-marked name and
   readable-body path to prioritize the matching `GeneralsMD/` source. A
   same-name hit does not prove identity, and lifted bytes are not C++
   recovery. If the tool is missing at the committed pointer, the BFME 1
   freshness check (AGENTS.md) is due regardless of its timestamp: complete the
   verified pointer update; never silently skip or mark this lane exhausted.
c. `python3 tools/zh_sweep.py compile` when the object cache is missing or its
   source, headers, toolchain or flags changed (`--force` when those inputs
   changed), then `python3 tools/zh_sweep.py match` (exact ZH placements) and
   `python3 tools/zh_sweep.py packets` (near misses for `tools/next_work.py`).
   Work viable packets from `python3 tools/next_work.py --tier packet`; re-run
   `match` and `packets` after material ledger or dependency changes. Land only
   through the identity and full-byte gates.

Then, in order:

- `python3 tools/list_naked_candidates.py Code` serves a byte-true dump from
  `Code/gen_asm/`, boundary proven (`--claim` claims while selecting).
- `python3 tools/next_work.py --tier structural|ghidra|anchored|similar|named|harvest`
  for identity/structural work; `--wb` serves bodies by WorldBuilder name lead;
  proven fixes: `docs/recipes.md`.
- `python3 tools/place_bodies.py <sources>` finds, by masked byte search, the
  other bodies the units the ledger already compiles emit, and reads their call
  sites for callees. Rescan affected units after an import, repair or
  shared-dependency fix; land incidental bodies that satisfy the identity,
  provenance and byte requirements (a placement alone is no recovery); repeat
  while placements unlock more. Prune what `./build.sh` refuses to a fixpoint and
  record the refusal in `reverse/place_denylist.txt`.

A tier reporting zero candidates exhausts only that search method; an empty
byte-match queue does not exhaust reusable reference source. Regenerate with
`tools/drift_classify.py`, `tools/anchor_unclaimed.py`, `./build.sh`.

A persistent mismatch may reflect a compiler quirk or unexpected instruction
ordering rather than incorrect logic. Consult `docs/recipes.md`, relevant records
under `reverse/attempt_support/`, and prior pertinent evidence. When a specific
mismatch warrants it, systematically test equivalent C++ variants of the
affected expression or code segment, compare the generated assembly, and
preserve useful findings for the next agent.

### Prefer coverage-first reference sweeps

Prefer reference-source sweeps first whenever compatible reference units exist;
optimize for verified unique bytes per effort by batching compatible units,
especially library families whose dependencies already exist. Escalate before
abandoning a reference for dump reconstruction:

1. Direct reuse or small evidence-backed repair (constants, declarations,
   offsets, helper selection, compiler settings) that preserves the verified body
   and semantics.
2. Moderate repair of control flow, data access, calls, layouts or compiler
   shape while identity and relationship stay well supported. Make evidence-backed
   adaptations; preserve the reference function's established purpose and
   semantics while reconciling target-specific differences.
3. Substantial reconstruction from the reference while retail evidence supports
   identity, ABI, behavior, call relationships and data usage; the reference
   stays the semantic and structural guide.
4. Byte-true reconstruction of the `Code/gen_asm/` body as real C++, only once the
   reference paths are exhausted or no longer applicable.

Use compiler variants from matched siblings, with caching and isolated trials;
preserve provenance, dependencies and compiler settings; continue through viable
independent candidates; commit successful imports with their ledger updates
coherently. Do not force a weak reference: once evidence no longer supports the
same identity or semantics, or reasonable repairs stop progressing, move on.
Re-run sweeps as dependencies, identities, compiler configurations and sibling
matches land.

### Compile BFME 1 donors beyond byte matches

`bfme1_sweep.py` compares retail bytes and cannot find every reusable body.
Before treating BFME 1 references as exhausted, compile plausible clean C++ donor
TUs with BFME 2's toolchain and settings (flags from matched siblings) and search
their emitted bodies in `game.dat` with `tools/place_bodies.py <donor-TU>`, even
when the BFME 1 bytes have no match. Prioritize supported identities and siblings
of successful transfers; exclude dumps and retired or refuted candidates unless
new evidence addresses the earlier finding. This is a read-only lead search:
never claim the external donor path as BFME 2 source. Port supported bodies into
an allowed `Code/` TU, preserving the donor revision, flags and dependencies, and
pass the normal byte and identity gates. A placement proves neither identity nor
recovery.

### BFME 1 reference updates (moved from AGENTS.md, 2026-10)

AGENTS.md ("BFME 1 reference freshness") says when to check and what may never be
skipped; this is the full procedure.

Use the `reference/open-bfme-1` submodule for building and donor discovery. On
initialization, and before BFME 2 work when the last successful check is missing
or over 72 hours old, fetch official `Open-BFME/Open-BFME-1` `master`, compare
commit IDs, and preserve dirty or unpublished submodule work.

Initialize cross-repository references without recursion. Do not initialize a
nested reference back to BFME 1 or BFME 2. Initialize other required build
dependencies explicitly.

Complete the current layout migration once: reconcile the old `Code/` and
`reference/` paths with upstream's `game/` and `inputs/reference/`, including
source `// cl:` flags and other moved inputs, using the existing layout resolver
where applicable, and check the resolved directories and headers (MSVC silently
ignores a missing include directory, so compilation alone does not prove the
intended headers were used). Verify and commit this repair with the updated
pointer; repeat only if upstream changes its layout again.

For a routine update:

1. Record the previous verified pointer and the checkout revision; update the
   clean checkout to upstream HEAD, keeping enough to compare old and new inputs
   at the same BFME 2 revision.
2. Run BFME 2's full byte verification with valid dependency caches; compare
   failures with the previous inputs under the same conditions; repair update
   regressions and report pre-existing failures separately. Never weaken
   verification or substitute headers silently.
3. Refresh donor sweeps and compile trials affected by changed source, headers or
   settings; record the donor revision with cached results; discard or regenerate
   results whose inputs no longer agree.
4. Include the verified submodule pointer and any required repairs in the next
   commit batch: advancing the local checkout does not update what other
   contributors receive.

Record success in ignored `build/bfme1-last-check.txt` only after verification,
or when upstream is already at the verified pointer. Do not fetch per transfer. If
an update is blocked, keep the last verified inputs and report the exact blocker
and attempted repair; do not mark it successful or suspend future freshness
checks indefinitely.

## Work selection in detail (moved from AGENTS.md, 2026-10)

AGENTS.md ("Work loop") gives the order; this is how the picker applies it.

### The default pick

`python3 tools/next_work.py --claim` tries gate debt first, then the link, stub
closure, header, TU-approval, TU-evidence, consolidation, data, code-identity,
Microsoft-header, DirectX and STLport 4.6 queues in an order drawn by weight (link
26, stubs 12, header 15, tu-approval 4, tu-evidence 3, consolidate 20, data 8,
identity 4, ms-headers 4, dx 1, stlport 3; the
evidence for each number is beside `TIER_WEIGHTS` in `tools/next_work.py`;
`BFME_TIER_WEIGHTS` overrides), falling through when one is empty or fully
claimed. The structural queues (`repair_queue.STRUCTURAL_QUEUES`) retire no
register line: each item's pass test is its owning tool's verdict (a later link
cycle for stubs, `tu_skeleton.py --merge` for consolidation, the rebuilt
`tu_map` for approval, the byte gate for header and STLport migrations). The stub queue
reads a local link cycle's `stubs.json` checked against its receipt and the
receipt's commit against HEAD; elsewhere it is skipped with a note. Naming is
not a default tier: `--wb` and `tools/name_lane.py` serve it on request. A standing deferral (blocked, attempted) in
`reverse/re_attempts.log` comes after all untried debt work, and a recorded dead
end drops it. Debt whose source no longer exists is served first in its queue, as
a regression.

Those numbers are priors. `tools/tier_tuning.py` (called by `next_work.tier_weights`)
moves each share within 0.5x to 2x of its prior toward the tiers whose landings
moved a headline figure in the 48 h before `origin/master`'s tip. Yield is read
from ledger state on that SHA, never from commits or subjects: Code/ source files
removed net per commit (a move scores 0, and the total is capped at the window's
real drop in source files, so restore-then-remove churn earns nothing) for
consolidate, as a fraction of the source gap at the window's start (files minus
the TUs that commit's `tu_map.csv` names); keys the data and
code-identity registers lost, as a fraction of the debt headline (gate baseline,
the data, identity and header registers and hatch counts). The other tiers keep
their prior: linked bytes are census-only and fleet-wide, stubs come from a local
link cycle, tu_map approval also moves with renames and rebuilds, and the header
tier's yield is mostly the TU merges a canonical header unblocks, which land as
consolidate removals, so its own queue keys would undercount it. A measured tier's
multiplier is the square root of its yield per prior share over the measured
tiers' mean; the shares are then scaled to sum to 100 inside the band. An empty
or fully claimed queue already gets nothing: the draw falls through it, which
shares it out pro rata. The measurement is cached per SHA in `build/tier_tuning/`
(about 2 s for a new SHA, 4 s cold), so every seat on one SHA draws from the same
shares; a cache entry is used only if it validates, and a git read that fails is a
measurement error (priors, never cached), not an empty register. Every default
pick prints `tier shares: ...`, and `--json` carries `selection_meta.tier_tuning`
(`in_force` and the reason), so a failed measurement is visible.
Tuned shares can put consolidate above link; that is intended.

- `python3 tools/next_work.py --weights`: per tier the prior, measured yield,
  fraction of the gap closed, ratio to the mean, final share, queue depth (built
  like `--ranked`, so as slow) and the chance each tier is tried first now.
- Kill switch: `BFME_TIER_TUNING=off` or `--static-weights` restores the priors;
  any `BFME_TIER_WEIGHTS` override also turns tuning off.

A pick builds only the queues its draw reaches, the first of them in a background
thread while it reads claims from origin. What it computes is cached in the shared
picker cache (`<git common dir>/bfme-picker-cache/memo/`, every worktree of the
clone; `tools/picker_cache.py`): check_csv's green verdict, the gate-debt, TU-map,
consolidation (all but its claim-dependent order), TU-approval, TU-evidence,
Microsoft-header and STLport queues per tree state (HEAD, submodule commits and
every path `git status` reports, by content), validated against the untracked
files each read; ledger indexes per `functions.csv` content; ZH scans and per-file
class and `__FILE__` checks per content across commits. A second pick on one
commit takes a few seconds; the first on a new commit rebuilds what changed.
`BFME_PICKER_CACHE=off` computes everything; `BFME_PICKER_CACHE=<dir>` moves it.

After the debt queues come the new-match tiers (Zero Hour packets, reloc-named,
drift, structural, Ghidra- and string-anchored). They should have no new uncovered
bytes to serve in the current tree. If a candidate appears, first check current
matched ranges, generated/alias owners, proven boundaries and stale queue inputs.
Only call it regression repair after history or `reverse/deleted_rows.csv`
establishes a lost row. Restore that row in its approved unit; a
`repair_queue.py dest 0xRVA` fallback is a lead, not TU approval. Do not add a
duplicate claim or a fresh one-function file just because the picker served it.

`next_work.py --wb` is served on request only. Its band 0 offers rowed bodies with
placeholder or pin-only names (`Rva*`, `helper*`) that a WorldBuilder lead can
name. For an existing matched C++ body, grade the lead with `name_evidence.py`
and use the guarded `rename.py` workflow in `docs/naming.md`; a WorldBuilder
lead alone does not prove the new name. A generated or dumped body needs actual
clean C++ recovery through the normal `add_match.py` admission and byte gates
(`--replace-rva <rva>` where appropriate). Do not reconstruct or replace an
already recovered body merely to rename it. Band 1 (unrowed) needs the same
coverage, ownership, freshness and history checks as other apparent gaps.

### Cleanup lane details

- Generated funclets onto real parents: repoint a `Code/gen_small/uw_gen_*.cpp`
  row to the `$L` label its matched parent emits, only where `tools/eh_verify.py`
  finds the parent's EH graph EXACT and binding that label to the retail funclet.
- Microsoft headers: `python3 tools/repair_queue.py ms-headers [--claim]` lists
  local copies of CRT, Windows SDK and MS STL definitions. A `drop-in-candidate`
  is only a candidate, and `./build.sh` byte verification is the authority; a CRT
  dllimport conflict needs a per-body callee check, never a blanket replacement.
- DirectX SDK: `next_work.py --tier dx [--claim]` serves a unit to move off the
  `reference/shims` DirectX stand-ins onto the vendored August 2005 SDK
  (`vendor/dxsdk-aug2005/`, opted in with a `// dxsdk` line).
- STLport: retail linked STLport 4.6 (evidence: `vendor/stlport-4.6/PROVENANCE.md`),
  not the 4.5.3 in `vendor/stlport`. A unit moves to the pristine 4.6 headers
  and the BFME patch layer (`vendor/stlport-4.6-bfme/`) with an exact
  `// stlport46` line. `python3 tools/repair_queue.py stlport` serves whole files
  whose rows the trial lane (`tools/stlport_trial.py`, `reverse/stlport_trial.csv`)
  saw match under 4.6, among files that carry the `// stlport` line (a file without
  it compiles no STLport header, so its trial rows prove nothing); the queue is a
  lead, `./build.sh` of the whole file is the proof. Repoint every row with `add_match.py --replace-existing`, notes gaining
  `migrated=stlport-4.6`. `next_work.py --tier stlport [--claim]` serves one file
  with its move and a `file:` claim. Its `adapt` knob (drop 4.5.3's `const` from the
  unit's allocator declarations) always applies; try the others (`-shim`, `-D`) only
  if the marker alone fails, since the opt-in already swaps each `reference/shims`
  STLport overlay for its 4.6 port.

### Work the file, not the row

`next_work.py` lists every other queued candidate in the same source file: that
file is your unit of work; drain it first (land rate 19.5% solo, 46.5% with ten or
more siblings landed together). Draining means a sequence of verified changes:
finish or revert each body or homogeneous batch before starting the next. A shared
header edit costs a full gate: edit every dependent body, pay once. When several
files in one subsystem show the same successful repair pattern, prioritize that
subsystem, checking that each evidence-backed delta applies (folder structure
alone is not evidence); return to the broad queue when behavior diverges.

### Investigate shared deltas first

When multiple failures suggest the same layout, offset, callee, compiler, ABI or
wrapper difference, test that shared explanation before retrying each body. Apply
a shared fix only where target evidence supports it; similar symptoms alone do not
establish a common cause. Do not repeat attempts blocked on the same unresolved
dependency: continue with independent candidates and resweep affected units once
it is resolved.

### Batch homogeneous trivial changes

Atomic does not mean one function per commit. When changes use one established
pattern and form one coherent, reviewable change (tiny getters/setters, thunks,
wrappers, global or hatch replacements differing only by verified RVA or offset),
make, ledger, verify and commit them as one batch, roughly 5–20 entries (a
guideline, not a quota or hard limit). Similar instruction shapes do not establish
identity, types, calling convention or layout: verify each member against its own
evidence. Keep substantive reconstruction, or work needing distinct identity,
compiler, ABI/layout or reconstruction reasoning, in separate commits. Verify the
whole batch before committing. If a member fails, determine whether that
undermines the shared pattern; continue with the remaining members only if their
evidence and verification still hold, otherwise reassess the batch.

## Frozen files (moved from AGENTS.md, 2026-10)

`find_declared_unmatched` refuses a staged source that defines **any** function
the ledger does not declare, and nothing re-checks unstaged files, so a file can
become uneditable. Check before planning work in one (silent means it commits):
`python3 tools/find_declared_unmatched.py <file>`.

Two remedies, not interchangeable:

- **Row the body**: real work, and the reason the file is frozen.
- **An `absent-from-retail` marker**, one per definition, only for a body retail
  dead-stripped; honest only where true, never to hide an over-claim. It must
  start `// ?` (`// ?<Class::method> absent-from-retail`) or it is silently
  ignored; the label is free, only the trailing word is read. Do not copy a
  ledger row's trailing comma into it (`// ?<mangled>,` misses).

Never hand-add a `present-unmatched` marker: it is a counted escape hatch, and the
enforced hatch gate refuses its unadmitted growth (`tools/hatch_counters.py`;
regression `tools/tests/test_hatch_counters.py`). Existing ones may be removed.

Read the undeclared definitions the report names. Before adding markers, remove
stale ones: a marker on a definition that IS matched is reported "still marked
present-unmatched (stale annotation)", and an add-only pass makes that worse.
After any marker change, re-run `find_declared_unmatched`
on that file and revert your whole file attempt if it still refuses (the report
gives `Class::method` without argument types, so a marker can land on the wrong
overload). The error message's suggestion of
`reverse/unclaimed_sources_whitelist.txt` does not apply: that protected list
(`tools/protected_paths.py`) only exempts sources with zero matched rows and may
only shrink.

## The build cache trap (moved from AGENTS.md, 2026-10)

Do not compile by hand through `tools/build.py` (`build.compile_source`) to see a
raw error: it writes the shared cache `build/match/<mangled-source-path>.obj`, and
later `./build.sh` and `explain_mismatch` runs silently reuse your object (the
symptom: a body that stops emitting its symbol). The tell is a cached `.obj` whose
source path no longer exists; delete that `.obj` **and** its `.deps.json`. Read
raw errors from `build.sh` or the `explain_mismatch` traceback.
