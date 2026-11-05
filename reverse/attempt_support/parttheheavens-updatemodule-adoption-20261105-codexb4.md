# PartTheHeavensUpdate: UpdateModule header prerequisite

Inspected revision: `85fc53335c`, 2026-11-05, seat
`yasinschroeder-codexb4`. No source path or ledger ownership changes.

## Completed

`PartTheHeavensUpdateRebuild.cpp` now includes the canonical
`GameLogic/Module/UpdateModule.h` instead of its explicit-vptr private base.
The existing module-data pointer is cast to the helper's local descriptor view;
the inherited object pointer remains at +8. No canonical header was changed.

`header_adopt_lane.py accept --class UpdateModule` passes for this helper and
the already-adopted `PartTheHeavensUpdate.cpp`, retiring exactly their two
`reverse/header_queue.tsv` rows through the owning tool. The constructor's
queue entry remains.

Verification:

- `./build.sh PartTheHeavensUpdate.cpp`: 14/14 rows exact.
- `./build.sh PartTheHeavensUpdateRebuild.cpp`: 3/3 rows exact, including
  the compiler-renumbered funclet verified through its parent's EH graph.
- `find_declared_unmatched.py` reports no unmatched definitions in the helper
  or destination TU.
- `data_check.py --enforce` on the helper: zero findings.
- `eh_verify.py` on the helper: one EH graph EXACT, none missing/nonexact.
- Ordinary `link_check.py` against census `c95fcfcfcd`, 2026-11-05 05:17:
  destination 427 -> 427 authored bytes, helper 226 -> 226; both LINKS.
  This is a local prediction, not a new census or real-link measurement.

## Consolidation remains blocked

The supported evidence planner surveyed the Update subsystem (945 sources,
135 groups); the selected TU's donors have macro/include context and private
class/flag prerequisites. Current `tu_skeleton.py --merge ... --dry-run`
accepts no donor before or after this repair. Its remaining `adopt_first`
list has narrowed to `PartTheHeavensUpdateCtor.cpp` alone.

- Constructor: its explicit `m_vtable`, secondary table fields and `m_24`
  initialization do not compile against the seed's real virtual base/view.
- Angle helper (`Rva004AC9FA.cpp`): its registered `-O1` override is carried
  into merge trials; PoolKey loses one row and Rebuild loses two under it.
  Its private PartTheHeavensUpdate and shadow views also conflict with the seed.
- Module-data destructor: merged bytes fail. The standalone destructor uses
  `novtable` and inline vector cleanup; the seed's constructor uses a different
  curve spelling and a declaration-only vector destructor. Both environments
  need reconciliation without changing external consumers' bindings.
- `tu_views.py` cannot share PartTheHeavensUpdate (a donor places data under
  the canonical bases), or ModuleData (different `novtable` attributes).
  Sharing Shadow was automatically reverted because AsciiString/Coord3D
  definitions were absent in the angle helper. No failed source is retained.

Next: reconstruct the constructor against the canonical base while preserving
its retail initialization order, and reconcile the angle helper's class and
compiler environment. Re-run the merge tool after a verified prerequisite
repair; no source-count reduction or broader link closure is claimed.

The module-data destructor's link-wide alternatename is untouched. Debt and
data-identity registers have no keys for either changed/adopted source beyond
the two header rows retired above. The pre-existing AI edits remain outside
this change.
