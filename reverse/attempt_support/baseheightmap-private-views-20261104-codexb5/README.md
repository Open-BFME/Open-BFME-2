# BaseHeightMap private-view prerequisites, 2026-11-04

Base: `4427436691`. Claimed scope: the 42 files selected for the approved
`Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp` TU.
The consolidation planner was regenerated and its snapshot check passed before
the edits. No source paths or ledger rows move in this batch.

## Repairs

`tools/tu_views.py --no-merge-check` reconciled four existing private views in
nine files, with compiler-layout, byte, declaration-coverage and external-symbol
checks for each applied class:

* `W3DBibBuffer`: combine the existing public bib methods, protected allocation
  methods, friendship and construction/destruction declarations across five
  owners. The existing constructor view supplies the opaque 0x109D0-byte storage.
* `Gen_0074B410`: identical declarations in the scorch updater and projection
  helper, retaining the existing `bfmeBitA(int x, int y) const` spelling.
* `Rva0006C995`: share the existing set field at +0, flag at +0x10 and 0x14-byte
  compiler layout between the seed and InitHeightData.
* `AssetList00208F90`: share the existing set, +0x0C layout word, +0x10 flag,
  constructor, assignment and stream declarations in its two owners.

The last two initially failed because the chosen declarations used typedefs
local to another donor. Replacing those field typedefs with their identical
underlying `_STL::set` types preserved all 31 rows in the two declaring owners;
the subsequent view retry passed. The now-unused typedefs were removed.
The existing `??6AssetList00208F90...` comment now accompanies `operator<<`.
Copied assignment/constructor bodies retain their existing clear names.

These are reconciliations of existing compiler views, not new evidence for
retail member names, complete layouts or external donor provenance. Opaque
storage and placeholder identities remain explicit. Canonical classes were
left to the header-adoption lane.

## Verification

* [Combined build](build.log): 106/106 rows across all nine affected sources;
  11 literals plus three empty-string references, 39 floating literals and
  eight named imports verified. EH label renumbering is checked through the
  existing parent graphs.
* [Declaration coverage](unmatched.log): passes; the seed retains its existing
  note of one unclaimed definition, with no new unmatched definitions.
* [Before](family-link-before.log) and [after](family-link-after.log) local
  link previews: all 42 units link, 20,899 -> 20,899 bytes, using the same
  2026-11-04 22:01 index at `3fbce7bcb2`. This includes the 2,519-byte seed.
  The old missing-seed-index prerequisite no longer reproduces in this preview.
  This is not a new census or real-link result.
* [Ledger check](ledger.log): passes.
* [Initial view decisions](initial-view-report.json),
  [successful set-view retry](set-view-report.json), and
  [typedef-only build](set-types-build.log) preserve the specific evidence.
* [Verification commands and exit codes](verification.json) and
  [final source hashes](source-hashes.json) identify the checked inputs.

Three newly written declaration blocks received LF line endings, preserving
the surrounding files' existing bytes. The corresponding final checks are
recorded in `format-build.log`, `format-unmatched.log` and `whitespace.log`.

## Remaining work

The broad supported merge dry-run was interrupted after more than 24 minutes
without a final report. It produced no accepted merge verdict; no reduction in
source files or increase in census coverage is claimed.

The `BoundedShortGrid` union was fully restored. Adding its inline `load` body
to EvaluateVisibleCliff changes `?load@BoundedShortGrid@@QAEFHH@Z` from an
external reference into a definition, even though its paired rows still match.
Keep the existing out-of-line caller/provider relationship when reconciling
that view; no link-wide alias was removed.

The next merge pass still needs the canonical renderer/header prerequisites
and the private-view conflicts identified by the existing TU plan (including
W3DTreeBuffer, W3DBridgeBuffer, SceneClass and the terrain projection views).
Finish those prerequisites before rerunning the broad supported merge. Debt
register ownership and source-path consumers are unchanged by this batch.
