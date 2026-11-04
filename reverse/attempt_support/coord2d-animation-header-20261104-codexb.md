# Coord2D animation header adoption, 2026-11-04

Base: `132c321fb8`. Scope: LINK-098's animation class-key prerequisite and
the already-adopted AIStatesSmallUpdates header-queue row.

## Target facts and source change

The existing getVel body at RVA `0x005C5046` returns the two floats at
AnimateWindow offsets `+0x2C/+0x30` through a hidden result pointer. Its
private Coord2D copy constructor is replaced by the existing registered
header's accepted companion, `Coord2DCtorView.h`. The RightFast unit uses
that same companion with its existing empty-destructor switch. No shared
header or compiler flags change.

ProcessAnimateWindow and AnimateWindowManager use the canonical POD header,
keeping their original POD operations. SlideLeftUpdate and SlideTopUpdate
include that header and retain their existing typed hidden-output calls.
The real getVel, setVel and setAnimData ledger names change only the Coord2D
class key (`U` to `V`). The ICoord2D argument keys are unchanged. No pin,
alias, additional body or address changes. The header tool's dependency
discovery requires the complete six-unit animation group and accepts it.

This does not establish any new donor name, layout or translation-unit path.
AIStatesSmallUpdates already includes Coord2D.h and has no source change;
its earlier link refusal does not reproduce with the fetched current index.

## Verification and debt retirement

Before changes, `./build.sh` passes 49/49 rows for the five animation
consumer/provider units plus AIStatesSmallUpdates, and 40/40 rows for
AnimateWindowManager. After the coordinated class-key change it passes
82/82 rows across the six animation units. The final owning-tool acceptance
also rebuilds all six, including both slides after their include changes.
All six final `find_declared_unmatched.py` checks pass. `check_csv.py` passes
with 99,433 function, 9,341 symbol and 2,269 data rows.

`header_adopt_lane.py accept --class Coord2D` passes the six animation
sources together and initially retires two rows. The pre-commit debt check
refuses that retirement: its preview contains only sources whose queue rows
are removed, omitting the debt-free AnimateWindowManager provider. RightFast
then loses its census-linked bytes because the index still exports the old
`setAnimData` class key. This is a debt-verifier cohort boundary, not a byte
failure. Both animation queue rows are restored, and the false rejection is
recorded through `re_log.py` at setVel's `0x005C5058..0x005C5069` boundary.
Retire those rows through the owning tool after the scheduled census includes
the coordinated providers, or after a separately verified checker repair.

The separate acceptance of AIStatesSmallUpdates passes and retires one row.
This is the only final header-queue removal. The same earlier boundary held
AI's row open until its coordinated providers reached the current index
(prior attempt at RVA `0x0034F01B` in `reverse/re_attempts.log`).

The before and final ordinary link previews against fetched census index
`5a13f2cd61` (2026-11-04 02:25) preserve all seven LINKS results:

| Source basename | Authored bytes before -> after |
| --- | ---: |
| AnimateWindowGetVel.cpp | 18 -> 18 |
| ProcessAnimateWindowRightFastInitReverse.cpp | 2,816 -> 2,816 |
| ProcessAnimateWindow.cpp | 1,873 -> 1,873 |
| SlideLeftUpdate.cpp | 456 -> 456 |
| SlideTopUpdate.cpp | 466 -> 466 |
| AnimateWindowManager.cpp | 1,817 -> 1,817 |
| AIStatesSmallUpdates.cpp | 619 -> 619 |

Total preview scope: 8,065 -> 8,065 authored bytes. This clears only the
animation source class-key/header prerequisite and AI's obsolete acceptance
refusal; animation debt retirement awaits the verification boundary above.
Rva00062B17Init's historical queue-identity boundary remains open. Carry the
changed symbol providers and consumers into the next scheduled census;
ordinary previews establish no new census-linked coverage or real-link result.

Local detailed logs: `build/codexb-coord2d/{before-build,manager-before-build,
cohort-build,accept-cohort,accept-ai,before-link,manager-before-link,final-link,
single-rightfast-link}.log`.
