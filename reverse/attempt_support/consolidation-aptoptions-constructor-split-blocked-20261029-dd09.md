# AptOptionsConstructor.cpp split (blocked) — 2026-10-29, worker dd-09

Item: `next_work.py --tier consolidate --claim` served "merge-split
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOptionsConstructor.cpp":
carve the 25 rows approved for
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOptions.cpp` out of the
mixed file, leaving the 2 rows the map places in another TU.

Claims held while working: `file:` on both paths; released after this record.

## What was tried

`python3 tools/tu_skeleton.py --split <file> --for <TU> --dry-run` on sandbox
fleet-dd-09, base 05523f28f1.

1. First refusal: `a namespace/extern "C" block defines something: carve not
   supported`. The trigger is the `namespace _STL { template <> struct
   less<AsciiString> {...} }` block (`brace_blocks`, tools/tu_skeleton.py:2026).
   Remedy landed: commit c727b0db15 moves that specialization to
   `AptOptionsConstructor_less.h`, a TU-scoped shim included where it stood. The
   TU still byte-matches 27/27 and the hooks pass; it needs no ledger change.
2. Second refusal: `an escape-hatch count would grow (hatch_counters rule 3)`.
   `hatch_move` scans the donor and the residual, and `carve` leaves the file's
   prelude in both texts, so `extern int g_Va00A04908;` duplicates and the
   file's `address_global` count (3 in reverse/hatch_baseline.tsv) becomes 4.
   A block-scope `extern` inside the constructor keeps the count at 3 and got the
   dry-run past this stage, but the tree has no block-scope externs and the
   change was dropped once the split proved blocked below.
3. Final refusal: `the residual loses matched rows` — 0x0057BC63
   (Rva0057BC63FunctorHolder ctor), 0x005185BA (Rva0057BC63FunctorWrapper ctor)
   and 0x00518892 (this-adjusting deleting-dtor thunk). `residual_keeps: 0`.

## Why it cannot be split as served

The three lost rows are COMDATs the compiler emits only for a user in the same
TU. The constructor is that user: it builds `AptRef<Rva0057BC63FunctorHolder>`
for every binding, and the holder constructor calls the wrapper constructor.
With the constructor carved out, nothing in the residual emits them. The map's
"other TU" rows here are not independent bodies; they are the select-any copies
the constructor's inline definitions produce (the ledger notes on those two rows
record identical digests in six TUs and that the row was moved here to end an
LNK2005).

The mirror move is no better: carved into
`Code/GameEngine/Source/Common/Rva0057BC63FunctorHolder.cpp` the two rows have no
user there either, so the per-row "alone" check refuses them. A synthetic user in
the residual would add code retail does not have, and making the constructor use
the out-of-line holder definition would stop this TU emitting the two COMDATs and
reopen the selected-provider question the earlier rehome settled.

## Next steps

A split of this file needs either a way to keep the residual's COMDAT rows
emitted or a lane that moves a row whose only emitter is the carved body
(`--split` requires the residual to keep every staying row). If the lane is
revisited, c727b0db15 already removes the first refusal.
