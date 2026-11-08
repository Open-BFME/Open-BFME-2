# 595 files sit behind TU approvals, two of them behind 113

Measured 2026-11-08 from `build/merge_all/decisions.json` (written 06:55 at
ea9fac481603) joined against the live `tu_skeleton.py --queue`.

## The finding

The `refused` blocker is only 120 of the 3854 queued decisions, so it looks
like the least interesting of the four. It is not. Of those 120:

- **27** are vendored or SDK sources. Never absorbable, correctly refused.
- **92** are refused for `N row(s) not approved for this TU (only approved rows
  move)`, and **34 of them need exactly one row**.

Those 92 fall across 38 TUs that still have a live queue entry, and **595 files
sit behind them**. Ranked by files freed per approval needed:

| files a merge would remove | approvals needed | TU |
| ---: | ---: | --- |
| **113** | **2** | `GameClient/InGameUI.cpp` |
| 41 | 2 | `W3DDevice/GameClient/BaseHeightMap.cpp` |
| 8 | 1 | `GUICallbacks/Apt/AptMyHero.cpp` |
| 24 | 3 | `GameLogic/Map/TerrainLogic.cpp` |
| 35 | 5 | `GameLogic/Object/Contain/OpenContain.cpp` |
| 126 | 19 | `MilesAudioDevice/MilesAudioManager.cpp` |
| 66 | 11 | `ScriptEngine/Scripts.cpp` |
| 4 | 1 | `ScriptEngine/ScriptConditions.cpp` |
| 43 | 17 | `W3DDevice/GameClient/W3DView.cpp` |
| 1 | 1 | `GUICallbacks/Apt/AptMapPreview.cpp` |

595 files is about 3.8% of the distance between the current 18,021 source files
and the 2,297 TUs `tu_map.csv` names -- available from TU-approval work, with no
merge search and no class reconciliation.

## The three cheapest, with their donors named

| TU | donor holding the unapproved row(s) |
| --- | --- |
| `GameClient/InGameUI.cpp` (113 files, 2 rows) | `GameClient/Rva0029A407Clear.cpp` |
| `W3DDevice/GameClient/BaseHeightMap.cpp` (41 files, 2 rows) | `Common/Rva000677CAHostRva0006DC8E.cpp` (1) and `W3DDevice/GameClient/BaseHeightMapCastRay.cpp` (1) |
| `GUICallbacks/Apt/AptMyHero.cpp` (8 files, 1 row) | `Common/Rva005B01D3Lerp.cpp` |

`InGameUI.cpp` is the one to look at: a single donor file, two rows, and 113
files freed if they are approved and the merge then verifies.

## Why this is worth saying

The four blockers are not comparable by item count, which is how the histogram
presents them. By files behind them:

| files | blocker | what clears it |
| ---: | --- | --- |
| 1490 | blocked-by-classes | header adoption, measured at 2.2% per unit |
| 595 | refused / unapproved rows | TU-evidence work, 1-2 rows for the best TUs |
| 468 | claimed | nothing; it clears itself when the claim lapses |
| 222 | split | a per-case prerequisite each, not a lane |

So `refused` is second by files and first by files-per-unit-of-effort, and it
was the one I nearly skipped because 120 items looked small.

## What this does not say

- Approving a row is **evidence work**, not a mechanical step: it means showing
  the row belongs in that TU (`docs/consolidation.md`, "Retail layout evidence").
  Two rows can be two hard problems. The ratio says where to look, not that it
  is easy.
- `frees` is an upper bound. A merge keeps only the donors that compile together
  without losing a row, and the link guard can still refuse it, so 113 files is
  the ceiling for `InGameUI.cpp`, not a promise. The same caution as in
  `merge-lane-claim-blocking-20261108.md`.
- The decision snapshot is as old as the pass that wrote it; the approval counts
  should be re-read before acting.

## Correction: InGameUI needs a carve, not two approvals

I wrote above that `InGameUI.cpp` is "a single donor file, two rows, and 113
files freed if they are approved". The second half is wrong, and checking the
addresses rather than the ratio says why.

`Rva0029A407Clear.cpp` holds three rows, of two different classes:

| rva | size | class |
| --- | ---: | --- |
| 0x0029A407 | 19B | `Rva0029A407` |
| 0x0029A41A | 28B | `Rva0029A41A` |
| 0x0029B53C | 28B | `Rva0029A407` |

`InGameUI.cpp`'s approved rows run 0x0029A4CA to 0x00775633, and its plan lists
exactly one row of this donor -- 0x0029B53C -- marked `refused (2 row(s) not
approved for this TU)`. The other two sit **below** the TU's first approved row,
and they are not adjacent to it: 0x0029A436 and 0x0029A452
(`GapBodiesGE06.cpp`) and 0x0029A469 (`Rva0029A469.cpp`) lie between them and
0x0029A4CA. Above them sit `ReplayControls.cpp` rows at 0x0029A39C-0x0029A3CE.

So the region is interleaved placeholder territory, and nothing suggests those
two rows are InGameUI's. Approving them *for InGameUI* to unblock the merge
would be asserting layout evidence that points the other way -- the exact thing
TU approval exists to prevent.

The real path is a **carve**: split 0x0029B53C out of `Rva0029A407Clear.cpp`
into `InGameUI.cpp`, leaving the other two rows where they are, as its own
verified commit before the merge. `docs/consolidation.md` is blunt about what
that costs -- each carve needs its own prerequisite retired first and the dry
run names which -- so this is not two approvals, and 113 files is still only a
ceiling.

**What this does to the finding.** The 595-file total stands, and so does the
point that `refused` is second by files and was hiding behind a small item
count. What does not stand is reading "N rows not approved" as "N approvals
away". For each of the 38 TUs the question is first *whether those rows belong
there at all*; where they do not, the work is a carve, which is a different and
usually larger job. The three cheapest entries by ratio should each be checked
the way this one was -- addresses first -- before anyone budgets for them.
