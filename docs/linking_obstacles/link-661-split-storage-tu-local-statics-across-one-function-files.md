### LINK-661: split storage: one retail global kept as several storages, mostly TU-local statics split across one-function files
Status: Open. Two instances repaired (the language buffer, below, and VertexLoc by the pointgr.cpp merge, 2026-11-13
seat halilkkaya-tl3 section at the end); the rest need TU merges. Updated: 2026-11-12 (seat
halilkkaya-lk103; consolidation dry runs by halilkkaya-cs96 at `4710051788e` and halilkkaya-cs99 at `11483448e79`, below); base `36e2968e498`, census
index `c31795c94c`.

halilkkaya-lk103; consolidation dry runs by halilkkaya-cs96 at `4710051788e` and halilkkaya-cs97, and two ScriptEngine.cpp
merges by halilkkaya-cs98 at `6effbe82406`, below); base `36e2968e498`, census index `c31795c94c`.

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
| `VertexLoc` 0x00DF708C (**repaired 2026-11-13**: one static in pointgr.cpp, tl3 section) | pointgr.cpp's global and PointGroupClassRva0017A890.cpp's static | Update_Location_Array (0x0017A890) writes through `&VertexLoc[0]` of its own static, which is never resized (null), while pointgr.cpp resizes and reads its own copy. The first point-group fill writes through a null vector. Tier 0 | the unit's own comment: retail codegen needs internal linkage, so merge into pointgr.cpp (both rows approved there) with VertexLoc static, along with its initializer (Rva007ABEF3ArgCtorInits.cpp) and atexit (Rva007B7280Siblings.cpp) users |
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

**2026-11-12 consolidation pass (seat halilkkaya-cs96, base `4710051788e`).** No merge landed; each boot-order merge
is walled by a tool refusal or a missing approval, measured with the supported dry runs (rows in
`reverse/re_attempts.log` under `tu-merge:<path>`):
- **pointgr.cpp (VertexLoc).** The seed's two "foreign" rows are ICF identities, not code to split: 0x00154BE0
  `VectorClass<float>::ID` and 0x00154E60 `VectorClass<Vector2>::ID` (24-byte folds of about 30 rows; pointgr.cpp's
  row comes first at each address). The map approves both for render2dsentence.cpp by T alone. `emission_held` keeps
  an implicit template instance in the seed only when its TU rests on C, so the merge reports the seed mixed;
  `--split` finds no spelled definition and `--emit-move` takes no template instances. Prerequisite: tooling
  (hold T-only template instances like C-only ones, the LINK-629 argument), then the DX8Wrapper, PointGroupClass and
  BfmeVciAnchorElem views, then VertexLoc file-static together with its initializer 0x007ACF20 and atexit 0x007B7400.
- **sortingrenderer.cpp (lists).** The missing approval comes from naming, not layout. In memory, `tu_map.build`
  with only 0x0012FE00 renamed to `?Insert_Triangles@SortingRendererClass@@SAXABVSphereClass@@IIII@Z` approves
  0x0012FE00 (Z) and 0x0012FD80 (T, 0x0012F190..0x0012FE00) for sortingrenderer.cpp. The SortingNodeStruct dtor and
  `??_G` stay proposed. Prerequisites: prove the parameter type, then run `rename.py function --respell` over the 11
  units that spell `BfmeSortingDispatchAt0012FE00`, then split Get_Sorting_Struct out of SortingNodeStructDtor.cpp.
- **W3DMouse.cpp (isThread).** `--split W3DMouseInitW3DAssets.cpp --for W3DMouse.cpp` carves all four isThread users
  and the datum. It refuses because the residual keeps the unused `extern unsigned int g_Va009E5DF8;`
  (`prune_unused_externs` is off when `extern_macro_tokens` cannot resolve `<d3d9.h>`), so the address_global total
  rises from 5 to 6. Past that, the static and the extern "C" isThread meet in one unit, so the split needs a
  `--prepared` W3DMouse.cpp. Prerequisite: name g_Va009E5DF8 or teach the extern pruning to accept system includes.
