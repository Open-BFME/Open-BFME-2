# RainOfFireUpdate consolidation trial (2026-11-04)

Allocated destination: `Code/GameEngine/Source/GameLogic/Object/Update/RainOfFireUpdate.cpp`; `consolidation_queue.py --check-tu` passed. A fresh Update-scoped planner and its `--check` passed. The plan had 16 approved rows, three pull donors and two mixed donors.

The merge dry run accepted no donors. `RainOfFireUpdateCtor.cpp` failed on a secondary-vftable redefinition; `RainOfFireUpdateDtor.cpp` failed on duplicate `ObjectModule` and `BehaviorModuleInterface` declarations. The mixed `ConstIntGetters4.cpp` row `0x004AC12F` matched alone but its split failed on duplicate module-interface declarations. The mixed `ModuleDataBuildFieldParse.cpp` row `0x004AC097` matched alone, but its split failed on duplicate `RainOfFireUpdateModuleData` and a missing field; it carries `g_00C54B00`. No changes or claims were made. No source reduction or identity/link progress is claimed.
