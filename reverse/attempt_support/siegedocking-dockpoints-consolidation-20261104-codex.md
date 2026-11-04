# SiegeDockingBehavior dock-point consolidation, 2026-11-04

Scope: declaration repair `50b940b9da`, followed by the mechanical absorption of
`SiegeDockingBehaviorDockPoints.cpp` into
`Code/GameEngine/Source/GameLogic/Object/Behavior/SiegeDockingBehavior.cpp`.

## Evidence and result

- The supported consolidation planner was run under the Behavior directory and
  its snapshot passed `name_lane.py consolidate --check build/consolidation`.
  The catalogue leaves the accessor placement unresolved; it is not approval.
  The current TU mapper approves both RVAs, 0x004598F2 and 0x0045992F, for this
  provisional TU. Grouping approval does not establish the original file name.
- Before reconciliation, the merge dry-run accepted no donor. Both accessors
  lacked declarations in the seed class. They now use its existing shared view,
  inherited Object accessor, and vector at +0x24; the two 61-byte retail bodies
  still match. No virtual slots were added.
- `tu_skeleton.py --merge` accepted the seed and DockPoints donor, preserved all
  10 matched rows, and passed the census link guard. The tool repointed exactly
  two source cells in functions.csv and two in tu_map.csv. The map was not
  regenerated. Net source-file change: -1.
- Final `./build.sh` passed 10/10, including three EH labels validated through
  parent metadata. `find_declared_unmatched.py` and `check_csv.py` passed.
- Link preview against the 2026-11-04 17:56 census (8c757ea0db): main TU LINKS,
  253 -> 375 authored bytes; destructor unit LINKS, 129 -> 129. The 122 bytes
  were already owned by the absorbed donor: this is consolidation, not a claim
  of newly linked bytes or a new census.
- EH data verifier: EXACT 2/2, with zero missing objects or baseline entries.
- Data identity check: zero findings; converged check: zero second names and
  zero unjudged rows. Ownership check reports only diagnostic B2 (a three-float
  point shares a layout fingerprint with BfmeShadowVectorPrefix).

## Consolidation and tooling audit

Audited this session's source-path move, DockPoints -> the approved TU,
including the prerequisite declaration change already handed to the publisher. Searched the removed basename
across tools/, .githooks/, .github/, Code/, docs/, reverse/, build.sh and
.gitmodules. There are no active consumers to update. Remaining occurrences are
its historical census entry in reverse/link_status.csv and the merge provenance
comment. Those retain their original meaning. There are no donor references in
symbols.csv fold proofs, body_owners.csv, data_rows.csv, data_ledger.csv or the
doxygen source list. Both source rows now name the surviving owner.

No gate/data/identity/header-queue debt keys name the absorbed donor or the TU.
No debt was retired. The header queue has no affected entries; the Microsoft
header queue was refreshed with its owning scanner (zero local Microsoft
names). No hatch was removed or transferred. The merger's link guard checked
the combined object against the existing bindings; the destructor's link
preview remains clean. Existing LINK-168 and LINK-236 were reviewed; their
remaining obstacles are unchanged by this accessor-only move.

## Remaining consolidation prerequisites

Six donors remain, with no changes to their source: InitializeBones has an
allocator-specialization conflict; Reserve has incompatible coordinate views;
Refresh redefines NameKeyGenerator; CanDock lacks the seed's interface method;
Xfer instantiates its allocator before its specialization; Dtor loses bytes
when composed with the seed. Reconcile each donor in a separate verified commit
before another merge. The mixed ConstIntGetters4 and LoadPostProcess files were
not split. Existing meaningful accessor locals and parameters were retained.
