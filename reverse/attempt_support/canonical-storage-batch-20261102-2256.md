# 14 BFME2 storage adoptions and1 queue maintenance item(s)

Base `d41f899c6523ea356ddc9f90779eda2a8170094c`. 14 separately claimed source units replace private
storage definitions with existing registered headers. 1 other
item(s) refresh already-completed queue evidence without changing source.
Normal gates preserve 209 native function/EH rows, 29916 ledger-extent
bytes, 535 retained external code bodies/relocation lists and
29 named TU-local code definitions. No new native rows, names,
pins, aliases, shared headers or baselines are authored. No optimization/ABI
switch changes; the source-local include-root repair is recorded in its proof.
No native/authored-byte or runtime improvement is claimed.

- [Adopt canonical Vector3 in Rva0052B278Permuted](rva0052b278permuted-vector3-20261102-2256.md): 4 existing rows, 36 retained external definitions.
- [Adopt canonical Vector3 in LivingWorldBuildPlotIcon](livingworldbuildploticon-vector3-20261102-2256.md): 3 existing rows, 34 retained external definitions.
- [Adopt canonical Vector3 in BaseHeightMapGetMaximumVisibleBox](baseheightmapgetmaximumvisiblebox-vector3-20261102-2256.md): 2 existing rows, 8 retained external definitions.
- [Adopt canonical Vector3 in W3DPropBufferCtor](w3dpropbufferctor-vector3-20261102-2256.md): 9 existing rows, 18 retained external definitions.
- [Adopt canonical Vector3 in LightEnvironmentClass_CopyAssign](lightenvironmentclass_copyassign-vector3-20261102-2256.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Matrix3D in SiegeDockingBehaviorInitializeBones](siegedockingbehaviorinitializebones-matrix3d-20261102-2256.md): 8 existing rows, 18 retained external definitions.
- [Adopt canonical Matrix3D in W3DScriptedModelDrawNukeRender](w3dscriptedmodeldrawnukerender-matrix3d-20261102-2256.md): 5 existing rows, 7 retained external definitions.
- [Adopt canonical Matrix3D in W3DDisplayDrawSkirmishAIStats](w3ddisplaydrawskirmishaistats-matrix3d-20261102-2256.md): 1 existing rows, 11 retained external definitions.
- [Adopt canonical Matrix3D in Weapon_positionProjectileForLaunch](weapon_positionprojectileforlaunch-matrix3d-20261102-2256.md): 1 existing rows, 3 retained external definitions.
- [Adopt canonical Matrix3D in LivingWorldManagerCreateBeaconObject](livingworldmanagercreatebeaconobject-matrix3d-20261102-2256.md): 7 existing rows, 47 retained external definitions.
- [Adopt canonical Vector4 in W3DScriptedModelDraw](w3dscriptedmodeldraw-vector4-20261102-2256.md): 19 existing rows, 38 retained external definitions.
- [Adopt canonical Vector4 in ObjectDoXfer](objectdoxfer-vector4-20261102-2256.md): 11 existing rows, 30 retained external definitions.
- [Adopt canonical Vector4 in StandingWaterArea](standingwaterarea-vector4-20261102-2256.md): 45 existing rows, 50 retained external definitions.
- [Adopt canonical Vector4 in ActiveBody](activebody-vector4-20261102-2256.md): 73 existing rows, 164 retained external definitions.
- [Refresh completed STLport locale Microsoft-header queue key](stlport-localefacets-ms-header-queue-20261102-2256.md): 20 existing rows, 70 retained external definitions.

Each unit has its own before-object and normal/frozen checks. Storage adoptions
also have isolated private compiles and owning header acceptance. The already
completed Microsoft-header key is refreshed only through its scoped owner scan. Added/removed components have no
incoming retained runtime/data root; exact added-code profiles are independently
checked. Named statics are compared separately; generated EH labels belong to
the complete runtime-section (BFME1) or native parent EH (BFME2) checks.

Owning acceptance retires 14 source/class queue row(s); strict preparation and new-variant checks pass.

Unsuccessful trial, not counted as completion: [b2-06](b2-06-storage-prerequisite-20261102-2256.md). Original source untouched; claim released.

Unsuccessful trial, not counted as completion: [b2-10](b2-10-storage-prerequisite-20261102-2256.md). Original source untouched; claim released.

Bounded preview, not a fresh census or complete current selection:

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

Code/GameEngine/Source/Common/Rva0052B278Permuted.cpp: LINKS  LINKED 324 -> 324 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 324)

Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldBuildPlotIcon.cpp: LINKS  LINKED 316 -> 316 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 316)

Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapGetMaximumVisibleBox.cpp: LINKS  LINKED 745 -> 745 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 745)

Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferCtor.cpp: LINKS  LINKED 319 -> 319 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 319)

Code/Libraries/Source/WWVegas/WW3D2/LightEnvironmentClass_CopyAssign.cpp: LINKS  LINKED 435 -> 435 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 435)

Code/GameEngine/Source/GameLogic/Object/Behavior/SiegeDockingBehaviorInitializeBones.cpp: LINKS  LINKED 813 -> 813 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 813)

Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DScriptedModelDrawNukeRender.cpp: LINKS  LINKED 415 -> 415 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 415)

Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDrawSkirmishAIStats.cpp: LINKS  LINKED 520 -> 520 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 520)

Code/GameEngine/Source/GameLogic/Object/Weapon_positionProjectileForLaunch.cpp: LINKS  LINKED 186 -> 186 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 186)

Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldManagerCreateBeaconObject.cpp: LINKS  LINKED 628 -> 628 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 628)

  diagnostic  ?_M_bkt_num@?$hashtable@U?$pair@$$CBHPAVRva003FD14D@@@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHPAVRva003FD14D@@@_STL@@@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHPAVRva003FD14D@@@_STL@@@2@@_STL@@ABEIABU?$pair@$$CBHPAVRva003FD14D@@@2@@Z  (codegen-like: 26 bytes against the majority copy's 5; unreferenced, not a blocker)

Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DScriptedModelDraw.cpp: LINKS  LINKED 2,938 -> 2,938 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 2,938)

Code/GameEngine/Source/GameLogic/Object/ObjectDoXfer.cpp: LINKS  LINKED 3,418 -> 3,418 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 3,418)

Code/GameEngine/Source/GameLogic/Map/StandingWaterArea.cpp: LINKS  LINKED 3,292 -> 3,292 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 3,292)

Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp: LINKS  LINKED 8,323 -> 8,323 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 8,323)

Code/Libraries/Source/WWVegas/WWLib/stlport_LocaleFacets.cpp: LINKS  LINKED 6,113 -> 6,113 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 6,113)

link_check: 15 of 15 link cleanly; LINKED 28,785 -> 28,785 bytes (3.5s)
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

Immutable outgoing audit at `d41f899c6523ea356ddc9f90779eda2a8170094c` -> `2dc166aca94053d6a451a88366c0650f0aeb654a` before this documentation-only amendment, exit2:

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base d41f899c6523ea356ddc9f90779eda2a8170094c; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```
