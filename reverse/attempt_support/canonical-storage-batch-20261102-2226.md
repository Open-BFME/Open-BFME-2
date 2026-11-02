# 12 BFME2 canonical-storage adoptions

Base `92f12c3fc4e42305d6c26c1da9290c17cc5d20cd`. 12 separately claimed existing source units replace
private storage definitions with their existing registered canonical headers.
Normal gates preserve 26 native function/EH rows, 6134 ledger-extent
bytes, 141 retained external code bodies/relocation lists and
4 named TU-local code definitions. No new native rows, names,
pins, aliases, shared headers, compiler flags or baselines are authored.
No native/authored-byte or runtime improvement is claimed.

- [Adopt canonical Vector3 in LightEnvironmentClass_Set_Output_Ambient](lightenvironmentclass_set_output_ambient-vector3-20261102-2226.md): 1 existing rows, 2 retained external definitions.
- [Adopt canonical Vector3 in Matrix3D_Set_Matrix3_Vector3](matrix3d_set_matrix3_vector3-vector3-20261102-2226.md): 2 existing rows, 2 retained external definitions.
- [Adopt canonical Vector3 in Rva0007E6F6Rva0007E6F6](rva0007e6f6rva0007e6f6-vector3-20261102-2226.md): 1 existing rows, 2 retained external definitions.
- [Adopt canonical Vector3 in simpledynvec_vector3_add](simpledynvec_vector3_add-vector3-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Vector3 in BaseHeightMapBoundingBox](baseheightmapboundingbox-vector3-20261102-2226.md): 1 existing rows, 9 retained external definitions.
- [Adopt canonical Vector3 in BaseHeightMap_getMaximumVisibleBox_Rva00376D29](baseheightmap_getmaximumvisiblebox_rva00376d29-vector3-20261102-2226.md): 1 existing rows, 4 retained external definitions.
- [Adopt canonical Vector3 in DX8SetAmbient](dx8setambient-vector3-20261102-2226.md): 1 existing rows, 2 retained external definitions.
- [Adopt canonical Vector3 in BridgeGetBridgeHeight](bridgegetbridgeheight-vector3-20261102-2226.md): 1 existing rows, 7 retained external definitions.
- [Adopt canonical Vector3 in W3DVolumetricShadowCtor](w3dvolumetricshadowctor-vector3-20261102-2226.md): 2 existing rows, 10 retained external definitions.
- [Adopt canonical Vector4 in LocomotorRva001E9A00AerialMove](locomotorrva001e9a00aerialmove-vector4-20261102-2226.md): 4 existing rows, 31 retained external definitions.
- [Adopt canonical Vector4 in W3DModelDrawParticleBones](w3dmodeldrawparticlebones-vector4-20261102-2226.md): 9 existing rows, 66 retained external definitions.
- [Adopt canonical Matrix3D in ObjectGetSingleLogicalBonePosition](objectgetsinglelogicalboneposition-matrix3d-20261102-2226.md): 2 existing rows, 5 retained external definitions.

Each unit has its own before-object, isolated private compile, normal byte gate,
frozen-file check and owning header acceptance. Added/removed components have no
incoming retained runtime/data root; exact added-code profiles are independently
checked. Named statics are compared separately; generated EH labels belong to
the complete runtime-section (BFME1) or native parent EH (BFME2) checks.

Owning acceptance retires 12 source/class queue row(s); strict preparation and new-variant checks pass.

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

Code/GameEngineDevice/Source/W3DDevice/GameClient/LightEnvironmentClass_Set_Output_Ambient.cpp: LINKS  LINKED 29 -> 29 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 29)

Code/Libraries/Source/WWVegas/WWMath/Matrix3D_Set_Matrix3_Vector3.cpp: LINKS  LINKED 128 -> 128 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 128)

Code/GameEngine/Source/Common/Rva0007E6F6Rva0007E6F6.cpp: LINKS  LINKED 231 -> 231 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 231)

Code/Libraries/Source/WWVegas/WWLib/simpledynvec_vector3_add.cpp: LINKS  LINKED 65 -> 65 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 65)

Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapBoundingBox.cpp: LINKS  LINKED 146 -> 146 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 146)

Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap_getMaximumVisibleBox_Rva00376D29.cpp: LINKS  LINKED 32 -> 32 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 32)

Code/Libraries/Source/WWVegas/WW3D2/DX8SetAmbient.cpp: LINKS  LINKED 226 -> 226 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 226)

Code/GameEngine/Source/GameLogic/Map/BridgeGetBridgeHeight.cpp: LINKS  LINKED 710 -> 710 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 710)

Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowCtor.cpp: LINKS  LINKED 365 -> 365 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 365)

Code/GameEngine/Source/GameLogic/Object/LocomotorRva001E9A00AerialMove.cpp: LINKS  LINKED 1,662 -> 1,662 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,662)

Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawParticleBones.cpp: LINKS  LINKED 2,190 -> 2,190 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 2,190)

Code/GameEngine/Source/GameLogic/Object/ObjectGetSingleLogicalBonePosition.cpp: LINKS  LINKED 281 -> 281 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 281)

link_check: 12 of 12 link cleanly; LINKED 6,065 -> 6,065 bytes (3.3s)
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

Immutable outgoing audit at `92f12c3fc4e42305d6c26c1da9290c17cc5d20cd` -> `020388024b464022d7ac04756263f27f57184000` before this documentation-only amendment, exit2:

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base 92f12c3fc4e42305d6c26c1da9290c17cc5d20cd; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```
