# Radar Snapshot table at 0x0080363C

The retail primary table is 52 bytes and has 13 slots. Both current
Radar lifetime units emit a 16-byte primary table and the same 56-byte
secondary table. The installed addresses are 0x00C0363C at +0 and
0x00C03604 at +4. Scope is RadarDtor.cpp and RadarRva002D7BD3.cpp.

Native scratch builds reproduced all 16 current function rows and
emitted matching 13-slot primary tables in both units. The 14
secondary entries kept the same bytes and relocations. The existing
subsystem class supplies the secondary profile.

| Primary slot | Retail RVA | Provider |
| --- | --- | --- |
| 0 | 0x002D8888 | Compiler weak deleting-destructor default to the rowed scalar wrapper |
| 1 | 0x002D7ABF | Radar::loadPostProcess |
| 2 | 0x0004FA11 | Radar literal getter, currently Rva0004FA11Named::name |
| 3 | 0x002D85D7 | Radar::xfer |
| 4 | 0x002D7AA6 | Radar::refreshTerrain |
| 5 | 0x002D7AB0 | Radar::queueTerrainRefresh |
| 6 | 0x002D7E68 | Radar::rva002D7E68 |
| 7–12 | 0x0003B810 | __purecall |

The slot 6 transfer keeps the private Radar.cpp dispatch offsets by
replacing s06 in place. Radar.h puts the same declaration in its
existing slot 6. TerrainLogic keeps its virtual call and the
W3DRadar override at 0x0004E3A6 makes a qualified direct call to the
exact 326-byte base body. The native verification covers 69 sources,
with 1,750 function rows, 17 data rows and 311 exact EH graphs. The
four current Radar-family tables in those objects keep their byte and
relocation manifests. The five changed or directly affected sources
link in the scoped preview at 6,319 bytes against census 179f73d302.

The owning slot 2 transfer to Radar::GetSnapshotName was refused because
there is no approved name for
`Code/GameEngine/Include/Common/Radar.h|slot|Radar@0x00C0363C|2`.
The six-byte original getter is in SubsystemNameGetters.cpp, and the
retail W3DRadar table at 0x00BC4E34 shares its address. Keep both
bindings in the approval and transfer proof. The map's proposed
W3DRadar.cpp route is insufficient for a source move.

After the slot 2 transfer, both lifetime units need a common Radar
declaration with the name-slot profile set before the first Snapshot
include. Preserve construction and destruction of the 64 events at
+0x2C, their 0x50-byte stride, the +0x4C reference field, and the
existing one-byte Radar::init in the secondary table. The shared
header's event pad and the two raw views in RadarFrameTick and Radar_reset
need reconciliation when introducing the typed array. Whole-image
verification remains pending.
