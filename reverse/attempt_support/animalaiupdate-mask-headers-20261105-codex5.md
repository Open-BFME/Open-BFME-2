# AnimalAIUpdate mask headers and consolidation prerequisites

Inspected revision: `ab15df8c55`, 2026-11-05; worker
`yasinschroeder-codex5`.

## Applied prerequisite repair

`Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AnimalAIUpdate.cpp`
now includes the canonical `BfmeFixedStorage0004543D.h` and
`Rva00045411BitSet.h` instead of declaring private 28-byte mask classes.
Neither private storage member was accessed. No field-token rewrite is needed,
so the automatic adoption's ambiguous `bytes`/`m_bits` diagnostics do not apply
to this manual substitution. The second header also supplies its established
nonthrowing constructor contract; the resulting bytes and EH graph verify.

Verification of the final source:

- `./build.sh <source>`: 15/15 matched; 28 string literals and one float
  literal verified. Existing funclet labels are resolved through parent EH data.
- `find_declared_unmatched.py <source>`: all definitions already matched.
- `header_adopt_lane.py accept --class BfmeFixedStorage0004543D <source>` and
  `accept --class Rva00045411BitSet <source>`: PASS; each owning verdict
  retired one row from `reverse/header_queue.tsv`.
- `eh_verify.py <source>`: three EH-bearing rows, all EXACT, no baseline debt.
- `link_check.py <source>`: LINKS, 3,167 -> 3,167 authored bytes against the
  census at `c95fcfcfcd` (2026-11-05 05:17). This is a preview preserving the
  existing census result, not a new census or real-link measurement.

## Merge trial and next work

The consolidation planner surveyed the AIUpdate directory before the trial.
`tu_skeleton.py --merge <source> --dry-run` rebuilt the stale TU map in memory,
found 22 approved rows, and accepted no donors. It wrote no source or ledger
changes. The rejected donors were:

- `AnimalAIUpdateMakeStateMachine.cpp`: `StateMachine` redefinition between
  the seed's view and `StateMachineClass.h` reached through the donor's headers.
- `AnimalAIUpdateCtor.cpp`: the chosen private class declaration lacks
  `getModuleNameKey`; the constructor additionally uses explicit vtable-storage
  members that the canonical AIUpdateInterface header does not expose.
- `AnimalAIUpdateXfer.cpp`: byte mismatch under the merged composition.

`Disp32FirstChaseGetters.cpp` and `Rva0026E836Derived.cpp` remain mixed sources.
The two mask adoptions above do not settle these other class contracts or claim
that a merge is now possible. Next reconcile the seed's StateMachine and
AIUpdateInterface/AnimalAIUpdate views with the existing headers, checking
the update receiver's secondary-interface ABI and complete EH graph before
retrying composition. The existing header queue retains those prerequisites.
No source paths moved and no aliases, pins, flags or shared headers changed.
