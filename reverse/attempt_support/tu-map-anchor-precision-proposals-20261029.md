# tu_map anchor precision: measured proposals for maintainers

Seat halilkkaya-bf1, 2026-10-29. Every figure below compares maps rebuilt in memory
(`tu_map.build`) from the same inputs, with and without one experimental change. I
committed none of these changes. Each needs an owner decision or a structured input
first.

Three narrow rules already landed, each with tests and with `tu_map.py --validate` and
`tu_evidence.py --validate` unchanged:

- An implicit copy constructor takes no Z from another constructor (+139 TU-APPROVED).
- A hinted TU that straddles two anchored TUs and reaches past both merges with neither
  (`contested()`, +78).
- A ZH `Tools/` file anchors no game TU (-6, all six rows approved into Tools paths).

Evidence kinds, kept apart:

- **Target**: retail addresses, row order, ledger notes.
- **Donor**: Zero Hour file layout.
- **Inference**: what the two together suggest.

## 1. Compiler-generated destructors as COMDATs (+141 / -38)

**Change.** A `??1X` row of a ZH-known class gets no Z, S or N when ZH defines no `X::~X`
in either a .cpp or a header.

**Gains:**

- debug_debug.cpp +56
- Win32GameEngine.cpp +27 (target: `??1W3DModuleFactory@@UAE@XZ` at 0x00042100 sits
  in Win32GameEngine's run)
- W3DModuleFactory.cpp +22
- ModuleFactory.cpp +18

**Losses:**

- LANGameInfo.cpp -10 (`??1LANGameSlot` at 0x00447B0E sits in LANGameInfo's run, and
  its S was right)
- StealthUpdate -7
- debug_cmd -5
- TileData -5

**Open question.** A compiler-generated destructor is emitted where the vftable or the
owning object is built. That is often the class's own TU, but not always. Decide
whether S may place it.

## 2. Rows the ledger notes as ICF-folded (+28 / -69)

**Change.** About 1,620 rows whose notes say `ICF-folded`, `folded copy` or `ICF fold`
take no Z, S or N.

**Gains:**

- AIHarvest.cpp +18
- MonsterDockUpdate +5
- AIDock +3

**Losses:**

- AptOnline.cpp -43
- AIDozerManager -17
- ElvenWoodSpecialPower's run retargets to WeaponChange, Scavenger and CloudBreak.

**Target facts.**

- 0x00544AB3 `?xfer@AIHarvestPrepareSiteState` notes: "ICF-folded: slot 3 of five".
- 0x004A0E47 `?loadPostProcess@MonsterDockUpdate` notes: "also
  SupplyCenter/RepairDockUpdate slot 1; one folded copy".

**Blocker.** The notes are free text and mix "this body is the fold owner" with "this
name is one of the folded aliases". A rule needs a structured token, for example
`fold-of=<owner symbol>`, written by the tool that proves the fold.

## 3. Dropping ZH Tools/ from Z/S outright (-242)

**What I tried.** Drop Tools/ from Z and S entirely, instead of the landed rule that only
refuses to anchor a Tools TU.

**What happened.**

- The pluglib Matrix4 rows fell back to N hints.
- Header-inline Matrix4, SphereClass and PlaneClass rows at 0x00068FEF..0x00069168 then
  U-merged into WWMath/matrix4.cpp through its S row 0x0006905B.
- That six-row run inside BaseHeightMap.cpp's span stopped being an island and broke
  BaseHeightMap (-186).

**Root cause.** S places header-inline non-virtual members. That is deliberate (test
`test_class_site_evidence_kept_for_out_of_line_and_non_virtual_members`), but it makes
any new S on a math class able to break the TUs that inline it. Revisit only together
with that decision.

## 4. The ModuleFactory COMDAT pile (no approval change, one false TU)

**Target fact.** 0x00252CB5..0x00256461 holds ModuleData constructors and destructors,
`buildFieldParse`, `friend_newModuleData` and `name` bodies for dozens of modules. That
is the shape of `ModuleFactory::init`'s per-module instantiations.

**What tu_map does.** Their class names give N hints, and U merges them into a
116-row "UpgradeSoundSelectorClientBehavior.cpp". The queue then serves that TU as
noncontiguous, because it is broken by ModuleFactory's own Z row 0x00255C5E.

**Proposed change.** Header-inline module boilerplate (`??[01]*ModuleData@@`,
`?friend_new*`, `?buildFieldParse@*ModuleData@@`) carries no N, as `COMDAT` already
does for cluster choice.

**Effect.** It recovers no approvals, but it removes a false TU from the
tu-approval queue.

## 5. A lone far row stretching a span: ImmortalBody.cpp (65 rows)

**Target fact.** ImmortalBody's constructor, `getModuleNameKey` and
`internalChangeHealth` sit at 0x004C086E..0x004C0918. `?xfer@ImmortalBody` sits at
0x004C20BA: 27 bytes, Version 1 then `ActiveBody::xfer`.

**Inference.** That body shape is shared by many body modules, so it is likely an ICF
fold. It lies within GAP of the other three rows, so ImmortalBody's span covers
StructureBody (Z) and the hinted Respawn, DelayedDeath, FreeLife, DetachableRider,
Oathbreaker and PorcupineFormation bodies. U merges all of them into ImmortalBody, and
none is approved.

**Fix.** Needs item 2's structured fold token. A narrower variant ("an ICF-folded Z row
may form an island") changes nothing here, because there are no longer runs on both
sides.

## 6. BFME 2 file organisation unlike Zero Hour's (no rule)

The Z rows below are correct for ZH and may be wrong for BFME 2. Zero Hour cannot
settle them:

- CriticalSectionClass ctor/dtor (Z=critsection.cpp) inside mutex.cpp's run
  (0x00613AE0, 0x00613B10).
- WindowTranslator's constructor (Z=WindowXlat.cpp) inside GameClient.cpp's run
  (0x002390E8, 82 proposed rows).
- `Render2DClass::Add_Tri` (Z=render2d.cpp) inside W3DDisplay.cpp's run (0x00045708).

These need target evidence (a `__FILE__` string, a WorldBuilder self-assert) per row.

## 7. Constructor arity conflation beyond copy constructors (8 rows, no rule)

Eight constructor rows take Z from a ZH constructor of a different arity: default vs
parameterised. Four are approved:

- `??0ArmorTemplate@@QAE@ABVAsciiString@@@Z` at 0x001D8F68
- `??0Waypoint@@QAE@XZ` at 0x002823D1
- `??0SkirmishPreferences@@QAE@H@Z` at 0x0043C128
- `??0LANPreferences@@QAE@H@Z` at 0x0044D2F5

Each sits in its ZH file's run, so the conflation is harmless today.

## 8. Free functions defined once in Zero Hour (+1,631 / -610)

**Change.** A free function (`?name@@Y...` or `?name@@Z...`) whose name exactly one ZH
game .cpp defines at file scope gets Z for that file. ZH defines 2,846 free function
names, 2,762 of them in a single file. 713 ledger rows match one, and 493 of those are
unassigned today.

**Gains:**

- GameClient.cpp +163
- CommandLine.cpp +114
- MainMenuUtils.cpp +87
- PartitionManager.cpp +79
- W3DControlBar.cpp +73
- GadgetListBox.cpp +67

**Losses:**

- TerrainLogic.cpp -292
- PeerDefs.cpp -159
- WideStrLenSource.cpp -35
- debug_except.cpp -23
- ATL.cpp -19
- md5c.c -6 (ZH's md5.cpp against BFME 2's vendored md5c.c)

**Assessment.** BFME 2 moved many free helpers between files. A new Z anchor that is
never an island turns each moved helper into a span breaker.

**Island variant measured (+1,632 / -294).** A run whose Z comes only from a free
function may be an island. That removes the TerrainLogic loss (-292 to -4). Still lost:

- PeerDefs.cpp -159. `GetAdditionalDisconnectsFromUserFile` (ZH PopupPlayerInfo.cpp)
  sits at 0x00384A00 inside PeerDefs's run, and the hinted rows around it now U-merge
  into the newly anchored PopupPlayerInfo.cpp, so the run is too long to be an island.
- WideStrLenSource.cpp -35. ZH AsciiString.cpp's `skipWhitespace`, `skipSeps` and
  `skipNonSeps` sit at 0x000357C0..0x00035DB0.
- PartitionManager -26, MapUtil -20, ATL -19.

**Recommendation.** The gain is large enough to justify an owner review of per-file
exceptions, or a precision gate like L's (held-out free-function Z rows against their
bracketing anchors at 99% or better) before it anchors.

