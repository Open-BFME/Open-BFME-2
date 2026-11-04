# Consolidation shard 0 follow-up (2026-11-04)

Scope: mechanical BFME 2 consolidation only. The inherited handoff at
`reverse/attempt_support/consolidation-shard0-20261104.md` records the earlier
six candidates. This follow-up records subsequent allocated TU trials. No source,
ledger, map, or claim was changed by these dry runs.

For each target, `consolidation_queue.py --check-tu` passed, the supported
`name_lane.py consolidate --under <target parent>` report was generated and
passed `--check`, then `tu_skeleton.py --plan` and
`tu_skeleton.py --merge <TU> --dry-run` were run. No trial accepted a donor;
therefore no normal merge, TU build, path-consumer audit, or publication of code
was applicable.

| TU | Dry-run result |
| --- | --- |
| `Code/GameEngine/Source/GameLogic/Object/Update/DelayedDeathBody.cpp` | Blocked: census-linked TU absent from census index; LinkGuard could not judge. |
| `Code/GameEngine/Source/GameLogic/Object/Upgrade/DelayedUpgrade.cpp` | No accepted donor; `DelayedUpgradeImplementation.cpp` fails because `upgradeImplementation`/member declarations are absent from the class view. |
| `Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate.cpp` | No accepted donor; conflicting subsystem/module definitions, missing `Object::rva00293077`, ctor/template errors, and one donor byte failure. |
| `Code/GameEngine/Source/GameLogic/Object/Create/SpecialPowerCreate.cpp` | Constructor donor rejected: matching `SpecialPowerCreate(Thing *, ModuleData const *)` declaration absent. |
| `Code/GameEngine/Source/GameLogic/Object/Create/SupplyWarehouseCreate.cpp` | Pool-key donor rejected on duplicate `SubsystemInterface` definition. |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehavior.cpp` | Donors rejected on duplicate `SubsystemInterface`/`Xfer`/`GameLogic` declarations and incompatible class views. |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DGameClient.cpp` | No accepted donor; the seed fails under merged flags at reference `cpudetect.h(171)` (`Get_Processor_Ticks_Per_Second`), and other donors lack member declarations. |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDraw.cpp` | No accepted donor; missing `DrawModule`/class members, duplicate vtable definitions, and type errors. |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/DevastateSpecialPower.cpp` | No accepted donor; required `DevastateSpecialPower` methods are undeclared; module-data dtor fails bytes. |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/ModelConditionAudioLoopClientBehavior.cpp` | No accepted donor; ctor/slot/dtor declarations missing from class view. |
| `Code/GameEngine/Source/GameLogic/Object/Body/OathbreakerBody.cpp` | Blocked: census-linked TU absent from census index; LinkGuard could not judge. |
| `Code/GameEngine/Source/GameLogic/Object/Update/ToggleDeploySpecialAbilityUpdate.cpp` | LinkGuard rejected the merge: it would lose `rva0044EDA6` and leave `vslot08@SpecialAbilityUpdate` unresolved; other donors also fail declaration checks. |
| `Code/Libraries/Source/Fesl/ariesudp.cpp` | `Rva00661650AriesUdp.cpp` donor rejected byte verification. |
| `Code/GameEngine/Source/Common/MessageStream.cpp` | No accepted donor; duplicate `GameMessage`/subsystem/coordinate definitions, translator pointer mismatch, and one byte failure. |
| `Code/GameEngine/Source/GameLogic/Object/Made002CCC90.cpp` | Finish donor rejected: constructor is compiler-generated but not declared in the class. |
| `Code/Libraries/Source/WWVegas/WW3D2/matpass.cpp` | No accepted donor; two lose rows under carried flags, two lack baseline matches, one compile error (`m_28`/`m_2c`), and class-view prerequisites remain. |
| `Code/GameEngine/Source/GameLogic/AI/GroupOrder.cpp` | No accepted donor; duplicate vtable and compiler-generated special-member definitions. |
| `Code/GameEngine/Source/GameClient/Snow.cpp` | No accepted donor; duplicate subsystem declarations and missing `WeatherSetting` members/constructors. |
| `Code/GameEngine/Source/Common/Command.cpp` | Add-upgradable-command-points donor rejected due duplicate `_STL::allocator` and `_STL::vector` definitions. |
| `Code/GameEngine/Source/Common/BfmeOwnVVD.cpp` | Translate-game-message donor rejected: `TheGameClient` type is unavailable in the combined TU. |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/TerrainResourceBehavior.cpp` | Module-data dtor donor rejected byte verification. |
| `Code/GameEngine/Source/Common/MemoryReadFile.cpp` | Current plan reports 0 approved rows, so dry run blocks with fewer than two donors; no compile trial. |

Remaining work for these candidates is prerequisite repair by other lanes
(class/header/signature/include reconciliation, byte repair, or census index
availability). Do not repeat unchanged dry runs before those inputs change.

Additional full-allocation trials after the first handoff commit:

| TU | Dry-run result |
| --- | --- |
| `Code/Libraries/Source/WWVegas/WWMath/wwmath.cpp` | `Code/Libraries/Source/WWVegas/WWLib/wwmath.cpp` donor rejected byte verification. |
| `Code/GameEngine/Source/GameLogic/Object/Upgrade/GeometryUpgrade.cpp` | No accepted donor; duplicate `BehaviorModuleInterface`, `BehaviorModule`, and `Rva001EAE6FHelper` declarations plus compiler-generated member definitions. |
