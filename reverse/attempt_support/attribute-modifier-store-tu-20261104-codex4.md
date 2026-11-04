# AttributeModifierStore TU reconciliation, 2026-11-04

Inspected base: `0d644f1776`; prerequisites: `2ce81cc99f`, `adff4f8c3d`.
Scope: `Code/GameEngine/Source/Common/AttributeModifierStore.cpp` and the
three clean donors selected by next_work (Rva00214ACCPush, Rva0022CA95Dtor,
StlSweepR3Rva00214B22). Existing attempts for this TU were read first.

## Completed and verified

- Rva0022CA95Dtor now uses the canonical SubsystemInterface header with all
  fourteen inherited slots enabled, avoiding the shim redefinition.
- Its two header members use the constructor's existing BfmeE16 spelling.
  This is a shared representation, not evidence of the application element
  type. Native deletion loops establish two pointer arrays at +0x0C/+0x18;
  the destructor reads those entries through ModifierStorePointerFields.
- Inline header teardown calls the established GameFree owner. The existing
  ICF-proven pointer-vector destructor row is still emitted explicitly for
  its unwind consumers; no pin, alias or row was removed or added.
- `./build.sh .../Rva0022CA95Dtor.cpp`: 6/6 rows exact; the parent graph
  places all three renumbered funclets exactly.
- `eh_verify.py .../Rva0022CA95Dtor.cpp`: EXACT 1/1.
- `find_declared_unmatched.py`: all definitions matched.
- `link_check.py .../Rva0022CA95Dtor.cpp`: LINKS, 220 -> 220 census bytes,
  using the published index at f6d845ecd4 (2026-11-04 13:15).
- Fresh tu_skeleton dry run accepts the seed and Rva0022CA95Dtor (39 rows).
  The actual merge wrote nothing: another worker holds 0x0007FAB3, a shared
  ICF row the tool claims before applying. Retry that same merge after this
  live claim clears; no further source reconciliation is needed for this donor.

## Remaining donors

Rva00214ACCPush still loses bytes when its push_back declaration changes
replaceModifier's inlining. StlSweepR3Rva00214B22 still reports C2908 because
its _Destroy<Rva00214ADC*> specialization follows the seed's instantiation.
Neither donor was changed. The three mixed donors remain outside this batch.
A primary-vector-header trial changed constructor bytes and was restored;
a per-member pointer cast changed the destructor's register allocation. A
whole-object pointer-fields view preserves all native bytes instead.

## Registers and publication

The current changes move no source or ledger row, so no register retirement
or path repointing is required. No donor keys exist in the data/identity/header
registers; the seed's NameKeyGenerator header debt remains. No hatches changed.
The accepted composition reports hatch-register transfer only for a future merge.
The source-path consumer audit found only the existing stlport_trial.csv
measurement and seed placeholder comments beyond automatically repointed ledgers;
a future applied merge must repeat the audit against its final outgoing range.
No new census, source-file reduction or linked-byte gain is claimed here.
