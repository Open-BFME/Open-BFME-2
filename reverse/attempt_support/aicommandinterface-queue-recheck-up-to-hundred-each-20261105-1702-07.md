# Retire 6 verified AICommandInterface header queue entries

Base: `76a9c1bd0fcd206e968ea59e45d9e3d7d02219e3`. These sources already included the registered header
or its supported companion. The owning header-adoption tool verified the
current objects and scoped link predictions and removed the entries.
The affected sources contain 14 existing matched rows.

Current compiler dependency receipts resolve the expected header in each source.
The source contents, function ledger and headers are unchanged by this batch.
The retirements record verified existing adoption. Full-game linking and
runtime behaviour require separate evidence.

| Source | Resolved header | Existing rows |
| --- | --- | ---: |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/EvacuateGarrisonSpecialPowerSlot19.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/AI/AIMoveAndEvacuateStateUpdate.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/SpecialPower/UnleashSpecialPowerSlot17.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 3 |
| `Code/GameEngine/Source/GameLogic/Object/Contain/HorseHordeContainRva00476D77.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 1 |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitGarrisonNearestBuilding.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 5 |
| `Code/GameEngine/Source/Common/Rva0044E6AEVirtForward.cpp` | `Code/GameEngine/Include/GameLogic/Module/AIUpdate.h` | 3 |
