### LINK-021: W3DRopeDraw ctor linked against non-retail headers emitting conflicting COMDATs and unresolved references
Status: Cleared. Updated: 2026-10-26; inspected revision: 692d9a3158.
Evidence / affected units: `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDrawCtor.cpp`,
`reverse/link_status.csv` reported 3 blockers (1 unresolved, 2 COMDAT collisions).
Completed: Replaced non-retail BFME1 sweep headers with verified minimal class kit matching `W3DRopeDrawDtor.cpp`.
Remaining / next check: None.
Clearance: `tools/link_check.py Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDrawCtor.cpp`
reports: LINKS (0 -> 164 bytes). Exact 1/1 byte match preserved.
Census confirmation: awaiting the next census.


2026-11-17 scope follow-up at `768d86245d4`: the historical minimal-kit census clearance above does not clear the current runtime table. Primary `0x007CBD60` has the correct 248-byte extent but twelve wrong override providers; its constructor/destructor still use active vector storage incompatible with the registered header's pointer-array representation. No repeated unchanged adoption trial or production change. Coherent shared container/provider reconciliation remains required before the owning bridge pass test. [Current cohort handoff](../../reverse/attempt_support/rope-native-vtable-prerequisites-20261117-root20.md).

The isolated declaration prerequisite now fixes Snapshot name/transfer slots 2/3 using their existing providers in all three emitting views. Normal 44/44 five-source rows and three EXACT EH graphs pass; both local 62-slot copies reduce differences 12 to 10. Every other runtime section/binding agrees, with the same SafeSEH handler after COFF symbol-index renumbering. No body, row, shared header, active container or bridge queue changed. Full table recovery still awaits the remaining prerequisites in the linked handoff; no runtime or bridge-retirement clearance is claimed.
