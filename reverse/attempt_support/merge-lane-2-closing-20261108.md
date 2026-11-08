# Merge lane 2 closing handoff, 2026-11-08

The lane closes because merges can't move cheaply right now, not because the queue is empty. Read this before
surveying these TUs, adopting `object.h` to free merges, or trying `StringBase` switches again. Measured at master
`7d99dff1a2` to `4daa8e15dd`. Scratch scripts were untracked under `build/` on srv1, so each method is described below.

## What the lane left open

- **A tool defect in `tools/tu_skeleton.py`'s `compose`** (below). Reported, not fixed.
- **The displaced-run rule** (below). Going to the owner. `tools/tu_map.py` is unchanged.
- **P51's row 0x005DFF76** has no approved route today (below).
- **LINK-649**: AITacticSiege's real table needs rows for AITactic's `v4` and `vslot08`.

## `compose` tool defect: an anchor is hoisted above the function it names

**Target facts.** None; this is a tool behaviour.

**Tree facts, measured.**

- `Code/GameEngine/Source/Common/RTS/Player.cpp` defines `static ScienceType *bfme_force_ScienceVec_erase(...)` and then
  the file-scope data `bfme_force_ScienceVec_erase_anchor = &bfme_force_ScienceVec_erase;`.
- `compose` writes declarations first and bodies after. The anchor lands with the declarations and the static function
  with the bodies. The composed text uses the name at line 620 and defines it at line 2485: C2065, then C2365.
- So `Player.cpp` fails **alone** under `compose`, with no donor, though the file builds as written.
- In-memory workaround, for this test only: a `struct` holding the helper as a static member, which `compose` treats as
  a declaration. The seed then passes. Of the 15 sampled donors stopped on this error, **10 pass**, 1 fails on bytes and
  4 still fail to compile (C2039 `bfmeVisitAll`, C2039 `rva002AC425`, C2953 `rts::hash`, C2953 `BitFlags`).
- The other 25 sampled donors stop on their own errors with the workaround on, so 10 of 40 pass in all. They are 0 of
  40 without it.
- Reach: a scan found 32 files with a file-scope initializer naming a function defined in the same file, 4 of them
  approved TU seeds. All 4 seeds were compiled alone and none hits this error (`GameInfo.cpp`, `Shadow.cpp` ok;
  `W3DHordeModelDrawManager.cpp`, `DataChunk.cpp` fail on bytes, not explained here). Their initializers name members
  declared in a class, so the name is already known. The donors among the 32 were not tested.

**Inference, not proven.** The defect bites when the only declaration of the named function is its definition. On the
sample rate, about 39 of `Player.cpp`'s 157 donors might pass with the seed. That is a pairwise rate, not a merge: only
the full merge search prices it, and the 4 compile failures above show more conflicts behind it.

**Next step.** Either `compose` keeps such an initializer after the function it names, with a regression test and a
`Verifier-Change` trailer, or `Player.cpp`'s anchor is respelled. Neither is done.

## First errors in the big TUs

**Method.** The largest-first survey was stopped after 2 hours with no results, because `merge_all` reports a TU only
when its whole search ends (`Player.cpp` and `MilesAudioManager.cpp` were still running). Instead, each donor was
compiled once with the seed, through `tu_skeleton`'s own `compose` and `Verifier`, first strategy only, with up to 40
donors per TU evenly sampled. This is a sample of pairs, not a merge search. Nothing was written or claimed.

| TU | Tested | Pass | Bytes | Compile | First error string-related | Main first error |
| --- | --- | --- | --- | --- | --- | --- |
| `Player.cpp` | 40 | 0 | 0 | 40 | 1 | 15 C2065 (the defect above); 15 C2011 across several classes |
| `MilesAudioManager.cpp` | 40 | 0 | 4 | 36 | 0 | 17 C2653 `MilesAudioManager` is not a class |
| `AIPathfind.cpp` | 40 | 0 | 7 | 33 | 0 | 17 C2061 identifier `Object` |
| `Scripts.cpp` | 40 | 0 | 0 | 40 | 0 | 18 C2011 across several classes; 8 C2504 `Rva003B573E` |
| `ai.cpp` | 26 | 1 | 0 | 25 | 19 | 19 C2953 `StringBase` |

**`StringBase` is not a shared cause.** In the four big TUs one first error of 160 is string-related, and four have a
string error anywhere. `ai.cpp` is the exception.

**`BFME_STRINGBASE_PUBLIC_*`: 0 of 27.** All 27 donors with a string-related error (23 in `ai.cpp`, 4 in the big TUs)
were retried with `PUBLIC_COPY`, `PUBLIC_DTOR` and `PUBLIC_DEFAULT_CTOR` all on. None got past its error. No donor in
the four big TUs uses these switches.

**`ai.cpp`'s C2953 and the macro reading.** `merge-lane-claim-blocking-20261108.md` reads it as donors needing
differently shaped `StringBase` definitions. `string_base.h` has `#pragma once`, so a second include is skipped whatever
macros are set, and the switches changed nothing. `ai.cpp` itself defines a one-member private `StringBase` and does
not include the shim. Inference: that private copy is the C2953.

## Three cheap fixes that failed

Each was tried in memory, on the seed only, against the donors stopped on that error.

