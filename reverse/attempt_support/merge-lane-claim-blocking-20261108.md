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
