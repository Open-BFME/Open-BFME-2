# Retire 3 verified FireLogicSystem header queue entries

Base: `ec3f5522afcea7ed1c991d489a1214606618c1a6`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 174 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptGlueRva003BD3CB.cpp` | `Code/GameEngine/Include/GameLogic/FireLogicSystem.h` | 1 |
| `Code/GameEngine/Source/GameLogic/System/CastleBehaviorRegisterOwnedObject.cpp` | `Code/GameEngine/Include/GameLogic/FireLogicSystem.h` | 24 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp` | `Code/GameEngine/Include/GameLogic/FireLogicSystem.h` | 149 |
