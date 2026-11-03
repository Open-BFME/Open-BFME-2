# ObjectFilter fixed-storage header adoption

Inspected master: `90ac7589a4`, 2026-11-03. Claimed the ObjectFilter
consolidation cohort through `next_work.py --tier consolidate --claim`.

The scoped consolidation planner found no original-path proof for this group;
the merge planner rebuilt its stale TU map in memory and approved 60 rows.
No generated map is committed. Both merge trials accepted no donors.

Replaced ObjectFilter.cpp's private 28-byte BfmeFixedStorage0004543D view with
its existing canonical header. There are no field accesses to rename: the
private `m_data` field was unused. This avoids the automatic field-renaming
collision with an unrelated class's `m_bytes` field without altering either.

- [Byte gate](build.log): 35/35 rows match; source, string, float and import
  checks pass. find_declared_unmatched.py reports all definitions matched.
- [Owning acceptance](accept.log): header_adopt_lane.py accept retires exactly
  the BfmeFixedStorage0004543D/ObjectFilter.cpp header-queue row.
- [Current-object link preview](link.log): LINKS, 3,355 -> 3,355 bytes against
  the 2026-11-03 20:03 index at 8661f15284; no census gain claimed.
- [Remaining merge blockers](merge-dry-run.log): record-view declaration
  ordering, duplicate StringBase headers, Assign's void/pointer return
  declarations, and vector-destruction bytes. [View reconciliation](views-dry-run.log)
  refuses overlapping record fields and the erase view's class/struct mismatch.

No source paths, aliases, pins, compiler flags or ledger rows changed. No merge
is applied. Further consolidation needs separate verified donor reconciliation.
