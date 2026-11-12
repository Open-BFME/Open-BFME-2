### LINK-662: canonical header adoption drops a unit's noinline destructor
Status: Repair landed / awaiting census confirmation (the 16:28 census at 4ba87ee6df predates the repair; see the
lk105 regression sweep below). Updated: 2026-11-12; inspected revision: d3809cf5c05 (census index c31795c94c).

**Problem.** OwnedPointerResets.cpp defines the 5-byte pointee destructors its owning-pointer resets and clears
call (each `~X` tail-jumps to a rowed clear helper). Retail calls those destructors out of line, so the unit's
private views declared them `__declspec(noinline)`. Five adoptions replaced the private views with generated
canonical headers (`tools/header_adopt_lane.py`) that declare a plain `~X();`, so cl expanded each destructor and
the resets and clears called the clear helper instead:

| canonical header commit (StarkillerHDX) | destructor | rows that changed call target |
|---|---|---|
| "Register canonical Rva00527FA2, adopt it in 5 units" (2026-11-11, before the census) | 0x00527FA2 | ?reset@Rva002D390E, ?clear@Rva002D3931 |
| "Register canonical Rva005D32D4, adopt it in 3 units" (2026-11-11, before the census) | 0x005D32D4 | ?clear@Rva005786CD |
| "Register canonical Rva0052710C, adopt it in 4 units" (2026-11-11, before the census) | 0x0052710C | ?reset@Rva002D38AE, ?clear@Rva002D3894 |
| "Register canonical Rva004E668E, adopt it in 3 units" (2026-11-12, after the census) | 0x004E668E | ?reset@Rva0029B5FD, ?clear@Rva0029B5E3 |
| "Register canonical Rva005E893E, adopt it in 3 units" (2026-11-12, after the census) | 0x005E893E | ?reset@Rva005CE236, ?clear@Rva005CE21C |

The byte gate passed all nine rows (`Functions: OK 79/79`): each new REL32 target is one `jmp` away from retail's.
link_check refuses the five COMDAT resets ("not retail's body"). So OwnedPointerResets.cpp was already at 0 bytes in
the c31795c94c census. After the Rva005E893E adoption, ThrowingNewHelpers.cpp (1,388 B in the census) also stopped
linking, because its `m_build.reset(...)` selects OwnedPointerResets.cpp's wrong `?reset@Rva005CE236` copy.
AptPalantirCallbacks.cpp, which calls the Rva002D38AE and Rva002D390E resets, was at 0 bytes for the same reason.

**Completed.** "Keep OwnedPointerResets.cpp's six pointee destructors out of line under their canonical headers"
puts `__declspec(noinline)` on the unit's out-of-line definitions of the five canonical destructors (0x004E668E,
0x0052710C, 0x00527FA2, 0x005D32D4, 0x005E893E). 0x005D4FFC still has its private noinline declaration. No header
or contract is edited. Object diff before and after: exactly the nine REL32 targets change (clear helper -> `??1X`),
plus `.debug$S`. A REL32 check of all 79 rows against retail found 9 different targets before and 0 after. Retail
evidence: for example, 0x005CE236+0x14 is `e8 f0a60100` -> 0x005E893E and 0x005786CD+0xD is `e8 f6ab0500`
-> 0x005D32D4. `./build.sh` exact 79/79; `find_declared_unmatched` clean; scoped DIR32 OK. link_check
(c31795c94c) over the 13 units that define, include or call these classes: 13/13 LINKS, LINKED 17,792 -> 21,358 B
(OwnedPointerResets.cpp 0 -> 1,927, AptPalantirCallbacks.cpp 0 -> 1,639, ThrowingNewHelpers.cpp back to 1,388,
the other ten unchanged).

**Recipe.** When a unit defines a destructor (or any small member) that retail calls out of line, and the unit
adopts a canonical header that declares it plainly, put `__declspec(noinline)` on the unit's definition. Do not
re-declare the class privately. Compare every REL32 target of the unit's rows with retail, not only the byte gate.

**Remaining / next check.** Tooling (not edited here): header_adopt_lane could refuse an adoption that changes a
REL32 target of a matched row, as LINK-660 asks for novtable. The byte gate could also report a REL32 target that
differs from retail's even when one `jmp` joins the two. Census confirmation: awaiting the next published census
(expect OwnedPointerResets.cpp and AptPalantirCallbacks.cpp to link and ThrowingNewHelpers.cpp to return).

