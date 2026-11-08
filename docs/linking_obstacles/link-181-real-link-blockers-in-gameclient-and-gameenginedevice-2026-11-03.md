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
  2026-11-04: retail insertion layout fixes the value-insert variant; node creation and identity/provider freshness still block the unit and debt retirement ([evidence](../../reverse/attempt_support/wolbuddyoverlay-retail-insert-layout-20261104.md)).
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

2026-11-04: the W3DGameClient newDrawable and createGameDisplay (0x0008FCAE) items are resolved pending census; see LINK-179's 2026-11-04 line.

**Seat halilkkaya-rl-o4 (2026-11-04, real link 41813987742 at `612abfbebb`: 65 unresolved, 1 duplicate).**
- **Rva0057621ACtor.cpp (10): resolved.** The file was a stale duplicate of the PlanningPhaseBehavior::Impl
  constructor 0x0057621A, which `Rva00575F38Dtor.cpp` already rows. It is retired, and its EH rows are
  re-rowed under the surviving constructor. Details are in LINK-060's 0x0057621A entry.
- **W3DVideoBuffer.cpp (7)** was already repaired on master by `353684d23f`, after the measured run.
- **W3DAnimationInfoVectorInsert.cpp (1): resolved.** `??0W3DAnimationInfo@@QAE@ABV0@@Z` was only a pin
  at 0x0004254E, Region2D's 31-byte copy that ICF folded with the other 16-byte memberwise copies.
  QuadStrip2D.cpp, whose strip vector this element type belongs to, now defines it out of line with a
  `fold-proof` row (`--icf-owner ??0Region2D@@QAE@ABU0@@Z`). It cannot be defined in the insert unit:
  with the body in view, cl hoists insert's `[ebx+4]` load above the call, and the 149-byte row
  fails. That holds for an inline `noinline` and for an out-of-line definition after the
  instantiation alike. The unit still fails link_check on two COMDAT bodies (`_Construct`,
  `_M_insert_overflow`: not retail's). Those are census matters, not real-link errors.
- **RegionDetailsStructuresIconCtor.cpp (3): 2 resolved, 1 open.** The Icon constructor's unwind
  funclets 0x007A3555/0x007A3560 call 0x005E211F and 0x00238D97, the 7-byte vptr stores of C77E7C and
  BED658. The view's `IconMouseObserver` and `LivingWorldBuildPlotObserver` now restore their vptr
  inline, and each destructor gets a `fold-proof` row there (`--icf-owner` the `Disp0DwordImmSetters`
  apply rows). This follows the `Rva005CE804Observer` and `Rva0023A128Listener` precedent at
  0x00238D97. Both scaffold funclets moved off `Code/gen_small` onto the constructor's own labels
  (eh_verify EXACT); they were blocked on these rows (re_attempts, LINK-095). link_check over
  Rva005E278EDtor, Disp0DwordImmSetters, LivingWorldScoreKeeper, Rva0023A128Ctor,
  Rva005CE804Constructor, the RegionDetailsStructuresPage TU and OpaqueScalarDeletingDtorsB16 shows
  no change; all stay LINKS.
  - Still open: `??1Icon@Impl@RegionDetailsStructuresPage@StrategicInGameUI@@UAE@XZ`. The destructor is
    rowed `??1Rva005E278E@@UAE@XZ` (0x005E278E, Rva005E278EDtor.cpp), with its `??_G` 0x005E283B, its
    handler 0x007A3531 and four funclet parents. `rename.py class --fold Rva005E278E --into Icon`
    refuses because T = 0x00C77B28 is named `??_7Icon@Impl@RegionDetailsStructuresPage@StrategicInGameUI@@6B...`,
    not `??_7Icon@@6B@`. A nested NEW name is "not a type identifier", so `--into` with the full
    `StrategicInGameUI::...::Icon` refuses too. Prerequisite: nested-class support in `class --fold`,
    or a reviewed reconciliation like `a5901cee17`. The destructor view's bases (Rva005E278EBase0,
    Rva005CCC07Base, LivingWorldLogicObserver) are the same tables as the constructor's (Rva0007DF07,
    IconMouseObserver, LivingWorldBuildPlotObserver) under other names, so one spelling has to be
    chosen.
