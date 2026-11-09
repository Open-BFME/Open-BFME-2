# --merge-all with a small --jobs spends its whole budget on the largest TU

Measured 2026-11-08, with the third targeted verdict read 2026-11-09. Four
merges were run: one `--merge-all --jobs 1 --budget-min 120` sweep and three
targeted `--merge TU` calls.

> **The yield conclusion in this note is superseded. Read this first.**
>
> Every merge here ran before `11de2a4ea56` ("tu_skeleton: try the seed's flags
> first, and stop a set whose seed is rejected", 2026-11-09 01:31). That commit
> says plainly: *"This can make merges possible that the old search could not
> reach, not only faster... The old search's results are not an upper bound."*
> Hours later `f905dceb3f1` merged **41 donors** into `Player.cpp` under the new
> search -- twenty times the best result recorded here.
>
> So "0-2 donors regardless of TU size" was a property of the old flag search,
> not of the lane, and must not be used to price merge work. What survives is the
> scheduling argument (unchanged: most-donors-first still opens a `--jobs 1` run
> on the largest entry), the claim-release lesson, and the rejection anatomy as a
> snapshot of where the old search stopped. The measured figures are left as
> recorded; only their interpretation is withdrawn.
>
> **One control was re-run.** `ai.cpp --dry-run` on the new search
> (`1650aa94c47`, 2026-11-09) returned **the same verdict**: 0 accepted, 26
> rejected, 9 mixed, `blocked: no verified merge of two or more donors`, and the
> same 23 classes in `reconcile_classes`. So the flag search is not what stops
> `ai.cpp`; its wall is genuine private-view reconciliation. The tool change
> raises the ceiling on some TUs (`Player.cpp`) and not on others (`ai.cpp`),
> which is exactly why the old numbers cannot be generalised in either
> direction.

## What happened

`--merge-all` takes the queue **most donors first**, so a `--jobs 1` run opens
on the largest entry. That was
`Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp`: 316 donor
files, 713 rows, 16 mixed, 0 refused.

It ran for **2 hours 45 minutes** on one core, produced no output at all (its
`log=print` default is block-buffered, so silence carries no information), held
**1023 scope claims** the whole time, and was stopped before it finished.
Nothing was written; the worker worktree produced no commit. Its claims were
released by hand in batches afterwards and the abandoned composition scratch
file removed.

Meanwhile three targeted merges of mid-queue TUs returned verdicts in well under
an hour each:

| TU | queue entry | approved rows | donors offered | accepted | outcome |
| --- | --- | ---: | ---: | ---: | --- |
| `Common/RTS/Team.cpp` | 44 files | 388 | 55 | **2** | merged, landed |
| `GameLogic/AI/ai.cpp` | 26 files | 163 | 35 | 0 | blocked, nothing written |
| `Common/RTS/ScoreKeeper.cpp` | 44 files | 112 | 44 | 0 | blocked, nothing written |

Three verdicts, **2 donors accepted out of 134 offered** (1.5%). None of the
three came within an order of magnitude of its own queue entry. "Donors offered"
counts every candidate the merge weighed -- accepted plus rejected plus mixed
plus refused -- and is larger than the queue entry's file count because a mixed
donor stays a satellite rather than being removed.

## Two independent walls, not one

`ScoreKeeper.cpp`'s 35 rejections are worth keeping because they split cleanly,
and only half of them are the wall the reconcile hint names:

| donors | rejection |
| ---: | --- |
| 19 | compile: a private view or a member the TU's own class body lacks (`C2011` type redefinition, `C2039`/`C2065` not a member, `C3855` `BitFlags` NUMBITS mismatch) |
| 13 | **byte mismatch** -- the donor compiles inside the merged TU and produces different bytes |
| 1 | link guard: merged object would lose a selected `_Rb_tree::insert_unique` COMDAT |
| 1 | flag override `-O1` costs the TU file 2 rows its region default matches |
| 1 | `C1001` internal compiler error |

The 19 are the documented wall, and `tu_views.py` plus header adoption is the
path through them. **The 13 are a second wall that no amount of view
reconciliation touches**: those donors already compile in the composition and
still miss retail's bytes, because the TU's own include set and flag region give
the compiler a different context than the donor's single-function file did. The
TU's `adopt_first` hint names only 3 donors and 4 classes, so it does not
describe the other 32 at all.

That matters for estimating the lane. If a view-reconciliation pass cleared all
19 of `ScoreKeeper.cpp`'s view failures, 13 byte mismatches plus 3 other refusals
would remain, and the ceiling on that TU would be 19 of 44 donors -- not 44. The
byte-mismatch share is unmeasured across the queue; this is one TU where it is
41% of the compilable donors.

## Why the budget was misspent, with the arithmetic

The point is not that `ScriptActions.cpp` is slow. It is that its **expected
yield is no larger than a small TU's.**

`Team.cpp` succeeded, and accepted **2 of its donors** -- removing one file
against a queue entry advertising 44. The merge search accepts a donor only if
the TU still compiles and no baseline row is lost, and the wall is private class
views: its reconcile hint named 20+ classes the donors declare for themselves.
There is no reason a 316-donor TU clears that wall more often than a 44-donor
one; it simply has more donors to try, so the search is longer while the
accepted set stays small.

So the realistic prize on `ScriptActions.cpp` was likely one to five files, the
same as `Team.cpp`, for a search cost perhaps an order of magnitude greater and
1023 claims held across it. The queue's `files` column reads like the prize and
is not: it is the count a *complete* merge would remove, and no merge measured
today came close to its own column.

**This paragraph's inference does not survive `11de2a4ea56`** (see the notice at
the top). Under the new flag search `Player.cpp` accepted 41 donors, so "a large
TU clears the wall no more often than a small one" is not a safe generalisation.
What stands without it: a `--jobs 1` sweep on a 316-donor entry held 1023 claims
for 2h45m and wrote nothing, and the same wall-clock spent on targeted merges
returned three verdicts and landed one merge.

