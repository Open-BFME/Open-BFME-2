# Buddy status CRT declarations and allocator binding

Inspected base: `c790c01553419f7cce4752f812e425b953243031`.
Claimed source: `Code/GameEngine/Source/Common/Rva003896E7Permuted.cpp`.

Replace the copied stdlib declarations and `_INC_STDLIB` suppression with the
toolchain's real `stdlib.h`. Keep its imported CRT declarations intact. While
the STLport headers and the existing inline cleanup specializations are read,
bind their `free` calls to the existing `_STL::free` GameMemory provider, as in
the PartitionManager header-adoption pattern. Undefine that macro immediately
after the includes and specializations.

Target facts:

- The existing 347-byte `updateBuddyStatus` row starts at RVA `0x003896E7`.
  Its direct calls at `0x00389715` and `0x0038982E` both reach `0x00030830`,
  the rowed GameMemory wrapper. They do not use the CRT free import thunk at
  `0x00628F98` or its IAT entry.
- The already committed `?free@_STL@@YAXPAX@Z` pin identifies that wrapper.
  No pin, alias, row, class layout, compiler flag or source path is added.
  These call-target facts do not establish a new donor name or layout.

Verification:

- Ordinary baseline and final builds pass all three rows (parent, handler and
  parent-proven cleanup funclet), nine nonempty strings, one empty-string
  reference and one named import. Frozen-file checks pass before and after.
- Supported `link_check.py --prepare-current` passes all three rows with strict
  reusable compiler receipts. Its ordinary gate reuses those exact objects.
- The external COMDAT inventory remains exactly fifteen names. Every body byte
  and extent is unchanged. Thirteen fingerprints are identical; the two
  changed fingerprints belong to `updateBuddyStatus` and the string destructor.
  Their only binding changes replace `_free` with `?free@_STL@@YAXPAX@Z` at
  two parent calls and one destructor call. The external symbol inventory
  changes only that undefined name. Scratch snapshots and the complete
  relocation comparison are under `build/buddy-crt-20261030-codexb4/`.
- The ordinary current-object preview remains LINKS, 347 -> 347 authored
  bytes, against the 2026-10-30 04:25 index at `6fe1089c24`. This is a preview,
  not a census gain or runtime result.

An initial header trial with empty `_CRTIMP` failed to compile because other
real headers redeclared shared CRT names with imported linkage. It was replaced
by the consistent imported-header form above; no failed reconstruction remains.

The outgoing source-tree consumer audit exits 2, INCONCLUSIVE. Its index at
`6fe1089c24` predates the inspected base, and the affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
compiler receipt. The changed source itself has its strict receipt. Carry this
source and affected consumers into the scheduled census; no whole-batch link
closure is claimed. LINK-006 retains that prerequisite.

The supported Microsoft-header scanner rebuilt its current index and the
scoped `refresh_queue` API refreshed this source alone. The queue moves from
31 copied definitions (five same, two mangling conflicts and 24 ABI conflicts)
to one unverified `free` macro. The macro differs from the debug CRT's
function-like macro; no claim of complete Microsoft-header clearance is made.
The scanner also retains two unresolved include-closure notes for
`Lib/BaseType.h` and `GameNetwork/GameSpy/BuddyThread.h`. All unrelated queue
records remain intact.
