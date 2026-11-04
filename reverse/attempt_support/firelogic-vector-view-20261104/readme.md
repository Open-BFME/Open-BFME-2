# Fire-logic pending-heat vector view

Inspected base: `7c51831185`, 2026-11-04.

The consolidation picker claimed FireLogicSystem.cpp and four clean donors.
`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Map/FireLogicSystem.cpp
--dry-run` accepted none: all four donors reported `bytes`.

A separate prerequisite was concrete: `tu_views.py ... --dry-run` refused
Rva00287F76Element because the owner's `unsigned short m_value` at +4..+6
conflicted with the vector fragment's `int b` at +4..+8. The owning source's
spread pass stores a cell pointer and unsigned-short heat, and its rowed
Rva002861B0Copy copies one dword and one word. Both views have eight-byte
stride. Align the fragment with that existing view; no original type name is
claimed and no donor layout is imported.

Verification after the edit:

- `./build.sh Code/Libraries/Source/WWVegas/WWLib/stlport_vector_rva00287f76_overflow.cpp`:
  2/2 matched (184-byte overflow and 55-byte push_back); reference checks pass.
- `find_declared_unmatched.py` on that source: all definitions matched.
- `tu_views.py ... --dry-run`: a compatible plan for both views, no overlap
  conflict; its proposed explicit tail padding is unnecessary for this edit.
- `link_check.py` on the fragment: LINKS, 239 -> 239 bytes against the
  2026-11-04 07:28 index at a62ac1c10b. This is a local preview, no census gain.

Next: retry the guarded merge with the views compatible. The initial `bytes`
refusals remain unclassified; this prerequisite alone does not claim a merge.
