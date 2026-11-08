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
  LightClass's table is since repaired in source (P21, the 2026-11-07 crash-triage entry below).
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

2026-11-07 MeshClass/RenderObjClass follow-up: the unrelated 0x005AD93A
float setter is now ordinary C++ under an address placeholder, replacing the
incorrect RenderObjClass gen-alias through add_match.py. Its +0x4C store differs
from the real 0x0006CEBF setter's +0x48. The emission-anchor call is removed;
collect.cpp no longer defines the false RenderObjClass copy. All five rows
remain exact and all other external body/relocation/COMDAT facts are unchanged.
Authored C++ rises 14 bytes, with coverage kept. The original class and TU are
still unknown; no original name is asserted or source moved. Six alignment-only
provider prerequisites remain, so no full MeshClass/table clearance is claimed.
[Native facts and verification](../../reverse/attempt_support/collect-float-setter-recovery-20261107/README.md).

Same pass, shared-body ownership: the canonical rendobj.h now declares
Get_Current_LOD and flag111/113/115 without emitting competing copies. Their
verified distlod.cpp owner selects the unchanged reference header. Normal
849/849 rows in the 21 known canonical-header emitters pass; current COFF
inspection of all 23 indexed providers leaves only the owner for each of
these four names. The other three previously blocked names have exact
first-provider twins under the existing strict flags/bytes/relocations rule.
Mesh's table stays 129 slots and the four affected pointer names keep slots
84/114/116/118. No bridge rule, row, pin, flag or path changes. The ordinary
three-unit preview conserves 2,294 authored linking bytes. These are provider
prerequisites, not a new actual-image/table/runtime clearance.
[Proof and remaining scope](../../reverse/attempt_support/renderobj-inline-provider-ownership-20261107/README.md).
The prior setter push's broader audit remains INCONCLUSIVE: index 9c81acd297
versus outgoing base 009791f6a9183bdf2a15fa583f1c30927c4b7013, with 23 consumers
without current receipts (first BaseHeightMapConstructor.cpp). Byte/EH checks
passed; carry the broader selection check into the next census and real image.

Header repair published as c8a28636a1: required gates pass 3,583 rows and
297 EXACT EH graphs across 291 source units, with converged data and scoped
DIR32 clean. The broader outgoing audit is still INCONCLUSIVE: index
9c81acd297 versus base db29d3c6aada78a523d4b07b5086a1595f3638e7, 290 consumers
without current audit receipts (first BaseHeightMapRenderObjClassRva0006846A.cpp).
Keep that selection scope open for the next census and real image; no image
or runtime clearance is inferred from the successful source gates.

**2026-11-07, crash-triage seat2 (P21): LightClass repaired in source.** LightClass, one of the 20
RenderObjClass-derived tables listed after lk40, is repaired in source rather than through the bridge.
LightClassCopyCtor.cpp, the only unit that emitted LightClass's tables (6 of retail's 130 slots in
`??_7LightClass@@6BRefCountClass@@@`), now includes the canonical LightClass.h over the canonical rendobj.h. Its
compiler-flag line gains the WWVegas include paths and `/DNDEBUG` (Zero Hour's refcount.h, which rendobj.h includes,
otherwise adds its debug members and the 0x120 size check fails); it defines BFME_RO_DTOR_DECL_ONLY (retail's
~LightClass tail-jumps to the rowed ~RenderObjClass 0x0013BE20), and defines Render (slot 12, the shared ret 4 at
0x0047A69C) and Is_Vertex_Processor (slot 129, mov al 1; ret at 0x0050B5C6) as fold-proof ICF aliases. `rename.py
function --to-class` moved `?Class_ID@Rva0006DD63@@QAEHXZ` (0x0006DD63, slot 3, VtableSlotBodiesR3.cpp) into
LightClass as `?Class_ID@LightClass@@UBEHXZ`. Result: 130 slots, 71 at retail's exact target, none wrong, 59 unrowed
inline base bodies; ./build.sh exact; link_check of both units LINKS (1,170 -> 1,176, 630 -> 630).
- Caveat: the canonical RenderObjClass has no PersistClass base, so the secondary table is now named
  `??_7LightClass@@6BMultiListObjectClass@@@` (one slot, the -8 `??_E` thunk). `reverse/data_ledger.csv` still names
  0x007D23B8 `??_7LightClass@@6BPersistClass@@@`, the stale-ledger case of cluster 2; no live consumer spells it.
