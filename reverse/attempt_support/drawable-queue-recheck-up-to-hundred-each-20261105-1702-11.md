# Retire 4 verified Drawable header queue entries

Base: `0661a2a1046527e7416e512d6312d37bf4cb7a0d`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 71 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehaviorUpdate.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 14 |
| `Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarCommandProcessing.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 8 |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowDecalHelpers.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 17 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeTransportContain.cpp` | `Code/GameEngine/Include/GameClient/Drawable.h` | 32 |

This scope replaces entries excluded from the preceding task count
during the upstream reconciliation.
