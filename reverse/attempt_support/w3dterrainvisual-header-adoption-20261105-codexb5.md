# W3DTerrainVisual header adoption, 2026-11-05

Inspected revision: `10b5d79f48`. Scope: the six queued W3DTerrainVisual
consumers; canonical headers unchanged. Target layout facts are documented in
`W3DTerrainVisualClass.h` and `TerrainVisualClass.h`; no new original names or
TU provenance inferred.

## Result

`W3DTerrainVisualLoad.cpp` and `W3DTerrainVisualXfer.cpp` now include the
existing canonical W3DTerrainVisual header. Load uses its three existing member
names. Xfer also removes its private TerrainVisual declaration. The water
Snapshot cast preserves the original pointer/transfer operation; it adds no
claim about the incomplete water class's inheritance.

The native xfer's first call targets RVA 0x00306A9B, already rowed as the
stdcall `Rva00306A9BDoXfer` in `Common/System/Xfer.cpp`. Use that provider
directly: the canonical public TerrainVisual::xfer spelling lacks the former
private view's protected spelling's existing pin/alias. No pin, alias or provider
was removed or added by hand.

## Verification

- Both original units byte-verified before editing; their objects were saved
  under untracked `build/terrain-header-before/`.
- `./build.sh` verified all eight rows across the two edited units, including
  the load parent's renumbered EH funclets and the shroud helper in the xfer TU.
- `find_declared_unmatched.py` passes for both final sources.
- `class_cleanup.runtime_graph` / `same_runtime`: load's complete non-debug
  object is identical. Xfer has no lost or added external definition; its only
  differences are the first call's verified callee spelling and `.drectve`.
  Normalizing that spelling and excluding the separately reviewed directive
  section gives identical runtime objects, including relocation bindings,
  weak defaults and COMDAT policies. The new directives are the existing
  canonical AsciiString header's seven alternatenames; all old directives remain.
- One W3DTerrainVisual `header_adopt_lane.py accept` over all six candidates
  accepted these two and retired exactly their two queue rows. Four unchanged
  private views were refused and remain queued. Xfer explicitly includes the base TerrainVisual header as required by its
  acceptance check; that base adoption is accepted through the same owning tool.
- Combined `link_check.py`: both LINKS, 1,348 -> 1,348 census-linked bytes
  (load 1,011; xfer 337), index census 2026-11-05 05:17 at `c95fcfcfcd`.
  This is a local prediction; no new real link or census is claimed.

The removed private TerrainVisual/W3DTerrainVisual declarations contain only
method declarations and fields; no inline body or alias was deleted. The
complete object comparisons additionally establish that no outside consumer
loses a definition from either edited unit.

## Remaining four consumers

- Rva00091E83Forwarders: opaque base padding and different neutral slot names
  block mechanical adoption; recover/reconcile those names before changing rows.
- VslotProxyForwarders: its `setWaterTransform(Matrix3D const*)` call-only view
  is absent from the target canonical interface; resolve that identity first.
- W3DGameClient: private 0x10/0x20 base/derived allocation views conflict with
  the canonical target-proven 0x14/0x24 extents; its factory needs separate
  source/row investigation, not a larger allocation hidden in this header swap.
- Destructor: automatic canonical-base substitution fails the destructor's byte
  comparison; reconcile its Rva002DAB18 base call and EH identities first.

These four trials were restored by the adoption tool; no nonmatching source is
retained. The remaining family is open under LINK-595.
