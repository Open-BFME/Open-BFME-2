# Preserved checkout recovery, 2026-11-04

Recovery input: `.git/runner-prepare.json`, backup
`refs/runner/preparation/1793771403712759218` at `6b8478d4292e6fff5ed596c7bc8f365eb4089b2b`.
The runner already rebased the nine preserved commits onto `0e0415d031`;
recovered tip before this repair is `c206136846`. There is no active rebase,
conflict index, saved stash, resyncStash or uncommitted saved edit. The backup
ref remains intact. No preserved commit was skipped or rewritten by this session.
All nine outgoing commits use the configured account noreply identity.

The first push dry run reproduced the two recorded refusals. Upstream's
QuadStrip2D entry owns LINK-198, so this checkout's newer SidesListNotifier
entry becomes LINK-199, including its filename. Its original contents and
constructor prerequisite are otherwise retained. No other entry is edited.

The armor identity retirement failed closed on two absent ledger objects
(RespawnBody.cpp and COM/_com_error.cpp) and one stale referenced provider
(Common/RTS/Team.cpp). Ordinary `./build.sh` on these three sources passes
171/171 function rows, one data row and all reference checks ([log](providers.log)).
`python3 tools/repair_queue.py verify-removed --range origin/master HEAD`
then exits 0 ([log](debt.log)); no register row or verifier is changed here.
The prior owning-tool retirements remain supported by current verification.

`python3 -m pytest tools/tests/test_tu_skeleton.py tools/tests/test_gate_exploits.py -q`
passes 239 tests and 63 subtests, with one skip ([log](tests.log)).
`python3 tools/check_csv.py` passes: 99,434 function, 9,341 symbol and 2,269 data rows.

The final source-path audit covers `0e0415d031..c206136846` plus this document
entry rename. The only removed source is Common/Rva00289371HashClear.cpp;
its two ledger/map source columns point to GameLogic/System/ExperienceLevelSystem.cpp.
Searching tools, hooks, workflows, includes, source, documentation, registers
and root build/config files finds no active consumer of the removed path.
The remaining hits are the destination's provenance comment and historical
attempt evidence ([search results](path-audit.log)); the historical census
observation remains unchanged. The renamed obstacle entry has no incoming
path references requiring updates. No further source path or consumer changes
are introduced in recovery.

The composed ExperienceLevelSystem batch's previously recorded inconclusive
census receipt scope remains in its existing handoff; this recovery does not
claim a new census, full-batch link clearance or real-link coverage gain.
