# LinearCampaignManager.cpp consolidation blockers

Allocated shard-0 destination: `Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp`.

The allocation and scoped planner checks passed. The plan has 112 approved rows, 20 clean donors, 12 mixed files and no refused files. The merge dry run accepted no donors. Rejections include `LinearCampaignAddCarryover.cpp` failing its `PlayerList.h` include-order guard; numerous private class/member and STL specialization conflicts; and byte mismatches in `LinearCampaignCarryoverInsert.cpp`, `Rva001EBD3BFinish.cpp`, `stlport_vector_bfmeassignrecord172_erase.cpp`, `FamilyDeletingDtors_Rva001EBFE5.cpp`, and `RvaTopByteFwds.cpp`. LinkGuard blocks the proposed composition across 19 census-linked units. The tool recommends class-view reconciliation across 15 classes. No source or ledger changes were applied.
