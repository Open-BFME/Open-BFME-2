# 6 BFME2 canonical-storage adoptions

Base `6ce079924bc1f37e6870576a1ecbc151598e76b1`. 6 separately claimed existing source units replace
private storage definitions with their existing registered canonical headers.
Normal gates preserve 10 native function/EH rows, 3012 ledger-extent
bytes, 48 retained external code bodies/relocation lists and
2 named TU-local code definitions. No new native rows, names,
pins, aliases, shared headers, compiler flags or baselines are authored.
No native/authored-byte or runtime improvement is claimed.

- [Adopt canonical Vector3 in Rva00118AC0Finish](rva00118ac0finish-vector3-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Vector3 in Rva001049C7AddTriangle](rva001049c7addtriangle-vector3-20261102-1632.md): 3 existing rows, 9 retained external definitions.
- [Adopt canonical Vector4 in ObjectWorldspaceBestContactPoint](objectworldspacebestcontactpoint-vector4-20261102-1632.md): 1 existing rows, 8 retained external definitions.
- [Adopt canonical Vector4 in W3DDisplayDrawSkirmishAIStats](w3ddisplaydrawskirmishaistats-vector4-20261102-1632.md): 1 existing rows, 9 retained external definitions.
- [Adopt canonical Vector4 in W3DSailModelDrawCtor](w3dsailmodeldrawctor-vector4-20261102-1632.md): 3 existing rows, 12 retained external definitions.
- [Adopt canonical Vector4 in W3DShadowMapManagerTextureMatrix](w3dshadowmapmanagertexturematrix-vector4-20261102-1632.md): 1 existing rows, 9 retained external definitions.

Each unit has its own before-object, isolated private compile, normal byte gate,
frozen-file check and owning header acceptance. Added/removed components have no
incoming retained runtime/data root; exact added-code profiles are independently
checked. Named statics are compared separately; generated EH labels belong to
the complete runtime-section (BFME1) or native parent EH (BFME2) checks.

Owning acceptance retires 5 source/class queue row(s); strict preparation and new-variant checks pass.

Unsuccessful trial, not counted as completion: [b2-02](b2-02-storage-prerequisite-20261102-1632.md). Original source untouched; claim released.

Unsuccessful trial, not counted as completion: [b2-05](b2-05-storage-prerequisite-20261102-1632.md). Original source untouched; claim released.

Bounded preview, not a fresh census or complete current selection:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Code/Libraries/Source/WWVegas/WW3D2/Rva00118AC0Finish.cpp: LINKS  LINKED 138 -> 138 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 138)

Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva001049C7AddTriangle.cpp: LINKS  LINKED 819 -> 819 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 819)

Code/GameEngine/Source/GameLogic/Object/ObjectWorldspaceBestContactPoint.cpp: LINKS  LINKED 635 -> 635 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 635)

Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDrawSkirmishAIStats.cpp: LINKS  LINKED 520 -> 520 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 520)

Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DSailModelDrawCtor.cpp: LINKS  LINKED 686 -> 686 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 686)

Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowMapManagerTextureMatrix.cpp: LINKS  LINKED 206 -> 206 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 206)

link_check: 6 of 6 link cleanly; LINKED 3,004 -> 3,004 bytes (2.9s)
```

## Parallel and sequential execution

The two independent repositories use separate source trees, object caches,
ledgers and claim namespaces; their working processes can run concurrently.
BUILD_POOL=14 per repository, aggregate28 build workers on28 logical CPUs.
Within one repository, source installation, normal verification, queue/log
writes, staging and commits are serialized. Private compilations are safe to
parallelize only with distinct objects and stable shared inputs; they do not
authorize simultaneous shared-cache or ledger writes. Dependent canonical-header
changes precede consumers and require their own wider gate. Publications follow
each repository's native workflow and account clock. No local inference or GPU
job is needed. No serial-vs-parallel speedup benchmark is claimed.

Full engine link, gameplay and RAM/leak/crash/FPS gains remain unproven.

Immutable outgoing audit at `6ce079924bc1f37e6870576a1ecbc151598e76b1` -> `b1ec8d85b90f7921ed692f2aaabeb190770cae1b` before this documentation-only amendment, exit2:

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base 6ce079924bc1f37e6870576a1ecbc151598e76b1; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```
