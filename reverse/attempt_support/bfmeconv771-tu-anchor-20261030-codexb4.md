# BfmeConv771 TU-approval investigation

Inspected tree: 9c59d3c608, after rebasing onto fca62453f4. Claimed the
picker's proposed destination Common/BfmeThingDSF.cpp and the actual source
Code/GameEngine/Source/Common/BfmeConv771.cpp. No source or map edit was made.

The default picker serves the single proposed row at RVA 0x00270221, size 19,
as TU approval. BfmeThingDSF.cpp does not exist: the row is already matched in
BfmeConv771.cpp. This is placeholder cleanup, not a lost-row regression.
`tu_skeleton.py --plan Code/GameEngine/Source/Common/BfmeThingDSF.cpp` rebuilds
the map in memory and returns zero approved rows/donors. The committed map's
N-only proposal is not authority to move it.

The supported Common/ consolidation planner and its currency check pass. Its
source packet leaves all three BfmeConv771 rows unresolved, with no target-path
evidence or alternatives. It also flags pragma context and the existing hatch
register. The proposed destination is not an original retail path finding.

Target facts and current reconstruction:

- 0x00270221 (19 bytes) destroys four twelve-byte elements at this+0x60
  through the vector destructor iterator. The separate Rva002701F4Ctor.cpp
  reconstructs two Matrix3D members followed by four Coord3D members; the
  existing DrawableDestructor.cpp view calls this helper for its +0x3AC
  member. These facts constrain layout and behavior, not the original name.
- 0x0055A614 (19 bytes) invokes the same iterator for four twelve-byte
  elements at this+8. It lies far from the picker row and cannot borrow its
  possible Drawable association as TU evidence.
- 0x00270234 (44 bytes) walks three null-terminated lists at +0x14C,
  calling slot +0x20 on each element. Its WorldBuilder lead is PIN_ONLY,
  score 1, and itself spells rva00270234. It supplies no canonical name.

Donor facts: reference/open-bfme-1 is pinned at
1d5131d3f193cdf01a99da66ccd6828639585650. Its corresponding BfmeConv771.cpp
retains the same BfmeThingDSF/bfmeGoDSF placeholders. The cached same-body
placement from BFME 1 0x00410B40 has no strings. A same-body placement with an
agent-chosen donor name is not canonical BFME 2 identity or source-path proof.
No target string/name-basis record supplies the missing name for these rows.

Checks: find_declared_unmatched reports all definitions matched; ./build.sh
Code/GameEngine/Source/Common/BfmeConv771.cpp passes 3/3 functions, source
claims, string, float and import checks. Existing coverage is preserved.

Deferred: establish the actual Drawable member/helper identity from stronger
target or independent source evidence, then use the naming tool and re-run
the TU approval pass test. The unrelated +8 helper needs its own owner proof.
Do not rename the donor placeholders into plausible names, move the mixed
source to the N-only destination, or call these already-covered bodies new
matches. No source-file, TU-approval, debt or linking gain is claimed.
