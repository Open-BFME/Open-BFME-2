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
