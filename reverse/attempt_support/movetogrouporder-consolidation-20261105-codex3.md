# MoveToGroupOrder consolidation, 2026-11-05

Scope: `MoveToGroupOrder.cpp` and `MoveToGroupOrderIsDone.cpp` under
`Code/GameEngine/Source/GameLogic/AI/`. Declaration repair: `12420f1a5b`.

The current in-memory TU map approves the done-check row at `0x00547368`
for `MoveToGroupOrder.cpp`. This is a provisional approved TU; the planner's
donor path `GameLogic/Ai/GroupOrders/MoveToGroupOrder.cpp` remains a lead,
not recovered target path evidence. No TU approval was added.

The initial merge failed on duplicate `rts::hash` definitions (also recorded
in `shard0-mechanical-consolidation-blockers-20261104-codex.md`). Sharing
`RtsHashView.h` exposed a second conflict: the seed's private Object position
member did not coexist with the donor's Object header. The seed now uses that
header's inherited `Thing::m_cachedPos`, at the same +0x38 offset.
Both repairs passed their individual byte checks before the merge.

`tu_skeleton.py --merge` accepted the seed and done-check donor, preserved all
eight matched rows, and removed one source file. Four mixed files remain.
Only the moved row's source column changed in the committed TU map; the map
was not regenerated. Header debt moved to the destination through the merge
tool. No hatch, alias, data or code-identity debt was removed by this merge.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/AI/MoveToGroupOrder.cpp`:
  8/8 rows match; string, float and import checks pass.
- `find_declared_unmatched.py`: passes; two pre-existing registered unclaimed
  definitions remain in the seed.
- `check_csv.py`: passes, 99,458 function rows.
- `data_check.py --staged`: no findings; `code_identity_gate.py --staged`:
  eight rows, no new findings, shadow mode.
- `tu_ownership.py --staged --shadow`: no findings.
- Merge link guard accepts the current composition against the census index.
  Before repair, both sources' previews are clean (312 + 143 authored bytes).
  After composition, the destination preview is clean (455 authored bytes).
  Two unreferenced Armor hashtable diagnostics remain non-blocking. This is
  preview evidence, not a census gain or a real game-link measurement.

Tooling compatibility audit: reviewed `origin/master..12420f1a5b` plus the
staged merge. Earlier outgoing commits contain no game-source path moves.
Searched the deleted donor's full path and basename across tools, hooks,
workflows, Code, documentation and reverse registers. There are no active
tool, include or build/config consumers to update. The ledger, TU map and
header-queue owner/accept command are repointed by `tu_skeleton`; no donor
keys exist in the data/code-identity or Microsoft-header registers. The
Microsoft-header report was refreshed by the merge tool. Remaining old-path
mentions are census history, original-source attribution, stored diagnostic
text or historical attempts/patches; they are retained intentionally.

The existing `AIUpdateInterface` header is used by the merged body; its
acceptance command passed during verification. Its queue-row retirement is
kept in a follow-up commit through `header_adopt_lane.py accept`. ArmorTemplate
header reconciliation and the four mixed donors remain outside this merge.

Publication correction: acceptance passed again after the merge and removed
the transferred queue row, but the runner's outgoing-range preflight refused
that retirement: the original donor no longer exists and the destination key
no longer survives to demonstrate the transfer. A follow-up restores the
destination's queue row, preserving the merge's explicit debt transfer. No
header-debt reduction is claimed by this batch. The header acceptance itself
passed; retirement remains for a later batch whose base contains the merge.
