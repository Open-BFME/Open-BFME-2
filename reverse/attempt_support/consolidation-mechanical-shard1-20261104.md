# Shard 1 mechanical consolidation blockers (2026-11-04)

Inspected base: `293fbba275`. Each listed target passed its current allocation
check, parent-scoped consolidation planner check, and `tu_skeleton.py --plan`.
The guarded merge dry runs accepted no donors. No claims or source/ledger edits
were made, and none of these trials was applied. LinkGuard reported the target
and relevant donors census-linked where noted by its output.

| Target | Rejected donor / exact blocker | Required work outside this seat |
|---|---|---|
| `GameLogic/Object/Collide/HordeMemberCollide.cpp` | `HordeMemberCollideOnCollide.cpp`: C2511, constructor overload not declared in `HordeMemberCollide`. | Reconcile the class declaration; the merge planner recommends `tu_views.py`. |
| `GameLogic/Object/SpecialPower/SiegeDeployHordeSpecialPower.cpp` | Constructor donor C2511; RVA004C63DE donor C2039 (`Rva004C63DE` missing); dtor C2600 (compiler-generated special member); Xfer C2039 (`xfer` missing); update C2039 (`update` missing); initiate C2509 (`getModuleNameKey` missing). | Reconcile `SiegeDeployHordeSpecialPower` and module-data declarations. The prior obstacle entry also documents the remaining interface prerequisites. |
| `GameLogic/Object/Made002CCA37.cpp` | `Made002CCA37Dot.cpp`: C2504 (`DamageNugget` base undefined) and C3861 (`generateDamageInfo` missing). | Reconcile the `DamageNugget` and `Made002CCA37` views. |
| `GameLogic/Object/Update/AutoFindHealingUpdate.cpp` | `AutoFindHealingUpdateCtor.cpp`: C2511, constructor overload not declared; planner recommends `UpdateModule`. | Reconcile the class/base declaration. |
| `GameLogic/Object/Behavior/CommandPointsUpgrade.cpp` | C2511 constructor overload not declared and C2509 `getModuleNameKey` not declared in `CommandPointsUpgrade`. | Reconcile class/module-data views and `UpgradeModule`/`Player` prerequisites. |
| `GameLogic/Object/Update/DeletionUpdate.cpp` | Donors failed with C2011 duplicate `GameLogic`, `SubsystemInterface`, `Xfer`, and `Module` declarations. | Reconcile private/shared header views before retrying. |
| `GameLogic/Object/Behavior/SupplyWarehouseCripplingBehavior.cpp` | `SupplyWarehouseCripplingBehaviorCtor.cpp`: C2511, constructor overload not declared. | Reconcile the class declaration and `UpdateModule` base. |
| `GameLogic/Object/Upgrade/TooltipUpgrade.cpp` | Pool-key donor C2509 (`getModuleNameKey` missing); removal donor C2504 (`UpgradeModule` undefined), plus duplicate `Drawable` declaration. | Reconcile the class/base views. |
| `GameLogic/Object/Body/StructureBody.cpp` | `StructureBodyCtor.cpp` failed bytes; LinkGuard rejected the seed composition because it would introduce duplicate selected symbol `?rva004C09A1@Rva004C09A1@@QAEXPBURva004C09A1Object@@@Z`. The same spelling also has an unrowed definition in `Common/GapBodiesGE24.cpp`. | Resolve provider ownership of the duplicate before another merge trial; retain the LinkGuard refusal. |

The dry-run outputs were observed directly during this session. They are
diagnostic only: no TU merge, source-file reduction, or linking gain is claimed.

## Additional allocated probes

These fresh destinations passed allocation, scoped planner currency and plan
checks. The guarded merge dry runs accepted no donor; no source or ledger
changes were applied and no claims were taken.