- **W3DMouse.cpp (1): resolved.** `56af6ee282` gave initD3DAssets retail's second, action-less unwind
  state with a Zero Hour `AsciiString` local in the dead cursor loop. That emitted out-of-line ZH
  `releaseBuffer`/`set` COMDATs calling ZH-only `AsciiString::freeBytes`, so W3DMouse.obj was the first
  copy in link order. The local is now BFME 2's `StringBase<char>` from the canonical
  `reference/shims/bfme2_ascii/string_base.h`; its release is the out-of-line 0x00036410. The rows stay
  22/22 exact, and eh_verify is EXACT 4/4 with initD3DAssets EXACT. A TU-local type with an inline
  destructor (inline, `noinline`, or a noinline `operator=`) loses the state, because cl drops it
  once it can see that nothing in the scope throws. First-copy check: W3DMouse led only
  `?releaseBuffer@AsciiString@@IAEXXZ` (next copy ProductionPrerequisite.obj, the only other toucher,
  which calls freeBytes too) and `?set@AsciiString@@QAEXABV1@@Z` (its only copy, verdict wrong, no
  other toucher). The new `??0?$StringBase@D@@QAE@XZ` copy matches the first copy (W3DDisplay.obj,
  position 804) by digest. `freeBytes` stays unresolved until ProductionPrerequisite.cpp (Codex's
  slice) stops emitting its own ZH `releaseBuffer` copy. `reverse/eh_baseline.csv` still lists
  initD3DAssets, though it has been EXACT since `56af6ee282`.
- **Rva005776A7Ctor.cpp (3): blocked on class identity tooling.** Vftable 0x00C6E8F8 holds
  PlanRetreatsPhaseBehavior::Impl::translateGameMessage (0x005771F4) at slot 0 and
  `OnMouseLeftClick` (0x0057723C) at slot 18. The constructor 0x005776A7 and the destructor 0x005770F7
  (`??1Rva005770F7`, Rva005770F7Dtor.cpp) both install it, so both placeholders are
  `StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl` over the canonical 26-slot UserInputTranslator.
  `s0`/`r0` are that translator's slots under a 2-slot private view; `??1Rva005776A7` is the
  destructor's other spelling. `rename.py class --fold Rva005776A7 --into Rva005770F7` refuses (the
  constructor's +0 stores install 0x00C6E430 before 0x00C6E8F8), and a nested NEW is not accepted.
  Prerequisite: nested-class `--fold` support, or a reviewed reconciliation like `a5901cee17` for
  PlanningPhaseBehavior::Impl (constructor beside destructor, UserInputTranslator base,
  ManualPhaseEnder record bound to `??1Wrap2000576C4B`).
  Link cleared 2026-11-04 (claude2): `s0`/`r0` made pure in the private view, as
  Rva00574CC1Dtor.cpp already spells the 0x00429191 carrier; 6/6 rows match and `link_check.py`
  reports LINKS (0 -> 170 bytes). The Impl class identity above is still open.
- **LivingWorldManagerCtor.cpp (1): blocked.** `Rva0022B12DSubsystem` is LivingWorldManager: the
  constructor installs 0x00BE5234, whose slot 0 is the `??_G` of `??1LivingWorldManager` (0x00214405).
  `--fold Rva0022B12DSubsystem --into LivingWorldManager` refuses: that slot is rowed
  `??_GRva00214405` in OpaqueScalarDeletingDtorsB04.cpp, which carries
  `/alternatename:??1Rva00214405=??1LivingWorldManager`. `--fold Rva00214405` refuses too (no
  installing row). The placeholder is also a template argument in SubsystemInterface.cpp's
  `initSubsystem`/`SubsystemSlot` rows. Prerequisites: respell the `??_G` row under LivingWorldManager
  and retire the alternatename, then fold the constructor class and its template-argument rows.
- **T1Base005F3750Ctor.cpp (1):** unchanged; see rl-o3's analysis above (mixed placeholder classes).
- Claims released: Rva005776A7Ctor.cpp and Rva005770F7Dtor.cpp (no edit).

**Design note: nested-class `class --fold` (rl-o4, 2026-11-04; banked, not built).** It would unblock
`??1Icon` (1) and Rva005776A7Ctor (3). The current gates and how each needs to change
(`tools/rename.py`, `plan_fold`/`fold_evidence`):
1. **NEW spelling.** Accept `A::B::C` with every part an IDENT; `plan_fold` checks `IDENT.fullmatch`
   at its top. The mangled scope is the reversed parts: `Icon@Impl@RegionDetailsStructuresPage@StrategicInGameUI@`.
   OLD stays a global placeholder.
