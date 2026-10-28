# Streak renderer inline floor linkage

Inspected base: `771fab033f8438b89fd91ca1521f9fadb0078e16`.
BFME 1 reference: `e74410b3738a2bb75d626085d9ebfd3406a43ff7`, with
the verified 2026-10-27 freshness receipt. Published preview index:
`41c28839bf`, 2026-10-28 11:08 (underlying census `c8734bec0c`).

The default picker claimed 0x00743700 and its source,
`Code/Libraries/Source/WWVegas/WW3D2/StreakRendererRenderStreak.cpp`.
The prior successful R11 reconstruction is preserved. The current object
already matches all four rows; its only ordinary-preview blocker is the
selected `_floorf` copy, the existing LINK-132/LINK-133 issue.

The wrapper has no incoming runtime reference in this object. A static
C-linkage declaration before math.h makes its unused inline wrapper local,
following the verified Pathfinder and terrain repairs. The renderer's
arithmetic, compiler options, declarations and dependency bindings remain
unchanged. No ledger, pin, shared header or source path moves.

The [object comparison](streak-renderer-floor-object-20261028-codex.json)
records exactly one removed external COMDAT, `_floorf`, with no additions.
All 80 retained COMDAT byte/relocation fingerprints, exclusive definitions,
undefined externals, weak aliases, runtime roots and retained edges are
unchanged. This is object evidence, not donor-source or layout evidence.

Verification:

- Normal `./build.sh`: 4/4 function rows exact; 18 float literals and two
  named imports verified. Frozen-file checks pass before and after.
- `eh_verify.py`: one EXACT graph. The byte verifier resolves both renumbered
  compiler funclet labels through that graph; the ledger rows remain valid.
- Scoped `data_check.py`: zero findings. `git diff --check` passes.
- `link_check.py --prepare-current` verifies this source and the unchanged
  retail floor wrapper owner, TerrainLogicAmbientColorRva0027DA6A.cpp:
  6/6 rows, 25 float literals, five imports and two strict reusable receipts.
- Same-index ordinary preview changes the renderer from blocked to LINKS
  for 14,007 authored nonpadding bytes. The paired floor owner still has its
  existing global selected-copy blocker; the pair's nonzero exit reflects
  that unchanged owner, not a renderer failure.
- The outgoing staged-tree audit exits 2, INCONCLUSIVE: the index predates
  the base and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks
  a current receipt. Carry this removed-provider scope and consumer into
  the next normal census. Full external consumer selection is unverified.

Only the renderer's preview is cleared. The global selected-copy issue,
census confirmation and runtime verification remain open. No census-linked
byte, debt or image-ownership gain is claimed. Scratch receipts are under
`build/streak-floor-20261028/`.
