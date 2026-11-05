# Retire 19 verified Drawable header queue entries

Base: `7dc4b67c8e26610c09218ebb9e47ccfab9a71afd`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 212 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/System/GameLogicDispatchDoSetRallyPoint.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 15 |
| `Code/GameEngine/Source/GameClient/InGameUISelectDrawable.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 7 |
| `Code/GameEngine/Source/GameClient/InGameUIInputModes.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 11 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainChangeToFormation.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 5 |
| `Code/GameEngine/Source/GameClient/Rva0029B1C2.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 6 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain_onContaining.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameClient/EvaEventFXNugget.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 13 |
| `Code/GameEngine/Source/GameLogic/System/DelayedExperienceLevelGrantSystem.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 15 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehavior.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 18 |
| `Code/GameEngine/Source/GameClient/InGameUICreateCommandHint.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 4 |
| `Code/GameEngine/Source/GameLogic/Object/Update/RubbleRiseUpdate.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 8 |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainTracksBind.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 15 |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarMultiSelect.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 3 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehavior.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 8 |
| `Code/GameEngine/Source/GameLogic/Object/Update/StealthDetectorUpdate.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 21 |
| `Code/GameEngine/Source/GameLogic/Object/Update/SpecialDisguiseUpdate.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 20 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ToggleMountedSpecialAbilityUpdate.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 18 |
| `Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCrushing.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 15 |
| `Code/GameEngine/Source/GameLogic/Object/WeaponPrivateFireWeapon.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 9 |
