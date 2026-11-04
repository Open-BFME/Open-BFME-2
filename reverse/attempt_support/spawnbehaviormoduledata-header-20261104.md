# SpawnBehaviorModuleData header adoption, 2026-11-04

Inspected source revision: `4db5a76637`. Claim owner: `yasinschroeder-codexb`.
Canonical header: `Code/GameEngine/Include/GameLogic/Module/SpawnBehaviorModuleData.h` (unchanged).

## Completed scope

Three consumers now include the canonical class instead of defining private views:

- `SpawnBehavior_createSpawn.cpp`: interprets the existing +0x20 opaque storage as the same STLport vector; uses canonical +0x19 and +0x172 fields.
- `SpawnBehavior_getUpgradeActivationMasks.cpp`: views the existing +0x5C member as its two-mask UpgradeMuxData view.
- `SpawnBehavior_update.cpp`: uses the same +0x5C view and the canonical Rva001EAE6FHelper declaration for the existing 0x80-byte clear call, avoiding a second helper definition.

Target layout facts are already documented in the canonical header. The casts preserve the consumers' established storage views; no new donor identity or member recovery is claimed.

`./build.sh` on these three sources: 5/5 rows matched, source claims and string/float/import checks passed. `find_declared_unmatched.py`: all defined functions already matched. `header_adopt_lane.py accept --class SpawnBehaviorModuleData` passed all three consumers and retired exactly their three queue rows.

Ordinary `link_check.py` preview, index 2026-11-04 17:56 at `8c757ea0db`:

| Consumer | Before | After |
| --- | ---: | ---: |
| createSpawn | 676 B | 676 B |
| getUpgradeActivationMasks | 46 B | 46 B |
| update (including owned hash lookup) | 527 B | 527 B |

All three link cleanly; 1,249 B preserved. This is a scoped preview, not a new census measurement.

## Remaining queued consumers

The automatic adoption trial was restored for every failing source:

- `FamilyDeletingDtors.cpp`: its synthetic `SpawnBehaviorModuleData(EmitVtableTag *)` vtable-emission constructor has no declaration in the canonical header (C2511). Reconcile emission of the rowed deleting destructor without adding a stand-in constructor to the real interface.
- `ModuleFactoryInit.cpp`: donor Common/ModuleFactory.h transitively defines ModuleData, conflicting with the canonical base (C2011). Reconcile the donor header context before adopting this derived class.
- `SpawnBehaviorModuleDataCtor.cpp`: its explicit +0 vtable member and empty BehaviorModuleData base cannot map to the canonical polymorphic ModuleData base. The rowed constructor and EH graph must remain exact; review base teardown identity and code generation together (existing LINK-095 context).
- `SpawnBehaviorModuleDataDtor.cpp`: the automatic rewrite cannot map its live vector at +0x20 to canonical opaque storage. Merely replacing it with opaque bytes would lose vector teardown. Recover a lifetime-compatible canonical vector/base representation and verify affected consumers before retrying.

No changes remain in those four files and their queue rows remain. No shared header, function row, pin, alias, source path or hatch changed.
