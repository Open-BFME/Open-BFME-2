# The header lane refused 113 units over pointers the compiler supplies

Measured 2026-11-07 against `reverse/header_queue.tsv` at 7fd11cc6a27 (6721 rows).

## Where the lane's failures sit

Grouping every queue row by its recorded failure:

| rows | failure |
| ---: | --- |
| 3083 | field renames |
|  822 | byte gate (FAIL) |
|  706 | compile C2039 |
|  250 | manual header |
| ~1860 | the rest (118 pending canonical, 106 pending byte/link, other compile codes) |

The 3083 field-rename rows break down further:

| rows | kind |
| ---: | --- |
| 1062 | a private field has no canonical field of that offset and size |
|  741 | other |
|  689 | the header's layout did not compile |
|  397 | the two disagree on the field's type at the same offset |
|   83 | include cycle |
|   50 | the unit's layout did not compile |
|   33 | anonymous nested struct |
|   28 | line splice or trigraph |

The 1062 "no canonical field" rows name 732 distinct slots, so they are a long
tail rather than a few shared gaps -- with one exception.

## The exception: a vftable pointer is not a missing field

113 of those rows refuse a unit over a four-byte field at an offset the
canonical class fills with a vftable pointer. 83 of them spell it `m_vtable`;
the rest spell it `m_vtbl`, `m_vptr`, `vtable` or `vptr`. `UpdateModule` alone
accounts for 26, then `Rva00253487Base` 9, `Drawable` 7, `UpgradeModule` 5.

`SlowDeathBehavior.cpp` shows the shape. Its private view is flat and declares
no virtual function, so it spells out all three of retail's pointers:

```
const void *m_vtable; // +0x00
const ModuleData *m_moduleData; // +0x04
Object *m_object; // +0x08
const void *m_p0C; // +0x0C
const void *m_p10; // +0x10
```

The canonical `UpdateModule : public BehaviorModule, public UpdateModuleInterface`
declares the virtuals instead, and the compiler lays those same three pointers
down at +0, +0xC and +0x10 -- the addresses `UpdateModule.h`'s target facts
already record for 0x00BF004C, 0x00BEFF90 and 0x00BFBCE4. There is no canonical
*field* at those offsets because there is nothing to name: the member goes away
with the view.

`field_renames` looked each of the view's own fields up in `flat_fields`, which
collects named data members only, and refused on the miss. That is a gap in how
the two layouts are compared, not debt in the tree.

## The fix

`vptr_offsets(name, layouts)` derives the offsets a class fills with a vftable
pointer: its own where it introduces one, and one per non-virtual base that
introduces one, at that base's offset. `class_layouts` already records `vfptr`
per class, so this needs no new compiler output. For canonical `UpdateModule` it
returns `{0, 0xC, 0x10}`.

`field_renames` now passes over a view field of pointer size at one of those
offsets instead of refusing, and records no rename for it.

Deliberately narrow:

- Only pointer-sized fields. `CommandButton::m_unmodelled_00 (+0x0, 20 bytes)`
  is still refused.
- Only offsets the canonical class really fills. A leading pointer whose
  canonical class is not polymorphic is still refused, and
  `BehaviorModule::m_p10 (+0x10)` is still refused because +0x10 is
  `UpdateModule`'s second interface, not one of `BehaviorModule`'s two.
- The check decides only whether the two layouts can be spoken about. A body
  that actually reads one of these members fails to compile, which the compile
  step answers; and the byte gate still has to pass, so a wrong adoption cannot
  come through this door.

Tests: seven in `tools/tests/test_header_field_renames.py`, three on
`vptr_offsets` (own pointer, one per polymorphic base, virtual and plain bases
skipped) and four on the comparison, including the three-pointer
`UpdateModule` shape.

## What it yields, measured

Four units sampled across four classes, each previously refused at its leading
pointer, now get past it and report their next real difference:

- `ActiveBodyValidateArmor.cpp`: `m_curArmorSetFlags (+0xF0)` is `BitFlags<17>`,
  the canonical `fieldF0` is `uint`.
- `CastleUpgradeModuleDataCtor.cpp`: `m_upgrade (+0x118)` is `int`, the
  canonical `m_upgradeToGrant` is `AsciiString`.
- `CastleMemberBehaviorCtor.cpp`: `BehaviorModule::m_p10 (+0x10)` -- a correct
  refusal, see above.
