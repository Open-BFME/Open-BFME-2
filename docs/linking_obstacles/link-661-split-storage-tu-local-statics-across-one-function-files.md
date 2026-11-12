### LINK-661: split storage: one retail global kept as several storages, mostly TU-local statics split across one-function files
Status: Open. One instance repaired (the language buffer, below); the rest need TU merges. Updated: 2026-11-12 (seat
halilkkaya-lk103); base `36e2968e498`, census index `c31795c94c`.

Evidence / affected units: the survey in LINK-627's 2026-11-12 lk103 section (walker plus a relocation resolver);
`?Get_Sorting_Struct@@YAPAVSortingNodeStruct@@XZ` 0x0012FD80 in `reverse/re_attempts.log`.

**Problem.** Code that writes one copy and code that reads the other disagree at run time. Every row byte-matches,
because a DIR32 relocation's bytes are the same whichever symbol it names; data_check reports these in shadow mode
only. Static detection: resolve each relocation of a matched row the way the real link does (a TU-local definition,
the kept strong or COMDAT definer, else the live `/alternatename` target) and group the retail `.data`/`.bss`
addresses by storage identity (name, plus the object for a static). Over the LINK-627 walk at tier 5 (44,609
functions), 84 addresses have more than one identity:
- 32 are dead copies: the address-named globals of `Rva007B6880Thunks.cpp`, `Rva007B6A00AtexitThunks.cpp` and
  `GlobalChainCleanup.cpp` (also the `GlobalFlagClearers_*.cpp` guard clearers and `Rva007AEA2CArrayInits.cpp` tree-wide).
  Each owning TU registers its own compiler `_$E` atexit thunk or EH funclet for its static, so the rowed copies run
  on nothing (or, through the initializer bridge, only on their own copy).
- 31 are displacement artifacts: an array's end pointer or an indexed access whose displacement lands on the next
  global. Four of these hide real splits (marked below).
- 4 are a `__real@`/`??_C@` literal read where retail reads a writable `.data` global. Only the language buffer had a
  writer that runs (repaired); the three frame-rate floats' only writer, `Rva00238895SetFrameRates`, has no caller or
  pointer anywhere in the retail image.
- 17 are true splits. Tree-wide, 53.

**Runtime-relevant splits, boot order first** (tier from the walk; TU from `reverse/tu_map.csv`):

