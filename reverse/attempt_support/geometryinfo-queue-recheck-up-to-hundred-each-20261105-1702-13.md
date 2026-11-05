# Retire 6 verified GeometryInfo header queue entries

Base: `b32cae0bd68356fc2626a4e092bc73ba1cd98f0b`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 103 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/Common/Rva00261D2EFilter.cpp` | `Code/GameEngine/Include/Common/Geometry.h` | 6 |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DScriptedModelDrawAdjustTransformMtx.cpp` | `Code/GameEngine/Include/Common/Geometry.h` | 4 |
| `Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateIsWithinStartAbilityRange.cpp` | `Code/GameEngine/Include/Common/Geometry.h` | 6 |
| `Code/GameEngine/Source/GameLogic/Object/Body/ImmortalBody.cpp` | `Code/GameEngine/Include/Common/Geometry.h` | 43 |
| `Code/GameEngine/Source/GameLogic/Object/ObjectDoXfer.cpp` | `Code/GameEngine/Include/Common/Geometry.h` | 11 |
| `Code/GameEngine/Source/GameLogic/Object/Update/FoundationAIUpdate.cpp` | `Code/GameEngine/Include/Common/Geometry.h` | 33 |

This scope replaces entries excluded from the preceding task count
during the upstream reconciliation.
