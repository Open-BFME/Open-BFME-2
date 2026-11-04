# BfmeB1137 MaterialPassClass adoption

Inspected revision: `05c96d387f`. Scope: `BfmeConv1137Dtor.cpp` and
`Gen006E2310Ctor.cpp` under `Code/GameEngine/Source/Common/`.

The consolidation dry run rejected both donors against `BfmeB1137.cpp` because
their private class views disagree. This prerequisite repair replaces both
private MaterialPassClass declarations with the existing canonical header.
Its 0x38-byte base replaces the destructor donor's four-byte base plus 0x54
bytes of padding; 0x20 bytes of derived padding keep the four texture holders
at +0x58, +0x5C, +0x60 and +0x64. The constructor donor already used a
0x38-byte base.

Target facts: the canonical header documents the four-slot MaterialPassClass
table. The derived table is RVA 0x007C8198, size 16 in `data_ledger.csv`.
Both producers declare the existing Install_Materials and UnInstall_Materials
overrides, preserving their inherited slots and agreeing on the derived table.
No new name, layout field, pin or alias is introduced.

Validation:

- `./build.sh Code/GameEngine/Source/Common/BfmeConv1137Dtor.cpp`: 8/8 rows
  match, including the four parent-EH-verified funclets.
- `./build.sh Code/GameEngine/Source/Common/Gen006E2310Ctor.cpp`: 5/5 rows
  match, including two parent-EH-verified funclets.
- `header_adopt_lane.py accept --class MaterialPassClass` on both sources
  together: PASS/PASS, two header-queue rows retired by the owning tool.
  Acceptance includes the cohort's current-object link prediction. The dtor
  alone failed against the constructor's old table; the coherent pair passes.
- `find_declared_unmatched.py` on both sources: all defined functions matched.

The census is unchanged. The original consolidation still requires reconciling
the destination's BfmeB1137 view and the constructor's Rva009519B base view.
