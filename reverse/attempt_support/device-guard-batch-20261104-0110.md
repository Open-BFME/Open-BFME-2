# Device guard header adoption after native unlock declaration repair

Base `94ebe7b612cfa4a6ac16f8d37ea28a8598edc437`. This continuation completes18 scoped tasks: one separately
committed canonical bool-unlock declaration repair, followed by17 individually
verified header adoptions. The canonical class has no storage, bases or vptr;
source-specific native CodeView verifies size1 in each adopted source. This
matches the actual registered header, not the older inferred4-byte contract
sample. No array or heap-allocation extent is inferred from that sample.

Private BFMEDX8DeviceLock definitions in the checked Code tree: 48->31.
Native header acceptance removes exactly17 owning queue keys. The adoptions
retain 129 existing code/EH rows (14467 ledger-extent bytes),
246 external code instances, and all373 non-debug object sections,
data and relocation destinations. Old resolved dependencies retain their
physical paths and native hashes; only the registered guard header is added.
The prior void/bool queue failure is addressed by the separate prerequisite,
not retried with unchanged inputs. No fields, method bodies, lifetime rules,
compiler flags, pins, aliases, identity records, TU ownership or gate code change.

The declaration prerequisite retains125 existing code/EH rows across its
original6 dependents. The dependency closure now has23 ledger sources, all
normally byte-verified and prepared with strict current receipts. These are
existing rows retained, not new authored coverage. The native preview below
is an index-based prediction, not a fresh census or complete-image link:

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
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/BfmeStrVM0Rva0025C4A4.cpp: LINKS  LINKED 83 -> 83 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 83)
Code/GameEngine/Source/Common/Rva00151744Clear.cpp: LINKS  LINKED 141 -> 141 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 141)
Code/GameEngine/Source/Common/Rva001517DEDtor.cpp: LINKS  LINKED 206 -> 206 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 206)
Code/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadarTerrainTexture.cpp: LINKS  LINKED 1,566 -> 1,566 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,566)
Code/GameEngineDevice/Source/W3DDevice/GameClient/HeightMapInitHeightDataRva000E1A39.cpp: LINKS  LINKED 780 -> 780 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 780)
Code/GameEngineDevice/Source/W3DDevice/GameClient/LookupTablePostEffect.cpp: LINKS  LINKED 443 -> 598 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 598)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva00111DB6PostFXLookupTable.cpp: LINKS  LINKED 342 -> 342 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 342)
Code/GameEngineDevice/Source/W3DDevice/GameClient/TerrainTracksRenderObjClassCreateBuffers.cpp: LINKS  LINKED 333 -> 333 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 333)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp: LINKS  LINKED 3,672 -> 3,672 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 3,672)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayInit.cpp: LINKS  LINKED 1,599 -> 1,599 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,599)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer_loadShrubsInVertexAndIndexBuffers.cpp: LINKS  LINKED 1,398 -> 1,398 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,398)
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainBackgroundDoPartialUpdate.cpp: LINKS  LINKED 1,932 -> 1,932 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,932)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp: LINKS  LINKED 2,849 -> 2,849 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 2,849)
  diagnostic  ?_M_clear@?$vector@DV?$allocator@D@_STL@@@_STL@@IAEXXZ  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
  diagnostic  ?deallocate@?$allocator@UBfmeE12@@@_STL@@QBEXPAUBfmeE12@@I@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
  diagnostic  ??0MathCoord2D@@QAE@ABV0@@Z  (codegen-like: 5 of 19 bytes differ from the majority copy; unreferenced, not a blocker)
  diagnostic  ?deallocate@?$_STLP_alloc_proxy@PAUBfmeE12@@U1@V?$allocator@UBfmeE12@@@_STL@@@_STL@@QAEXPAUBfmeE12@@I@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterDepthShaderGetter.cpp: LINKS  LINKED 148 -> 148 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 148)
Code/Libraries/Source/WWVegas/WW3D2/BfmeResetTextureBackend.cpp: LINKS  LINKED 384 -> 384 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 384)
Code/Libraries/Source/WWVegas/WW3D2/DynamicIBAccessWriteLock.cpp: LINKS  LINKED 338 -> 338 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 338)
Code/Libraries/Source/WWVegas/WW3D2/FXShaderGeometry.cpp: LINKS  LINKED 3,479 -> 3,479 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 3,479)
  diagnostic  ?deallocate@?$allocator@F@_STL@@QBEXPAFI@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
  diagnostic  ?deallocate@?$_STLP_alloc_proxy@PAFFV?$allocator@F@_STL@@@_STL@@QAEXPAFI@Z  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
  diagnostic  ??1?$_Vector_base@FV?$allocator@F@_STL@@@_STL@@QAE@XZ  (relocations differ from the majority copy, bytes equal; unreferenced, not a blocker)
