### LINK-619: vtable bridge refusals: deleting destructors rowed away from the TU that emits them first, and a stale data ledger
Status: Open (partly repaired). Updated: 2026-11-07; seats halilkkaya-lk38 (base `3d70a843d39`) and
halilkkaya-lk40 (base `4b2bb61eb1d`) and halilkkaya-lk57 (base `def612cde76`; clusters 2 and 3, last section), queue `reverse/vtable_bridge_queue.tsv` from real links `95341e20cc`
and `1d41894d2a`, census index `d707d2f53b` (lk40: `94d8ffa1ad`).

**Problem.** Besides multiple-kept-names (LINK-618), the bridge (`tools/vtable_bridge.py`) refuses tables
for three reasons the queue lists: strong-definition (134), no-kept-definition (421) and
target-not-winning-provider (516). A refused table is not bridged, so the first kept copy wins at run time,
and that copy is often one slot long.

**Measurement used here.** A read-only `vtable_bridge.plan()` over the current kept objects (the same input
list `exit_link.link_setup` builds: `object_inventory` minus `placement_objects`, runtime libraries as
archives, retail from `image_report.Retail`), run in a scratch script. Nothing is linked. On this tree with
the committed `data_ledger.csv`, it reproduces the published queue to within a few rows: 3,442 tables,
1,767 generated, 152 already correct, 1,523 refused (no-kept-definition 429, multiple-kept-names 402,
target-not-winning-provider 526, strong-definition 134).

**Cluster 1, repaired: deleting destructors rowed outside the approved TU that emits them first.**
- Shape: exactly one blocked slot, slot 0 (the scalar deleting destructor, once a `??_E` adjustor thunk).
  Its row sits in a donor unit: a destructor file, a constructor file, or an `EmitVtableTag` scaffold in a
  grab-bag. The class's own approved TU also emits that COMDAT with its vtable and comes first in link
  order. The bridge requires the ledger owner's object to be the winning provider, so it refuses the whole
  table.
- Root cause: `??_G` is compiler-generated wherever the vtable is emitted. Both units define it, and the
  ledger chose the donor as its owner.
- Fix: repoint the row into the approved TU with `tools/add_match.py NAME RVA SIZE TU
  --replace-existing`, which runs a build. Preconditions, checked for every row:
  1. the address is `approved` for that TU in a fresh in-memory tu_map rebuild (`tu_map.current_rows`;
     the committed map is stale);
  2. the TU's COMDAT has the donor's bytes and relocation targets (`??1Class`, `??3@YAXPAX@Z`);
  3. the TU links under the census.
  The TU's `// tu-skeleton:` placeholder for the row is rewritten in place on the same line. A scaffold
  block that no longer owns a row is removed, and a donor left with no rows is deleted.
- Selection: 39 tables in the queue have every blocked slot of this shape with the first provider being
  the approved TU file itself.
  - Done: 35. `e8a03bfcfe6` (proof: W3DStreakDraw, LANGameInfo, AptMessengerOnline; removes the
    scaffold LANGameInfoDeleter.cpp); `cb5d1217e42` (18 donors that define the destructor or constructor);
    `04f558fc9d2` (14 EmitVtableTag scaffolds, 13 blocks removed).
  - Simulation: target-not-winning-provider 526 -> 491 and generated 1,767 -> 1,802, exactly these
    tables. link_check stayed green throughout. Each unit keeps its status, and 28 bytes (8 for the
    thunk) move from donor to TU. Census bytes are conserved, except +28 where a row left the
    non-linking donor ProductionQueueHordeContainModuleDataDtor.cpp.
  - Remaining 4:
    - 0x007DA270 (Rva001DA2D5 into INIAudioEventInfo.cpp): the file is claimed by another seat.
    - 0x0086A314 SynchronizeGroupOrder, and 0x00870A5C/0x00870A70 in FadeInTextRender.cpp: the TU does not
      link under the census (its own `??_7` copy differs from the first). Moving the row there would lose
      28 census-linked bytes. `tu_skeleton.py --merge` of SynchronizeGroupOrder.cpp rejects all three
      pure donors on private views (`tools/tu_views.py` first).
  - Rva00426745 keeps its class block in OpaqueScalarDeletingDtorsB10.cpp. Its +0xC thunk 0x0042673D is
    rowed there, and a fresh map only proposes that address for BfmeStringRecord00426A5B.cpp.