## What to do instead

- **Run targeted `--merge TU` on mid-queue entries**, not `--merge-all` with a
  small `--jobs`. Each returns a real verdict in under an hour and lands
  independently.
- If `--merge-all` is used, give it `--jobs N` so the giant does not occupy the
  only worker, and expect the first wave to be the longest.
- **Judge a TU by donors likely to be accepted, not by its file count.** The
  queue's `files` column is what a *complete* merge would remove, and no merge
  here came near its own column. ~~three data points put it at 0-2 regardless of
  TU size~~ -- withdrawn: that was the old flag search. `Player.cpp` took 41
  donors under the new one.
- **Price a TU's view-reconciliation work against its byte mismatches too.**
  Clearing the views raises a TU's ceiling to its compilable donors, not to its
  donor count; on `ScoreKeeper.cpp` under the old search that ceiling was 19 of
  44. Whether the new flag search moves byte mismatches as well as compile
  failures is not measured here -- it plausibly does, since flags decide bytes.
- A claimed-scope sweep that is going to be abandoned should be stopped
  deliberately rather than left to a `timeout`, so its claims can be released;
  1023 claims otherwise sit for the full four hours.

## Caveats

- One abandoned sweep is not proof the merge would have failed. It may have
  been minutes from accepting a large set.
- Three targeted merges is a small sample, they disagree (one merged, two
  blocked), and all three are mid-queue TUs in `Common/` and `GameLogic/`;
  nothing here measures the `Code/Libraries/` or device trees.
- **The decisive caveat, found a day later:** all four runs used the pre-
  `11de2a4ea56` flag search, whose author states its results are not an upper
  bound. Treating these numbers as the lane's yield was wrong. The general
  lesson is the one that keeps recurring in this lane: a measurement of a tool
  is only valid for that tool's revision, so record the revision and check it
  before reusing the number.
- The byte-mismatch share is measured on **one** TU. It may be unusually high
  there: `ScoreKeeper.cpp`'s donors are heavy on STL container instantiations
  (`Rva0039B*` fill/copy/count helpers), which are exactly the bodies most
  sensitive to a TU's include set. Treat 41% as a reason to measure the share
  queue-wide, not as the queue-wide figure.
- `--merge-all`'s ordering is defensible on its own terms: most donors first is
  the right order if acceptance rates were uniform. The measurement here is that
  they are not, in a way that makes the ordering expensive.
