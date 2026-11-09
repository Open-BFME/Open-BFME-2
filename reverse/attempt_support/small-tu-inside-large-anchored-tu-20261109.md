# One structural situation holds 639 donor files: a small hinted TU inside a large anchored TU

Measured at `bd70a8e2ef8`, 2026-11-09. Fourth and last note of the day; it
root-causes `why-29-destinations-are-not-approved-20261109.md`, whose three
verdicts turn out to be three views of one thing.

## The situation

A tiny hinted TU -- often a single row -- sits **inside** a large anchored TU's
address span, and the row physically lives in that anchored TU's source file.
`Object.cpp` is the clearest case:

| | span | size |
| --- | --- | ---: |
| `objectrecoveryhelper.cpp` (candidate, `by=N`, `proposed`) | `0x0028CA4D..0x0028CA92` | **0x45** |
| `object.cpp` (anchored) | `0x0028A670..0x0029A12B` | **0xFABB** |

A 69-byte "translation unit" strictly inside a 64 KB one. The row
(`?GetSnapshotName@ObjectRecoveryHelper@@MBEPBDXZ`) is written in `Object.cpp`.

## The deadlock, in full

1. `tu_skeleton.merge()` refuses `Object.cpp` before weighing any donor: its file
   holds a row the map places in another TU. 208 donor files wait on this.
2. The refusal says "split it first". A split may move a row only into its
   **approved** unit, and `objectrecoveryhelper.cpp` is only `proposed`.
3. It cannot become approved. `provisional()` refuses a candidate whose span an
   anchored TU's reach covers -- condition 3 -- and `object.cpp` covers it.
4. It cannot be absorbed into `object.cpp` either. The `U` union in
   `tu_map.build()` treats two interleaving clusters as one TU, but only when
   **both** spans are at most `UNION_SPAN` (0x2000):

   ```python
   if span[a][1] - span[a][0] > UNION_SPAN or span[b][1] - span[b][0] > UNION_SPAN:
       continue
   ```

   `object.cpp`'s span is 0xFABB, about 32x the limit, so the pair is never even
   considered.

Nothing in the lane can move, and the row is not carvable by a split either way:
`GetSnapshotName` does have a body in `Object.cpp`, so this one is not the
header-COMDAT wall -- it is purely an approval deadlock.

## It is the whole group, not one case

Of the 29 destination TUs behind the merge lane's carvable blockers, **22 sit
inside a covering anchored TU's span, and in all 22 the anchored span exceeds
`UNION_SPAN`** -- by 10x to 40x. The three verdicts of the previous note are three
symptoms of it:

| provisional() verdict | destinations inside a too-large anchored TU |
| --- | ---: |
| OVERLAPS AN ANCHORED TU | 7 |
| SPAN BROKEN | 11 |
| TOO FEW ROWS | 4 |

Counted once per blocked TU: **16 TUs, 639 donor files.**

| donors | blocked TU | its small inside candidate(s) |
| ---: | --- | --- |
| 208 | Object.cpp | objectrecoveryhelper.cpp |
| 109 | AIStates.cpp | aiattackpositionaimattargetstate, aiattackmeleeengagestate, aifollowpathasteamstate |
| 83 | LivingWorldLogic.cpp | attackorders.cpp |
| 42 | ConnectionManager.cpp | bfmeconnectionmanager.cpp |
| 32 | PeerDefs.cpp | gamespyinfo.cpp |
| 32 | PersistentStorageThread.cpp | psplayerallstats.cpp |
| 29 | MapUtil.cpp | playerposition.cpp |
| 27 | PeerThread.cpp | dualindexeddispatchthunk, bfmestagingcreationcrcs |
| 23 | dx8wrapper.cpp | bfmeenumerationdesc, dx8wrapperstagehelper |
| 13 | W3DWater.cpp | waterdrawfxshaderparametersourcenamespace, renderableriverarea |
| 12 | AptDisplayList.cpp | aptpseudodisplaylist.cpp |
| 11 | LivingWorldRegionManager.cpp | livingworldregionbonusrule.cpp |
| 7 | LivingWorldCampaignManager.cpp | livingworldregionmanager.cpp |
| 5 | W3DRoadBuffer.cpp | troadseginfo.cpp |
| 3 | AptScoreScreen.cpp | aptscorescreen.cpp |
| 3 | EAString.cpp | eastringc.cpp |

