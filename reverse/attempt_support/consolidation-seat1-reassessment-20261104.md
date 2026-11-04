# Consolidation shard 1 reassessment (2026-11-04)

After the first 20 allocated candidates were exhausted, the full allocator
listing contained 99 unheld shard 1 TUs. These newer probes passed
`consolidation_queue.py --check-tu`; each scoped consolidation snapshot passed
`name_lane.py consolidate --check` before the plan and dry run. No dry run
accepted a donor, so no claims or source changes were made.

| Destination | Dry-run result |
| --- | --- |
| `debug_io_con.cpp` | LinkGuard refused both ctor/dtor donors: merged composition loses the selected `DebugIOInterface` deleting dtor COMDAT and breaks another unit's `DebugIOCon` vtable. |
| `AptMpChat.cpp` | `Rva0057FF3ECtor.cpp` fails `C2511`: `Rva0057FE6B(TargetRef00217D4C*, int, bool)` is absent from the target view; `tu_views` reconciliation is required. |
| `lapi.c` | Both record-lookup donors have no baseline match. |
| `BloodthirstyUpdate.cpp` | Donors fail class/compiler prerequisites (`C2373` vftable redefinition, `C2600` undeclared special member), a module-data donor fails bytes, and LinkGuard reports unresolved update-interface methods after the dtor move. |
| `W3DFloorDraw.cpp` | No donors accepted: the ctor and Xfer donors lack class members (`C2511`/`C2039`); pool-key and dtor donors fail declarations; `W3DFloorDrawModuleData` view reconciliation is required. |
| `SpecialDisguiseUpdate.cpp` | Ctor donors fail on missing declarations (`C2511`/`C2600`); the module-data dtor fails bytes; reconciliation is required for both update and module-data views. |

The current full listing and preceding continuation evidence cover the other
allocated candidates. No mechanical task in the reviewed scope can proceed
without manual class/view/provider repairs or a changed LinkGuard composition;
those prerequisites belong to other seats. No TU merge, split, matched-row
preservation or file reduction is claimed here.