| TU | Change | Result |
| --- | --- | --- |
| `AIPathfind.cpp` | Add `class Object;` at the top | 0 of 17: all become C2027, undefined type `Object` |
| `MilesAudioManager.cpp` | Include the canonical `MilesAudioManager.h` | 0 of 17: the seed itself then fails with C2614 |
| `ai.cpp` | Replace the private `StringBase` with the shim | 0 of 19: the seed stays exact, all stop on C2011 `AsciiString` |

## `object.h` adoption doesn't free merges

11 units adopted `object.h` and landed (through `7d99dff1a2`), with bytes and vtable slots checked. **0 merges freed.** Of
91 private-view files, 10 passed the tool outright. 41 are refused on a field, 27 of those on a first refusal at
`+0x10C` (18), `+0x094` (5) or `+0x0A8` (4). In the 32 smallest TUs surveyed, 3 of 124 rejected donors name `Object` in
their errors, and in the same survey 0 name `AITactic`. Check slots as well as bytes: `RebuildHoleBehaviorDtor.cpp`
passed on bytes while slot 2 changed from `GetSnapshotName` to `crc`, and needed `BFME_SNAPSHOT_NAME_SLOT`.
`ReplaceSelfUpgrade.cpp` stays blocked on a ctor that stores vtables and a dtor that doesn't.

## The claimed group is not a work list

The 89 "claimed" TUs (1,708 files) were a snapshot: at 12:50 UTC 79 of them had no live holder. In the rerun the static
read put 320 files behind private class views, 72 behind splits and 43 refused. `split` touches all 79 TUs but frees few
files; it places rows. Compile testing reached only the 32 smallest TUs (125 files): 2 donors accepted, 124 rejected.

## P51: 0x005DFF76 has no approved route

**Target facts.** 0x005DFF76 is 5 bytes, `jmp 0x005DFE18`. `~LadderPreferences` at 0x005DFF7B calls 0x005DFE18 directly,
not 0x005DFF76. No row in 0x005DF17C..0x005E03F6 references a `__FILE__` string.

**Tree facts.** `tu_evidence.py --write` gives 1,298 rows and none in the block. 32 rows there name
`Common/UserPreferences.cpp` by `Z` or `S`, whose main cluster is 106 rows at 0x00535781..0x00537C3F, so they are
`displaced`. Placing them in any other TU trips the rule that a row contradicting both `Z` and `S` is never approved.
0x005DFF76 has no hints and can only take C, which needs two approved brackets.

**Donor facts.** `wb_name_leads.csv` has no leads in the block. WorldBuilder has a `Common/UserPreferences.cpp` path,
marked not present in `game.dat`.

**Inference, not proven.** BFME 2 moved these classes into a separate object with no name evidence. Adjacency of the
row to `OnlinePreferences_Unresolved.cpp`'s rows is placement evidence only.

## The displaced-run rule (not adopted)

**The rule.** A long run of displaced `Z`/`S` rows is its own object, with a provisional TU. `tools/tu_map.py` is
unchanged, and everything here was measured from the committed map and the retail image.

**Tree facts.** 19 runs of 8 or more rows, 323 rows: 218 real names, 103 address-named (identity unknown), 2 template or
compiler, 0 matching `tu_map.py`'s `COMDAT` pattern. 140 have their own `Z`; 183 have only `S`.

**Donor-based estimate of precision: 97.66%, below the 99% gate. The truth here is WorldBuilder leads**, `.cpp` files
only, on hint runs of 8 or more across the whole map: 792 of 811 rows, 124 of 132 runs naming one file. WorldBuilder leads
are donor facts, so this estimates precision and doesn't prove it. Against the 19 runs, 11 have a lead: 2 span several
files (`AIPathfind.cpp`: `pathfinder_path` and `pathfinder_layer`; `pathfinder_cell` and `pathfinder_classify`), 8 name
one different file and 1 agrees. A run that spans several files is one provisional TU over several real files, which
the provisional rule's hold-out recorded at zero.

**Circular, don't quote.** A five-fold hold-out adapted to this rule gives 100%, 0 of 289 groups mixing. Approval comes
largely from the same `Z`/`S` hints, and runs break at approved rows of other TUs, so it can't see the real failure. The
same applies to 13,618 of 13,624 approved rows agreeing inside hint-run spans. The real `tu_map.py --holdout` can't
test this rule, because it strips the hints the rule runs on.

**Target facts.** The 8 runs with at least 3 funclet parents are contiguous in `.text$x`. Approved TUs have a median of
0.80 on that test, so this is weak support. The game's own `__FILE__` agrees on 25 of 25 rows, in only 7 runs.

**Unlock, measured upper bounds.** All 19 runs: 710 rows approvable, 239 whole files inside, 220 files removed if all
merged, 150 files needing a split. Without the 2 contradicted runs: 621 rows, 185 files, 168 removed. P51 block alone:
56 rows, 18 files, 17 removed, 13 needing a split.

**Estimates.** About 4 of the 220 files, at the 2 of 126 donor acceptance rate. About 0.7 points on TU-APPROVED.
`shader.cpp` and `rendobj.cpp` have no `Z` rows, so they may be header inlines.

**0x005DFF76 under the rule, read from the rules and not rebuilt.** Probably approved by C between 0x005DFAB3 and
0x005DFF7B, 0x4C8 apart. It needs more than the rule: an exemption from the contradiction rule, and one name for the group,
because the rows' `N` hints disagree.
