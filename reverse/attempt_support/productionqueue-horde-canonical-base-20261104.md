# ProductionQueueHordeContain canonical module-data base

Inspected revision: `186e92f871d2b95a40872d4264f516eef19a2a7d`.
Scope: `Code/GameEngine/Source/GameLogic/Object/Contain/ProductionQueueHordeContain.cpp`.

The consolidation picker selected this TU and six whole-file donors. The
initial `tu_skeleton.py --merge ... --dry-run` accepted none: behavior views
disagree about their base and virtual interface; element views disagree about
their fields; `_Construct` has competing explicit instantiation/specialization
declarations. No donor was moved or deleted. Four mixed files remain outside
the whole-file merge scope.

The TU's private HordeGarrisonContainModuleData view occupied 0x58 bytes and
the derived view added 0x7C padding before its vector at +0xD4. The registered
header documents the actual 0xD4 base, including its GarrisonContainModuleData
parent and fields. Replacing that private view with the existing header and
removing the compensating padding preserves the vector's offset and the 0xE0
derived size. No header, function identity, pin, alias or ledger row changed.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Contain/ProductionQueueHordeContain.cpp`:
  all 16 rows match; strings, floats and imports pass. Existing EH labels are
  verified through the parent EH graph after compiler label renumbering.
- `find_declared_unmatched.py` on the TU and all six donors: all defined
  functions already matched, both before this edit and on the edited TU.
- `header_adopt_lane.py accept --class HordeGarrisonContainModuleData` on the
  TU: PASS, retired exactly its one `reverse/header_queue.tsv` row.
- `link_check.py` on the TU: LINKS, census 425 -> current preview 441 authored
  bytes against the 2026-11-04 13:15 census at `f6d845ecd4`. This is a local
  provider/binding preview, not a new census or headline measurement.
- `check_csv.py`: OK (99,451 function rows; 9,331 symbols; 2,268 data rows).

The initial planner snapshot under ignored `build/consolidation` covered the
Contain subsystem, including original-path alternatives and routing blockers;
the source edit invalidates that snapshot. This prerequisite repair moves no
paths or protected-register keys. Existing data/identity/hatch debt is kept;
the sole retired header row passed its owning lane's acceptance command.

Remaining consolidation work: reconcile the behavior base/interface views and
the eight-byte vector element, then reconcile the module-data destructor's
direct Garrison base and element type with this TU's canonical intermediate
base and vector member. These are source-model disagreements, not demonstrated
link regressions; the TU and its donors were census-linked in the merge guard.
Refresh the evidence planner and run a new merge trial after those repairs.
