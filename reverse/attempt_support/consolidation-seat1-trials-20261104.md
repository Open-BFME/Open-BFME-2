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
