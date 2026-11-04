# PlayerAITypeSet allocation donor prerequisite (2026-11-04)

Inspected revision: `65918d10b6`. Prerequisite repair: `78af254464`.
Scope: `PlayerAITypeSet.cpp` and the approved donor
`stlport_vector_record_2154f3_allocate_copy.cpp`.

The destination's opaque 16-byte `BfmeVectorRecord0002154F3` view did not
emit the allocation donor's implicit owning destructor. Replacing it with the
donor's existing AsciiString plus vector<AsciiString> view preserves all 16
destination rows. This is a reconciliation of existing recovered views, not
new evidence for a retail class name or source-level inheritance.

Declaration-only specializations also suppressed the donor's primary
`__copy_backward`, range `_Destroy` (two declarations) and `__copy` bodies.
Removing the first three changes the allocation donor's merge refusal from
`bytes` to a link refusal naming the missing `__copy` provider; removing the
fourth clears that refusal. The final `tu_skeleton.py --merge ... --dry-run`
accepts the destination and allocation donor, 33 rows, with its link guard.
The parser still fails on `BfmeItemERE` declaration order, and the W4
fill-insert donor still fails bytes. The two mixed donors remain outside this
merge; see the earlier consolidation handoff.

Checks on the prerequisite repair:

- `./build.sh PlayerAITypeSet.cpp`: 16/16 exact, one data row and three funclet
  pins verified; the commit hook also verifies all three EH graphs EXACT.
- `find_declared_unmatched.py`: all defined functions already matched.
- Staged code identity: zero new findings; staged shadow data: zero findings;
  staged TU ownership passed. The normal pre-commit hook passed.
- Paired current-object link preview: both units LINKS, preserving 624 and
  690 authored bytes. Index: `f12552d0a7`, census 2026-11-04 20:47.
  These previews do not change census headline figures.
- The consolidation snapshot was regenerated after the repair and passed
  `name_lane.py consolidate --check build/consolidation` before application.

Application was blocked before any writes by another worker's claim on
`0x0007FAB3`, the allocation donor's existing ICF-folded vector-base destructor.
The merge tool released the acquired scope. No donor was removed and no
ledger or protected-register debt was retired. The next step is to apply the
already verified allocation-donor merge after that claim becomes available,
then build the resulting TU and audit path consumers and provider bindings.
