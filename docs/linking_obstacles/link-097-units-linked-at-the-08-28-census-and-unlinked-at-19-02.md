### LINK-097: units linked at the 08:28 census and unlinked at 19:02 (consolidation window)

**Status: Open (2 repaired here; 2 fixed upstream; 4 held by other workers). Updated: 2026-10-26; inspected revision: `acfc3c889a`; census index `5ce093a71a` (2026-10-26 19:02).**

- **Evidence / affected units:** comparing `reverse/link_status.csv` from the 08:28
  recorder `d1f046749a` (measured tree `47e030bafc`) with the 19:02 recorder
  `bf3dd31211` leaves 43 path-stable units that linked and no longer did, 95,344
  bytes by current `target_size`. 223 further linked paths disappeared into
  consolidation merges and cannot be compared by path; 75 consolidation-created
  TUs are not in the census and `link_check.py` refuses to preview them
  ("not in census ... not previewable") until the next census. Current-object
  previews against the 19:02 index: 38 of the 43 link cleanly (86,849 bytes),
  and `ObjectCreationListStore.cpp`'s 312 bytes also links when checked with
  its ctor unit (the 43-batch still reports it because it uses the census's
  ctor object). Four remain: `SidesList_sidesInfo.cpp` (1,817 B, duplicate
  `??4SubsystemInterface@@QAEAAV0@ABV0@@Z`), `Common/Rva005189CFText.cpp`
  (279 B, unresolved `?BfmeLODLevelNames@@3PAPBDA`),
  `subsystem/SubsystemInterfaceCopy.cpp` (68 B, the same duplicate) and
  `W3DPropDrawModuleDataCtor.cpp` (33 B, vtable first-copy).
- **Completed (this pass):**
  - `GameLogicDestructor.cpp` (887 B, commit `link: restore GameLogicDestructor's 13-slot SubsystemInterface view`): `de67bc5003` adopted the
    one-slot canonical `SubsystemInterface.h` here while `GameLogicInit.cpp`
    keeps its 13-slot private view, so the secondary vtable
    `??_7GameLogic@@6BSubsystemInterface@@@` lost by link order (no retail
    address). Restored the 13-virtual view; the adoption PASS compared function
    bytes but not emitted COMDAT vtables. `./build.sh` OK 30/30,
  - `GameLogicInit.cpp` (attempt 2026-10-31): adopting canonical `Code/Libraries/Source/subsystem/SubsystemInterface.h`
    is blocked because `GameLogicInit.cpp` calls `reset()` and `update()` (slots 9 and 10 of retail's 14-slot table
    `0x00BD77A0`) across multiple subsystems (`TheSidesList`, `TheTaintManager`, `TheVictorySystem`,
    `TheMineshaftPortalNetworkManager`), and derived classes (`TeamFactory`) rely on these virtual methods.
    Adopting the 1-slot canonical header causes C2039. Kept the 14-slot private view matching `GameLogicDestructor.cpp`.
    `link_check.py` 0 -> 887 B.
  - `ObjectCreationListStore.cpp` (312 B, commit `link: give ObjectCreationListStore the canonical SubsystemInterface base`): `Rva001F092ACtor.cpp`
    derived from a private `BFME2NativeNetwork` base with an inline virtual
    dtor, emitting a second `??_7ObjectCreationListStore@@6B@` whose dtor slot
    was not the canonical out-of-line 0x001B4E74. Derive from the canonical
    12-byte `SubsystemInterface` instead; `./build.sh` OK 7/7 across both
    units, ctor stays 118 B.
  - `AptValue/Rva006DF470Initialize.cpp` (1,374 B) was fixed independently
    upstream by `5581a2a2cf`; `DozerAIUpdateCtor.cpp` (8,003 B) by the fix
    recorded in LINK-096.
- **Remaining / next check:** the four held units above. `SidesList_sidesInfo.cpp`
  and `SubsystemInterfaceCopy.cpp` share one cause: the canonical out-of-line
  copy assignment COMDAT does not agree with the unit's own declaration.
  `Rva005189CFText.cpp` needs a coordinated data-name pass: the LOD table is
  defined as `?rva00202B6CNames@@3PAPBDA` in `Rva00202B6CGet.cpp` and five other
  consumers use that spelling, while the ledger's provisional name is
  `BfmeLODLevelNames`; a consumer-only edit would break the other five.
- **Census confirmation:** awaiting. The 19:02 census's 7,569,166 B omits the
  43 units' 95,344 B; the current preview relinks 87,161 B of that
  (86,849 + 312), so a fresh census should measure above the 08:28 peak's
  7,614,012 B if nothing else moves.

**2026-10-27 package c140 follow-up, inspected `a0b82f68445de8ab0254437ef7e97332ce48cfb0`, ordinary-preview index `bf3dd31211` (2026-10-27 00:39):** The SubsystemInterface assignment copies in `SubsystemInterfaceCopy.cpp` and `SidesList_sidesInfo.cpp` have the same retail-proven digest `2f838b02686b`; the duplicate is a strong-versus-COMDAT collision. A `__declspec(noinline) inline` owner trial made the two-unit preview report LINKS but dropped `??4SubsystemInterface@@QAEAAV0@ABV0@@Z` from the owner object, so the 2-row byte check failed and the trial was reversed. The restored owner passes 2/2 and both units retain D1 in the final cohort. The canonical `Code/Libraries/Source/subsystem/SubsystemInterface.h` declares the copy constructor but omits copy assignment, allowing SidesList to emit an implicit assignment. Next: declare the existing out-of-line assignment in that shared header, retain its row in the owner and verify all header dependents. Shared-header edits were outside this package. No clearance or census gain is claimed.

**2026-10-27 `Rva005189CFText.cpp` cleared (ordinary preview, index `bf3dd31211`):** the unit was the only consumer that spelled the LOD level-name table 0x009B95F4 as `BfmeLODLevelNames`, a name no object defines. It now declares the defined `rva00202B6CNames` (Rva00202B6CGet.cpp), the spelling the other five consumers already bind, so no other unit changes. `./build.sh` OK 7/7 and 4 string refs; `link_check.py` 0 -> 279 B. The data ledger row's provisional name is still `BfmeLODLevelNames`; settling the single real name stays with the data lane. Census confirmation: awaiting.

**2026-10-27 assignment repair, control `12b5b45db2`, same ordinary-preview
index:** the canonical header now declares the existing out-of-line assignment.
SidesList's implicit definition disappears; the owner's 31-byte row and
relocation remain unchanged. All 548 header dependents plus the owner pass:
4,604 function rows, 107 data rows, string/float/import checks, EH (704 EXACT
and the same three baselined differences) and converged data. The unchanged
548-unit preview cohort goes from 484 to 486 clean units, with no regressions
or other blocker-list changes. SidesList clears 1,714 authored bytes and the
owner 68 (+1,782 preview bytes); this clears the assignment-duplicate pair
only. The W3DPropDraw prerequisite remains open; the LOD consumer was
subsequently repaired as recorded above, with its data identity still pending.
Census confirmation remains pending. [Durable scope and evidence](../../reverse/attempt_support/subsystem-assignment-link-20261027-codex3.md).