- Retained debt: LightClassCopyCtor.cpp's LightClass header-queue row stays. `header_adopt_lane accept` passes it
  together with VtableSlotBodiesR3.cpp, but the pre-commit retirement judges the unit alone against the census copy of
  VtableSlotBodiesR3.obj (which still defines the placeholder) and predicts a loss; recorded as a false reject in
  re_attempts.log at 0x00130AC0, routed to the tooling queue. The unit's RenderObjClass, AABoxClass and SphereClass
  rows also stay queued; their recorded reasons predate the adoption and were not re-judged here.
- Runtime: not yet proven; the test receipt (2026-11-07T194022Z-boot_smoke-1e6b78e98671) stops in Object INI loading
  before the shell map, where lights are built. P21 stays open until a receipt reaches the shell map.
- Outgoing audit (index fetched at c5e492e56d, base 6b03ea70b8): INCONCLUSIVE, no loss named. Both objects hold the
  ordinary dependency receipt, not a census-grade (include-inventory) one. link_check against that index: both units
  LINK. Carry LightClassCopyCtor.cpp and VtableSlotBodiesR3.cpp into the next census.

**2026-11-07, crash-triage seat2 (P24 prerequisite): CameraClass's table reaches retail's 131 slots.** camera.cpp
compiles CameraClass from the Zero Hour camera.h shims (`reference/shims/bfmecamera/camera.h`, twin
`reference/shims/sweep/camera.h`), which declared Cull_Sphere and Cull_Box non-virtual, so its table stopped at 129
of retail 0x00BD26E0's 131 slots (129 = 0x00135960, 130 = 0x00135990). Both shims now declare them virtual
(db1ca0d50b; 52 dependents, 1299/1299 exact); `rename.py function --virtual` respelled the Cull_Box row UBE. The
non-virtual Cull_Sphere row W3DScene.cpp emitted through an absent-from-retail anchor is retracted (1820bfa66f) and
camera.cpp, its approved TU, rows the virtual copy (a0e7ba1e07); link_check: camera.cpp 10,109 -> 10,151,
W3DScene.cpp 222 -> 180, both LINK. The canonical CameraClass.h already declared both virtuals. The six alignment-only
inlines and slot 93 above still apply to this table. Next: P24's Rva007C454 (retail 0x00BC6C58) overrides slots
129/130 under placeholder names `?rva0007BEA7@Rva007C454@@…` / `?rva0007BEDA@Rva007C454@@…`, which go through
name_lane and then `rename.py function --respell` (const) before its canonical-CameraClass views can link.


