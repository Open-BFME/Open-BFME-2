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
- **Rva0008EF3FProductCtor_Unresolved (35, now 16).** Partly repaired by halilkkaya-rl-o2; see
  "W3DInGameUI's vtable" below.
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

**W3DInGameUI's vtable (seat halilkkaya-rl-o2, 2026-11-03, base `c3bdb94097`).**
Rva0008EF3FProductCtor_Unresolved.cpp builds W3DInGameUI, and its constructor emits the vtable
0x00BC7A88 against the canonical `InGameUI.h`. Retail InGameUI's own table 0x00BFD410 equals it
except for the overrides. The unit went from 35 unresolved names to 16.

| Commit | Names | How |
|---|---|---|
| `7ff7f42ca1`, `061dff9d0a` | 3 | `updateFormationPreview`, `rva0029DB61` and `rva0029FD1B` were rowed non-virtual (`QAE`). `rename.py function --virtual` respelled them. In each private view the method takes its neutral pad slot (slot53, slot54, v80), so later slots keep their index. A plain `--virtual` put the new slot first and shifted the +0x118/+0x12C/+0x144 calls. |
| `76cadac5d7` | 16 | `InGameUI.h` defines the inline slots and protects the snapshot methods (below). |

The inline-slot evidence for `76cadac5d7`:
- Right after its constructor, in table order, retail W3DInGameUI's object holds the bodies of
  slots 20, 21, 51, 63, 64, 71, 76 and 95, and of +0xC slot 2 (0x0008EF81..0x0008EFD2).
- InGameUI's own tables point at these same copies, so they are inline COMDATs of InGameUI.
- Slots 52, 70, 72, 102 and 103 point at identical bodies folded elsewhere by ICF.
- Zero Hour declares six of these inline with the same bodies, and its snapshot methods protected.
- The `loadPostProcess`/`xfer` rows are `MAE`. +0xC slot 2 is `GetSnapshotName`, which returns
  "InGameUI".
- Every emitted COMDAT is byte-equal to its retail copy.
- The header gate covered 133 dependents (1,557/1,557).
- link_check over the 132 includer units shows no unit going from LINKS to not linking.

Still open in this unit (16 names):
- **`??1Rva0008EF3FProduct`.**
  - `rename.py class --fold Rva008F00D --into Rva0008EF3FProduct --dry-run` plans cleanly: 4 rows
    and 1 pin across Rva0008F00DDtor.cpp and OpaqueScalarDeletingDtorsB09.cpp.
  - Both files were held by StarkillerHDX@fleet on 2026-11-03.
- **13 out-of-line slots, rowed under placeholder classes in Common units.** All lie in the range
  tu_map approves for InGameUI.cpp. Route: `rename.py function --to-class InGameUI` (`40e5b4c325`),
  with each definition prepared under the canonical header. Its installer check may stop on
  InGameUICtor.cpp's six-slot private view. The slots:
  - slot10_00, slot10_01, slot10_04: 0x0029B558/63/D8 (Rva0029B558, GapBodiesS3B.cpp).
  - slot10_03: 0x0029B5CD (GapBodiesSeat1A.cpp).
  - getScrollAmount: 0x0029A872 (VtableSlotBodiesR3F.cpp).
  - slot49, slot50: 0x0029AA62/0x0029AAC8 (Rva0029AA3F.cpp).
  - getPendingPlaceSourceObjectID 0x0029A9BB and getMousedOverDrawableID 0x0029A7EA
    (DispDwordFieldGetters.cpp).
  - slot65: 0x0029AB03 (DispByteOneSetters.cpp).
  - slot77: 0x0029C0A9 (VslotSmallBodiesC.cpp).
  - slot87: 0x0029ACE3, rowed `?bfmeGoBLD@@YGXPAX@Z` in BfmeConv485.cpp, a stdcall free-function
    spelling of a thiscall slot.
  - slot89: 0x0029ACFB (GapBodiesS3B.cpp).
- **slot92.** Its body is the ICF-shared 0x0043812F, `mov eax,[ecx+0x5C8]`. The header's
  `int slot92()` would return the VideoBuffer pointer: fix the return type before inlining it.
