# Consolidation shard 1 trial evidence (2026-11-04)

Scope: allocated mechanical consolidation only. For each destination below,
`consolidation_queue.py --check-tu` passed, the narrow `name_lane.py consolidate
--under ...` report passed `--check build/consolidation`, the destination plan
was inspected, and `tu_skeleton.py --merge ... --dry-run` accepted zero donors.
LinkGuard protected census-linked units. No merge, split, source/ledger change,
or claim was applied. Candidate compile repairs and view reconciliation are
outside this seat.

| Destination TU | Rejected donor / exact dry-run obstacle |
| --- | --- |
| `Code/GameEngine/Source/GameLogic/Object/Die/CreateObjectDie.cpp` | `CreateObjectDieModuleDataCtor`: duplicate `ModuleData` / `DieMuxData` class definitions; module-data dtor: byte mismatch; eldest-kind ctor: LinkGuard duplicate module-data dtor and retail COMDATs; corresponding dtor: byte mismatch. Mixed plans included `GapBodiesGE22.cpp` and `DieModuleDerived.cpp`. |
| `Code/GameEngine/Source/Common/T2WideCtype.cpp` | `T2CtypeTableFacets.cpp`: duplicate `_STL::ctype<char>` specializations. |
| `Code/GameEngine/Source/GameLogic/Object/Update/WeaponModeSpecialPowerUpdate.cpp` | `WeaponModeSpecialPowerUpdateCtorThunk.cpp`: `getModuleNameKey` undeclared in class view; class reconciliation required for `WeaponModeSpecialPowerUpdate`. |
| `Code/GameEngine/Source/Common/W3DHordeModelDrawManager.cpp` | Donors rejected for absent `HordeGroupNode::W3DHordeModelDrawModuleData` / `buildFieldParse` / `m_vec1`, target ctor-view mismatch, duplicate STL allocator/vector/tree/string definitions, byte mismatches, or LinkGuard allocator COMDAT loss; 16 class views need reconciliation. |
| `Code/GameEngine/Source/Common/SubsystemLegend.cpp` | Pair destructor duplicates STL allocator/list base; append donor fails allocator deallocate (`C2244` / fatal type mismatch); class reconciliation required for `SubsystemLegend`. |
| `Code/Libraries/Source/WWVegas/WW3D2/rendobj.cpp` | Asset-name and copy donors fail bytes; ctor loses `RefCountClass` scalar deleting destructor and `RenderObjClass` vftable under LinkGuard; intersection donor duplicates `RayCollisionTest` ctor under LinkGuard. |
| `Code/GameEngine/Source/Main/BfmeDfe6e4.cpp` | Watchdog ctor donor conflicts on `InitializeCriticalSection` C linkage and lacks `m_mutexStorage`; dtor lacks `m_mutexStorage`; reconciliation required for `MutexClass`, `Rva0009990D`, `Watchdog`, and `WatchdogCriticalSection`. |
| `Code/GameEngine/Source/GameLogic/System/GameLogicDispatch.cpp` | `GameLogic_clearGameData` has a syntax error before `VS`; update donor duplicates `SubsystemInterface`; existing class view requires reconciliation. |
| `Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObject.cpp` | Only clean donor `GeometryRecordVector.cpp` fails byte verification; mixed-file candidates remain untouched. |
| `Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldEyeTower.cpp` | Xfer donor lacks `BfmePod8`; reconciliation required for `BfmePod8`. |
| `Code/Libraries/Source/Fesl/gamebrowser/gamebrowserdemangler.cpp` | `Rva00800920FeslCtor.cpp` lacks `rva00800a40` and `m_14`; reconciliation required for `Rva00800920Owner` / `Rva7F4CC0Child`. |
| `Code/GameEngine/Source/GameLogic/Object/Update/ThreatFinderUpdate.cpp` | Map-load donor duplicates StringBase STL template; destructor donor fails bytes; reconciliation required for `ThreatFinderUpdate`. |
| `Code/GameEngine/Source/GameLogic/Map/PolygonTrigger.cpp` | Pair donor has undefined `PolygonTrigger` / syntax error; permuted donor has negative subscript and missing member; ctor donor has undefined `PolygonTrigger` / missing `addPolygonTrigger`; class reconciliation required for `Rva002E3A8DHolder`, `Rva002E3A8DPair`, `Rva0030B72CPoint`, and `Rva00330C50`. |

Mixed-file split check for `Code/GameEngine/Source/Common/GapBodiesSeat1B.cpp`
was also inspected. `--split FILE --for
Code/GameEngine/Source/GameLogic/Map/PolygonTrigger.cpp --dry-run` refused:
`an escape-hatch count would grow (hatch_counters rule 3): a copied helper or
datum carries one`. Nothing was applied; do not retry unchanged. The other
`--split FILE` plan showed rows routed to multiple TUs and was not applied.

