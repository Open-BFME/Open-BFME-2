### LINK-181 Real-link blockers in GameClient and GameEngineDevice (2026-11-03)

Seat halilkkaya-zs-o2. The real link was measured at `96cfeda7ba`; `reverse/exit_link_blockers.tsv`
lists the sources.

**Repaired.** Each unit's unrowed Zero Hour bodies were dropped. Rows, data rows and every name a
census unit takes were kept, and `link_check` over the consumers shows no loss.

| Unit | Real-link error rows | Linked bytes |
|---|---|---|
| SkirmishGameOptionsMenu | 46 | 0 → 98 B |
| LanGameOptionsMenu | 28 | 0 → 65 B |
| WOLGameSetupMenu | 11 | 0 → 23 B |
| WOLBuddyOverlay | 12 | does not link (see below) |
| W3DTerrainLogic | 7 | 0 → 145 B |

- **Menus** (`3670a49f64`): the three units together give 85 error rows, and 51 unique names lose
  their last reference.
- **WOLBuddyOverlay** (`75b05dbceb`): its 17 rows stay exact through address anchors. It still has
  two BuddyInfo-tree COMDAT variants that predate this change, so it does not link yet.
- **W3DTerrainLogic**: drops `loadMap`, `getExtent`, `getMaximumPathfindExtent`,
  `getExtentIncludingBorder` and `crc`.

**Repaired by seat halilkkaya-rl-o1 (2026-11-03, base `5a3c7309be`).** These units' unrowed ZH bodies
were dropped. Each emission side effect a row or another object needed is kept by an anchor marked
`absent-from-retail`. For a protected member or nested type, the anchor is a static member of a derived
helper that is never instantiated, following `TerrainTrackEdgeInfoO1.cpp`.

| Unit | Real-link error rows (names losing last ref) | link_check |
|---|---|---|
| HeightMap (`cf32e0aa8d`) | 32 (31) | 0 → 107 B, LINKS |
| W3DTankTruckDraw (`0a31cca6e5`) | 33 (30) | 0 → 103 B, LINKS |
| W3DGameClient (`207a6e191b`) | 9 of 10 (9) | still blocked (see below) |

The hatch register drops 12 `present-unmatched` entries (`01980b16b6`).

How each unit was handled:
- **HeightMap.** The ctor's vtable was the only emitter of the five `BFME_RO_DEFINE_FLAGS` setters
  (Set_Alpha and `_bfme_ro_flag110/112/114/116`), so they are now kept by qualified calls. Render was
  the only caller of `RTS3DScene::getCustomPassMode` (0x0026FF4F), which an address anchor now keeps.
- **W3DTankTruckDraw.** An array of the protected `TreadObjectInfo` in a derived helper emits both
  0x000CDFB1 and 0x000636B3 (`Material_Override`'s ctor; retail `.text` never references it).
- **W3DGameClient.** Qualified calls keep `GameClient::firstDrawable` and `getDrawableList`, which
  GameClientDrawableTOC needs, and the protected `createGameDisplay` row.

Verification for each unit:
- `./build.sh` exact, `find_declared_unmatched` clean and scoped DIR32 OK.
- An orphan scan against the census index finds no lost definition that another object references.
- First-copy COMDAT check: every COMDAT one of these objects provided first in link order has
  byte-identical copies elsewhere. A/B `link_check` runs, with each unit's census object against its
  tip object, change no unit's state:
  - `Invalidate_Cached_Bounding_Volumes`: part_buf, composite, mesh, segline, streak and
    HLodUpdateObjSpaceBoundingVolumes all stay LINKS. Its 7 copies share one digest and the ledger
    owner is composite.
  - The other first-copy COMDATs of the three units: 5 + 5 + 106 units, no change.

**Still open in these units.**
- **W3DGameClient (1).** The row createRayEffectByTemplate calls the view spelling
  `?newDrawable@BFMEThingFactory@@QAEPAVDrawable@@PBVThingTemplate@@W4DrawableStatus@@H@Z`, which is
  pinned to 0x002CF21B. That address's definer is `?newDrawable@ThingFactory@@QAEPAXPAXHH@Z`
  (Rva002CF21BGet.cpp), as the canonical `Code/GameEngine/Include/Common/ThingFactory.h` declares it.
  Prerequisite: adopt the canonical ThingFactory.h in this unit in place of Zero Hour's, then respell
  the call and retire the pin.
- **W3DGameClient's createGameDisplay row (0x0008FCAE).** The census judges it "not retail's body",
  and code identity flags its callee 0x00104EBF as rowed `??0Rva00104DB0`, not `??0W3DDisplay`. The
  row allocates 0xD8 bytes and sits among W3DGameWindowManager rows, so its identity is doubtful.
- **W3DTankTruckDraw rows.** 0x000CDFB1's only retail reference is the DIR32 at 0x000CEAC0 in
  W3DTankDraw's ctor (0x000CEA6C), and tu_map approves the address in W3DTankDraw.cpp. The row is
  W3DTankDraw::TreadObjectInfo's implicit ctor. Moving it there, as an implicit ctor with a
  Material_Override view ctor, retires the `/alternatename` W3DTankDraw still needs. That renames a
  non-placeholder row, so it waits for the naming lane. 0x000636B3 is approved in W3DGhostObject.cpp,
  whose ZH `static RenderObjClass::Material_Override animationDisableOverride` lives in
  W3DGhostObjectScene.cpp today. It follows that file's merge.

**Blocked: needs class work rather than body drops.**
- **Rva0008EF3FProductCtor_Unresolved (35).** The canonical `InGameUI.h` slot names (slot52,
  slot10_xx, crc, ...) have no definers. Retail table 0x00BC7A88 points those slots at ICF-shared
  bodies rowed under other names. The fix is either fold rows (`add_match --icf-owner`) or slot
  renames in the shared header.
- **EvaMessageVectorAssign.** `??1EvaMessageInfo` is retail 0x003F60C8, rowed as
  `??1BfmeStringRecord00111ACF`. The fix is a placeholder-class rename.
- **W3DShaderManagerScreenBWFilterInit and Rva000FDCD7Get.** Both need the unowned screen-filter
  data globals at 0x009B5B54 and 0x009B5BD4 defined.
- **HelicopterSlowDeathUpdate (16, GameLogic).** The 16 names come from its unrowed ZH code calling
  three ZH-only SlowDeathBehavior bodies: `??1`, `crc` and `loadPostProcess`.
  - In retail the dtor is 0x0045D39E, rowed as `??1Rva0045D39E@@UAE@XZ`, so Rva0045D39E is
    SlowDeathBehavior.
  - `loadPostProcess` is the ICF-shared 0x00497805.
  - `crc` has no BFME 2 slot.
  - Fix in the consumer: drop its ZH bodies and keep the `isDieApplicable` row 0x0045D49E emitted.

**SlowDeathBehavior TU merge (2026-11-02).**
- The native seed (`0f8974c269`) drops the ZH chain, and the seed now links (28 B).
- A merge of 5 donors verifies: 18/18 rows exact, the TU goes 0 → 1,372 B, and there is no loss over
  3,316 units.
- `class_gate` refuses the merge. Its `scoped_move_spans` gives no move credit to a composed TU that
  contains a template class head, so the verbatim private UpdateModule/INIException views read as new
  copies.
- The false reject is logged in `reverse/re_attempts.log`. A tooling fix that credits non-template
  spans is needed.

**PlayerList.cpp merge.** It waits on `file:PlayerList.cpp`, held by ancalgonn-ops-srv1 for a
`// cl:` cleanup.
