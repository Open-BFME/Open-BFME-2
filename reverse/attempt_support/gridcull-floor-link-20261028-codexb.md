# Grid culling inline floor linkage

Inspected base: `9dc3b3d773e7982e4623a0ff8543e49135221eca`.
Preview index and census: `d92e7e6635`, 2026-10-28 15:58.
BFME 1 freshness receipt: 2026-10-26, verified upstream and reference
`001ccd8e27686e9887235b62ff797627f2dde7f5`.
The default picker claimed 0x0066D5E0 and the gridcull.cpp file scope.

The current object failed ordinary preview solely on the selected `_floorf`
copy, the existing LINK-132/LINK-133 issue. Earlier renderer repairs did not
clear this consumer against the current index. Its runtime relocation graph
has no incoming `_floorf` references: inline calls reach the CRT floor import.
The source's size-optimization comment does not require exporting this unused
inline copy. Giving it internal C linkage ahead of math.h follows the existing
verified floor-linkage repair, while preserving the optimization settings.

The [object comparison](gridcull-floor-object-20261028-codexb.json) proves
`_floorf` is the only removed external COMDAT. All 89 retained external COMDAT
byte/relocation fingerprints, strong definitions, undefined symbols, weak
aliases, runtime roots and retained reference edges are unchanged. Snapshot
verdicts are deliberately unassessed; equality is the comparison, while the
normal byte gates and preview supply retail and linking checks.

Checks:

- Before and after normal builds: 48/48 function rows exact; eight float
  literals and 60 named imports verified. The existing funclet verifies
  through its parent's EH data despite compiler-label renumbering.
- Complete EH graph: EXACT. Frozen-file checks before/after, class gate and
  scoped data checks pass (zero data findings).
- Strict preparation of gridcull.cpp and the unchanged retail `_floorf`
  owner TerrainLogicAmbientColorRva0027DA6A.cpp: 50/50 rows exact and two
  reusable receipts. No owner row, pin or shared header changes.
- Same-index ordinary preview: gridcull.cpp changes from blocked to LINKS,
  0 -> 11,117 authored bytes. Paired preview retains that result; the
  unchanged retail floor owner still reports the global selected-copy blocker.
  This is not a census-linked gain.
- Outgoing staged-tree batch audit: INCONCLUSIVE (exit 2). The index predates
  the base and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks
  a current receipt. Full external selected-consumer coverage remains
  unverified; carry this consumer into the next scheduled census.

Scratch source, object and comparison script:
`build/gridcull-floor-link-20261028/`. No source paths move, no debt retirement
or runtime result is claimed. Carry the removed-copy scope and its affected
consumers into the next scheduled census.
