# LevelUpUpgrade header adoption and consolidation boundary

Inspected revision: `eb6aa2afcfc40112d6bd7ef4322c9d9472dfa53e`.
Scope: `Code/GameEngine/Source/GameLogic/Object/Upgrade/LevelUpUpgrade.cpp`
and its `LevelUpUpgradeMuxSlots.cpp` donor. Picker claimed both files.

## Completed

Replaced the donor's private `ExperienceTracker` with
`Code/GameEngine/Include/GameLogic/ExperienceTracker.h`. Both level reads use
canonical field `m_24`, at the same +0x24 offset as the old `m_level` view.
No function, global, class or member was renamed.

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Upgrade/LevelUpUpgradeMuxSlots.cpp`:
  2/2 matched; source, string, float and import checks passed.
- `find_declared_unmatched.py` reports all definitions matched for both files
  before work, and for the changed donor after work.
- `header_adopt_lane.py accept --class ExperienceTracker` on the donor: PASS;
  retired its one `reverse/header_queue.tsv` row through the owning tool. Its
  scoped link guard also passed. A separate `link_check.py --refresh` was
  interrupted during broad stale-provider cache restoration; it supplies no
  verdict and is not counted as verification.
- No changes to data/identity baselines, pins, aliases or source paths.

## Consolidation still blocked

The supported planner surveyed the Upgrade directory (144 sources, 20 groups).
Its committed TU map is stale, so the consolidation tool rebuilt placement in
memory; no regenerated map is committed. The successful planner snapshot was
made after the dry-run completed (an earlier concurrent scan encountered a
removed temporary composition and was discarded).

`tu_skeleton.py --merge .../LevelUpUpgrade.cpp --dry-run` accepted no donors.
The mux donor failed C2504 (undefined `UpgradeMux` base) and C2511 (missing
`LevelUpUpgrade` constructor overload). LinkGuard protects both census-linked
units. The mixed `FireWeaponWhenDeadBehaviorDerived.cpp` donor remains untouched.

`tu_views.py .../LevelUpUpgrade.cpp --dry-run` can plan a shared leaf declaration,
but reports `UpgradeModule` and `UpgradeMux` as registered-header work and
will not reconcile their private copies. The seed has canonical BehaviorModule
followed by UpgradeMux/ModuleInterface; the donor uses ObjectModuleBase,
UpgradeModuleInterface and UpgradeMux. Matching a leaf declaration alone does
not reconcile these base chains or the donor's placeholder slot-2 declaration.

Next: adopt/reconcile the registered module bases while preserving +0x10 mux
receiver adjustment and slot-2 identity, verify each donor, then rerun the
supported merge. No source-file reduction or census improvement is claimed.
