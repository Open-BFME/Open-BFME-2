# TerrainLogic header adoption: filter and aerial height query

Inspected revision: `8441814e97f2fb09023996254544b1f7c06f01b3`.

- `Code/GameEngine/Source/GameLogic/AI/Rva002619C1FilterAllow.cpp`:
  replace its private sixteen-slot TerrainLogic declaration with the canonical
  header; slot 15 calls `isClearLineOfSight(start, end)`.
- `Code/GameEngine/Source/GameLogic/Map/AerialPathfinder.cpp`:
  replace its private seven-slot TerrainLogic declaration with the canonical
  header; slot 6 calls `getGroundHeight(x, y, 0)`.

Slot identities and signatures come from the canonical header's retail-table
contract. No new donor identity or layout claim is made. Both removed views
contain declarations only: no inline bodies, data definitions, or link-wide
aliases are removed. The shared header is unchanged.

Verification:
- Declared-unmatched checks pass before and after both edits.
- `./build.sh` over both files: 3/3 functions matched, all 3 float references
  verified; source, string and import checks pass.
- One `header_adopt_lane.py accept --class TerrainLogic` over both files:
  PASS for both; exactly two TerrainLogic header-queue rows retired.
- Combined `link_check.py` over both files: 2/2 link cleanly, preserving
  514 -> 514 census-linked bytes (250 filter + 264 aerial), index
  `2026-11-05 15:19` at `f44cbcf5b0`.

This clears these two consumer-adoption rows only. No new census, real-link,
image execution, seed-table repair, or class-wide clearance is claimed.
