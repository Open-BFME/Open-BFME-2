# AIGroup consolidation prerequisite, 2026-11-04

Scope: `Code/GameEngine/Source/GameLogic/AI/AIGroup.cpp` and the eight
single-TU donors served by `next_work.py --tier consolidate --claim`.
No source paths or ledger owners moved in this pass.

## Verified prerequisite

`AIGroupDeleter.cpp` already defines the absent-from-retail
`AIGroup(EmitVtableTag *)` constructor that emits its deleting destructor.
The destination class view lacked the declaration, so composition failed
with C2511. The published prerequisite adds that declaration and its tag
forward declaration to the destination view.

- `./build.sh Code/GameEngine/Source/GameLogic/AI/AIGroup.cpp`:
  104/104 rows exact, including the existing funclet-label remapping and
  STLport constructor-fold checks; one string and 26 float literals verified.
- `eh_verify.py` on that source: eight EH rows EXACT, none baselined.
- `find_declared_unmatched.py`: passed for all nine selected sources before
  work and for the destination after the declaration change.
- `link_check.py`: LINKS, 12,881 -> 12,881 bytes against the published
  2026-11-04 13:15 census index at f6d845ecd4. This is a preview, not a census.
- Normal commit hooks passed; data shadow scan found zero findings. Code
  identity remained in shadow and reported two iterator/const-begin findings.

## Composition and claim boundary

The initial `tu_skeleton.py --merge ... --dry-run` accepted no donor.
After the prerequisite, the same command exits zero and accepts only
`AIGroup.cpp` plus `AIGroupDeleter.cpp`, with `rows: 100` in the plan and
the census-linked link guard enabled. The merge engine verifies every
baseline row before accepting this composition.

The actual apply command stopped before writing files:
`blocked: held by another worker: 0x0014F3C4`.
The live claim listed another worker's verified change awaiting publication.
The merge engine rolled back this pass's claims. No file reduction is claimed.
Once the shared claim clears, rerun the normal merge command and all audits.
The plan requires the generated `Verifier-Change` transfer trailer for the
hatch register; preserve that trailer on an eventual merge commit.

## Remaining donors and checks

The final dry-run still rejects GetCenter (AI/TheAI declaration ordering),
AttackTeam (incomplete ThingTemplate), BroadcastOrders (CommandSourceType
ordering), GetCommandButtonSourceObject (GUICommandType ordering and duplicate
MAX_COMMANDS_PER_SET), Xfer (private m_node versus the STLport member list),
Add (canonical Object header conflicts with the destination's fuller view),
and Scatter (duplicate iterator comparison template). These are composition
diagnostics, not proof that changing the named declaration alone will suffice.
`tu_views.py --dry-run` also identifies differing Coord3DCopy,
SimpleObjectIterator, Object and SpawnBehaviorInterface views.

Header debt stays with its current source paths. The selected donors have
existing header-queue entries; no data/identity debt was retired. There is no
path-move consumer audit to apply until a merge actually writes source paths.
The original-path planner was consulted before work, refreshed after the final
trial, and passed `name_lane.py consolidate --check build/consolidation`.
The TU engine rebuilt stale map inputs in memory. Do not commit a regenerated
TU map.
