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

This is header-debt retirement. Existing matched, C++ exact and census-linked
bytes are preserved; no new byte gain or class-wide closure is claimed.
