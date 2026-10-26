# AI Xfer header adoption

Inspected upstream `a1ee5c1f39`, with verified BFME 1 reference `f633d0e97a`.
The default queue served the complete
`Code/GameEngine/Source/Common/AIFlankAttackTacticImp_DoXfer.cpp` source.
Its historical canonical-header trial failed with `Snapshot` undeclared.

## Flank-attack route transfer

Replace the private Xfer vtable with the registered `BfmeXfer.h`. Declare its
operand types in the local AI consumer header `AIXferTypes.h`, included before
the canonical header. The shared header and function row remain unchanged.
The local header contains declarations only, not alternative class bodies.

MSVC reverses the contiguous `operator==` overload group in the emitted vtable.
An initial source-order interpretation changed only the call-slot immediates;
selecting the actual unsigned-int and Coord3DBase overloads restores retail's
`0x78` and `0x60` dispatch. Loading/storing stay at `0x04` and `0x08`.
The native addresses, route view, vector operations and transfer order are kept.
The Coord3DBase pointer view agrees with the existing opt-in Coord3DBase header;
no new layout or donor-name recovery is claimed.

- Complete source read; frozen-file checks pass before and after.
- Normal byte/reference gates pass 1/1 row, 156 bytes, before and after.
- Ordinary link previews against index `f995f30157` (2026-10-25 21:36 UTC)
  keep this already-linked unit at 156 -> 156 authored bytes.
- The supported TU merge dry-run still accepts the seed, this donor and the
  destructor donor, with 10 rows and no rejected donors. It leaves the two
  pre-existing mixed-file donors outside the merge. No merge was applied.
- Keeping operand declarations in their own include is necessary: the normal
  composer hoists includes above source declarations. Plain source forwards
  would reintroduce the historical `Snapshot` compile failure on composition.
- `header_adopt_lane.py accept --class Xfer` passes and retires this source's
  single queue row through the owning-tool path.

## AI upgrade transfer

The whole `Code/GameEngine/Source/Common/AIUpgrade_DoXfer.cpp` consumer uses
the same operand-declaration include and canonical Xfer header. Its existing
two-byte version buffer is passed by the Version overload at slot `0x28`;
the integer and AsciiString use their `0x7c` and `0x6c` overloads. The buffer
initialization, native callees, string lifetime and subsequent object lookup
remain unchanged. No Version layout definition is introduced.

Frozen-file checks and normal builds pass before and after: two rows, 254
bytes including the existing ten-byte EH handler. The current parent EH graph
is EXACT, with no baseline exception. The owning header-acceptance tool passes
and retires the source's queue row.

The source is absent from census index `f995f30157`; ordinary link_check refuses
a preview with `not in census ... so not previewable`. No clean link preview
or census result is claimed for this consumer. The next published census is
required to judge it; the acceptance and byte/EH checks do not substitute for it.

## Harvest prepare-site state

The whole `Code/GameEngine/Source/Common/AIHarvestPrepareSiteState.cpp` uses
the same two includes in place of its private Xfer vtable. Its transfer keeps
the existing Version1 call and passes `m_20` to the unsigned-int overload at
slot `0x78`. The constructor, onEnter, update and native state table are unchanged.

Normal gates and frozen-file checks pass before and after: four function rows
(362 bytes) and the 68-byte data table. The owning acceptance command retires
this source's queue row. The combined ordinary preview for this source and the
flank route keeps both units clean, 518 -> 518 authored bytes against the same
index. The AIUpgrade limitation above is separate from that two-unit result.

This is retirement of three header-debt rows. Seven function rows preserve
772 bytes, plus the 68-byte data row; the existing upgrade EH graph is EXACT.
No new matched, C++ exact or census-linked byte gain or class-wide closure is
claimed.
