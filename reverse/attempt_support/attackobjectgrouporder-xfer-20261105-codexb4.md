# AttackObjectGroupOrder transfer reconciliation (2026-11-05)

Inspected revision: d7db81b686. Scope: the seed and
`Code/GameEngine/Source/GameLogic/AI/AttackObjectGroupOrderXfer.cpp`.

The inherited unfinished edits made the seed derive from `GroupOrder` while
retaining its placeholder virtual declarations. They fail C2555 because the
seed declares `slot10` returning void and the shared base returns int.

Keep the seed's existing vfptr and 0x18-byte prefix view. Declare its proven
slot 3 as `xfer(Xfer *)`; give the transfer donor the same declaration and
member layout. The base transfer call uses the shared `GroupOrder` view at
this same address and explicitly qualifies `GroupOrder::xfer`, preserving the
retail direct call. The canonical Coord3D triple is transferred through
`asBase(m_pos)`. This reconciles existing matched code; it does not recover a
class hierarchy or add any row, pin, alias or hatch.

Verification before merge:

- `./build.sh` on both sources: 6/6 matched (330 + 79 bytes).
- `find_declared_unmatched.py` on each: all definitions already matched.
- Current-object `link_check.py`: both LINKS, 409 -> 409 predicted bytes,
  compared with census 2026-11-05 05:17 at c95fcfcfcd. Census-only also reports
  both LINKS. These are predictions, not a new census measurement.
- `tu_skeleton.py --merge .../AttackObjectGroupOrder.cpp --dry-run` accepts
  the seed and transfer donor, preserves all six rows, and passes its link
  guard. Constructor donor still fails C2373 (explicit vtable data conflicts
  with the compiler vtable); three mixed satellites remain outside the merge.
- No source-keyed debt or header-queue rows name these two files in the
  gate, code-identity, data-check, hatch, header or ms-header registers.

Next step: apply the verified transfer merge through `tu_skeleton.py`, audit
path consumers and refreshed queues, and verify the final TU. The constructor
and mixed satellites remain separate work.