| storage (retail VA) | copies | effect | prerequisite |
|---|---|---|---|
| `sorted_list` 0x00DB6200, `clean_list` 0x00DB620C | statics in sortingrenderer.cpp and SortingRendererBFME1.cpp, plus SortingNodeStructDtor.cpp's `.bss` view of `clean_list`+4 | Get_Sorting_Struct (0x0012FD80) never reuses the nodes Flush_Sorting_Pool returns, so every sorted batch allocates a new 0x2A8-byte node (a per-frame leak; Deinit frees its own empty lists). Tier 0 | merge into sortingrenderer.cpp. The map approves Flush/Flush_Sorting_Pool/Deinit there; 0x0012FD80 and Insert 0x0012FE00 are only proposed for SortingNodeStruct.cpp, and these shared statics are evidence for sortingrenderer.cpp |
| `VertexLoc` 0x00DF708C | pointgr.cpp's global and PointGroupClassRva0017A890.cpp's static | Update_Location_Array (0x0017A890) writes through `&VertexLoc[0]` of its own static, which is never resized (null), while pointgr.cpp resizes and reads its own copy. The first point-group fill writes through a null vector. Tier 0 | the unit's own comment: retail codegen needs internal linkage, so merge into pointgr.cpp (both rows approved there) with VertexLoc static, along with its initializer (Rva007ABEF3ArgCtorInits.cpp) and atexit (Rva007B7280Siblings.cpp) users |
| W3DMouse `isThread` 0x00DE4B30 | W3DMouse.cpp static; W3DMouseInitW3DAssets.cpp `extern "C"` definition | the init path's thread flag and the draw path's disagree. Tier 2 | merge into W3DMouse.cpp (approved). Dry run: W3DMouseInitW3DAssets.cpp is mixed (4 rows elsewhere); MouseThreadClass and W3DMouse views to reconcile first |
| `lastActiveVertexBuffer` 0x00DEBCF4 | external in W3DVolumetricShadowRenderShadows.cpp; statics in W3DVolumetricShadowRenderMeshVolume.cpp and ...RenderDynamicMeshVolume.cpp | RenderShadows' per-frame reset does not reach the mesh renderers' caches, so a stale buffer pointer can skip SetStreamSource. Tier 3 | W3DVolumetricShadow.cpp (proposed only) |
| `drawEdgeX/Y`, `drawStartX/Y` 0x00DEC2DC..E8 | statics in W3DProjectedShadowRenderShadows.cpp and W3DProjectedShadowDecalHelpers.cpp (W3DProjectedShadow.cpp has a third, unused set) | the decal helpers never see the extents RenderShadows computes. Tier 3 | merge into W3DProjectedShadow.cpp (approved). Dry run: 17 classes to reconcile, 7 mixed donors |
| `m_mapDX/m_mapDY` 0x00DFF124/28 | MapUtil.cpp statics; `extern "C"` definitions in MapCacheAddMap.cpp/MapUtilLoadMap.cpp | getExtent (MapUtil.cpp) reads zero extents that loadMap/addMap wrote elsewhere (map cache, skirmish list). Not on the boot walk | MapUtil.cpp; loadMap 0x00302F2B is only proposed (PlayerPosition.cpp) |
| `g_00DEBE14`/`g_00DEBE2C` | ints in Rva000F1A32Ctor.cpp; retail reads `g_00DEBE0C`/`g_00DEBE24`+8 (the vectors' VectorMax) | the shadow manager ctor's "resize if smaller than 1000" test reads an int that never changes. Same result on the first construction. Tier 2 | name the vector field (`((char *)&g_00DEBE0C) + 8`) after checking codegen |
| ScriptEngine CanAppContinue latches 0x00DFE15C/D, `st_CurrentFrame` 0x00DFE160 | ScriptEngine_ctor.cpp statics; `g_00DFE15C`/`g_00DFE15D` in ScriptEngine*.cpp; a second `st_CurrentFrame` static in the appendMessage forwarder | the ctor's `= true` reaches only its own copies. Matters only with the script debug DLL loaded (`st_DebugDLL`). Tier 0 | ScriptEngine.cpp merge. Extern tested and failed: `??0ScriptEngine` stops matching (re_log row on 0x00208343) |

Also split, but benign or off the boot path: `theLogicRandomLogFile` (two statics, a debug log handle that stays
null), the Debug_Statistics texture counters, the GameSpy `piNextID`/`piSettingData` and `matchbotProfileID` pairs,
ConstGlobalGetters2.cpp's own copies of bfmedynamicvertexbuffer.cpp's statistics statics (its getters return 0),
and constant name tables bound twice (`AITargetTypeNames`, `TheDrawableIconNames`, `BfmeSaveLoadRegistrations`).

**Why not extern.** Making the SortingRenderer lists external in sortingrenderer.cpp and `extern` in the other two units
(SortingNodeStructDtor.cpp through a +4 view cast) breaks five rows: Deinit, Get_Sorting_Struct, Insert,
Insert_VolumeParticle and Flush. MSVC 7.1 /O2 schedules loads and allocates registers differently for an
internal-linkage global. The VertexLoc and W3DMouse units record the same finding in comments. A split where
retail's global was file-static therefore needs the users back in one TU (`tools/tu_skeleton.py --merge`; see
docs/consolidation.md). The extern recipe fits only when every copy is already external, as for the language buffer.

**Repaired.** "Read the language buffer, not the literal "English", in FileSystem's lang lookups":
FileSystem::openFile and doesFileExist pushed their own "English" literal where retail pushes the language buffer
0x00DD509C. GameEngine::init calls Rva00600665Set, which copies the configured language into that buffer. Both rows
are on the boot walk at tier 0. Bytes unchanged; one relocation per row now names `?g_00DD509C@@3PADA`.

**Next.** Do the merges above in boot order: sortingrenderer.cpp needs TU approval of 0x0012FD80/0x0012FE00 first,
pointgr.cpp needs the VertexLoc users. Re-run the survey (scripts in the LINK-627 section) after each merge.
