# Retire 20 verified AIUpdateInterface header queue entries

Base: `7ee53b4481251c5cc7207650df6ca49bc66e22dd`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 43 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/Object_teleportTo.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/AI/AIMoveAndDeleteStateUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/Rva003C8A15Do.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedFollowWaypoints.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/Libraries/Source/WWVegas/WWLib/Rva00586D8EVSlots.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 5 |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIUpdateInterfaceIgnoreObstacle.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/ObjectGuardingHelperDisband.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedFaceWaypoint.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/AutoAbilityBehaviorTargetPredicate.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_Rva003C7A30Do.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/UnleashSpecialPowerSlot17.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 3 |
| `Code/GameEngine/Source/GameLogic/AI/AIGroupScatter.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/AutoAbilityBehaviorRva0045A447.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/ObjectRva00295A84.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedFireWeaponFollowingWaypointPath.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/AI/AIMoveToStateOnEnter.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceHandleEngagedFlag.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doMoveUnitTowardsNearest.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 6 |
| `Code/GameEngine/Source/Common/GapBodiesGE16.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 7 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_Rva003C951B.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 7 |
