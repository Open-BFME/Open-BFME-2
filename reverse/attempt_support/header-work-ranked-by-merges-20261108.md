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

## Crossed with the queue's live rows

The ranking above says what a class costs the merge lane. It does not say how
much work the class is. Crossing it with the header queue's *live* rows -- the
6275 whose unit still declares a private body, per
`header-queue-prediction-20261108.tsv` -- gives both at once. 445 classes have
live rows; 250 of those also block a merge:

| class | live rows | donors held | TUs |
| --- | ---: | ---: | ---: |
| UpdateModule | 73 | 34 | 33 |
| Player | 221 | 52 | 21 |
| Thing | 82 | 27 | 19 |
| Drawable | 111 | 22 | 18 |
| AIUpdateInterface | 197 | 24 | 17 |
| BehaviorModule | 48 | 16 | 15 |
| Matrix3D | 53 | 15 | 15 |
| Vector3 | 72 | 18 | 15 |
| ContainModuleInterface | 51 | 12 | 12 |
| Overridable | 28 | 12 | 11 |
| AICommandInterface | 81 | 11 | 10 |
| ModuleData | 44 | 10 | 10 |
| UpgradeMux | 17 | 16 | 10 |
| TerrainLogic | 61 | 32 | 9 |
| ThingTemplate | 86 | 21 | 9 |
| UpdateModuleInterface | 25 | 9 | 9 |
| DX8Wrapper | 91 | 11 | 8 |
| RenderObjClass | 77 | 15 | 8 |

`UpdateModule` is the pick: the widest reach in the lane (33 TUs) for the
smallest body of work among the wide ones (73 rows), and the three classes
beside it in the module hierarchy -- `UpdateModuleInterface` 25 rows / 9 TUs,
`BehaviorModule` 48 / 15, `BehaviorModuleInterface` 26 / 8 -- are the same
adoption done once. `UpgradeMux` is the cheapest entry outright: 17 live rows
reaching 10 TUs.

`Player` and `AIUpdateInterface` carry the most work by far (221 and 197 rows)
for narrower reach, and `Player` was already held by another seat for it.

Beware reading this as a work estimate. A live row means the unit still declares
a private view, not that adopting the header will succeed there; the measured
pass rate on a declaration-only sample was about one in twelve
(`header-lane-vptr-standin-20261107.md`). The columns rank candidates; they do
not predict yield.

## Priced: what a header change costs, per class

A change to a canonical header re-verifies every ledger source that reaches it.
Counted with `header_dependents` for every class above with 7 or more TUs of
merge reach (no compiling; full table in `header-gate-costs-20261108.tsv`):

| class | live rows | TUs | sources re-verified |
| --- | ---: | ---: | ---: |
| RTS3DScene | 28 | 7 | **20** |
| ModelConditionFlags | 52 | 8 | **23** |
| DrawModule | 29 | 7 | 47 |
| UpgradeMux | 15 | 10 | 71 |
| ContainModuleInterface | 51 | 12 | 73 |
| Rva0036CA00Str | 34 | 7 | 85 |
| DX8Wrapper | 91 | 8 | 117 |
| GameWindow | 62 | 7 | 238 |
| Vector3 | 72 | 15 | 241 |
| ModuleData | 44 | 10 | 292 |
| RenderObjClass | 77 | 8 | 296 |
| AICommandInterface / AIUpdateInterface | 81 / 197 | 10 / 17 | 404 |
| Player / ThingTemplate | 221 / 86 | 21 / 9 | 475 |
| TerrainLogic | 61 | 9 | 635 |
| Drawable | 111 | 18 | 702 |
| Thing | 82 | 19 | 1728 |
| DamageInfo / GeometryInfo | 32 / 29 | 7 / 7 | 1753 |
| Overridable | 28 | 11 | 1774 |
| UpdateModule / UpdateModuleInterface | 73 / 25 | 33 / 9 | 1796 |
| Matrix3D | 53 | 15 | 1863 |
| BehaviorModule / BehaviorModuleInterface | 48 / 26 | 15 / 8 | 1925 |
| AudioManager | 62 | 7 | 2234 |

A spread of about 100 to 1.

### This prices one lane, not both

The distinction matters and the table is misleading without it.

- **Adopting a header in a unit changes only that unit.** No cascade, no full
  gate. The cost of probing is one compile per unit, and this column is
  irrelevant to it.
- **Changing the canonical header itself** -- the contract-to-header work in
  `header-missing-field-rows-anatomised-20261108.md` -- pays this column, once,
  and unblocks every row of that class that the missing field was holding.

So read it only when the plan is to edit a header.

### What it changes about the pick

`UpdateModule` was my pick above on reach alone. It is the joint most expensive
header here (1796) and also the broadest (33 TUs) -- a real tension, not a
mistake, but no seat should edit that header casually.

The classes that are cheap *and* carry rows are the ones to look at for a header
fix: `ModelConditionFlags` 52 rows for 23 sources, `RTS3DScene` 28 for 20,
`DrawModule` 29 for 47, `ContainModuleInterface` 51 for 73. None of those is in
the top of the reach ranking, which is the point.

It also says where I spent compute badly. I probed `Thing` (82 units, 0 passes)
and `Drawable` (108 units, 1 pass), which price at 1728 and 702, and left
`ModelConditionFlags` and `RTS3DScene` unprobed. Probing does not pay the gate
cost, so that was not the wrong spend for the reason the table gives -- but the
two cheap classes are better targets for the lane that follows probing, and they
were in front of me unmeasured.