- **slot96.** 0x0008EFCC returns InGameUI's field-parse table 0x00BFC338, which today exists only
  as the address-named `g_00BFC338` (INIThinFieldParsers2.cpp).

Bookkeeping that waits for the unit to link:
- The nine retail copies 0x0008EF81..0x0008EFD2 keep their placeholder rows in VslotSmallBodiesC,
  DispByteFieldGetters, DispByteFieldSetters, DispDwordFieldGetters and SubsystemNameGetters.
- A trial repoint of these rows to this unit verified 9/9, but it moves 81 census-linked bytes into
  a unit that does not link yet. Land it, and fold rows for slots 52/70/72/102/103, with the
  unit's last fix.

Screen filters (the W3DShaderManagerScreenBWFilterInit and Rva000FDCD7Get entries above):
- 0x009B5B54.. are statically initialized filter objects: vptr 0x00BCF364/0x00BCF380/0x00BCF440
  plus zero fields.
- Defining them emits those vtables, and their slots are rowed under mixed placeholder classes
  (BfmeThingDF, Rva000FBA0F, Rva000FBA4A, Rva000FC63DFilter, Rva000FDD1C).
- Prerequisite: `--to-class` those slots into the filter classes before defining the globals.

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

**Repaired by seat halilkkaya-rl-o3 (2026-11-04, base `343195ceec`).** Unrowed Zero Hour bodies were
dropped or retargeted. Each unit stays exact, find_declared_unmatched is clean, scoped DIR32 is OK,
the orphan scan finds 0, and A/B link_check over the first-copy siblings shows no change.

| Unit | Names | How |
|---|---|---|
| InGameUI.cpp (`10b6e4f300`) | 3 | Drops ZH `setRadiusCursor` and `clearWorldAnimations`. An anchor keeps the `??_GWorldAnimationData` row (0x007593F0). |
| FXList.cpp (`525a9fb493`) | 2 | The inline ZH `doFXPos` forwards to the rowed four-argument `reallyDoFX`, as retail 0x001E19CE does (`push 0; push 0`). |
| W3DTerrainVisual.cpp (`0048fd4f8b`) | 1 | Drops ZH `setWaterTransform(const WaterHandle *, Real x4)`. |
| MapUtil.cpp (`a77d88bab8`) | 10 + the addMap LNK2005 | Applies lk19's banked patch: drops ZH `addMap` and the static chain only it reached. MapCacheAddMap.cpp and MapCacheLoadUserMapsBFME2.cpp go 0 → 1,191 B and 0 → 1,198 B. |
| MapUtil.cpp (`ce66feaa26`) | 4 | Drops ZH `populateMapListbox` and `populateMapListboxNoReset`, which take AsciiString by value. BFME 2's are rowed in MapUtilGetDefaultMap.cpp. MapUtil.cpp has no unresolved name left. |

- In FXList.cpp a qualified-call anchor cannot replace the reference FieldParse table. Emitting
  `ParticleSystemFXNugget::doFXObj` through a direct call compiles `atan2(float, float)` out of
  line instead of inlined, and the row fails. This holds with or without `inline_depth(0)` and at
  either place in the file. Only the parse, constructor and vtable route reproduces retail's body.

- MapUtil.cpp keeps 19/19 rows exact without any foreign row moving. Rows the dropped bodies used to
  emit stay this file's rows through explicit instantiations, and three changes made that work:
  - getExtent (0x003000B5) stays `static`. Its EAX convention needs every caller visible, and its
    out-of-line copy is emitted only when a later function references it. An `absent-from-retail`
    anchor references it in place of retail's addMap. lk19's external getExtent changed the
    convention.
  - `vector<ICoord2D>::_M_insert_overflow` (0x00181770), the `map<UnicodeString, AsciiString>`
    constructors (0x00157020, 0x00620E90, 0x00620720) and the four waypoint-tree members are
    explicitly instantiated.
  - `__default_constructed<AsciiString>` is explicitly instantiated as well. PeerThread.cpp binds
    to this file's copy by declaration, which the orphan scan caught.
