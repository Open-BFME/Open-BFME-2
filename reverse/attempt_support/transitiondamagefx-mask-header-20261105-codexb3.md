# TransitionDamageFX mask header adoption

Inspected `528dcedaf3ed60e814158798260e05670a75d4ac`, 2026-11-05.
Scope: the claimed TransitionDamageFX TU and its four unmixed donors.

The supported planner was run under
`Code/GameEngine/Source/GameLogic/Object/Damage/`, with its report in
`build/consolidation/transitiondamagefx`. The current in-memory TU plan has
75 approved rows, five files and seven excluded mixed donors. The supported
merge dry-run still accepts no donors: the module-data destructor and map-load
donors have declaration conflicts, the erase helper loses bytes under the
seed's flags, and the behavior destructor would select the wrong
DamageModule destructor. The detailed prior boundaries remain in
[the template-contract handoff](transitiondamagefx-template-contracts-20261105.md).
No source moves or TU-map changes are retained.

The map-load donor now includes the existing canonical
`BfmeFixedStorage0004543D.h` instead of declaring a private class. Retail's
seven-word stack initialization remains an unsigned array, zeroed in place,
with bits 7 and 60 set before passing its address to the existing filter
constructor. The canonical class has no default constructor; this preserves
the existing instruction sequence without introducing a constructor call or
changing that shared header. This is a storage view, not a recovered mask name.

Verification:

- `./build.sh` passes all five source rows, both parent-bound unwind labels
  and the float-reference check. Declared-unmatched checks pass before and
  after the edit.
- `header_adopt_lane.py accept --class BfmeFixedStorage0004543D` passes and
  retires exactly this source's header-queue row through the owning tool.
- Original and changed texts were independently compiled with
  `tu_skeleton.Verifier`, which keeps scratch objects outside `build/match`.
  All five rows match in each. `class_cleanup.runtime_graph` and
  `same_runtime` confirm identical non-debug COFF bytes, relocation bindings,
  COMDAT policies, weak bindings and all 14 external definitions.
- `link_check.py` remains LINKS for 339 authored bytes against the
  2026-11-05 05:17 census at `c95fcfcfcd`. No census or real-link gain is claimed.
- Scoped register searches show no data/identity keys on the changed source;
  no such debt is retired. The other two header debts belong to the seed and
  remain. No path-consumer audit is needed because no source path changes.

The automatic adoption transform declined its include scan on a trigraph in
STLport's unused platform configuration header. The authored source edit
passes the normal byte verifier and authoritative acceptance guard; no gate
or reference file was changed.

Next: the merge still needs the map-load register allocation and destructor
contracts described in the prior handoff reconciled. Header adoption alone
does not satisfy the TU-consolidation pass test.
