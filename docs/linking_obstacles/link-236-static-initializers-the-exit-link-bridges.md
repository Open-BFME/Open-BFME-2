### LINK-236: static initializers the exit link bridges

Status: open (lane started 2026-11-04 by halilkkaya-in-o1 at `993e6014c8`; halilkkaya-in-o2 at
`f2cec2a7f8`: report tie fix, Drawable.h constant and 84 rowed copies, bridged 969 -> 885 on the
fixed report; halilkkaya-in-o3: BlockParse registrations are per-unit file-scope nodes, 40 rowed in
their units, bridged 885 -> 845; halilkkaya-in-o4: the msgr/thtr service records are file-scope
objects of the 0x0065D090 constructor, 64 registered, and the 62 transaction records of its
0x0065D070 sibling, plus 2 BlockParse nodes, bridged 845 -> 717; halilkkaya-in-o5: 17 private-view
units adopt the canonical Drawable.h and row their copies, bridged 717 -> 700, then 3 more, bridged
702 -> 699 on the report with `registered_comdat_copies_discarded`; halilkkaya-fix-o1: 7 round-2
includes moved below their units' Snapshot includes, restoring the vtables they had shifted, bridged
699 unchanged; halilkkaya-in-o5 then 7 units free since round 2, bridged 699 -> 692;
halilkkaya-in-o6: 7 BlockParse nodes rowed in the units whose `.text$yc` run holds them, bridged 692
-> 685, then Network.cpp's two timeGetTime initializers, bridged 685 -> 683, and the ZeroInits masks
traced to a giant-bird header, not AerialPathfinder.h; halilkkaya-in-o7: the small grab-bags' forms
recorded, 4 FrameRate/GlobalInits entries rowed in their owners, bridged 683 -> 679, then the
AttributeModifierStore and BannerUI copies, bridged 679 -> 677, and AISpellBookShroudReveal's
`g_00E06648`, bridged 677 -> 676, Drawable.cpp's two, bridged 676 -> 674, and AIStates'
IDLE_COUNTDOWN_DELAY, bridged 674 -> 673; halilkkaya-lk39: GameEngine.cpp's copy and MessageBox
initializer and `g_00E063FC`, bridged 673 -> 670; the four held BlockParse nodes and two of their
units' copies, 670 -> 664; 19 guard-anchored units freed since round 2, 664 -> 645; three copies
their units already compiled, 645 -> 642; two private Drawable views replaced, 642 -> 640; 8 units
by their guard's approved function, 640 -> 632; MetaEvent's copy, 632 -> 631; two private Thing
views replaced, 631 -> 629; AIStates' copy, 629 -> 628; RayEffect's, 628 -> 627 (bridge_entries on
`24abddc449`'s objects); halilkkaya-lk44: the LinearCampaign node and SlavedUpdate's interval,
627 -> 625; five copies their TU's only compiling fragment registers, 625 -> 620; FXList's node
and copy and ObjectCreationList's copy, 620 -> 617; eleven BlockParse nodes in Chat,
FireLogicSystem, GlobalWeatherSystem, ScriptEngine, GameFont, INIVictorySystem, INIEnvironment and
Eva, 617 -> 606; five copies their own TU files already compile, 606 -> 601 (bridge_entries on
`006ca45a16`'s objects plus its readmission); halilkkaya-lk46: the AsciiString atexit family's twelve
strings, the copies that open their runs, the CreateAHeroSystem node and three FX binder objects, 605
-> 583, then AptDate's interpreter, the INI macro table and file name, ScriptEngine's and Eva's copies
and seven run-closing BlockParse nodes, 583 -> 572 (bridge_entries on `2335dd1fbb`'s objects plus the
round; see "Round lk46"); halilkkaya-lk51: INIObject.cpp moved off Zero Hour's PreRTS.h and 23 copies
placed by the function-local statics just before them, 572 -> 548 (see "Round lk51"); halilkkaya-lk54:
MSVC 7.1's .bss layout read from scratch objects and a scratch link (function-local statics follow a
unit's main .bss whenever the unit has a plain zero-initialized global), and with it the MapObject,
AptMainMenu, AptOptions, AptCreateAHero and AptLanLobby copies, 548 -> 543, then 14 copies that sit
inside or close their own unit's statics, 543 -> 529 (see "Round lk54"); halilkkaya-lk58: lk54's
four settled leads (the LuaScriptEngine copy, the LivingWorldSound zoom region, the ScriptActions flash
divisor, SidesList), then GameClient/DrawableFramesPerFlash.h, with which 31 copies of units that refuse the
canonical Drawable.h registered, 529 -> 494 (see "Round lk58"); next seat continues).

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
- *Units free since round 2, second pass (halilkkaya-lk39, 2026-11-07).* 24 guard-anchored units
  that rounds 2 and 4 found held were claimable (CrushDie was left alone: another contributor is
  working on DieModule). A trial script built each with the include after its last include, then
  after its first, and kept a position only if the unit stayed exact, emitted exactly one new
  `_$E1` with the copy's 16 bytes, and kept every `??_7` digest. 19 took it after their last
  include and are rowed as `_$E1`: AttributeModifierPoolUpdate, BloodthirstyUpdate,
  FakePathfindPortalBehaviour, CivilianSpawnUpdate, PropagandaTowerBehavior,
  FireWeaponWhenDeadBehavior, ReplenishUnitsBehavior, ArrowStormUpdate, CommandButtonHuntUpdate,
  OneRingPenaltyUpdate, AttributeModifierAuraUpdate, RadiateFearUpdate, BroadcastStealthUpdate,
  DestroyEnvironmentUpdate, RousingSpeechUpdate, GloriousChargeUpdate, EmotionTrackerUpdate,
  WoundArrowUpdate and ManTheWallsSpecialPower. link_check: 20/20 with the grab-bag.
  image_report: bridged 664 -> 645, twice 6 -> 6, unidentified 524 -> 524.
  - Reverted (private views): HitReactionBehavior (private `Drawable` with an inline
    `testModelCondition` over +0x258), GiveUpgradeUpdate (private `Drawable` with one field at
    +0xB0), FloodUpdate (private `Matrix3D` and `Thing`), DemoTrapUpdate and ReplaceObjectUpdate
    (private `Thing`; ReplaceObjectUpdate reads `m_id` through it). The two `Drawable` views need
    only a cast view over the canonical class; the `Thing` views follow SquishCollide's recipe
    (round 5).
  - *The two `Drawable` views, fixed.* HitReactionBehavior now includes the canonical header after
    its last include and tests the condition words through a file-local view
    (`HitReactionDrawableConditionView`; the canonical class keeps +0x258 opaque and already
    declares `rva00274176`). GiveUpgradeUpdate's word at +0xB0 is the canonical `field_0b0`; the
    unit still copies its bits with an int store. Both copies are rowed as `_$E1`, every `??_7`
    keeps its digest, 3/3 link with the grab-bag, bridged 642 -> 640.
  - *Two `Thing` views, fixed.* `DemoTrapObjectView.h` (one includer) now includes the canonical
    thing.h; its Object pads from +0x60 to its byte at +0x438 and the unit reads the position as
    `m_cachedPos`. ReplaceObjectUpdate's private Thing served one read of the owner's id at +0x74;
    the read now goes through its Object view. Both copies are rowed as `_$E1`; bridged
    631 -> 629.
  - *Still refused.* FloodUpdate's private `Matrix3D` declares `buildTransformMatrix`, which the
    canonical Matrix3D storage header does not carry (a shared-header change).
    AnimationSoundClientBehavior's private `Drawable` (`enabled` at +0x44A, `parent` at +0xFC)
    needs the same cast-view treatment as HitReactionBehavior.
- *Guard's function approved to the file (halilkkaya-lk39).* For each bridged copy, read the
  data-ledger entry just before its static; when it is a function-local guard, look up the guarded
  function's row and its approved TU. Where that TU file exists, includes no Drawable.h and holds
  only this copy's guard, the trial took the header in 8 more units: W3DSailModelDraw,
  FadeAndDieOrnamentUpdate, GettingBuiltBehavior, RampageBehavior, ProductionUpdate,
  HijackerUpdate, UnleashSpecialPower and Made002CCAA1 (after its first include; after its last,
  an earlier ordinal made the copy `_$E2`). Four of them had only a fragment including the header;
  those fragments' copies stay unidentified until their merges. AnimationSoundClientBehavior was
  reverted (private views; C2227 at `->position`). link_check 9/9; bridged 640 -> 632.
  - Not taken: tu_map approves five special powers' guards (ElvenWood, CloudBreak, Taint,
    FreezingRain, Darkness) to `ElvenWoodSpecialPower.cpp` and both siege containers' guards to
    `HordeSiegeEngineContain.cpp`, while retail gives each copy its own run, so those approvals do
    not settle the unit. InstantDeathBehavior, SlowDeathBehavior, CreateObjectDie and CrushDie were
    left for the contributor working on DieModule. ControlBar's guard
    (`updateConstructionTextDisplay`) is approved to `ControlBarUnderConstruction.cpp`, which does
    not exist yet.
- *Copies that open a rowed unit's run (halilkkaya-lk39).* A copy followed in its run by `_$E<n>`
  rows of one unit, before that run's marker, is that unit's (wrappers come before units in a run,
  never inside one). MetaEvent.cpp: copy 0x007AD0CC, static right after TheMetaMap, then its two
  nodes. It now includes the header after FieldParse.h; the nodes move from `_$E1`/`_$E3` to
  `_$E3`/`_$E5` and were retracted and readmitted by relocation target. Bridged 632 -> 631. The same
  shape, reverted or not tried: Mouse.cpp (0x007AD3A6, Zero Hour `Thing.h` collides), INIObject.cpp
  (0x007AD453, `PreRTS.h`), W3DView.cpp (0x007AC07C before `_$E6`, Coord3D collides; LINK-018 is
  out of scope), GameLOD.cpp (0x007AD6F3, `PreRTS.h`), SpawnBehavior.cpp (0x007B0BFF before
  `_$E86`, Zero Hour `Drawable.h`) and Eva (0x007AD1B3 before Eva.cpp's nodes; TheEva's definer is
  not settled).
  AIStates (0x007AEB9A before IDLE_COUNTDOWN_DELAY) is rowed the same way in the fragment that
  in-o7 gave the global, `Rva0033FE65OnEnter.cpp`: it includes the header before the definition,
  the copy is `_$E1` and IDLE_COUNTDOWN_DELAY moves to `_$E3`. Bridged 629 -> 628.
- *Singleton anchors (halilkkaya-lk39, weaker than the guard rule).* About 45 bridged copies sit
  right after a unit's singleton (`TheX`) in `.bss` with no guard between. The singleton's unit
  owns the copy unless a unit with no other `.bss` sits between, so these need a second fact.
  RayEffect.cpp is rowed (0x007AE33C): the copy is alone in its run, its static follows
  TheRayEffects, the file's only global, and Zero Hour's RayEffect.cpp includes Drawable.h (donor
  fact). Bridged 628 -> 627. Display.cpp (0x007ADD9D after `g_bfmeVM0Scale`) lacks the donor
  fact, and View.cpp, W3DTerrainTracks.cpp, GameClient.cpp and the other Zero Hour-shaped
  singleton units build against Zero Hour's Drawable.h, whose constant is not dynamic.
- *Copies a unit already compiles (halilkkaya-lk39).* A TU file that includes the canonical header
  compiles its copy, but with no row image_report counts it as unidentified (an unplaced static
  breaks no tie). Cross the unidentified list with the bridged copies' guard units: W3DStreakDraw
  (0x007AC563, since its 11-05 merge), BuildingBehavior (0x007B0920) and BannerCarrierUpdate
  (0x007B17BD, guard of 0x00496B48, approved to the unit) each sit alone in their run with the
  static right after the unit's own guard. Rowing them needs no source change: bridged 645 -> 642,
  unidentified 524 -> 521. ControlBar.cpp also compiles a copy, but the copy that follows a
  ControlBar guard (0x007B3BCE, `updateConstructionTextDisplay`) has its guard's function approved
  to `ControlBarUnderConstruction.cpp`, which does not exist yet, and ControlBar.cpp is held by
  Burachi-3D. AssistedTargetingUpdate (0x007B13C0) waits for a codex seat's merge into that file. 227
  other files still compile an unidentified copy (image_report at `318099a57f`); most are
  fragments whose TU file is not merged yet.

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
- *The four held nodes, rowed (halilkkaya-lk39).* All four owners were free on 2026-11-07. Each
  defines its node at the end of the file, and the two that compile the canonical header also
  take their copy:
  - `Locomotor.cpp`: Drawable.h after its `GameLogicObjectLookupView.h` include; copy `_$E1`
    0x007AD285, node `_$E3` 0x007AD2EF. Retail puts the five flag sets between them, so the node's
    ordinal moves when those are recovered. LocomotorStore's view gains only the static callback.
  - `AwardSystemManager.cpp`: Drawable.h after its first include block; copy `_$E1` 0x007AFE1E,
    node `_$E5` 0x007AFE2E (the object skips `_$E3`).
  - `GameLogic/Object/CreateAHeroManager.cpp`: node `_$E4` 0x007ADB1D after its rowed copy. The
    atexit-only 0x007ADB11 is still registered by the AtexitInits grab-bag.
  - `ObjectCreationList.cpp`: node `_$E116` 0x007AD4CC, after its `debrisModelNamesGlobalHack`
    `_$E113`. It builds against Zero Hour's Drawable.h, so its copy 0x007AD4BC stays bridged until
    it takes the canonical header.

  Every `??_7` the four objects emit keeps its digest. link_check over the owners, both grab-bags
  and the callbacks' files: 8/8 link. image_report: bridged 670 -> 664 (exactly these six), twice
  6 -> 6, unidentified 524 -> 524.
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
  its run. Nothing in .text reads eleven of them (0x007ABC6F, 0x007ADD08, 0x007ADE88, 0x007AE043,
  0x007AE2CE, 0x007AEE6B, 0x007B014F, 0x007B042B, 0x007B08B2, 0x007B1122, 0x007B1328). That suggests
  a second header constant (inference). By the attribution TSV its includers would be W3DDisplay,
  ModuleFactory, AIUpdate, TacticalAI, GettingBuiltBehavior, RebuildHoleBehavior and
  RebuildHoleExposeDie, among others. Only SpawnBehavior::update reads its own copy (0x00E035C8).
  The header is not identified, so the eleven wait.
- *Correction: W3DDisplay does not read 0x00DE1B50.* The one DIR32 to it in updateAverageFPS is
  `fstp qword [esi*8 + 0x00DE1B50]` at 0x0004380F, which stores `fpsHistory[historyOffset++]`. esi
  is the index already incremented, so the array starts at 0x00DE1B58. The BFME 1 name
  START_CUMU_FRAME for this static (round 1 above) is therefore unsupported.
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
  - Rva0033FE65OnEnter.cpp (AIStates.cpp TU) `_$E1` 0x007AEBAA: `IDLE_COUNTDOWN_DELAY =
    BfmeLogicFramesPerSecond * 2` (`add eax, eax`). It follows AIStates' Drawable.h copy
    0x007AEB9A in its run; the fragment defines the global and its onEnter reads it. Bridged
    674 -> 673.

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
- *Not attributed (in-o7).* 0x007B3B50 (`g_00E05F24`, client / 2) is alone in its run, after
  ControlBarCommandProcessing's run, which ends with its rowed copy `_$E1` (static 0x00E05E18). Its
  static follows `g_00E05E24` and precedes getCommandAvailability's keys, so it is the next unit's
  own copy. processCommandUI reads it anyway, so the unit and the name are open.
- *Next.* Units whose global is already ledger-owned are the cheap ones: 0x007B1A27 (SlavedUpdate's
  `BfmeSlavedUpdateIntervalFrames` in SlavedUpdateRepair.cpp, held by another seat), 0x007B51EB
  (Rva005F0152ImageGet) and 0x007B67A0 (`g_aptDateInterpreter`, AptDate.cpp's POD view). The
  ctor/dtor families need the owner to declare the real class and take the cleanup row too.
  These ctor entries have a rowed ctor and cleanup, and a run that names a unit:
  - 0x007AD7DD `TheFXParticleEditor`: `BfmeDualVtableReleaseDtor` ctor 0x00203618, cleanup
    0x007B75E2. It is in ScriptEngine's run and defined in ScriptEngine_init.cpp; ScriptEngine.cpp
    is held by another seat.
  - 0x007AC022 `g_Va00DE2008`: WaterDraw shader-parameter namespace, ctor 0x0007EBFB, cleanup
    0x007B6BF5. It follows the copy 0x007AC012, which the TSV gives to W3DGameClient.
  - 0x007ADCAE `g_Va00DFE7A8`: timing-log object, ctor 0x0023DBF9, cleanup 0x007B7786. It shares a
    run with a 0x10-byte MaskInits memset and a copy the TSV gives to BoneFXUpdate (unchecked).
  - The two `ios_base` pairs come from `<iostream>` includers. Their runs' copies have no unit yet.

  The library tail (0x007B5xxx..0x007B6830) is 16-byte-aligned objects with no pool-init markers
  between them, so the marker method does not attribute entries there.

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
  - *GameEngine.cpp and g_00E063FC (halilkkaya-lk39, rowed).* GameEngine.cpp's run is its Drawable.h
    copy 0x007ADBC1 (static 0x00DFE714 after TheGameEngine), then 0x007ADBD1 (`g_00DFE718 =
    MessageBoxA == MessageBoxW`), then the marker 0x007ADBE5. The unit now includes the canonical
    Drawable.h after its first includes and defines the bool with its initializer at the end, so it
    emits `_$E1` and `_$E3` in retail's order. GameEngine::init reads the bool on its crash path.
    Zero Hour's GameEngine.cpp defines `TheSystemIsUnicode` the same way at its end (donor fact),
    and Open-BFME-1's reconstruction keeps it there; the name is not adopted. 0x007B4439
    (`g_00E063FC = timeGetTime()`) is alone in its run, and the global sits between TheNAT and
    NAT::update's stats-wait static. Its definition and its reader 0x005A671D are in
    `Rva005A6709Predicate.cpp`, which now gives it the initializer as `_$E1`.
    `Rva007ADBD1ImportInits.cpp` held nothing else and is gone (path audit: only generated reports
    name it now, `reverse/tu_map.csv`'s source column for five initializer rows and
    `reverse/link_status.csv`; no tool, hook or include). link_check: 4/4 link (GameEngine +36,
    Predicate +12, HalfRate -16; the deleted file held the other 32). image_report: bridged 673 ->
    670 (exactly these three), twice 6 -> 6, unidentified 524 -> 524.
- Separately, decide the HalfRate header constant.
- *Next leads after halilkkaya-lk39 (bridged 627 on `24abddc449`'s objects).* The cheap groups the
  entry marked ready are done; what is left needs views reconciled, merges, or one more fact:
  - Singleton-anchored copies (about 45, see "Singleton anchors" above): each needs a second fact
    (a guard, a rowed entry of the unit in the same run, or a donor include) before it is rowed.
  - Units whose run proves the copy but whose view refuses the canonical header: Mouse, INIObject,
    GameLOD, SpawnBehavior and the other Zero Hour-shaped units (they build against Zero Hour's
    Drawable.h), W3DView (Coord3D, LINK-018), FloodUpdate (Matrix3D::buildTransformMatrix),
    AnimationSoundClientBehavior (its view calls an out-of-line Drawable::getPosition) and
    BuildAssistant (private Drawable and Thing; its run also holds two FrameScaleSse entries).
  - 227 files compile an unidentified copy, most of them fragments; each TU merge that brings the
    TU file's copy home lets its row move there.
  - LinearCampaign node 0x007AD333 (target facts, not rowed): its run closes with 0x007AD348, the
    table's one registration of a second select-any pool object at 0x00DB8FEC (its later copies
    0x007AFEAC and 0x007B030B are unregistered markers). That object's data sits right after this
    node (0x00DB8FE0 + 12) in `.data`, so the node's unit is the pool header's first includer in
    link order; the callback 0x001ED580 is approved to LinearCampaignManager.cpp. GlobalLanguage's
    rowed node opens the same run, so check which of the two units owns the pool before rowing.
  - Held or left to their owners: ControlBar.cpp (Burachi-3D), AssistedTargetingUpdate
    (0x007B13C0, a codex merge), and the die modules InstantDeathBehavior, SlowDeathBehavior,
    CreateObjectDie and CrushDie (DieModule work).
  - Vtable siblings: link_check over every changed unit, its consumers and its 31 Ctor/Dtor
    sibling files gives 75/76; the one failure, ReplaceObjectUpdateModuleDataDtor.cpp
    (`??_7ReplaceObjectUpdateModuleData` differs from the first copy), already failed in the census
    (`reverse/link_status.csv`: no, one COMDAT loser), and every `??_7` the changed units emit kept
    its digest.
  - `g_00DFE718` keeps its address name; `TheSystemIsUnicode` is the donors' name for it, a lead for
    the naming lane, not this one.

**Round lk44 (halilkkaya-lk44, 2026-11-07, bridged 627 -> 601).** Each entry below was retracted
from its grab-bag and readmitted in its owner by relocation target; every touched object kept its
`??_7` digests, link_check passed on the owners with their callbacks' files, and image_report
removed exactly the named RVAs.
- *LinearCampaign (lk39's question, answered).* Every run that holds a copy of the pool
  0x00DB8FEC ends with that pool's initializer and then a 0x00DA60E8 marker: the pair is one
  includer's (0x007AD348/0x007AD362, 0x007ADCC4/0x007ADCDE, 0x007AE0B8, 0x007AEE7B, 0x007AFEAC,
  0x007B030B, 0x007B0844, 0x007B0DF0, 0x007B1190, 0x007B3D36). The node 0x007AD333 opens that pair's
  run and its `.data` precedes the pool's, so LinearCampaignManager.cpp (callback approved there)
  is the pool's first includer; GlobalLanguage's node opens the run with no marker of its own.
  The node is LinearCampaignManager.cpp's `_$E1`. The pool entry 0x007AD348 stays bridged: it is a
  select-any static our source does not define (a hatch to write by hand).
- *A `.data` marker for object starts (target fact).* Two header name lists, {NONE, HOLD, KILL,
  SPAWN, 0} and {NONE, CATAPULT_ROCK, TREBUCHET_ROCK, 0} (36 bytes at 0x00BBB50C...), open the
  `.data` of every object that includes their header. A node right after them starts a new object;
  nodes 12 bytes apart with no lists between belong to one object (or to list-less objects). Read
  with the runs, this placed the OnlineChatColors node (after the lists, before Chat.cpp's
  GameSpyColor) in Chat.cpp and the two victory nodes in INIVictorySystem.cpp.
- *Ledger-owned global.* SlavedUpdateRepair.cpp (SlavedUpdate.cpp TU) defines
  `BfmeSlavedUpdateIntervalFrames = LOGICFRAMES_PER_SECOND / 4` (0x007B1A27, `_$E1`); its run is
  SlavedUpdate's copy 0x007B1A17, then this entry.
- *Copies their TU's only compiling fragment already registers.* Where a copy's static follows a
  guard of its own class (or the copy opens a run that its unit's rowed node closes) and exactly
  one file of that TU compiles the copy, the copy is rowed there with no source change, as
  AIStates' was: UnitRevivalTracker.cpp `_$E1` 0x007AF039, ProjectileStreamUpdateGetAllPoints.cpp
  `_$E1` 0x007AEB70, Rva0037441ELeaf.cpp (StealthUpdate) `_$E1` 0x007AEED9,
  StructureToppleUpdateCrushing.cpp `_$E2` 0x007B1B4E, W3DPropDrawReact.cpp `_$E1` 0x007AC4E5,
  FXListAtBonePosFXNugget_doFxAtBones.cpp `_$E1` 0x007AD231 (FXList.cpp's run) and
  GenericObjectCreationNuggetDoStuffToObj.cpp `_$E2` 0x007AD4BC (ObjectCreationList.cpp's run). A
  merge that brings one of these fragments home must keep or re-read its ordinal.
- *Copies their own TU files compile, guard one entry back.* A copy whose static follows its unit's
  guard with one unit-owned flag between (lk39's rule wanted the guard directly before), or sits
  between the unit's singleton and its guard, is the unit's when the TU file itself compiles the
  copy: StealthDetectorUpdate.cpp 0x007B1A52, ToggleMountedSpecialAbilityUpdate.cpp 0x007B1D70
  (the flags 0x00E03BCC and 0x00E03D34 sit in a GlobalFlagClearers grab-bag), the W3DDevice
  W3DTornadoDraw.cpp 0x007AC60B and DelayedExperienceLevelGrantSystem.cpp 0x007B0241, each `_$E1`,
  and RubbleRiseUpdate.cpp `_$E2` 0x007B1B24 (its static follows the guard
  RubbleRiseUpdate::doRubbleDoneStuff tests, which the data ledger labels as
  StructureCollapseUpdate's).
  A scratch matcher found these by pairing each bridged copy's guard or owner TU (looking up to
  three `.bss` entries back) with the TU's compiling files; what it still lists needs a second fact
  (W3DGameClient's 0x007AC012 follows the widely read 0x00DE2000, whose owner is not settled) or
  belongs to held or multi-fragment TUs (ControlBar, SlowDeathBehavior, SpawnBehavior,
  RiderChangeContain, HordeContain, Object, InGameUI).
- *Nodes rowed in their units.* FXListStoreParse.cpp (FXList.cpp fragment that defines the callback
  and links) `_$E1` 0x007AD241; Chat.cpp `_$E21` 0x007AD424; FireLogicSystem.cpp `_$E4` 0x007ADFCA
  (`.data` between theFireLogicSystemParseRegistration and Rva00285FA9Parse's field table);
  GlobalWeatherSystem.cpp `_$E10` 0x007AE908 (after GameWindowManagerScript's marker-less strings);
  ScriptEngine.cpp `_$E2`/`_$E4` 0x007AD801/0x007AD816 (they close its run); GameFont.cpp
  `_$E1`/`_$E3` 0x007ADA7B/0x007ADA90 (right after BannerUI's node; FontSubstitution's callback
  directly follows GameFont's parseFontSizeMapping); INIVictorySystem.cpp `_$E1`/`_$E3`
  0x007ADA12/0x007ADA27 (WorldBuilder names the file); INIEnvironment.cpp `_$E1` 0x007AD845
  (WorldBuilder names the file); Eva.cpp `_$E7` 0x007AD202 (its INI view gains the static
  `parseMiscEvaData`).
- *Leads found, not taken.*
  - GameLogic.cpp's copy is 0x007B0615: its run is the copy, g_Va00E032E8's UnicodeString
    0x007B0625, g_Va00E032EC's map 0x007B063B, then the marker, and the copy's static 0x00E032E4
    directly precedes g_Va00E032E8. GameLogic.cpp compiles the copy as `_$E4` after g_Va00E032E8's
    `_$E1`; moving that definition below the Drawable.h include (line 1897) gives retail's order.
    GameLogic.cpp was held (class:UpdateModule, Burachi-3D).
  - MapUtil.cpp's run is copy 0x007AE595 (static right after TheMapCache), m_boundaries 0x007AE5A5
    (MapUtil compiles it as `_$E30`, unidentified because the ledger names 0x00DFF134
    g_Va00DFF134), worldDict, the supply/tech lists and TheSupplyAndTechImageLocations. MapUtil is
    Zero Hour-shaped with `object-symbol=` rows.
  - CreateAHeroSystem 0x007ADAD2: its run (copy 0x007ADAA5, vector 0x007ADAB5, node) follows
    GameFont's nodes; `.bss` has TheCreateAHeroManager (0x00DFE344) before the copy's static, and
    WorldBuilder names CreateAHero.cpp for the callback. tu_map approves CreateAHero.cpp's rows to
    GameLogic/Object/CreateAHeroManager.cpp, whose own run is the next one (copy 0x007ADB01,
    ArmySummaryDescription), so retail has two units there; settle the approval first.
  - AsciiString atexit family: readers name the units. "<!TRUE!>" 0x007AF334 -> Team.cpp,
    "ALL" 0x007AF7FE -> Scripts.cpp, "FarmTemplate" 0x007B31DF and the vector 0x007B31FA ->
    AIEconomyBuilder.cpp, "CreateAHero" 0x007B434E -> AIUnitBuilder.cpp, "<ANY>" 0x007B46C3 ->
    AIBase.cpp, "GuiFX.apt" 0x007AF0F1 -> AptGuiFX. Each global is an `unsigned` placeholder in the
    AtexitInits grab-bag; rowing needs its AsciiString type and a name (data identity) and the
    `.text$yd` cleanup row moved with it.
  - CrowdResponse 0x007B003F: WorldBuilder names CrowdResponseSystem.cpp, which the tree lacks.
    Glow/Ring/Fire (0x007AD85A..0x007AD884) follow Skybox as one list-less group, callbacks in
    Drawable_Rva0030xxxx.cpp without a TU. CloudEffect/PlayerAIType (0x007AD9E8/0x007AD9FD) are one
    object just before INIVictorySystem in `.data` and code; its file is unnamed. The INI wrapper
    sequences (CommandSet..DamageFX, SpecialPower..HeaderTemplate, Bridge) need wrapper files the
    tree lacks.

**Round lk46 (halilkkaya-lk46, 2026-11-07, bridged 605 -> 572).** Measured with
`image_report.bridge_entries` over the kept objects (exit_link's rule); the same rule gave 605 on
`2335dd1fbb`'s objects, not lk44's 601. Each entry was retracted from its grab-bag
(`reverse/deleted_rows.csv`) and readmitted in its owner by relocation target; every touched object
kept its `??_7` digests, link_check passed on the owners with their readers, and bridge_entries removed
exactly the named RVAs.
- *Runs hold one copy each (target fact).* No `.text$yc` run holds two Drawable.h copies (430 runs
  with a copy, none with two, none without a marker), so every Drawable.h includer emits the
  pool-init marker. A copy, every entry after it and its run's marker are therefore one unit, and the
  copy-first runs below need no `.bss` neighbour. This supersedes the handoff TSV's neighbour guesses
  for 0x007B433E (AIUpgradeScienceBuilder), 0x007B4698 (AIFarmKillSquad) and 0x007AF7DD (INITerrain).
- *The AsciiString atexit family (lk44's lead), done.* Each string is `AsciiString g("lit")` under
  `#pragma inline_depth( 0 )` (the out-of-line `AsciiString(const char *)` 0x0000654A, as
  Rva003EE900Forward.cpp does); its cleanup `_$E<n+1>` is `mov ecx, g; jmp ??1AsciiString@@QAE@XZ`
  with or without `BFME_ASCII_DTOR_DECL`. The global takes the AsciiString type in its owner, its
  readers drop their casts, a data row follows its owner, and the address name is kept (one global per
  address; the hatch register moves the token under `Verifier-Change`):
  - AIUnitBuilder.cpp: copy 0x007B433E `_$E1`, "CreateAHero" 0x007B434E `_$E3`/`_$E4` (cleanup
    0x007B95A4); Drawable.h after GameInfo.h.
  - AIBase.cpp: copy 0x007B4698 `_$E2`, "PrimaryAIBaseMarker" 0x007B46A8 `_$E4`/`_$E5`, "<ANY>"
    0x007B46C3 `_$E7`/`_$E8` (reader AIBase_DoXfer.cpp).
  - AIEconomyBuilder.cpp: "FarmTemplate" 0x007B31DF `_$E1`/`_$E2`. Its run continues with
    `AIEconomyBuilder::m_farmList`'s vector 0x007B31FA, still bridged: the unit's view of it is a
    12-byte POD shared by other files.
  - Team.cpp: copy 0x007AF324 `_$E1`, "<!TRUE!>" 0x007AF334 `_$E3`/`_$E4` (reader
    TeamGetControllingPlayer.cpp, `evaluateProductionCondition`).
  - ScriptWriteDataChunk.cpp (Scripts.cpp TU; Scripts.cpp itself is Zero Hour-shaped): copy 0x007AF7DD
    `_$E1`, "ALL" 0x007AF7FE `_$E3`/`_$E4`. The all-players mask between them (0x007AF7ED, a two-bit
    `BitFlags` constructor on 0x00E02D64) stays bridged: its type is not settled, and defining it will
    move the string's ordinals.
  - AptGuiFXInit.cpp: "GuiFX.apt" 0x007AF0F1 `_$E1`/`_$E2` (it opens LANChatHistory's run; AptGuiFX
    has no marker of its own).
  - W3DCamTransform.cpp: "Zoom" 0x007ACAAA `_$E1`/`_$E2` (`BfmeLiveCameraModeNameStorage`). Its copy
    0x007ACA9A stays bridged: the unit's private Matrix3D and Thing views collide with the canonical
    header (C2011).
  - Rva00101FD8Create.cpp: "LookupTablePostEffect" 0x007ACB5D `_$E1`/`_$E2`. This one was a runtime
    defect: that file already defined `const AsciiString g_00DEC3B8` default-constructed (an
    atexit-only `_$E1`), which the factory and the PostFX paths compared against, while the grab-bag
    built a second object, `g_Va00DEC3B8`, from the literal. The data row now names the readers'
    symbol. Removing that 12-byte atexit-only `_$E1` also removed a false shape credit: 0x007B6600
    (atexit-only, library tail) is now counted as bridged, so that step shows 593 -> 593.
  - Rva003EE900Forward.cpp (LivingWorldRegionEffectsManager.cpp TU): "ConqueredEffectEvenglow"
    0x007AF934 `_$E19`/`_$E20` and "ConqueredEffectFlareup" 0x007AF94F `_$E22`/`_$E23`, appended to
    the file's six sibling strings so their ordinals keep their rows. Retail's order (the nine keys
    0x007AF8E3..0x007AF9BB, then the table initializer 0x007AF9D6, the node 0x007AFC11 and the ctor
    0x007AFC26) needs that TU merged.
  - AptPalantirConstructor.cpp (the palantir unit; WorldBuilder names Palantir.cpp): copy 0x007AE39C
    `_$E1`, "Palantir.apt" 0x007AE3AC `_$E3`/`_$E4` (reader: the subsystem constructor 0x002D638E in
    OpaqueScalarDeletingDtorsB06.cpp; static after the subsystem singleton 0x00DFF028).
- *CreateAHeroSystem node (lk44's lead).* Not a TU approval question for this entry: retail has two
  units there. Run A is the copy 0x007ADAA5 (static after TheCreateAHeroManager, which CreateAHero.cpp
  defines), a vector 0x007ADAB5 and the CreateAHeroSystem node; run B is the unit
  GameLogic/Object/CreateAHeroManager.cpp already registers (copy 0x007ADB01, ArmySummaryDescription
  node). The node 0x007ADAD2 moved beside its callback `iniParseCreateAHeroSystem` in
  CreateAHero_FindBlingByUpgradeName.cpp (split from CreateAHero.cpp), `_$E2`, as FXList's did; no TU
  is asserted. tu_map's proposal of the callback to GameLogic/Object/CreateAHeroManager.cpp
  (W=CreateAHero.cpp) is the consolidation lane's to settle with these two runs as evidence. The copy
  stays bridged (the fragment's own `BitFlags` collides with thing.h), as does the vector.
- *W3DGameClient's 0x007AC012 (lk44's lead): the second fact says W3DWater, not W3DGameClient.* The
  run is the copy, then 0x007AC022, which constructs the WaterDraw shader-parameter binder at
  0x00DE2008 (ctor 0x0007EBFB; cleanup 0x007B6BF5 runs the dtor 0x0007EC44). 0x00DE2000 is the water
  render object that the binder's own callbacks read, and the binder's code sits just before
  W3DWater.cpp's rows in `.text`. Rva0007EBFBWaterDraw.cpp, which defines the binder class, now
  includes Drawable.h and defines `WaterDrawFXShaderParameterSourceNamespace g_Va00DE2008;`: copy
  `_$E1`, binder `_$E3`/`_$E4`.
- *The binder siblings.* The Terrain binder 0x007AC6DD (object 0x00DEBC64 right after its singleton
  g_00DEBC60) is Rva000E19A3Dtor.cpp's `_$E1`/`_$E2` (alone in its run; the data row takes the class
  type, sizeof 40). The Vegetation binder 0x007AC747 (object 0x00DEBC98) and its run's copy 0x007AC737
  are W3DVegetationBufferBase.cpp's `_$E3`/`_$E4` and `_$E1`.
- *Next leads (ctor scan: `mov ecx, g; call ctor; atexit` entries crossed with the ctor's file and
  the global's `.bss` neighbours).*
  - The screen filters 0x007AC8B0, 0x007AC8E0, 0x007AC910, 0x007AC940, 0x007AC956, 0x007AC9B0,
    0x007AC9C6, 0x007AC9F6: file-scope filter objects (Zero Hour's W3DShaderManager.cpp defines its
    `Screen*Filter` objects at file scope, a donor fact). Their ctors are rowed in ScreenFilter*.cpp
    fragments; the unit needs the filter classes declared once and its runs read between markers.
  - 0x007AD50B (`Rva001F4B01` at 0x00DFDD0C after TheParticleSystemManager and the copy 0x007AD4FB),
    0x007AD7C0 (a vector at 0x00DFE174 after TheScriptEngine and the copy 0x007AD7B0), 0x007AE097
    (`Rva004E5610` at 0x00DFEDFC after InGameUI's `m_replayWindow` and the copy 0x007AE087) and the two
    fire settings 0x007AE79E/0x007AE7B4 (TheFireSettingsSaved/TheFireSettings, after TheFireManager):
    each needs its object's real class in the unit that owns the run.
  - Copies whose views refuse the canonical header (W3DCamTransform, the CreateAHero fragment, and
    lk39's list), and 0x007B6600 (atexit-only, library tail).
- *Round lk46, continued (bridged 583 -> 572).*
  - AptDate.cpp `_$E1`/`_$E2` 0x007B67A0/0x007B9C50 (lk44's lead): the unit's view of
    `AptActionInterpreter` declares the rowed constructor 0x006FE980 and destructor 0x006FE9C0, so its
    existing `g_aptDateInterpreter` definition emits retail's initializer.
  - INI_loadFile.cpp (INI.cpp TU): the macro table 0x007ABBB3 `_$E1`/`_$E2` and the current file name
    0x007ABBC9 `_$E4`/`_$E5`, in retail's order. The table becomes `struct INIMacroTable` with the
    rowed constructor 0x0002DC3C and destructor 0x0002CD7B (INI.cpp's key; its data row takes that
    symbol); the name, already an AsciiString there, goes under `inline_depth( 0 )` so the
    out-of-line `AsciiString()` 0x00326BE6 is called instead of folding to an atexit-only
    initializer. That atexit-only `_$E1` had been a second false shape credit: 0x007B6190 (the thtr
    codec's atexit-only entry) now counts as bridged (582 -> 581 for two real entries).
  - *Units with `_$E` rows can take the header too.* lk39's trial refused a position whenever the build
    failed, and a unit whose rows name `_$E<n>` fails once the copy shifts its ordinals. The
    trial now judges the fresh object instead (no compile error, every `??_7` digest kept, the copy
    first and the old initializers unchanged after it) and the shifted rows are retracted and
    readmitted by relocation target. ScriptEngine.cpp (copy 0x007AD7B0 `_$E1`, static after
    TheScriptEngine; nodes to `_$E4`/`_$E6`, Drawable.h after FieldParse.h) and Eva.cpp (copy
    0x007AD1B3 `_$E1`, static after TheEva; nodes to `_$E3`..`_$E9`, after Rva000427195.h) took it.
    SlavedUpdateRepair.cpp, Armor.cpp, Mouse.cpp, INIObject.cpp and SpawnBehavior.cpp still fail to
    compile with it at their six latest include positions (Zero Hour-shaped views, as lk39 found).
  - *Nodes that close their runs are their marker unit's.* The marker ends the unit that emits it and
    the INI wrappers emit none, so a node directly before a marker is the marker unit's own node.
    Seven such nodes moved beside their callbacks, each `_$E1` unless noted: ScoredKillEvaAnnouncer
    0x007B0010 (ScoredKillEvaAnnouncerController.cpp; its `.data` follows the header name lists that
    open a new object), MissionObjectiveList 0x007B0383
    (MissionObjectiveTracker_ParseMapMissionObjective.cpp), ShadowMap 0x007ABFE3
    (Rva0007BA35Method.cpp), CrowdResponse 0x007B003F (CrowdResponseBlockParse.cpp), MeshNameMatches
    0x007B01FD (MeshInstancingParse.cpp), EmotionNugget 0x007B0354 (Rva004DCAD2Parse.cpp) and
    LivingWorldSound 0x007AFCB4 (LivingWorldSound.cpp `_$E4`, after the unit's region initializer).
  - *Leads checked, not taken.* AptButtonTooltipMap (copy 0x007ADB82 and node 0x007ADB92, one unit
    after the Apt player's 0x00DFE4CC): Rva00224A3F.cpp defines the node and its two-entry field table
    as one aggregate record, so the node needs splitting from the table first. The fire settings
    0x007AE79E/0x007AE7B4 and the Fire node 0x007AE7CA (INIBfmeSettingsParsers.cpp, marker-less, before
    a map-object unit's copy): their cleanups jump to 0x0030AF8F, rowed as
    `??1Rva0030AF8FAudioEventRTS@@QAE@XZ`, which is the settings class's implicit destructor (two
    AsciiString members), so that row's identity comes first. 0x007B51EB constructs
    `Rva005F0152ImageGet.cpp`'s `MappedImageCache Rva00A06858` through the ctor rowed as
    `??0Rva005F00FB@@QAE@XZ`: one class under two names. SkirmishAIData/AIDozerAssignment (run after the
    copy 0x007AE14A, static after g_00DFEEF8) have their callbacks in two files.
    FXParticleSystem's node (excluded) and LivingWorldMapInfo (class:LivingWorldManager) were left.

**Round lk51 (halilkkaya-lk51, 2026-11-07, bridged 572 -> 548).** Measured with
`image_report.bridge_entries` over the kept objects (exit_link's rule) on `154ad4a447`'s tree plus the
round. Each copy was retracted from the HalfRate grab-bag (`reverse/deleted_rows.csv`) and readmitted in
its file by relocation target; every touched object kept its `??_7` digests, link_check passed on the
files with their TU siblings, and bridge_entries removed exactly the named RVAs at each step.
- *INIObject.cpp off Zero Hour's headers (lk46's blocked list).* The unit's two callbacks only read a
  token and build AsciiStrings, so it now builds on `ascii_string.h` and the canonical
  `Common/INI/INI.h`, as the other INI units do, and then includes the canonical Drawable.h; its cl line
  drops the Zero Hour include paths. Its copy 0x007AD453 opens the run its three nodes close, so it is
  `_$E1` and the nodes move from `_$E10/_$E12/_$E14` to `_$E3/_$E5/_$E7` (the Zero Hour headers had used
  the early ordinals). Small Zero Hour-shaped units whose bodies need only INI and AsciiString can take
  the same route; Armor.cpp, Mouse.cpp, GameLOD.cpp and SpawnBehavior.cpp use much more of Zero Hour's
  class graph and were not tried.
- *The rule used for the rest (target and object facts).* In all 394 of our objects that compile a copy,
  no non-dynamic static follows the copy's static in its section, so a unit's copy closes its `.bss`.
  The statics of a non-inline function live in its own unit, and a `getModuleNameKey`'s pool key and
  guard sit with the code retail placed in its class's region (the first definer). So when a bridged
  copy's static directly follows a function-local static (at most a flag between), and no other copy
  sits between, the copy belongs to the unit of the file that defines that function. A scratch scanner
  (data-ledger entry below each bridged static, then the owning function's row, file and tu_map TU)
  listed 86 such copies; held, excluded and refusing units were left (below).
- *Taken (23).* Each file includes the canonical Drawable.h at the latest include position where the
  unit compiles (trial: fresh object, no compile error, copy first, every `??_7` digest kept), or
  already compiled the copy:
  - module pool keys: SpellRechargeModifierUpgrade.cpp 0x007B219E, Collide/HordeMemberCollide.cpp
    0x007B265A, Update/CivilianSpawnCollide.cpp 0x007B274A, ObjectGuardingHelperPoolKey.cpp 0x007B2FE0,
    RunOffMapBehavior.cpp 0x007B0D45 (the flag between, 0x00E03624, and the run's `list<int>` 0x00E0362C
    are read by code in the class's region and by the AI exit states), SiegeDeploySpecialPower.cpp
    0x007B2A1C, CastleUpgrade.cpp 0x007B2270, and StructureCollapseUpdate's 0x007B1AFA in
    Rva004A44B1.cpp (doCollapseDoneStuff; StructureCollapseUpdate.cpp refuses the header);
  - other function guards: StrategicInGameUIQueueUnitButton.cpp 0x007B53AA (GetButtonImage
    0x005F8BD4) and StrategicInGameUIGetButtonImage.cpp 0x007B521B (0x005F0383, another unit),
    BfmeLogMsg574.cpp 0x007AEB1C, ScriptEngineGetTeamNamed.cpp 0x007AEC1A (ScriptEngine.cpp's own copy
    is 0x007AD7B0, so getTeamNamed is another unit), Rva003FF02EPowerCap.cpp 0x007AFCF8,
    AIPlayerQueueSupplyTruck.cpp 0x007B32E3, Rva0050AEE4KillContained.cpp 0x007B3664 (`_$E2`),
    InGameHeroSelectInterfaceCtor.cpp 0x007B395B, SpecialPowerModuleRva0049402B.cpp 0x007B16AD (its
    function reads the flag between), Rva005C7889Init.cpp 0x007B4922;
  - files that already compiled the copy: PlayerBecomingLocal.cpp 0x007AE19E,
    InGameToggleStanceCommandButtonCtor.cpp 0x007B3F1E, CastleBehaviorRegisterOwnedObject.cpp
    0x007AF244 (`_$E2`; the copy closes the CastleBehavior block 0x00E027C8..0x00E0282C),
    HordeContainChangeToFormation.cpp 0x007B0DE0, and ActionManagerSpecialPowerChecks.cpp 0x007B013F
    (`_$E3`; the copy opens the run in-o6 gave ActionManager, its static follows TheActionManager, Zero
    Hour's ActionManager.cpp includes GameClient/Drawable.h, and this is the TU's only compiling file).

  A merge that brings one of these fragments home must keep or re-read its ordinal.
- *Refused (re_attempts.log).* ToppleUpdate.cpp 0x007B1C10, FoundationAIUpdate.cpp 0x007B08F6 and
  SpecialAbilityUpdate.cpp 0x007B078B (which opens its five ZeroInits masks) do not compile with the
  canonical header at their latest include positions. AptMainMenu.cpp 0x007B3886 compiles, but the
  copy shifts its two `object-symbol=_$E2/_$E4` campaign-string cleanup rows; those hatch rows need a
  supported respelling first.
- *Checked, not taken (one more fact needed).*
  - TerrainResourceManager 0x007AECC6: between its guard and the copy sit the `ios_base::Init` and
    `_Loc_init` objects 0x00E01E40/41, whose initializers 0x007AECA4/0x007AEC8E open the copy's run. The
    run is one `<iostream>` includer's, but whether that is TerrainResourceManager.cpp is open.
  - AptMapPreview 0x007B4194 and AptMyHero 0x007B4722: the globals between their statics and the copy
    are read by other units (AptMpChat and FileTransfer; WWLib's Rva005B0E9F), so the copy may be a
    unit with no other `.bss`.
  - WanderAIUpdate 0x007B1C88: the flag between is `g_bfmeDockingTraceActive`, and the next entry is a
    docking unit's key.
  - SiegeEngineContain 0x007B0EF6 / HordeSiegeEngineContain 0x007B0F20 and SymbioticStructuresBody
    0x007B27B8 / DetachableRiderBody 0x007B2830: each pair has its own runs, but tu_map approves both
    guards' files to one TU (HordeSiegeEngineContain.cpp, ImmortalBody.cpp), so rowing both would put
    two copies in one approved TU. Settle the approvals first.
  - InvisibilityManagerRva00438E5B.cpp 0x007B0685: tu_map approves 0x00438E5B to GameLogic.cpp, whose
    copy lk44 placed at 0x007B0615; one of the two is wrong. Rva005E936AGet 0x007B5197: a constructed
    object 0x00E06778 sits between, and its initializer opens the run.
  - AIUpdate 0x007ADE78 (six fragments compile a copy; the guard's pool-key file does not),
    RiderChangeContain 0x007B0F74 (Zero Hour-shaped; two other fragments compile one), BoneFXUpdate
    0x007B13EA (Zero Hour-shaped), FloatUpdate 0x007B14E0 and BoneFXDamage 0x007B24C0 (class claims
    held by another contributor), the five special powers in ElvenWoodSpecialPower.cpp (held), and
    GiantBirdAIUpdate 0x007AEDD7 (class claim held).
- *Next.* Singleton-anchored copies still need a second fact. For each bridged copy, the nearest owned
  `.bss` entry below it, whether that file compiles a copy, and whether Zero Hour's same-named `.cpp`
  includes GameClient/Drawable.h give the shortlist (View, W3DTerrainTracks, W3DTerrainVisual,
  MilesAudioManager, InGameUI and BuildAssistant have the donor include). The brief's harder items
  (W3DCamTransform's private Matrix3D/Thing, the CreateAHero fragment's private `BitFlags<int, class>`,
  Scripts' mask 0x007AF7ED, AIEconomyBuilder's `m_farmList`, the fire settings, 0x007B51EB and the
  screen filters) are unchanged; the ctor families also need their `.text$yd` cleanup rows moved out of
  `Rva007B6880Thunks.cpp`, which another seat holds.

**Round lk54 (halilkkaya-lk54, 2026-11-07, bridged 548 -> 529).** Measured with
`image_report.bridge_entries` over the kept objects (exit_link's rule) on `0aff0e89c0`'s tree plus the
round. Each entry was retracted (`reverse/deleted_rows.csv`) and readmitted by relocation target; every
touched object kept its `??_7` digests, link_check passed on the files with their TU siblings, and
bridge_entries removed exactly the named RVAs.
- *Where MSVC 7.1 puts a unit's statics (object and link facts: scratch units such as `int *g; const
  int C = f(); int fn(int v) { static int s = v; return s; }`, compiled through `build.compiler_command`
  into `build/`, then linked with the toolchain's link.exe and read from the MAP).* A unit's plain
  zero-initialized globals, then its dynamically initialized statics in definition order (the Drawable.h
  copy first, since the header comes first), share the main `.bss` section. Every function-local static
  and guard, of an inline or a non-inline function, gets its own COMDAT `.bss` section (`/O1`, `/O2`,
  `/Od` and `/Gy-` alike). cl creates the main `.bss` as section 3 when the unit has any plain
  zero-initialized global (even one defined last), and last, after every COMDAT, when it has none.
  link.exe keeps one object's sections in section-table order (a scratch link of three objects, in both
  link orders). So:
  - a unit with a plain global (an Apt screen's instance, a singleton, a flag) lays out
    `[plain globals][copy, dynamic statics][function-local statics]`;
  - a unit without one lays out `[function-local statics][copy, dynamic statics]`.

  Retail shows both: Team, AwardSystemManager, the palantir unit and Mouse (copies proven by their runs)
  have their own function-local statics after the copy; SpawnBehavior and WallUpgradeUpdate (no plain
  global) have their pool key and guard before it.
- *What that changes.* Round lk51's rule (a copy whose static follows a unit's function-local static is
  that unit's) holds only for a unit with no plain zero-initialized global. When the unit has one, its
  copy precedes its own function-local statics, and a copy after them belongs to the next object. A
  ledger entry that looks like a plain global can be a guard flag with a grab-bag home
  (`GlobalFlagClearers*`) or a function-local AsciiString with an address name; read who uses it first.
  Re-checked this way, none of lk51's 23 rows shows its own unit's plain global before the statics it
  follows, so none is proven wrong; three have an unidentified entry in between and stay to be confirmed
  (StrategicInGameUIGetButtonImage after the dynamic MappedImageCache 0x00A06858,
  StrategicInGameUIQueueUnitButton after 0x00A06918, InGameHeroSelectInterfaceCtor after 0x00A04954 and
  0x00A04964). The rule did reverse lk51's blocked AptMainMenu attribution below.
- *Taken (5).*
  - Rva003B242CGet.cpp (the MapObject unit's Dict file): copy 0x007AE7DF `_$E1` opens the run whose last
    entry is this file's Dict initializer 0x007AE806, now `_$E3`. The `.bss` agrees (copy 0x00E0093C,
    then the dynamic map-object list holder 0x00E00940 and the Dict 0x00E00944). Zero Hour's
    WorldHeightMap.cpp defines the same pair (`MapObject::TheMapObjectListPtr`, `TheWorldDict`; donor
    fact); in BFME 2 the unit sits in the MapObject code region. The holder's initializer 0x007AE7FB stays
    bridged: our definition is in GameLogicInit.cpp, outside this lane's scope.
  - AptMainMenu.cpp: copy 0x007B385C `_$E1` (static 0x00E048E4 after the instance 0x00E048DC and the
    restart thread 0x00E048E0, before the statics of rva00514950, evilCampaign and goodCampaign). The two
    campaign cleanups move to `_$E4` (good, 0x007B91A8) and `_$E6` (evil, 0x007B919E), read by relocation
    target; the object-symbol= `??__Fcampaign@...` rows are gone and the file has none left. Round lk51's
    0x007B3886 was the wrong copy.
  - AptOptions.cpp: 0x007B3886 `_$E1` (static after AptOptions' instance 0x00E04908; AptOnline's instance
    0x00E04904 has no copy). AptCreateAHero.cpp: 0x007B3832 `_$E1` (after `s_instance` 0x00E048D4).
    AptLanLobby.cpp: 0x007B071D `_$E1` (after `s_instance` 0x00E03354). Each is the approved TU file and
    takes the header after its last include.
- *Refused (re_attempts.log).* GiantBirdAIUpdate.cpp 0x007AEDD7 (no plain global: its statics
  0x00E01EAC..0x00E01EB8, then the copy and its five masks) does not compile with the header: its private
  `Thing`/`Object` views collide (C2011). AptMyHero.cpp 0x007B46F8 (instance 0x00E06450, the copy, then
  rva005B0A53's static AsciiString 0x00E06458 and guard) refuses it too: its private `Matrix3D` lacks
  `Rotate_Vector`. Both need their views reconciled onto the canonical classes first.
- *Leads settled, not taken.*
  - 0x007AEA1C (copy after TheSidesList) is SidesList.cpp's. Zero Hour's SidesList.cpp defines
    `TheSidesList` and then `static AsciiString static_readPlayerNames[MAX_PLAYER_COUNT]` (donor fact);
    retail's run is the copy, then 0x007AEA2C, an `__ehvec_ctor` over 20 AsciiStrings at 0x00E01D60, and
    BFME 2 code uses MAX_PLAYER_COUNT = 20. Our ScriptEngine.cpp's definition of TheSidesList is
    misplaced (ScriptEngine.cpp's own copy is 0x007AD7B0). To row it, SidesList.cpp (Zero Hour-shaped,
    PreRTS.h) needs the canonical Drawable.h, then the TheSidesList definition and the array (out of
    Rva007AEA2CArrayInits.cpp), in that order.
  - 0x007B1C88 is WorkerAIUpdate's, not WanderAIUpdate's: the plain global g_bfmeDockingTraceActive, the
    copy, then WorkerAIUpdate's getActionDelayForDock statics 0x00E03CB0..0x00E03CB8 (Zero Hour's
    `key_warehouseUpdate`/`key_centerUpdate`) and its pool key. Zero Hour's WorkerAIUpdate.cpp includes
    GameClient/Drawable.h. Our WorkerAIUpdate.cpp is Zero Hour-shaped (PreRTS.h).
  - TerrainResourceManager 0x007AECC6: the run is CAtlWinModule's selectany initializer (0x007AEC78, not
    in the table), `_Loc_init` 0x007AEC8E, `ios_base::Init` 0x007AECA4, an atexit-only object 0x007AECBA
    and the copy, so its unit includes ATL's atlbase.h, then `<iostream>`, then Drawable.h. The unit has
    no plain global (its function-local statics 0x00E01E2C..0x00E01E3C, from code in its region
    0x00359853.., come first), so the run is TerrainResourceManager's. The ATL include is the open
    question; 0x007ABC99..0x007ABCE7 is a second unit of the same shape.
  - 0x007B0615 (static after `AptSaveLoad::s_instance` 0x00E032E0) is AptSaveLoad's: its run continues
    with g_Va00E032E8's UnicodeString and g_Va00E032EC's map, the dynamic statics after the copy. So
    lk44's GameLogic.cpp lead is wrong, and GameLogic.cpp's `_$E1` for g_Va00E032E8 is misplaced.
    GameLogic.cpp is held (Burachi-3D).
  - LivingWorldSound.cpp's `_$E1` builds `Region2D g_00E02EAC` with the default constructor, but retail
    0x007AFC6B builds it as (-FLT_MAX, -FLT_MAX)..(FLT_MAX, FLT_MAX) through the two-endpoint ctor
    0x00004C06, so our image's zoom region starts at zero (a runtime defect). Retail inlines the Coord2D
    temporaries and has an empty inline Region2D dtor (cleanup 0x007B816A is a lone `ret`), so the unit
    needs the canonical Lib/Region2D.h and a Coord2D with an inline two-float ctor instead of WWMath's
    region.h. The node before it, 0x007AFC56 (LivingWorldArmyIcon), belongs to the object before the
    header name lists at 0x009C17CC, not to LivingWorldSound.
  - Rva007B6880Thunks.cpp and Rva007ABB96AllocCtorInits.cpp are claimed by ancalgonn-swarm-defects, so
    the ctor-family moves (with their cleanup rows) and the AllocCtor entries wait.
- *Copies inside or closing their own unit (543 -> 529, 14 more).* Two readings of the layout rule
  settle a copy without a guard of its own class:
  - *Sandwich.* The copy's static sits between a plain global and a function-local static of the same
    unit (readers or tu_map put both in one TU). One object's sections are contiguous, so the copy is
    that object's: TerrainLogic.cpp `_$E2` 0x007ADF88 (TheTerrainLogic, g_waypointListHead, then
    Bridge::Bridge's statics; no `_$E1` is emitted), ScriptConditions.cpp 0x007AF889, GameStateMap.cpp
    0x007B0115, W3DHordeModelDrawManager.cpp 0x007ABFB9, WinMain.cpp 0x007AB7F0 (retail's first entry;
    ApplicationHWnd..gLoadScreenBitmap, then nextParam's buffer), AIPathfind.cpp 0x007AE51D (g_00DFF0D0,
    read only by AIPathfind code, then Pathfinder::rva002EC479's guard), MineshaftPortalBehaviour.cpp
    0x007AEEAF and MilesAudioManager.cpp `_$E3` 0x007ABDC1 (AudioEventsReloaded, then rva00058314's
    function-local vector 0x00DE1E54: a "G" in the ledger, an F by its readers).
  - *Closing.* The copy follows statics that only unit X's code reads and precedes the next object's
    function-local statics; that next object therefore has no plain global and its own copy comes after
    its statics (all four are registered), so the copy closes X: W3DTreeDraw.cpp 0x007AC491,
    W3DScriptedModelDraw.cpp 0x007AC36B, ControlBarCommand.cpp 0x007B3B7A and Made002CC774.cpp
    0x007B35C2.
  - Plus SelectionXlat.cpp 0x007B04B3 (after TheSelectionTranslator; Zero Hour's SelectionXlat.cpp
    defines it and includes GameClient/Drawable.h) and TacticalAI.cpp 0x007AE2BE (after g_00DFEFCC,
    read only by TacticalAI code; its run continues with the logic-rate /2 constant 0x007AE2CE, whose
    static directly follows the copy's, so both are TacticalAI's dynamic statics; the constant's header
    is still unknown and it stays bridged).

  No copy static taken this round is read by any code but its initializer (raw DIR32 scan), so the
  grab-bag retractions leave nothing uninitialized. That check matters for the FrameRate-shaped copy
  0x007AF85F: its static 0x00E02D9C is ScriptActions' flash interval, read by the flash actions through
  the grab-bag's `g_00E02D9C`, so its readers must move to the TU's own constant in the same change.
- *Refused this round (re_attempts.log).* Weapon.cpp 0x007AE2F8 (TheWeaponStore and the weapon reload
  flag, then makeAssistanceRequest's statics) and GameClient.cpp 0x007ADC48 (TheGameClient, then
  GameClient::update's lastStallTime) are sandwiches, but both files are Zero Hour-shaped (PreRTS.h) and
  the canonical header stops compilation (C1903). InGameUI.cpp 0x007AE087 is the same case untried: its
  run is the copy, the Rva004E5610 object 0x00DFEDFC and the frame constant 0x00DFEE08, all after
  TheInGameUI and m_replayWindow.
- *A misplaced lk51 row.* bfmeLogMsg574 (0x00333B36) lies in LuaScriptEngine's code region, and
  LuaScriptEngine has plain globals (g_activeObj12F0610, read only by LuaScriptEngine code), so its
  object is [TheLuaScriptEngine, g_activeObj, copy 0x007AEAF2][bfmeLogMsg574's output and guard]. The
  copy lk51 rowed in BfmeLogMsg574.cpp, 0x007AEB1C, is the next object's; BfmeLogMsg574.cpp's `_$E1`
  is retail 0x007AEAF2. Moving that row changes no count (0x007AEB1C becomes bridged again until its
  unit is found).
- *Next.* Take the singleton-anchored copies with the layout rule: a copy directly after a unit's plain
  global is that unit's when the unit includes Drawable.h (a run entry of the unit after the copy, a
  function-local static of the unit after it, or a donor include, settles it). 52 bridged copies
  directly follow another copy, so copy-only units are common and that second fact is needed. Read who
  uses a ledger "global" before classifying it: flags in `GlobalFlagClearers*` are often guards, and
  address-named entries can be function-local objects. Units whose views refuse the header
  (GiantBirdAIUpdate, AptMyHero, WorkerAIUpdate, SidesList, Weapon, GameClient, InGameUI and lk51's
  list) need their private views reconciled or their Zero Hour headers replaced first.
**Round lk58 (halilkkaya-lk58, 2026-11-07, bridged 529 -> 494).** Measured with
`image_report.bridge_entries` over the kept objects (exit_link's rule) on `1c19aa750b`'s tree plus the
round. Each entry was retracted (`reverse/deleted_rows.csv`) and readmitted by relocation target; every
touched object kept its `??_7` digests, link_check passed on the changed files (for TheSidesList, on all
28 files that name it), and bridge_entries removed exactly the named RVAs at each step.
- *Round lk54's settled leads, done.*
  - BfmeLogMsg574.cpp's `_$E1` is now retail 0x007AEAF2, LuaScriptEngine's copy (the unit's plain
    TheLuaScriptEngine and g_activeObj12F0610, the copy, then bfmeLogMsg574's output and guard).
    0x007AEB1C is back in the HalfRate grab-bag under its address name, its tombstone removed in the same
    commit. No count change.
  - LivingWorldSound.cpp defines `Region2D g_00E02EAC(Coord2D(-FLT_MAX, -FLT_MAX), Coord2D(FLT_MAX,
    FLT_MAX))` on the canonical Lib/Region2D.h and Lib/Coord2DCtorView.h instead of WWMath's region.h.
    Its `_$E1` is retail 0x007AFC6B (73 bytes, same relocation order) and `_$E2` the lone-ret cleanup
    0x007B816A; Rva007AFC6BRegionInit.cpp is deleted. The runtime defect (a zero default zoom region) is
    fixed. 529 -> 528.
  - ScriptActions: the only readers of 0x00E02D9C are the flash actions 0x003BB5B7 and 0x003BFF50, and a
    unit reads only its own copy, so 0x007AF85F belongs to ScriptActionsRva003BB5B7.cpp, which defines
    both. The actions now divide by the file's own DRAWABLE_FRAMES_PER_FLASH, and the grab-bag's
    `g_00E02D9C` and its writer go in the same commit; `_$E1` = 0x007AF85F. 528 -> 527.
  - SidesList.cpp defines TheSidesList (moved from ScriptEngine.cpp with its data row), then
    `static AsciiString static_readPlayerNames[20]`: `_$E28` = 0x007AEA1C, `_$E30` = 0x007AEA2C, `_$E31` =
    0x007B7BBE. The object's .bss is TheSidesList +0, the copy +4, the array +8, as retail. ArrayInits'
    `g_Va00E01D60` is gone with its data row and hatch line. 527 -> 525.
- *GameClient/DrawableFramesPerFlash.h (new; the canonical Drawable.h now includes it).* It holds
  the canonical header's one dynamic constant. A unit that cannot take the whole canonical Drawable.h
  includes it where retail's unit included Drawable.h and builds the same 16-byte copy. Such units build
  on Zero Hour's PreRTS.h and Thing, or keep a private Thing, Drawable or Matrix3D view. Units that include
  Zero Hour's GameClient/Drawable.h put `reference/shims/bfme2_drawable_flash` first on their `// cl:`
  include path. That shim reads Zero Hour's header with its compile-time constant renamed, then includes
  the BFME 2 header. BoneFXUpdate's private Drawable.h shim includes it in place of the Zero Hour line.
  This retires the "canonical header refuses" blocker for every logged copy except the held ones.
- *Taken this way (525 -> 494, 31 copies).*
  - Zero Hour includers (shim): WorkerAIUpdate 0x007B1C88 `_$E28`, Weapon 0x007AE2F8 `_$E23`,
    GameClient 0x007ADC48 `_$E22`, RiderChangeContain 0x007B0F74 `_$E22`, Mouse 0x007AD3A6 `_$E22` (nodes
    now `_$E36/_$E38`), Armor 0x007ACFE5 `_$E14` (node `_$E18`), GameLOD 0x007AD6F3 `_$E24` (nodes
    `_$E29.._$E41`), SpawnBehavior 0x007B0BFF `_$E16` (g_00E035C8 `_$E88`), InGameUI 0x007AE087 `_$E25`,
    BridgeBehavior 0x007B094A `_$E16`, DozerAIUpdate 0x007B142E `_$E26`, View 0x007ADDF9 `_$E14`;
    BoneFXUpdate 0x007B13EA `_$E18` through its own shim.
  - Private views or Zero Hour headers without Drawable.h (header include): ToppleUpdate 0x007B1C10
    `_$E4`, FoundationAIUpdate 0x007B08F6, GiantBirdAIUpdate 0x007AEDD7, PlaceEventTranslator 0x007B054B
    (noCanDoSound's cleanup becomes the bare `_$E4`, replacing an object-symbol= row), SiegeDockingBehavior
    0x007B0A40, FloodUpdate 0x007B150A, AnimationSoundClientBehavior 0x007B2C32, AptMyHero 0x007B46F8,
    W3DView 0x007AC07C `_$E6` (TheW3DFrameLengthInMsec now `_$E8`; Coord3D untouched), SpecialAbilityUpdate
    0x007B078B, BuildAssistant 0x007AF1CE, ActiveBody 0x007B2774, AutoHealBehavior 0x007B0834,
    StatusBitsUpgradeIfEldestKindof 0x007B2024, PhysicsUpdate 0x007AF18A, FlammableUpdate `_$E14`
    0x007B14B6, GameWindowManager 0x007AE240 `_$E14`, and SlavedUpdateRepair.cpp 0x007B1A17 (`_$E1`,
    ahead of the interval initializer, now `_$E3`, that the same run holds). Unmarked ordinals are `_$E1`.
  - Attribution, for each: the earlier rounds' logged evidence (runs for Mouse, Armor, GameLOD,
    SpawnBehavior and W3DView; .bss for the rest). A copy that closes a unit's own function-local statics
    in a unit with no plain global (lk54's rule) gives RiderChangeContain, ToppleUpdate,
    FoundationAIUpdate, BoneFXUpdate, GiantBirdAIUpdate, PlaceEventTranslator, SiegeDockingBehavior,
    FloodUpdate, AnimationSoundClientBehavior, ActiveBody, AutoHealBehavior, BridgeBehavior, StatusBits,
    PhysicsUpdate (PhysicsBehavior's key), DozerAIUpdate, FlammableUpdate and SlavedUpdate. The copy sits
    inside or right after the unit's plain globals for Weapon, GameClient, InGameUI, WorkerAIUpdate,
    AptMyHero and BuildAssistant. GameWindowManager is a sandwich: TheWindowManager, the copy, then
    assignDefaultGadgetLook's statics. View is singleton-anchored (TheTacticalView, the copy alone in its
    run) and Zero Hour's View.cpp includes GameClient/Drawable.h.
  - A merge that brings SlavedUpdateRepair.cpp into SlavedUpdate.cpp, or FlammableUpdateDtor.cpp into
    FlammableUpdate.cpp, must keep the copy ahead of the unit's other initializers.
- *Leads, not taken.*
  - The AI unit: 0x007AE14A's static follows `g_00DFEEF8` (238 references, `Rva002A8F24` type,
    defined in Rva005EEA20Find.cpp), and its run is the copy, then the AIDozerAssignment and
    SkirmishAIData nodes 0x007AE15A/0x007AE16F (callbacks 0x002A92F2, 0x002A8A31). That is Zero Hour's
    AI.cpp shape (TheAI, then its two INI blocks), so `g_00DFEEF8` is TheAI's slot. Rowing needs one
    file to define the global, the copy and both nodes, and the callbacks have no approved TU yet.
    Player's own copy stays 0x007AE19E: becomingLocalPlayer's statics follow the AI copy, and Player has
    no plain global.
  - W3DProjectedShadow: TheW3DProjectedShadowManager, then the copy 0x007ACB09, then two more plain
    globals, then the copy 0x007ACB33, then flushDecals' statics. These are two objects. Which one is
    W3DProjectedShadow.cpp needs the second object's plain globals (g_00DEC2D4, Rva00DEC2D8Manager)
    placed first.
  - In-run entries of units now owning their copy: InGameUI's object 0x007AE097 (0x00DFEDFC,
    ctor 0x004E5610) and `g_00DFEE08 = BfmeLogicFramesPerSecond` 0x007AE0AD; SpecialAbilityUpdate's
    five ZeroInits masks and `g_00E033D0 = BfmeLogicFramesPerSecond` 0x007B07F5; GiantBirdAIUpdate's
    five MaskInits; BuildAssistant's two FrameScaleSse floats. Each belongs in the unit after its copy
    once its header or name is known (the `= BfmeLogicFramesPerSecond` copies share one unknown header
    constant).
  - `g_bfmeDockingTraceActive` (0x00E03CA8) is WorkerAIUpdate's plain global by the same layout (it
    opens that object's .bss before the copy), but AIUpdateInterfaceFindNearestLabeledContactPoint.cpp
    defines it; moving the definition and its data row would match retail's .bss and changes no count.
  - Held this round: FloatUpdate 0x007B14E0 and BoneFXDamage 0x007B24C0 (class claims, lk56), the
    ElvenWoodSpecialPower.cpp five (one file holds five units' copies), the DieModule units, ControlBar,
    AssistedTargetingUpdate. TerrainResourceManager (ATL then `<iostream>` then Drawable.h) is unchanged.


**2026-11-07 AptDate lookup consolidation.** AptDateLookup.cpp is absorbed into the approved AptDate.cpp after the calendar view declared the native const-qualified virtual lookup with its existing clock offsets. All 87 code rows, the cache data row and three EH graphs verify. Local link preview against 436fb45367 preserves the combined 9,825 bytes (4,746 plus 5,079). The outgoing path audit covers the sole removed path since 9c81acd297. The merge tool repoints functions.csv and tu_map.csv. The old path remains in a merge provenance comment, an EH provenance note and historical census, verdict and evidence records. The interpreter initializer and cleanup still belong to AptDate.cpp. A real-link run containing the merge is pending.


**2026-11-07 AptDate interpreter storage.** The data verifier independently confirms the 72-byte zero-filled allocation at VA 0x00E182E0. It belongs to AptDate.cpp alongside the matched initializer 0x007B67A0 and cleanup 0x007B9C50. The ledger addition does not edit the source or its startup actions.
