# Retire 5 verified Player header queue entries

Base: `a2e60c2b5c5a358ac55a6cafec78fb95f8083f59`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 146 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/CommandPointsUpgrade.cpp` | `Code/GameEngine/Include/Common/Player.h` | 8 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ThreatFinderUpdate.cpp` | `Code/GameEngine/Include/Common/Player.h` | 20 |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateConstruction.cpp` | `Code/GameEngine/Include/Common/Player.h` | 19 |
| `Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderRva002F83F5Neighbors.cpp` | `Code/GameEngine/Include/Common/Player.h` | 1 |
| `Code/GameEngine/Source/GameClient/GameClientDrawableTOC.cpp` | `Code/GameEngine/Include/Common/Player.h` | 98 |
