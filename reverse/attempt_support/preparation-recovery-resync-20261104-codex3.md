# Preserved batch resync recovery, 2026-11-04 (codex3)

Preparation record: `.git/runner-prepare.json`; retained backup
`refs/runner/preparation/1793755157392811320` at `2110880e9577`.
The record names no stash or resyncStash. No saved untracked, staged or
unstaged changes remain outside the replayed commits. Backups are retained.

The resumed rebase onto `5a13f2cd6151` stopped at the network header adoption.
ConnectionManager_sendLocalGameMessage already included NetCommandMsg.h
upstream; preserve that adoption and add NetGameCommandMsg.h. Resolve the
header queue from upstream's current rows, subtracting only this commit's
accepted keys rather than resurrecting other workers' removed debt.
The remaining three commits replay without conflict; no commit was skipped.
The resulting ten-commit tip is `f15933d95c` before this recovery correction.

`check_csv.py` passes (99,433 rows). All three network adoption sources pass
`find_declared_unmatched.py`. The first push dry run exits 1 after 13.1 s:
only two obstacle ID collisions are reported before its early gate stop.
Upstream now owns LINK-188 and LINK-189. Preserve those entries and move this
batch's AptScriptFunction and NetGameCommandMsg notes to LINK-195 and LINK-196,
respectively, changing only their heading IDs and filenames. The previous
recovery note's LINK-189 assignment records its earlier state.

The earlier Player header-key transfer remains in the replayed recovery
commit: UpgradeDie.cpp retains the vanished donor's queue row. This resync
adds no debt retirement or source edits beyond conflict resolution.

Repeated full-batch path-consumer audit: removed Rva00447B0EDtor.cpp,
Rva005965A5Ctor.cpp and UpgradeDieOnDie.cpp, plus both renamed obstacle paths
and the original LINK-187 Apt filename. No active tool, hook, workflow,
shim, include, build/configuration or current ledger/debt register names
these paths. Code references are donor provenance or an existing layout
comment; historical census, attempt and obstacle records stay unchanged.
The prior LANGameInfo, AIStructureStats and UpgradeDie audits retain their
composition and provider/consumer evidence. The publication gate rechecks
current bytes, debt verdicts and affected linking consumers against upstream.

Check log: `build/recovery-20261104-codex3-dry-run.log` (first refusal).
The follow-up gate and publisher logs are under the same build prefix with
`-verified-dry-run.log` and `-publish.log` suffixes.
