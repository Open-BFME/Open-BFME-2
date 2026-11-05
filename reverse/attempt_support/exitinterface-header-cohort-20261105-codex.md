# ExitInterface consumer cohort, 2026-11-05

Inspected source: `b4138cc419`. Census preview: `f44cbcf5b0`, 2026-11-05 15:19 UTC.

Eight queued consumers now include the existing canonical ExitInterface header.
The changes spell native virtual slots by their canonical names, pass position
and angle outputs by reference, and retain reserved doors as ExitDoorType.
No header, compiler flag, ledger row, source path, alias or pin changed.

`./build.sh` verified 135/135 rows over the nine-file trial, including the
41-row AIDock attempt later restored. String, float, import and data-row checks
passed. All eight retained files pass `find_declared_unmatched.py` afterwards;
`check_csv.py` passes. One whole-cohort `header_adopt_lane.py accept --class
ExitInterface` retired exactly eight queue rows and retained the two refusals.
The final retained scope is 94 byte-matched rows. A combined eight-file
`link_check.py` preview passes 8/8 consumers and preserves 14,303/14,303
census-linked bytes against the above index.

## Provider preservation

Each removed private ExitInterface view contains declarations only, no inline
bodies. For every retained object, compare the fresh COFF external-definition
set against the union of its strong and COMDAT definitions in the census index.
No prior external definition is missing. This covers every symbol supplied by
these objects, including definitions other objects might import through aliases.
No `/alternatename` changed.

| Consumer | Prior definitions | Fresh definitions | Removed |
| --- | ---: | ---: | ---: |
| `Code/GameEngine/Source/GameClient/InGameUICanSelectedObjectsDoAction.cpp` | 11 | 11 | 0 |
| `Code/GameEngine/Source/GameLogic/AI/AIHordeCowerStateSlots.cpp` | 31 | 31 | 0 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorBuildCastleStructure.cpp` | 32 | 32 | 0 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva0046CF21.cpp` | 5 | 5 | 0 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateQueryRallyOverride.cpp` | 11 | 11 | 0 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionUpdateQueue.cpp` | 690 | 690 | 0 |
| `Code/GameEngine/Source/GameLogic/Object/Update/Rva0049D526.cpp` | 3 | 3 | 0 |
| `Code/GameEngine/Source/GameLogic/System/GameLogicDispatchDoSetRallyPoint.cpp` | 18 | 18 | 0 |

## Remaining cohort prerequisites

- AIDock: the canonical trial preserves all 41 matched rows and 53/53 external
  definitions, but acceptance predicts a 2,608-byte loss on
  `??_7AIDockMachine@@6B@`: its unaddressed COMDAT differs from the first copy
  in link order. Restoring the original source and rebuilding reproduces the
  identical blocker. The attempt is restored and its queue row remains.
  Reconcile the AIDockMachine table/provider cohort before retrying adoption.
- HordeSiegeEngineContainRva0047D53A: its private type named ExitInterface is
  actually a 42-slot contain receiver with `remove(Object*,bool)` at slot 41,
  reached at this+0x20. The canonical exit interface has only 12 slots and lives
  at another subobject. This file remains unchanged; establish the correct
  contain receiver identity and evidence before attempting its header adoption.

These are preview and byte-verification results, not a new real link or game run.
