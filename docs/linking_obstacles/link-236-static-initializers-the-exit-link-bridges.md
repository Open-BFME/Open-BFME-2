### LINK-236: static initializers the exit link bridges

Status: open (lane started 2026-11-04 by halilkkaya-in-o1 at `993e6014c8`; halilkkaya-in-o2 at
`f2cec2a7f8`: report tie fix, Drawable.h constant and 84 rowed copies, bridged 969 -> 885 on the
fixed report; halilkkaya-in-o3: BlockParse registrations are per-unit file-scope nodes, 40
rowed in their units, bridged 885 -> 845; halilkkaya-in-o4: the msgr/thtr service records are
file-scope objects of the 0x0065D090 constructor, 64 registered, and the 62 transaction records
of its 0x0065D070 sibling, plus 2 BlockParse nodes, bridged 845 -> 717; halilkkaya-in-o5: 17
private-view units adopt the canonical Drawable.h and row their copies, bridged 717 -> 700, then 3
more, bridged 702 -> 699 on the report with `registered_comdat_copies_discarded`;
halilkkaya-fix-o1: 7 round-2 includes moved below their units' Snapshot includes, restoring the
vtables they had shifted, bridged 699 unchanged; halilkkaya-in-o5 then 7 units free since round 2,
bridged 699 -> 692; halilkkaya-in-o6: 7 BlockParse nodes rowed in the units whose `.text$yc` run
holds them, bridged 692 -> 685, then Network.cpp's two timeGetTime initializers, bridged 685 -> 683,
and the ZeroInits masks traced to a giant-bird header, not AerialPathfinder.h; halilkkaya-in-o7:
the small grab-bags' forms recorded, 4 FrameRate/GlobalInits entries rowed in their owners, bridged
683 -> 679, then the AttributeModifierStore and BannerUI copies, bridged 679 -> 677, and
AISpellBookShroudReveal's `g_00E06648`, bridged 677 -> 676, and Drawable.cpp's two, bridged
676 -> 674; next seat continues).

`initializers_bridged` (real link at `612abfbebb`: 961) counts the entries in retail's `.CRT$XCU`
table that no kept object registers. `tools/exit_link.py` registers them from a generated
`retail_initializers.obj` so that an image can start. The exit test needs the count at 0, with every
entry registered by real source. This entry records how the count is measured, the method that
retires an entry, and what remains.

**Mechanism (MSVC 7.1, target and object facts).** A global with a dynamic initializer makes its
object emit a TU-local `_$E<n>` in `.text$yc` and a DIR32 to it in `.CRT$XCU`. A global with a
destructor also gets an atexit cleanup `_$E<n+1>` in `.text$yd`. Every object numbers its own
ordinals, so two TUs' `_$E1` are different functions. The VC 8 `??__E` names in the ledger are labels
only; the object symbol is `_$E<n>`. The linker sorts `.text$yc` and `.text$yd` to the end of
`.text`, which is why retail's initializers sit together at 0x007AB7F0..0x007B67FF and the cleanups
at 0x007B6880 and later. `_initterm` runs the table in link order, and each TU's entries are
contiguous in definition order.

**Measuring locally.** `python3 tools/image_report.py --out build/<dir>` takes about 20 s over the
`build/match` objects (no link, allowed for seats). It writes `initializers.not_registered_rvas`,
`plain_functions`, `twice`, `by_shape_only` and `unidentified`. `image_report.bridge_entries(rows,
kept)` gives exactly the list `exit_link` bridges.

**Tool fix `212c0525c0`.** The 2026-11-03 report credited each object's `_$E1` to the first ledger
row aliased `_$E1`, so its numbers were wrong:
- the "54 `??__E` rows nobody registers" were all registered;
- the 60 "unreachable" entries were registered too;
- the 27 "registered not in retail" were atexit ordinals credited by name.

Now a `_$E<n>` is read only in its own object. An unrowed one is first narrowed by masked shape;
then its relocations pick the entry, because each DIR32 and REL32 target must land where the ledger
places it.

