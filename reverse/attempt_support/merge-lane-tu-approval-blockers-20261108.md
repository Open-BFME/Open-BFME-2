# TU approval is not a cheap merge lever: 92 files, and 37 of 38 TUs need more

Measured 2026-11-08 from `build/merge_all/decisions.json` (written 06:55 at
ea9fac481603). This note began as a much bigger claim; the arithmetic that
produced it was wrong and the correction is the useful part, so it is kept at
the bottom.

## What the refused blocker is

`--merge-all` leaves 3854 ranked decisions behind, with this histogram:

| items | files | blocker |
| ---: | ---: | --- |
| 2218 | 222 | split |
| 1490 | 1490 | blocked-by-classes |
|  120 | 120 | refused |
|   26 | 468 | claimed |

The 120 refused break down as:

- **27** vendored or SDK sources. Never absorbable, correctly refused.
- **92** refused for `N row(s) not approved for this TU (only approved rows
  move)`, spread over 38 TUs. **34** of the 92 need exactly one row.

A refused item is one donor file, and it frees one file. So the work behind
unapproved rows is **92 files**, not more.

## And approval is rarely the only thing in the way

Of the 38 TUs carrying an unapproved-row refusal, grouped by every blocker kind
they carry:

| TUs | blockers on that TU |
| ---: | --- |
| 30 | blocked-by-classes + refused + split |
|  6 | refused + split |
|  1 | blocked-by-classes + refused |
|  1 | refused only |

The one TU blocked by nothing but unapproved rows is
`Code/Libraries/Source/WWVegas/WW3D2/AnimationAsset.cpp`: **5 rows to approve,
and its queue entry removes 1 file.**

So TU approval is not a standalone lever in this lane. For 37 of 38 TUs it is
one prerequisite among two or three, and clearing it alone moves no file count.

## The InGameUI case, worked

Worth keeping because it shows the second trap. `InGameUI.cpp` has the largest
queue entry of any TU carrying an approval refusal, and its refusal names a
single donor with two unapproved rows -- which reads like two approvals for a
very large merge. It is not.

`Rva0029A407Clear.cpp` holds three rows, of two different classes:

| rva | size | class |
| --- | ---: | --- |
| 0x0029A407 | 19B | `Rva0029A407` |
| 0x0029A41A | 28B | `Rva0029A41A` |
| 0x0029B53C | 28B | `Rva0029A407` |

`InGameUI.cpp`'s approved rows run 0x0029A4CA to 0x00775633, and its plan lists
exactly one row of this donor -- 0x0029B53C -- marked `refused (2 row(s) not
approved for this TU)`. The other two sit **below** the TU's first approved row
and are not adjacent to it: 0x0029A436 and 0x0029A452 (`GapBodiesGE06.cpp`) and
0x0029A469 (`Rva0029A469.cpp`) lie between them and 0x0029A4CA, and
`ReplayControls.cpp` rows sit above at 0x0029A39C-0x0029A3CE.

The region is interleaved placeholder territory and nothing suggests those two
rows are InGameUI's. Approving them *for InGameUI* to unblock a merge would be
asserting layout evidence that points the other way -- the exact thing TU
approval exists to prevent. The real path is a carve of 0x0029B53C into
`InGameUI.cpp`, as its own verified commit, and `docs/consolidation.md` is blunt
that each carve needs its own prerequisite retired first.

`InGameUI.cpp` also carries blocked-by-classes and split items, so the carve is
not the last thing in its way either.

## How the figure was wrong, and the lesson

The first version of this note said **595 files** sat behind TU approvals and
called `refused` the lane's best files-per-effort blocker. That came from
joining each TU's *whole queue entry* (how many files a complete merge of it
would remove) to the approval refusals *on* that TU. Those are different
quantities: a refused item is one donor and frees one file, while a TU's queue
entry counts all its donors, most of which are blocked by something else
entirely.

The histogram says so directly -- `refused 120 items, 120 files` -- and I had
that number in front of me while computing 595 from the other direction.

Two rules worth carrying:

1. **Attribute a blocker's cost at the blocker's own granularity.** Per-donor
   blockers (`refused`, `blocked-by-classes`, frees 1 each) cannot be priced
   against whole-TU totals. Only `claimed` items carry a TU-level `frees`, which
   is why 26 of them account for 468 files.
2. **Check the TU's other blockers before calling one of them the lever.**
   Clearing the only blocker you measured frees nothing if two more remain, and
   37 of these 38 TUs have more.

`merge-lane-claim-blocking-20261108.md` was checked against both rules and
stands: its figures come from `claimed` items' own `frees`, which is TU-level,
and it already states that `frees` is an upper bound twice over. Its TUs do
carry `split` items as well, but those are the mixed donors that stay satellites
rather than blocking the merge, which is what `frees` being an upper bound
already accounts for.
