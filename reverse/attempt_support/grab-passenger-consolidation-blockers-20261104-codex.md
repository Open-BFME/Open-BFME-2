# GrabPassengerSpecialPower.cpp consolidation blockers

Allocated shard-0 destination: `Code/GameEngine/Source/GameLogic/Object/SpecialPower/GrabPassengerSpecialPower.cpp`.

The allocation and scoped planner checks passed. The plan has 17 approved rows, three clean donors, two mixed files and no refused files. The merge dry run accepted no donors: `GrabPassengerSpecialPowerDoAtObject.cpp` fails because `SpecialPowerModule` is an undefined base; `GrabPassengerSpecialPower_doSpecialPower.cpp` lacks constructor/member declarations in its local views. The tool recommends reconciling `GrabPassengerSpecialPower`, `GrabPassengerSpecialPowerModuleData` and `SpecialPowerModule`. LinkGuard blocks the composition across the three census-linked units. No source or ledger changes were applied.
