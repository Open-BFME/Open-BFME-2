### MissileUpdate composition (2026-10-29, seat yasinschroeder-claudeb2)

- Landed: 2a7a171df8 merged 4 files into `MissileUpdate.cpp` (13 rows).
  1290a2c081 gave the TU the real five-base view
  (`Rva004A76DEBase0..4`, vptr stores now compiler-generated). b0b5f7fb8e
  retired the 0-B duplicate claims at 0x004A7551 and 0x004A78B8; the
  `MissileUpdateDtor.cpp` overrides own them now and are no longer gen-alias.
- Regression and repair: 1290a2c081 also added v01/getModuleNameKey/xfer
  slots to Base0. That left `?v01@Rva004A76DEBase0@@UAEXXZ` unresolved and
  made the TU's `??_7MissileUpdate@@6BRva004A76DEBase0@@@` copy differ from
  `MissileUpdateDtor.cpp`'s (link_check: MissileUpdate.cpp 670 -> 0 B).
  3d22a99311 restored the Dtor unit's virtual layout slot for slot
  (link_check at index d92e7e6635: MissileUpdate.cpp LINKS 888 B,
  MissileUpdateDtor.cpp 270 B, MissileUpdateXfer.cpp 283 B). Rule: every
  unit that emits a MissileUpdate vftable must spell the same virtual
  layout.
- Remaining (dry run `build/missile_dry4.txt` was local scratch, not committed):
  - `MissileUpdateDtor.cpp` compiles and byte-matches inside the merged TU,
    but the link guard refuses it until a census places the new row layout
    ("a file without a census object would place the merged unit earlier
    in link order"). Re-run `tu_skeleton.py --merge ... --dry-run` after
    the next census.
  - PoolKey (0x004A7699) and Xfer (0x004A796A) need getModuleNameKey/xfer as
    real Base0 slots 2/3. Table 0x00C5362C has 276 B (69 slots), and Base0 is
    the Module base. Adopt `Code/GameEngine/Include/Common/Module.h` (see
    "Module base chain" above) in the TU and in MissileUpdateDtor.cpp
    together, so the vftable copies stay identical and slot 1 resolves to a
    real provider.
  - `MissileUpdate_update.cpp` (polymorphic Thing view; past 0.98 partial),
    `MissileUpdateModuleDataDtor.cpp` (bytes) and
    `FamilyDeletingDtors_muse-7fd4.cpp` (needs the `EmitVtableTag` ctor on
    MissileUpdateModuleData) are not reconciled yet.