**2026-11-07 why rename.py has no same-class `--to-class` respell (swarm Link lane).** A mode that would
have respelled P24's placeholder slots 129/130 (`rva0007BEA7`/`rva0007BEDA`) from the canonical base's slot
was dropped after three Codex rounds: proving the name from the base's table by subobject offset, header
text or the compiled table each left a P1 (a same-length secondary table can stand in for a wrong-length
primary; an installer's private view can declare the member virtual where the canonical header does not).
Placeholder method names take the ordinary route: blind-vote naming, then an inferred respell.

**2026-11-08, crash-triage seat2 (P25 phase 1): census check required for RefCountClass slot 0.** f0d7034d24 makes
the canonical `RefCountData.h` define `RefCountClass` under Zero Hour's `REFCOUNT_H` guard too (one definition for
both header families) and makes `Delete_This` the inline `{ delete this; }` that retail shows: its live body
0x0006CE57 (slot 0 of all 106 RefCountClass-derived tables, rowed under the placeholder
`?DeleteThis@BfmeDynamicVBRefCount@@UAEXXZ`) has a byte-identical unreferenced twin at 0x0030F466. The 334 header
dependents stay byte-exact (pre-push verified 334) and a 12-unit link_check sample is unchanged, but the outgoing link
batch audit was inconclusive (no census-grade receipts), and per-unit checks cannot see COMDAT selection. Before this
change the image already bound slot 0 to an unrowed COMDAT copy (BaseHeightMapConstructor.obj); with more units now
emitting the inline body, **the next census or real link must confirm that slot 0 of the RefCountClass-derived tables
still resolves to a `Delete_This` body** (crash triage checks it when that census reports). Phase 2 (multilist) waits
for that confirmation. Follow-up: rename the placeholder row at 0x0006CE57 to `?Delete_This@RefCountClass@@UAEXXZ`.
- **Verified 2026-11-08 (crash triage):** on the diagnostic image 8bd091877e (master f0d7034d24, phase 1 included;
  real link run 42434021523 at the same base: 132 unresolved, 0 duplicates), all 106 retail tables whose slot 0 is
  0x0006CE57 resolve by ledger name, and slot 0 still resolves to a `Delete_This` body in 104: 84 to the rowed retail
  body (`?DeleteThis@BfmeDynamicVBRefCount@@UAEXXZ`, alias `?f0@CamBase0@@UAEXXZ`, byte-identical to 0x0006CE57 apart
  from the operator-delete displacement) and 20 to the unrowed `?Delete_This@RefCountClass@@UAEXXZ` COMDAT from
  BaseHeightMapConstructor.obj (a different but equivalent shape: `push 1; call [eax+4]`). The other 2 hold a deleting
  destructor (`??_7BaseHeightMapRenderObjClass@@6BRO0@@@` and `??_7Rva006DD51@@6BRva006DD51Base0@@@`, scaffold views).
  The pre-phase-1 image 05d517395d gives the identical 84/20/2 split, so phase 1 changed no slot-0 binding. Follow-ups,
  not caused by phase 1: those 2 scaffold tables, and naming the 0x0006CE57 row so the 20 tables bind to it.

**2026-11-08, bounding getter order/identity boundary:** Rva001684D6Copy.cpp's
served table 0x007D41C8 remains a real path-order refusal. The refreshed census
index selects exact animobj twins in retail order, but exit_link's default
path order selects BaseHeightMapConstructor with identical 22-byte getter
bodies/relocations and different alignment flags. A direct Targets.resolve
replay reproduces both outcomes. Normal three-unit gate passes 193/193.
A blanket alignment-mask change is not applied: position-observing code
(call/pop is one counterexample) needs a sound proof boundary first. A private
speed-preference flag trial loses 15/30 BaseHeightMapConstructor rows and is
not landed. No source/header/verifier edit; queue and owners stay intact.
[Reproduction and remaining proof](../../reverse/attempt_support/renderobj-bounding-order-20261108/README.md).

**2026-11-08 terrain destructor RenderObj adoption:** Rva0006D0D7Dtor.cpp
removes its RO0/RO8/ROC4/private-RenderObj scaffold and includes canonical
rendobj.h; a native two-slot DX8_CleanupHook view preserves +0xC4, with the
existing resource callback names. All26 rows remain exact and the one parent
EH graph is EXACT. Header acceptance retires its RenderObjClass debt row.
Source slot0 now names Delete_This, slot1 the deleting destructor, and the
cleanup table has the two resource callbacks. The primary grows1->129 slots
but retail needs148; the SnapC8 one-slot view and full BaseHeightMap lifetime/
interface adoption remain open. Preview817B is conserved; the separate
bounding-getter alignment refusal and real-image verification remain pending.
[Source and table scope](../../reverse/attempt_support/baseheight-renderobj-parent-20261108/README.md).

The parent prerequisite published as 7aac060ff5 with all 26 rows and the
parent EH graph exact. Its broader outgoing audit was INCONCLUSIVE: index
f4727bbd09 versus base 142b6e389c1d5a49fb9e9686da0ab0c15f405f30, one missing
current source receipt (Rva0006D0D7Dtor.cpp). Preserve that selection scope for
the next census and real image.

