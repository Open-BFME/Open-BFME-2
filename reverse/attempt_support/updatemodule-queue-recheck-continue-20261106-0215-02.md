# Retire 3 verified UpdateModule header queue entries

Base: `f2bc89b3658ad47c5969f5d6c6c836209122175f`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 50 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/Update/EmotionTrackerUpdateCtor.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 5 |
| `Code/GameEngine/Source/GameLogic/Object/Update/LargeGroupBonusUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 23 |
| `Code/GameEngine/Source/GameLogic/Object/Update/FireWeaponUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 22 |
