# TransportContainModuleData factory header adoption

Inspected base: `de2be71366`, 2026-11-05. Scope: the four queued consumers of
`TransportContainModuleData`; shared headers and member providers are unchanged.

## Retained repair

`AODHordeContain.cpp` now includes the registered TransportContainModuleData
header before Drawable.h instead of declaring a private 0x18C-byte class.
ModuleData selects Snapshot's existing lowercase post-load and pointer-transfer
surface first. Including it after Drawable selected the capitalized surface and
left the module-data class abstract; a scratch compiler diagnostic identified
the two unimplemented pure virtuals. No new Snapshot variant was introduced.

Checks on the retained source:

- `./build.sh .../AODHordeContain.cpp`: 30/30 functions and one data row match;
  nine float literals pass; both renumbered funclets resolve through their EH data.
- `find_declared_unmatched.py`: all defined functions already matched.
- `eh_verify.py`: 13 EXACT EH graphs, zero non-exact or missing objects.
- Ordinary `link_check.py`: LINKS, 2,204 -> 2,204 bytes against the published
  2026-11-05 15:19 census at `f44cbcf5b0`. This is a preview, not a game run.
- A HEAD-source diagnostic compile to `build/aod-before-header.obj`, outside
  the shared match cache, compared with the verified adopted object: 84 external
  definitions before and after; no symbol removed or added. The removed private
  class declared methods only and supplied no inline body or alias. Every
  existing alternatename directive remains.
- One `header_adopt_lane.py accept --class TransportContainModuleData` over
  all four consumers passes the factory and retires its single queue row.

## Remaining cohort

The owning tool leaves all three other rows queued:

- `TransportContain.cpp` and `TransportContainModuleDataDtor.cpp`: the canonical
  header's +0xA4 `void *` cannot replace their nontrivial STL list. The header's
  +0x180 byte storage also cannot supply the destructor's vector teardown.
  Recover typed container members and their constructor/destructor behavior
  together before retrying; the automatic trials were restored.
- `ContainModuleDeletingDtors.cpp`: already includes the canonical header and
  has no private TransportContainModuleData body. Byte verification passes, but
  the ordinary preview reports LINKS 420 -> 392 bytes because the 28-byte
  TransportContainModuleData deleting destructor is now rowed in
  TransportContain.cpp. Acceptance refuses that per-file loss. Keep the queue
  row until a census includes the moved owner and the normal acceptance passes.

The only other queued class in AODHordeContain.cpp is Locomotor; its class claim
is held by another worker, so no Locomotor adoption was attempted.
