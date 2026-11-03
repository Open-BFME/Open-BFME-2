### LINK-021: W3DRopeDraw ctor linked against non-retail headers emitting conflicting COMDATs and unresolved references
Status: Cleared. Updated: 2026-10-26; inspected revision: 692d9a3158.
Evidence / affected units: `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDrawCtor.cpp`,
`reverse/link_status.csv` reported 3 blockers (1 unresolved, 2 COMDAT collisions).
Completed: Replaced non-retail BFME1 sweep headers with verified minimal class kit matching `W3DRopeDrawDtor.cpp`.
Remaining / next check: None.
Clearance: `tools/link_check.py Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDrawCtor.cpp`
reports: LINKS (0 -> 164 bytes). Exact 1/1 byte match preserved.
Census confirmation: awaiting the next census.
