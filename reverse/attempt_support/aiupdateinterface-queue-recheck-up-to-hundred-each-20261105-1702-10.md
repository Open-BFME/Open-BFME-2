# Retire 8 verified AIUpdateInterface header queue entries

Base: `2d2c304b0907d81e564acb579dddd22148ab7149`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 138 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleRva0049466D.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 11 |
| `Code/GameEngine/Source/GameLogic/AI/AIGroupAttackTeam.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 15 |
| `Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateRun.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 14 |
| `Code/GameEngine/Source/GameLogic/AI/MoveToGroupOrder.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 8 |
| `Code/GameEngine/Source/GameLogic/AI/AIGuardRetaliateStates.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 10 |
| `Code/GameEngine/Source/Common/System/BuildAssistantWallLocations.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 5 |
| `Code/GameEngine/Source/GameLogic/AI/AIPlayerTeamBuild_QueueUnits.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateTeamStateIs.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 74 |

This scope replaces entries excluded from the preceding task count
during the upstream reconciliation.