The next allocated candidate is
`Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/VeterancyCrateCollide.cpp`;
its allocator `--check-tu` exited 0. Start by checking wind-down and generating
that narrower planner report. No matched-row preservation or file reduction is
claimed because no trial was applied. Progress snapshot before this note:
byte match 100%; linking figures unchanged; SOURCE FILES 18,540; TU-APPROVED
51,048 rows / 1,447 of 2,297 TUs.

## Continuation: AIReturnTheRingTactic

The allocation passed for `AIReturnTheRingTactic.cpp`; the current Common
planner passed currency check and the plan listed 21 approved rows, two
donors, and four mixed files. Merge dry run rejected
`AIReturnTheRingTactic_run.cpp` because the class view lacks `run` and `m_owner`;
reconciliation is required for `AIReturnTheRingTactic` and
`Rva005C4AD1LeaField`. Both donors were census-linked. All four mixed files
were inspected and their split dry runs refused:

| Mixed file | Split dry-run result |
| --- | --- |
| `Rva004ECECDTacticCreate.cpp` | Carved `0x005AB41F` matches alone, but destination lacks `findRingBearer` and `m_player`. |
| `Rva004ECECDTacticCtors.cpp` | Carved `0x005AB3BE` matches alone, but destination lacks `findRingBearer` and `m_player`. |
| `Rva005AB309Tactic.cpp` | Eight carved rows match alone, but destination lacks `canRun` and `m_owner`; proposal includes an `aiData` copy and data symbol `g_009BC1B8`, requiring path-keyed identity accounting outside this seat if accepted. |
| `Rva005DCC24Derived.cpp` | No carved row matches under destination flags; rows `0x005AB309` and `0x005AB338` match only under donor flags. |

No source, ledger, or claims changed. The next unheld shard-list candidate is
`Code/GameEngine/Source/GameLogic/AI/GarrisonObjectGroupOrder.cpp`; recheck its
allocation and wind-down before its scoped planner.

## Continuation: GarrisonObjectGroupOrder

Allocation and planner currency passed. Plan: 15 approved rows, five donors,
three mixed files. Merge dry run accepted no donors: both ctor donors trigger
`C2373` vftable redefinition, Xfer lacks the class `xfer` member, and the
`rva00546DD4` donor cannot instantiate abstract `AICommandInterface` and lacks
its method declaration. Reconciliation is required for
`GarrisonObjectGroupOrder`, `GroupOrder`, and `Object`; LinkGuard marked all five
destination/provider units census-linked.

All mixed files were inspected and split dry runs refused:

| Mixed file | Split dry-run result |
| --- | --- |
| `GroupOrderClassNames.cpp` | Two carved rows match alone, but destination lacks `getClassName` and `getClassKey`. |
| `GroupOrderClones.cpp` | Carved `0x00546CB8` matches alone, but destination lacks `rva00546CB8`. |
| `GroupOrderDerivedDtors.cpp` | Carved `0x00546CAD` fails bytes. |

No changes or claims were applied. Next unheld queue candidate:
`Code/GameEngine/Source/GameLogic/Object/Collide/HordeMemberCollide.cpp`;
recheck allocation and wind-down before proceeding.

## Continuation: HordeMemberCollide

Allocation and scoped planner currency passed. Plan: three approved rows, two
donors, one mixed file. Merge dry run accepted no donors: the class view lacks
the constructor used by the OnCollide donor (`C2511`), requiring
`HordeMemberCollide` view reconciliation; both involved units are census-linked.
The listed mixed file `Rva004BB68EDerived.cpp` had no rows approved for this
destination, so its split dry run reported `blocked: no row of that file is
approved for that TU`. Nothing was applied or claimed. Next listing candidate:
`Code/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeployHordeSpecialPower.cpp`.

## Continuation: SiegeDeployHordeSpecialPower

Allocation and planner currency passed. Plan: 17 approved rows, seven donors,
one mixed file. Merge dry run accepted none; the destination itself fails
LinkGuard because the merged object loses selected `DeflectSpecialPowerModuleData`
vftable COMDAT. Other donors fail bytes, ctor declaration, missing method
declarations, or abstract `AICommandInterface` instantiation. Class
reconciliation is required for `Object`, `Rva00589079`,
`SiegeDeployHordeSpecialPower`, and its module data. The mixed
`ConstIntGetters4.cpp` proposal carves `0x004C63D8` with matching bytes, but
LinkGuard refuses moving selected string COMDAT
`??_C@_0BN@KBCIEECP@SiegeDeployHordeSpecialPower?$AA@` without matching
private/weak-free context. Nothing applied. The next shard list candidate is
`Code/GameEngine/Source/GameLogic/Object/Made002CCA37.cpp`.