### Regression sweep over the 16:28 census (2026-11-12, seat halilkkaya-lk105)

Base `54e2556eae9`. Census 2026-11-12 16:28 at `4ba87ee6df` (link_check index `5e2fc81a04`), compared with the 00:41
census at `b7f2abb266`.

**Method.** First, the per-unit `reverse/link_status.csv` of the two "link_census: census ..." commits. Then
link_check over the 1,541 sources changed since `c31795c94c` or reached by a changed header
(`header_dependents.py --range`), about 6 s per 100 units, and finally over all 17,730 ledger units at the base.
A REL32 check compared every rowed function's call targets with retail's (lk104's relchk, generalized).

**What the census lost.** LINKED 7,660,390 -> 7,646,960 B (-13,430), files linked 17,683 -> 17,675. Eight units went
from "yes" to "no":

| cause | units (bytes in the 00:41 census) | causing commit (author) | state at the base |
|---|---|---|---|
| LINK-662 (noinline destructors inlined) | InGameUIHandleBuildPlacements 4,280; StrategicInGameUIPlanningPhaseBuildingSelectionCtor 2,343; ThrowingNewHelpers 1,388; InGameUIPlaceBuildAvailable 561 (8,572 B) | "Register canonical Rva004E668E, adopt it in 3 units", "Register canonical Rva005E893E, adopt it in 3 units" (StarkillerHDX) | repaired after the census by "Keep OwnedPointerResets.cpp's six pointee destructors out of line under their canonical headers"; all four LINK when checked together with OwnedPointerResets.cpp (8,577 B) |
| a respell removed the only provider | Win32BIGFileSystem 2,559 (also the third unresolved symbol of the real link at 6e1bad5179) | "P143: the pathfinder's outer map inserts on its Rva00534743Record value" (Jon Farmer) | repaired on master after the base by "Use the matched tree copy in Win32BIGFileSystem" (Krzysztof Włoch, LINK-229) |
| LINK-664 (generated header drops the size) | SidesList 2,346 | "Register canonical Rva0032A3A9Element, adopt it in 3 units" (StarkillerHDX) | open; the file and the class were held by other seats |
| LINK-663 (re-based scaffold view) | Rva0056AD19Dtor 312 | "OpaqueScalarDeletingDtorsB12: adopt the registered parents for Rva0056AD19" (nleigh) | repaired here, 0 -> 315 B |
| file retired | DieModuleDerived.cpp | nleigh's "Exit ... from DieModuleDerived" series | not a loss: its seven destination units link in both censuses |

**Since the census.** link_check finds no new loser among the 54 commits from `4ba87ee6df` to the base. Four
"does not link" verdicts (Rva005CE4FADtor, Rva005CF4A8SelectionCtor, ThrowingNewHelpers, the
PlanningPhaseBuildingSelection constructor) are stale-index artefacts: each LINKS when checked with
VslotNullCheckedForwarders3.cpp and OwnedPointerResets.cpp, whose census objects predate lk104's moves.
At the base, link_check over all 17,730 ledger units reports 17,653 LINK (668 s). Of the 77 that do not, only two
linked in either census: SidesList.cpp (LINK-664) and Win32BIGFileSystem.cpp (repaired since). Four others also
fail locally: BfmeStringTailRecord180Ctor, Rva00236285Ctor, BaseHeightMap_Rva00069F4F and atlbasemodule. Each
reports an STLport `__imp_` symbol or `___ImageBase` as unresolved, although the index records each as linked.
These are local false alarms: Rva00236285Ctor.cpp's object has the census digest, and none of the four sources
changed after the census. No unit that LINKS is lower than its census bytes.

**Removed `novtable` / `noinline` since `c31795c94c`.** Every removal in `git log -p -- Code` is accounted
for. Rva006DE350's six units (LINK-660) are repaired, ObjectTypes and CrateCollideModuleData keep or deliberately
change theirs, and the OwnedPointerResets destructors (this entry) are repaired. Two other removals remain.
B12's Rva0056AC26A/B bases led to LINK-663. Rva003AEEB3's two noinline constructors went in "Adopt the canonical
Rva003AEEB3 and DefaultModuleHeadBase in three FX base units", and the REL32 check shows no changed target in
those units.

**Silent form (REL32 one `jmp` away).** No new instance. Over all units, 18 call sites name a symbol whose retail
target is a `jmp` to it (LINK-662's shape). Fifteen are the StringBase release pattern below (4 rows, 11 funclets),
and 3 are funclets of the Rva002294A3 and Rva0073F4F3 destructors in units unchanged since the census. Only two
of the 18 are in changed units, SidesList.cpp and GameLogicInit.cpp, both in that pattern. The pattern itself is
long-standing and repeats across the code base. 467 rows call `??1AsciiString@@QAE@XZ` (0x0048BA39,
`jmp 0x00036410`) where retail calls 0x00036410 directly (ModuleFactoryInit.cpp alone has 194 and linked in both
censuses), and 15 call StringBase's destructor or releaseBuffer where retail calls 0x0048BA39. This check matches
funclets by label name, and the object renumbers labels, so its funclet results are only indicative. None of these
breaks a link, so none was repaired.

**Done (commits by subject).** "Give B12's Rva0056AD19 scaffold the Rva0056AC26 base so its primary table has
retail's five slots again" (LINK-663) and "Give Rva0056AD19's primary table retail's slot 1, the shared false body"
(the table now equals 0x0086D1EC slot for slot).

**Measure.** lk74_snap/lk74_cmp with HEAD's `vtable_bridge.py`, base -> after: bridged 3,349 -> 3,348, slots
50,526 -> 50,521, already correct 2,216 -> 2,217, mismatching source slots 37,929 -> 37,925, refusals identical (33),
nothing newly bridged, no correct table lost. The base differs from lk104's final snapshot by 5 newly bridged tables
and 2 lost correct ones. All 7 come from "data_ledger: four stale rows that hid boot-path vtables from the bridge",
which widened 0x0081B5D0, 0x0081B5E0 and 0x0083702C to their real extents and retyped 0x0081C8F0 as a vtable.
That change exposed short tables; it is not a source regression.

**Refusals / deferrals (re_attempts.log).**
- false-reject rename.py --to-class, 0x0056AD79: Rva0056AD19's Base2 table 0x0086D1B0 holds this 7-byte body in
  slot 13, its only image reference, and Base2 declares the slot `bool slot13()`. The placeholder row is
  spelled `unsigned char get() const` (`QBEEXZ`), and --to-class keeps the return type. It refuses a full
  `--new` that changes `E` to `_N`, the same kind as the 0x00130FCE `H`/`_N` record. 1 table.
- deferred, 0x0032B580 (SidesList.cpp, LINK-664): the file and the class were held by other seats.

**Next leads.**
1. LINK-664: SidesList.cpp once the Rva0032A3A9Element header carries its 0x80 size (or a decl-only
   `_Destroy<Rva0032A3A9Element *>` in the unit).
2. Tooling: `header_adopt_lane` could refuse an adoption that changes a matched row's REL32 target (this entry) or
   shrinks `sizeof` below the contract (LINK-664). A respell that stops a unit defining a COMDAT could be checked
   against every object that references the symbol. P143's message reports other definers for each symbol its
   units stopped defining. Even so, the real link at 6e1bad5179 left the void* `_M_create_node` unresolved: only
   Win32BIGFileSystem.cpp's own `_M_clone_node` copy named it. Run locally on objects identical to the census's,
   link_check reports STLport `__imp_` symbols and `___ImageBase` as unresolved (four units above), while the
   census links them.
3. LINK-514, same class: Rva0056AD19's secondary table 0x0086D1B0 differs from retail only in slot 13, which is
   0x0056AD79 (`mov eax,[ecx+0Ch]; mov al,[eax+26h]; ret`, the Base2 override that reads the m_14 task's byte
   +0x26). It is rowed as the placeholder `?get@Rva0056AD79ByteChaseField@@QBEEXZ` in Disp8ByteChaseGetters.cpp.
   The --to-class move is ready, with prepared sources, once a byte-to-bool return respell exists (refusal above).
4. The next published census should show the four LINK-662 units, Win32BIGFileSystem.cpp and Rva0056AD19Dtor.cpp
   back (about 11,450 B), and SidesList.cpp still missing until LINK-664 is fixed.
