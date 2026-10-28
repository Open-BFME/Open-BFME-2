# Projected-shadow decal inline floor linkage

Inspected base: `e6588f7665d316281a7c7906298082815cda0a0b`.
BFME 1 reference: `e74410b3738a2bb75d626085d9ebfd3406a43ff7`, covered
by the verified 2026-10-27 freshness receipt. Fetched preview index:
`41c28839bf`, 2026-10-28 11:08 (underlying census `c8734bec0c`).

The default picker claimed 0x001086EC and its source,
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowDecalHelpers.cpp`.
Prior attempts concern recovering the private helper ABI and real decal
callers; those successful reconstructions are preserved. All 17 rows match
before this change. The ordinary preview reports only the known LINK-132 /
LINK-133 selected `_floorf` blocker.

A static C-linkage declaration before the math headers keeps their unused
inline wrapper local, following the earlier terrain/pathfinder/renderer
repairs. The original external copy has no incoming runtime reference in
this object. The [object comparison](decal-floor-object-20261028-codex.json)
shows only `_floorf` removed, no added external COMDAT, and all 82 retained
byte-and-relocation fingerprints unchanged. Exclusive definitions, undefined
externals, weak externals, runtime roots and retained reference edges agree.
These are target object facts, not evidence for donor names or source layout.

Verification:

- Normal `./build.sh`: 17/17 rows exact, 43 float literals and 12 named
  imports verified. Frozen-file checks pass before and after.
- `eh_verify.py`: both EH graphs EXACT. Existing funclet ledger hints remain
  valid through the verifier's graph-based compiler-label resolution.
- Scoped `data_check.py`: zero findings. `git diff --check` passes.
- `link_check.py --prepare-current`: strict reusable receipts for this source
  and the unchanged retail `_floorf` owner,
  TerrainLogicAmbientColorRva0027DA6A.cpp; 19/19 rows, 50 float literals and
  15 imports verified.
- Same-index ordinary preview changes the decal unit from blocked to LINKS,
  covering 10,338 authored nonpadding bytes. The paired floor owner retains
  its existing selected-copy blocker; that explains the pair's exit 1.
- Outgoing staged-tree `link_batch_audit.py` exits 2, INCONCLUSIVE: the index
  predates the base, and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a
  current receipt. Carry this removed-copy scope and consumer into the next
  normal census. Full external consumer selection remains unverified.

LINK-132 / LINK-133 already record a separate upstream repair of the selected
Render2DSentenceDrawBFME2 copy. The old-index preview difference here is not
an incremental current-master or census-linked-byte claim. This bounded
cleanup removes the decal unit's unused public wrapper dependency while
preserving its verified code. Global repair confirmation and runtime checks
remain with the normal maintainer measurement workflow.

No rows, pins, source paths or shared headers move. Scratch objects and the
batch-audit output are under `build/decal-floor-20261028/`.