- The MapUtil TU merge is still blocked:
  - `--split` lists 6 implicit STLport rows approved for other TUs and 13 rows with no TU.
  - `--merge --dry-run` lists MapCache/MapMetaData adoption as adopt_first for 12 donors.
  - Retail's addMap and getExtent still need to meet in this TU, which retires the anchor.

**Misidentified row 0x001EC981 (for the naming/identity lane).**
`?removeAllBibs@W3DTerrainVisual@@UAEXXZ` (W3DTerrainVisual.cpp, 13 B, no notes) is not
W3DTerrainVisual's.
- Its bytes are `8b 49 10 85 c9 74 05 e9 .. c3`: a null-checked tail jump through `this+0x10` to
  0x001EC3B5, which is rowed `?onCurrentMissionWon@LinearCampaign@@QAEXXZ` (648 B).
- It sits among LinearCampaignManager.cpp's null-checked forwarders: 0x001EC98E, 0x001EC99B and
  0x001EC9AC.
- Its only retail caller is ScriptGlueRva003BD598 (0x003BD598, call at +0x24). That caller loads
  `TheLinearCampaignManager` (VA 0x00DFDC8C) into ecx and spells the call
  `reinterpret_cast<W3DTerrainVisual *>(TheLinearCampaignManager)->W3DTerrainVisual::removeAllBibs()`.
- The pin `?removeAllTerrainBibs@BaseHeightMapRenderObjClass@@QAEXXZ` → 0x001EC3B5 (symbols.csv)
  follows only from the misplacement. It names a second function at LinearCampaign's address, and it
  is W3DTerrainVisual.cpp's last real-link name.
- Fix: re-identify the row as a LinearCampaignManager member that forwards to its campaign's
  `onCurrentMissionWon`, in LinearCampaignManager's TU. Respell the ScriptGlue caller, drop the ZH
  `removeAllBibs` body and retire the pin. This is not done ad hoc: it corrects the identity of a
  readable-named row and a pin.

**InGameUI slot chain: handoff (rl-o3, 2026-11-04).**
- The full-width installer views for InGameUICtor.cpp and InGameUIDtor.cpp are banked in
  `reverse/attempt_support/ingameui-installer-views-20261104-rlo3/` (`d8b9e43e29`).
  - Both files stay exact.
  - Both compile retail's 120/4/5 tables with 0 clashes.
  - With the views applied, `--to-class InGameUI` passes its installer check.
- The `--to-class` back-reference false reject on slot49/slot50 is fixed in rename.py
  (`973766f5fa`). The tool now reads name and argument-type back-references from the decoration's
  grammar, so the 3 in `PBUCoord3D@@` is no longer one. With the views not applied, slot49's dry
  run now stops only at the installer check.
- Next steps, in order. Land all of them as one batch, because the views alone take
  InGameUICtor/Dtor (3,642 B) from LINKS to not linking:
  1. Apply the banked views.
  2. Run `--to-class` with prepared C++ for the eligible slots:
     - slot10_00, slot10_01, slot10_03, slot10_04;
     - slot49, slot50, slot65, slot77 (full `UBE` name), slot89;
     - getMousedOverDrawableID.
     Each slot body can cast `this` to its unit's existing field view (for example Rva0029AA3F)
     while being defined as `InGameUI::slotNN` under the canonical header.
  3. Respell the return types of getScrollAmount and getPendingPlaceSourceObjectID.
  4. Convert slot87 from its free stdcall row into an InGameUI method.
  5. Resolve slot92 and slot96 as noted below.
  6. Confirm with link_check over InGameUICtor, InGameUIDtor, Rva0008EF3FProductCtor_Unresolved and
     the respelled units.

