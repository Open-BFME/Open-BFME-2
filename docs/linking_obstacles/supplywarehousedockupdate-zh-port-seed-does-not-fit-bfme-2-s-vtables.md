### SupplyWarehouseDockUpdate ZH-port seed does not fit BFME 2's vtables (2026-10-30)

Status: inspected, no repair. Base `c744574392`, index `12b9e7a7c0`. The
seed (`SupplyWarehouseDockUpdate.cpp`, 3 matched rows, 217 bytes) is a verbatim
ZH port and does not link: 7 unresolved symbols and 2 COMDAT losers. The
retail vtables at `0x00853790` (ObjectModule view) and `0x00853740`
(DockUpdateInterface view) show three structural mismatches:

- **Dtor access.** Retail's base dtor is `??1DockUpdate@@UAE@XZ` (`0x0058A0F4`,
  `Rva0058A0F4Dtor.cpp`), but the ZH header spells it `MAE`.
- **Rows already exist under placeholder names.** Slot 0 is
  `??_GRva004A7D55` (`0x004A7E27`), which calls `??1Rva004A7D55`
  (`0x004A7D55`): the real `~SupplyWarehouseDockUpdate`. The seed's
  present-unmatched dtor duplicates it.
- **No `crc` virtual.** BFME 2 has none, so the seed's present-unmatched
  `crc`/`loadPostProcess` bodies reference `DockUpdate::crc`, which is not in
  retail. Slot 1 is `loadPostProcess` (`0x004A7FC5`, `Rva004A7FC5Slot.cpp`),
  slot 3 xfer (`0x004A7D7B`), slot 4 the pool key (`0x004A7DA5`), slot 5
  `0x004A7E43`.

The remaining unresolved symbols (`DISABLEDMASK_NONE` as `BitFlags<13>`
against retail's `BitFlags<11>` at `0x00A030CC`,
`Drawable::updateDrawableSupplyStatus`,
`SupplyWarehouseActionObject::getDistanceSquared`) come from the ZH `action`
and `onObjectCreated` bodies, which are present-unmatched.

Next: rebuild the unit on BFME 2 views. Drop the ZH bodies that have no retail
row and rename the `Rva004A7D55` rows to `SupplyWarehouseDockUpdate`. This
overlaps the blocked TU merge (re_attempts `tu-merge:...SupplyWarehouseDockUpdate.cpp`).
No census gain claimed.