Code/Libraries/Source/WWVegas/WW3D2/Render2DSentenceBuildNotCenteredBFME2.cpp: LINKS  LINKED 2,240 -> 2,240 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 2,240)
Code/Libraries/Source/WWVegas/WW3D2/Render2DSentenceDestructorBFME2.cpp: LINKS  LINKED 484 -> 484 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 484)
Code/Libraries/Source/WWVegas/WW3D2/RenderAssetSwitchTexturesBFME2.cpp: LINKS  LINKED 866 -> 866 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 866)
Code/Libraries/Source/WWVegas/WW3D2/Rva001171B0Cluster.cpp: LINKS  LINKED 209 -> 209 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 209)
Code/Libraries/Source/WWVegas/WW3D2/WW3D_Get_Render_Target_Resolution.cpp: LINKS  LINKED 205 -> 205 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 205)
Code/Libraries/Source/WWVegas/WW3D2/bfme2_mesh_material_pass.cpp: LINKS  LINKED 3,465 -> 3,465 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 3,465)
  diagnostic  ?Release_Ref@MeshModelClass@@QAEXXZ  (codegen-like: 11 bytes against the majority copy's 10; unreferenced, not a blocker)
  diagnostic  ??0Rva0007BB16Record@@QAE@PBDH@Z  (codegen-like: 26 bytes against the majority copy's 22; unreferenced, not a blocker)
link_check: 23 of 23 link cleanly; LINKED 27,162 -> 27,317 bytes (4.2s)
```

No TU merge is attempted. In particular, reference/shims/indexbuffercount/
dx8indexbuffer.h still has its older void unlock declaration and private guard;
that separate shim is outside this changed canonical-header dependency graph.
Its seed composition and any remaining DynamicIBAccessClass view agreement
remain prerequisites for a future supported merge. The historical obstacle
entry is updated without marking the broader merge obstacle cleared.

No full-game boot, memory/leak/crash/FPS or multicore improvement is proved.
Independent projects verify concurrently; operations using one repository's
source/cache/commit state remain sequential. No local model is used.

- [Adopt canonical device guard in W3DWaterDepthShaderGetter](b2-g01-device-guard-header-20261104-0110.md): 4 retained rows; one retired header key.
- [Adopt canonical device guard in Rva001517DEDtor](b2-g02-device-guard-header-20261104-0110.md): 8 retained rows; one retired header key.
- [Adopt canonical device guard in WW3D_Get_Render_Target_Resolution](b2-g03-device-guard-header-20261104-0110.md): 3 retained rows; one retired header key.
- [Adopt canonical device guard in Rva00151744Clear](b2-g04-device-guard-header-20261104-0110.md): 4 retained rows; one retired header key.
- [Adopt canonical device guard in HeightMapInitHeightDataRva000E1A39](b2-g05-device-guard-header-20261104-0110.md): 10 retained rows; one retired header key.
- [Adopt canonical device guard in Rva001171B0Cluster](b2-g06-device-guard-header-20261104-0110.md): 5 retained rows; one retired header key.
- [Adopt canonical device guard in BfmeStrVM0Rva0025C4A4](b2-g07-device-guard-header-20261104-0110.md): 4 retained rows; one retired header key.
- [Adopt canonical device guard in Rva00111DB6PostFXLookupTable](b2-g08-device-guard-header-20261104-0110.md): 8 retained rows; one retired header key.
- [Adopt canonical device guard in DynamicIBAccessWriteLock](b2-g09-device-guard-header-20261104-0110.md): 2 retained rows; one retired header key.
- [Adopt canonical device guard in BfmeResetTextureBackend](b2-g10-device-guard-header-20261104-0110.md): 3 retained rows; one retired header key.
- [Adopt canonical device guard in RenderAssetSwitchTexturesBFME2](b2-g11-device-guard-header-20261104-0110.md): 8 retained rows; one retired header key.
- [Adopt canonical device guard in Render2DSentenceDestructorBFME2](b2-g12-device-guard-header-20261104-0110.md): 8 retained rows; one retired header key.
- [Adopt canonical device guard in W3DRadarTerrainTexture](b2-g13-device-guard-header-20261104-0110.md): 10 retained rows; one retired header key.
- [Adopt canonical device guard in LookupTablePostEffect](b2-g14-device-guard-header-20261104-0110.md): 12 retained rows; one retired header key.
- [Adopt canonical device guard in bfme2_mesh_material_pass](b2-g15-device-guard-header-20261104-0110.md): 22 retained rows; one retired header key.
- [Adopt canonical device guard in Render2DSentenceBuildNotCenteredBFME2](b2-g16-device-guard-header-20261104-0110.md): 3 retained rows; one retired header key.
- [Adopt canonical device guard in W3DDisplayInit](b2-g17-device-guard-header-20261104-0110.md): 15 retained rows; one retired header key.

#### Outgoing native batch audit

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base 94ebe7b612cfa4a6ac16f8d37ea28a8598edc437; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: 2 source object(s) lack current receipts; first: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp
```

Inconclusive cases are carried forward to the next maintainer census. They
are unverified consumers, not evidence of a clean complete-image link.
