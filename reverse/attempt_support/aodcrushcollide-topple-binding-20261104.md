# AODCrushCollide external vtable consumer and merge handoff

2026-11-04; repair parent `faf660ef4a`. Continues
[the prerequisite report](aodcrushcollide-consolidation-20261104.md).

The post-adoption merge retry still required
`??_7AODCrushCollide@@6BCollideDtorB2@@@`. A binary search across every
`build/match/*.obj` found a real external consumer:
`Code/GameEngine/Source/GameLogic/Object/Update/ToppleUpdateCtor.cpp`.
Its source explicitly used that name for the constructor's +0x0C vptr.
The isolated adoption and destructor preview had not checked that consumer.

## Target evidence and repair

Retail destructor RVA 0x004BBEDD writes VA 0x00C5A260 at +0x0C;
retail ToppleUpdate destructor RVA 0x004A8091 writes the same VA at +0x0C.
The new, normally built AODCrushCollide destructor object defines
`??_7AODCrushCollide@@6BBehaviorModuleInterface@@@` for that subobject.
Rebound ToppleUpdateCtor's declaration and use to that existing provider.
No alias, pin, hatch, layout, or /alternatename pragma was added or removed.

Checks:

- `./build.sh .../ToppleUpdateCtor.cpp`: 2/2 rows exact, 157-byte constructor
  and 10-byte compiler-emitted EH handler; source/string/float/import checks pass.
- `find_declared_unmatched.py .../ToppleUpdateCtor.cpp`: all bodies matched.
- `link_check.py --fetch-index`: official index dated 2026-11-04 20:47 at
  `f12552d0a7` (16,963 compiled objects fetched to the store).
- Joint current-object `link_check.py` on AODCrushCollideDtor and
  ToppleUpdateCtor: both LINKS, 60 -> 60 and 167 -> 167 bytes respectively.
- Repeated binary search across `build/match/*.obj` after the rebind: no
  occurrence of the old CollideDtorB2 vtable symbol. This is a cached-object
  audit, not a new full-game link or census.
- `git diff --check`: pass. Existing scoped locals and parameters retain
  their clear names; no naming edits were needed for this binding repair.

## Remaining prerequisites

A new guarded merge dry run after fetching the index and verifying both current
objects still rejects AODCrushCollideDtor: the index retains the old external
ToppleUpdateCtor reference. Current paired previews pass, but the guard does not
replace that outside consumer. Record this conservative stale-input rejection
in re_attempts.log; no guard or index was hand-edited and no merge was applied.
Retry after supported provider-index refresh/census includes the rebound
consumer, or after a separate tooling fix can authenticate current outside
consumer provenance. This report does not authorize maintainer-only runners.

The independent FamilyDeletingDtors_muse-95ab byte mismatch remains. Its
DominateEnemySpecialPowerModuleData header debt and both rows remain intact.
The main AODCrushCollide TU was not edited, and no source path moved.
No headline linking gain or source-file reduction is claimed. One header-queue
row was retired by the prerequisite repair's acceptance tool.
