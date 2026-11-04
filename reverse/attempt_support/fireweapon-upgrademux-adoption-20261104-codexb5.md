# FireWeaponWhenDeadBehavior UpgradeMux adoption

Inspected base: `af96165a3a8663715f06b18dc25ff0d851c4be4d`.
Worker: `yasinschroeder-codexb5`; model: GPT-6.

## Repair and evidence

`FireWeaponWhenDeadBehaviorOnDie.cpp` now includes the existing canonical
`GameLogic/Module/UpgradeMux.h` instead of declaring its own truncated mix-in.
The existing `isActiveUpgrade` helper calls the canonical slot-zero declaration
`isAlreadyUpgraded`. The removed view called that same slot `isUpgradeActive`;
its flag occupied the same +4 byte. The canonical header records the target
constructor, flag access and table-slot evidence. No shared header, ledger
identity, alias, pin or path changes accompany this adoption.

The original supported adoption trial failed with C3861 at the helper call.
After selecting the canonical declaration, supported adoption with `--apply`
passes. `header_adopt_lane.py accept --class UpgradeMux` passes and retires
exactly this source's UpgradeMux row from `reverse/header_queue.tsv`.

## Verification

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehaviorOnDie.cpp`:
  1/1 exact, the complete 310-byte onDie body at RVA 0x00482C4A; string,
  floating-point and import reference checks pass.
- `find_declared_unmatched.py` on the source: all defined functions matched.
- `link_check.py` on the source: LINKS, 310 -> 310 authored bytes against
  index `f12552d0a7` (2026-11-04 20:47). This preserves its existing preview
  result; no census gain is claimed.
- `check_csv.py`: passes (99,452 function rows, 9,328 symbol rows,
  2,268 data rows). `git diff --check`: passes.

## Consolidation handoff

The Behavior consolidation planner surveyed 418 sources and produced 57 groups;
its stale-map warning is retained as context, not approval. The merge engine
rebuilds current assignments in memory. The initial supported dry run of
`FireWeaponWhenDeadBehavior.cpp` accepts no donor. It reports 12 approved rows,
two mixed sources and an UpgradeMux compile prerequisite. `tu_views.py --dry-run`
finds a compatible ModuleData superset but refuses the behavior's +0x2C field:
`Rva00263895Member` versus `Rva003427DD` (constructor versus assignment views).
No merge or file-count reduction is claimed.

A read-only supported UpdateModule adoption trial on the seed now passes,
unlike the queued historical compile failure. The class claim is held by
another worker; the seed was left unchanged and neither UpdateModule queue row
was retired. Next: adopt the seed when its claim is available, reconcile the
UpgradeMux/Die interfaces and the +0x2C member views, then retry the supported
TU merge with current objects and provider/consumer checks.

The post-adoption merge dry run still accepts no donor. UpgradeMux disappears
from `adopt_first`; Player remains for the donor, and UpdateModule and
UpdateModuleInterface remain for the seed. The current compile stop is C2143 /
C2501 at temporary composed-source line 191. `reconcile_classes` now names only
FireWeaponWhenDeadBehavior. The passing standalone byte/link result above is the
retained change; do not mistake the merge trial for a verified composition.