| Target | Rejected donor / exact blocker | Required work outside this seat |
|---|---|---|
| `GameLogic/Object/WeaponSet.cpp` | All 13 proposed donors were rejected on compile prerequisites: duplicate `AsciiString`, incompatible enum assignment, duplicate/private `Weapon` and `WeaponSet` declarations, absent members, `BitFlags` template mismatch, duplicate placement `operator new`, and undeclared `EmitVtableTag` constructor. LinkGuard listed the affected units census-linked. | Reconcile class and header views before retrying; preserve the rejected donors. |
| `Common/OathbreakersFadeAwayBehavior.cpp` | Constructor donor C2511; update donor lacks `getModuleNameKey`. | Reconcile private class and AI interface views. |
| `Libraries/Source/debug/debug_io_con.cpp` | LinkGuard refused ctor/dtor donors: selected `DebugIOInterface` deleting-dtor COMDAT changes and another unit's `DebugIOCon` vtable breaks. | Resolve provider/consumer COMDAT ownership before retrying; existing LINK-137 handoff covers this blocker. |
| `GameLogic/System/AiOrdersManager.cpp` | Patrol donor C2460 self-referential `Rva0054840A::ObjectID` and C2065 `ObjectID`. | Reconcile `GroupOrder` / `Rva00355B61` views. |
| `Main/BfmeDfe6e4.cpp` | Watchdog donor C2733 duplicate C-linkage `InitializeCriticalSection`; C2065 missing `m_mutexStorage`. | Reconcile class and private storage views. |
| `GameEngineDevice/.../GUI/AptAnimData.cpp` | `AptAnimDataRenderData.cpp` C2065 `map` undeclared; related `.findSlot` view is also absent. | Reconcile the AptAnimData view. |
| `GameLogic/Object/Update/ModelConditionSpecialAbilityUpdate.cpp` | Module-data-dtor donor rejected on byte verification; both units census-linked. | Resolve the byte mismatch in the owning source lane before retrying. |
| `Libraries/Source/Fesl/gamebrowser/gamebrowserdemangler.cpp` | `Rva00800920FeslCtor.cpp` lacks `rva00800a40` and `m_14` members on `Rva00800920Owner`; planner calls for class-view reconciliation. | Reconcile `Rva00800920Owner` and `Rva7F4CC0Child` views. |
| `GameLogic/Object/SpecialPower/DeflectSpecialPower.cpp` | The seed composition itself fails LinkGuard: the census-linked target would leave unresolved `??1DeflectSpecialPowerModuleData@@UAE@XZ`. | Resolve the module-data dtor provider before retrying; existing DeflectSpecialPower obstacle entries record related identity/interface prerequisites. |
| `GameClient/Drawable/Update/SwayClientUpdate.cpp` | Constructor donor C2511, constructor overload undeclared in `SwayClientUpdate`. | Reconcile the class view. |
| `GameLogic/Object/ObjectTypes.cpp` | `ObjectTypesCtor.cpp` C2600 compiler-generated constructor is undeclared. | Reconcile the class view; the existing ObjectTypes obstacle covers its next-census prerequisite. |

Mixed-source split inspection was also completed for the relevant allocated
plans. `BfmeConv1324.cpp` lists the gamebrowser destination row; its `--split
... --for gamebrowserdemangler.cpp --dry-run` preserved the row beside the TU
but rejected the residual on C2146/C2501 (`BfmeThingTVB` view), with the
two-object LinkGuard check. `Rva00809E40FeslAdmission.cpp` lists that same
destination; its split dry run rejected the move because selected private
string COMDATs lacked matching private/weak-free context. `ConstIntGetters4.cpp`
was inspected for allocated `DeflectSpecialPower.cpp` and `SwayClientUpdate.cpp`
destinations: the split dry runs preserved each getter beside its TU but
rejected compilation (missing `Object::m_conditionBits` for Deflect and
duplicate `Module` / absent `ObjectModule::xfer` for Sway). No split was
applied. These are tool refusals, not evidence of a safe move.
