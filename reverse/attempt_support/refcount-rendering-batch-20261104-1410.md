# BFME2 verified source batch

Base `a7d6d877db6f0b65e6827a0479c32093b5eb8d52`. 19 source tasks; 233 retained code/EH rows,
17059 summed ledger-extent bytes and 465 external code definitions.
These are existing matches, not new authored coverage.

Adopt the target-backed RefCountClass header in 19 distinct sources;
coupled FXShader::RenderingMethod projections also adopt their canonical
header where necessary. Counter+4/size8/slot0 and the inherited deleting slot1
are compiler-checked. The old dummy RenderingMethod slot1 would shift Begin
and later calls by4; the complete shared derived interface preserves slots
2/3/4/5/6. No shared header is edited and no new guessed API is introduced.
Existing inline base teardown definitions stay visible at their optimization
context. Every emitted external/local code body and relocation remains exact.

Some objects reorder their COMDAT sections when an inline destructor is
defined after its canonical declaration. The private graph comparison proves
a complete section bijection: raw section data, stable defined-symbol anchors,
COMDAT selection/association and every relocation edge; SafeSEH records are
resolved to their handler identities instead of unstable COFF symbol indexes.
The comparator passes identical/permuted positive controls and rejects a
one-byte negative control. This is read-only evidence; repository verifiers,
flags, pins, aliases and baselines are not changed.
Native owning acceptance retires 19 keys, each listed in local
bfme2-retired-header-keys.json. All other resolved dependency paths/hashes stay.
The original RTS3DSceneRenderOneObject remains outside this accepted batch:
its additional private RenderObjClass hierarchy needs a separate ABI repair.

Linking was reviewed first. W3DMouse's served BFME2 blocker is already fixed
upstream, so no credit is taken for it. BFME1's movement-provider prerequisite
remains documented with the refreshed donor. Native scoped dated prediction:

```text
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
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/WWVegas/WWLib/sharebuf_float_dtor.cpp: LINKS  LINKED 59 -> 59 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 59)
Code/GameEngine/Source/Common/Rva00072A08Ctor.cpp: LINKS  LINKED 20 -> 20 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 20)
Code/Libraries/Source/WWVegas/WWLib/sharebuf_vector2_copy_ctor.cpp: LINKS  LINKED 249 -> 249 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 249)
Code/Libraries/Source/WWVegas/WWLib/sharebuf_vector4_copy_ctor.cpp: LINKS  LINKED 249 -> 249 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 249)
Code/Libraries/Source/WWVegas/WW3D2/ShareBufferClassUnsignedCtor.cpp: LINKS  LINKED 174 -> 174 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 174)
Code/Libraries/Source/WWVegas/WWLib/sharebuf_unsigned_copy_ctor.cpp: LINKS  LINKED 175 -> 175 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 175)
Code/Libraries/Source/WWVegas/WWLib/sharebuf_vector3_copy_ctor.cpp: LINKS  LINKED 263 -> 263 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 263)
Code/Libraries/Source/WWVegas/WWLib/sharebuf_shader_copy_ctor.cpp: LINKS  LINKED 301 -> 301 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 301)
Code/GameEngine/Source/GameClient/System/FXParticleSystem/GpuDrawModuleDoParticles.cpp: LINKS  LINKED 787 -> 787 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 787)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBufferDrawRoads.cpp: LINKS  LINKED 962 -> 962 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 962)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBufferDrawBridges.cpp: LINKS  LINKED 1,083 -> 1,083 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,083)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterDrawRiverWater.cpp: LINKS  LINKED 1,984 -> 1,984 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,984)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DVegetationBufferBase.cpp: LINKS  LINKED 1,124 -> 1,124 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,124)
Code/Libraries/Source/WWVegas/WW3D2/fxshadersetup.cpp: LINKS  LINKED 2,881 -> 2,881 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 2,881)
Code/GameEngine/Source/Common/System/TBuff.cpp: LINKS  LINKED 729 -> 729 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 729)
Code/GameEngine/Source/Common/GapBodiesGE31.cpp: LINKS  LINKED 824 -> 824 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 824)
Code/GameEngineDevice/Source/W3DDevice/GameClient/FlatHeightMap.cpp: LINKS  LINKED 4,107 -> 4,107 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 4,107)
  diagnostic  ?setIsTerrain@W3DTreeBuffer@@QAEXXZ  (layout-like: 3 byte(s) differ from the majority copy, same length -- a stale private class view?; unreferenced, not a blocker)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowTextureDestructor.cpp: LINKS  LINKED 121 -> 121 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 121)
Code/Libraries/Source/WWVegas/WW3D2/MaterialPassClassCtorThunk.cpp: LINKS  LINKED 114 -> 114 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 114)
link_check: 19 of 19 link cleanly; LINKED 16,206 -> 16,206 bytes (3.3s)
```

This is not a fresh census or a full-image link. No game run, memory/leak/crash,
64-bit, FPS or multicore improvement is demonstrated. Independent projects
can verify concurrently; per-repository edits, cache writes and publication
remain sequential. BUILD_POOL14 each, no local model.

- [Adopt canonical RefCountClass in sharebuf_float_dtor](b2-r01-refcount-header-20261104-1410.md): 2 retained rows.

- [Adopt canonical RefCountClass in Rva00072A08Ctor](b2-r02-refcount-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical RefCountClass in sharebuf_vector2_copy_ctor](b2-r03-refcount-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical RefCountClass in sharebuf_vector4_copy_ctor](b2-r04-refcount-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical RefCountClass in ShareBufferClassUnsignedCtor](b2-r05-refcount-header-20261104-1410.md): 5 retained rows.

- [Adopt canonical RefCountClass in sharebuf_unsigned_copy_ctor](b2-r06-refcount-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical RefCountClass in sharebuf_vector3_copy_ctor](b2-r07-refcount-header-20261104-1410.md): 4 retained rows.

- [Adopt canonical RefCountClass in sharebuf_shader_copy_ctor](b2-r08-refcount-header-20261104-1410.md): 4 retained rows.

- [Adopt canonical RefCountClass in GpuDrawModuleDoParticles](b2-r09-refcount-header-20261104-1410.md): 4 retained rows.

- [Adopt canonical RefCountClass in W3DRoadBufferDrawRoads](b2-r10-refcount-header-20261104-1410.md): 5 retained rows.

- [Adopt canonical RefCountClass in W3DBridgeBufferDrawBridges](b2-r11-refcount-header-20261104-1410.md): 7 retained rows.

- [Adopt canonical RefCountClass in W3DWaterDrawRiverWater](b2-r12-refcount-header-20261104-1410.md): 6 retained rows.

- [Adopt canonical RefCountClass in W3DVegetationBufferBase](b2-r13-refcount-header-20261104-1410.md): 15 retained rows.

- [Adopt canonical RefCountClass in fxshadersetup](b2-r15-refcount-header-20261104-1410.md): 53 retained rows.

- [Adopt canonical RefCountClass in TBuff](b2-r16-refcount-header-20261104-1410.md): 20 retained rows.

- [Adopt canonical RefCountClass in GapBodiesGE31](b2-r17-refcount-header-20261104-1410.md): 55 retained rows.

- [Adopt canonical RefCountClass in FlatHeightMap](b2-r18-refcount-header-20261104-1410.md): 40 retained rows.

- [Adopt canonical RefCountClass in W3DShadowTextureDestructor](b2-r19-refcount-header-20261104-1410.md): 6 retained rows.

- [Adopt canonical RefCountClass in MaterialPassClassCtorThunk](b2-r20-refcount-header-20261104-1410.md): 3 retained rows.
