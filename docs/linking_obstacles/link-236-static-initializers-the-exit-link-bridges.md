### LINK-236: static initializers the exit link bridges

Status: open (lane started 2026-11-04 by halilkkaya-in-o1 at `993e6014c8`; halilkkaya-in-o2 at
`f2cec2a7f8`: report tie fix, Drawable.h constant and 84 rowed copies, bridged 969 -> 885 on the
fixed report; next seat continues).

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
| `INI/Rva007ABBF6BlockParseInits.cpp` | 130 |
| `StaticTagInitializers.cpp` | 63 |
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
