# InstantDeathBehavior merge handoff (2026-11-04, codex4)

Base: `86bac9c573` (handed to the fleet publisher). Native seed recovery and
four hatch removals are complete; see
[the repair evidence](instantdeath-native-field-table-20261104-codex4.md).

The supported consolidation planner was regenerated after that source change.
The byte/link-guarded dry run accepts the seed plus:

- InstantDeathBehaviorPoolKey.cpp (3 rows)
- InstantDeathBehaviorCtor.cpp (1 row)
- InstantDeathBehaviorModuleDataCtor.cpp (2 rows)

All live under `Code/GameEngine/Source/GameLogic/Object/Behavior/`.
With the seed, this is seven rows and would remove three source files.
No move has been applied: the applying tool exits 2 before writing because
shared rows 0x00068E15, 0x0007E48F and 0x002DFCF6 are held by
`yasinschroeder-codex2`. Claims list reports AptTimeLineStats.cpp for the first
and SiegeDockingBehavior.cpp for the other two. Do not bypass the claim check.
The tool releases any portion it acquired on refusal; no retained TU source
or ledger path differs from the published native-seed repair.

Next: after those claims settle, regenerate/check the supported planner and
run tu_skeleton.py --merge on the approved InstantDeathBehavior.cpp. Verify
and publish the merge separately, with its printed register-transfer trailer
and the batch path-consumer audit. The prior dry run is evidence, not authority
to apply a manual composition.

Rejected donors remain unchanged: parser files need typed member views;
onDie needs compatible names/layout and two canonical header adoptions;
module-data dtor composition fails bytes. RvaVectorDtorFamily.cpp and
DieModuleDerived.cpp remain mixed. Preserve all their rows. No source-count
reduction, census gain, game link or smoke result is claimed by this handoff.
