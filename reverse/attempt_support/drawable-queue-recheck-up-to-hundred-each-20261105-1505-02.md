# Retire 20 verified Drawable header queue entries

Base: `d593ae697df4c248d34905200edb0d51142ef2ef`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 70 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderTintHierarchy.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DPropDrawReact.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 3 |
| `Code/GameEngine/Source/GameClient/Drawable_rva0027541E.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 4 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/OpenContainAdd.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorResume.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawReactToTransformChange.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateStartMoveSound.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 13 |
| `Code/GameEngine/Source/Common/Rva000B508A.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Upgrade/BaseUpgradeUpgradeImplementation.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 3 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainAveragePosition.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw_setTerrainDecal.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 3 |
| `Code/GameEngine/Source/GameClient/InGameUISiegeDeployTarget.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 5 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/SlaughterHordeContainRva00463AD3.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameClient/InGameUI_selectMatchingCallback.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 5 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/RiderChangeContainOnContaining.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/RampageBehavior_update.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/RiderChangeContainOnRemoving.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 1 |
| `Code/GameEngine/Source/GameClient/InGameUIIdleWorker.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 9 |
| `Code/GameEngine/Source/GameClient/Drawable/Update/SwayClientUpdate.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 8 |
| `Code/GameEngine/Source/GameClient/InGameUI_selectMatchingAcrossRegion.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 7 |
