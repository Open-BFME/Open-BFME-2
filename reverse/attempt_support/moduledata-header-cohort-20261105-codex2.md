# ModuleData header cohort, 2026-11-05

Inspected source revision: `db6bc5435cb158b601350f881bf56f31e8ec3090`.
Scope: the following thirteen ModuleData header-queue consumers, claimed as
`yasinschroeder-codex2`.

- `Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldPlayerCreateRevival.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferDoXfer.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBuffer.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/Rva0021294ACreate.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/Rva002B85ECFilter.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/Rva002B8A9FPushOnce.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/Rva002B8AC0Finish.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/Rva002B8D06Xfer.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/Rva002B8DFCXfer.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/Rva0031BF1BRemove.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/Rva003F5970Ctor.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/Rva004EC869.cpp`

Changes and evidence boundary:

- Replace private ModuleData declarations with the existing canonical header.
  Revival uses slots 13/28; shrub/tree drawing uses slot 16 with explicit casts
  to its existing data views. These slot identities preserve the target call
  offsets; they do not establish additional retail method names.
- Rva0021294ACreate's derived record starts its own fields at +8: the canonical
  base already owns +4, so the former duplicate +4 member is removed.
- Seven field-only records use distinct address-labelled offset views through
  explicit casts, retaining ModuleData pointer/container ABI identities.
  Rva004EC869 similarly retains an opaque entry view for its +0x1C virtual call
  taking an int. These are structural views, not recovered retail class names
  or claims that these offsets belong to canonical ModuleData.
- No shared header, ledger identity, source path, pin or alias was changed.

Verification:

- `./build.sh <all thirteen sources>`: 125/125 functions exact; 45 funclet pins
  verified, 13 literals plus 18 empty-string references exact, 35 float literals
  and four named imports verified. Final run has all thirteen cache inputs current.
- One cohort `header_adopt_lane.py accept --class ModuleData <all sources>`
  passed all thirteen and retired thirteen rows in `reverse/header_queue.tsv`.
  Final acceptance after distinguishing the offset-view names also passed all thirteen.
- `link_check.py <all sources>`: thirteen LINKS, 23,819 -> 23,819 preview-linked
  bytes. Index census: 2026-11-05 15:19 at `f44cbcf5b0`. This preserves the
  measured scope; it is not a new census or a real-link milestone.
- Before/after COFF symbol audit: twelve units lose no external definition.
  W3DTreeBuffer stops emitting
  `?getModuleInfo2F0@ThingTemplate@@QBEABVModuleInfo@@XZ`. All 26,379 objects
  under build/match were searched, with COFF symbol checks on matching objects:
  W3DTreeBufferXfer remains a provider; there are zero undefined consumers.
  Every unit's weak-alias map is unchanged. No link-wide alias was removed.

The wider module-chain obstacle remains open. Continue with the remaining
ModuleData header queue and its documented layout conflicts; no TU merge or
broader clearance is claimed by this cohort.