- `AIUpdateInterfacePrivateCommands.cpp`: a 20-byte field -- a correct refusal.

So none of the four adopts outright. The gain is that 113 rows will record the
difference that actually blocks them rather than a classifier artifact, which is
what the next worker needs to act on. Two of the four now point at a type
disagreement at a known offset, which is naming-lane and contract work.

Also found while measuring: `SlowDeathBehavior.cpp`'s queue row is stale. Its
probe no longer compiles at all (C1083), so that row's recorded field-rename
failure predates some header move and does not describe the unit's current
state. `class_layouts` keeps only the error codes from a failed probe
(`re.findall` with a capturing group discards the message), so the missing
include cannot be named from the queue text alone.

## Follow-up, same day: a second bug, a sharper split, and one adoption

### probe_text dropped the unit's toolchain markers

`SlowDeathBehavior.cpp`'s stale row (above) was not stale. Its probe failed
C1083 because `probe_text` cuts the unit just past its view, and this unit's
`// platformsdk` line sits at line 446 -- below the cut. `build.py` and
`stlport_overlay` read `// platformsdk`, `// dxsdk`, `// stlport` and
`// stlport46` from anywhere in the file (the old fixed-window trap is fixed and
documented in `build.py`), so the probe compiled without the PlatformSDK include
directory and `#include <windows.h>` at line 14 could not resolve.

`lost_markers(text, kept)` returns the markers the cut dropped and `probe_text`
re-appends them; they are comments, inert to the compiler and read by the build
module. The probe then compiles.

76 queue rows fail at the header's layout with C1083, so this was not one unit's
problem. The other header-layout codes are C2011 (285), C1189 (141), C2084 (28)
and C2953 (25).

### The 113 vptr rows are two different things

Of the 99 distinct (unit, field) pairs behind those rows:

- **43 assign the pointer by hand** and can never adopt. `SlowDeathBehavior.cpp`
  is one: its constructor writes all three with
  `__identifier("??_7Rva0045D39E@@6BObjectModule@@@")` and friends, because
  retail's constructor installs three particular vftables. With the header
  adopted there is no member to assign, and the compile says so
  (`C2065: 'm_p0C' : undeclared identifier`). These units want a
  `// class-gate: allow` comment recording why, as the two ICoord2D views have.
- **56 only declare it** as leading padding. Those are adoptable in principle,
  and the refusal was the only thing in their way.

### One adoption landed -- but not because of either fix

`Code/GameEngine/Source/GameLogic/Object/Object.cpp` adopting
`AttributeModifierPoolUpdate.h` passes the byte gate outright. Two others
sampled from the 56 still refuse, each on a later field and for good reason:
`SubsystemInterface::m_04 (+0x4)` has no canonical counterpart, and
`ConnectionManager::opaque24` is a 73732-byte opaque block.

**Correction.** Commit e972ab5d44's message credits this adoption to the two
fixes above. That is wrong, and this is the record of it. Re-running the
adoption with both fixes neutralised at runtime (`vptr_offsets` returning an
empty set, `lost_markers` returning nothing) still gives PASS. Neither fix can
reach this unit: its only toolchain marker is `// stlport` on line 2, above the
cut, and its private view declares two methods and no data member at all, so
`field_renames` finds no own field to look up and never consults the vptr
offsets. The row was simply **stale** -- the unit became adoptable through other
work and the queue kept the old failure.

That is the more useful finding. `reverse/header_queue.tsv` is a historical
record, not a current measurement: a row says what happened when it was written.
Before treating any part of those 6721 rows as debt, re-run the units; some
number of them already adopt. Sizing that staleness is the open question this
leaves, and it bears on every count in this document.

### Held back: naming the compiler error

`class_layouts.compile_layouts` keeps only the error *codes* from a failed
compile -- `re.findall(r"error (C\d+)[^\n]*", ...)` returns just the group, so
the message is discarded and the 739 rows that fail at a layout record a bare
code. Keeping each error's own text is what turned the C1083 above from
"compile failed: C1083" into "Cannot open include file: 'windows.h'", which is
the whole diagnosis.

That change is written and tested (five tests, including the three-error cap and
the no-error-line fallback) but **not landed**: `tools/class_layouts.py` is held
by `ancalgonn-swarm-seat6` for the bridge lane's conflicting duplicate type
records. Whoever takes it next should keep each error's text; every consumer
only stores `str(exc)`, so nothing parses the format, and `land_wave.py`'s
`^compile failed: (\S+)$` matches `build.py`'s message, not this one.

