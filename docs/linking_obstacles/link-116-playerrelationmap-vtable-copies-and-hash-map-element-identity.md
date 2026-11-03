### LINK-116: PlayerRelationMap vtable copies and hash_map element identity
Status: Cleared (ordinary preview). Updated: 2026-10-27; inspected revision: e1e28795a9e0f9c1a46105e106990ac4a5ba8ef6.
Evidence / affected units: `Common/RTS/PlayerRelationMapCtor.cpp` (81 B) was L0 against index `bf3dd31211` on two blockers. (a) `??_7PlayerRelationMap@@6B@` differed between the constructor unit (loadPostProcess/crc/xfer) and the destructor and deleter units (three `__purecall` slots). Retail vftable 0x00BFDD90 holds the deleting destructor 0x002ADE55, the shared empty ret 0x000B3FD0, the rowed literal getter 0x002AD0C0 and xfer 0x002ADEBE. (b) The `hash_map<int, Rva002AF625Element>` ctor 0x002AF625 calls hashtable ctor 0x002AF438, rowed for the element `Rva002AF438Element`. Only a pin carried the 625 spelling, so the unit instantiated its own non-retail hashtable copy that called a local `_M_initialize_buckets`.
Completed: all three emitters now declare the Snapshot slots through `BFME_SNAPSHOT_NAME_SLOT`. Slot 2 was renamed `?GetSnapshotName@PlayerRelationMap@@MBEPBDXZ`, and `?loadPostProcess@PlayerRelationMap@@MAEXXZ` was rowed as an ICF fold of 0x000B3FD0 (Player.cpp, present-unmatched marker removed). The element is now spelled `Rva002AF438Element` in both constructor units and the 0x002AF625 row, and the redundant 625 hashtable pin was dropped. `link_check.py` on the Ctor, Deleter, Dtor, SubsystemNameGetters2, RelationMapXfer and StlSweepW5Rva002AF438 units: Ctor 0 -> 81 B and the other five keep LINKS. `PlayerCtorBFME2.cpp` stays L0 on unrelated blockers (UnitRevivalTracker dtor, Rva002B0F3CEnergy slots, Rva001FEAB2Element hashtable).
Remaining / next check: `TeamRelationMap` (dtor 0x003A2563, deleter) uses the same `__purecall` view and should take the same slots once its constructor unit emits a different copy.
Clearance: preview only, index `bf3dd31211`.
Census confirmation: awaiting.

2026-10-30 identity-retirement preflight at `43231d14ed`: the unchanged
`RelationMapXfer.cpp` passes its supported 6/6-row build and strict explicit
provider preparation. The owning `retire identity` command still refuses:
1,645 ledger objects are missing, so kept-copy selection is unknown. The
identity register remains unchanged; this does not clear that finding.
Populate and verify the current whole-tree objects before retrying retirement.
[Scoped evidence](../../reverse/attempt_support/crt-headers-player-20261030-codexb5.md).
