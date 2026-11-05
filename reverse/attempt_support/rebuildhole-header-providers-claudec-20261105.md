# RebuildHoleBehavior canonical header: native providers (claudec, 2026-11-05)

Base: 8e4a7fa9d5. Census for previews: 2026-11-05 05:17 at c95fcfcfcd.

Target facts used (retail tables, see `RebuildHoleBehaviorClass.h`):
- primary table 0x00C49A74 slot 1 = 0x00497805 (ICF `jmp UpdateModule::loadPostProcess` 0x0058B03E);
- slot 2 = 0x0048331C (returns the class literal 0x00BF5880);
- die table 0x00C49A64 slot 0 = 0x004835FB (this = +0x20; clears the worker ID at interface+8).

Changes:
- 0x0048331C: placeholder `?name@RebuildHoleBehavior@@QBEPBDXZ` (ModuleNameGetters.cpp) becomes
  `?GetSnapshotName@RebuildHoleBehavior@@MBEPBDXZ` in its approved TU RebuildHoleBehavior.cpp.
- 0x004835FB: placeholder `?rva004835FB@Rva004835FB@@QAEXH@Z` (VslotSmallBodiesW.cpp) becomes
  `?onDie@RebuildHoleBehavior@@UAEXPBVDamageInfo@@@Z` in its approved TU RebuildHoleBehavior.cpp.
- 0x00497805: ICF alias row `?loadPostProcess@RebuildHoleBehavior@@MAEXXZ` in RebuildHoleBehaviorDtor.cpp,
  `fold-proof=Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate.cpp` (same shape as
  BoneFXDamage's alias at that address). tu_ownership reports A1 for it in shadow mode.
- RebuildHoleBehavior.cpp: private interface/UpdateModule/class views replaced by the canonical header;
  the constructor 0x00483271 is plain member initialization (no `__identifier` vptr stores) and
  byte-matches; `update()` unchanged.
- RebuildHoleBehaviorDtor.cpp: canonical header; the four `/alternatename` hatches removed. Their
  source names were referenced only by Dtor.obj's own old private vtables (census index `touches`).

Verification:
- `./build.sh` RebuildHoleBehavior.cpp, RebuildHoleBehaviorDtor.cpp, ModuleNameGetters.cpp,
  VslotSmallBodiesW.cpp: all functions matched; string/float/import checks OK.
- link_check preview (all four): 4 of 4 LINK; RebuildHoleBehavior.cpp 1,213 -> 1,259,
  RebuildHoleBehaviorDtor.cpp 227 -> 232, ModuleNameGetters.cpp 300 -> 300 (before moving the getter out),
  VslotSmallBodiesW.cpp 644 -> 598 (its 46 bytes moved to RebuildHoleBehavior.cpp).
- Definitions lost versus the census objects: `?getDie@BehaviorModule@@...` from Dtor.obj (160 other COMDAT
  definers) and the two placeholder names (no users).
- `header_adopt_lane.py accept`: RebuildHoleBehavior x2, UpdateModule and UpdateModuleInterface rows for
  RebuildHoleBehavior.cpp retired (cohort with RebuildHoleBehaviorDtor.cpp).
