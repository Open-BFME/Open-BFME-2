### LINK-692: two retail scoped-lock classes shared the name `CriticalSectionLock`
Status: Repair landed / awaiting verification. Updated: 2026-11-18; inspected revision: `d2c836ff88`.

Evidence / affected units: `Common/Rva001DBBAD.cpp` (180 B) and `GameClient/GUI/GameWindowTransitions.cpp`
(2,934 B) failed `comdat ??1CriticalSectionLock@@QAE@XZ (retail: unproven and differs from the kept
copy)`. Both define a private `CriticalSectionLock` whose out-of-line destructor is the 9-byte
`push [ecx]; call LeaveCriticalSection; ret`, and both come ahead of the name's owner in the census's
link order (positions 3937 and 3942; `Find_Asset.cpp`, 16060, rows 0x0061FC60 as the 10-byte
`mov eax,[ecx]; push eax; call; ret`). The earlier reading, written into GameWindowTransitions.cpp
and behind the `#pragma optimize("t", on)` pair `16ad168ccf` retired from Rva001DBBAD.cpp, was that
these units need the favor-speed shape. Retail says otherwise:

- A scan of retail `.text` for rel32 jumps and calls finds 0x0061FC60 reached only by the nine unwind
  funclets at 0x007A7513..0x007A76C3 (the asset-manager units).
- The unwind funclets of these two units, 0x0076987E (`Rva001DBAA4::unlock`) and 0x007698D9, jump to
  0x001DBA9B, whose 9 bytes are exactly the body these units emit (digest 68c485ad2a, the one the
  census proves retail for `?leave@Rva001DBA9BSectionView@@QAEXXZ`, the row at that address).
- 0x001DBA85, the 22 bytes just before it, is the matching constructor, rowed as
  `??0Rva001DBA85@@QAE@PAX@Z` (GapBodiesGE49.cpp). The pair sits directly ahead of the
  `Rva001DBAA4` functions (0x001DBAA4..), where the first object needing them out of line put them.

So retail has two lock classes: the asset-manager one (0x0061FC40 / 0x0061FC60) and a GameEngine
one (0x001DBA85 / 0x001DBA9B). One name for both made the GameEngine copy a wrong
`CriticalSectionLock`.

Completed: the private view in both units is renamed `Rva001DBA85`, the class the ledger already
names at the constructor's address (a placeholder for a placeholder: no real name is claimed). Both
objects now emit `??1Rva001DBA85@@QAE@XZ` with retail's bytes for 0x001DBA9B and no
`CriticalSectionLock` symbol. `./build.sh` of both: 40/40 exact. `link_check.py` (index
`147fd3e52b`): both LINK, 0 -> 3,114 bytes.

Remaining / next check: 0x001DBA9B is still rowed as `Rva001DBA9BSectionView::leave` in
Bfme5SmallTests.cpp and pinned as `??1Gen_uw_001dba9b@@QAE@XZ` for the two generated funclets
(`uw_0076987e`, `uw_007698d9`, uw_gen_001.cpp). With an approved unit for 0x001DBA85 and 0x001DBA9B
(`tu_map.csv` has none), the pair belongs to `Rva001DBA85` in the `Rva001DBAA4` unit, and the two
funclets can then be repointed onto their parents, which already emit them. The constructor's
parameter is `CRITICAL_SECTION *` in these views and `void *` in the row's name; neither is proven.
Do not restore the `"t",on` pair in Rva001DBBAD.cpp: it produced the other class's body.
Clearance: the two units' scope cleared by the current-object preview above.
Census confirmation: awaiting; the preview does not change the headline.
