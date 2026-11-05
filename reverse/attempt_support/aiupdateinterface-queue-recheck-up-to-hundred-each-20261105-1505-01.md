# Retire 20 verified AIUpdateInterface header queue entries

Base: `8e90760e14e8c5fdd51222145475a0df0c56e858`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 60 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_computeQuickPath.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 3 |
| `Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdateMoveToNewRepairSpot.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/Rva003C8B62Do.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 3 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsTransferTeam.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamFaceWaypoint.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 2 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_Rva003C9E4E.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doAttackMoveTeamTowardsNearest.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 8 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_Rva003C9D0D.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 5 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/HorseHordeContainRva00476D77.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/ObjectRva00295FA9.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 2 |
| `Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderRva002E9EA7.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitGarrisonNearestBuilding.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 5 |
| `Code/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateOnExit_AIInternalMoveToState.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doMoveTeamTowardsNearest.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 6 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitGuardForFramecount.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 4 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/SlaughterHordeContainUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 4 |
| `Code/GameEngine/Source/Common/Rva0044E6AEVirtForward.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 3 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/RunOffMapBehaviorSlot5.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 2 |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/RepairSpecialPower.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 6 |
| `Code/GameEngine/Source/GameLogic/AI/PathfinderCheckForMovement.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
