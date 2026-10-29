# QuadStrip2D consolidation audit, 2026-10-29

## Scope and evidence

Prerequisite commit `2fa85235e6` replaces the seed's private STLport vector
template with `<vector>`, retaining a declaration of the existing BfmeE12 swap
specialization. All three seed rows remain exact, with a current preview of
LINKS 215 -> 215 authored bytes.

`tools/tu_skeleton.py --merge Code/GameEngine/Source/Common/QuadStrip2D.cpp`
then absorbs `Code/GameEngine/Source/Common/Rva005388ABCtor.cpp` and repoints its
23-byte row at `0x005388AB`. Four matched rows now share the destination, and
one source file is removed. This is consolidation, not newly recovered bytes
or a new linker census result. The placeholder constructor name is unchanged.

The merge tool re-derived the current map in memory because the committed map
is stale. The destination is an approved **provisional** TU grouping; its path
is not a newly proved original filename. The committed `tu_map.csv` change is
only the absorbed row's source-column repoint, not a regenerated map.

The supported consolidation planner ran before the pass and again after the
merge. Its final `--check build/consolidation` passed. Its routing warnings
remain investigation hints; the merge tool's current approvals govern the move.

## Verification and registers

- `./build.sh` verifies 4/4 rows (238 authored bytes), one complete emitted
  STLport constructor fold and its resolved callees, with no unverified
  string, float or import references. `find_declared_unmatched.py` is clean.
- `check_csv.py` passes: 99,005 function rows, 9,420 symbol rows and 2,235 data
  rows. The new ledger source is tracked. `tu_ownership.py --staged` passes.
- `code_identity_gate.py --staged`: four rows, zero new findings, shadow mode.
  `data_check.py --staged`: zero findings, zero outside the baseline.
- Neither the removed source nor the destination has a header-queue,
  Microsoft-header-queue, identity, data, hatch or flag-override register key
  requiring transfer. The merge's owning report refresh made no queue change.
  A fresh Microsoft-header scan finds zero local Microsoft declarations.
- The merger's LinkGuard accepts the composition against the authenticated
  2026-10-29 15:08 census index at `85f6b7f40c`, preserving the census-linked
  seed and constructor, selected COMDATs and outside consumers. A strict
  current-object receipt followed by the normal preview reports LINKS for all
  238 bytes. Before absorption the seed and constructor previewed LINKS for
  215 and 23 bytes respectively, so their combined coverage is preserved.

## Tooling compatibility audit

Fetched origin/master through `a3d754a035` immediately before the audit. Reviewed
the complete outgoing range through `2fa85235e6` and merge `1966efeff8`. No earlier
outgoing commit moves a source path. The two-dot diff also shows concurrent
upstream work, which is absent from this branch's outgoing commit range; the
upstream side changes neither merge source nor Region2D.h.

Searched the removed full path and basename across `tools/`, `.githooks/`,
`.github/`, Code, shims, docs and reverse records, including build consumers,
includes, path-keyed registers and fold proofs. There is no active include,
tooling or configuration consumer to repoint. Functions and TU-map sources were
repointed by the merge tool; no body-owner, data-ledger or doxygen entry names
the donor. Intentional old mentions remain in the census's `link_status.csv`,
the historical helper-selection handoff, the merge provenance comment and the
river constructor's source-evidence comment. They are not build inputs.

## Remaining prerequisites

The other donors remain unchanged. The assignment and vector-copy files still
redefine STLport templates. Transform composition also encounters duplicate
placement-new definitions in the BFME 1 WWLib header. Parse needs a reconciled
QuadStrip2D view and constructor declaration. W3DAnimationInfo vector insertion
changes bytes when composed; its existing element-family identity
and COMDAT debt are retained. Mixed files remain outside this merge. Reconcile
these prerequisites in separately verified commits before another merge.
