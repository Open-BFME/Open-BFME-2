# Retire 5 verified AIUpdateInterface header queue entries

Base: `47fd56b87931070902fe1c96e0f4e581e87d311f`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 22 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/Rva003C7AF3Do.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Update/StrafeAreaUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 5 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/DefaultProductionExitUpdateXfer.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 4 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SupplyCenterProductionExitUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 7 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateExitObjectViaDoor.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 5 |
