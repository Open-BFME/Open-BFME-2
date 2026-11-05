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

## Applied merge and outgoing-batch audit

Applied through `tu_skeleton.py --merge`: absorbed the transfer donor, removed
one source file and repointed its one function/map source column. The TU map
assignment and approval evidence did not change. The other five bodies remain
in place. Constructor C2373 and the mixed satellites remain the next work.

The final transfer uses an explicit `Coord3DBase &` view of the canonical
triple. This keeps the same bytes while avoiding an extra emitted `asBase`
helper whose COMDAT the shadow identity check could not certify. Final staged
code-identity check: six rows, zero new findings.

Final verification:

- Merged TU: 6/6 byte-matched (409 own bytes); no declared-unmatched bodies.
- Link preview: merged TU LINKS, 330 -> 409 bytes; constructor LINKS,
  147 -> 147 bytes. The increase is moved ownership, not new census coverage.
- Converged data: zero second names and unjudged rows; shadow data: zero
  findings. EH: zero EH-bearing rows in this TU. TU ownership, case-collision,
  CSV integrity and diff-whitespace checks pass.
- Microsoft-header inventory refreshed for destination and deleted donor:
  zero local Microsoft declarations, no queue changes. Header queue has no
  row naming either file. The merged TU includes the shared GroupOrder header
  and does not define a private GroupOrder class.
- No gate/identity/data-check/hatch/header/MS-header/flag/data-ledger key was
  owned by the absorbed file. No debt retirement or alias removal is needed.

Audited the complete pending path batch against origin/master
`40a6d245b5621bd0817fac2910ecbda05bcbc23c`, including the earlier PhysicsBehavior
constructor/pool-key absorptions and this transfer absorption. Combined old
path/basename searches across tooling, hooks, workflows, Code and docs found
no active path consumer requiring an update. Remaining mentions are source
origin/evidence comments and historical census/deleted-row records. Active
ledgers, ownership columns, protected registers, queues and doxygen inputs do
not name any of the three removed files. This audit does not reword historical
provenance.

All five changed Code sources in the outgoing batch pass normal byte checks:
54/54 rows, 23 literals plus three empty-string references, 18 float literals,
and 13 funclet pins checked through parent EH data. `link_check.py
--prepare-current` then produced strict reusable receipts for those five
explicit sources without updating the census/index/status.

The outgoing-batch link audit remains **INCONCLUSIVE**: its index predates the
outgoing base, and affected unchanged consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. See [latest audit](attackobjectgrouporder-batch-link-20261105-codexb4.txt).
Carry the changed providers, removed providers and affected consumers into the
next scheduled census. The composition guard and local previews pass; the
complete outgoing batch is not claimed link-clean. No census or runtime gain
is claimed. Runner publication currently waits for the maintainer lock.
