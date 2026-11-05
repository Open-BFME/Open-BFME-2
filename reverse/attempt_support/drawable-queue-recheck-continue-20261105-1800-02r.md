# Retire 5 verified Drawable header queue entries

Base: `7e9627eb472422b6613a412eb06ed7dc9d029b44`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 337 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/Upgrade/ReplaceSelfUpgrade.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 14 |
| `Code/GameEngine/Source/Common/GapBodiesSeat1A.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 136 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/TransportContain.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 34 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 42 |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 111 |
