# Preserved-batch recovery audit, 2026-11-04

## Saved work and conflict resolution

Preparation backup: `refs/runner/preparation/1793831457941446872`.
The preparation record was in `syncing` phase at upstream `3a95b274a2`,
with no `stash` or `resyncStash`. Its five saved commits are accounted for:

- Destructor declaration prerequisite `b5c4a55dba` already exists upstream as
  `f3bc7ff782`; both have stable patch ID
  `fd206533279c71f38c567b168d4b423675acae38`. The runner omitted this replay.
- The destructor merge, scoped naming, WorldHeightMap adoption and CashHack
  consumer adoption replayed successfully. Source comment conflicts retain
  upstream wording. The WorldHeightMap obstacle note retains upstream text
  first, followed by this seat's original text without rewording.

No saved edit was discarded. The backup ref and unrelated October 27 stash
`b1db0a09c4` remain intact; that stash is not named by this preparation record
and was not applied. The restored working tree had no untracked files.

## Current checks and source-path audit

`python3 tools/check_csv.py` passes. All definitions in the three changed
source files are matched. `git diff --check` passes.

`BFME_PUSH_SPACING_S=0 python3 tools/push.py --dry-run` passed the pre-push
hook and author/committer check. The hook verified 35/35 function rows,
three string literals, 26 float literals, three EXACT EH graphs and eleven
converged data addresses. Protected hatch-key transfer and debt-removal
checks passed. No new census, real link or runtime smoke result is claimed.

The complete outgoing path-change audit was repeated after recovery. The sole
removed source is RainOfFireUpdateDtor.cpp, absorbed by RainOfFireUpdate.cpp.
Searches in tools, hooks, workflows, source/header includes, configuration and
registries find no active consumer of the old path. Remaining mentions are
the destination's provenance comment, historical ledger notes and attempt
support, the historical LINK-168 repair note, and census-owned link_status.csv.
The existing link-wide alternatename remains in the destination; none was
removed. No new source-path move was introduced during recovery.

## Link-audit boundary for the next scheduled census

The dry-run hook initially found no strict current receipt for the three
edited providers. The supported follow-up command succeeds:

```text
python3 tools/link_check.py --prepare-current \
  Code/GameEngine/Source/Common/Rva002CD169Ctor.cpp \
  Code/GameEngine/Source/GameLogic/Object/Update/RainOfFireUpdate.cpp \
  Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapCellQueries.cpp
```

It verifies all 35 rows and records strict reusable receipts for all three
providers, without changing census/index/status. The subsequent
`link_batch_audit.py` check of base `b9fe466f66` through tip `2123c241ed`
(the publisher's rebased four-commit batch) returns 2, INCONCLUSIVE:

```text
link batch audit: INCONCLUSIVE baseline: index at 2f0cb97f52, outgoing base b9fe466f66fd8ae5ecad68316010c4188244bbea; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```

Carry the three changed providers, the absorbed destructor and their consumers
into the next scheduled census. The broader selected-provider and consumer
loss audit remains unverified; passing byte/debt hooks and current provider
receipts do not close it. Existing constructor, mixed-source and other
header-adoption prerequisites remain as recorded in the family entries.

## Publication

`/opt/runner/publish --now` confirmed `publish: pushed`. The four recovered
commits landed as `76aea367ce` (destructor merge), `1ffc984d74` (scoped names),
`95e586d56c` (WorldHeightMap consumer) and `aceff5a538` (CashHack consumer).
The checkout then synchronized cleanly with origin/master. No new task was
selected during this recovery.
