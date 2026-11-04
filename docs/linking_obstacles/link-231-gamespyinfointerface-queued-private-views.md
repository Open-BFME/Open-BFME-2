### LINK-231: queued GameSpyInfoInterface consumers retain private virtual views
Status: Cleared for five consumers. Updated: 2026-11-04; inspected revision: `0afe04e636`.
Completed: BuddyDefs.cpp, RequestBuddyAddRva004178C1.cpp, StagingRoomGameInfo.cpp, Thread/PeerThreadPushStatsBfme.cpp and stlport_list_00416a5d_bounded.cpp use the existing shared interface; acceptance retired their five header-queue rows, with 144/144 rows matching and combined per-unit link-preservation verdicts passing.
Remaining / next check: other queued consumers remain outside this scope; no shared header or container identity change.
Evidence: [adoption and verification](../../reverse/attempt_support/gamespyinfo-header-adoption-20261104-codex4.md).
Census confirmation: no new measurement or linked-byte increase claimed.
