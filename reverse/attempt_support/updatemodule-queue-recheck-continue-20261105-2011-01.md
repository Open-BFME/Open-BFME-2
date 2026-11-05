# Retire 8 verified UpdateModule header queue entries

Base: `60cc40eb3a289822e9e31e0c4957c3bea6ed3d9d`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 194 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/DeflectSpecialPower.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 12 |
| `Code/GameEngine/Source/GameLogic/Object/Update/FloodUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 21 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ThreatFinderUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 20 |
| `Code/GameEngine/Source/GameLogic/Object/Update/AttributeModifierAuraUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 20 |
| `Code/GameEngine/Source/GameLogic/Object/Upgrade/CostModifierUpgrade.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 17 |
| `Code/GameEngine/Source/GameLogic/Object/Update/EmotionTrackerUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 25 |
| `Code/GameEngine/Source/GameLogic/Object/Update/AttributeModifierPoolUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 48 |
| `Code/GameEngine/Source/GameLogic/Object/Update/ProductionUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` | 31 |