**Item analyses that did not land (rl-o3).**
- **InGameUI's 13 out-of-line slots.** `--to-class` reads the vftable from both installer units.
  Today both declare only 6 virtuals:
  - InGameUICtor.cpp is held by StarkillerHDX@fleet (class:ResourceEntryCollector).
  - InGameUIDtor.cpp has a private view.
  - The image report agrees: `??_7InGameUI@@6BSubsystemInterface@@@` is 7 slots against retail's 120.
  A full view in both adds references to every still-unresolved slot, so those two linking units
  (2,686 B and 956 B) would stop linking until all of them resolve. Land the view with the last
  slot, not before. Three slots need more than `--to-class`, which keeps the return type and
  parameters:
  - getScrollAmount's row returns `Rva00SlotFloat2Copy`, not `Coord2D`.
  - getPendingPlaceSourceObjectID's row returns `int`, not `ObjectID`. ZH declares `const ObjectID`.
  - slot87's row is the free stdcall `?bfmeGoBLD@@YGXPAX@Z`.
  - slot77 needs the full mangled name (`UBE`), which the tool accepts.
- **W3DInGameUI's emitted vtable is short.** Rva0008EF3FProductCtor_Unresolved.cpp includes the
  canonical SubsystemInterface.h before InGameUI.h, so `BFME_SUBSYSTEM_SLOTS` is off. Its
  `??_7Rva0008EF3FProduct@@6BSubsystemInterface@@@` has 114 slots against retail's 125 (image
  report). Every InGameUI slot after slot 3 sits 8 below retail's index. The link cannot see this.
- **slot92 and slot96.**
  - Zero Hour declares `cameoVideoBuffer` (slot92) out of line (InGameUI.h:478; body in InGameUI.cpp
    as `present-unmatched`). Its fold into 0x0043812F is therefore not evidence for inlining: it
    needs a fold row under the corrected `VideoBuffer *` return type.
  - slot96 is ZH's inline `getFieldParse() const { return s_fieldParseTable; }` (InGameUI.h:488).
    It needs `InGameUI::s_fieldParseTable` at 0x00BFC338 as a real global.
- **W3DGameClient's newDrawable.** The canonical ThingFactory.h needs the canonical
  SubsystemInterface. This unit's views sit on Zero Hour's 8-byte SubsystemInterface: SnowManager's
  0x74 size check and the GameClient shim. Respelling the call therefore means adopting
  SubsystemInterface in the unit first. Splicing the canonical ThingFactory.h onto the ZH base
  through its include guards was judged a workaround and not done.
- **Screen filters.** The filter objects are statically initialized, so no constructor, destructor
  or deleting-destructor row installs 0x00BCF364/0x00BCF380/0x00BCF440. `--to-class` refuses
  without an installer, so these slots need a tool route for static-object vtables first.
- **AptPlayerTooltipMap's `??1Rva00224C95`.** Retail funclet 0x0076F6BC destroys AptPlayer's
  `m_levels[14]` (stride 0x28) through the EH vector destructor iterator 0x00629110, with destructor
  VA 0x00624252. That RVA is rowed `??1DetailedArchivedDirectoryInfo@@QAE@XZ` (ArchiveDirInfoO1.cpp).
  Either the element type is that class, or the two destructors fold. That is an identity decision.
- **T1Base005F3750Ctor's `??1T1Base_005F3750`.** Retail's constructor 0x0055C903 installs 0x00C1D3F4
  at +0. Slot 0 of that table is `??_GRva003ABA36` (0x003AE8D5), so the class's destructor is
  `??1Rva003ABA36` (0x003ABA36). `rename.py class --fold Rva003ABA36 --into T1Base_005F3750` refuses,
  because Rva003ABA36's copy constructor 0x003AE7B8 installs other tables. The two placeholders mix
  classes, and that needs identity work first.
- **LivingWorldManagerCtor (5).** The member constructors it spells `??0Rva002130CA`,
  `??0Rva00212379` and `??0Rva00211FA3` reach the ICF-folded STLport constructors 0x00213E11
  (hash_map) and 0x0033C432 (map) only through pins. The member types need to be the real
  containers in both the constructor and destructor views, together with their EH funclets.

**Row 0x001EC981 re-identified (2026-11-04).** Done as this entry's fix proposed, plus the real terrain pair it left open; evidence and remaining census check in LINK-090. Not done: rehoming 0x001EC98E, 0x001EC99B, 0x001EC9AC's address-named classes.
