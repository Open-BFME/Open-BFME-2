# Ten further device guard header adoptions

Base `093c6dadfe96a32107a697565804b1f9aa8a2f1c`. Adopt the existing BFMEDX8DeviceLock header in ten more
sources. The bool-unlock header prerequisite was published previously and
counts as zero new tasks. No shared header or locking algorithm changes.
Native CodeView independently proves each prior guard is empty and one byte,
with no fields, bases, vptr, virtuals or statics. Some prior declarations use
struct; canonical class spelling is accepted only after checking every emitted
code/data section, external reference and relocation. Neither constructor
mangling nor the old inferred four-byte contract proves a retail class keyword
or allocation stride.

All 193 existing code/EH rows (17256 ledger-extent bytes), 285 external
code instances and 392 non-debug sections remain identical. Only the
registered header is added to each dependency set; all old physical paths and
native hashes are retained. Native acceptance retires exactly ten owning
queue keys. The initial thirteen private guard definitions fall to three: the protected VP6 wrapper is restored after strict preparation
refuses that territory; its queue key stays open. In addition,
W3DDisplay.cpp has a distinct imported/force-inline constructor declaration;
W3DFloorBuffer.cpp has a real pointer member. Neither is treated as empty.

W3DShroud.cpp participates only for its independent empty device guard. Its
private Shroud owner and automatic texture/counting/tree member lifetimes stay
unchanged and blocked as documented in LINK-225. BaseHeightMapInitHeightData.cpp
is processed after its separate Shroud header adoption. Counts in the two
cohorts overlap for this source and must not be added as unique native rows.

The native link pick was investigated before this cleanup: its dated missing
global report predates the already published forty-byte provider repair.
No duplicate provider or new link credit is claimed. No fresh census,
full-image link, runtime, memory/leak/crash/FPS or multicore gain is established.
No pins, aliases, TU moves, ledgers, baselines or ABI flags change.

- [Adopt canonical device guard in Rva00066A9ASubHeadB](b2-g01-device-guard-header-20261104-1105.md): 4 existing rows, one retired key.
- [Adopt canonical device guard in WaterRenderObjInit](b2-g02-device-guard-header-20261104-1105.md): 4 existing rows, one retired key.
- [Adopt canonical device guard in W3DDisplayReset](b2-g03-device-guard-header-20261104-1105.md): 3 existing rows, one retired key.
- [Adopt canonical device guard in Rva00131965TextureLoaders](b2-g04-device-guard-header-20261104-1105.md): 18 existing rows, one retired key.
- [Adopt canonical device guard in W3DTerrainVisualInit](b2-g06-device-guard-header-20261104-1105.md): 9 existing rows, one retired key.
- [Adopt canonical device guard in BaseHeightMapInitHeightData](b2-g07-device-guard-header-20261104-1105.md): 8 existing rows, one retired key.
- [Adopt canonical device guard in RenderableRiverArea](b2-g08-device-guard-header-20261104-1105.md): 13 existing rows, one retired key.
- [Adopt canonical device guard in W3DShroud](b2-g09-device-guard-header-20261104-1105.md): 25 existing rows, one retired key.
- [Adopt canonical device guard in W3DShaderManager](b2-g10-device-guard-header-20261104-1105.md): 32 existing rows, one retired key.
- [Adopt canonical device guard in GameWindow](b2-g11-device-guard-header-20261104-1105.md): 77 existing rows, one retired key.

## Scoped native receipt and preview

```text
link_check: preparing 10 explicit safe provider(s), no extra sources
Source claims: OK (10 sources, scoped byte-verified)
Data rows: OK (8 row(s) byte-verified)
Compile: 0 of 10 TU(s) (deps-cache: 10 current)
Funclet pins: 48 row(s) verified past a renumbered $L label
    $L687 (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualInit.cpp): $L687 was renumbered; verified parent EH data places $L903 at 0x0075FF57
    $L689 (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualInit.cpp): $L689 was renumbered; verified parent EH data places $L905 at 0x0075FF69
    $L690 (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualInit.cpp): $L690 was renumbered; verified parent EH data places $L906 at 0x0075FF73
    $L691 (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualInit.cpp): $L691 was renumbered; verified parent EH data places $L907 at 0x0075FF7D
    $L692 (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualInit.cpp): $L692 was renumbered; verified parent EH data places $L908 at 0x0075FF87
Functions: OK 193/193 matched across 10 source file(s)
String-ref verify: OK (11 literals + 2 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (28 compiler literals verified)
Import-ref verify: OK (28 named imports verified)
link_check: 10 explicit providers byte-verified with strict reusable receipts; census/index/status unchanged, LINK closure not yet checked
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/Rva00066A9ASubHeadB.cpp: LINKS  LINKED 114 -> 114 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 114)
Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp: LINKS  LINKED 2,933 -> 3,214 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 3,214)
Code/GameEngine/Source/GameLogic/Object/Behavior/RenderableRiverArea.cpp: LINKS  LINKED 734 -> 734 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 734)
  diagnostic  ?deallocate@?$allocator@UBfmeE12@@@_STL@@QBEXPAUBfmeE12@@I@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
  diagnostic  ?deallocate@?$_STLP_alloc_proxy@PAUBfmeE12@@U1@V?$allocator@UBfmeE12@@@_STL@@@_STL@@QAEXPAUBfmeE12@@I@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapInitHeightData.cpp: LINKS  LINKED 1,101 -> 1,101 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,101)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayReset.cpp: LINKS  LINKED 259 -> 259 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 259)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp: LINKS  LINKED 6,036 -> 6,036 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 6,036)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroud.cpp: LINKS  LINKED 1,889 -> 1,889 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,889)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualInit.cpp: LINKS  LINKED 557 -> 557 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 557)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjInit.cpp: LINKS  LINKED 297 -> 297 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 297)
Code/Libraries/Source/WWVegas/WW3D2/Rva00131965TextureLoaders.cpp: LINKS  LINKED 2,458 -> 2,458 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 2,458)
link_check: 10 of 10 link cleanly; LINKED 16,378 -> 16,659 bytes (3.5s)
```
