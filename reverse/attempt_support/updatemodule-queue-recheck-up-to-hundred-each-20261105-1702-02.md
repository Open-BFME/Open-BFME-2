# Retire 17 verified UpdateModule header queue entries

Base: `7f025c9cceab516a0813d725003a17095e86ab72`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 188 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WanderAIUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 12 |
| `Code/GameEngine/Source/GameLogic/Object/Update/WoundArrowUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 8 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/OpenContainXfer.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 4 |
| `Code/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 13 |
| `Code/GameEngine/Source/GameLogic/Object/Update/BroadcastStealthUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 14 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/AimWeaponBehavior.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 12 |
| `Code/GameEngine/Source/GameLogic/Object/Update/WeaponModeSpecialPowerUpdateBase.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 11 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SupplyCenterProductionExitUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 7 |
| `Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdateConstructor.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Update/DetachableRiderUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 10 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/AutoAbilityBehavior.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 19 |
| `Code/GameEngine/Source/GameLogic/Object/Update/WeaponModeSpecialPowerUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 8 |
| `Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyCenterDockUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 10 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateExitObjectViaDoor.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 5 |
| `Code/GameEngine/Source/GameLogic/Object/Update/CommandButtonHuntUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 22 |
| `Code/GameEngine/Source/GameLogic/Object/Update/BloodthirstyUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 14 |
| `Code/GameEngine/Source/GameLogic/Object/Update/RadiateFearUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 18 |
