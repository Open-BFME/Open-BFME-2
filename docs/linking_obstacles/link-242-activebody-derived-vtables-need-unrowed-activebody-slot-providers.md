### LINK-242: ActiveBody-derived vtables need unrowed ActiveBody slot providers
Status: Blocked. Updated: 2026-11-04; inspected revision: 49dfd905bf.
Evidence / affected units: `Code/GameEngine/Source/GameLogic/Object/Body/PorcupineFormationBody.cpp`
defines PorcupineFormationBodyModule's constructor, so it emits the class vtables, and their
inherited ActiveBody slots reference three symbols nothing defines:
`?GetSnapshotName@ActiveBody@@UBEPBDXZ` (retail slot 2 of 0x00C5B038 is 0x004BF88D, rowed as the
non-virtual `?name@ActiveBody@@QBEPBDXZ`), `?Rva004BE67E@ActiveBody@@UBE?AVAsciiString@@XZ`
(0x004BE67E is rowed as `?Rva004BE67E@DetachableRiderBody@@UBE?AVAsciiString@@XZ`) and
`?applyDamageScalar@ActiveBody@@UAEXM@Z` (declared in `GameLogic/Module/ActiveBody.h`, no row).
`tu_skeleton.py --merge ... --dry-run` (index 2026-11-04 16:16 at 2f0cb97f52) compiles and
byte-matches all three donors (PorcupineFormationBodyModuleSlots.cpp,
...ModuleRva004C21A9.cpp, ...ModuleSlots_AttemptDamage.cpp) and rejects each only because those
census-linked donors would join an object with these unresolved references. The same gap applies
to any unit that emits an ActiveBody-derived vtable.
Completed: the TU's PorcupineFormationBodyModule and its ModuleData views were reconciled with the
donors (two commits ending at 49dfd905bf); every row still byte-matches.
Remaining / next check: give the three slots their providers without a second name on one address:
rename the 0x004BF88D row to the virtual GetSnapshotName (its existing non-virtual `name()` callers
need a qualified-call spelling), decide whether 0x004BE67E's owner is ActiveBody (the body-interface
table 0x00C5B5B0 is not in `vftable_map.py`'s output), and find applyDamageScalar's address. Then
re-run the dry run; the merge removes three files.
Clearance: pending.
Census confirmation: not claimed.