**2026-11-08 terrain texture-handle prerequisite:** the same destructor now
uses canonical RefCountPtr<TextureClass> for its five owning texture members.
All 25 retained rows and its one EH graph remain exact; the redundant private
RefTex destructor row is retired while its canonical owner at 0x0017098D
continues to cover the range. Complete index touches identify no outside
consumer of RefTex. Ordinary preview stays LINKS (817->805 authored bytes,
removing the redundant 12-byte claim). Full-header adoption is still blocked:
the game-free allocator binding restores the exact 735-byte parent and EH,
but two cleanup rows need native twin-callee ownership and twelve newly exposed
virtual names need providers. No pin or masking change is made. The primary
129/148-slot and Snapshot 1/4-slot gaps, broader consumer selection, and actual
image/runtime verification remain open.
[Verified scope and full-header trial](../../reverse/attempt_support/baseheight-texture-handles-20261108/README.md).
- **P24, camera table (2026-11-08, crash-triage seat2):** `Rva007C454` is registered with base `CameraClass`, and slots 129 and 130 of 0x00BC6C58
  are respelled const by the this-cv route (`?Cull_Sphere@Rva007C454@@UBE_NABVSphereClass@@@Z`, `?Cull_Box@Rva007C454@@UBE_NABVAABoxClass@@@Z`),
  after the route's walker stopped dropping `this` at `__EH_prolog` (006734770a). Earlier spellings above are history. Verified: the six units
  build exact and link_check LINKS, unchanged at 470 bytes; no boot receipt covers it yet.

Texture-handle cleanup published as e45a923881, first attempt 34.7 seconds.
Normal byte/EH/DIR32/data checks pass; name_dependents finds zero outside
users of the retired RefTex name. Broader audit remains INCONCLUSIVE: index
f4727bbd09 versus base eba83a23bec9a0ccf16e8e8bbf244379acf77da4, one missing
current source receipt (the destructor). Array-helper identity, complete
interfaces, census selection and actual-image verification remain open.

**2026-11-08 Camera whole-file cleanup:** camera.cpp's redundant
BfmeVciAnchorElem/bfmeVciAnchor pair is removed. All 60 code rows, its data row
and both EH graphs remain exact; all 212 external COMDAT fingerprints are
unchanged, private LinkGuard is clean, and ordinary preview conserves
10,151 authored bytes. The Frustum anchors and optimization pragmas remain:
broader removal changes selected providers despite preserving most owned rows.
The served 0x007D26E0 table still encounters the already-recorded path-order
bounding-getter refusal at slots 65/66; no alignment exception or table/runtime
clearance is claimed.
[Provider comparison and retained mechanisms](../../reverse/attempt_support/camera-vci-anchor-cleanup-20261108/README.md).

Camera cleanup published as eb6c24b55e. All 60 code rows, its data row,
both EH graphs and scoped DIR32 pass after rebase. Broader audit remains
INCONCLUSIVE: index f4727bbd09 versus base
8be98f3efe60da401d09c05038aeac98afe27011, one missing current source receipt
(camera.cpp). The shared provider refusal and actual-image check stay open.

**2026-11-08 texture-diagnostics whole-file type cleanup:**
INIStatsRecordTextures.cpp uses canonical StringClassData.h and pinned
BFME1 vector.h, removing its two private VectorClass/DynamicVectorClass
templates. Existing provider specializations and release /DNDEBUG preserve
all five rows and the exact parent EH graph. All 16 external COMDAT
fingerprints and definition names stay unchanged, private LinkGuard is clean,
and preview conserves 435 authored bytes. Strict preparation supplies a
reusable source receipt without changing census status. The served 0x007D0D80
table's provider/alignment refusal remains pending a new real link; no
alignment exception, pin, row or path is changed.
[Type provenance and verification scope](../../reverse/attempt_support/ini-texture-shared-types-20261108/README.md).

