# Which classes block the most merges

Measured 2026-11-08 from `build/merge_all/decisions.json` at ea9fac481603, the
ranked decision queue a `--merge-all` pass leaves behind.

## Why rank this way

`tools/tu_skeleton.py --merge-all --dry-run --static` puts 493 TUs in the queue
and four blockers in front of them:

| items | files freed | blocker |
| ---: | ---: | --- |
| 2218 | 222 | split |
| 1490 | 1490 | blocked-by-classes |
|  120 | 120 | refused |
|   26 | 468 | claimed |

`blocked-by-classes` is the only one whose items free a file each, and it is the
one the header tier serves. The header queue's own order (`header_adopt_lane.py
order`) ranks by dependency stage, not by what a class costs the merge lane, so
the same work can be ranked by how many merge donors it holds up.

Each `blocked-by-classes` item carries the classes whose private views disagree
in that TU. Counting the items a class appears in, and the distinct TUs behind
them:

| class | donors held | TUs |
| --- | ---: | ---: |
| Object | 188 | 27 |
| ScriptActions | 85 | 2 |
| Player | 52 | 21 |
| MilesAudioManager | 42 | 1 |
| InGameUI | 37 | 5 |
| UpdateModule | 34 | 33 |
| TerrainLogic | 32 | 9 |
| OpenContain | 29 | 5 |
| Thing | 27 | 19 |
| W3DView | 27 | 1 |
| SpawnBehavior | 27 | 1 |
| Pathfinder | 26 | 3 |
| ScriptEngine | 25 | 3 |
| AIUpdateInterface | 24 | 17 |
| AudioManager | 22 | 7 |
| Drawable | 22 | 18 |

1490 items name 784 distinct classes in all, so the tail is long; these sixteen
account for a disproportionate share of it.

## Reading it

Two different shapes hide in the same column, and they are worth different work:

- **Deep and narrow.** `ScriptActions` 85 donors in 2 TUs, `MilesAudioManager`
  42 in 1, `W3DView` 27 in 1, `SpawnBehavior` 27 in 1. All the value is in one
  merge. Reconciling that class only pays if its TU then merges, so it belongs
  to that TU's own pass (`tu_views.py TU`), not to a header batch.
- **Broad.** `UpdateModule` 34 donors across **33** TUs, `Thing` 27 across 19,
  `Drawable` 22 across 18, `AIUpdateInterface` 24 across 17, `Vector3` 18
  across 15, `BehaviorModule` 16 across 15. One canonical header moves many
  independent merges, and none of them has to succeed for the next to be worth
  trying. This is the shape a header batch should pick.

`Object` is both: 188 donors over 27 TUs, the largest number in either column.

## Caveats

- The reasons say "header lane ranking; not compiled". A class listed against a
  donor is a view disagreement the static ranking found, not a compiler verdict,
  so the count is what the lane *believes* blocks the merge.
- `frees` is 1 on these items, so files-freed does not separate them; the donor
  count does.
- The snapshot is as old as the last `--merge-all` pass that wrote it
  (`measured_at` names the commit). Re-read it rather than trusting this table
  after a wave lands.
- `class:Player` was held by another seat for exactly this work (25 header-queue
  rows) when this was measured, which is the right seat for the #3 entry.

## Where the vptr fix lands in this

`UpdateModule` is the broadest-reach blocker here, and it is also the class that
accounted for 26 of the 113 queue rows the vftable-pointer refusal was blocking
(`header-lane-vptr-standin-20261107.md`). So that fix was in the right place by
this ranking too, which the yield measurement alone did not show.
