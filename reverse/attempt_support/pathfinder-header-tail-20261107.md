# Pathfinder canonical header: remaining four adoption units

Header queue item: adopt `Code/GameEngine/Include/GameLogic/AIPathfind.h` (class
Pathfinder). Landed: W3DViewDraw.cpp (inline `getFirstBridge`, +0x5C),
Rva002E916AFootprintCheck.cpp (friend `Rva002E7388Owner`, ICoord2D math view),
PathfinderSelectBridgeLayer.cpp (`m_layers[2..15]`, `m_triggers` +0x38).

Blocked units and the canonical storage each needs (all offsets are the views'
own, compile-proven by their matched rows; none is yet a header target fact):

| Unit | Lane refusal | Fields read that the header keeps opaque |
|---|---|---|
| PathfinderReset.cpp | nested `DebugPos` declarator | +0x14..+0x44 ints, +0x1BEB4/5/6 bools, +0x1BEB8 int, +0x1BEBC float[64], +0x1C0BC ListNode3C*[64], +0x1C9E0/4, +0x1D1E8/C |
| PathfinderRva002F83F5Neighbors.cpp | `m_pad000` no layout proof | +0x14 map lo/hi, +0x24 extent, +0x34 `MixFileInfoBuffer *m_closedList`, +0x38 `m_isTunneling`, +0x1BEB6, +0x1BEBC wall heights, +0x1C1CC `_STL::vector<Rva002F35AFHop>` |
| PathfinderSidewaysAttack.cpp | `m_pad000` no layout proof | as Neighbors plus `m_searchWord`/`m_destMineshaft` at +0x1C1D8 after the vector |
| pathfinder.cpp | `m_pad004` no layout proof | as Neighbors plus +0x1C1BC `m_moveAlliesDepth`, +0x1C1D8 mine shafts, +0x1D1F0 `PathfinderOpenQueue` |

Conflicts to settle first (target facts, not view names):
- The header's `IRegion2D m_extent` is at +0x14 (getCell 0x002E6D62); the
  views call +0x14 the map/clamp range and put a second extent at +0x24.
- The header comment's "64 four-byte strings at +0x1BFBC" vs Reset's
  `ListNode3C *[64]` at +0x1C0BC and the "tree at +0x1C1C0" vs the views'
  vector at +0x1C1CC.
- Putting `_STL::vector` and `PathfinderOpenQueue` in AIPathfind.h pulls
  STLport into ~211 consumers; prefer typed opaque members or a forward-declared
  wrapper with a static size check.

Next step: extend AIPathfind.h's tail with fields justified by constructor and
destructor stores (0x002F6E22 / 0x002F213F) and the reset 0x002F462C, then rerun
`header_adopt_lane.py adopt --apply` on the four units.