- Related, not done: about 24 more tables whose blocked slot's owner and first provider are both
  one-function donors of the same approved TU (a constructor file before a destructor file). There the TU
  file is not the provider, so a row move is not enough. They clear with the TU merge once the private
  views reconcile (examples: Weapon, WeaponSet, Team, Player's Rva002AC340, GameEngine, ai.cpp's
  Rva002FED8D, OilSpillUpdate, SiegeEngineContain, TransportContain's horde tables).

**Cluster 2, analysed: no-kept-definition is a stale `reverse/data_ledger.csv`.**
- The bridge takes its table names only from data_ledger.csv (`table_rows`). The committed file was last
  regenerated on 2026-10-09 (`334ccb560e4`). `tools/data_ledger.py --out <scratch>` from current objects
  gives every one of the 421 queued tables a current name:
  - 311 get exactly one kept `??_7`, for example 0x007C16C4 `??_7Rva00040F1E@@6B@` -> `??_7Mutex@@6B@`;
  - 84 get several (placeholder/real splits for LINK-618's method);
  - 26 get a strong or non-vtable name (hand-built arrays, see cluster 3).
- The simulation with the fresh ledger: no-kept-definition 429 -> 0, multiple-kept-names 402 -> 839,
  strong-definition 134 -> 146, target-not-winning-provider 526 -> 579, generated 1,767 -> 1,987, already
  correct 152 -> 188. Total refusals rise 1,523 -> 1,602, because the fresh ledger exposes every name now
  bound at a table.
- Not committed here. A regeneration rewrites the whole cache: 21,901 -> 34,417 addresses, 726 vtable
  rows renamed. data_check, the data sweep and rename.py's `--fold` evidence also read it. The precedents
  (`d1bae008b74`, `334ccb560e4`) went in as their own Verifier-Change commits. Recommend one, ahead of
  further LINK-618 folds: `--fold` refuses on stale ledger names, as the AI-state folds did.

**Cluster 3, analysed: strong-definition.**
- 87 of 134 are FXParticleSystem module templates (owned by another cluster; not touched).
- The other 47 are hand-built vtables defined as strong data:
  - `_vtbl_00Cxxxxx` / `vtbl_00BFxxxx` arrays of `__identifier` slot names in module constructors
    (HordeNotifyTargetsOfImminentProbableCrushingUpdateCtor.cpp, BridgeBehaviorCtor.cpp,
    StancesBehaviorCtor.cpp, ...);
  - address-named `?g_...@@3QBQBXB` / `?vftable_0112xxxx@@3HA` tables;
  - `R2DataXXXXXXXX` ints standing in for a vtable pointer (R2ZeroingConstructors.cpp, Radar.cpp).
- Each needs the real class view whose compiled table names those slots, which is header-lane work per
  class (LINK-617 covers the unrelocated arrays). Not homogeneous enough for one fix.

**Cluster 4, analysed: target-not-winning-provider by inline COMDATs.**
- The largest group is RenderObjClass's header-inline virtuals: BaseHeightMapConstructor.obj is the first
  provider of 519 blocked slot references, including the ICF-shared `?_bfme_ro_v50@RenderObjClass` that
  blocks 27 unrelated single-slot tables. STLport facets and VectorClass instantiations follow.
- These copies come from headers in many TUs, so no ledger owner can be first in link order.
- Possible fixes:
  - a bridge rule that accepts a first provider whose COMDAT bytes and relocations equal the owner's (a
    `Verifier-Change` to the Link lane's tool, not done here);
  - header adoption that stops the extra emissions.

**Next check.** The next published real link's `vtable_bridge_queue.tsv` should no longer list the 35
tables as target-not-winning-provider (they should be bridged). The `vtables_bridged` count rises by about
35 as refusals turn into generated copies. Neither is measured yet.

Clearance: none claimed (no new real link measured). Census confirmation: none claimed.

2026-11-06, SynchronizeGroupOrder prerequisite (base `c1b6ebfd3a`): private views explain the refused approved merge and selected-table conflict. The constructor seed emitted one slot; retail C6A314 has fourteen. Six native constant/passthrough callbacks are now supplied as independently verified real ICF bodies in the existing seed, with14/14 rows and four EXACT EH graphs retained. No pin/alias added. This is a dependency, not a table clearance: a coupled fourteen-slot view and supported virtual-clone reconciliation, then the approved merge and current provider-selection checks, remain. [Native table and proof](../../reverse/attempt_support/synchronize-group-order-native-table-20261106/README.md).

Same pass, full-view repair: the four sources now agree on the complete14-slot ABI view. Supported rename.py --virtual proves clone5469FD at slot13 and carries its handler/funclet metadata. Normal20/20 and five EXACT EH graphs pass; both emitted tables are56B and all14 relocation targets independently equal native. Preview at d707d2f53b now gives4/4 LINKS, cohort259->521B (seed0->262B). Approved donor merge follows; actual image selection/runtime and census confirmation remain pending. The related canonical GroupOrder header's enum/return-type reconciliation remains separate.

Same pass, approved merge: all three donors are absorbed by tu_skeleton.py after the documented current-object index refresh clears the stale nonvirtual-name/table evidence. Three source files disappear; all20 rows and five EXACT EH graphs remain, and the merged table's14 pointers again equal native. The guard passes, normal/private composed facts agree, and no donor debt/header/hatch key is lost. The merged521B preview conserves the repaired cohort's521B. The tooling/path audit finds no independent active consumer edit; the mixed GroupOrderClassNames.cpp donor stays. This repairs the source/table prerequisites of the earlier SynchronizeGroupOrder exception; actual next-image selection and runtime verification remain open. [Composition and audit](../../reverse/attempt_support/synchronize-group-order-native-table-20261106/README.md).

Published as `d117bf74a1`, `0a1151cb9e` and `67435ce87e` on2026-11-06. The normal pre-push hook verified20/20 and five EXACT EH graphs and proved no remaining old-clone consumer among17996 units. Its broader audit stays **INCONCLUSIVE**: provider index faee62b0b2, actual outgoing base7d5bb0f61e8f0802df8a6530171c18316e112468, four consumer objects without current receipts (first ChangeStanceGroupOrder.cpp). Carry those consumer/selection checks into the next census and real image; no broader link/runtime clearance is claimed. The push tool rebased and reused verification receipts after a lost race, then landed on its second attempt.

**2026-11-07, seat halilkkaya-lk40 (base `4b2bb61eb1d`): the twin rule re-measured, and weak-external thunks.**
- The published queue (real link `1d41894d2a`, 488 target-not-winning-provider) predates the twin rule
  (`fad073e21b1`, `b4c05ad2fe5`): neither commit is an ancestor of `1d41894d2a`. The same read-only
  `vtable_bridge.plan()` simulation over the current kept objects (full `./build.sh` green) gives
  generated 4,256, already correct 264, refused 297: target-not-winning-provider 88, strong-definition 134,
  omitted-target 33, ambiguous-table-name 28, no-kept-definition 8, unrowed-target 5,
  ambiguous-target-name 1, multiple-kept-names 0.
- No remaining refusal has LINK-619's shape (first provider = the slot row's approved TU). The
  "about 24 tables" above (Weapon, WeaponSet, Team, Rva002AC340, GameEngine, Rva002FED8D, OilSpillUpdate,
  SiegeEngineContain, TransportContain's horde tables, ...) no longer refuse: their donor copies are
  byte-and-relocation twins (checked per slot), so the twin rule bridges them without a merge.
- The 88, by what makes the earlier copy fail the twin check (per blocked slot):
  - 48 tables: a `??_EX@@W..` adjustor thunk (`sub ecx,N; jmp ??_EX@@UAEPAXI@Z`) whose jump target is a
    weak external (`IMAGE_SYM_CLASS_WEAK_EXTERNAL`, default `??_GX`). `comdat_body` refused every
    non-external relocation target. **Repaired**: `tools/vtable_bridge.py` now compares such a target by
    name plus its IMAGE_WEAK_EXTERN default and characteristics (the linker resolves a name once for the
    image, so equal weak relocations reach the same code). Simulation: target-not-winning-provider
    88 -> 40, generated 4,256 -> 4,300, already correct 264 -> 280, no table lost or newly refused.
    Examples: `??_ETeam@@O3AEPAXI@Z` (TeamCtor.cpp first, TeamDeleter.cpp owner), the eight
    `Rva0056A..`/`Rva0056B..` screen tables, ScriptEngine/PlayerList/SidesList/GameState's `WM@` thunks,
    five FXParticleSystem module-template tables (bridged by the tool rule only; no FXParticleSystem
    source touched).
  - 29 tables: alignment only. The copies have equal bytes and relocations, but one object is built `/O1`
    (`IMAGE_SCN_ALIGN_1BYTES`, 0x60101020) and the other `/O2` (`ALIGN_16BYTES`, 0x60501020). 20 are
    RenderObjClass-derived tables whose first provider of six header-inline virtuals
    (`Get_Bounding_Sphere`, `Get_Bounding_Box`, `Get_Current_LOD`, `_bfme_ro_flag111/113/115`) is
    BaseHeightMapConstructor.cpp (`/O1`), owners hlod.cpp and distlod.cpp; the rest are
    `Get_ObjectScale` (U4GlobalGuardedNotifies.cpp), VectorClass/SimpleVecClass deleting destructors,
    `??_GBucket`, `??_GW3DShroudMaterialPassClass`, `??_G?$basic_ios`, `Get_Vertex_Array`. The twin
    rule's tests refuse a flags (alignment) difference on purpose; not changed here. Proposal for the
    Link lane: compare flags without `IMAGE_SCN_ALIGN_MASK` (0x00F00000), which only moves where the
    linker places the kept copy.
  - 6 tables: different bytes; the first provider's private view compiles another body (for example
    PendingSurfaceStructResize.cpp's `??_G?$VectorClass@UPendingSurfaceStruct..` calls an out-of-line
    `??1` where retail's 93-byte copy in render2dsentence.cpp inlines it; MaterialCollectorClassCtor.cpp,
    Rva0040DB52Ctor.cpp, the two Fesl browser owners, PoolDeleteDeletingDtors01.cpp). These need the
    first provider's view reconciled with the owner's.
  - 5 slots: EH bodies with local relocations and loaded `.xdata$x`/`.text$x` associative sections
    (STLport `money_get::do_get`, `basic_filebuf::seekoff`, `VectorClass<Vector3/Vector4>::Resize`),
    which no twin check can compare; their owner must be the first provider.

- Verification of the tool change: 69 bridge tests, nine of them new (a weak-thunk twin; refusals for a
  different default, different characteristics, a missing aux record on one or both sides, a non-external
  default, aux bytes on a non-weak target, another weak name, and plain against weak); each of the seven
  new guards fails a test when removed. 156 bridge/exit-link tests pass. Next check: the next real link's `vtable_bridge_queue.tsv`
  lists these 48 tables (0x007C5320 ... 0x00879594) as bridged or already correct, not refused.

**2026-11-07, lk40 continued: source repairs for the byte-difference and EH-copy slots.** Each is its own
commit, verified by `./build.sh`, find_declared_unmatched, scoped DIR32, an object A/B of every emitted
`??_7` (unchanged unless noted) and link_check over every unit that defines or references the class's
symbols (no unit changed status). The simulation after each: target-not-winning-provider 40 -> 36.
- 0x008EAED0 (Apt value classes, 15 slots; names AptValue, RvaAptValueBase, Rva006DE350,
  BfmeAptValue006DCD20): `??_GRva006DE320` (0x006DE320) re-homed with `add_match.py --replace-existing`
  from the grab-bag PoolDeleteDeletingDtors01.cpp into AptValue.cpp, its approved TU (fresh in-memory
  map); the grab-bag held no other row and is deleted, so its non-retail `??_GRva006DE350` copy (first in
  link order) is gone. Its code-identity key transfers to AptValue.cpp (the finding remains:
  `??_GRva006DE320` calls `??1Rva006DE320`, a pinned twin name of 0x006DE350, not the row's own symbol).
  link_check 10/12 (AptValue.cpp and Rva006CBF40Deferred.cpp did not link before either).
- 0x007D3C48 (VectorClass<PendingSurfaceStruct>): PendingSurfaceStructResize.cpp no longer explicitly
  instantiates the vector constructor (rowed in render2dsentence.cpp), so it stops emitting the vtable
  and a `??_G` calling `~VectorClass` out of line; Render2DSentenceDestructorBFME2.cpp declares the
  `ID(const T *)` specialization beside the other three, dropping its `return 0` stub. 15/15 link.
- 0x007D4628 (VectorClass<VertexMaterialClass *>): MaterialCollectorClassCtor.cpp's private template
  now spells vector.h's members and inline destructor/Clear and includes `<new>`, so its `??_G` equals
  matinfo.cpp's 0x0016FF30. It also emits `??_7VectorClass<ShaderClass>` and its `??_G`, both equal to
  matinfo.cpp's. 14/14 link.
- 0x007D4EB4 (VectorClass<Vector4>): Rva007B7280Siblings.cpp declares `Resize` for Vector3 and Vector4
  as specializations, like its operator==/ID, so its /O2 EH copies (uncomparable: local relocations,
  loaded `.xdata$x`) leave the link. 13/13 link.

**Remaining target-not-winning-provider after lk40 (36, simulation at lk40's last commit).**
- 20 RenderObjClass-derived tables (RenderObjClass, MeshClass, CameraClass, LightClass,
  ParticleEmitterClass, CompositeRenderObjClass, Animatable3DObjClass, Box/AABox/OBBoxRenderObjClass,
  Null3DObjClass, SegmentedLineClass, Line3DClass, StreakLineClass, ParticleBufferClass,
  TerrainTracksRenderObjClass, BaseHeightMapRenderObjClass, SimpleDynVecClass<float>, two placeholders).
  Each has 7 blocked slots: the six alignment-only inline virtuals above, and slot 93
  `?Set_ObjectScale@RenderObjClass@@UAEXM@Z`, an ambiguous-target-name: the gen-alias row 0x005AD93A in
  collect.cpp carries `object-symbol=?Set_ObjectScale@RenderObjClass@@UAEXM@Z`, but retail's bytes
  there store at +0x4C (`f3 0f 11 41 4c`) where RenderObjClass::Set_ObjectScale (0x0006CEBF, rowed in
  RenderObjCopy.cpp) stores at +0x48, and it sits in the AI code region between
  Pathfinder::setDebugPathPosition and AIBase. It is another class's float setter. A what-if that ignores
  alignment bits moves these 20 tables to ambiguous-target-name; with the gen-alias recovered under its
  own name as well they would bridge. Retail keeps the /O1 copies of all these RenderObjClass inlines in
  one block (0x0006CE71..0x0006D03E) beside BaseHeightMapRenderObjClass's code; the six rows are owned
  by /O2 units (hlod.cpp, distlod.cpp) and their addresses have no approved TU (inline/displaced), so
  this pass did not move them.
- 9 more alignment-only tables, where the first provider's flags are fixed by its own matched rows:
  `Get_ObjectScale` x3 (U4GlobalGuardedNotifies.cpp), `Get_Vertex_Array` (W3DBridgeBuffer.cpp),
  VectorClass<int> (Render2DSentenceAllocateSurfaceBFME2.cpp), VectorClass<StringClass>
  (INIStatsRecordTextures.cpp), Bucket (BucketDtor.cpp), W3DShroudMaterialPassClass (W3DScene.cpp),
  SimpleVecClass<float> (streak.cpp), VectorClass<Vector3> (Rva007B7280Siblings.cpp, which must emit the
  vtable for its teardowns; its Resize slot's first copy is now vector_class_vector3_ctor.cpp's EH body).
  The ignore-alignment what-if clears four of them outright (Get_ObjectScale x3, Get_Vertex_Array).
- STLport EH bodies (not touched: the STLport 4.6 move is another lane): 0x007BB9D8 `money_get::do_get`
  x2 (stlport_money_get.cpp first), 0x007BBD50 `basic_filebuf::seekoff`
  (FstreamDefaultProtectionNameCtors.cpp first). The same decl-only specialization would hand them to
  their owners.
- Different bodies, not repaired: 0x008394CC `??_GRva0040DB52` (the constructor unit is built /Oy- for
  its own row and emits a framed copy; retail's 0x0040E09B follows that constructor directly, approved
  TU only proposed: ArmySummary.cpp), 0x008E3D14/0x008E3D28 Fesl browser owners (the constructor units'
  views lack the base class and inline destructor that Y2FeslBrowserDestructors.cpp's rows inline; the
  addresses have no approved TU).

**2026-11-07, seat halilkkaya-lk57 (base `def612cde76`): clusters 2 and 3 repaired in the tool and the ledger.**
- Cluster 3 (strong-definition), the bridge side: `b643f770dc9` refuses a strongly defined name alone instead of its
  whole retail address. The other names there still pass every existing rule on their own copies (SELECT_ANY only,
  no shared or prefixed section, no common or absolute copy, unique address, every slot resolved to the winning or twin
  provider); 16 regression cases cover the per-name bridge and these neighbours. The strong arrays themselves still need
  their real class views (LINK-617), but they no longer hide the compiled tables at their addresses.
- A data_rows owner hides a table: `fa1e73a5667`. Regenerated, the ledger names 36 retail tables `global`, because a
  verified `reverse/data_rows.csv` owner (a hand-built strong array) is their canonical name. The bridge took only
  `kind=vtable` rows and would have lost the 58 compiled `??_7` names bound there; a `global` row binding a `??_7` name
  is now a table.
- Cluster 2 (stale ledger): `9bb9fed143d` regenerates `reverse/data_ledger.csv` with `tools/data_ledger.py`, as recommended
  above. Simulation on this tree (full `./build.sh`, the same read-only `plan()`), bridge before these commits with the
  committed ledger -> all three: generated 4,437 -> 5,176, already correct 289 -> 511, refused 213 -> 278.
  no-kept-definition 6 -> 0, ambiguous-table-name 32 -> 2, unindexed bindings 620 -> 2; strong-definition 133
  addresses -> 189 names (counted per name now); target-not-winning-provider 36 -> 44 (newly indexed tables, none
  previously bridged); no-retail-slots 0 -> 34 (vbtables); unbounded-retail-row 0 -> 5 (one-byte placeholder owners);
  unsupported-selection 0 -> 2 (the runtime's `type_info`, `_com_error`). Names bridged or already correct
  4,726 -> 5,687 (+968, -7: stale spellings no retail code installs; listed in LINK-627).
- LINK-618's recorded trip is gone: 0x00811368 no longer lists `??_7Rva0034159A@@6B@`, only `??_7AIDockState@@6B@`.
  The committed ledger listed 1,214 `??_7` names no kept object defines or references; the regenerated one lists none.

Next check: the next real link's `vtable_bridge_queue.tsv` has no `no-kept-definition` rows and about 189
`strong-definition` rows, one per strongly defined name. Clearance: none claimed (no real link measured).
