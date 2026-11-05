# AIPathfind saved-plan claim scope refusal

Inspected source revision: 3dcdacf594, 2026-11-05. The supported current-input
planner uses 401 approved rows, 73 candidate files and 32 mixed sources.
The dry merge accepts the seed plus three callback donors: ED15A (also D01E),
F4491 and F4D8B. Four existing functions total 977 bytes; no source has moved.
The saved plan passes the normal byte verifier and its unmodified LinkGuard.
The seed independently passes 90 function checks and two data checks; the
three donor builds pass 2, 1 and 1 function checks. The seed preview retains
5,069 authored bytes against the published 2026-11-05 census index.

The actual apply exits 2 before writing anything. It claims all 73 candidate
files and their 217 distinct RVAs, including rejected candidates. Two rejected
candidate fold addresses, 0x0007FAB3 and 0x0014F3C4, are held by
`yasinschroeder-codexb2` for AIDozerManager.cpp (about 0.8 hours left at the
check). The accepted three donors contain neither address. A subsequent
`claims.py claim <four files and four callback RVAs> --dry-run` reports all
eight claimable. The tool releases its partial broad claim acquisition.

This is a claim-scope false reject for saved-plan application, not permission
to bypass claims. Next: claim only a valid saved plan's accepted cohort before
its existing fresh byte/link/carry checks; if that plan fails, acquire the full
search scope before searching or writing any wider merge. Keep contention on
any accepted donor or its rows blocking. Reproduce both cases in tool tests
and keep the game-source merge separate. Broader declaration/template/byte
obstacles remain as listed in dry-run-summary.json. No census, source-file,
TU-approved, debt or runtime gain is claimed by this investigation.
