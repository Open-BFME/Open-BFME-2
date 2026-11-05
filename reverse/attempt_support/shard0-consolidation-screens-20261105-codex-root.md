# Shard 0/5 mechanical consolidation screens (2026-11-05, root seat)

For each fresh TU below, the allocator check passed, the planner was refreshed under the TU's parent, the snapshot check passed, and `tu_skeleton.py --merge TU --dry-run` accepted no donors. No merge was applied, no claims were taken, and no source or ledger files changed. LinkGuard reported the tested seed/donor units census-linked unless noted. The merged compositions were never built; these are dry-run blockers for manual source/header owners.

- `Common/LivingWorldBuildingNuggetSpawnArmy.cpp`: `Rva004FA659Method.cpp` uses a method missing from the destination class view (C2039). `GapBodiesGE26.cpp` split trial carved 0x004FA644 but does not address the compile blocker; `XferScienceTypeVector.cpp` split carved no row. No split applied.
- `GameLogic/Object/DamageNugget.cpp`: C2600 compiler-generated constructor, absent `DamageNugget`/`Object` members and protected `findModule` in three donors. No accepted donors.
- `GameLogic/System/GlobalWeatherSystem.cpp`: constructor donor has duplicate `SubsystemInterface` and list definitions (C2011).
- `GameLogic/Object/SpecialPower/GrabPassengerSpecialPower.cpp`: missing `SpecialPowerModule` base and constructor overload (C2504/C2511).
- `Libraries/Source/Apt/AptDate.cpp`: `AptDateLookup.cpp` refers to absent `objectMemberLookup` and applies member modifiers to a nonmember (C2039/C2270).
- `GameLogic/Object/Behavior/StancesBehavior.cpp`: ctor donor redefines the vftable (C2373).
- `Libraries/Source/WWVegas/WW3D2/streak.cpp`: destructor donor has an explicit specialization after instantiation (C2908).
- `GameLogic/Object/Update/BoneFXUpdate.cpp`: duplicate `Coord3D`, damage flag helper, and `GameClientRandomVariable` definitions across donors.
- `GameLogic/Object/Behavior/FireWeaponWhenDeadBehavior.cpp`: OnDie donor has syntax errors; class view lacks declarations.
- `GameLogic/Object/Upgrade/CostModifierUpgrade.cpp`: module-data destructor donor references absent `bytes`.
- `Common/ClearanceTestingSlowDeathBehavior.cpp`: undeclared compiler-generated special member (C2600), duplicate array new/delete, and thunk byte mismatch.
- `GameLogic/Object/Update/ToggleHiddenSpecialAbilityUpdate.cpp`: constructor overload absent from class view (C2511).
- `Common/TaintManagerImpl.cpp`: undeclared compiler-generated `BfmeTaintManager` special member (C2600).
- `GameLogic/Object/Update/TemporarilyDefectUpdate.cpp`: donor refers to absent `m_p0C` and `m_p10` fields.
- `GameLogic/Object/Update/ModelConditionSoundSelectorClientBehavior.cpp`: two donors have empty compile diagnostics; no donor accepted.
- `GameLogic/Object/Die/RebuildHoleExposeDie.cpp`: deleting-dtor donor requests undeclared `EmitVtableTag*` constructor (C2511); module-data dtor fails byte verification.
- `Libraries/Source/WWVegas/WW3D2/matpass.cpp`: two donors lose rows under carried flags, two have no baseline match, and ctor has duplicate `RefCountClass` definitions. Existing LINK-439 records this prerequisite.
- `GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DAptComponentColorPicker.cpp`: LinkGuard refuses the two donors because the merged object would lose the census-required W3DAptComponentColorPicker constructor/destructor and Rva0074104C providers.
- `Common/MessageStream.cpp`: donors have duplicate `GameMessage`, `SubsystemInterface`, and coordinate definitions; propagation fails on incompatible translator-pointer types; command-name donor fails bytes. No mixed-file split can repair these other donor prerequisites.

Existing allocated blockers were skipped when their obstacle entry already records an unchanged prerequisite (including AITNGuard held donor/RVA claims, XferMD5CRC selected-provider issue, SpellRechargeModifierUpgrade, ProcessAnimateWindow, BuildingBehavior, InheritUpgradeCreate and W3DMouse). This seat did not change their state. Screened and previously documented shard candidates retain their evidence in the existing support files linked from LINK-252. No split was applied: the observed accepted split at SpawnArmy would not unblock its failing method donor, and the MessageStream compile blockers span unmixed donors.

This pass found no mechanically accepted merge, so net source files removed and matched rows preserved by applied merges are both zero. No census, build, link cycle, smoke test, or identity-debt retirement was performed.
