# 81 mergeable TUs never reach the queue, and 30 are one row away

Measured 2026-11-09 at `1650aa94c47`, using `tu_skeleton.py`'s own predicates.
`tools/tu_skeleton.py --queue` lists **493** TUs with donors to absorb. It is not
the whole lane: another **81 TUs holding 1586 donor files** are refused before a
single donor is weighed, so they appear in no queue, no `--merge-all` ordering
and no `decisions.json`.

## The refusal

`tu_skeleton.merge()` checks this before any compile:

```python
if tu in mixed or ((ROOT / tu).exists() and tu not in don):
    report["blocked"] = "TU path exists and holds rows of another TU (split it first)"
    return report
```

A TU whose own file holds even one row the map puts elsewhere is refused
outright. That is sound -- absorbing donors into a file that owes a row to
another TU would carry that row away from its home -- but the cost is invisible,
because the refusal lands before the TU is ever ranked.

Verified against the live queue, which the predicate explains exactly:

| check | result |
| --- | --- |
| blocked TUs that appear in `--queue` | **0** of 138 |
| `MilesAudioManager.cpp` (in the queue, 105 files) | not blocked ✓ |
| `ai.cpp` (merge dry-run runs today) | not blocked ✓ |
| `RTS/ScoreKeeper.cpp` (observed refusal) | blocked ✓ |
| the 81 blocked-with-donors vs the 493 queue entries | **disjoint** |

## Confidence decides the remedy, and the blocker ignores it

`donors()` builds its `assigned` table from **any** non-empty `tu` column:

```python
_CACHE["assigned"] = {int(r["rva"], 16): r["tu"].lower() for r in map_rows()
                      if r["kind"].startswith("code") and r["tu"]}
```

So a merely **proposed** placement blocks a merge exactly as hard as an approved
one -- and the two need completely different work. AGENTS.md is explicit that
rows move only into *the address's approved unit*, so a row proposed elsewhere
cannot simply be split out; its placement has to be settled first.

Across the 81 blocked-with-donors TUs, by the confidence of their blocking rows:

| TUs | donors | blocking rows are |
| ---: | ---: | --- |
| 32 | 548 | approved elsewhere |
| 20 | **605** | **only proposed elsewhere** |
| 29 | 433 | a mix of both |

And among the 30 TUs blocked by exactly one row:

| TUs | donors | blocker | remedy |
| ---: | ---: | --- | --- |
| 16 | 259 | approved elsewhere | a split, once its evidence holds up |
| 14 | **443** | only proposed elsewhere | TU-approval/evidence work first |

The split-shaped work is the *smaller* half. The largest blocked TUs are all in
the proposed column.

## The cases, named

**One row, approved elsewhere** -- the split-shaped half. Largest first:

| donors | TU | blocking row | approved home | by |
| ---: | --- | --- | --- | --- |
| 73 | `Object/Contain/HordeContain.cpp` | `?ModuleFactoryHookAt0047A6A4@@YAXPAXH0@Z` | `AODHordeContain.cpp` | C |
| 35 | `Common/RTS/ScoreKeeper.cpp` | `??A?$map@PBVThingTemplate@@H...` | `CollisionManagerImpl.cpp` | C |
| 31 | `LivingWorld/LivingWorldRegion.cpp` | `?rva002B3769@Rva002B3769@@QBE...` | `LivingWorldLogic.cpp` | C |
| 25 | `System/SaveGame/GameState.cpp` | `??0SaveDate@@QAE@XZ` | `INI.cpp` | C |
| 15 | `AIUpdate/DozerAIUpdate.cpp` | `?privateRepair@WorkerAIUpdate@@MAEX...` | `WorkerAIUpdate.cpp` | **Z** |
| 15 | `WW3D2/matinfo.cpp` | `??0?$DynamicVectorClass@PAVTextureClass@@...` | `meshmdlio.cpp` | C |
| 13 | `WW3D2/mesh.cpp` | `?Enable_Two_Sided_Rendering@VisRasterizerClass@@...` | `visrasterizer.cpp` | **S** |
| 13 | `Apt/AptCIH.cpp` | `??_GRva006CBF40@@UAEPAXI@Z` | `AptValueNameEntry.cpp` | C |

Evidence letters for these 16: **C 12, N 1, S 1, T 1, Z 1.** Twelve of sixteen
rest on contiguity alone, which is the weakest signal `tu_map.py` records, so
"mechanical" overstates most of them: the evidence wants reading before a row
moves. `DozerAIUpdate.cpp` (Z, a Zero Hour definition) and `mesh.cpp` (S) are
the better-evidenced ones.

