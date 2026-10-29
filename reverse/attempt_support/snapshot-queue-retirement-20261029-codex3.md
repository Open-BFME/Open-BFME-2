# Retire the allocator Snapshot discovery errors

Inspected base: `a72bd0c42a`, 2026-10-29. This completes the queue cleanup
enabled by `3450d8a38b` (scope-aware discovery) and `0ce38b8299` (owning-tool
acceptance of a proven discovery error). No game source or verifier changes.

The default picker claimed `class:Snapshot` and its seven queued sources.
Only these three entries are discovery errors, all under
`Code/GameEngine/Source/Common/System/`:

| Source | Compiled nested record | Ordinary preview bytes |
| --- | --- | ---: |
| Rva00034D10Snapshot.cpp | EA::Allocator::GeneralAllocator::Snapshot, 36 bytes | 874 -> 874 |
| Rva000353F0Trace.cpp | EA::Allocator::GeneralAllocator::Snapshot, 36 bytes | 493 -> 493 |
| memory_pool.cpp | EA::Allocator::GeneralAllocator::Snapshot, 36 bytes | 8,757 -> 8,757 |

For each source, `header_adopt_lane.queued_text` finds the source in the commit
that queued it, and `class_layouts.class_bodies` finds no namespace-scope
`Snapshot` in that historical text. Current compiler CodeView contains no
global `Snapshot` record, including forward references. The snapshot builder
also contains its distinct 56-byte `Rva00034D10Snapshot` record. The owning
tool's `misclassified` predicate returns true for all three. This is target
source/history and compiler evidence, not a donor-name inference.

`python3 tools/header_adopt_lane.py accept --class Snapshot` with the three
explicit paths reports PASS for each and retires exactly three rows from
`reverse/header_queue.tsv`. No canonical include is owed by these unrelated
allocator records. The four real Snapshot queue entries remain unchanged.

Verification:

- `find_declared_unmatched.py` reports all defined functions already matched
  in each unchanged source; memory_pool retains its existing note about one
  unclaimed definition. No source edit or marker was added.
- `./build.sh` on the three sources passes 56/56 function rows, one data row,
  14 literals, two empty-string references and 45 named imports.
- `link_check.py --prepare-current` on the same explicit scope passes and
  produces strict reusable compiler receipts; its normal gates reuse those
  same objects.
- `link_check.py --fetch-index` retains the published index at `85f6b7f40c`,
  2026-10-29 15:08. Ordinary preview passes all three units, preserving
  10,124 authored bytes. This is a preview against that older index, not a
  new census or consumer-wide measurement.
- `check_csv.py` passes (99,005 function rows, 9,420 symbols, 2,235 data rows).
- Staged `repair_queue.py verify-removed` passes for all three retirements.

This retires three invalid header-debt entries through their register's
acceptance path. It claims no header adoption, new matched/linked bytes,
image ownership change or clearance of the remaining LINK-098 prerequisites.
