# Retire 14 verified Player header queue entries

Base: `deaa7e75680fef233f3a22172c9daadd1deff6cb`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 555 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameClient/DrawableShroud.cpp` | `Code/GameEngine/Include/Common/Player.h` | 5 |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/OldSchoolHelpBoxContentSource.cpp` | `Code/GameEngine/Include/Common/Player.h` | 33 |
| `Code/GameEngine/Source/Common/Made002CC7DE.cpp` | `Code/GameEngine/Include/Common/Player.h` | 15 |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/OCLSpecialPower.cpp` | `Code/GameEngine/Include/Common/Player.h` | 22 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainUpdatePosition.cpp` | `Code/GameEngine/Include/Common/Player.h` | 1 |
| `Code/GameEngine/Source/Common/CreateAHeroManager.cpp` | `Code/GameEngine/Include/Common/Player.h` | 47 |
| `Code/GameEngine/Source/GameClient/GUI/parseSpellIndex_Thunk.cpp` | `Code/GameEngine/Include/Common/Player.h` | 38 |
| `Code/GameEngine/Source/GameLogic/Object/CreateAHero.cpp` | `Code/GameEngine/Include/Common/Player.h` | 28 |
| `Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderSidewaysAttack.cpp` | `Code/GameEngine/Include/Common/Player.h` | 5 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/GateOpenAndCloseBehavior.cpp` | `Code/GameEngine/Include/Common/Player.h` | 49 |
| `Code/GameEngine/Source/GameLogic/Object/LocomotorMoveTowardsPositionHorde.cpp` | `Code/GameEngine/Include/Common/Player.h` | 14 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp` | `Code/GameEngine/Include/Common/Player.h` | 42 |
| `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptTimeLine.cpp` | `Code/GameEngine/Include/Common/Player.h` | 136 |
| `Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp` | `Code/GameEngine/Include/Common/Player.h` | 120 |
