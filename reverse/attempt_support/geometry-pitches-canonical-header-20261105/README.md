# Geometry pitch-query canonical header adoption, 2026-11-05

Inspected revision: `5cfb4fb321`. Source: `Code/GameEngine/Source/Common/GeometryInfoCalcPitches.cpp`; retail row `0x006BE4C0`, 159 bytes.

Replace the private GeometryInfo declaration with `Code/GameEngine/Include/Common/Geometry.h`. Read the native center triple through canonical scalar storage at +0x18/+0x1C/+0x20, retaining the original copy and position-add order. The float math overloads, compiler profile, ledger row and existing link-wide alias are unchanged.

Verification:

- Normal `./build.sh` before and after: 1/1 exact, 159 bytes; final strict declaration audit passes.
- Owning `header_adopt_lane.py accept --class GeometryInfo` passes and retires exactly one header queue row. No other debt register changes.
- Current-object preview: LINKS, LINKED 159 -> 159 bytes against index `c95fcfcfcd`, 2026-11-05 05:17. This is a preview, with no census gain claimed.
- Object link facts: the only removed COMDAT is the unused private inline `getCenterPosition`, digest `bd6df221bf90`, 58 bytes. All remaining normalized COMDAT bytes/relocations, strong definitions, undefined names and weak externals equal the original. See `object-facts.json`.
- The published index reference graph has no incoming edge to either public or private `getCenterPosition` spelling. Its touches inventory contains only this provider for the private spelling; see `index-references.json`.
- A scan of all 139,631 `.obj` files under `build/` found no current match-object consumer, but did find a public-spelling undefined reference in historical `build/weapon-assistance-cleanup/Weapon-before.obj`. The pre-adoption/layout/composition scratch objects merely define the private spelling. See `all-object-reference-scan.json`. The alias and its hatch entry are therefore retained; this is not a claim that every historical object can link without them.

The supported consolidation planner reports Geometry prerequisites, not merge approval. The Geometry merge dry run still accepts no donors: incompatible overrides and byte/profile differences remain. This change removes one private-class/header prerequisite; it does not reduce the source count or establish a single compiler profile for Geometry.cpp. No source path, pin, shared header or gate change.
