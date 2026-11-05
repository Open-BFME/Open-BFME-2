# Retire 2 verified UpgradeCenter header queue entries

Base: `77f55d6ea2e15caaf2a88f3407d4ca0b8c8b6740`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 126 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp` | `Code/GameEngine/Include/Common/Upgrade.h` | 52 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateTeamStateIs.cpp` | `Code/GameEngine/Include/Common/Upgrade.h` | 74 |
