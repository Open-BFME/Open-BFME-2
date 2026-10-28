# Mesh material I/O seed cleanup, 2026-10-28

Base: `5ab8984c4c`. Scope: `Code/Libraries/Source/WWVegas/WW3D2/meshmdlio.cpp`.
This is hatch retirement and removal of an obsolete emission anchor. No TU
merge, source-file reduction, new match, new name or linked-byte gain is claimed.

## Selection and remaining consolidation prerequisites

The default picker claimed the meshmdlio TU and its 18 donor scopes. The fresh
`name_lane.py consolidate --under Code/Libraries/Source/WWVegas/WW3D2/` report
and `tu_skeleton.py --plan` describe 116 approved rows across 19 files, including
14 mixed files. The committed TU map was not changed. Original-path hints and
same-name donor paths do not establish BFME 2 source identity.

The earlier merge attempt in `reverse/re_attempts.log` accepted no donors and
reported the seed's StringClass Get_String guard plus donor view conflicts.
That unchanged merge attempt was not repeated. Current `tu_views.py --dry-run`
still reports incompatible MeshLoadContextClass bases, overlapping MeshMatDescClass
fields, MeshGeometryClass/MeshModelClass inheritance, MaterialInfoClass's shared
RefCount token, Vector3 class/struct mangling, VertexMaterialClass virtual slot
zero and BfmeHandleCX constructors. Reconcile these in independently verified
changes before composition. No generated reconciliation was applied.

## Change and provider evidence

Remove the disabled Zero Hour mesh-saving block, including its 22
`present-unmatched` annotations. It was inside `#if 0` and supplied no compiled
body. Remove `_bfmeMeshLoadContextInlineAnchor`, its friend declaration and its
inline-depth pragmas. The anchor had an absent-from-retail annotation and forced
four getter copies already supplied by their ledger owners.

[The object comparison](meshmdlio-seed-cleanup-20261028-codex.json) records the
before/after object hashes and primary-provider digests. COMDAT count falls from
80 to 75: only the anchor and those four getter copies disappear. Every retained
COMDAT has the same size and digest of bytes plus symbolic relocations; none is
added. Removed defined external symbols are exactly those five, and undefined
external symbols are unchanged. The two legacy getters equal their copies in
`MeshModelLegacyMaterials.cpp`; the other two equal their copies in
`MeshLoadContextAddLegacyMaterial.cpp`, including symbolic relocations.

The existing RefCount optimization pair remains: the previous evidence showed
that removing it changes Add_Ref. Four active present-unmatched declarations
remain. `hatch_counters.py --update` removes exactly 22 baseline entries
(present-unmatched total 3,746 to 3,724). No seed entry exists in the code/data
identity registers or header/MS-header queues; code identity remains in shadow.
All ledger owners remain tracked and no source paths move.

## Verification and limits

- Before/after `./build.sh meshmdlio.cpp`: 11/11 exact rows, 352 bytes.
- Primary-owner build: 27/27 exact rows; nine EH labels resolved and one named
  import checked. `link_check.py --prepare-current` then verifies all 38/38 rows
  and prepares strict receipts for all three units.
- `find_declared_unmatched.py`: all definitions declared, 11 matched rows;
  unclaimed definitions fall from 27 to four.
- `eh_verify.py`: no EH-bearing seed rows and no missing EH coverage.
- `data_check.py --converged`: 11 addresses, zero second names, zero unjudged.
- Ordinary preview at index `41c28839bf` (2026-10-28 11:08): seed LINKS before
  and after, 352 bytes. The three-unit after preview keeps all 3,801 authored
  bytes linking (352 + 2,714 + 735). This confirms inherited linking only.
- Staged-tree `link_batch_audit.py` is **inconclusive**: the index predates the
  outgoing base and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. Strict receipts for the three directly checked units do not close
  that wider consumer scope. Carry the removed duplicate-provider selection
  into the next scheduled census; no broader link clearance is claimed.

LINK-012 retains the shared material-view prerequisites and census follow-up.
No nightly, census, boot or game-smoke runner was started.
