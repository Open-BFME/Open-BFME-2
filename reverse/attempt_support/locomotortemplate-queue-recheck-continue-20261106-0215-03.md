# Retire 2 verified LocomotorTemplate header queue entries

Base: `61cfd2a1ee35f819772c359efb79107f137e818c`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 8 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/AI/AIWanderInPlaceStateUpdate.cpp` | `Code/GameEngine/Include/GameLogic/LocomotorTemplate.h` | 2 |
| `Code/GameEngine/Source/GameLogic/AI/AIWanderStateMethods.cpp` | `Code/GameEngine/Include/GameLogic/LocomotorTemplate.h` | 6 |
