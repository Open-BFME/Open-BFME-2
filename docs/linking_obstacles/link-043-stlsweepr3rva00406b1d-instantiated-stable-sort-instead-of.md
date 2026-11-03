### LINK-043: StlSweepR3Rva00406B1D instantiated stable_sort instead of emitting scalar deleting destructor
Status: Open for the extended family; original unit cleared. Updated: 2026-10-26; inspected revision: 896af216804e1f1e34de28bd318285fbbbfcc536.
Evidence / affected units: `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00406B1D.cpp`,
`reverse/link_status.csv` reported 4 unresolved blockers (`??0Rva00406B1DRecord@@QAE@ABU0@@Z`, `??1Rva00406B1DRecord@@QAE@XZ`, `??4Rva00406B1DRecord@@QAEAAU0@ABU0@@Z`, `??MRva00406B1DRecord@@QBE_NABU0@@Z`).
Completed: Retail 0x00406B1D (28 B) is the scalar deleting destructor `??_GRva00406B1DRecord@@QAEPAXI@Z` calling ~Rva00215E42 at 0x004059AC. Replaced `stable_sort` template instantiation with direct delete anchor calling rowed dtor provider `??1Rva00215E42@@UAE@XZ` via `/alternatename`, resolving all 4 unresolved symbols.
Remaining / next check: none for the original unit (inspected b06312df51); the extended family below still needs three destructor identities reconciled.
Clearance: `tools/link_check.py Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00406B1D.cpp`
reports: LINKS (0 -> 28 bytes). Exact 1/1 byte match preserved.
Census confirmation: awaiting the next census.
Same cause, more units (2026-10-26, K5): nine more `StlSweepR3Rva<rva>.cpp` units that instantiated
`stable_sort` over a 1-byte record only to emit the 28 B non-virtual `??_G...Record` now use a plain
delete site (the `StlSweepR3Rva0046AA69.cpp` form), keeping each file's existing destructor
`/alternatename` and retiring its three `#pragma optimize` lines: 005CE7CE, 005E96DC, 00406CB7,
0044BE1D, 00482A4D, 0052BBD7, 00587752, 005DA663, 0042D4EB. 0042D4EB's binding also named a
placeholder since renamed (`??1Rva005794ED@@UAE@XZ` -> `??1EndTurnButtonImpl@StrategicHUD@@QAE@XZ`)
and now names the current symbol; that record is very likely `StrategicHUD::EndTurnButtonImpl` itself
(naming-lane follow-up, would drop the alternatename). Each 1/1 exact and `link_check` LINKS (0 -> 28 B).
Still open in this family, no hatch added: 00551B02, 005838DC and 005AFEDB have no destructor binding.
Retail calls rowed virtual destructors (`??1GameSpyBuddyMessageQueue@@UAE@XZ` 0x00551988,
`??1Rva005838B5@@UAE@XZ` 0x005838F8, `??1Rva005AFE3F@@UAE@XZ` 0x005AFE3F), so these rows are probably
those classes' virtual `??_G...@@UAEPAXI@Z` (same 28 B shape); next check: each class's vtable slot 0,
then rename the row and emit it from the class's own unit.

Same shape, still open (K10, 2026-10-26, inspected revision 7790bd44c7):
`StlSweepR3Rva0052BBD7.cpp` (row `??_GRva0052BBD7Record@@QAEPAXI@Z` 0x0052BBD7, 28 B) instantiates
`stable_sort` and fails on unresolved `Rva0052BBD7Record` copy ctor, `operator=` and `operator<`;
its dtor is already bound by an `/alternatename` to `?rva004E366E@Rva004E366E@@QAEXXZ` (0x004E366E,
"vector erase plus free clear", rowed as a plain method). Trial: replacing the instantiation with an
inline `delete p` helper emits no `??_G` (1/1 FAIL, symbol not found), reverted. The LINK-043 route
(non-inline anchor plus `/alternatename`) adds hatches, so it was not repeated. Hatch-free route:
name 0x004E366E as the real class's destructor (`??1<Class>`) and give the record that class, then
find what emits a non-virtual `??_G` without an invented anchor. Status for this unit: Open.

#### Six deleting-destructor instantiations, 2026-10-26

Evidence / affected units: `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva{00551B02,005838DC,005AFEDB,005CE7CE,005DA663,005E96DC}.cpp`, one existing 28-byte scalar deleting-destructor row each. Current retail disassembly and emitted-helper references are in the [worker handoff](../../build/link-report.md) and `build/w4-link-20261026/evidence.log`; ordinary previews use published index `d1f046749a`, rules `retail-truth-4`.

Completed: replace each unrelated `stable_sort` instantiation with scalar `_STL::_Destroy<Record>`. MSVC emits the same deleting destructor from the existing declared destructor. No handwritten function, anchor or new alias is needed. The unused min/max adapters and optimization pragmas disappear. All six rows pass `build.sh`, declaration, EH and shadow data checks. Units `005CE7CE`, `005DA663` and `005E96DC` now report LINKS in the combined current-input preview. Their existing bindings to `FamilyDeletingDtors_muse-06-5E8EA9.cpp` (005E8F6A), `Disp0DwordImmSetters.cpp` (005970E6) and `Rva005E9625Dtor.cpp` (005E9625) are unchanged; all three providers remain LINKS.

Remaining / next check: `00551B02`, `005838DC` and `005AFEDB` each retain only their record destructor as unresolved. Their retail calls already target rowed destructors: `GameSpyBuddyMessageQueue` at 00551988 (126 B, BuddyThread_Unresolved.cpp), `Rva005838B5` at 005838F8 (59 B, Rva00587F69Dtor.cpp), and `Rva005AFE3F` at 005AFE3F (71 B, Rva005AFE3FDtor.cpp). Reconcile the deleting-destructor row's class and virtual contract with its provider rather than adding an alias. The GameSpy class has a real-name lead; the other application class names remain unknown. Row renames were unavailable to this worker. BuddyThread_Unresolved.cpp retains its pre-existing deque blockers; the other two provider units remain LINKS.

Update 2026-10-28: `tu_skeleton.py --merge` moved the `005AFEDB` record destructor (from `StlSweepR3Rva005AFEDB.cpp`) and its retail callee `??1Rva005AFE3F` at 005AFE3F (from `Rva005AFE3FDtor.cpp`) into the approved TU `Code/GameEngine/Source/GameClient/GUI/ChatWindowsInGame.cpp`; both rows byte-verify there. The class/contract reconciliation above is still open; census confirmation of the merged unit is pending.

Clearance: `005CE7CE`, `005DA663` and `005E96DC` are cleared in ordinary-preview scope; census confirmation pending. The other three units remain blocked. Across the full paired worker scope, no previously clean unit becomes blocked and no compared unit gains a named blocker; raw before/after outputs are retained with the handoff. This does not clear the broader identity or whole-game linking scope.
