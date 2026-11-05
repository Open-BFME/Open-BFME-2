# Retire 19 verified Player header queue entries

Base: `6079d53659825b2599d5fa52ac4043ffef013210`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 175 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/Common/Rva004BDFCB.cpp` | `Code/GameEngine/Include/Common/Player.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Die/SpecialPowerCompletionDieNotify.cpp` | `Code/GameEngine/Include/Common/Player.h` | 1 |
| `Code/GameEngine/Source/GameLogic/AI/PartitionFilterRva00341C54GetPlayerMask.cpp` | `Code/GameEngine/Include/Common/Player.h` | 2 |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleCreateViewObject.cpp` | `Code/GameEngine/Include/Common/Player.h` | 4 |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleDtor_Unresolved.cpp` | `Code/GameEngine/Include/Common/Player.h` | 5 |
| `Code/GameEngine/Source/GameLogic/Object/ObjectGetCreateAHeroSpecialPower.cpp` | `Code/GameEngine/Include/Common/Player.h` | 6 |
| `Code/GameEngine/Source/Common/AIRoamingDefenseTactic.cpp` | `Code/GameEngine/Include/Common/Player.h` | 14 |
| `Code/GameEngine/Source/GameLogic/Object/ObjectOnDie.cpp` | `Code/GameEngine/Include/Common/Player.h` | 3 |
| `Code/GameEngine/Source/GameLogic/System/GameLogicDispatchDoSetRallyPoint.cpp` | `Code/GameEngine/Include/Common/Player.h` | 15 |
| `Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/VeterancyCrateCollide.cpp` | `Code/GameEngine/Include/Common/Player.h` | 13 |
| `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` | `Code/GameEngine/Include/Common/Player.h` | 24 |
| `Code/GameEngine/Source/GameLogic/Object/WeaponEffects/MetaImpactNugget.cpp` | `Code/GameEngine/Include/Common/Player.h` | 6 |
| `Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/AptInGameSpellBookInterface.cpp` | `Code/GameEngine/Include/Common/Player.h` | 28 |
| `Code/GameEngine/Source/GameLogic/Object/Update/OneRingPenaltyUpdate.cpp` | `Code/GameEngine/Include/Common/Player.h` | 13 |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleTrigger.cpp` | `Code/GameEngine/Include/Common/Player.h` | 12 |
| `Code/GameEngine/Source/GameLogic/Object/Update/EmotionTrackerUpdate_update.cpp` | `Code/GameEngine/Include/Common/Player.h` | 7 |
| `Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderCheckChangeLayers.cpp` | `Code/GameEngine/Include/Common/Player.h` | 1 |
| `Code/GameEngine/Source/Common/RTS/PlayerList.cpp` | `Code/GameEngine/Include/Common/Player.h` | 18 |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarRva0031D230.cpp` | `Code/GameEngine/Include/Common/Player.h` | 2 |
