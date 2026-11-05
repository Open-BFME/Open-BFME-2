### LINK-186: `ElvenWoodSpecialPower.cpp` cannot adopt the canonical `SpecialPowerModuleData.h`: its module-data vftables must agree with the one-slot `EmitVtableTag` copies

Status: Open. Updated: 2026-11-03; inspected revision: c1d6ceeedb.
Evidence / affected units: the census-linked seed `ElvenWoodSpecialPower.cpp` (4,178 B) keeps a
private one-slot `SpecialPowerModuleData` view. Including `Include/GameLogic/Module/SpecialPowerModuleData.h`
instead keeps all 63 rows matched, but the header gives the base `ModuleData`'s virtual slots, so
the seed's `??_7WeaponChangeSpecialPowerModuleData@@6B@` and `??_7ElvenWoodSpecialPowerModuleData@@6B@`
differ from the first copy in link order (`link_check`: "first: differs from the first copy in link
order (no retail address)", LINKED 4,178 -> 0). Landed as f1e093490e and reverted in c1d6ceeedb.
The other emitters are `SpecialPowerModuleDeletingDtors.cpp` (one-slot `EmitVtableTag` views of 14
module-data classes) and the census object of the deleted `ScavengerSpecialPowerModuleDataCtor.cpp`.
The same collision blocks the `tu_skeleton.py --merge` of this TU: the CloudBreak, ElvenWood and Taint
module-data dtor donors include the canonical header (C2011 against the seed's view).
Remaining / next check: give every emitter of these vftables the canonical header's slot layout in
one batch (start with `SpecialPowerModuleDeletingDtors.cpp`), confirm with `link_check` that each
unit still links, then adopt the header in the seed and re-run the merge dry run.
Clearance: pending.

2026-11-05 prerequisite: WeaponChangeSpecialPowerModuleDataDtor now uses the canonical base (4/4 byte rows, EH EXACT, preview 84 -> 84; header queue accepted); seed/emitter reconciliation remains next. [Evidence](../../reverse/attempt_support/elvenwood-moduledata-header-20261105.md).