For scale: 639 of the 1,513 donor files behind the pre-compile blocker, and more
than the 586-file CARVABLE group and the 181-file TOO FEW ROWS group that earlier
notes pointed the lane at. Those two framings were right about what the map says
and wrong about where the cost is.

## The guard is deliberate, and one subset falls outside what it guards against

`UNION_SPAN` is not an oversight. `tu_map.contested()` documents what a wrong
union does: a single row at `0x004A0E47` inside `SupplyCenterDockUpdate`'s span
"merged the whole class into SupplyCenterDockUpdate.cpp, whose span then covered
RepairDockUpdate", and `AIHarvestPrepareSiteState` likewise "stretched AIDock.cpp
across AIHarvest.cpp's `__FILE__` row". The danger is a union **stretching** a
span across a third TU's anchor.

That danger needs the candidate to reach outside the anchored span. Measuring
containment separates the cases:

- **17 of the 22 destinations are strictly contained** -- `anchor_lo <= lo` and
  `hi <= anchor_hi`. Counted once per blocked TU: **12 TUs, 586 donor files.**
  Unioning a strictly contained candidate into its container cannot change the
  container's span at all, so it cannot stretch across anything.
- 5 are only partial overlaps (`gamespyinfo.cpp`, both `eastringc.cpp` spans,
  and the mutually-breaking `livingworldregionmanager` /
  `livingworldregionbonusrule` pair). These are the shape `contested()` warns
  about and should stay refused on this evidence.

That a union is span-safe is not the same as it being *correct*: it would assert
that the hinted class is written in the container's file. For a 69-byte candidate
inside 64 KB that is the likely reading, and it is what the `U` signal's own
comment describes -- "TUs whose small clusters interleave are one TU (one file,
several classes)". But likely is not proven.

## What this does not claim

- **No tool change is proposed and none was made.** Any change here moves
  approvals, so it needs `tu_map.py --validate` at or above the gate and the
  hold-out harness (`--holdout signal-U`, and `--unit row`), on top of a
  maintainer's judgement about the asymmetric case. This note is the measurement
  such a decision would need, not the decision.
- **Not that these 16 merges would succeed.** They have never reached a compile.
  Of 24 carves attempted today 23 refused, several after a clean carve, so an
  approval buys an attempt.
- **Not that the candidates are wrong.** A small TU inside a large one is a real
  possibility -- retail linked some small objects between a big one's
  contributions. Containment says the union would be span-safe, not that the
  class lives in the container.
- **Not a claim about the other 1,373 proposed TUs.** Only the 29 destinations
  that would unblock a merge were measured.

## Corrections this note makes to my own earlier ones today

- `why-29-destinations-are-not-approved-20261109.md` called TOO FEW ROWS "the one
  mechanical subset" and said one more named row "tips it over". That is too
  optimistic. 6 of its 9 destinations hold **a single row, full stop**, and 3
  hold one real function plus its EH funclets, which never count toward
  `PROV_MIN` because `P` is not in `APPROVABLE` -- `manthewallsspecialpowerslotview.cpp`
  has nine rows and counts one. A second row must genuinely belong to the file;
  reaching `PROV_MIN` by naming something that does not would be fabricating
  evidence.
- A hypothesis of mine that this group was an artifact of `N` deriving `<dir>`
  from each row's current file was tested and dropped: only 2 of the 9 have a
  sibling TU key of the same basename, and neither sibling holds the missing
  rows.
- `merge-blocker-remedy-is-unreachable-20261109.md` pointed the lane at
  `siegeenginecontain.cpp` as "best-evidenced" because of its 4 WorldBuilder
  leads. Those leads' two addresses (`0x0047BBA7`, `0x0047C07F`) are **already
  approved** into `HordeSiegeEngineContain.cpp` by `U`, so they are not available
  to raise its count, and the leads do not help.

## Method

`tu_map.provisional()` was wrapped to capture the real `assigned` (35,134 rows),
`roots` (723 anchored TUs) and `lo_hi` (2,289 spans) from `tu_map.build()`, which
had to be called directly because `current_rows()` serves rebuilds from the
shared picker cache. Spans, containment and the `UNION_SPAN` comparison are read
straight off that state; `UNION_SPAN` and `PROV_MIN` are read from the module
rather than copied. Donor files are counted once per blocked TU -- an earlier
run of this same diagnosis summed a TU once per destination, which triple-counted
`AIStates.cpp`.
