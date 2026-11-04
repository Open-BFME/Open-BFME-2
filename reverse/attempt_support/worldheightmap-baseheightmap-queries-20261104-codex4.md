# WorldHeightMap adoption in terrain queries, 2026-11-04

Inspected revision: `807dc34382`, on upstream `7779e19d6b`.
Claim owner: `yasinschroeder-codex4`.

## Completed scope

The three files under `Code/GameEngineDevice/Source/W3DDevice/GameClient/`
now include the existing canonical WorldHeightMap header:

- `BaseHeightMapCellQueries.cpp`: seven matched rows.
- `BaseHeightMapEstimateMaxHeightAlongLine.cpp`: one matched row.
- `BaseHeightMapIsClearLineOfSight.cpp`: one matched row.

Their private views had the same target-backed width, height, border and
16-bit data accesses already documented by the canonical header. No shared
header, field layout, function identity, pin, compiler flag or ledger extent
changed. The canonical WorldHeightMap header brings in RefCountData.h;
each consumer then sets the donor REFCOUNT_H include guard before including
BaseHeightMap.h, preventing the donor rendobj.h dependency from defining a
second RefCountClass. This is local to these consumers; no donor file changed.
No alternatename was removed or changed.

## Verification

- `./build.sh` passed all nine rows before and after adoption, including
  25 compiler float literals and eight named imports.
- `find_declared_unmatched.py` passes all three final sources.
- `header_adopt_lane.py accept --class WorldHeightMap` passed all three
  consumers and retired exactly their three rows from reverse/header_queue.tsv.
- A combined `link_check.py` preview predicts all three link against the
  census index at `f12552d0a7`, 2026-11-04 20:47 UTC: cell queries 939 -> 939,
  estimate 591 -> 591, line of sight 916 -> 916 authored bytes, 2,446 total.
  This preserves existing census-linked bytes; it is no new census or real link.
- `check_csv.py` and `git diff --check` pass.

Scratch compilation through tu_skeleton.Verifier preserves every matched RVA.
class_cleanup.same_runtime also proves complete non-debug object equality for
EstimateMaxHeightAlongLine (`d8a5e82422711dcb` -> `9840ede62327c003`) and
IsClearLineOfSight (`fca3d15a157df468` -> `c3c270f51669cbe7`).
CellQueries (`1db9e6cf37648dcf` -> `7dfa23027adbda21`) is not completely object
equal: the canonical header has both const and non-const accessors, so calls on
the non-const map select getDataPtr/getXExtent/getYExtent's non-const overloads.
Their emitted four-byte accessor copies replace the const copies. Its old
imported forceinline getBorderSizeInline declaration is replaced by the
canonical ordinary inline definition, adding a four-byte select-any copy.
The new accessor copies have no relocations; all seven matched bodies and the
combined link preview still pass. No complete-object equality is claimed for
CellQueries. The outgoing link-batch audit must judge affected consumers too.

All inspected function locals and parameters already describe their coordinate,
height or Bresenham-walk roles; no scoped naming change was needed.

## Remaining work

This closes only these three header-queue entries. The remaining WorldHeightMap
consumers still have aggregate-view, naming and helper-surface prerequisites;
the incompatible seed/donor compiler flags recorded in the earlier handoff
still block consolidation. No TU merge, source-path move, census run or smoke
run was performed.

## Outgoing consumer-audit handoff

After publication handoff of `f8d3dbf86e`, `link_check.py --prepare-current`
passed all three explicit providers, including the ordinary nine-row byte
and reference gates, and produced strict reusable receipts without changing
census/index/status. This resolved the first audit's missing-receipt report
for the edited sources.

The subsequent `link_batch_audit.py --base 807dc34382 --tip f8d3dbf86e`
remains **INCONCLUSIVE** (exit 2): the official index at `f12552d0a7` is not
the outgoing base, and affected outside consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Thus no clean whole-consumer audit or proven consumer regression is
claimed. The normal three-source prediction and header-adoption acceptance
above still pass. Carry this scope into the next official census with current
outside-consumer objects; the fleet publisher will also run its normal batch
audit on the actual rebased outgoing bundle. No verifier was changed and no
maintainer-only measurement was run.
