### LINK-254: RadarMarkerClientUpdate Snapshot slots rowed under placeholders
Status: Open. Updated: 2026-11-05; inspected revision: 91a4f16d0e.
Evidence / affected units: RadarMarkerClientUpdateCtor.cpp (0x004C9BCD) and
RadarMarkerClientUpdateDtor.cpp (0x004C9C38) model their vptr stores with private, non-polymorphic
views so they emit no vtable. Written against RadarMarkerClientUpdate.cpp's real classes, both
byte-match (1/1 and 5/5), but their vtables then reference
`?GetSnapshotName@DrawableModule@@MBEPBDXZ` and link_check drops them (32 -> 0 and 118 -> 0 bytes).
Retail tables (game.dat): RadarMarkerClientUpdate 0x00C5EDB8 slots 0..4 are 0x004C9CDB (??_G),
0x000B3FD0, 0x004C9BED, 0x004C9C7D, 0x004C9BF3 (getModuleNameKey); the intermediate Rva00362EC7
table 0x00C170A4 has 0x00252B84 at slot 2. Rows: 0x004C9BED `?Rva004C9BEDGet@@YAHXZ`
(ConstIntGetters4.cpp), 0x00252B84 `?name@Rva00252B84Named@@QBEPBDXZ` (SubsystemNameGetters.cpp),
0x004C9C7D `?xfer@BehaviorModule@@QAEXPAVXfer@@@Z` (non-virtual spelling).
Completed: none landed; the trial edits were reverted. The TU-side edits that made both bodies
match: a zeroing default constructor on Rva004C9B8F, an inline `virtual ~Rva00362EC7() {}` (its
row 0x00362EE3 is emitted by the destructor donor today) and a declared ~RadarMarkerClientUpdate.
Remaining / next check: give slot 2 of both tables (and slot 3) their virtual names: declare
RadarMarkerClientUpdate::GetSnapshotName and move 0x004C9BED into it (0x00252B84 is done: rowed
`?GetSnapshotName@DrawableModule@@MBEPBDXZ` since 2026-11-05, claudeb2; the free-function
placeholder 0x004C9BED has no tool mode yet). Then rewrite both donors and run
`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Update/RadarMarkerClientUpdate.cpp`.
MarkerTypeUpdateModuleDataCtor.cpp (0x004C9C98) is a separate case: its _ReadWriteBarrier keeps
the vptr store ahead of the +0x08 zero store, which every compiler-generated spelling reorders.
Clearance: pending.
Census confirmation: not claimed.
