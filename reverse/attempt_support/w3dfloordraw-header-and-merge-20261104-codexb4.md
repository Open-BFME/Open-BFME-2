# W3DFloorDraw header adoption and consolidation audit

Inspected revision: d0a7899698; 2026-11-04; worker yasinschroeder-codexb4.
Audit range: origin/master beaefa11e87c1f6c200d10f821b430edf96838ba through
that revision plus this staged merge. The only source-path removals in the
outgoing range are W3DFloorDrawXfer.cpp and W3DFloorDrawPoolKey.cpp.

Two prerequisite commits replace private W3DFloorDraw declarations in the
main source and xfer source with the existing canonical header. The original
field offsets are unchanged; inherited module-data and drawable pointers are
cast to the existing narrow views. header_adopt_lane.py accept retired the
W3DFloorDraw queue row for each source, plus the main source's FieldParse
and MultiIniFieldParse rows. All four acceptance verdicts passed, including
the linked-byte preservation checks. No debt row was deleted by hand.

The supported consolidation planner was regenerated before composition.
The current in-memory map approves the destination as a provisional TU:
grouping is approved; the provisional path is not independent proof of the
original retail source filename. tu_skeleton.py --merge --dry-run accepted
the seed, xfer, and module-name-key sources. Application reused that plan,
reverified bytes and the census-linked guard for all six candidate sources,
and absorbed the two donors. Four functions.csv source cells and four
existing tu_map.csv source cells move; no regenerated map is committed.
Two data_ledger.csv entries (the name key and its static guard) transfer to
the destination with their names and addresses unchanged. No debt is retired
by the merge and no pin, alias, fold proof or hatch is added or removed.

Verification after application:

- ./build.sh destination: 23/23 rows exact, including resolved funclet labels
  and the complete emitted STLport constructor fold; string, float and import
  references pass.
- find_declared_unmatched.py: all defined functions already matched (the
  existing diagnostic about one unclaimed definition remains unchanged).
- eh_verify.py: five EH parents EXACT, no baseline entries or missing objects.
- check_csv.py: OK; tu_ownership.py --staged: exit 0.
- link_check.py destination: LINKS, own bytes 1,010; baseline 798 from census
  2026-11-04 05:53 at 5a13f2cd61. This per-file comparison absorbs the donor
  rows; it is not new linked coverage or a census measurement. The merge's
  guard also checked selected COMDATs and affected outside consumers.

Combined outgoing path-consumer audit: searched both removed basenames across
tools, hooks, workflows, Code, docs and root build/configuration paths. Only
provenance comments in the destination retain the old paths. No active include
or tooling consumer needs an update; ledgers remain the source-discovery input.
No removed basename remains in identity, data-check, header, Microsoft-header,
hatch, flag, body-owner, data-row, symbol or doxygen registries. The merge tool
refreshed header/Microsoft-header reports without changing those queues.
Existing destination BaseHeightMapRenderObjClass adoption debt stays queued.
Historical link_status.csv, deleted_rows.csv explanations and attempt evidence
retain their original paths intentionally.

Remaining consolidation prerequisites: the ctor still uses its private m_10
slot and owner view; the dtor and draw-module source conflict with the main
source's terrain/drawable declarations, and the draw-module ModuleData view
uses a different class key. Reconcile those donors in separate verified
header-adoption commits. Seven mixed sources remain outside this merge.
The current pass removes two source files, keeps all rows and retires four
header-queue entries; no real-link, census or image-ownership gain is claimed.
