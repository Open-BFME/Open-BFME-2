# A size decided with no fields: 38 contracts whose sizeof came from empty views (2026-11-06)

## What the rule does

`class_contract.decide()` settles `sizeof` in a fixed order, and the last resort is a
plurality of the compiled private views:

```python
fitting = collections.Counter({s: n for s, n in sizes.items() if s >= end})
top = fitting.most_common(2)
size, size_rule = (top[0][0], "majority") if ... else (end, "tie")
```

The `s >= end` filter is the safeguard: `end` runs past the last *decided field*, so any
view too small to hold the fields the contract already froze cannot vote on the size. That
works. 406 of the 444 majority/tie contracts have at least one decided field and are
filtered this way.

## Where it fails

When no field was decided, `end` is 0, the filter admits everything, and an empty view
votes. An empty class is 1 byte under MSVC, so each such view says "1". The non-degenerate
views disagree among themselves across many distinct sizes, so no single real size holds a
plurality - and the degenerate bucket wins with a small minority of the votes.

38 contracts decided their size with no field decided: 28 record size 1, 4 record 0, and 6
record 8-16. The clearest cases:

| class | recorded size | views | views saying 1 | largest view |
|---|---|---|---|---|
| ThingTemplate | 1 | 466 | 61 | 1600 |
| Player | 1 | 60 | 9 | 1880 |
| LivingWorldPlayer | 1 | 29 | 15 | 968 |
| Rva002BA8F1Logic | 1 | 132 | 101 | 304 |
| Shell | 1 | 58 | 43 | 120 |

Player is the sharpest: 9 of 60 views say 1, and 1 still wins. ThingTemplate's own
contract records a retail `allocation_observed` of 0x640 alongside the size of 1.

Not every one of the 38 is wrong. FileSystem has 66 views and all 66 are size 1, with a
largest view of 1 - there, 1 is simply all the evidence there is, and recording it is
honest. The defect is specifically a *minority* degenerate bucket winning a fragmented
vote, not the presence of empty views.

## Why it matters

A contract is the frozen ABI claim a canonical header is generated from, and these say the
class is one byte with no members. Any size or layout comparison against them is vacuous:
the header lane's reconciliation planning hit this on ThingTemplate (466 views), Team and
MeshModelClass in the same pass, and the plans are in
`reverse/attempt_support/reconcile-plans-20261106/`. It is the same shape as the class-key
rule corrected in 2b6d25c8174: a vote over names and views we derived, overruling or
standing in for evidence retail actually carries.

## What to do, and what not to

The module's own stated principle already decides this: "An attribute still tied after all
five rules is a queue item, never a guess." A size decided from views that froze no field
is a guess. The minimal change is to queue the size as a decision item in that case rather
than record it, so no consumer reads 1 as authoritative - the queue entry can carry the
candidates, as the existing `size`/`field@0x0` queue items already do.

This was deliberately not changed in this pass. Rewriting the rule changes up to 38
contracts, each of which generates a canonical header that units are gated against, so it
needs its own verified pass rather than riding along behind a measurement.

## A correction worth recording

The first measurement here modelled the rule as a plain plurality over `view_sizes` and
reported that 48 contracts would change if size-1 views did not vote. That was wrong: it
ignored the `s >= end` filter, so it counted contracts whose vote is already filtered, and
its INI row (2172 -> 12) was an artefact of that mistake. The figures above come from
applying the rule as written, computing `end` from each contract's own decided fields. If
anyone finds the number 48 in a scratch note, it is superseded by the 38 here.

## A sharper invariant, and a correction to the above

The empty-view analysis above is about one rule. There is a rule-independent check that
catches more, and it needs no new evidence: a contract already records
`evidence.retail_layout.facts.extent_lower_bound`, the bytes retail's own constructor
writes into the object. **A decided size below that is a self-contradiction.** 66 of the
568 contracts violate it - 54 decided by `majority`, 10 by `tie`, and 2 by `zh`.

The worst are not subtle:

| class | recorded size | retail ctor writes | rule |
|---|---|---|---|
| Pathfinder | 1124 | 119280 | majority |
| WorldHeightMap | 40 | 73940 | majority |
| Debug | 4 | 40805 | majority |
| Mouse | 4 | 20496 | majority |
| TerrainLogic | 4 | 6428 | majority |
| Player | 1 | 1876 | majority |
| ThingTemplate | 1 | 1600 | majority |

Team is the clearest single case to fix first, because three independent sources already
agree against its contract: the contract records size 60, while its own evidence has
retail allocating 0x13C at three sites and the constructor writing 297 bytes, and the
canonical header carries a hard assertion - `typedef char CanonicalTeamSizeCheck[sizeof(Team)
== 0x13C ? 1 : -1];` - with a comment naming the three allocation sites. The contract
contradicts the header it is supposed to describe.

**The correction.** The section above named MeshModelClass alongside ThingTemplate and Team
as a contract "that cannot support a size check", implying the same voting defect. That was
wrong: MeshModelClass's size of 192 was decided by the `zh` rule, not by a vote, and its
problem is only that 192 sits one byte below the 193 its constructor writes. It is caught
by the extent invariant here, not by excluding empty views. The same applies to the other
`zh`-decided violation. Grouping it with the vote defect misattributed the cause.

So the two findings are distinct and the second is the better place to start: excluding
empty views from the vote fixes a plurality artefact in up to 38 contracts, while refusing
or queueing any size below the recorded ctor-write extent is one comparison, covers 66
contracts across three different deciding rules, and cannot be wrong - the contract is
disagreeing with evidence it already carries.