- **statistics.cpp (texture counters).** The splits are refused for data-identity debt that is this duplicate
  definition, and the residual loses `Find_Record_Texture`. Needs a `--prepared` split.

**2026-11-12 second consolidation pass (seat halilkkaya-cs97, base `4b82f841b5a`).** Still no merge; every
boot-order merge now waits on tooling or on a naming vote, not on source work this lane can do (rows in
`reverse/re_attempts.log` under `tu-merge:<path>`; the two tool refusals are recorded as `false-reject`):
- **W3DMouse.cpp (isThread).** Two prerequisites landed in W3DMouseInitW3DAssets.cpp (each 16/16 exact, link_check
  LINKS 3,416 B): the `g_Va009E5DF8` extern now sits at block scope in setRedrawMode, its one user, so the carve takes
  all five occurrences and no hatch total grows (`hatches_move True`); and freePolygonAssets (0x00098F43) is an
  ordinary out-of-line member, as in Zero Hour's W3DMouse.cpp, so the carve finds it. The split dry run now carves
  0x00099B6F, 0x00099DCC, 0x0009A04A, 0x000992B0, 0x00098F43 and the isThread datum and refuses none, but blocks on
  `residual_loses` 0x0006331F, 0x0007B261, 0x000852F7, 0x00085317: header-inline COMDATs (Rva0013101E ctor,
  CameraClass::Set_Projection_Type, Vector3::Find_X_At_Z/Find_Y_At_Z) only the carved bodies emit, approved for no unit
  or for the provisional, N-hinted `W3DDevice/GameClient/Vector3.cpp`. `--shatter` refuses earlier, on eight
  header_queue rows keyed to the donor. Next: tooling (riders for inline COMDATs only carved bodies emit), then a
  `--prepared` W3DMouse.cpp that reconciles the donor's private views with the seed's Zero Hour headers and keeps one
  static isThread.
- **sortingrenderer.cpp (lists).** The 0x0012FE00 rename has no canonical basis (zh_sweep places ZH's sphere overload
  nowhere; its `GGGG` spelling is not this `IIII` body), so it is an inferred respell needing two workers' votes, which
  this seat could not supply. The four callers that build the first argument build 12 bytes with no radius store, so
  BFME 2's parameter is likely centre-only (`const Vector3 &`), not Zero Hour's `SphereClass`. The stale alias pin
  `?Insert_Triangles@SortingRendererClass@@SAXABVSphereClass@@GGGG@Z` at 0x0012FE00, which made `--respell` refuse,
  named nothing any object used and is retired. Evidence split into target facts, donor facts and inferences:
  `reverse/attempt_support/sortingrenderer-0012fe00-signature-20261112.md`.
- **statistics.cpp (texture counters).** False reject: `--split` refuses Record_Texture and Record_Texture_End for
  data-identity debt keyed to their files, but that debt is the duplicate definition only the carve removes (the
  extern route fails, four recorded attempts). `--merge` reports both donors mixed only for their homeless `_$E`
  initializer/atexit rows, which docs/consolidation.md says go with their parent object.
- **pointgr.cpp (VertexLoc).** False reject recorded in the tooling lane's form (T-only ICF template instances held
  against the seed). No ledger route exists: render2dsentence.cpp's object defines neither `VectorClass<float>::ID` nor
  `VectorClass<Vector2>::ID`.

