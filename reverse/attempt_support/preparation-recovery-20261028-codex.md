# Preserved batch recovery, 2026-10-28

Recovered all seventeen saved commits onto upstream `696149099c`; checked tip
`6f76860438`. The preparation record named backup
`refs/runner/preparation/1793206558444709652`, no stash and no resync stash.
The backup and existing stashes remain intact. No commit was skipped, and no
untracked or unstaged saved edit remained after the rebase.

The FireWeaponUpdate data-owner conflict retains both its intended new TU owner
and upstream's OilSpillUpdate owner. The ScriptEngine MS-header queue conflict
retains its merged destination entry and all six independent upstream entries.
Obstacle-register conflicts retain both sets of handoffs. A subsequent upstream
advance rebased cleanly. Of the 36 outgoing Code paths, all match the backup
except StreakRendererRenderStreak.cpp, which additionally retains upstream's
identical internal-linkage floorf declaration. The earlier Coord3D adoption
already present upstream remains there rather than being reapplied.

The complete outgoing path audit covers nineteen removed fragments: three
FireWeaponUpdate and sixteen ScriptEngine donors. Combined full-path and
basename searches find no active tool, hook, configuration, include, queue,
debt-register or path-column consumer selecting a deleted source. Remaining
mentions are provenance comments, historical attempts/deleted-row notes,
function-row evidence prose and the historical census status. Existing
consolidation handoffs retain provider/COMDAT, debt and queue evidence; the
recovery changes no source placement or declaration beyond the saved batch.
Scratch search results are in `build/recovery-path-audit.txt`.

`python3 tools/check_csv.py` passes (98,945 function rows, 9,417 symbols and
2,203 data rows). `git diff --check` passes. The conflict index and working tree
were clear. `git push --dry-run origin HEAD:master` exits 0 and reports
PRE-PUSH OK: 229/229 function rows across twenty sources, three data rows,
fifteen EXACT EH graphs, string/float/import checks and converged data checks.
Its log is `build/recovery-push-dry-run.log`.

The outgoing link audit remains INCONCLUSIVE: index `41c28839bf` predates the
base, and six affected source objects lack current receipts, first
`Code/GameEngine/Source/GameClient/Eva.cpp`. Carry these consumers, the moved
providers and the saved declaration/data repairs into the next scheduled
census. The successful hook is not full consumer-link verification, and no
census-linked-byte or image-ownership gain is claimed.

## Publisher retirement refusal and preserved upstream deferral

Subsequent upstream advances were rebased without skipping commits. Independent
obstacle and queue entries were retained. Upstream now carries the shared-header
adoptions, including the geometry helper; its only source conflict was the saved
explanatory comment, which is retained alongside the upstream include.

The repeated local dry run at base `4ccc160a05` passed the same 229 function,
three data and fifteen EH checks. The fleet publisher then tested the batch at
`3dbbc13cb7` and refused the geometry helper's Coord3D queue retirement because
`link_check produced no usable per-unit verdict`. The local ordinary preview
still gives LINKS, 121 -> 121 bytes. Upstream commit `4ccc160a05` had already
deferred this exact retirement for the same publisher limitation; replaying
the saved batch removed that restored row again.

Restore the exact upstream queue row in a new corrective commit. The source
and original adoption evidence stay intact; this batch claims no retirement
of that key. Retry the owning acceptance tool only when the publisher can
obtain its required per-unit preview. Its queue failure text remains historical.
No verifier is changed. The publisher refusal is saved in
`build/recovery-publish-third.log`, and the local dry run in
`build/recovery-push-dry-run-rebased.log`. All preparation backups remain intact.
