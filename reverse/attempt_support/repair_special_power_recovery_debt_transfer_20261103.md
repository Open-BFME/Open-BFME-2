# RepairSpecialPower preparation recovery, 2026-11-03

The preserved batch at f849b4407c contained eight commits; the runner had
completed its rebase onto f41c2b71be before this recovery. The preparation
record named no stash or resyncStash, and the index, worktree and untracked
file list were clean. The backup remains at
refs/runner/preparation/1793749220390128452. No saved change was discarded.

The initial `BFME_PUSH_SPACING_S=0 python3 tools/push.py --dry-run` refused
three vanished-source header debts: AICommandInterface, AIUpdateInterface
and ThingTemplate on RepairSpecialPowerAtObject.cpp. Commit 5e21f25896
transferred them to RepairSpecialPower.cpp, then 89e9239e01 accepted them.
The outgoing net diff therefore had neither a surviving transfer nor
deleted-row accounting for the absorbed donor. Its matched row is still
live at 0x004C875E, so a deleted-row tombstone would be incorrect.

Restore exactly the three transferred queue rows from 5e21f25896 under
RepairSpecialPower.cpp. The source merge and all byte-verified bodies remain
unchanged; these three debts remain outstanding for a later owning-lane
acceptance after the transfer lands. This supersedes the debt-retirement
claim in repair_special_power_header_closure_20261103.md; its historical
acceptance and inconclusive affected-consumer audit evidence remain valid.
The BehaviorModule and snow-renderer header retirements remain subject to
the outgoing hook's normal acceptance checks. No new link clearance or
census result is claimed.