**2026-11-12 third consolidation pass (seat halilkkaya-cs99, base `11483448e79`).** The pointgr.cpp false reject is
fixed by the tooling commit "tu_skeleton: let the seed keep a T-bracketed template instance its TU cannot hold"
(`11483448e79`): the seed is no longer mixed. The merge of what the dry run accepts landed as "Merge 2 files into
pointgr.cpp (65 rows, ...)": it absorbs `Rva00179100Siblings.cpp` (0x00179100) only, 65/65 exact, link_check LINKS
12,013 -> 12,034 bytes. The VertexLoc split is **not** closed: `PointGroupClassRva0017A890.cpp` is still rejected.
Measured, in order:
- **Compile (persist.h C2146).** The donor includes `<d3dx9.h>`, `RenderStateStruct.h` and a private `DX8Wrapper`
  (inline `Get_Transform(int, Matrix4 &)`); the seed is built against d3d8 (`banked_segline/dx8wrapper.h`,
  `D3dx8math.h`). The two `PointGroupClass` views also differ: the donor includes canonical `PointGroupClass.h`
  (`flag01`, `friend Rva007B73C0`), the seed keeps its own ZH-shaped class (`BILLBOARD`, `friend ::Rva00912CF0`,
  `_Init`/`_Shutdown`, a `__declspec(noinline) inline` `rva00917920`). The dry run lists `adopt_first PointGroupClass`
  for the seed; the header_queue row cannot be taken by the lane ("defined inside a preprocessor conditional").
- **Linkage.** With `static VectorClass<Vector3> VertexLoc;` (and the forward `extern` dropped) the seed stays 64/64
  exact, so the merged unit can make it file-static. That removes the external symbol the hand-written initializer
  0x007ACF20 (`Rva007ABEF3ArgCtorInits.cpp`) and atexit 0x007B7400 (`Rva007B7280Siblings.cpp`) bind to. pointgr.obj's
  own initializer for it (`_$E32`, 26 B) has retail's shape, but its atexit (`_$E33`) is a 10-byte
  `mov ecx,VertexLoc; jmp ??1?$VectorClass@VVector3@@@@UAE@XZ` thunk, not 0x007B7400's 59-byte inlined destructor:
  the seed's decl-only `template <> VectorClass<Vector3>::~VectorClass();` (kept so the unit emits no /O2 `??_G`)
  stops the inline expansion. compressed_loc and transformed_loc have the same 10-byte atexits.
- **Prerequisites, in order:** the seed adopts canonical `PointGroupClass.h` (additive declarations there:
  `friend void Rva00912CF0();` and whatever else the seed's bodies need); the donor moves onto the seed's d3d8 /
  banked dx8wrapper world and stays exact alone; the Vector3 destructor inlines in the atexits so 0x007ACF20 and
  0x007B7400 can be rowed as pointgr.cpp's `_$E` pair (an `object-symbol=_$E<n>` row is no hatch, hatch_counters
  rule 9) while the `??_G` copy stays out; then the merge, re-verifying the 12000-byte body, whose match depends on
  temp numbering (31 dead ints, `reverse/attempt_support/rva17a890-2026-10-20.md`), in the merged context.
