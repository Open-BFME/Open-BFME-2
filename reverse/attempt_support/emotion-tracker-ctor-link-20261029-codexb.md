# EmotionTracker constructor ObjectModule adoption

Inspected base: `76edfbb817`, 2026-10-29. Published preview index:
`85f6b7f40c`, 2026-10-29 15:08. Claimed scope: constructor 0x004B21B9
and `Code/GameEngine/Source/GameLogic/Object/Update/EmotionTrackerUpdateCtor.cpp`.

The current constructor failed the ordinary link preview on one COMDAT:
`??_7EmotionTrackerUpdate@@6BObjectModule@@@`, whose definition differed
from the first copy in link order. Its private ObjectModule declared only a
virtual destructor. The destructor source already includes the canonical
ObjectModule header and consequently emits the inherited Module/Snapshot
virtual slots. The current blocker differs from the older missing
UpdateModuleInterface::update provider recorded in the obstacle register.

The constructor now includes the same canonical ObjectModule header. Its
existing ID access views the shared `Object *m_object` through the existing
local Thing layout at +0x74. This explicit cast resolves the incomplete-Object
error recorded by the prior header-adoption attempt, while preserving the
native access and every constructor byte. No canonical header was changed.
The separate Thing adoption remains queued; this change does not establish
a complete retail EmotionTracker virtual interface or recover its remaining
placeholder type identities.

The BFME 1 constructor at verified reference `f64f0f32d56a` was reviewed:
it retains private base views and is only a structural donor lead. The
BFME 2 destructor's existing shared-header use and current object/link results
support this repair. BFME 1 layout, interfaces and vector element spelling
were not imported.

Verification:

- `find_declared_unmatched.py` passes before and after the change.
- `./build.sh` retains all five constructor rows, including three compiler
  funclets verified through the parent EH graph after label renumbering.
- `eh_verify.py` reports EXACT for the constructor and destructor graphs.
- Strict `link_check.py --prepare-current` verifies 11/11 rows across the
  constructor and unchanged destructor with reusable receipts.
- Ordinary paired preview reports LINKS for both: constructor 0 -> 430
  authored bytes, destructor 159 -> 159, total 159 -> 589. These are preview
  values, not census gains; the picker originally described 460 raw row bytes.
- `header_adopt_lane.py accept --class ObjectModule` passes and retires one
  row from `reverse/header_queue.tsv` through the owning tool.
- `check_csv.py` passes. No source paths, ledger rows, pins or hatches change.

The staged-tree batch audit is INCONCLUSIVE: the index predates the inspected
base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry that consumer and this provider scope into the next scheduled
census. The bounded paired preview is verified; full consumer closure and
census confirmation remain pending.