Landed instead: members written inside a class a ZH .cpp defines (+190, -6).

## 9. COMDAT-pattern names carry no N (+531 / -599)

**Change.** Drop N for every name `COMDAT` matches (`??_G`/`??_E`, `?friend_new*`,
`??[01]*ModuleData@@`).

**Effect.** Gains include ModuleFactory.cpp +51 (item 4) and AptOnlineLogin.cpp +64.
Losses spread across many module TUs whose own ModuleData constructors and destructors
sit inside them. Too broad as stated. Item 4's narrower form, restricted to the
ModuleFactory pile, needs an address-range or caller-based test.

## 10. Every header-inline member as a COMDAT for S (+738 / -116)

**Change.** `header_comdat` treats every member whose ZH body sits in a header as a
COMDAT, not only constructors and virtual members. This reverses the decision that
`test_class_site_evidence_kept_for_out_of_line_and_non_virtual_members` encodes
(RenderObjClass::Get_Bits keeps S). Measured at 3d869178d5.

**Gains:**

- StrategicInGameUI.cpp +238
- AIPlayer.cpp +140
- W3DDynamicLight.cpp +38 (RingRenderObjClass::Peek_Inner_Scale_Channel, inline in
  ringobj.h, at 0x0006E12F no longer breaks it)
- W3DShadowMapManager +28
- streakRender +27
- LANGameInfo +24
- BaseHeightMap +21

