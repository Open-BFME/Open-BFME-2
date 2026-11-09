# name_lane: a settle route for stuck resolutions, and the double voter

Queue item for a tools seat, from the Bridge lane, 2026-11-08. The coordinator accepted both limits
for now and asked for this as separate later work. Record counts are from origin/master at
866702946d; re-run them before building on them.

## 1. Nothing moves a reviewed approval that stopped proving its spelling

`resolved_workers` moves a worker off its vote when it accepts another spelling, and two such
acceptances count for neither. Two checkouts that cross can each record an agreement, because neither
sees the other's row. Once merged, `verify_resolution` proves neither spelling, so no wrong name lands.
But the key is stuck, and a stuck key needs a hand repair:

- `apply` prints "reviewed approval is no longer valid for this source and voter set; left" and goes on.
- `resolve` refuses both voters: "this key is already approved, landed or disputed".
- `dispute` only takes a landed name.
- An edit to the source does not reopen it. In `cmd_apply`, the `if not valid: ... continue` branch runs
  before the source-changed branch, and that branch also excludes `nr-` ids. So the rule in `name_lane.py`'s
  docstring, "when its source has changed it lands nothing and reopens the key", does not hold for `nr-`
  records. No `nr-` row has ever been marked `source-changed`. The skip dates from 41249fd2b1 (2026-10-30)
  and predates the moved-worker rule.

A reproduction is in `tools/tests/test_name_lane.py`: `crossed_approvals`, and the
`test_status_names_*` tests. `status` names these keys (`report_unsettled`); it settles nothing.

### Open records already stuck

There are no crossed keys today. All 4 open `nr-` records have a source that changed or has gone:

| Record | Status | Source | Key | Spelling |
|---|---|---|---|---|
| nr-7efe40c71cd2880cbab900c7 | agreed | changed, placeholder gone | `StlSweepW5Rva002D07F4.cpp`, 0x002D07F4 | `_Rb_tree` of `BfmeStringRecord002CF550` |
| nr-e4d8727398104fb1bead084b | agreed | changed, placeholder gone | `StlSweepW5Rva002D07F4.cpp`, 0x002D0B36 | `set` of `BfmeStringRecord002CF550` |
| nr-6506d6827f6e1f9ee4ab222c | blocked | changed, placeholder still there | `Rva0025E5F4RelayCommands.cpp`, class `Rva0023D201StatusView` | `GameLogicPlayerQuitStatusView` |
| nr-1991a682a72145c6f3de9233 | blocked | file gone | `Rva007F7AE0LobbyListRequest.cpp`, class `Rva007F7AE0Owner` | `LobbyListRequestContext` |

The first two are the first case to settle. They are P29's, and those rows landed by another route
(5504eefa7f, respelled by code identity), so they are stale rather than blocking. `status` lists both as
held. It does not list the two blocked records, because `resolve` does not refuse a blocked key.

### What to build

Proposed, neither built nor tested: `apply` gives an invalid `nr-` record the same treatment as any other
record. If the source has changed and the placeholder is still there, it writes `source-changed` and
reopens the key. If the placeholder has gone, the record goes stale, which is what should happen to P29's
two. A resolution binds to its source, so after a reopening the voters can accept again.

Questions for the design:

- A crossing on an **unchanged** source stays stuck, since a reopening needs a source change. Writing a
  `source-changed` row by hand would not free it either, because `resolve` still refuses a worker that has
  already accepted a different spelling for that source. If this needs a route, it is an auditable
  withdrawal of an acceptance, which `resolved_workers` then has to read. Nothing should let a voter settle
  a key by editing the source.
- Which status is right for a blocked record whose file has gone?
- Run the old and new rule over every record before landing, as was done for the moved-worker rule. Compare
  every voted or resolved spelling by hash, not only the spellings named in resolutions: a worker that moves
  loses the spelling it moved off, which no resolution names.

## 2. A worker with two blind votes counts for both spellings

"One spelling" holds only for a worker that has accepted a spelling other than its votes. A worker with two
different vote hashes counts for both, and recording a reason on one of its own votes changes nothing, since
a reason on your own vote moves you nowhere. If it accepts a third spelling, it counts for that one only.
This behaviour predates the moved-worker rule, which did not change it.

One case on master, with no agreement resting on it:

- Key: `Code/GameEngine/Source/Common/RTS/Rva002AD19EArmor.cpp|function|0x002AD19E|rva002AD19E`
- Worker `w-2a58b1ead41e`, two votes on 2026-11-02 from sessions `drz-k9-n34b2` (6715b6f808, hash
  97139ffe68e8...) and `drz-k9-n34b3` (5d691347b6, hash 2a61422bf72b...).
- The third vote is `w-4cad33e49465`, session `drz-k2-n34b` (1124ec5129, hash 995322e7aa6e...): three
  different spellings.
- None of the three votes has a row in `reverse/name_vote_sources.csv`, and the key has no row in
  `reverse/name_agreed.csv`.

Not investigated: how a second vote from the same worker got through `submit`, and whether the fix belongs
there. Decide what two votes should count for (neither, or the later), then audit as above.