2. **Ledger respelling.** `frag.sub(new, name)` swaps one token. For a nested NEW, replace only OLD's
   scope token (`??1OLD@@`, `??_GOLD@@`, `??_EOLD@@W..`, `??_7OLD@@6B..`, `?m@OLD@@`). Refuse a symbol
   that spells OLD in a type position (`V OLD@@`, `VOLD@` back-reference `0`) or carries any
   name back-reference digit after the scope: the nested scope adds len(parts)-1 entries to MSVC's
   name table, so later back-references shift. Also refuse a symbol whose remainder spells one of
   NEW's components, because cl would compress it to a back-reference. Today's targets need none of
   this: `??1Rva005E278E@@UAE@XZ`, `??_GRva005E278E@@UAEPAXI@Z`, `__ehhandler$`, `parent=` tokens,
   `??0Rva005776A7@@QAE@PAVRva005772BF@@H@Z`.
3. **Evidence regexes.** `SPECIAL_MEMBER` and `GLOBAL_VTABLE` (`\?\?_7([A-Za-z_]\w*)@@6B`) and the
   T-names check (`??_7NEW@@6B@`) read one identifier. They need a scope form
   `((?:[A-Za-z_]\w*@)+)@`, compared as the reversed `::` spelling. The data ledger already binds
   0x00C77B28/0x00877B04/0x00877B0C to `??_7Icon@Impl@RegionDetailsStructuresPage@StrategicInGameUI@@6B...`,
   so the "T names NEW" gate is satisfiable.
4. **Sources.** `rewrite_tokens` cannot turn `class OLD : ...` into a nested definition, because it
   does not know whether the enclosing scopes are namespaces or classes, or how the unit declares
   them. Take the C++ as `--prepared REL=FILE`, the way `function --to-class` does, and keep the
   tool to the ledger respelling and the gates. The build plus `commit_checks` decide.
5. **PlanRetreats needs one more gate decision.** Neither direction passes today:
   - `--fold Rva005776A7 --into Rva005770F7`: OLD's only row is the constructor, and it installs
     0x00C6E430 before 0x00C6E8F8 at +0. The "all +0 stores install T" rule finds no own table.
   - `--fold Rva005770F7 --into Rva005776A7`: refused because the adjustor `??_ERva005770F7@@W3AEPAXI@Z`
     (0x00577185) has no owning row that installs a +4 table. The destructor restores +4 only through
     the out-of-line base destructor, and the constructor is not an own-table row.

   Possible rule: a constructor's last +0 store is its own table, which `own_secondary` already
   assumes for +disp. That is a weaker-evidence gate change: Verifier-Change commit plus
   `tools/tests` cases, including the 0x007CEFA0 three-class ICF table, which must still refuse.

   PlanningPhaseBehavior::Impl was reconciled by hand in `a5901cee17` (pre-tool); its unit
   Rva00575F38Dtor.cpp is the template for the prepared sources.

**Seat halilkkaya-lk23 (2026-11-04, real link 41825144174 at `efbd3f2cb2`: 55 unresolved, 1 duplicate).**
- **Tool: `rename.py class --fold` takes a nested class (`ea1cc82ec2`).** Use `--into A::B::C` and pass
  every unit that spells OLD as `--prepared REL=FILE`, declaring the enclosing scopes and no longer
  spelling OLD. Mangled names take the decorated scope (`C@B@A`). A respelled symbol may carry no name
  back-reference, and the result may not spell one of NEW's names twice. All other gates are unchanged.
- **Tool: vftable stores are read relative to `this` (`8a94b4fdd4`).** `this_stores` follows registers
  that hold `this + d` (`lea edi,[esi+4]; mov [edi],T` is a +4 store). That was the PlanRetreats +4
  adjustor false reject. A constructor whose every store is proven owns its last +0 store. The design
  note's plain "last +0 store" would have picked 0x00C6E8EC, the +4 table, for 0x005776A7.
- **RegionDetailsStructuresIconCtor.cpp (1): resolved** (`7e3f21faab`, fold Rva005E278E into
  `StrategicInGameUI::RegionDetailsStructuresPage::Impl::Icon`, vftable 0x00C77B28). The unit goes
  0 → 231 B LINKS.
