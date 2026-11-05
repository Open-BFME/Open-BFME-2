# Retire 14 verified Drawable header queue entries

Base: `4ebdf7a4a8b15aff69ed8f3a506bcc763504db84`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 23 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/Common/Rva000D19F9.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Update/Rva0037441ELeaf.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_rva003BA943.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 2 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SpawnPointInitializeBonePositions.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Weapon_positionProjectileForLaunch.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DScriptedModelDrawRva000B90A3.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameClient/InGameUIGetAllSelectedLocalDrawables.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsRva003BB5B7.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 2 |
| `Code/GameEngine/Source/GameClient/FXNuggetBaseSlots.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 2 |
| `Code/GameEngine/Source/GameClient/MessageStream/CommandXlatTargetProbe.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameLogic/AI/Rva00438D58Update.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 5 |
| `Code/GameEngine/Source/GameClient/InGameUIPlaceBuildAvailable.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameClient/InGameUIUpdateLocalPhantomStructureDisplay.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 3 |
| `Code/GameEngine/Source/GameClient/Drawable_rva00276BA9.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
