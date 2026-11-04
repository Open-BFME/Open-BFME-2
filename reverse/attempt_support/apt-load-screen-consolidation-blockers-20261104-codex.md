# AptLoadScreen.cpp consolidation blockers

Allocated shard-0 destination: `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptLoadScreen.cpp`.

The allocation and scoped planner checks passed. The plan has 56 approved rows, three donor files, one mixed file and no refused files. The merge dry run accepted no donors: `AptLoadScreenInit.cpp` references undeclared `m_layout`; `AptLoadScreenCtor.cpp` defines a constructor absent from the destination class view. The tool recommends reconciling private `AptMapPreview` and `Rva0057E3DB` views. LinkGuard blocks the composition across all three census-linked units. No source or ledger changes were applied.