- **Rva005776A7Ctor.cpp: `??1Rva005776A7` resolved** (`a68e83af11`, fold Rva005776A7 into Rva005770F7,
  vftable 0x00C6E8F8). Still open: `r0`, `s0` and the `??_7Gen_uwm_00429191` COMDAT variant.
  - The +0 base is canonical UserInputTranslator: retail 0x00C6E430's 26 slots are
    `UserInputTranslator.h`'s.
  - Adopting that header alone gives the derived table UserInputTranslator's bodies at slots 0 and 18,
    where retail has Impl's 0x005771F4 and 0x0057723C. That is a runtime-wrong table. Overriding them
    under the placeholder spells `?translateGameMessage@Rva005770F7@@...`, which nothing defines.
  - So the class must first be named `StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl`.
    `--fold Rva005770F7 --into` that name refuses: nothing names 0x00C6E8F8 for Impl. There is no
    data_ledger row, and the installers' objects bind only the placeholders' tables.
  - The remaining evidence is the slots: 0 and 18 hold Impl's rowed virtuals, and no other table holds
    them. It is not encoded as a gate. An intermediate base whose empty destructor drops its own vptr
    store cannot be told apart. Retail `~UserInputTranslator` (0x00429191, 7 bytes) stores only Base0's
    0x00BDBA74.
  - Maintainers must decide: accept slot evidence for these Impl names (`a5901cee17` did so by hand),
    or a WorldBuilder-basis naming route.
- **Gate caveat.** The destructor rule "first +0 store is its own table" misreads a destructor whose
  own vptr store is elided, when its first store is a base's at +0: `~UserInputTranslator` above. The
  "T names NEW" check is the backstop.
  - The null-guarded case is fixed (`071899a749`). 0x003ABA36 stores 0x00BBB554 at
    `[this ? this+0x18 : 0]` (`neg/sbb/and`), and `this_stores` now reads that store at +0x18.
  - `--fold Rva003ABA36 --into T1Base_005F3750` now refuses on the copy constructor's own 0x00C1D55C
    against T1Base's 0x00C1D3F4. That agrees with rl-o3: the placeholders are mixed.
- **LivingWorldManagerCtor.cpp:** unchanged. `--fold Rva0022B12DSubsystem --into LivingWorldManager`
  still stops at slot 0's `??_GRva00214405`.
- **T1Base005F3750Ctor.cpp: resolved by method 2.** The class is `__declspec(novtable)`. Its constructor
  stores retail's 0x00C1D3F4, 0x00C1C780 and 0x00C1D3E4 by hand from `extern "C"` tables whose slots
  name the rowed bodies. `??1T1Base_005F3750` and `??_GT1Base_005F3750` are no longer referenced, and
  5/5 rows match. `link_check` names no unresolved symbol; the only remaining verdict is the pre-existing
  `??_7DefaultDrawModuleInfo@FXParticleSystem` comdat order note. The class identity fold above stays open.

**Seat halilkkaya-lk29 (2026-11-05, real link run 42035295927 at `dbde7dbe3b`: 10 unresolved, 0 duplicates).**
- **W3DScriptedModelDrawDestructor.cpp `?GetSnapshotName@DrawableModule@@MBEPBDXZ`: cause found, fix
  prepared, blocked on a claim.** New since the link at `50ff761bcd`. `f3fbb9188c` adopted the canonical
  `DrawableModule.h`, whose slot 2 nothing defines. Retail's body is 0x00252B84, rowed
  `?name@Rva00252B84Named@@QBEPBDXZ` in SubsystemNameGetters.cpp. The fix is `rename.py function --to-class
  DrawableModule` with DrawableModuleCtor.cpp prepared on the canonical header. That preparation is
  trial-verified: 1/1 bytes, and retail 0x00C07E54's slot order, with only this name left unresolved.
  SubsystemNameGetters.cpp is held by yasinschroeder-claudeb2 (`class:LivingWorldBuilding`).
  [Handoff](../../reverse/attempt_support/drawablemodule-getsnapshotname-to-class-20261105-lk29.md).
  Landed 2026-11-05 (claudeb2) as planned: link_check names no unresolved symbol for the unit; real link to confirm.
- **`?ji_006291ae@@YAPAXPAXHI@Z`:** resolved by `b4c9b2d8a8` (Ancalgonn). `811358bb29` removed the body,
  which `Rva00219B9EAccessor.cpp` still reaches through `/alternatename`.
