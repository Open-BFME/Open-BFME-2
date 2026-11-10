### LINK-217: ReplaceObjectUpdate consolidation needs compatible class views
Status: Blocked. Updated: 2026-11-10; inspected revision: 037f3f47495 + local repair.
Completed:
- 2026-11-04 (`2d0ce472f888`): canonical module-data base adopted in `ReplaceObjectUpdateModuleDataCtor.cpp`; one header-queue row retired, 61 bytes exact and link preview preserved. No donor merge accepted.
- 2026-11-10 (local): `ReplaceObjectUpdateModuleDataDtor.cpp` (`Rva0044ECCE`) now inherits `Code/GameEngine/Include/Common/ModuleData.h` (`m_pad[0xC8 - 8]`), matching the 31-slot derived `??_7ReplaceObjectUpdateModuleData@@6B@` emitted by `ReplaceObjectUpdateModuleDataCtor.cpp`; `build.py` (7/7 matched), `eh_verify.py` (1 EXACT), `find_declared_unmatched.py --fail`, `class_gate.py`, and `link_check.py` over 5 TU-family units pass (`5/5`, `LINKED 2,527 -> 2,747 B`, `ReplaceObjectUpdateModuleDataDtor.cpp 0 -> 220 B`).
Remaining / next check: reconcile `ReplaceObjectUpdate`'s base (`SpecialAbilityUpdate` vs `Rva0044EF5E`), `Rva0044ECCE` -> `SpecialAbilityUpdateModuleData`, `ReplaceObjectUpdateModuleData`'s member views, and `Rva004B2B2F` in verified prerequisite commits, then retry `tu_skeleton`; keep the two mixed files (`GapBodiesGE24.cpp`, `ModuleUpdateDtors.cpp`) separate. Also note global `ModuleData::slot14` mismatch remains in `vtable_bridge_queue.tsv` alongside sibling `ModuleData` tables.
Evidence: [repair and current merge receipt](../../reverse/attempt_support/replaceobjectupdate-consolidation-20261104.md).
Clearance: pending; census confirmation not claimed.