| Measure (on `993e6014c8`'s objects) | Old | New |
| --- | ---: | ---: |
| Registered | 145 | 228 |
| Bridged | 961 | 938 |
| Unreachable | 60 | 0 |
| Registered twice | not reported | 116 |
| Unidentified | not reported | 342 |

**Method to retire an entry (`a8956992cd`, `a3743fba03`, 0x007AE9E6, bridged 938 -> 937).**
1. Read the plain row's body. It names the global it builds (DIR32 store or `mov ecx, g`).
2. Find the global's owner in `reverse/data_ledger.csv`. The initializer row belongs with that
   definition.
3. In the owner, give the definition its initializer: `unsigned int doubleClickTime =
   GetDoubleClickTime();`. The spelling comes from the Zero Hour donor's `GadgetListBox.cpp`; keep the
   linkage the ledger name has.
4. `./build.sh` the owner, then read its object's `.CRT$XCU` and the new `_$E<n>` body. They must equal
   retail's bytes.
5. Commit the retraction on its own: delete the plain row, add a line to `reverse/deleted_rows.csv` and
   remove the body. `add_match --replace-rva` takes over only scaffold rows.
6. Then run `add_match '_$E<n>' <rva> <size> <owner>`. A bare `_$E<n>` row is not a hatch
   (`hatch_counters` rule 9).
7. Re-run `image_report`: the RVA should leave `not_registered_rvas`. Also run link_check and scoped
   DIR32 checks on both files.

**What is left (937 bridged, all plain function rows), by grab-bag file:**

| Grab-bag file | Rows |
| --- | ---: |
| `Rva007AB7F0HalfRateInits.cpp` | 425 (341 after in-o2, 314 after in-o5) |
| `INI/Rva007ABBF6BlockParseInits.cpp` | 130 (90 after in-o3, 88 after in-o4, 81 after in-o6) |
| `StaticTagInitializers.cpp` | 63 (0 after in-o4) |
| `GameNetwork/Rva007B55E0TxnNameInits.cpp` | 62 (0 after in-o4) |
| `Rva007AD295ZeroInits.cpp` | 56 (attribution notes below) |
| `Rva007ABC6FFrameRateInits.cpp` | 31 |
| `Rva007ABEF3ArgCtorInits.cpp` | 16 |
| `Rva007ABBB3CtorInits.cpp` | 13 |
| `Rva007AB85CAtexitInits.cpp` | 12 |
| `Rva007AC6DDGlobalInits.cpp` | 12 |
| Smaller files | about 100 |

Most rows say "owning TU unrecovered". The work is attribution first, then step 3 in the owner.

**HalfRateInits (425 rows): `DRAWABLE_FRAMES_PER_FLASH` (halilkkaya-in-o2, 2026-11-04).**
- *Target facts.* 442 table entries share one 16-byte body, `mov eax, [0x00DBA4E8]; cdq; sub eax,
  edx; sar eax, 1; mov [s], eax; ret`: 425 in `Rva007AB7F0HalfRateInits.cpp`, 16 in
  `Rva007ABC6FFrameRateInits.cpp`, one in `Rva005AB309Tactic.cpp`. Seven copies are read.
  `Drawable::updateDrawable` does `getFrame() % [0x00DFEB98]` (0x00275A30 `div`, `test edx, edx`),
  and ScriptActions' flash actions do `frames / [0x00E02D9C]` (0x003BB5ED `idiv`). Those are the
  two uses Zero Hour makes of `DRAWABLE_FRAMES_PER_FLASH` (Drawable.cpp, ScriptActions.cpp).
- *Other half-rate constants.* Three of the read copies are other constants that share the body.
  SpawnBehavior::update reloads `[0x00E035C8]` (Zero Hour `SPAWN_UPDATE_RATE`, SpawnBehavior.h).
  W3DDisplay::updateAverageFPS reads `[0x00DE1B50]` (BFME 1 `START_CUMU_FRAME`, W3DDisplay.cpp).
  ControlBar::processCommandUI reads `[0x00E05F24]`. Each of these units also has its own
  Drawable.h copy (0x00E035C4, 0x00DE1B4C, 0x00E05E18).
- *Header.* The canonical `GameClient/Drawable.h` now defines `const int DRAWABLE_FRAMES_PER_FLASH =
  BfmeClientFramesPerSecond / 2;`. Every includer compiles the retail body as its own `_$E<n>`
  over a static named `_DRAWABLE_FRAMES_PER_FLASH`.
- *Ordinals.* The new initializer moves later ordinals by two. Two units had `object-symbol=_$E<n>`
  cleanup rows: `UnitRevivalTracker.cpp` (4, 5 -> 6, 7) and `GameLogicDispatchDoSetRallyPoint.cpp`
  (2, 3, 5 -> 4, 5, 7). A stale `_$E5` there still verified, because the moved cleanup has the same
  masked bytes. Read each ordinal's relocation targets, not only its bytes.
- *Retail .text$yc layout (target fact).* After each unit's Drawable.h copy comes an unregistered
  26-byte `push -1; push 0; mov ecx, 0x00DA60E8; call; push; call atexit`. There are 716 such
  copies in .text$yc, and only the first (0x007AB800) is in the table: a selectany pool whose
  .CRT$XCU entry the linker kept once. Each copy marks one unit, which bounds unit runs in the table.
- *.bss order (target fact).* A unit's dynamic-init statics come after its other statics, so a copy's
  static follows its own unit's data. The draw modules show it, for example
  `$S1@getModuleNameKey@W3DDefaultDraw` at 0x009EA308 followed by the copy at 0x009EA30C. So do
  W3DDisplay's statics, then 0x00DE1B4C, then `START_CUMU_FRAME`.
- *Measurement.* The header alone moves no figure (`image_report` `a0399b2d38`). The 256 copies stay
  unidentified until a row names each one. The old report credited them by the shared rate vote
  (bridged 937 -> 681), which was false.
- *Rowed (29, `6aa90adf0b` + next).* An entry is attributed only when all of these hold:
  - its static directly follows a function-local static guard (`$S<n>`) of the unit's own class;
  - no other copy claims that TU;
  - the approved TU file is the only file of its TU that includes Drawable.h;
  - its object compiles the copy.

  The row retracts the HalfRateInits body and readmits `_$E1`/`_$E2` in that file.
  `reverse/attempt_support/link236-drawable-frames-per-flash-attribution-20261104.tsv` gives every
  remaining copy's neighbour, its TU and why it waits. 144 wait for their TU to include Drawable.h,
  and 55 for a merge or a stale receipt. 85 have no neighbour with a TU, and 112 sit where tu_map
  gives one TU to several copies, so that neighbour data is mis-assigned. For these, use the
  .text$yc pool-init markers before trusting tu_map.
- *Included (round 2).* 108 of the 144 "TU does not include Drawable.h yet" copies sit after a `$S<n>`
  guard of their unit. Of those, 70 TU files were claimable (32 were held by other seats, 6 do not
  exist). Each got `#include ".../GameClient/Drawable.h"` after its first include and was built on
  its own:
  - 48 stayed byte-exact and compile the copy; they are rowed in this series;
  - StatusBitsUpgradeIfEldestKindof was held back. It already fails link_check (unresolved
    `UpgradeMux::setUpgradeExecuted`, census 245 -> 0) without the include;
  - 21 do not compile with the canonical header, or change bytes, and were reverted. Their
    private `Thing`/`Drawable`/`Snapshot` views or other header conflicts come first: W3DTankDraw,
    PhysicsUpdate, PlaceEventTranslator, ClickReactionBehavior, GiantBirdSlowDeathBehavior,
    TunnelContain, CitadelSlaughterHordeContain, RefundDie, RebuildHoleExposeDie, UpgradeDie,
    OilSpillUpdate, FlammableUpdate, SlavedUpdate, SupplyTruckAIUpdate, RespawnUpdate,
    GeometryUpgrade, TooltipUpgrade, SquishCollide, AODCrushCollide, ActiveBody, HeroDie.
- *Fragments (round 3).* TransportContain.cpp and MonsterDockUpdate.cpp already compiled their copy
  beside one more fragment of the TU that includes Drawable.h. Each TU file's copy is rowed, and
  the fragment's copy stays unidentified until the merge. BuildingBehavior (0x007B0920) is the
  same case, held by another seat.
- *Guard's own file (round 4).* tu_map's data rows put several copies in one TU. For copies after
  a `$S<n>` guard, the guard's defining file (data ledger `source`, mapped to its TU by code rows)
  is better evidence when the guard's class names that TU file. It gave 58 more units with a unique
  copy. 13 were claimable, and 5 took the include and are rowed: W3DLaserDraw, W3DFloorDraw,
  GarrisonContain, SpawnPointProductionExitUpdate and OathbreakersFadeAwayBehavior. 8 do not
  compile with the header: W3DDebrisDraw, W3DLightDraw, ProjectileStreamUpdate, AutoHealBehavior,
  BridgeBehavior, AODHordeContain, AssistedTargetingUpdate and ModelConditionAudioLoopClientBehavior.
  36 are held by other seats, and 9 include another `Drawable.h` that builds no copy.
  2026-11-04: W3DFloorDraw absorbs its accepted Xfer and pool-key donors (24 rows preserved); no census gain is claimed. Shadow identity/data findings and the provider-consumer audit are in [the handoff](../../reverse/attempt_support/siegedeploy-consolidation-20261104.md).
- *Private views (round 5, halilkkaya-in-o5).* 17 of the 29 refused units now take the canonical
  header without editing it, and each copy is rowed as its unit's `_$E1` (W3DDebrisDraw `_$E2`).
  Three causes explained every refusal fixed so far:
  - *DamageInfo class-key.* Drawable.h forward-declares `struct DamageInfo` for its rowed
    `rva0027B18C` (`PAU`). MSVC mangles with the first key it sees, so an include before the
    unit's own `class DamageInfo;` renames `onDie`/`beginSlowDeath`/`attemptDamage` to `PBU`
    names the ledger lacks (133 rows spell `PBV`). Put the include after that declaration:
    HeroDie, RefundDie, UpgradeDie, CitadelSlaughterHordeContain, AODCrushCollide, TunnelContain.
    GiantBirdSlowDeathBehavior moves its declaration and the include above its `#define inline
    static inline`.
  - *Snapshot slot spelling.* When Drawable.h is the first to include the Snapshot shim, it
    defines `BFME_SNAPSHOT_NAME_SLOT` and `BFME_SNAPSHOT_CAPITALIZED_SLOTS`. The unit's own
    Snapshot classes then gain slots (RespawnUpdate `[eax+0x1b8]` -> `0x1c0`) or turn abstract
    (SupplyTruckAIUpdate). Put the include after the unit's first Snapshot include: RespawnUpdate,
    W3DTankDraw (after View.h), SupplyTruckAIUpdate, ModelConditionAudioLoopClientBehavior (after
    TurretAI.h). OilSpillUpdate's include goes after its Coord3D ctor view.
  - *Private and older headers.* TunnelContainView.h, ClickReactionObjectView.h and
    GeometryUpgradeView.h held private `Drawable` (and `Thing`) copies; each view has one
    includer and now includes the canonical header. TooltipUpgrade.cpp and BfmeDebrisDrawView.h
    included `DrawableBFME2.h`, which builds no copy.
  - AODHordeContain needed only the include. Its fragment AODHordeContainOnContaining.cpp still
    compiles a second, unidentified copy until the merge.
  - *Private `Thing` layouts (3 more).* SquishCollide's private `Thing` (vptr pad, `tmplate` +4,
    position +0x38, angle +0x44, 0x48 bytes) and RebuildHoleExposeDie's private `Drawable`/`Thing`
    give way to the canonical classes. `tmplate` reads become `m_template`. Each private `Object`
    now pads from the canonical Thing's end (+0x60) to its first own field (id at +0x74).
    RebuildHoleExposeDie's `Object` keeps its inline `getTemplate` over the inherited
    `m_template`. W3DLightDraw takes the include after WW3D2 `rendobj.h`, whose full WWMath
    `Matrix3D` makes thing.h's `Matrix3DData.h` stand down. Its copy is `_$E2`.