## Continuation: Made002CCA37

Allocation and plan checks passed (three approved rows, two donors, no mixed
files). Merge dry run accepted none: LinkGuard reports that moving
`Made002CCA37Dot.cpp` would make the census-linked unit lose retail-selected
`??1Made002CCA37@@UAE@XZ`. No changes or claims were applied. Next shard-list
candidate is `Code/GameEngine/Source/GameLogic/Object/Upgrade/LevelUpUpgrade.cpp`.

## Continuation: LevelUpUpgrade

Allocation and scoped planner currency passed. Plan: four approved rows, two
donors, one mixed file. Merge dry run accepted none: the mux-slot donor has an
undefined `UpgradeMux` base (`C2504`) and the target class view lacks members;
`LevelUpUpgrade` view reconciliation is required. Both units are census-linked.
The mixed `FireWeaponWhenDeadBehaviorDerived.cpp` file had no approved rows for
this TU, so split dry run refused with `blocked: no row of that file is approved
for that TU`. Nothing applied. Next listing candidate:
`Code/GameEngine/Source/GameLogic/Object/Upgrade/TooltipUpgrade.cpp`.

## Rejected split trial: TooltipUpgrade

`TooltipUpgrade.cpp` passed the allocation check and current scoped consolidation
planner. Its merge dry run accepted no donors because of class-view prerequisites.
The mixed `ModuleDataBuildFieldParseChained.cpp` split dry run accepted exactly
row `0x004B7A2E` and its owned data at `0x00C58C38`; LinkGuard judged the split
residual and destination together. Tool application preserved the rows and
repointed `functions.csv`, `data_rows.csv`, `data_ledger.csv`, and `tu_map.csv`,
and updated `docs/doxygen/sources.cfg`.

Trial verification: `./build.sh TooltipUpgrade.cpp` passed 3/3 rows;
`./build.sh ModuleDataBuildFieldParseChained.cpp` passed 46/46 rows;
`find_declared_unmatched.py` found all definitions already matched;
`check_csv.py` passed; `data_check.py --converged` checked 11 addresses with no
second names or unjudged rows; staged code identity checked 49 rows with zero
new findings; staged data check reported zero findings. The ownership shadow
scan reports B1 for a private `DelayedDeathBodyModuleData` view in
`TooltipUpgrade.cpp`; it is outside the moved row and needs class/view owner
reconciliation by another contributor. The commit hook rejected this copy:
"`TooltipUpgrade.cpp`: declares its own `DelayedDeathBodyModuleData`; include
Code/GameEngine/Include/GameLogic/Module/DelayedDeathBodyModuleData.h instead
(or `// class-gate: allow DelayedDeathBodyModuleData <reason>` for a proved
codegen view)". This seat cannot repair class views, so the trial source and
ledger changes were restored and all four claims released. No split landed and
no identity debt was retired. The two source paths were searched in active
tools, hooks, workflows and include directives; no active path consumer was
found. The remaining provenance comments retain original-path history.
LinkGuard found no lost selected provider/COMDAT in the dry run. Another
contributor must resolve the shared-header class view before retrying.

## Continuation: DeletionUpdate

Allocation and scoped planner checks passed (12 approved rows, four donors,
two mixed files). Merge dry run accepted no donors: all three donor compiles
reported duplicate class definitions (`GameLogic`, `SubsystemInterface`,
`Xfer`/`Module`, and related views). The destination and donor units are
census-linked. `ModuleNameGetters3.cpp` split dry run carved only `0x00488351`
and that row matched alone, but the destination compile failed with duplicate
`DeletionUpdate` class definition; LinkGuard compared residual and destination
together. `Rva0024A797Derived.cpp` had no row approved for this TU. No changes
or claims were applied. Class/view reconciliation is outside this seat.

## Continuation: CommandPointsUpgrade

Allocation and scoped planner checks passed (10 approved rows, three donors,
one mixed file). Merge dry run accepted no donors: the ctor donor lacks the
`CommandPointsUpgrade` constructor declaration (`C2511`), while the mux-slot
donor lacks its `getModuleNameKey` member (`C2509`); both require class-view
reconciliation for `CommandPointsUpgrade` and `CommandPointsUpgradeModuleData`.
The mixed `FireWeaponWhenDeadBehaviorDerived.cpp` split carved destructor
`0x004B85D4` and both carved rows matched alone, but the destination compile
failed on duplicate `AsciiString` class declarations. LinkGuard compared both
split sides. No changes or claims were applied.
