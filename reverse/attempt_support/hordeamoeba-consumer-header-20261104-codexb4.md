# HordeMeleeAmoeba consumer header adoption

Inspected revision: `9dce5d53b922a735659192f823030fd78fd89e1f`.
Scope: the main `HordeContain/HordeMeleeAmoeba.cpp` consumer and
`Contain/HordeMeleeAmoebaAttackUnit.cpp`. The canonical header is unchanged.

Removed both private HordeMeleeAmoeba class bodies. AttackUnit now enables
STLport for the canonical vector declaration. The main consumer uses the
canonical `slots`, `flag14`, `held` and `other` members, casting storage to its
existing target-backed entry, held-object and data views. A compile-time size
check ties the entry view to the canonical 60-byte record. The native layout
evidence remains in `hordeamoeba-canonical-qc10-20261031/README.md`; this change
does not identify the original record type or unknown virtual providers.

Verification:

- `find_declared_unmatched.py` passes both changed sources before and after.
- `./build.sh` preserves all five main-consumer bodies and both AttackUnit
  bodies, including string, float and import reference checks.
- `header_adopt_lane.py accept --class HordeMeleeAmoeba` passes each source
  and retires exactly their two rows from `reverse/header_queue.tsv`.
- `link_check.py` checks current cached compilation dependencies and reports
  both units LINKS, preserving 2,772 and 96 census-linked bytes respectively.
  Its census reference is 2026-11-04 12:23 at `40fe1783d7`. This is a preview,
  not a new linking or ownership measurement.

The other three header-queue candidates remain unchanged. Automatic adoption
encounters the seed's `vector<BfmeE16>`/`vector<BfmePod60>` identity difference
and the deleting/destructor donors' STLport/header-surface incompatibilities.
The existing LINK-201 seed-lifetime and selected-vtable prerequisites remain;
the prior recorded EmitVtableTag/full-header failure was not retried. No TU
merge, alias removal or family-link clearance is claimed.