- *Units free since round 2 (round 5).* 8 guard-anchored units that round 2 found held were
  claimable. 7 now include the header and row their copy as `_$E1`: ControlBarBeacon,
  AptTimeLineStats, WallHubBehavior, CreateAHeroManager, KeepObjectDie (include after its `class
  DamageInfo;`), W3DSupplyDraw and ExperienceLevelSystem. ExperienceLevelSystem's BlockParse
  nodes move to `_$E3`/`_$E5`, as in-o4 predicted. Their rows were retracted and readmitted, read
  by relocation target. The stale `_$E3` row still verified against the moved ExperienceLevel
  node, because the two node bodies share masked bytes.
  - SiegeDockingBehavior was reverted. With the header first, its vtable takes the capitalized
    Snapshot slots, and SiegeDockingBehaviorDtor.cpp stops linking
    (`??_7SiegeDockingBehavior@@6BObjectModule@@@` differs from the first copy). After its view,
    which defines only `BFME_SNAPSHOT_NAME_SLOT`, the header does not compile (Coord3D). Byte
    exactness does not catch a vtable that changes this way, so run link_check over the unit's
    sibling files.
- *Still refused (round 5).*
  - PlaceEventTranslator compiles with the include at every position tried, but
    `translateGameMessage` swaps two spill slots. Its FreelistPool comment records the same
    declaration-count sensitivity. Its `??__FnoCanDoSound` cleanup would also move from `_$E2` to
    `_$E4`.
  - Zero Hour-shaped units (`PreRTS.h`, Zero Hour `Thing.h`/`Coord3D`): PhysicsUpdate,
    ProjectileStreamUpdate, AssistedTargetingUpdate, FlammableUpdate, AutoHealBehavior,
    BridgeBehavior and SlavedUpdate. The canonical header collides with Zero Hour's `Thing`,
    `Coord3D` and `ModelConditionFlags`. AutoHealBehavior, BridgeBehavior and SlavedUpdate already
    include Zero Hour's `GameClient/Drawable.h`, whose constant is not dynamic.
  - ActiveBody defines private `Matrix3D` (with `Get_Y_Vector`), `Drawable`, `Thing` and `Object`
    views. thing.h's `Matrix3DData.h` lacks `Get_Y_Vector`, so the unit needs the WWMath
    `matrix3d.h` before the header, and then its other views reconciled.