**Losses:**

- BattlePlanUpdate.cpp -47
- seglinerenderer -15
- lightenvironment -8
- chunkio -8
- aabox -6

**Assessment.** This is the root of item 3: math and refcount inline helpers
(Matrix3D, Vector3, RefCountClass::Release_Ref) are emitted wherever they are used.
The net is clearly positive, but it overturns a recorded decision, so it is the
owner's call.

## 11. An approved TU named by Zero Hour's file, which BFME 2 split out (lead only)

**Target facts.**

- `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLoginMenu.cpp` is
  approved with 106 rows: 31 GameSpyLoginPreferences members
  (0x005C9DA8..0x005CB1B3), C rows and funclets.
- None of its rows is a WOLLoginMenu function.

**Donor facts.**

- ZH writes GameSpyLoginPreferences inside WOLLoginMenu.cpp, which gives the Z and S.
- `reverse/worldbuilder_source_paths.csv` records
  `C:\Projects\bfme2\Code\GameEngine\Source\Common\GameSpyLoginPreferences.cpp` in
  worldbuilder.exe.

**Inference.** BFME 2 moved the class into its own file, so the approved TU probably
carries the wrong path.

**Risk.** A merge would write these rows into the ZH file name. tu_map has no route by
which a WorldBuilder path can override a Z/S file name, and the consolidation doc rules
that a WorldBuilder path approves nothing. This needs a maintainer decision: either
rename the TU after its merge, or allow a WorldBuilder path to name a TU whose rows are
all one class.

This predates this session. The in-class-member rule only turned the class's
constructor and destructor from S into Z.

## 12. Provisional names that would rename a Zero Hour-named file (4 TUs)

Of 518 approved provisional TUs, four hold rows that all sit in one existing file. That
file has a ZH .cpp name different from the provisional name, so a merge would move the
rows from a ZH-named file to a naming-hint name:

- `ScopedCriticalSection.cpp`, rows now in NameKeyGenerator.cpp
- `W3DDevice/GameClient/WWMath.cpp`, rows now in W3DRoadBuffer.cpp
- `IMEManagerInterface.cpp`, rows now in IMEManager.cpp
- `WWLib/Buffer.cpp`, rows now in buff.cpp

The last case comes from 3d869178d5. Its rows used to carry a wrong
Z=WW3D2/bw_render.cpp from BW_Render's nested Buffer class.

**Proposed check.** tu_skeleton (or provisional()) could refuse a provisional merge
whose only donor already has a ZH file name.

## Checks run against my scratch scripts

`#if 0` code in ZH .cpp files yields no Z anchor in use: 43 definitions exist only
there, and none is referenced. 445 (class, method) pairs have several ZH .cpp files.
For a pair defined in the game tree too, Z picks the game file because the walk is
sorted; pairs defined only in Tools/ are what the landed Tools rule now covers.
