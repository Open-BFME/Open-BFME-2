# A contract's size is voted on without consulting its own retail access

`header_adopt_lane.py adopt --class Rva0039C0F4` cannot succeed, and the reason
is not this class. 646 of 2,689 contracts — **24%** — record a `size` smaller
than the highest `this`-relative access their own evidence records, and 536 of
those are not queued, so a header is generated for them anyway.

## The instance

`next_work.py --claim` served class-header adoption for `Rva0039C0F4`
(`reverse/header_queue.tsv#2f3cf8e434f0`). The adopt fails:

    FAIL Code/GameEngine/Source/Common/Rva0039C0F4Sum.cpp(47):
         error C2065: 'm_maps' : undeclared identifier

The generated header declares the method and nothing else:

    class Rva0039C0F4 {
    public:
        int rva0039C0F4(const AsciiString &name);
    };
    typedef char canonical_..._sizeof[sizeof(Rva0039C0F4) == 1 ? 1 : -1];

`Rva0039C0F4Sum.cpp` needs `ObjectCountMap m_maps[20]` at `+0x1FC` to compile a
body that is already `matched` (`find_declared_unmatched.py`: "All defined
functions are already matched").

The contract explains itself:

    "size": 1, "size_by": "majority",
    "view_sizes": {"1": 2, "748": 1},
    "retail_access": {"0x1fc": {"4": 1}},
    "outliers": [{"offset": 508, "sources": ["…/Rva0039C0F4Sum.cpp"], "views": 1}]

Two views declare a bare method stand-in, one declares the real 748-byte
object. Majority wins, and the contract records `size: 1` beside its own
record of a 4-byte read at offset 508. A one-byte object cannot be read at 508.

## Why the rule does not catch it

`class_contract.py` does have a size-contradiction check (~line 679), and its
comment is clear that it is deliberate:

> It is queued, never imposed: two facts can show the recorded size is wrong
> without establishing which of them is the sizeof.
> Both facts are needed before queueing, because a queued attribute refuses
> header generation and neither fact alone should carry that.

The two facts it requires are `extent_lower_bound` (the ctor's `this`-relative
writes) and `allocation_observed`. `retail_access` is computed (line 298),
stored in the contract, and **never consulted by the size decision** — even
though `RULE_STRENGTH` (line 252) ranks `retail-access` above `majority`.

So a class whose only contradicting fact is an access is silently given a size
its own evidence rules out.

## Scope

| | contracts |
| --- | ---: |
| total | 2,689 |
| size below their own highest retail access | **646 (24%)** |
| …of those, already queued (header refused) | 110 |
| …of those, **not** queued (header generated anyway) | **536** |

By the rule that decided the size: majority 595, tie 46, zh 3, retail-new 2.

The gap is not rounding. Median 59 bytes; 314 exceed 64 bytes; 83 are ≤ 8 and
could be a miscount. The extremes are not close calls:

| class | size | access reaches |
| --- | ---: | ---: |
| `Debug` | 4 | 40,468 |
| `WorldHeightMap` | 40 | 32,980 |
| `Mouse` | 4 | 20,480 |
| `Rva00111784DwordField` | 1 | 10,936 |
| `TerrainLogic` | 4 | 6,420 |

## What I did not do

I did not change `class_contract.py`. Queueing on an access alone would refuse
header generation for ~536 classes and contradicts the documented decision
above — `retail_access` is an inference from `[ecx+disp]` operands with `this`
tracked through register copies, so a mis-attributed member row can produce a
false offset exactly as a mis-attributed write can. Blocking 536 classes on one
inference is the failure mode that comment exists to prevent.

The design-consistent repair is to make access a **third corroborating fact**,
so the rule becomes "any two of {ctor writes, observed allocation, retail
access}" rather than the current fixed pair. I could not size that here: the
contract files do not store `extent_lower_bound` or `allocation_observed`, so
the corroborated subset has to be computed inside `retail_layout.py` at build
time. That measurement is the next step, and it decides whether the fix is
worth its blast radius.

A narrower repair worth weighing alongside it: leave the size alone and let
`adopt` fall back to the outlier view when the majority view cannot compile the
unit. That fixes the lane without touching 536 contracts, but it leaves the
contracts recording sizes their evidence rules out.

## Reproducing

    python3 tools/header_adopt_lane.py adopt --class Rva0039C0F4 \
      --header Code/GameEngine/Include/GameLogic/Rva0039C0F4.h \
      --apply Code/GameEngine/Source/Common/Rva0039C0F4Sum.cpp

The scope table comes from reading `size` against
`max(offset + max(width))` over `evidence.retail_access` for every
`reverse/class_contracts/*.json`.
