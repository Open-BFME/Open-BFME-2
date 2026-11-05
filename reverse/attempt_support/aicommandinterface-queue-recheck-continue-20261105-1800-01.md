# Retire 7 verified AICommandInterface header queue entries

Base: `babe36570dde18d174497cf49b6594fa5bfa53fd`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 95 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/ObjectDefect.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 4 |
| `Code/GameEngine/Source/GameLogic/Object/FellBeastSwoopPower.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 13 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ToggleHiddenSpecialAbilityUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 11 |
| `Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateRun.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 14 |
| `Code/GameEngine/Source/GameLogic/AI/AIStatesDerivedOnExit_ComputeGoal_ComputeGoal_Update.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/Common/System/BuildAssistantWallLocations.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 5 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_garrison.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 47 |
