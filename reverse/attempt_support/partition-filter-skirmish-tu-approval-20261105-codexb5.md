# PartitionFilterSkirmishAI constructor: TU approval blocked

Inspected revision: `06b6310955`, 2026-11-05. This is a placement
investigation; the existing matched constructor is not a regression.

The picker served the proposed unit
`Code/GameEngine/Source/GameLogic/AI/PartitionFilterSkirmishAI.cpp` for
`??0PartitionFilterSkirmishAI@@QAE@PAVObject@@PAVSkirmishAI@@@Z`,
RVA `0x002FD71E`, 29 bytes. The source actually owning it is
`Code/GameEngine/Source/GameLogic/AI/PartitionFilterCtorCopies.cpp`.

Current-input checks:

- `check_csv.py` passes.
- `find_declared_unmatched.py` on the actual owner reports all defined
  functions already matched (27 matched rows; anchor helpers are marked
  absent from retail).
- `./build.sh` on the owner passes 27/27 functions, plus string, float and
  import reference checks.
- `tu_skeleton.py --plan` on the proposed unit rebuilds the stale map in
  memory and reports zero approved rows and zero donors.
- `name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/AI/`
  produces a complete report with no missing inputs. Its file packet leaves
  this constructor unresolved, without an alternative placement or anchor.
- Searches for `PartitionFilterSkirmishAI` in the local Zero Hour reference
  and BFME 1 game sources find no definition. The planner path catalogues,
  retail string-xref register and WorldBuilder name leads have no hit for
  that token.

The current committed map's `N` assignment is a naming hint. The function
already has a real class/constructor name; renaming a placeholder cannot
unlock this particular row. Its only other same-class row, `allow` at
`0x00261535`, has a separate proposed Object-directory TU, far from this
out-of-line constructor copy. Neither a shared class name nor the stored
vftable proves which retail TU emitted the constructor.

Next useful work requires an independently checkable placement anchor or a
validated layout signal for this constructor's host TU. Do not create the
proposed one-function file or move the row on naming evidence alone. No
source, map, debt register or naming record was changed by this attempt.
