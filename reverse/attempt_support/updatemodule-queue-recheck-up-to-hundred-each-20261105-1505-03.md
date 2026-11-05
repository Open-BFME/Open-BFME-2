# Retire 19 verified UpdateModule header queue entries

Base: `eb678001cc1ccca29b1f9378dfa65cb9152df301`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 116 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/Contain/OpenContainDtorRva00464692.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 8 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/GateOpenAndCloseBehaviorSlots.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 9 |
| `Code/GameEngine/Source/GameLogic/Object/Update/FloatUpdateUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 2 |
| `Code/GameEngine/Source/GameLogic/Object/Update/DelayedWeaponSetUpgradeUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 8 |
| `Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdateXfer.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProneUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 10 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/GateOpenAndCloseBehaviorCtorShard.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 3 |
| `Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdateXfer.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateXfer.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 3 |
| `Code/GameEngine/Source/GameLogic/Object/Update/MonitorConditionUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 12 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/OpenContainCtor.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 6 |
| `Code/GameEngine/Source/GameLogic/Object/Update/StrafeAreaUpdate_update.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 1 |
| `Code/GameEngine/Source/GameClient/ResourceOwnedEntryList.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdateCtor.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 18 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/DefaultProductionExitUpdateXfer.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 4 |
| `Code/GameEngine/Source/GameLogic/Object/Update/DamageFieldUpdateRva004911AE.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 11 |
| `Code/GameEngine/Source/GameLogic/Object/Update/PhysicsBehaviorTrajectory.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 3 |
| `Code/GameEngine/Source/GameLogic/Object/Update/CritterEmitterUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 14 |
| `Code/GameEngine/Source/GameLogic/Object/Update/RadarUpdateConstructor.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 1 |
