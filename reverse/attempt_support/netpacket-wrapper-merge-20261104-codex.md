# NetPacket wrapper reader consolidation

2026-11-04; prerequisite `0b2bcef681` (canonical wrapper allocation and fixed
EH cleanup). `tu_skeleton.py --merge Code/GameEngine/Source/GameNetwork/NetPacket.cpp`
absorbed only `NetPacketO1.cpp`, removing one source file. The existing wrapper
reader at 0x0058E0E2 moves into its approved retail TU. The source-layout planner
was refreshed before the successful composition; tu_skeleton rebuilt its stale
map in memory. The committed map change is solely the one moved row's source
column, not a regenerated map or changed approval.

## Scope and checks

- Before: seed 209 matched rows plus one wrapper-reader row. After: the normal
  destination build verifies 210/210 matched rows; all 67 EH parents are EXACT.
  No baseline or debt key is retired by this move.
- `check_csv.py`, frozen-file checks, string/float/import verification pass.
- Ordinary link preview: destination LINKS 33,226 -> 33,525 bytes against the
  2026-11-04 13:15 census at f6d845ecd4; the absorbed source already owned the
  additional 299 bytes. Combined before/after is unchanged at 33,525. The strict
  new-variants preview passes. This is no measured linked-byte gain.
- Before/after COFF audit against both standalone prerequisite objects: no
  external code definitions are added, removed or changed, including normalized
  body/relocation digests, sizes and exclusivity. External data definition
  names, contents, normalized relocation digests, sizes and exclusivity are
  unchanged. No new external reference appears. Existing link-wide aliases
  in the seed are retained unchanged.
- No source being removed owns an identity/data/header debt key. The existing
  NetPacket list-copy identity obstacle is unchanged. The merge tool refreshes
  Microsoft-header queue evidence for the destination (one extra memcpy
  declaration occurrence, same ABI finding); the header queue has no reader
  row to transfer. No protected key is silently retired.
- Path-consumer audit covers the complete new path-changing batch after the
  prerequisite. Combined searches for NetPacketO1 and its old full path find
  no active consumer in tools, hooks, workflows, includes or build configuration.
  The functions ledger and map source column are repointed by tu_skeleton.
  Remaining old-path mentions are census-owned reverse/link_status.csv,
  historical attempt/obstacle evidence and the merge's origin comment; retain
  them. The tooling fixture for NetPacket.cpp still uses the surviving path.
- The inspected reader's scoped naming packet covers all nine bindings with no
  inventory warnings. A native child proposes i -> readOffset and msg ->
  wrapperMessage, explicitly retaining the other seven. Parent reviewed the
  complete proposal and diff; scoped apply verifies the pair together.

The two serializers still require their distinct payload layouts to be
reconciled; the Unicode helper still has a separate compiler/EH boundary.
Mixed donors are untouched. Full outgoing provider/consumer audit and the next
scheduled census decide integration beyond the scoped previews; no real-link
or runtime result is asserted here.
