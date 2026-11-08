# One expired claim can hold a whole TU's merge

Measured 2026-11-08 from `build/merge_all/decisions.json` (written 06:55 at
ea9fac481603) against the live claim table a few hours later.

## What the decision queue says

`--merge-all` skips any TU whose scope another seat claims, and records it as
`claimed`. There are 26 such items, and **468 files sit behind them** -- the
second largest file count of the four blockers, behind `blocked-by-classes`
(1490) and well ahead of `split` (222) and `refused` (120).

The skip is per TU, not per donor. A TU is set aside when *any* of its files is
held, so the cost of one claim is the whole merge:

| files behind it | TU | files held when measured |
| ---: | --- | ---: |
| 157 | `Common/RTS/Player.cpp` | 8 |
|  65 | `GameLogic/Object/Weapon.cpp` | 8 |
|  58 | `GameClient/Drawable.cpp` | **1** |
|  44 | `Common/RTS/Team.cpp` | **1** |
|  35 | `Common/RTS/ScoreKeeper.cpp` | **1** |
|  26 | `GameLogic/AI/ai.cpp` | **1** |
|  15 | `Common/System/Upgrade.cpp` | **1** |
|  11 | `GameLogic/Object/Update/StealthUpdate.cpp` | **1** |

So 189 of the 468 files were behind a single held donor each.

## All six single-donor claims had expired

Claims last four hours. Re-checking the six holders against `claims.py list`
after the snapshot was written:

    Drawable_rva00273755.cpp            free
    Team.cpp                            free
    ScoreKeeperDoXfer.cpp               free
    AIObjectTargetPredicate.cpp         free
    UpgradeCenterCanAffordUpgrade.cpp   free
    StealthUpdate.cpp                   free

None is held now. Those six merges were not blocked by anything in the tree;
they were blocked by where another seat happened to be working at 06:55, and
that passed.

## What follows

- **A `claimed` item is the cheapest kind of blocker, and the only one that
  clears by itself.** A seat picking merge targets should re-read the claim
  table rather than the `claimed` rows of a decision snapshot, which record
  where the fleet was, not where it is.
- **`--merge-all` ordering spends the budget on the wrong end.** It takes the
  queue most-donors-first, so a run opens on the largest TU
  (`ScriptActions.cpp`, 316 donors) and accretes 316 donors with bisecting
  compiles before reaching anything else. With `--jobs 1` and a 120-minute
  budget that can be the entire run. The 189 files above are six ordinary
  `--merge TU` calls.
- The per-TU skip is defensible -- a merge writes the TU and deletes every
  absorbed donor, so it needs all of them -- but the cost of it is worth
  knowing: a claim on one one-function file is a claim on its TU's whole merge.
  Releasing scope claims promptly after a push
  (`claims.py release file:<path>`) is worth more than it looks.

## Caveat

Reading `frees` from a snapshot is reading an upper bound twice over: it was an
upper bound when written (the merge keeps only donors that compile together
without losing a row) and the tree has moved since. These eight TUs are
candidates to try, not 468 files in hand.

## Correction (2026-11-08, same day): a claim hides the real blocker

This note said the six single-donor TUs "were not blocked by anything in the
tree; they were blocked by where another seat happened to be working at 06:55,
and that passed". That is wrong, and running one of them says so.

`ai.cpp` was in the list: 26 files, 159 rows, one held donor at snapshot time,
free by the time I checked. `BFME_CLAIM_OWNER=... tu_skeleton.py --merge
Code/GameEngine/Source/GameLogic/AI/ai.cpp` with the claim gone:

    approved: 163
    mixed:    9 donors
    refused:  {}
    accepted: []
    rejected: 35 donors
    blocked:  no verified merge of two or more donors

Every donor was rejected at the compiler, 19 of them with
`error C2953: 'StringBase' : template class has already been defined`, and 39
of the messages name `reference/shims/bfme2_ascii/string_base.h`. Nothing was
written and the merge released its own claims.

That header is not missing a guard -- it has `#pragma once` on line 1. It is
*macro-configured*: `BFME_SB_CLEAR_DECL`,
`BFME_STRINGBASE_PUBLIC_DEFAULT_CTOR`, `BFME_STRINGBASE_PUBLIC_COPY` and
`BFME_STRINGBASE_PUBLIC_DTOR` each change which members the class exposes, and
donors define different sets before including it. Two donors therefore need two
differently shaped `StringBase` definitions in one unit. That is the spelling
conflict documented in `docs/consolidation.md` ("Spelling conflicts: the
mechanical half of blocked-by-classes", 2026-11-03), and that section's own
follow-up ("Sharing views does not move the merge", 2026-11-04) reports the
`tu_views` path does not clear this category.

### The general mistake, stated once

`--merge-all` skips a claimed TU **before compiling it**. So a `claimed`
decision is the *first* reason the TU was set aside, not the only one, and the
snapshot cannot know what the compiler would have said. For `ai.cpp` the
snapshot recorded `claimed` and `split` and no `blocked-by-classes` -- because
it never got far enough to find out.

This is the third time in one session that reading the decision queue as a
work-availability list has misled me, each in a different way:

1. Counting per-donor blockers against whole-TU file totals, which turned 92
   files into 595 (`merge-lane-tu-approval-blockers-20261108.md`).
2. Treating one measured blocker as the only one, when 37 of 38 TUs had more
   (same note).
3. Treating a `claimed` TU as otherwise ready, when the claim is recorded
   *instead of* compiling it (here).

The queue is a record of why work stopped, not an estimate of what work is
available. Every `frees` figure in it is an upper bound on an upper bound, and
the only way to price one of these TUs is to run its merge.

**What still stands:** claims do expire and a claimed TU is worth *re-running*
rather than reasoning about -- the run costs one merge search and returns a real
verdict. Releasing scope claims promptly after a push still matters. What does
not stand is any reading of 468 or 189 as files in reach.
