# Native tree binding repair for Rva000D3FA0Map

2026-10-30, base `39b2df5afd`, owner `yasinschroeder-codex3`.
The default picker claimed `0x00241C20` and
`file:Code/GameEngine/Source/Common/RTS/Rva000D3FA0Destructor.cpp`.
This repairs existing matched placeholders; there is no new code coverage,
canonical container name, source-path move or approved-TU claim.

## Target facts

The complete 72-byte destructor at `0x004398D8` uses its member at `this+4`
for calls to `0x00240C60` and `0x002418E2`. The 41-byte clear body tests the
count at +4, tears down the root, resets sentinel left/right to itself and
parent/count to zero. These are red-black-tree operations, rather than hash
bucket traversal. Its existing owner is
`?rva00240C60@Rva00439325@@QAEXXZ` in `Rva00439325Erase.cpp`.
The existing 56-byte destructor owner `??1Rva00439325@@QAE@XZ` in
`RvaTreeDtorFamily.cpp` clears and frees the sentinel. Neither provider is
edited or given an additional pin.

The complete five-byte forwards at `0x0043985D` and `0x00241C20` jump to
those clear/destructor owners respectively. Parent unwind funclet
`0x007881E6` loads its saved this, adds four and jumps to `0x00241C20`.
The other parent funclet destroys canonical Snapshot. Native vptr stores
remain `0x00BEE024` and `0x00BBB554`.

These facts support an eight-byte tree view and a containing lifetime
wrapper, not an original payload or container name. Both wrappers retain
address-derived names. The old `hash_map<unsigned, Relationship>` view and
two hashtable pins falsely assigned hash-table names to existing tree bodies.
Their comments used a donor/ICF conjecture; no donor source establishes this
BFME 2 container identity. The erroneous wrapper names are tombstoned while
their same ranges remain matched. The source's incorrect 89-byte/donor/vptr
comment is removed. The existing three virtual-slot alternate names stay.

## Verification

- `./build.sh Code/GameEngine/Source/Common/RTS/Rva000D3FA0Destructor.cpp`
  passes all six rows and literal/import checks. The compiler's renumbered
  local funclets resolve through their existing parent evidence.
- The canonical Snapshot vtable pair (`Rva000D3FA0Destructor.cpp` and
  `Rva00243177.cpp`) passes EH verification: EXACT 3, no missing objects.
- `find_declared_unmatched.py` passes before and after the source edit.
- `pin_consistency.py --check` passes after removing the two obsolete pins.
- `check_csv.py` passes: 99,010 function rows; matching coverage is retained.

## Debt retirement boundary

`repair_queue.py retire identity` refuses the change because its HEAD-name
coverage comparison treats the two retyped wrapper names as missing rows.
Both RVAs retain their five-byte matched rows and the parent verifies, but
this check does not accept tombstones/retyping as coverage evidence. The
four identity-register keys are deliberately retained; no debt-register
retirement is claimed. The false reject is recorded through `re_log.py`.
No verifier code or baseline is edited to get around it.

Strict preparation passes 236/236 rows across the edited source, both native
tree providers and the constructor/vtable partner, with 58 funclet bindings
and reusable receipts. Ordinary preview against the fetched index
`85f6b7f40c` (2026-10-29 15:08) reports all four LINKS: destructor 0 -> 82,
clear provider 100 -> 100, destructor family 4,823 -> 4,823, constructor
partner 154 -> 154 authored bytes. This is a prediction, not a census gain.
The earlier destructor-only preview failed on two COMDAT and two selected
hashtable identities. Outgoing audit results follow below. No census, ownership or smoke gain is
claimed; no nightly or maintainer-only runner is invoked.

## Outgoing audit

The audit of the staged tree against `origin/master` (`c5e059b5ac`) returns
INCONCLUSIVE (exit 2): the census index at `85f6b7f40c` predates the base,
and the affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. This covers the entire outgoing batch, including its earlier CRT
header and word-vector migration commits. No proven regression is reported,
but consumer selection/loss verification did not complete. Carry the changed
sources, removed hashtable identities, existing native tree providers,
vtable partner and affected consumers into the next scheduled census.

## Final verification and counter follow-up

The commit hook passes 3,160/3,160 rows across 95 affected sources, all 45
data rows, literal/import checks and EXACT 317 EH rows. Commit `f250e22f26`
was handed to the runner's fleet publisher with the three earlier commits.

The missing CreateAHeroManager consumer now has a strict reusable receipt:
23/23 rows and its literal/import checks pass. Repeating the outgoing audit
still returns INCONCLUSIVE: the index predates the base, and the wider scope
has 181 source objects without current receipts (first
`Common/AIBasePenetrationTroopsTactic_canRun.cpp`). This clears only the
specific missing consumer receipt, not full consumer selection/loss checks.
Scheduled census confirmation remains pending.

`hatch_counters.py --update` removes the two obsolete pin occurrences:
`0x00240C60` goes from two to one and `0x002418E2` from one to zero. It also
removes the stale narrow StringBase destructor exemption in
`BodyModuleDeletingDtors.cpp`, whose private copy and marker were removed by
upstream commit `49eb6d6520`. Inspection of that change confirms the canonical
header replacement; the current source passes its declared-body check and
all five matched rows plus literal/import checks. No source changes accompany
this inherited counter cleanup. Register totals fall from 9,415 to 9,413
pins and from 3,662 to 3,661 present-unmatched occurrences. The four identity
keys remain unchanged.
