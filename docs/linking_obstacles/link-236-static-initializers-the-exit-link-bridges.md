### LINK-236: static initializers the exit link bridges

Status: open (lane started 2026-11-04 by halilkkaya-in-o1 at `993e6014c8`; halilkkaya-in-o2 at
`f2cec2a7f8`: report tie fix, Drawable.h constant and 84 rowed copies, bridged 969 -> 885 on the
fixed report; halilkkaya-in-o3: BlockParse registrations are per-unit file-scope nodes, 40
rowed in their units, bridged 885 -> 845; halilkkaya-in-o4: the msgr/thtr service records are
file-scope objects of the 0x0065D090 constructor, 64 registered, bridged 845 -> 781; next seat
continues).

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
| `Rva007AB7F0HalfRateInits.cpp` | 425 (341 after in-o2) |
| `INI/Rva007ABBF6BlockParseInits.cpp` | 130 (90 after in-o3) |
| `StaticTagInitializers.cpp` | 63 (0 after in-o4) |
| `GameNetwork/Rva007B55E0TxnNameInits.cpp` | 62 |
| `Rva007AD295ZeroInits.cpp` | 56 |
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
- *Next.* The units that fail to compile need their private `Thing`/`Drawable` views reconciled
  with the canonical header (header-adoption lane) before the include. Held units can follow the
  same steps once free. The handoff table lists each copy.

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

**How to attribute a TU.**
- Neighbouring entries in retail's table that are already registered by a known object bound the run.
- The static's `.bss` address falls inside its TU's data contribution next to ledgered globals.

**Runtime hazards found (not counted in `initializers_bridged`).**
- **Registered twice (116).** Objects register an initializer whose retail entry another object
  already registers, so the image builds that global twice. 52 come from
  `FXParticleSystemFactories.obj`, which re-emits `ModuleTag<...>::s_key`/`s_name` template-static
  initializers rowed in `FXParticleSystemModules.cpp`; an example is 0x007AF6F3. Retail compiled these
  once. The split `FXParticleSystem*` files each instantiate them, and merging those files into their
  TU removes the copies.
- **Unidentified (342).** Registrations whose shape and relocations match no retail entry. 224 are
  in `FXParticleSystem.obj`, `FXParticleSystemFactories.obj` and `FXParticleSystemModules.obj`; for
  example `g_categoryModuleTemplate<N>` ctor+atexit. They run in our image and never in retail. Check
  whether retail initializes these statically before an image boots.
- **Shape-only credits (3).** These are listed in `by_shape_only` and are weak.

**Next useful checks.**
- Pick a family whose global already has a data-ledger owner and apply the method there. The
  `Rva007ADBD1ImportInits.cpp` timeGetTime globals are owned by `Network.cpp` and
  `Rva005A6709Predicate.cpp`.
- Separately, decide the HalfRate header constant.
