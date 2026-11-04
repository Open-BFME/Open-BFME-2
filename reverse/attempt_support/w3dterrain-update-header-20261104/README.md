# W3DTerrainVisual update: canonical-header adoption

Inspected source revision: `1e2125afaae297db81897cd518dffcc3689124da`.
Provider index: 2026-11-04 17:56, `8c757ea0db`.

The claimed W3DTerrainVisual consolidation scope includes
`Code/GameEngine/Source/Common/W3DTerrainVisual_update.cpp`. Its queued
W3DTerrainVisual adoption failed because automatic field substitution treated
the private view's pointer as the terrain object. The target header documents
two polymorphic subobjects: the SubsystemInterface receiver is complete-object
`+4`, and the water pointer is complete-object `+0x18`. Retail update
`0x00091D0D` reads receiver `+0x14` and passes the original receiver to the
empty-base operation at `0x000B3FD0`.

The source now includes W3DTerrainVisualClass.h, reads its water pointer and
retains the existing Rva0010082F call view. With this multiple-inheritance
declaration, MSVC 7.1 biases `this` inside this override. The explicit four-byte
receiver projection preserves the empty-base call's argument. A normal
static_cast to SubsystemInterface added a null adjustment sequence and failed
the byte comparison; that trial was replaced. No opaque callee was renamed,
and the existing link-wide /alternatename directive is retained.

Validation:

- `./build.sh Code/GameEngine/Source/Common/W3DTerrainVisual_update.cpp`:
  1/1 matched, 37 bytes; string, float and import references pass.
- `find_declared_unmatched.py` on that source: all defined functions matched.
- [Header acceptance](header-accept.log): PASS, one header-queue row retired
  through `header_adopt_lane.py accept --class W3DTerrainVisual`.
- [Before](link-before.log) and [after](link-after.log) link previews both
  retain the source's 37 authored bytes and report LINKS. This is a local
  prediction, not a new census or a real game-link measurement.

No source path, ledger owner, pin, shared header or hatch changed. The
consolidation of the destination TU is a separate pass test; this adoption
alone claims no removed source file or completed TU merge.