- **LivingWorldManagerCtor.cpp `??1Rva0022B12DSubsystem@@UAE@XZ`: first prerequisite done.** Slot 0 of
  0x00BE5234 is now rowed `??_GLivingWorldManager@@UAEPAXI@Z` (0x002146B8), and 0x00214058 is rowed
  `??_ELivingWorldManager@@WM@AEPAXI@Z`. Both are in LivingWorldManagerDtor.cpp, which already emits
  them byte-identically. B04's `Rva00214405` class, its `/alternatename` and two pins are gone, and
  link_check totals are unchanged (32,395 B). `--fold Rva0022B12DSubsystem --into LivingWorldManager`
  now stops at the canonical-class check. GameEngineInit.cpp, LivingWorldManagerCtor.cpp and
  SubsystemInterface.cpp declare the placeholder class, so the fold would make private copies.
  `run_batch(source_edits=...)` can couple their header adoption with the fold, but the constructor unit
  cannot adopt the header yet, for two reasons:
  1. The header has opaque byte arrays where the constructor builds typed members (LINK-073).
  2. Its 14-slot table would name `init`, `reset`, `update`, `loadPostProcess`, `GetSnapshotName` and
     `xfer` under LivingWorldManager. All of these are rowed under placeholders (0x00210D0D, used by
     two slots, 0x002123BE, 0x00210F27, 0x00214052, 0x00213D93). Adopting the header would trade one
     unresolved name for about six.
  Prerequisites: real member types in the header, then the slot names (`function --to-class`; 0x00210D0D
  needs its fold first), then the coupled fold.
- **EvacuateDamageCtorModuleFactoryBody.cpp `??1PB_DeepBase@@UAE@XZ`:** unchanged. 0x004B96CC is still
  `??1Rva004B96CC` (re_attempts.log entries for 0x0002CD7B and 0x004B96CC), and 0x0002CD7B is still misnamed `~EvacuateDamage`.
  Not attempted: DamageModule is lk28's this session.
- **ProductionPrerequisite.cpp `?freeBytes@AsciiString@@AAEXXZ`:** LINK-182's PerTurnStats plan is still
  not feasible. `LivingWorldScoreKeeper.h` still has `Rva004EE501` and only forward-declares PerTurnStats.

**2026-11-08 module constructor Thing adoption:** DrawableModuleCtor.cpp and
ObjectModuleCtor.cpp replace their short private Thing views with the canonical
header and its existing public friend helpers, locally force-inlined. All three
rows and both parent EH graphs pass; owning-tool acceptance retires two header
debts. Retained code, relocation bindings, flags, policies and named data remain
equal. Added framed helper copies do not displace the native earlier providers
in cached census or default real-link path order; strict native-provider receipts
are current. Paired checks pass and preview conserves LINKS/226 bytes. This
clears only the two header debts, with full current image and TU recovery open.
[Helper emission and selection proof](../../reverse/attempt_support/thing-module-header-adoption-20261108/README.md).

Published as b38a3024b4; first attempt landed in 50.8 seconds. Required
row/EH/scoped-DIR32 checks pass after rebase. Broader link audit remains
INCONCLUSIVE: index d171e84869 versus outgoing base
195accef7eb242f0247ea449bf48c6d07435daa7; Common/AICowerState_onEnter.cpp
lacks a current receipt. AIBaseBuilder now has a local current receipt, but
this does not change the earlier recorded audits or establish image closure.

**2026-11-08 Thing header dependency cohort: DamageNugget.cpp** adopts canonical
Thing, Matrix3D and Vector3 together and retires three owning-tool header debts.
All 14 source rows, three EH graphs and eleven floats remain exact; strict
provider preparation and staged-peer checks pass. Twenty-seven retained code
COMDAT facts/flags/policies and seven named data allocations agree. The two
omitted helper copies retain current earlier native providers. The emitted
Normalize copy now matches all 100 native bytes at0x0006924F, replacing a
57-byte copy, with its existing ownership untouched; the added iterator is
native-exact. Preview conserves LINKS/1,393, with no new coverage or image
clearance. Canonical Object, remaining views and TU consolidation stay open.
[Complete provider and copy proof](../../reverse/attempt_support/damage-nugget-header-adoption-20261108/README.md).

Published as e834581c00; first attempt landed in 43.2 seconds. Required
row/EH/scoped-DIR32 checks pass. Broader audit remains INCONCLUSIVE: index
d171e84869 versus outgoing base ca053513b317febbcba85988de518b2b40da03a7;
DamageNugget itself lacked a current strict receipt after rebase. A local
post-publication refresh passes 19/19 rows across it and the two explicit
providers, and the full scoped object/provider proof passes again. This
refresh does not rewrite the recorded push audit or establish image closure.

