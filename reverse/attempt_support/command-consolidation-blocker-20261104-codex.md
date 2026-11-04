# Command.cpp consolidation trial

Allocated shard-0 destination: `Code/GameEngine/Source/Common/Command.cpp`.

`consolidation_queue.py --check-tu` and the scoped planner/current-snapshot check passed. The TU plan has 10 approved rows, two clean donors, three mixed files and no refused files. The merge dry run accepted no donors: `Command_AddUpgradableCommandPointsToBonus.cpp` fails compilation because `_STL::allocator` and `_STL::vector` are already defined; LinkGuard reports both the seed and donor census-linked. The report recommends reconciling private `Command` views. No source or ledger changes were applied.
