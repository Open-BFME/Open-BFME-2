# BattlePlanUpdate vision-object PlayerList adoption

2026-11-03; source base `34beab5e5daa7055427bbab435b634de8c4dc41b`;
claim owner `yasinschroeder-codex5`.

The current TU plan approves 50 rows across eight files, with no mixed or
refused files. The supported merge dry run accepts no donors. This change
addresses a header prerequisite in the vision-object donor; it moves no source
paths or ledger rows and commits no regenerated TU map.

The naming/consolidation planner surveyed the BattlePlanUpdate source prefix
and its original-path alternatives before editing. Its packet identifies one
eight-file investigation group with 29 static blockers. Overlapping earlier
planner runs correctly refused transient merge-probe inputs; the final planner
completed after the probe exited.

## Target facts and change

`createVisionObject` at RVA `0x00497A4B` loads a Player pointer from
`ThePlayerList + 0x18`, then its team from Player + 0x2EC. Canonical
`PlayerList.h` places the twenty-element `m_players` array at +0x18 and exposes
element zero through `getNeutralPlayer()`. Replace the donor's private scalar
view with that header and accessor. Correct the old comment calling this the
local player: canonical `m_local` is at +0x10. No new name or layout is inferred.

`header_adopt_lane.py accept` retires the donor's existing Player queue row
(the source already included canonical Player.h) and its PlayerList queue row
after this adoption: two header-debt rows removed through their owner.

## Verification

- `./build.sh` on the final vision source: 1/1 exact, 157 bytes; source,
  string, float and import checks pass.
- `find_declared_unmatched.py`: all defined functions already matched, both
  before and after editing.
- Both header-lane accept commands pass; no affected identity, data or
  Microsoft-header debt keys were found for this donor.
- Current-object `link_check.py` against census index `8661f15284`
  (2026-11-03 20:03): seed LINKS 2,605 -> 2,605 bytes; vision donor LINKS
  157 -> 157 bytes; combined 2,762 -> 2,762. This is a preview, not a new
  census result or a real-link clearance.
- `check_csv.py`: OK, 99,430 function rows, 9,343 symbols, 2,269 data rows.

## Remaining prerequisites

Automatic Player adoption in the seed refuses its field-renaming plan:
`m_team` is also a member of included `TeamInQueue`. The seed's Player view
declares this unused pointer at +0x2EC; no seed expression uses `m_team`.
No seed change or gate workaround was applied. The false reject is recorded
through `re_log.py`; binding-scoped adoption support is the next tooling check.

The merge also reports incompatible BattlePlanUpdate base clauses, missing
member declarations, an AsciiString/`const char **` mismatch in the module-data
constructor, `m_84` in the destructor, and BitFlags/Xfer declaration issues.
These remain separate prerequisite work. No source-file reduction, hatch
retirement, new linked coverage or image-ownership measurement is claimed.
