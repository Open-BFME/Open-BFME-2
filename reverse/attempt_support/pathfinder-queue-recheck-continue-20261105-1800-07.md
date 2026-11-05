# Retire 3 verified Pathfinder header queue entries

Base: `3b2d65d3651486ae750275cf61bac60d2534014e`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 50 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameClient/DrawableDoXfer.cpp` | `Code/GameEngine/Include/GameLogic/AIPathfind.h` | 17 |
| `Code/GameEngine/Source/GameLogic/Object/GenericObjectCreationNuggetReallyCreate.cpp` | `Code/GameEngine/Include/GameLogic/AIPathfind.h` | 11 |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/OCLSpecialPower.cpp` | `Code/GameEngine/Include/GameLogic/AIPathfind.h` | 22 |