- *Vtable regression from round 2 (halilkkaya-fix-o1, 2026-11-04).* Seven of the round-2 units
  that put Drawable.h first took the capitalized Snapshot slots. Byte verification and their own
  link_check passed, but one vtable in each changed:
  - W3DTruckDraw, W3DBuffDraw, AssaultTransportAIUpdate, SpawnPointProductionExitUpdate and
    UnpauseSpecialPowerUpgradeModuleData now had `__purecall` at slots 1 and 3, with
    `loadPostProcess`/`xfer` moved later.
  - DynamicPortalBehaviour and EvacuateDamage had `xfer` moved from slot 3 to slot 12 and slot 10.
  - W3DTruckDraw is first in link order, so its wrong copy beat W3DTruckDrawDtor.cpp's, and the
    Dtor stopped linking (188 B).

  Each include now follows the unit's first include that reaches the Snapshot shim:
  - W3DTruckDraw and W3DBuffDraw: DrawModule.h;
  - DynamicPortalBehaviour and SpawnPointProductionExitUpdate: AIPathfind.h;
  - EvacuateDamage: ObjectModule.h;
  - AssaultTransportAIUpdate: GameInfo.h;
  - UnpauseSpecialPowerUpgrade: UpgradeModule.h.

  Every `??_7` the seven units emit has its pre-include digest again (read from the object
  store's build of the parent commit), and W3DTruckDrawDtor links again. Their `_$E1` rows stay
  valid. in-o5's round of 7 freed units had the same shift in WallHubBehavior (xfer slot 3 -> 10)
  before it landed; its include now follows `Common/Snapshot.h`, and the other 6 units' tables
  were unchanged.
- *Rule.* After adding or moving an include, compare every `??_7` the unit emits with the unit's
  object before the edit, not only its bytes and its own link_check. A vtable has no row and no
  byte gate, and most of these tables have no sibling copy that link_check could compare against.
  Where a sibling does emit the table (Ctor/Dtor files), run link_check over the unit and the
  sibling together: alone, the sibling is judged against the index's stale copy. The object store
  (`build._objstore_dir` keyed by the old source's md5) holds the pre-edit object.
- *Next.* The handoff table lists each copy's state. ActiveBody and the Zero Hour-shaped units
  need their views or header graph reconciled first. Held units follow the same steps once they
  are free.

**BlockParseInits (130 rows): per-unit `BlockParse` nodes (halilkkaya-in-o3, 2026-11-04).**
- *Target facts.* All 130 entries are one 21-byte body, `mov eax, [0x00DDF578]; mov [node], eax;
  mov [0x00DDF578], node; ret`. Each links one 12-byte `{ next, token, parse }` node onto
  `theBlockParseList`. Retail holds the node's token and parse pointer in .data and next = 0.
  A function-local registration (`Pathfinder::Pathfinder`, 0x002F6F0B) stores all three fields at
  run time instead.
- *What it is.* It is not a header constant. It is a file-scope `BlockParse theXBlockParse("X",
  parse);` whose inline constructor does `next(theBlockParseList)` and `theBlockParseList = this`.
  For a namespace-scope object, MSVC 7.1 builds the constant members in .data and emits only the
  link as `_$E<n>`; a scratch compile gives EXACT 21/21 against 0x007ABBF6. Each object also emits
  the constructor's COMDAT (retail 0x0004147D). So every entry belongs to the unit that defines its
  node. Ordinals step by two (`_$E1`, `_$E3`, ...), after whatever the unit already numbers.
- *Attribution.* The node's callback has an approved TU in tu_map, and the node sits in that TU's
  contiguous .data and .text$yc run in link order (the INI*.cpp files run 0x00DB8934..0x00DB9788).
  INIAudioEventInfo's nodes follow its own name lists at 0x00DB8A80. MiscEvaData's callback
  (0x001DCFE5) comes before Eva's code while its node comes after Eva's nodes, so Eva owns it.
  Zero Hour's `INI*.cpp` wrappers explain the nodes whose callback lives elsewhere: in CommandSet,
  CrateData and DamageFX, the node calls the store's parser directly. These nodes still wait for an
  `INI*.cpp` unit our tree does not have.
- *Rowed (40, this series).* Each owner defines the struct with its inline constructor (a
  TU-scoped view; there is no canonical declaration yet). Each owner also defines the node at the
  end of the file, so no earlier ordinal moves. Each node's data row is repointed to its owner, and
  the address is readmitted as `_$E<n>`:
  - GameLOD: ReallyLowMHz..AudioLOD (`_$E27`..`_$E39`);
  - INIAudioEventInfo: MusicTrack..Multisound (`_$E2`..`_$E12`);
  - INIObject: Object, ObjectReskin, ChildObject (`_$E10`..`_$E14`);
  - Eva: PredefinedEvaEvent, NewEvaEvent, EvaEventForwardReference;
  - INIWater, INIMultiplayer and MetaEvent: two each;
  - INIAiData, INICommandButton, INIDrawGroupInfo, INIMappedImage, INIMiscAudio and INITerrainRoad:
    one each;
  - Mouse (MouseCursor, Mouse `_$E34`/`_$E36`), LargeGroupAudio and INITerrain (Terrain,
    WaterTextureList): two each;
  - GlobalLanguage, AnimationSoundModuleManager and LivingWorldCampaign: one each.
- *Waiting.* MiscEvaData needs `INI::parseMiscEvaData` in Eva.cpp's INI view. FXList (0x007AD241)
  compiles in FXList.cpp as `_$E48`. It stays in the grab-bag because FXList.cpp does not link yet
  (census: COMDAT losers), and moving the entry there would cost 21 linked bytes. These need their
  wrapper unit or a claimable owner: AudioSettings, ShadowMap, LoadSubsystem, Armor (Armor.cpp),
  Bridge (INITerrainBridge.cpp is approved but missing), CommandSet, ControlBarScheme,
  ControlBarResizer, CrateData, WindowTransition and DamageFX. ScriptEngine.cpp is held by another
  seat. The rest (about 85) follow the same steps once a node's unit is clear.
- *Rowed by in-o4 (2).* ExperienceLevelSystem.cpp now defines ExperienceLevel and
  ExperienceScalarTable as `_$E1` and `_$E3`. Both callbacks are approved to that TU in tu_map.
  Retail's table runs 0x007ADFDF (a Drawable.h copy whose static 0x00DFECCC follows the unit's own
  0x00DFECC8/0x00DFECC9), then 0x007ADFEF and 0x007AE004, then the unit's pool-init marker. The
  Drawable.h copy is held by in-o2's lane. Once the unit includes Drawable.h, these two become
  `_$E3` and `_$E5`. link_check must take the unit together with the grab-bag. Taken alone, it sees
  the census grab-bag's copies of the nodes as duplicates.
- *Next leads.* Use a unit's own Drawable.h copy as the anchor. Each copy is followed in `.text$yc`
  by that unit's other initializers and then its pool-init marker. The handoff TSV names each
  copy's unit, so any grab-bag entry between a copy and the next marker belongs to that unit.
- *Runs end at the marker (halilkkaya-in-o6, target facts).* The 26-byte pool-init marker closes
  each unit's `.text$yc` run. GameLOD shows it: its Drawable.h copy 0x007AD6F3, then its rowed nodes
  `_$E27`..`_$E39`, then the marker 0x007AD796. The `INI*.cpp` wrappers emit no marker. INIAiData's
  `_$E1` (0x007ACFD0) sits directly before Armor's copy, and INITerrainRoad's `_$E1` directly before
  the Science node. So a run between two markers can hold one wrapper's nodes, then one unit.
- *Rowed by in-o6 (7).* Each node's run, read between markers, holds only that node's unit:
  - Armor (`Armor.cpp` `_$E16`), ModifierList (`AttributeModifierStore.cpp` `_$E1`) and BannerType
    (`BannerUI.cpp` `_$E1`) follow their unit's own Drawable.h copy. Each copy's `.bss` static
    follows TheArmorStore (0x00DFDBCC), TheAttributeModifierStore (0x00DFE1DC) or TheBannerUI
    (0x00DFE330).
  - PlayerTemplate (`PlayerTemplate.cpp`), Rank (`RankInfo.cpp`) and LivingWorldRegionCampaign
    (`LivingWorldRegionManager.cpp`) are the only entry of their run. Science (`Science.cpp`)
    comes before 0x007AD5A9 in its run. Each callback's approved TU in tu_map is that unit.
  - Each owner defines the node at the end of the file, as in-o3 did. RankInfo.cpp's
    RankInfoStore view gains only the static `friend_parseRankDefinition` declaration. Every
    `??_7` the 7 objects emit keeps its pre-edit digest.
  - Verified: link_check passes for all 7 owners and the grab-bag. They gain 7 x 21 bytes, and
    the grab-bag loses the same. image_report: bridged 692 -> 685, and exactly these 7 RVAs leave
    `not_registered_rvas`. No touched object registers anything twice or unidentified.
- *Attributed but held (in-o6).* These follow the same rule. They wait only for the owner's
  claim:
  - Locomotor 0x007AD2EF: `Locomotor.cpp`'s run is its copy 0x007AD285, five ZeroInits and the
    node. Held by Burachi-3D.
  - ObjectCreationList 0x007AD4CC: `ObjectCreationList.cpp`, run [copy 0x007AD4BC, node]. Held
    by yasinschroeder-claude.
  - AwardSystem 0x007AFE2E: `AwardSystemManager.cpp`, run [copy 0x007AFE1E, node]. Held by
    yasinschroeder-claudeb.
  - ArmySummaryDescription 0x007ADB1D: `CreateAHeroManager.cpp`. The run is its rowed `_$E1`
    copy 0x007ADB01, then 0x007ADB11, then the node. The node's .data follows
    `_CreateAHeroSubClassFieldParse`. Held by halilkkaya-nw-o2.

  FXList stays in the grab-bag (above). The other runs hold several callbacks' nodes, or a copy
  whose unit tu_map does not settle, for example AptButtonTooltipMap's run.
- *Hazard.* A unit that later takes Drawable.h, or adds a dynamic initializer before these nodes,
  moves their ordinals. Read each `_$E<n>`'s relocation target (its node) again.

**StaticTagInitializers (63 + 1 rows): online-service records (halilkkaya-in-o4, 2026-11-04).**
- *Target facts.* 64 table entries (0x007B5DF0..0x007B6170 and 0x007B61A0..0x007B65E0) share one
  22-byte body: `mov eax, [type]; push code; push eax; mov ecx, &record; call 0x0065D090; ret`. The
  type global is `[0x00DD8290]` (VA 0x00CE34C8, "msgr") for AUTH..PING and `[0x00DD8318]` ("thtr")
  for CONN..HGAM. The codes are four-character constants. 0x0065D090 stores {type, "", code} and
  returns this. A raw E8 scan finds it called from these 64 initializers only. Its neighbour
  0x0065D070 stores {type, name, 0} and is called only from the 62 TxnNameInits initializers, so
  both families are one three-word record with two constructors.
- *What it is.* Each entry is the `.text$yc` dynamic initializer of a file-scope
  `Rva007F0210 record(type, 'CODE');`. MSVC 7.1 compiles the out-of-line constructor call to exactly
  this body, and the ordinals step by two. The row at 0x0065D090 was a placeholder `set` and is now
  `??0Rva007F0210@@QAE@HH@Z` (hand rename, tombstoned, body unchanged).
- *Layout (target facts).* Each service run in .data is [codec object][service type][record
  table]: 0x00DD828C/0x00DD8290/0x00DD8298 for msgr and 0x00DD8314/0x00DD8318/0x00DD8320 for thtr.
  The record table lists the records in .CRT$XCU order. Each run's table entries start with the
  codec object's atexit-only initializer: 0x007B5DE0 for msgr and 0x007B6190 for thtr.
- *Folding hazard.* If an object defines the type value, MSVC 7.1 folds it into the first dynamic
  initializer that reads it (`push 0x00CE34C8`, no load). The value is reloaded only after an earlier
  initializer in that object has made a call. Retail reloads it in AUTH. So the msgr type
  `bfmeRva012C3B38TagValue` moved beside the msgr codec object in
  `Rva007B5DE0StaticInstance.cpp`, its .data neighbour, and AUTH reads it as an extern.
- *Rowed (64).* `StaticTagInitializers.cpp` defines the 63 records in retail order: msgr DISC..PING
  `_$E1`..`_$E55` and thtr CONN..HGAM `_$E57`..`_$E125`. `StaticTagInitializerC6D010.cpp` defines
  AUTH as `_$E1`. tu_map gives these records no TU, so they stay in their files.
- *Next.* The records, codec objects and type values belong in one TU per service, together with
  the record tables and the codec code (for example `findEntry` 0x00667FC0 reads 0x00DD8298, and
  0x00669410 reads 0x00DD8320). Merge them when tu_map approves those TUs. The 0x007B6190 thtr codec
  initializer sits in `Rva007AC6DDGlobalInits.cpp`.

**TxnNameInits (62 rows): transaction records (halilkkaya-in-o4, 2026-11-04).**
- *Target facts.* Entries 0x007B55E0..0x007B5DC0 are one 22-byte body, `mov eax, [type]; push
  "Name"; push eax; mov ecx, &record; call 0x0065D070; ret`. The services run in table order acct
  (20), blob (10), fdbk (2), rank (11), recp (4), club (11) and fsys (4). Retail's table has only two
  other entries in that run: the acct codec object's atexit-only initializer 0x007B55D0 just before
  Login, and a mutex object's initializer 0x007B5860 just before blob.
- *Rowed (62).* `Rva007B55E0TxnNameInits.cpp` defines the records as
  `Rva007B55E0TxnName g(type, "Name");` in retail's table order, `_$E1`..`_$E123`. The explicit
  constructor-call functions, the `#pragma code_seg(".text$yc")` and the default constructor with
  its `present-unmatched` marker are gone. The type values are `const char *` globals initialized to
  a literal, so they are address constants and nothing folds. The file's hatch lines shrink by 62.

**ZeroInits (56 rows): per-unit header objects (halilkkaya-in-o4, 2026-11-04, not rowed).**
- *Target facts.* The body is `push 4; push 0; push &s; call memset; add esp, 0xC; ret`. The copies
  come in runs of five, with consecutive statics, plus one single copy (0x007B3162). Each run of five
  directly follows a unit's Drawable.h copy in `.text$yc`, and its statics directly follow that
  copy's static in `.bss`. For example, 0x007B0CA7 (static 0x00E03604) is followed by 0x007B0CB7..
  0x007B0CFF (0x00E03608..0x00E03618) and then the pool-init marker 0x007B0D11.
- *Units.* The handoff TSV attributes the copies before the runs to these units: Locomotor,
  StealthUpdate, UnitRevivalTracker, FadeAndDieOrnamentUpdate, AptMpGameSetup,
  SiegeDockingBehavior, GiantBirdSlowDeathBehavior and SquishCollide, plus the FrameRate copies
  0x007ADD08 and 0x007ADEF6. Most of these units do not compile with the canonical Drawable.h yet,
  or they are claimed. GiantBirdSlowDeathBehavior compiles it since in-o5, and its copy is rowed.
- *What it is (inference).* There are five 4-byte objects per includer, each with a memset default
  constructor. That suggests five internal-linkage `BitFlags<n <= 32>`-style objects from one header.
  One more run, 0x007AEDE7..0x007AEE2F in `Rva007ADC9CMaskInits.cpp` (statics 0x00E01EC0..0x00E01ED0),
  is read and written: the GiantBirdAIUpdate constructor 0x0036B717 ORs flag bits into all five, and
  the giant-bird states read them. The header is not identified yet.
- *Runs by marker (halilkkaya-in-o6, target facts).* Twelve runs of five, each read between
  pool-init markers, with each unit taken from the `.bss` data just before the statics:
  - Locomotor (0x007AD295, after TheLocomotorStore's unit data);
  - ModuleFactory (0x007ADD18, after TheModuleFactory and two half-rate copies);
  - Drawable.cpp (0x007ADF06, after 0x00DFEB98, the constant `Drawable::updateDrawable` reads);
  - GiantBirdAIUpdate (0x007AEDE7);
  - AerialPathfinder (0x007AEF03; statics 0x00E01F14.. right after TheAerialPathfinder 0x00E01F10;
    no Drawable.h copy in its run);
  - the unit after Rva0037FE3D's statics, ArmyPlacerPlaceObjects.cpp (0x007AF063, no copy);
  - StrafeAreaUpdate (0x007AF3D7, after its pool key; no copy);
  - ActionManager (0x007B015F, after TheActionManager and two copies);
  - SpecialAbilityUpdate (0x007B079B, after its statics and its copy);
  - AutoAbilityBehavior (0x007B0A6A, after its statics; no copy);
  - GiantBirdSlowDeathBehavior (0x007B0CB7);
  - SquishCollide (0x007B25BC).

  Four runs have no Drawable.h copy, so the masks come from their own header, not one tied to
  Drawable.h. 0x007B3162 is a lone copy in a run of its own. 0x007AF7ED (17 bytes, ArgCtorInits) only
  starts with the same `push 4; push 0` bytes and is not one of these.
- *What the masks are (target facts).* Only giant-bird code reads them. They are the `mask` argument
  `Rva00368C7A::rva003681F2` (0x003681F2) passes to `AerialPathfinder::computeAerialPath`
  (0x0037609C). AerialPathfinder's constructor 0x0022C987 builds a 4-byte BitFlags member at +0x0C
  through 0x003B31AD (the ICF-folded `BitFlags<N <= 32>` constructor) and ORs in 0x28. The giant-bird
  constructor ORs the same 0x28 into mask 0 before it propagates it to masks 1 to 3.
- *Not AerialPathfinder.h (target facts).* `GameEngine::init` allocates the pathfinder inline
  (`push 0x14`, `new` at 0x0022F3F2, ctor call 0x0022F405) and stores TheAerialPathfinder at
  0x0022F42B, so GameEngine.cpp includes the class. GameEngine.cpp's run (copy 0x007ADBC1 with
  static 0x00DFE714 after TheGameEngine, then 0x007ADBD1, then the marker 0x007ADBE5) has no masks.
- *Donor facts.* A search of Zero Hour's `GameEngine/Include` for `static` object definitions
  finds only static class members. A search of the BFME 1 reference for a memset zero-init family
  finds none.
- *Inference.* The header is a giant-bird module header, most likely GiantBirdAIUpdate.h, with five
  internal-linkage flag sets that the GiantBirdAIUpdate constructor fills. The string
  "GiantBirdAIUpdate" is read only by `ModuleFactory::init` and GiantBirdAIUpdate's own code, and
  both units have a run. Nothing names the header or the five objects, so the rows stay.
- *Next.* Recover GiantBirdAIUpdate.h (class plus the five sets) once a name source exists. Each
  run's unit then includes it. GiantBirdAIUpdate's own five are `g_00E01EC0`..`g_00E01ED0`, shared
  today by its split fragments, and they need its TU merged first: per-fragment copies would split
  the constructor's writes from the states' reads.

**The small grab-bags: what each family is (halilkkaya-in-o7, 2026-11-04).** Each form below is
read from retail bytes and compiled in scratch (`cl` through `build.compiler_command` into
`build/`, never `build/match`). Counts are bridged entries on `ffd59e2e74`.
- *FrameRateInits (31): unit constants derived from the frame rates.* `int X =
  BfmeLogicFramesPerSecond * k` (k = 1, 2, 3, 4, 5, 10, 60, 120), `/ 2`, `/ 4`, and `1000 /
  BfmeClientFramesPerSecond`. `/ 2`, `* 1`, `* 60` and `1000 /` compile to retail's bytes with any
  flags. `* 2` (`add`), `* 3`/`* 5`/`* 10` (`imul`), `* 4` (`shl`) and `/ 4` (`push 4; pop ecx;
  idiv`) need the owner's own flags; blended `/O1` emits `lea`. Sixteen are the `/ 2` shape. Twelve
  of those divide `BfmeLogicFramesPerSecond`, and each directly follows a unit's Drawable.h copy in
  its run. Nothing in .text reads ten of them (0x007ADD08, 0x007ADE88, 0x007AE043, 0x007AE2CE,
  0x007AEE6B, 0x007B014F, 0x007B042B, 0x007B08B2, 0x007B1122, 0x007B1328). That suggests a second
  header constant (inference). By the attribution TSV its includers would be ModuleFactory,
  AIUpdate, TacticalAI, GettingBuiltBehavior, RebuildHoleBehavior and RebuildHoleExposeDie, among
  others. W3DDisplay's updateAverageFPS reads its copy (0x00DE1B50) and SpawnBehavior::update reads
  its own (0x00E035C8). The header is not identified, so the ten wait.
- *GlobalInits (17): mixed.* Most are `T g;` objects (`mov ecx, g; call ctor; push cleanup; call
  atexit`). 0x007B6670/0x007B6680 register only an atexit cleanup (a trivial ctor and a real
  dtor). 0x007AE7FB stores an address constant (`g = &x`). 0x007B6800 is `Random3Class(0, 0)`.
- *CtorInits (25) and AtexitInits (12): `T g;` and `T g("literal");` with a destructor.* 22
  bytes: `mov ecx, &g; call T::T(); push _$E<n+1>; call atexit; pop ecx; ret`. AtexitInits is
  the 27-byte `push "lit"` form, all through `AsciiString::AsciiString(const char *)`
  (0x0000654A). CtorInits' ctors are AsciiString/UnicodeString defaults (0x00326BE6), STLport
  map/set defaults (0x0033C432, 0x0024613C) and unit classes (0x003818F4...). Two pairs are
  STLport's per-includer `ios_base::_Loc_init` (0x0000F740) and `ios_base::Init` (0x00016AA0)
  objects: 0x007ABCAF/0x007ABCC5 and 0x007AEC8E/0x007AECA4, so each comes from a unit that
  includes `<iostream>`. Rowing one also moves its `.text$yd` cleanup row (`_$E<n+1>`, today in
  `Rva007B6880Thunks.cpp`) into the owner.
- *AllocCtorInits (17): STLport containers with the defaulted allocator argument.* 29 bytes:
  `push ecx; lea eax, [esp+3]; push eax; mov ecx, &g; call ctor(const allocator &); push cleanup;
  call atexit`. The ctors are out-of-line `vector`/`list` (allocator) ctors (0x004F710A,
  0x002C5309, 0x004226CE, 0x002F0BE0). A scratch empty `Alloc()` adds a `mov byte [esp+7], 0`
  that STLport's allocator, with its user-declared ctor, does not.
- *StringInits (9): STLport `string`/`wstring` objects from literals* (`basic_string(const char *,
  const allocator &)`, 0x00009100 and 0x0000BF20). Their globals sit at 0x009DEB2C..0x009DEF38
  among STLport's library data (`_Nameless`), so they belong to STLport 4.6 sources, not game
  units.
- *ArgCtorInits (16): constructors with constant arguments.* Pools built as `(0, -1)` with an
  atexit dtor, like the pool-init marker (0x0006EFC8, 0x002E8548); DisabledMask constants through
  the one-, two- and four-bit `BitFlags<11>(BogusInitType, ...)` ctors (0x00481B7F, 0x005E5963,
  0x005CBA5F); table objects through 0x00559A11/0x00559A76 with 0 or 1; and 0x000411C1(1).
- *MaskInits (14): `BitFlags<N>` default ctors that call `memset`.* `push size; push 0; push &g;
  call memset; add esp, 0xC`. They include KINDOFMASK_NONE (0x1C), DISABLEDMASK_NONE/ALL (4) and
  in-o4's giant-bird masks. A scratch inline `memset` ctor folds to static zero, so the real
  `BitFlags`/bitset header is needed to compile them.
- *Rowed (4, this series).* Each owner already defined or owned the global; its initializer now
  comes from the owner's definition, and the grab-bag body was retracted:
  - W3DView.cpp `_$E6` 0x007AC08C: `Int TheW3DFrameLengthInMsec = 1000 /
    BfmeClientFramesPerSecond;`. Its run is W3DView's copy 0x007AC07C, then this entry; its
    `.bss` slot follows that copy's static 0x00DE2048 among W3DView's file statics.
  - LargeGroupBonusUpdate.cpp `_$E3` 0x007B15B2: `g_00E03994 = BfmeLogicFramesPerSecond`, the
    ModuleData ctor's default update rate. It follows the unit's rowed copy `_$E1`.
  - SpawnBehavior.cpp `_$E86` 0x007B0C0F: `g_00E035C8 = BfmeLogicFramesPerSecond / 2`. Its run
    is SpawnBehavior's copy 0x007B0BFF, then this entry; the static follows the unit's pool key.
  - v3_rnd.cpp `_$E2` 0x007B6800: the unit defines `BFME_RANDOM3CLASS_CTOR_NOINLINE`, as BFME 1's
    v3_rnd.cpp does, so `Vector3Randomizer::Randomizer` calls the pinned out-of-line ctor.
  - AISpellBookShroudReveal.cpp `_$E1` 0x007B4BC6 (next round): `g_00E06648 =
    BfmeLogicFramesPerSecond * 10`, the frame its picker 0x005D7FA6 waits for. The entry is the
    only one of its run; the unit's own flags give retail's `imul`. Bridged 677 -> 676.
  - Drawable_rva00275598.cpp (Drawable.cpp TU) `_$E1` 0x007ADEF6 and `_$E3` 0x007ADF60: Drawable.cpp's
    own flash interval `g_00DFEB98 = BfmeClientFramesPerSecond / 2`, which updateDrawable in that
    fragment reads, and `BfmeHealingIconDisplayFrames = BfmeLogicFramesPerSecond * 3`, which
    drawHealing 0x00273DCF reads. They open and close Drawable.cpp's run around five ZeroInits
    masks. The second definition moved from the grab-bag with its data row. Recovering the masks
    will move the second ordinal. Bridged 676 -> 674.

  Verified: every owner exact; each `??_7` keeps its pre-edit digest; link_check over the owners,
  their reader files and both grab-bags: 11/11 link (owners +76 bytes, grab-bags -60, plus the
  copy the census index predates); scoped DIR32 OK; image_report bridged 683 -> 679 (exactly
  these 4 RVAs), twice 6 -> 6, unidentified 519 -> 519.
- *Copies rowed with in-o6's run attribution (in-o7).* AttributeModifierStore.cpp and BannerUI.cpp
  now include the canonical Drawable.h and row their copies 0x007AD97D and 0x007ADA3C as `_$E1`.
  Their ModifierList and BannerType nodes move to `_$E3`. BannerUI's include must follow
  `LivingWorldBattle.h`: before it, Drawable.h defines the Snapshot slot macros first and that
  header refuses to compile. Armor (0x007ACFE5) was reverted: Armor.cpp is Zero Hour-shaped
  (`PreRTS.h`), and the canonical header collides with Zero Hour's `Thing`. link_check must take
  the BlockParse grab-bag with these units, because the census index (17:56) predates in-o6's node
  moves. Taken alone, AttributeModifierStore, BannerUI and the untouched Armor all report the
  grab-bag's stale copy of their node as a duplicate. With it, 7/7 link. image_report: bridged
  679 -> 677, twice and unidentified unchanged; both units' `??_7` digests are unchanged.
- *Next.* Units whose global is already ledger-owned are the cheap ones: 0x007AEBAA (`g_00E01E04`, AIStates'
  run, defined in the fragment Rva0033FE65OnEnter.cpp), 0x007B1A27 (SlavedUpdate's
  `BfmeSlavedUpdateIntervalFrames` in SlavedUpdateRepair.cpp, held by another seat), 0x007B51EB
  (Rva005F0152ImageGet) and 0x007B67A0 (`g_aptDateInterpreter`, AptDate.cpp's POD view). The
  ctor/dtor families need the owner to declare the real class and take the cleanup row too.

**How to attribute a TU.**
- Neighbouring entries in retail's table that are already registered by a known object bound the run.
- The static's `.bss` address falls inside its TU's data contribution next to ledgered globals.

**Runtime hazards found (not counted in `initializers_bridged`).**
- **Registered twice (116; 6 since `b4d81c1215`).** Objects register an initializer whose retail
  entry another object already registers. The FXParticleSystem part was a counting error, not a
  runtime hazard (halilkkaya-fx-o1, 2026-11-04). *Object facts:* MSVC 7.1 emits a template static
  data member's dynamic initializer in every object that instantiates it, and puts its `.CRT$XCU`
  slot in a COMDAT section of selection 5 (associative) tied to the pick-any COMDAT of the data. In
  `FXParticleSystemFactories.obj`, `_$E94`'s slot (section 1098, `0xC0301040`) is associative with
  section 1097, `?s_key@?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@...`, and
  `FXParticleSystemModules.obj` carries the same pair. The linker keeps one copy of the data and drops
  the other object's associated slot, so the slot runs once. `image_report` now counts one
  registration per owning COMDAT (`registered_comdat_copies_discarded`). On `4be378257d`'s objects:
  81 copies discarded (80 Factories/Modules pairs and one `AutoPoolClass<HAnimComboDataClass>::
  Allocator` pair in `hanim.obj`/`HAnimComboBFME1.obj`), twice 58 -> 6, unidentified 599 -> 520,
  not registered 781 -> 783 (two weak shape credits moved).
- **Unidentified (342; 520 by the corrected report, 146 of them FXParticleSystem).** Registrations
  whose shape and relocations match no retail entry. They run in our image and never in retail.
  The FXParticleSystem ones are emission scaffolding, not retail globals: none is in
  `reverse/data_ledger.csv`.
  - 77 in `FXParticleSystem.obj`: file-scope `CategoryModuleTemplate<N> g_categoryModuleTemplateN`
    objects and `g_*Assign*` pointers to members (`FX_FORCE_CATEGORY_ASSIGN`). The comments say
    they exist to force out template constructors and assignments nothing in the split file calls.
  - 39 plain in `FXParticleSystemModules.obj`/`FXParticleSystemFactories.obj`: the same pattern,
    `g_*ModuleConcrete` and `g_defaultConcreteN` objects and `g_*ConcreteAssign` pointers.
  - 29 associative `ConcreteModuleClass<...>::s_instance` slots that match no retail entry, and
    one in `Rva003A5A58WindUpdate.obj`.
  Retail emitted those COMDATs from the module code of its own `fxps*.cpp` units. The scaffolding
  can go only when the bodies that need the COMDATs share a unit with them, which needs TU approval
  for the `fxps*` units first. The evidence package is in `docs/consolidation.md` ("FXParticleSystem:
  approved units are single files, approval is the wall").
- **Shape-only credits (3).** These are listed in `by_shape_only` and are weak.

**Next useful checks.**
- Pick a family whose global already has a data-ledger owner and apply the method there.
  - *Network.cpp (halilkkaya-in-o6, rowed).* 0x007ADDC7 and 0x007ADDD3 are the only entries of
    their `.text$yc` run, between Display.cpp's copy 0x007ADD9D and View.cpp's copy 0x007ADDF9.
    Their globals 0x00DFEA2C and 0x00DFEA30 lie in Network.cpp's `.bss` run, before
    NetworkTimingOverruns. Network.cpp now defines them as `= timeGetTime()`. MSVC numbers
    them `_$E1` and `_$E3`. Both files link (+24 / -24 bytes), and bridged went 685 -> 683.
  - *Still open.* 0x007B4439's global 0x00E063FC is read by `Rva005A6709Predicate.cpp`.
    0x007ADBD1 (`g_00DFE718 = MessageBoxA == MessageBoxW`) is the second entry of GameEngine.cpp's
    run, after its copy 0x007ADBC1, whose static 0x00DFE714 follows TheGameEngine. Its bool
    0x00DFE718 is defined in the grab-bag today.
- Separately, decide the HalfRate header constant.
