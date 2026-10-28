# Coord3D companion adoption, 2026-10-28

Inspected base: `20c2620db2211c082d1bc38350ed115cd2be6641`.
Ordinary preview index: `41c28839bf`, published 2026-10-28 11:08,
underlying census `c8734bec0c`. This is header-debt retirement, not a
census-linked-byte or image-ownership gain.

## Accepted scope

The default picker claimed `class:Coord3D`. The library owner and matrix
consumers retain the class-key and interface prerequisites in LINK-018;
their previous rejected trials were not repeated.

| Source (basename) | Matched rows | Change | Ordinary linked bytes |
| --- | ---: | --- | ---: |
| BridgeObjectCtor.cpp | 7 | Existing derived companion accepted | 1,683 -> 1,683 |
| BridgeBehaviorHandleObjectsOnBridgeOnDie.cpp | 4 | Existing derived companion accepted | 448 -> 448 |
| OneRingPenaltyUpdate.cpp | 5 | Existing inline companion accepted | 482 -> 482 |
| AIStructureCreepTactic.cpp | 52 | Existing derived companion accepted | 0 -> 0 |
| W3DViewGetAxisAlignedViewRegion.cpp | 3 | Replace private coordinate with derived companion | 389 -> 389 |
| stlport_vector_geometryshape_base.cpp | 2 | Replace private coordinate with constructor companion | 121 -> 121 |

All six pass `header_adopt_lane.py accept --class Coord3D`; only that
command removes their six queue rows. The first four source files are
unchanged. The tool now recognizes the companions after `e46cd47132`;
the old include-recognition false reject no longer applies to these files.
AIStructureCreepTactic retains the existing selected Object-pointer-vector
destructor, insert-overflow and push-back conflicts. Acceptance preserves
its zero census-linked coverage; it does not clear those conflicts.

The geometry-vector unit requires a user copy constructor to copy its three
floats. `Coord3DCtorView.h` supplies that existing contract. The viewport
requires external constructor/destructor callbacks for its four-coordinate
array, while its Region3D extent members must remain trivial. The existing
derived companion's external-lifetime switches and a Coord3DBase alias
preserve those two distinct requirements. No shared header changes.

Normal builds preserve all five rows in the two edited units. The complete
viewport EH graph is EXACT. Before/after COFF comparisons using
`link_census._comdat_sections` and `_coff_symbols` preserve all ten geometry
and three viewport external COMDAT byte/relocation digests, their external
definition/reference sets (12 entries each), and weak bindings.
Both edited units pass `link_check.py --prepare-current` with strict receipts.
Frozen-file checks pass before and after each edit. The six accepted units
have 73 matched rows; their twelve EH graphs are EXACT. Their combined
ordinary preview preserves 3,123 authored linked bytes. Full external
consumer selection remains for the outgoing batch audit and normal census.

Post-handover batch check against `bef6d6aaef3e24555350f14542c7b158b5bba9b2`:
all six accepted units and the two pre-existing SDK serializer changes have
strict receipts, with 75/75 function rows exact. The batch audit remains
INCONCLUSIVE: index `41c28839bf` predates that base and affected consumer
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Carry these
declaration changes and that consumer into the next normal census; the
bounded source checks do not establish complete consumer selection.

The commit hook's shadow identity warning names the geometry unit's
`??0Coord3D@@QAE@ABU0@@Z` copy. Its pre-edit and post-edit external COMDAT
fingerprints are identical: 25 bytes, digest `79571e26f4e7`, no relocations.
This is an inherited copy-selection prerequisite, not a new body divergence;
no identity debt is retired or registered by this change.

## Home-point adoption remains blocked by provider visibility

`Rva00506CF5HomePoint.cpp` was tested with `Coord3DCtorView.h` followed by
`Coord3DBase.h`. Replace the initial inline `set` call with three explicit
field stores and pass `asBase(position)` to HomeVector3's existing base-copy
constructor. This replaces its private derived coordinate and permits
removing its class-gate exemption without changing the six matched rows.
All thirty original external COMDAT digests and all original external
definitions/references remain unchanged; the shared `asBase` inline helper
is the only added external definition. Parent EH mapping resolves the three
renumbered unwind labels through the verified graph.

Acceptance nevertheless refuses the ordinary preview's 763 -> 0 result.
The restored original has exactly the same unresolved references:

- `?Gen00DD0870@@3UCoord3DBase@@A`
- `?Rva00506C82Find@@YAPAVGameSlot@@PBURva00506C82Arg@@@Z`

Both are owned by consolidated `Common/AIBaseBuilder.cpp` in the current
data/function ledgers. The paired preview refuses that provider because it
is absent from census `c8734bec0c`. The restored home-point source and current
provider pass nine function rows plus the provider's data row. The home-point
source, exemption and queue row are restored exactly. A blocked false-reject
entry is recorded through `re_log.py`; no acceptance check was bypassed.

Next: obtain the normal census/index containing AIBaseBuilder.cpp, or resolve
the provider-aware retirement diagnostic in a separate tooling change, then
repeat the bounded companion trial. The class-key, library member-growth
and other lifetime prerequisites in LINK-018 remain open.
