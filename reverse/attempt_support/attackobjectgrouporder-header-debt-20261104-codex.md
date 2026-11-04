# AttackObjectGroupOrder header-debt retirement

Inspected revision: `b2d7f6da6f`; source unchanged by this repair.

`Code/GameEngine/Source/GameLogic/AI/AttackObjectGroupOrder.cpp` already
includes `Include/GameLogic/Module/AIUpdate.h` and uses the canonical
`AIUpdateInterface` and `AICommandInterface`. Its two header-queue rows still
describe a private `m_commands` field that this source no longer declares.

Retired both rows through their owning commands, each reporting PASS and one
retired row:

```
python3 tools/header_adopt_lane.py accept --class AIUpdateInterface Code/GameEngine/Source/GameLogic/AI/AttackObjectGroupOrder.cpp
python3 tools/header_adopt_lane.py accept --class AICommandInterface Code/GameEngine/Source/GameLogic/AI/AttackObjectGroupOrder.cpp
```

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/AI/AttackObjectGroupOrder.cpp`:
  5/5 matched; string, float and import checks passed.
- `find_declared_unmatched.py` on the TU and both constructor/transfer donors:
  all defined functions already matched.
- `link_check.py` on the TU: LINKS, 330 -> 330 census-linked bytes; census
  2026-11-04 02:25 at `5a13f2cd61`. This is a local preview, not a new census.
- Initial `check_csv.py`: OK, 99,438 function rows, 9,340 symbol rows,
  2,269 data rows. No source or ledger rows moved or changed.

The planner and fresh consolidation dry run still accept no donor. The
constructor donor conflicts with the implicit vftable (C2373); the transfer
donor needs `xfer` declared on the seed and its `GroupOrder` base (C2039/C2352).
`tu_views.py` confirms the flat seed disagrees with both donors' base clauses.
No reconstruction was written. The next consolidation prerequisite remains
reconciling the hierarchy and vtable declarations; retiring these two stale
header rows does not clear that obstacle.