- **Merged-context probe (same base, scratch only).** pointgr.cpp's text with VertexLoc static and the 0x0017A890 body
  inserted at its retail position (`flag01` spelled `BILLBOARD`, everything else the seed's d3d8 world), compiled with
  pointgr.cpp's own command into a scratch object (not the build cache), gives an 11,820-byte body against retail's
  12,000, with 10,942 differing bytes. The first difference is structural, not temp numbering: retail builds
  `Vector3 scaled_offset[3]` through `??_H` with the out-of-line `??0Vector3@@QAE@XZ`, as the donor's own headers do,
  while the seed's `vector3_len_link.h` shim (`WWINLINE Vector3(void) {}`, force-inlined) constructs nothing. So
  the merge also needs one Vector3 view that keeps the seed's 64 rows and gives this body its out-of-line default
  constructor; that is a prerequisite ahead of the temp-numbering re-check above.

**2026-11-12 third consolidation pass (seat halilkkaya-cs98, base `6effbe82406`, census index `c6bfa84ddc`).** The
four boot-order merges above were not retried. Rows in `reverse/re_attempts.log` under `tu-merge:<path>`:
- **ScriptEngine.cpp (CanAppContinue latches 0x00DFE15C/D, `st_CurrentFrame` 0x00DFE160).** Merged
  ("Merge 19 files into ScriptEngine.cpp", 195 rows, -18 files; it needs the cs98 adoption commits for
  ThingTemplate in ScriptEngineSetPriorityDefault.cpp and BfmeOwnZC in ScriptEngineEnableDisable.cpp and
  ScriptEngineRva0020C3BBCallScript.cpp to land in an earlier push). At the base the same merge was refused by
  class_gate (false reject recorded): the merged unit gets no move credit because the seed's
  `#pragma comment(linker, "/alternatename:??1Rva00207E26Vector...")` trips `scope_code`'s blanket `'??' in raw`
  test, though `??1` is no trigraph. Putting the three donors on the canonical headers removed every private
  registered class from the merged text instead. The latch split is **not ended yet**. Object symbols after the
  merge: ScriptEngine.cpp defines `?g_00DFE15D@@3EA` and relocates `?g_00DFE15C@@3EA`;
  ScriptEngine_ctor.cpp still defines statics `_st_CurrentFrame`, `_scriptLastFrame`,
  `_scriptLogicContinuationLatch` and `_scriptClientContinuationLatch`, and the appendMessage forwarder a second
  `_st_CurrentFrame`. ScriptEngine_rva002047CF.cpp and ScriptEngine_updateClientDebugFrame.cpp (the latches'
  external halves) now read canonical ScriptEngine.h (`m_1A4D9`); a second merge ("Merge 2 files into
  ScriptEngine.cpp", 196 rows) took _rva002047CF.cpp, so the external writer of `?g_00DFE15D@@3EA` (0x002047CF)
  now sits in the unit that defines and reads it. ProviderGuard refuses _updateClientDebugFrame.cpp (beside its `g_00DFE15C` definition the merged
  copy of `?g_00DFE168@@3EA` differs).
  Prerequisite left: ScriptEngine_ctor.cpp, rejected C2504 `Rva002075F3`: its private view spells the whole
  object (templates, eight map headers, attack array, 20-player arrays) where canonical ScriptEngine.h is opaque
  from +0x1C to +0x19100; the ctor needs those members typed in the canonical header first. Then one static per
  latch in the TU, and the forwarder's `st_CurrentFrame` with it.
- **LivingWorldLogic.cpp** (not a LINK-661 split; consolidation queue). The first dry run of this TU accepts
  the seed plus 27 donors (211/211 exact), but class_gate refuses three verbatim-moved registered classes for the
  same `??` cause, here BfmeFiveArgCtorWI.cpp's `/alternatename:??1AsciiStringWI...` pragma. False reject
  recorded; the two adoptions that would avoid it (WindModuleInfo, Rva004F6093Holder) fail on bytes in the
  header queue. A tooling fix (refuse only the real trigraphs `??[=/'()!<>-]`, as `moved_bodies` already does)
  lands it as it is (-27 files).
- **W3DVolumetricShadow.cpp (`lastActiveVertexBuffer`).** Blocked on TU approval, not source: every user's main
  body is only proposed (renderShadows 0x000EFC7A Z, RenderMeshVolume 0x000F200A Z, RenderDynamicMeshVolume
  0x000F3D23/0x000F42FF/0x000F4AB7 Z and 0x000F2F5A/0x000F4003 C); only their funclets are approved.
- **W3DProjectedShadow.cpp (`drawEdge`/`drawStart`).** The reader W3DProjectedShadowDecalHelpers.cpp is mixed
  (0x001089EA proposed N for W3DDualProjectedShadow.cpp), so no merge takes it; the last dry run
  (re_attempts.log:103197) rejected the seed under every merged flag set. Prerequisite: place 0x001089EA.
- **MapUtil.cpp (`m_mapDX`/`m_mapDY`).** Not merged: the writer loadMap 0x00302F2B (MapUtilLoadMap.cpp) and the
  `extern "C"` definer (MapUtil_unk_...cpp, 0x00302E87/0x00302F1B) are only proposed, by C, for
  PlayerPosition.cpp; MapCacheAddMap.cpp (a reader) is approved for MapUtil.cpp but would bring an `extern "C"`
  declaration of the name MapUtil.cpp keeps static.


**2026-11-12 VertexLoc pass (seat halilkkaya-pg1, base `b8e28c36439`).** Nothing landed in `Code/`. Both routes
are measured, and the merge blocker is narrower than the pass above reported. Handoff with the full table:
`reverse/attempt_support/pointgr-vertexloc-merge-probe-20261112.md`. Rows are in `reverse/re_attempts.log`, on
0x0017A890 and on `tu-merge:Code/Libraries/Source/WWVegas/WW3D2/pointgr.cpp`.
- **Facts.** Retail has one datum, 0x00DF708C. 0x0017A890, the sizer 0x0017F150, 0x00179B50, 0x0017E920,
  0x007ACF20 and 0x007B7400 all name it. We have two: pointgr.obj's external `?VertexLoc@@3V?$VectorClass@VVector3@@@@A`
  (`_$E32` initializer, `_$E33` 10-byte atexit) and PointGroupClassRva0017A890.obj's static `_VertexLoc`
  (`_$E6`/`_$E7`, which have no rows). The hand rows 0x007ACF20 and 0x007B7400 bind pointgr.obj's symbol but sit
  in no `.CRT$XCU` table, so they never run.
- **Route A refused (extern), for one reason.** The donor with an `extern` or non-static VertexLoc differs in
  1,897 bytes from offset 0. Only internal linkage lets cl hoist `mov eax,[VertexLoc+4]` above
  `sub esp,0xB8`. Taking the address elsewhere in the TU (`Resize`, `Length`) keeps the static body exact,
  so no extern spelling can work.
- **Route B blocked (merge), on the seed's own hatch, not the Vector3 shim.** The seed's
  `vector3_len_link.h` constructor is the donor's `vector3.h` one. The merged body inlines `??_H` because
  pointgr.cpp's `bfmeVciAnchor` (`#pragma optimize("gsy")`) synthesizes it in /O1 shape. The donor alone with
  that anchor gives the same 11,772-byte miss; with the anchor but no pragma, it is exact. Removing the anchor
  keeps `??_H` out of line in 0x0017A890 but breaks 0x00179B50, Render and RenderVolumeParticle, and loses
  the hoist. Retail's `??_H` call counts (3 / 0 / 4 in 0x00179B50 / Render / 0x0017A890) come from neither
  shape. A probe copy of pointgr.cpp also needs `/O2 /arch:SSE /G7` spelled in its `// cl:` line, because
  flag_defaults applies them only to the ledger path. Without them the copy compiles x87 (9,136 bytes).
- **Bridge measure.** No source or ledger row changed, so no table moved and no unit's link status changed.
- **Cause ranking, unchanged in order.** sortingrenderer.cpp lists, then VertexLoc (now walled by the anchor
  conflict), then W3DMouse `isThread`, then the shadow renderers.
- **Next leads.** (1) A merged pointgr.cpp probe without the gsy anchor, in retail function order (Render and
  RenderVolumeParticle after 0x0017A890), with the approved destructor 0x00178ED0 and `_Init` 0x0017E210 in the
  same text. Look for 3 / 0 / 4 `??_H` calls with all 65 seed rows exact. (2) Then the canonical
  `PointGroupClass.h` adoption. (3) Then VertexLoc static, with 0x007ACF20 and 0x007B7400 rowed as pointgr.obj's
  `_$E` pair, the way the VertexDiffuse and VertexUV pairs already are. That needs the `VectorClass<Vector3>`
  destructor inline-visible.

**2026-11-13, seat halilkkaya-bt2 (CI diagnostic image `2e045b51115`, artifact `diagnostic-link-2e045b51115...`, base
0x2000000): the VertexLoc split in the linked image, read statically.** Nothing changed in `Code/`.
- Target facts: retail 0x0017A890 starts `mov eax,[0x00DF7090]` (VertexLoc+4, `.Vector`), the datum Render's sizer
  0x0017F150 resizes. Its triangle loops store through that pointer after `add eax,8`; the first store is
  `movss [eax-8],xmm0` at 0x0017CBF9.
- Image facts (capstone over `exit.exe`, names from `exit.map`): the body (`?rva009148C0@PointGroupClass@@...` at
  0x02723870) starts `mov eax,[0x02C07284]`, which is PointGroupClassRva0017A890.obj's static `_VertexLoc`
  (0x02C07280, constructed by that object's `_$E6` at 0x029949D0 and nothing else). pointgr.obj's
  `?VertexLoc@@3V?$VectorClass@VVector3@@@@A` is at 0x02C166DC; the sizer (`rva00914860`) and every other pointgr.cpp
  user name that one. The image's store at body+0x2369 (0x02725BD9) is retail's 0x0017CBF9 instruction. With the
  static never resized, `eax` is 8 there and the first point written goes to address 0.
- Reach (retail call graph, E8 sites): `DefaultModule<5>::doParticles` of FXParticleSystem (0x0055C478) calls
  PointGroupClass::Render (0x0017F400, call at 0x0055C844) and RenderVolumeParticle (0x0017F6E0, at 0x0055C81E);
  Render calls 0x0017A890 at 0x0017F695 right after the sizer, RenderVolumeParticle at 0x0017FA91;
  ParticleBufferClass::Render_Particles (0x001AEF10) also calls Render. So the first draw of one of these
  particle systems faults.
- Same objects at `2e045b51115` (`build/match`): 0x0017A890's relocation at offset 1 names `_VertexLoc`; pointgr.obj's
  `Rva00912CF0`, `rva00913AF0`, `rva00914860`, `_$E32` and `_$E33` name the external. The split is unchanged since
  `a1dee01711d` (2026-10-20).
- Consequence for the order of work: of the splits in the table above, this is the one whose first use faults (the
  SortingRenderer lists only leak), so its merge ranks first. The repair is still the pointgr.cpp merge with
  VertexLoc file-static (pg1's next leads above); no extern spelling can reproduce the body.

**2026-11-13 VertexLoc pass (seat halilkkaya-vl1, base `01da21cb5ba`).** The merged-context probe that pg1 asked for
(pointgr.cpp's text, no gsy anchor, VertexLoc static, the 0x0017A890 body; scratch objects under `build/vl1`, never
`build/match`) now compiles every seed row and the 12,000-byte body exact with retail's `??_H` pattern 3 / 0 / 4 / 0
(0x00179B50 / Render / 0x0017A890 / RenderVolumeParticle). What it took, target facts first:
- **`??_H` is inlined by size, per caller.** Micro tests: an /O2 `??_H` (50 bytes) stays a call in a large function,
  the 34-byte gsy copy is inlined everywhere; empty-constructor loops vanish once inlined. Retail's pattern (calls in the
  big 0x0017A890 and for 0x00179B50's named matrices, elided in Render) is the /O2 `??_H` with no anchor.
- **The rows_link matrix4 shim was the wall, not the anchor.** It declares the rows constructor and `Transpose`
  `__declspec(dllimport) __forceinline`; an imported inline body is not optimized on its own first, so its `Row[4]`
  construction keeps a `??_H` call wherever it is inlined (6 / 1 / 5 / 1). BFME 1's own matrix4.h (`WWINLINE`) elides
  them. Same shim with only those two declarations `WWINLINE`: exact too.
- **BFME 2's DX8Wrapper transform accessors.** Retail's out-of-line `Get_Transform` 0x000768FE is WORLD / VIEW /
  PROJECTION (DeviceProjectionMatrix) / default `Make_Identity`, and `Set_Transform(Matrix4)` 0x000A68A7 stores
  ProjectionMatrix and DeviceProjectionMatrix in PROJECTION and clears the identity bit before setting the changed bit.
  With Zero Hour's `Get_Transform` the body was 11,984 bytes (case 0 operand order, case 7); with BFME 2's it is exact.
  The inlined bodies' temporaries steer register choices in every caller: Render and RenderVolumeParticle then match
  only in Zero Hour's own spelling (`Vector4 result = view * loc` in the loop, `.X/.Y/.Z` stores), and 0x00179B50 only
  with BFME 2's `Set_Transform` too (18 bytes off without it). Probe table: `reverse/attempt_support/pointgr-vertexloc-merge-probe-20261112.md` (2026-11-13 section).
- **Landed as separate commits:** pointgr.cpp on BFME 1 matrix4.h, `BFME2_DX8WRAPPER_TRANSFORMS` in the banked shim,
  canonical PointGroupClass.h (header_queue row accepted) and no anchor (65/65); the donor on pointgr.cpp's header world
  without its private DX8Wrapper (1/1); VertexLoc file-static in pointgr.cpp with 0x007ACF20 / 0x007B7400 rowed as its
  `_$E32` / `_$E33` (the hand stand-ins retracted, tombstoned; 26 + 59 bytes moved to their owner in link_check).
- **The merge is still walled, by the provider guard, not by bytes.** With the donor's destructor visible too
  (`b5ef33d8ac9`) and the local index brought to HEAD (`link_check.py --update-index`; the census still held the
  stand-ins' references to the old external VertexLoc), `tu_skeleton.py --merge pointgr.cpp --dry-run` composes and
  byte-accepts PointGroupClassRva0017A890.cpp in pointgr.cpp, then refuses it: ProviderGuard "members disagree" and
  "path order" on the unreferenced inline COMDAT `?Get_Transform@DX8Wrapper@@SAXW4_D3DTRANSFORMSTATETYPE@@AAVMatrix4@@@Z`.
  Since the donor moved onto the banked shim (`90d495de95` on master) it emits that COMDAT (digest 6d4f27785efc, the
  /O2 BFME 2 body) and, first in path order, is the copy a path-order /OPT:NOREF link keeps; before, and again after a
  merge, Render2DClassRender's c4c6893c5c81 is. Census (retail) order is unchanged (fxshadernamespacesas,
  Render2DClassRender, the donor and pointgr.cpp all LINK). A `__declspec(dllimport)` Get_Transform emits no COMDAT but
  keeps the Transpose temporaries' `??_H` calls (6 / 1 / 5 / 1), so no source spelling avoids the copy.
- **That refusal is a false reject** (recorded as `false-reject` under `tu-merge:` in `reverse/re_attempts.log`). No
  relocation in any `build/match` object names the `_D3DTRANSFORMSTATETYPE` spelling outside `.debug` sections; its
  11 emitters (linegrp, mapper, pointgr, seglinerenderer, LineGroupClassRender, PointGroupClassRva0017A890,
  Render2DClassRender, Rva00177860Render, SimpleStreakRendererRenderStreak, SortingRendererBFME1,
  StreakRendererRenderStreak) only carry the unreferenced inline copy. Retail's row 0x000768FE is the other spelling,
  `?Get_Transform@DX8Wrapper@@SAXW4D3DTRANSFORMSTATETYPE@@AAVMatrix4@@@Z` (fxshadernamespacesas.cpp). exit_link's
  /OPT:NOREF places whichever copy it keeps, but nothing calls it, so `90d495de95` changed no code that runs and the
  merge would only return the kept copy to Render2DClassRender's. Source routes measured: pointgr.cpp with
  dx8wrapper.h above its size pragmas makes its copy equal the donor's (57/57 rows exact) but leaves the path-order
  clause; Render2DClassRender.cpp with BFME 2's Get_Transform makes its copy equal as well but breaks its Render row
  0x0011A040 (7,625 bytes against 7,476, 3,587 differ).
- **Next.** A narrow provider-guard rule: a COMDAT that no object references outside its debug sections (an inline
  copy nothing calls) has no kept copy that matters, in either order, with a regression test that a referenced one is
  still judged; `tools/tu_skeleton.py` was held by another seat (ancalgonn-swarm-toollane2) during this pass. Then
  the merge itself: one `_VertexLoc`, named by 0x0017A890, the sizer 0x0017F150, 0x00179B50, 0x0017E920 and the `_$E`
  pair. Until then the split remains (pointgr.obj's static and the donor's static), but no object names the external
  symbol any more and both copies are constructed by their own registered `_$E` pairs.

**2026-11-13, seat halilkkaya-tl3 (base `3a7e946d6af`, index brought to HEAD with `link_check.py --update-index`):
the VertexLoc split is repaired.** Two commits:
- **Tool.** The provider guard's refusal was the false reject recorded above. `tu_skeleton: the provider guard no
  longer judges a COMDAT nothing references` (landed as `3e7ea070ff`): a name no relocation of the link population
  names outside its debug sections (the census reference graph, its COMDAT edges and /alternatename targets, plus
  the replaced, replacing and unindexed objects read directly), all of whose definitions are discardable COMDAT
  copies, is not judged for members disagree (when the merged copy is one member's) or the order clauses; every
  referenced name is judged as before. Regression tests in `tools/tests/test_tu_skeleton_provider.py`.
- **Merge.** `tu_skeleton.py --merge Code/Libraries/Source/WWVegas/WW3D2/pointgr.cpp` absorbed
  PointGroupClassRva0017A890.cpp (rows 67 in the plan; `./build.sh` pointgr.cpp 68/68 exact). The other donors stay
  rejected for bytes as before (PointGroupClassDestructor.cpp, Vector2Resize.cpp, Vector2Equality.cpp). The merged
  object keeps pointgr.cpp's own copy of the unreferenced `Get_Transform` (`d0fe1357e6f5`); path order now keeps
  Render2DClassRender's `c4c6893c5c81`, as before `90d495de95`, and nothing calls it.
- **One definer (target fact: one datum, VA 0x00DF708C).** Before: two `_VertexLoc` statics, pointgr.obj's (named by
  0x00179B50, 0x0017E920, the sizer 0x0017F150 and the `_$E32`/`_$E33` pair 0x007ACF20/0x007B7400) and
  PointGroupClassRva0017A890.obj's (named by 0x0017A890 and its own `_$E8`/`_$E9`). After, over the 17,731 objects
  of exit_link's path order: exactly one `_VertexLoc` (pointgr.obj, static), named by 0x0017A890
  (`?rva009148C0@PointGroupClass@@...`), 0x00179B50, 0x0017E920, the sizer 0x0017F150 (both of its names) and
  `_$E32`/`_$E33`; the donor's leftover object in `build/match` is no link input. lk103's split-storage scan
  (rscan + split2 over the 82 rows at 0x00179xxx-0x0017Fxxx, 0x007ACF20, 0x007B7400) listed `SPLIT 0x009F7090`
  before and lists no split after: every reference to 0x009F708C/90/94 resolves to that one static.
- **Link preview.** `link_check.py`: before, pointgr.cpp LINKS 12,119 B and the donor LINKS 11,964 B; after, pointgr.cpp
  LINKS 24,083 B; Rva007ABEF3ArgCtorInits.cpp (422 B) and Rva007B7280Siblings.cpp (333 B) LINK unchanged. No other
  ledger object names the moved symbols.
- **Left for their owners.** `reverse/data_ledger.csv`'s 0x009F708C row still names the external
  `?VertexLoc@@3V?$VectorClass@VVector3@@@@A` (no object has defined it since `27e9b262733`), so data_check (shadow)
  reports `wrong-name _VertexLoc` for pointgr.cpp, as it did before the merge; the ledger is tool-written
  (`tools/data_ledger.py`), refreshed by the measurement cycle. The header_queue DX8Wrapper row moved with the donor
  to pointgr.cpp (the banked DX8Wrapper view).
- **Next.** The table's other splits, in order: sortingrenderer.cpp lists, then W3DMouse `isThread`.