**One row, only proposed elsewhere** -- the bigger half by donors. Largest first:

| donors | TU | blocking row | proposed home | by |
| ---: | --- | --- | --- | --- |
| **208** | `GameLogic/Object/Object.cpp` | `?GetSnapshotName@ObjectRecoveryHelper@@MBEPBDXZ` | `ObjectRecoveryHelper.cpp` | **N** |
| 83 | `LivingWorld/LivingWorldLogic.cpp` | `?GetMaxHeroLeaderRank@AttackOrders@@QAEHXZ` | `AttackOrders.cpp` | **N** |
| 43 | `GameClient/Eva.cpp` | `??0BfmePod52@@QAE@XZ` | `BfmeRecord001DD3BC.cpp` | U |
| 27 | `Contain/HordeContain/HordeSiegeEngineContain.cpp` | `?buildFieldParse@SiegeEngineContainModuleData@@...` | `SiegeEngineContain.cpp` | **N** |
| 16 | `WW3D2/meshmatdesc.cpp` | `??0?$ShareBufferClass@VShaderClass@@...` | `OpaqueRefBuffer.cpp` | C |
| 12 | `Apt/AptAnimation.cpp` | `?next@AptActionQueueC@@QAEPAU...` | `AptActionQueueC.cpp` | **N** |
| 11 | `W3DDevice/GameClient/W3DPropBuffer.cpp` | `?Set@Vector4@@QAEXMMMM@Z` | `Vector4.cpp` | **N** |

Evidence letters for these 14: **N 9, C 2, U 2, K 1.** Nine of fourteen carry
name evidence -- the row's own symbol names the file -- which is the strongest
letter in the table, yet the placement is still only *proposed*. `Object.cpp` is
the extreme case: **648 approved rows and 208 donor files behind one 6-byte
`?GetSnapshotName@...` row that `by=N` evidence places in
`ObjectRecoveryHelper.cpp`, a file that does not exist in the tree.**

So the single highest-leverage item the merge lane has is not a merge or a split.
It is settling one row's TU placement.

## What this does not claim

- **1586 donor files is not 1586 removable files.** It is what a complete merge
  of all 81 would absorb. Unblocking a TU buys it an *attempt*. Measured
  acceptance is far lower, and varies by tool revision: see
  `merge-all-ordering-costs-a-whole-budget-20261108.md`.
- Whether a *proposed* placement should block a merge is a question for the
  tooling seat, not a defect I am asserting. Refusing to accrete donors around a
  row whose home is unsettled is defensible conservatism. The measurement here is
  only that it is what happens, and that it accounts for 605 of the 1586 donors.
- `ObjectRecoveryHelper.cpp` does not exist as a file; its other rows sit in
  `ObjectRecoveryHelperPoolKey.cpp`, and its own `0x0028CA4D` row is `proposed`
  too. Settling `0x0028CA92` is TU-evidence work on a group, not a one-row edit.
- The 81 and the foreign-row counts come from `donors()`, so they match the tool.
  The per-row attribution reimplements the inner test with `tu_skeleton`'s
  `emission_held()` and `fold_alias()`; it reproduced the tool's count on every
  TU, but the split or approval is the real test.
- 57 of the 138 blocked TUs hold fewer than 2 donors, so unblocking them buys
  nothing today. They are excluded from every figure above.

## Method, and two corrections it took

The committed `reverse/tu_map.csv` is stale, and `tu_skeleton` rebuilds the map
in memory. Reading the committed file shows `0x0028CA92` with an **empty** TU
column; the rebuilt map assigns it to `ObjectRecoveryHelper.cpp`. Any count of
this blocker taken from the committed CSV is wrong.

Two over-claims were caught before this note was published, both the same shape:

1. A hand-rolled "does any row here belong elsewhere" test said **112** TUs. It
   flagged `MilesAudioManager.cpp`, which is in the queue with 105 files, because
   `donors()` exempts `emission_held` rows, ICF fold aliases and homeless rows
   that follow the seed. Calling `donors()` gives **81**.
2. The first draft called the `Object.cpp` fix "a mechanical split, not a
   judgement call". It is not: that placement is `proposed`, and AGENTS.md
   forbids moving a row anywhere but its approved unit. Checking the confidence
   column moved 443 of the 702 one-row donors out of the split-shaped bucket.

The recurring lesson, now three times in this lane: **use the lane's own
predicates, and read the confidence column before pricing any row move.**
