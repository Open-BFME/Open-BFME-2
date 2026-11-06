# Preserved header-adoption recovery, 2026-11-06

Preparation record: `.git/runner-prepare.json`, backup
`refs/runner/preparation/1793922804653601098`. The runner resynced all five
preserved commits onto `6d409fd607c65c809f113d4d95597486c9b56638` before this
session; no stash or resyncStash was recorded. The index and working tree were
clean, with no rebase in progress. A range comparison accounts for all five
commits' substantive edits; no saved source change was discarded.

`python3 tools/check_csv.py` passes. The required
`BFME_PUSH_SPACING_S=0 python3 tools/push.py --dry-run` builds the outgoing
header-adoption cohort but refuses two WindowVideoManager queue retirements:

```
PlayerInitFromDict.cpp: acceptance fails: link_check predicts a loss of census-linked bytes
ControlBar.cpp: acceptance fails: link_check predicts a loss of census-linked bytes
```

An ordinary joint `tools/link_check.py` preview over the four saved
WindowVideoManager consumers reports:

| Consumer | Census-linked bytes | Preview bytes | Result |
| --- | ---: | ---: | --- |
| PlayerInitFromDict.cpp | 4,707 | 0 | unresolved `?TheEmptyString@UnicodeString@@2V1@B` |
| ControlBar.cpp | 10,339 | 0 | same unresolved symbol |
| ControlBarConstructor.cpp | 567 | 567 | LINKS |
| Rva001D92C0Dtor.cpp | 331 | 331 | LINKS |

The index is the 2026-11-05 15:19 census at `f44cbcf5b0`. These are predictions,
not real-link or runtime measurements. Restore the two refused rows verbatim
from upstream's header queue. Preserve the byte-passing source changes and
the other accepted retirements. Retry these two retirements only when the
owning acceptance passes with the UnicodeString dependency resolved.

A fresh `header_adopt_lane.py accept --class WindowVideoManager` over all
four consumers confirms exactly those two FAIL and two PASS verdicts and
leaves both restored queue rows in place. `check_csv.py` and
`git diff --check` pass after restoration.

No source files were edited in recovery. Current class claims held by other
workers cover PlayerInitFromDict (Player) and ControlBar (GameWindowManager).
The queue and LINK-616 note have this checkout's file claims.