### A stale local census index reports losses that are not there

Retiring the adoption's queue row refused: `header_adopt_lane.py accept` runs
`link_check`, which said `Object.cpp: does not link  LINKED 7,026 -> 0 bytes`
with `?loadPostProcess@ObjectHelper@@MAEXXZ` and
`?xfer@ObjectHelper@@MAEXPAVXfer@@@Z` unresolved.

It was not the adoption: the pre-adoption file failed identically. Nor was it a
regression. Both symbols are `matched` rows in
`Code/GameEngine/Source/Common/Rva004DF81BXfer.cpp`, which links on its own, and
the canonical `ObjectHelper.h` declares both `protected: virtual`, so the
manglings are exactly the ones reported missing. The rows were created today
(a8c5cef5e52 01:16, db25603390e 02:26) while `build/link_census/link_index.pkl`
was from 2026-11-04 07:13 -- three days older than the definitions it was being
asked about.

`python3 tools/link_check.py --fetch-index` brought the published index to
2026-11-08 01:56 (17,943 objects), and Object.cpp then reports
`LINKS  LINKED 7,026 -> 7,026 bytes`. The row retired on the next `accept`.

Worth knowing because the failure is indistinguishable from a real one and
points at the unit you just touched: a local index older than the rows it judges
invents link losses, and the natural response is to revert good work. Fetch the
index before believing a loss, and check whether the unresolved symbols have
rows whose commits postdate the index.

## The staleness question, answered (2026-11-08)

The section above left "how much of the queue is stale" open and said it bears
on every count in this document. Measured against the worktree at 6494b4b9d0,
`reverse/header_queue.tsv` (6513 rows) without compiling anything:

| rows | verdict |
| ---: | --- |
|    0 | the source no longer exists |
|   79 | the source already includes the canonical header |
|  239 | the source no longer declares the class with a body of its own |
| 6195 | live: only a re-run decides |

So **318 rows (4.9%) are provably stale** and the rest still describe the tree.
The queue is a usable measurement after all, which is the opposite of what the
`Object.cpp` row suggested; that row was in the 239.

A worked one: `BaseHeightMapBoundingBox.cpp` holds an `AABoxClass` row whose
failure is a byte-gate FAIL. The file now includes the canonical
`BaseHeightMap.h` and takes `AABoxClass` transitively from WWMath, with no
private view anywhere in it. Nothing about the recorded failure can be acted on.

Three cautions on the 4.9%:

- It is a floor, not the total. A row whose private view survives but whose
  recorded *failure* has since been fixed still reads as live here; only
  `accept` (which compiles, re-reads the layout, byte-checks and asks
  `link_check` for a per-unit verdict) can judge that.
- The detectors are deliberately coarse. "Already includes the canonical
  header" matches the header's basename under any relative prefix, and "no
  longer declares the class" looks for `class X {` or `struct X :` with a body,
  so a view reached through an include is counted as absent. Both err toward
  calling a row live.
- `retry_budget` is 3 on all 6513 rows, so nothing has been spending it. It
  records no retry history and cannot be read as one.

The 318 group into 100 classes, the largest being `State` 39, `View` 20,
`Thing` 18, `Vector3` 15, `UpdateModule` 15, `Matrix3D` 13 and `GameLogic` 12.
Nine sit under another seat's live `class:` or `file:` claim, leaving 309 in 97
(class, header) cohorts to retire through `accept`.

The queue is also shrinking on its own: 6721 rows on 2026-11-07, 6513 today,
with field renames 3083 -> 3012, byte gate 822 -> 803, C2039 706 -> 682 and
manual header 250 -> 218.

### Correction: 98 rows, not 318, and the lane already has the verdict

The 4.9% above is wrong, in two ways, and running `accept` over the 318 found
both within two cohorts:

- `State`, 37 sources: 1 PASS, 36 FAIL, every failure
  `does not #include Code/GameEngine/Include/Common/StateMachine.h`.
- `View`, 20 sources: 0 PASS, 20 FAIL, `still declares a private body; does not
  #include .../View.h`.

**First mistake: retirement turns on the include, not on the view.**
`adoption_problems` retires a row by proving the unit *adopted* the canonical
header, which means including it. A unit that reaches the class through some
other header has adopted nothing. "No private view" was never the test.

