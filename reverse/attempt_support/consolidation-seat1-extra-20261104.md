# Consolidation shard 1 additional probes (2026-11-04)

Both destinations passed `consolidation_queue.py --check-tu`. Each used a
narrow `name_lane.py consolidate --under <parent>` snapshot and passed
`name_lane.py consolidate --check` before `tu_skeleton.py --plan` and
`--merge --dry-run`. No donor was accepted and no source or ledger was changed.

| Destination | Blocker for the mechanical lane |
| --- | --- |
| `Code/Libraries/Source/debug/debug_io_con.cpp` | Both donors are census-linked. The constructor donor changes selected `??_GDebugIOInterface@@MAEPAXI@Z` and `??_7DebugIOCon@@6B@` COMDATs; the destructor-thunk donor changes the same provider COMDAT and breaks another unit's `??_7DebugIOCon@@6B@` copy. LinkGuard rejected both. |
| `Code/GameEngine/Source/Common/SubsystemLegend.cpp` | Both donors are census-linked. The destructor donor hits duplicate `_STL::allocator` and `_STL::_List_base` template definitions (`C2953`); the append donor has `_STL::allocator<_Tp>::deallocate` declaration mismatch (`C2244`) followed by a fatal compiler error. The target also requires `SubsystemLegend` view reconciliation. |

The COMDAT/provider composition and STL declaration prerequisites need work
outside mechanical consolidation. No merge, matched-row movement or file
reduction is claimed.
