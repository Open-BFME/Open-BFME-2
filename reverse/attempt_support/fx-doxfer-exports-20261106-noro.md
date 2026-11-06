# LifeEvent and RenderObjectDraw info: retail DoXfer exports

2026-11-06; base `c628ead017b`. Status: repair verified locally, awaiting the automated
real link.

## Target facts

Export ordinal 1169 names `?DoXfer@LifeEventModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z`
at `0x00563E72`. Ordinal 1173 names the `RenderObjectDrawModuleInfo` spelling at
`0x00562871`. Both rows carried `?xfer@...@@MAEXPAVXfer@@@Z`.

## Consumers

Renaming the rows alone would have added unresolved names. Index `d707d2f53b`
shows four vtables binding the old names, emitted by six units, and two more units
call the bases directly. All eight now compile the reference-taking slot.

- Header `LifeEventModuleInfo.h` and `RenderObjectDrawModuleInfo.h`: the reference
  mode is public, as in `RenderObjectUpdateModuleInfo.h`. No unit used that mode
  before this change. The RenderObjectDraw `LoadPostProcess` in the capitalized mode
  is now a declaration, because `FXParticleSystem.cpp` defines that exported name.
- `LifeEventModuleInfoCopyCtorThunk.cpp` and `LifeEventModuleInfoDefaultCtor.cpp`:
  the private views take the new slot and declare `LoadPostProcess`, so that vtable
  slot no longer holds `__purecall`. Retail export 1310 puts it at `0x000B3FD0`.
- `VectorDeletingDtorsV04.cpp`, `Rva005E2C70Destructor_Rva003abc21.cpp`,
  `Rva005634F7Ctor.cpp` and `Rva003AB9FFDtor.cpp` stay in the default mode. The index
  shows no vtable of theirs binding the old names.

No second body or alias is added, and the old names are tombstoned.

## Verification

- `./build.sh` on the ten changed units: **17/17** rows exact.
- The commit hook rebuilds the ten header dependents.
- `link_check.py`: 10 of 10 LINKS, 963 -> 963 bytes against index `d707d2f53b`.
  This is a preview, not an export-link check.
- `build/match` objects: the old spellings appear nowhere, and the ten changed units
  use the new ones. That directory holds only part of the tree's objects.

No real-link or runtime result is claimed.