**Second mistake: the detectors were a reimplementation, and both were loose.**
"Already includes the canonical header" matched the header's basename anywhere
in an include path, so `#include "../Common/GameLogicObjectLookupView.h"` read
as an adoption of `View.h`; that is why the whole `View` cohort was mispredicted.
The view test missed bodies the lane's own `class_layouts.class_bodies` finds.
Re-measured with the lane's own `includes_header` and `class_bodies` instead of
my own, against the queue at 6496 rows:

| rows | verdict |
| ---: | --- |
| 6275 | the unit still declares a private body: live debt |
|  123 | no body, but the unit still names the class |
|   81 | no body and the unit never names the class |
|   17 | the unit includes the canonical header |

So **98 rows (1.5%) are retirable**, not 318, and 6275 are ordinary live debt.
The lesson is narrow and worth keeping: predict a lane's verdict with the lane's
own predicates. Ten lines of regex standing in for `includes_header` and
`class_bodies` were wrong on both.

### Measured, not predicted: 16 of 16, and 0 of 81

Both groups were then run through `accept`:

| predicted | passed | judged |
| --- | ---: | ---: |
| `adopted` | **16** | 16 |
| `no-body-unreferenced` | **0** | 81 |

The prediction built from the lane's own `includes_header` and `class_bodies`
was exact on the group it was built for. The other group failed completely, and
the reason is worth recording, because `header_adopt_lane.misclassified` exists
for apparently that exact case: a row owes no include when the unit declared no
namespace-scope body of the class in the commit that queued it *and* its
compiled types hold no global of that name.

`Recorder.cpp` satisfies the second half -- `compile_layouts` returns 221 types
for it and `State` is not among them -- and still fails. The first half is what
refuses: `queued_text('State', ...)` returns the file as it stood when the row
was queued, and `State` **did** have a private body in it then. The guard is
deliberate and its comment says so: "so no view renamed since can pass". A view
that was removed or renamed since cannot be distinguished from one still present
under another spelling, so the lane will not call the row a discovery error.

So these 81 rows are neither live debt nor retirable: the unit no longer copies
the class, and nothing can prove the row dead. That is a real gap, but it is a
gap in what the register can *prove*, not a bug, and closing it means deciding
what evidence should stand for "this view went away without being adopted" --
a judgement call for a maintainer, not a tool change to make unasked.

The per-row four-way prediction is `header-queue-prediction-20261108.tsv`. The
earlier `header-queue-staleness-20261108.tsv` records the superseded two-way
verdicts; read this table, not that one.

### What the sweep retired

35 rows left `reverse/header_queue.tsv` on the register path: 6513 rows before,
6478 after. 16 from the `adopted` group, 17 from the first two passes over the
coarser plan, and 2 from the `UpgradeMux` adoptions below.

## UpgradeMux adopted in two units (2026-11-08)

Picked from the merge-blocker ranking (`header-work-ranked-by-merges-20261108.md`):
17 live rows reaching 10 TUs, the cheapest wide entry in the lane.

`adopt` over all 17: **2 PASS, 15 FAIL**. Both passing units
(`DetachableRiderBody.cpp`, `RadiateFearUpdate.cpp`) were applied,
byte-verified (25/25 functions matched across the two) and their rows retired
through `accept`.

Two private class copies gone, and two views worth looking at: the one in
`RadiateFearUpdate.cpp` spelled `bool m_upgradeExecuted` correctly and declared
four of the sixteen virtuals; the one in `DetachableRiderBody.cpp` derived from
`Rva004C1C29Slots<11>` and declared the four pure-virtual hooks.

**`canonical_classes.csv`'s sampled adopt rate does not predict the queue.**
Its note for `UpgradeMux` reads "49/76 sampled units adopt", and 2/17 adopted
here. Those are not in conflict: the queue *is* the set that already failed, so
its rows are the residue the 49 left behind. The same reading applies to every
class in the ranking -- `UpdateModule`'s "46/357" says nothing about its 73
queue rows. Rank by rows and reach, never by the registry's sampled rate.

The 15 failures are not a long tail. Five share one cause:
`UpgradeMux::m_executed (+0x4, 4 bytes) has no canonical field of that offset
and size`, which is the padding-span pattern anatomised in
`header-missing-field-rows-anatomised-20261108.md`. One more is its sibling
(`m_muxPad (+0x5, 3 bytes)`) and one is a token-collision refusal
(`m_executed also appears at file scope; a token rename would reach it`).
