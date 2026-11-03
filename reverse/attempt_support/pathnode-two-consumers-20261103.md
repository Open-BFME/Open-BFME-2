# PathNode adoption in append and advance consumers

Inspected base: `678d949f99`. Scope: `PathAppendNode.cpp` and
`PathClosestPoint.cpp` under `Code/GameEngine/Source/GameLogic/AI/`.

Both consumers now include the existing canonical
`Code/GameEngine/Include/GameLogic/PathNode.h` instead of defining a private
PathNode. The header's target evidence establishes the 0x24-byte layout:
next/previous/optimized links at +0/+4/+8, Coord3D at +0x0C, layer at +0x18,
optimization flag at +0x1C, and portal ID at +0x20. Those offsets agree with
both removed declarations. Append's previous/optimized/position/waypoint
accesses map to m_prev/m_nextOpti/m_pos/m_portalID; advance's node accesses
map to m_next/m_nextOpti/m_pos. Its separate `position` parameter stays intact.
No shared header, symbol identity, source path, pin or alias changes.

Verification:

- `find_declared_unmatched.py` before and after passes for each file; append
  retains its pre-existing absent-from-retail anchor.
- Normal `./build.sh` before and after: append 2/2 rows (132 + 14 bytes),
  advance 1/1 row (328 bytes); three float literals also verified for advance.
- `header_adopt_lane.py accept --class PathNode FILE` passes for each file
  and retires exactly those two rows from `reverse/header_queue.tsv`.
- Published index fetch keeps census 2026-11-03 20:03 at `8661f15284`.
  Combined `link_check.py` reports both units LINKS: 146 -> 146 and
  328 -> 328, combined 474 -> 474 bytes. This is a scoped preview, not a
  new census or real-link measurement.

The automatic adoption queue had refused ambiguous broad field renames.
Only the proven PathNode member accesses were changed manually here. Other
PathNode queue entries remain independent work; the canonical header is frozen.
No linking obstacle's status or next step changed in this header-only cleanup.
