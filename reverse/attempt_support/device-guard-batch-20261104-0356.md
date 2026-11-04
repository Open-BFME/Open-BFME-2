# Eighteen further device guard header adoptions

Base `9f09ad902069704754e50c9d5aec04ee0629a13d`. Retire18 more private empty BFMEDX8DeviceLock definitions using
the existing registered header. The bool-unlock declaration prerequisite was
already published in the preceding run; it is reused and counts as zero new
tasks here. This run makes no shared-header or callee declaration change.
Seven sources explicitly spell __cdecl; their existing declaration agrees with
the header's default convention and is preserved. Native CodeView independently
proves size1, no fields, bases, vptr, virtuals or statics in every adopted source.
No heap or array stride is inferred from the older inferred4-byte contract sample.

Each claimed source passes normal/frozen/header acceptance gates. All732
existing code/EH ledger rows (80860 ledger-extent bytes), 1157 external
code instances, and all1647 non-debug sections/data/relocations remain
identical. Only the registered header is added to resolved dependencies; every
old physical dependency path and native hash is retained. Native acceptance
removes exactly18 owning header queue keys. In the initial31-source inventory,
private definitions fall to13. The held W3DShroud.cpp was excluded.
No method body, object lifetime, ABI option, pin, alias, identity, ledger or
baseline changes. No new authored-byte coverage is claimed.

The native repair picker is empty. The current link picker serves W3DGameClient
and its already recorded newDrawable prerequisite. LINK-179/LINK-181 describe
the unsupported donor/native SubsystemInterface, factory and vtable composition;
no unchanged broad context trial is repeated. The device-guard family is a
supported independent cleanup following the already verified shared repair.

The index-buffer merge obstacle remains open: its separate older
reference/shims/indexbuffercount/dx8indexbuffer.h still has the old void
declaration/private guard. This run does not change that shim or perform a TU
merge. The published shared header is unchanged, so this batch's normal scope
is the18 adopted sources, not a new global header closure.

Native preview and current receipt results follow below. They are not a fresh
census, a full-image link or a game run. No memory/leak/crash/FPS/multicore gain
is established. Independent projects run concurrently; per-repository source,
cache and commit operations remain sequential. No local model is used.

- [Adopt canonical device guard in fxshaderasset](b2-g01-device-guard-header-20261104-0356.md): 8 retained rows, one retired key.
- [Adopt canonical device guard in dx8vertexbuffer](b2-g02-device-guard-header-20261104-0356.md): 10 retained rows, one retired key.
- [Adopt canonical device guard in fxshadersetup](b2-g03-device-guard-header-20261104-0356.md): 53 retained rows, one retired key.
- [Adopt canonical device guard in bfmedynamicvertexbuffer](b2-g04-device-guard-header-20261104-0356.md): 46 retained rows, one retired key.
- [Adopt canonical device guard in texture](b2-g05-device-guard-header-20261104-0356.md): 24 retained rows, one retired key.
- [Adopt canonical device guard in W3DTaint](b2-g06-device-guard-header-20261104-0356.md): 20 retained rows, one retired key.
- [Adopt canonical device guard in W3DRadar](b2-g07-device-guard-header-20261104-0356.md): 64 retained rows, one retired key.
- [Adopt canonical device guard in ww3d](b2-g08-device-guard-header-20261104-0356.md): 66 retained rows, one retired key.
- [Adopt canonical device guard in W3DTerrainBackground](b2-g09-device-guard-header-20261104-0356.md): 56 retained rows, one retired key.
- [Adopt canonical device guard in ParticleSys](b2-g10-device-guard-header-20261104-0356.md): 126 retained rows, one retired key.
- [Adopt canonical device guard in dx8wrapper](b2-g11-device-guard-header-20261104-0356.md): 235 retained rows, one retired key.
- [Adopt canonical device guard in Rva0007E12F](b2-g12-device-guard-header-20261104-0356.md): 3 retained rows, one retired key.
- [Adopt canonical device guard in Rva001F636C](b2-g13-device-guard-header-20261104-0356.md): 3 retained rows, one retired key.
- [Adopt canonical device guard in W3DVideoBufferAllocate](b2-g14-device-guard-header-20261104-0356.md): 2 retained rows, one retired key.
- [Adopt canonical device guard in BaseHeightMapLoadRoadsAndBridges](b2-g15-device-guard-header-20261104-0356.md): 3 retained rows, one retired key.
- [Adopt canonical device guard in W3DDisplayResetD3DDevice](b2-g16-device-guard-header-20261104-0356.md): 3 retained rows, one retired key.
- [Adopt canonical device guard in Render2DSentenceClass_Reset](b2-g17-device-guard-header-20261104-0356.md): 3 retained rows, one retired key.
- [Adopt canonical device guard in W3DVideoBufferCtorBfme](b2-g18-device-guard-header-20261104-0356.md): 7 retained rows, one retired key.

## Scoped native preview

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
Code/GameEngine/Source/Common/Rva0007E12F.cpp: LINKS  LINKED 76 -> 76 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 76)
Code/GameEngine/Source/Common/Rva001F636C.cpp: LINKS  LINKED 93 -> 93 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 93)
Code/GameEngine/Source/GameClient/System/ParticleSys.cpp: LINKS  LINKED 5,018 -> 5,018 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 5,018)
Code/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar.cpp: LINKS  LINKED 8,300 -> 8,300 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 8,300)
Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapLoadRoadsAndBridges.cpp: LINKS  LINKED 112 -> 112 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 112)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayResetD3DDevice.cpp: LINKS  LINKED 288 -> 288 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 288)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTaint.cpp: LINKS  LINKED 2,877 -> 2,877 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 2,877)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainBackground.cpp: LINKS  LINKED 13,514 -> 13,514 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 13,514)
  diagnostic  ??0TextureArgumentView@@QAE@ABV?$RefCountPtr@VTextureClass@@@@@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DVideoBufferAllocate.cpp: LINKS  LINKED 180 -> 180 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 180)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DVideoBufferCtorBfme.cpp: LINKS  LINKED 213 -> 213 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 213)
Code/Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass_Reset.cpp: LINKS  LINKED 183 -> 183 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 183)
Code/Libraries/Source/WWVegas/WW3D2/bfmedynamicvertexbuffer.cpp: LINKS  LINKED 6,860 -> 6,860 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 6,860)
Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.cpp: LINKS  LINKED 790 -> 790 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 790)
Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp: LINKS  LINKED 28,658 -> 28,658 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 28,658)
Code/Libraries/Source/WWVegas/WW3D2/fxshaderasset.cpp: LINKS  LINKED 1,007 -> 1,007 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,007)
Code/Libraries/Source/WWVegas/WW3D2/fxshadersetup.cpp: LINKS  LINKED 2,881 -> 2,881 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 2,881)
Code/Libraries/Source/WWVegas/WW3D2/texture.cpp: LINKS  LINKED 1,979 -> 1,995 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,995)
Code/Libraries/Source/WWVegas/WW3D2/ww3d.cpp: LINKS  LINKED 4,980 -> 4,980 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 4,980)
link_check: 18 of 18 link cleanly; LINKED 78,009 -> 78,025 bytes (3.4s)
```


#### Outgoing native batch audit

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base 9f09ad902069704754e50c9d5aec04ee0629a13d; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

Inconclusive cases are carried forward to the next maintainer census. They
are unverified consumers, not evidence of a clean complete-image link.
