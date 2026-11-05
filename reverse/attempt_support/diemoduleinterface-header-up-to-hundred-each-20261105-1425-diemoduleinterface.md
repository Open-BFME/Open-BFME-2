# Adopt the registered DieModuleInterface header in 6 units

Base: `163a06716c509fb8cbf9baf65b44295514d3041d`. Native scope: 52 existing rows and 291 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same full class layout and virtual slots before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

The scoped header acceptance checks the dated linking prediction.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `Code/GameEngine/Source/Common/VslotSmallBodiesE.cpp` | 10 | 12 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorDtor.cpp` | 5 | 58 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehavior.cpp` | 7 | 64 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehaviorOnDie.cpp` | 1 | 8 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehaviorUpdate.cpp` | 14 | 102 |
| `Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCrushing.cpp` | 15 | 47 |
