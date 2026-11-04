# TileData RGBA mip fragment consolidation, 2026-11-04

Inspected prerequisite revision: `f88363941e1be9ae179543d9ee08233865f1ddb7`.
Outgoing-range audit base: `9990d567e406421094f1879aecf9bf569e84d86d` (`origin/master`).

## Target facts and repair

The current in-memory TU map approves RVA 0x00111A05 (134 bytes) for
`Code/GameEngineDevice/Source/W3DDevice/GameClient/TileData.cpp`.
The supported planner's TileData group identifies the original TileData path,
private-view reconciliation and quoted-include review; it does not itself
approve the move. The supported merge plan supplies approval and byte checks.
The earlier boundary is recorded in
[the 2026-10-26 declaration handoff](consolidation-sol-tiledata-declarations-20261026.md).
No additional original function or member name is inferred here.

Prerequisite commits replaced the fragment's private TileData with the
canonical header and cast its byte-array buffers to the existing word helper.
They also replaced the destination's private TileData and RefCountClass views.
A local inline definition of the canonical base destructor preserves the
existing inline teardown; canonical field references replace the private ones.
The header lane accepted all three adoption rows. The fragment's stale
present-unmatched marker and its one hatch key were removed with its fix.
No data or identity key is retired by this merge.

## Merge and verification

`tu_skeleton.py --merge .../TileData.cpp --dry-run` accepts the destination
and `Code/GameEngine/Source/Common/Rva00111A05Finish.cpp`; the applied merge
reuses that verified plan and its census-linked guard. It deletes the fragment
and repoints exactly one functions.csv row and one tu_map.csv source cell.
The TU map's assignments and evidence are not regenerated into the commit.

- `./build.sh .../TileData.cpp`: 10/10 byte-exact rows, including the
  destructor's renumbered funclet verified through its parent EH data.
- `find_declared_unmatched.py`: clean.
- `check_csv.py`: 99,440 function rows, 9,336 symbol rows, 2,269 data rows; OK.
- `tu_ownership.py --staged`: passes; one approved owner for the moved row.
- `code_identity_gate.py --staged`: 10 rows, zero new findings (shadow).
- `data_check.py`: zero findings; no data-ledger ownership changes.
- `eh_verify.py`: one EH-bearing parent, EXACT, no missing object.
- `link_check.py`: merged destination previews 719 linked bytes, equal to
  the pre-merge pair's 585 + 134 bytes. Both standalone prerequisite units
  also passed. These are previews, not a new census or whole-game link.
- `link_check.py --new-variants --staged-peers --staged --shadow`: passes.
- Scoped `ms_header_audit.py scan --write-queue`: zero local Microsoft names,
  no queue change. Neither affected source retains a header-queue row,
  MS-header row, code/data identity key or hatch key.

The merge's current-object guard and staged identity/COMDAT checks preserve
provider/consumer bindings in this scope. No pin, alias or data provider is
removed. The full outgoing link-batch audit remains the publisher hook's check.

## Complete pending path audit

Reviewed the outgoing range above plus the staged merge using
`git diff --name-status --find-renames origin/master`.
Its only game-source path deletion is Rva00111A05Finish.cpp; the other pending
game-source changes are in place. The obstacle-ID metadata rename has no game
source consumer. Searched the old full path and basename across active tools,
hooks, workflows, source/includes, build configuration, docs and registers,
including hidden tracked configuration. No active tool/include/build consumer
requires a change. Remaining old-path references are the merge's provenance
comment, the 2026-10-26 historical handoff, and reverse/link_status.csv's
published census snapshot. The census snapshot is intentionally unchanged.
No affected fold proof, data owner, path debt or header queue remains on the
deleted source. The scoped Microsoft-header refresh changed no tracked queue.

Result: one fewer Code source file; three header-queue rows and one stale hatch
retired in separate prerequisite commits. All ten existing matched rows remain.
The mixed TileDataGetRGBDataForWidth.cpp donor still stays out of this merge;
its earlier split/deleting-destructor boundary is not claimed repaired.