Shared-type cleanup published as e17651338f. Its strict source receipt is
current and all required row/EH/DIR32/data checks pass. Broader audit stays
INCONCLUSIVE: index eba83a23be versus base
0fbd488b314b440e163d497ec0b5fc11af609e9a, affected
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. The existing
11-byte DynamicVector destructor copy versus native's 67-byte storage-release
body also remains a code-identity shadow finding. Import suppression loses
the cleanup row; extern-template declarations do not change emission, so
neither trial is landed. Preserve this lifetime/provider scope with the
table alignment boundary for the next census and real image.

**2026-11-08 ChangeStanceGroupOrder table repair:** both constructor and
destructor emitters now share a temporary ABI view and emit the native 14-slot,
56-byte table. Four byte-exact ICF leaf bodies supply the missing slots; all
15 code rows and every data-table relocation pass. Garrison/Attack providers
are unchanged. The redundant strong g_0086A36C array is removed and its data
row transferred to the compiler table at the same address and extent. Paired
preview is 2/2 LINKS against eba83a23be, with strict receipts for both sources.
Canonical GroupOrder hierarchy, historical data-ledger regeneration, actual
kept-provider/bridge selection and runtime confirmation remain open; this is
source-scope verification, not a full-link or image clearance.
[Slot closure and ownership transfer](../../reverse/attempt_support/change-stance-native-table-20261108/README.md).

Published as 4e99290287; required row/data/DIR32/EH checks pass. The broader
audit remains INCONCLUSIVE: index eba83a23be versus outgoing base
25c2bd22038a7fe74ce5ed110b86d92d956f6df9, affected AIBaseBuilder.cpp lacks
a current receipt. Carry this consumer into the next census/image check;
no broader link clearance is claimed.

**2026-11-08 second virtual-base-table false reject:**
Rva0030CAA9OwnerCtor.cpp's two ??_8 offset tables contain exactly native's
(-4,116) and (-24,144), with no relocations. All15 rows and its parent EH
graph pass; the positive-slot selector still admits both and reports
no-retail-slots. The tool remains claimed by another worker, so no verifier,
data ledger or queue was edited. Its two real function tables remain separate
bridge/interface work. [Exact offsets and next repair](../../reverse/attempt_support/wave-owner-vbtable-20261108/README.md).

**2026-11-08 default-alpha copy table bindings:**
DefaultModuleTemplate01InlineCopyCtors.cpp removes two unowned one-byte
definitions and names the existing alpha-info/head compiler tables at their
native addresses. The 97-byte body and its two registered data owners pass;
private LinkGuard and LINKS/97 preview are clean. Bounded cached replay drops
strong-definition refusals from 2 to 0, with the same one five-slot head bridge.
The alpha-info table is already correct in that cached emitter. Its private
copy view/helper is removed; complete containing-class recovery for v0b/vsub,
current-image provider selection and real-link queue confirmation remain open.
[Native operands and provider scope](../../reverse/attempt_support/default-alpha-table-bindings-20261108/README.md).

Published as c2ca5f6f36 after one lost race, with the source receipt reused
on retry. Required checks pass. Broader audit stays INCONCLUSIVE: index
eba83a23be versus base 4904abd4bd222cb47e06f9bbccd5f30303a5e693, affected
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Preserve that
consumer for the next census/image check.

**2026-11-08 Vector3 global-teardown provider boundary:** the first
Rva007B7280Siblings.cpp deleting copy is71B, with a34B rowed owner in
vector_class_vector3_ctor.cpp. Whole-class extern-template suppression drops
the copy/table but changes two teardown bodies (4/6 exact). No Code change
is retained; all six live rows pass and preview is LINKS/353 at d171e84869.
Current endpoint dest queries supply no usable approved TU, so no merge was
attempted. The different body and Resize/EH provider proof remain open;
this recheck does not authorize an alignment exception or clear a table.
[Evidence](../../reverse/attempt_support/vector-global-provider-20261108/README.md).
