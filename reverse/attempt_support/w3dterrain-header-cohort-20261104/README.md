# W3DTerrainVisual canonical header: intersection, bibs, initialization

Inspected revision: `f15c898883`, following the update adoption in that commit.
Provider index: 2026-11-04 17:56, `8c757ea0db`.

Three more claimed donors now include W3DTerrainVisualClass.h rather than
redeclaring the class: W3DTerrainVisualIntersectTerrain.cpp,
W3DTerrainVisualAddFactionBibDrawable.cpp and W3DTerrainVisualInit.cpp,
all under Code/GameEngineDevice/Source/W3DDevice/GameClient/.

Target facts: the primary methods access the terrain pointer at complete-object
+0x14 and logic-height-map guard at +0x1C. The secondary SubsystemInterface
receiver is complete-object +4. Initialization and reset access the same members
through this receiver, at +0x10 and +0x18 respectively. The canonical declaration
accounts for these displacements. The explicit receiver projection on the existing
empty-base/reset call views preserves retail ECX, as in the update adoption.
Opaque terrain, water and counted-object operations retain their existing call
views. No new names or layouts are inferred for those callees.

Validation:

- Normal ./build.sh: intersection 1/1, bibs 4/4 and initialization/reset 9/9
  rows match; EH funclets remain verified against their parent graphs.
- find_declared_unmatched.py: all defined functions matched in each source.
- Native header acceptance: [intersection and bibs](cohort-accept.log) retire two
  entries; [initialization/reset](init-accept.log) retires one. These three queue
  rows are removed only by header_adopt_lane.py accept --class W3DTerrainVisual.
- Link previews: [intersection before](intersect-before.log),
  [bibs before](bibs-before.log) and [both after](cohort-after.log) retain
  249 and 1,556 authored bytes; [init before](init-before.log) and
  [after](init-after.log) retain 557. All report LINKS. These are predictions,
  not new census figures or a real game-link result.

No source paths, ledger ownership, shared headers, pins or hatches changed.
Existing link-wide alternatename directives are retained. This repairs header
prerequisites for consolidation; no TU merge or source-file reduction is claimed.
