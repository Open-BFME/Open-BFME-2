### LINK-619: vtable bridge refusals: deleting destructors rowed away from the TU that emits them first, and a stale data ledger
Status: Open (partly repaired). Updated: 2026-11-06; seat halilkkaya-lk38 (base `3d70a843d39`), queue
`reverse/vtable_bridge_queue.tsv` from real link `95341e20cc`, census index `d707d2f53b`.

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