**2026-11-08 AutoDeposit Thing header queue follow-up:** the old m_08 view is
already absent from AutoDepositUpdateCtor.cpp. The explicit canonical Thing
include passes owning-tool acceptance and retires one header debt. Both rows,
62 retained code COMDAT facts/flags/policies, three named data allocations and
undefined references agree; the sole added iterator matches native and the
existing provider policy. Strict preparation passes; preview conserves
LINKS/144. No new coverage, table-bridge or full-image clearance is claimed.
[Scoped proof](../../reverse/attempt_support/auto-deposit-thing-adoption-20261108/README.md).

Published as a2b72d5896; first attempt landed in 40.7 seconds. Required
row/scoped-DIR32/data checks pass. Broader audit remains INCONCLUSIVE: index
d171e84869 versus outgoing base e834581c00d638d23b569831da5d7be01f7c999f;
Common/AICowerState_onEnter.cpp lacks a current receipt. No wider closure
or runtime claim is made.

**2026-11-08 Object death-handler Thing adoption:** ObjectOnDie.cpp replaces
its private 0x48-byte Thing prefix with the canonical 0x60-byte class and
shortens following padding to preserve Object offsets. All three rows and
the parent EH graph pass; one owning-tool header debt is retired. Eleven
retained code COMDAT facts/flags/policies and three data allocations agree.
The omitted getTemplate copy retains an identical, strictly current earlier
Recorder provider; the added iterator is native-exact. Strict preparation
passes 142/142 across the two sources. Full Object/TU and image recovery
remain open; no new coverage or runtime clearance.
[Accessed offsets and provider proof](../../reverse/attempt_support/object-on-die-thing-adoption-20261108/README.md).

Published as 5cb5a9defb on attempt 3 (38.2 seconds for the successful
attempt); two lost races retried through push.py with reused verification
receipts. Required row/EH/scoped-DIR32 checks pass. Broader audit remains
INCONCLUSIVE: index d171e84869 versus outgoing base
6d2b4678a617b00bb5bf9f4f475eaf9b12fa238d; Common/AICowerState_onEnter.cpp
lacks a current receipt. Ordinary preview conserves LINKS/807 and still
reports unchanged, unreferenced clearStatusBit/setStatusBit variants; those
are not cleared by this header adoption.

**2026-11-08 canonical Thing accessor / AnimalAIUpdate:** the existing
getTemplate accessor gains its inline body after the canonical class; Animal
adopts the header and preserves accessed Object offsets. The final header
form passes 18,890 row checks across 1,734 sources and 2,504 exact EH graphs;
one existing baselined NetCommandWrapperList exception is outside this header
dependency. All 15 Animal rows and three EH graphs pass; one owning-tool
header debt is retired. All 13 emitted getters in scope retain the existing
four-byte body. Full-scope variant checking passes. No native accessor RVA,
new coverage or image/runtime clearance is claimed. Remaining Animal AI
interface/header and TU work stays open.
[Declaration-order controls and scope proof](../../reverse/attempt_support/animal-ai-thing-adoption-20261108/README.md).

Published as d44889a491 on attempt 2 (866.3 seconds for that attempt).
The carried check refreshed 5,787 stale source objects and passed all
41,331 row checks plus strings, floats, imports, full DIR32 consistency and
module registry. The broader link audit remains INCONCLUSIVE: index
d171e84869 versus outgoing base 314cbfd1c1be15d969daacd816a3033036bb471e;
three source objects lacked current strict receipts, first AnimalAIUpdate.
No full-image or runtime clearance is claimed.

Animal's canonical AICommandParms adoption also passes, retiring one further
header debt with all 15 rows and three EH graphs exact. AI interface and full
class adoption remain prerequisites; LINK-592 records the removed helper's
strict replacement-provider proof and the unchanged link preview.

**2026-11-08 Animal AI interfaces:** canonical AICommandInterface and
AIUpdateInterface adoption now clears two further header debts. The primary
bridge supplies the canonical parent's secondary update call; the command
bridge preserves its proven receiver and register allocation. All 15 rows
and three EH graphs remain exact, with all 63 code COMDAT facts, 30 named
data allocations and external bindings unchanged. Preview still conserves
LINKS/3,167 bytes. The complete Animal class, its donors and TU composition
remain open; no current image or runtime clearance.
[Receiver controls and object proof](../../reverse/attempt_support/animal-ai-interfaces-adoption-20261108/README.md).
