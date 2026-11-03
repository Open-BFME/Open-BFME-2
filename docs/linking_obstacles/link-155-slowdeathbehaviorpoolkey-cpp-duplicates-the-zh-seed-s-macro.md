### LINK-155: SlowDeathBehaviorPoolKey.cpp duplicates the ZH seed's macro copy (2026-10-30, open)

The link tier serves `Module/SlowDeathBehaviorPoolKey.cpp`
(`SlowDeathBehavior::getModuleNameKey`, 0x0045D459, 69 B): duplicate, comdat
loss and wrong selection. Its approved unit (tu_map) is
`Behavior/SlowDeathBehavior.cpp`. That unit is a ZH-header port, and its
`MAKE_STANDARD_MODULE_MACRO` emits a second "unknown" copy, so the strong row
and the inline copy collide. The fix is the merge, not a trim of either copy.
`tu_skeleton.py --merge Behavior/SlowDeathBehavior.cpp --dry-run` (origin
`07f7d7f8ec`) accepts no donor:
- the PoolKey donor hits C2084 (the body already exists);
- Xfer and ModuleDataCtor hit class redefinitions (`Xfer`, `Module`, `ModuleData`);
- Ctor is missing `m_secondary20`/`m_secondary24`;
- Notify is missing `ObjectCreationList::rva001F0410`;
- ParseDeathFlags fails to compile;
- HelicopterSlowDeathUpdate mismatches its bytes;
- `Rva0045D887BitSet.cpp` would lose its link (`DISABLEDMASK_ALL`/`NONE`,
  `UpdateModule::crc`).

Prerequisite: reconcile the seed onto the BFME views (`tu_views.py
Behavior/SlowDeathBehavior.cpp`, classes Rva0045D887, SlowDeathBehavior,
SlowDeathBehaviorModuleData, UpdateModule), together with the UpdateModule
layout and `setExtraBounciness` home issue above. No source change is retained,
and no census gain is claimed. The log is in `build/sdb-dry.log` (scratch).
