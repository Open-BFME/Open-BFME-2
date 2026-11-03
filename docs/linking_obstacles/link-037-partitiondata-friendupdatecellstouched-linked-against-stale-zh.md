### LINK-037: PartitionData_friendUpdateCellsTouched linked against stale ZH updateCellsTouched instead of native ShroudManager::Data provider
Status: Cleared. Updated: 2026-10-26; inspected revision: 7e7941d0cb.
Evidence / affected units: `Code/GameEngine/Source/GameLogic/Object/PartitionData_friendUpdateCellsTouched.cpp`,
`reverse/link_status.csv` reported wrong_selected 1 for `?updateCellsTouched@PartitionData@@AAEXXZ`.
Completed: In retail, tail call at 0x0073B250 jumps directly to 0x0073AD90 (`ShroudManager::Data::UpdateCellsTouched`).
Updated unit to call `((ShroudManager::Data *)this)->UpdateCellsTouched()` instead of unmatching legacy ZH method.
Remaining / next check: None.
Clearance: `tools/link_check.py Code/GameEngine/Source/GameLogic/Object/PartitionData_friendUpdateCellsTouched.cpp`
reports: LINKS (0 -> 37 bytes). Exact 1/1 byte match preserved.
Census confirmation: awaiting the next census.
