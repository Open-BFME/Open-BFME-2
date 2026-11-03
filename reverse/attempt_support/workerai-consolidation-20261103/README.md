# WorkerAIUpdate consolidation: current declaration blockers

Inspected revision: `2ec4cfb034acdb88159d1db7540f717b91cb097a`.
Target: `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate.cpp`.
No game source, ledger row, pin, alias or protected register was changed.

The current `tu_skeleton.py --merge <target> --dry-run` rebuilds the stale
TU map in memory. It finds 72 approved rows, 14 mixed donors, no refused
donors and five candidate donor files besides the existing target. It accepts
none and exits 2. Unlike the earlier attempt in `re_attempts.log`, the seed
no longer fails because `WORKER_FIELDS` is missing. Current rejections are:

| Donor | First reported compile blocker |
| --- | --- |
| `WorkerAIUpdateCtor.cpp` | Canonical `Lib/Coord3D.h` redefines `Coord3D` alongside the seed's reference headers; the lookup view also conflicts. |
| `WorkerAIUpdateDtor.cpp` (under `GameLogic/Module/`) | The seed's `MemoryPoolObject::deleteInstance()` does not accept the donor's integer flag argument. |
| `Rva004A9E3ESound.cpp` (under `Source/Common/`) | Canonical `GameAudio.h` includes canonical `SubsystemInterface`, conflicting with the seed's reference-backed subsystem definition. |
| `WorkerAIUpdateDeleter.cpp` | The seed's `WorkerAIUpdate` declaration lacks the donor's synthetic `EmitVtableTag *` constructor. |
| `WorkerAIUpdateXfer.cpp` | Canonical `BfmeXfer.h`/`XferVersion.h` conflict with the seed's `Xfer` declaration. |

The tool lists canonical-header prerequisites in the ctor: AICommandInterface,
AIUpdateInterface, GeometryInfo, ModelConditionFlags, Player, State,
StateConditionInfo, Thing, ThingTemplate, UpdateModule, UpdateModuleInterface
and Vector3. The xfer donor additionally needs AIUpdateInterface adoption.

`tu_views.py <target> --dry-run` exits 0 but identifies structural conflicts:
the three state-machine private views have different bases between ctor and
dtor; four WorkerAIUpdate views have different bases; Rva004A9947 differs in
`novtable`; BfmeWorkerDockPoint differs in class-key without a matched symbol
settling it. Its two mechanical plans (Rva004A99F6 and Rva002D9531) do not
address the reported merge blockers and were not applied.

Verification:

- `check_csv.py`: OK, 99,430 function rows, 9,343 symbol rows, 2,269 data rows.
- `name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/`:
  completed; 107 source files surveyed, 25 investigation groups, no missing
  inputs. Its stale-map warning is not an approval; the merge uses a fresh
  in-memory map.
- `find_declared_unmatched.py` for the target and all five donors: all defined
  functions already matched (existing admitted markers remain).
- `./build.sh <target>`: 17/17 matched, one string literal checked; the
  renumbered `$L310` funclet is verified through its parent's EH data.
- `reverse/link_status.csv` records all six files as linked. The dry-run's
  link guard likewise identifies all six as census-linked; no merged object
  reaches clearance. No new census or headline change is claimed.

Next useful work: reconcile a donor's canonical headers with the seed's
reference-backed declarations in a separate verified commit, then retry the
merge. For the sound donor, preserve its canonical AudioManager and fix the
seed's competing subsystem/audio environment first. For the dtor, settle the
state-machine inheritance and destructor-call contract before changing calls.
Its eight link-wide aliases remain intact; removing them requires an all-object
consumer audit or another retained provider, not just this unit's byte result.
