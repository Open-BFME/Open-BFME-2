# ArmySummary canonical-header adoption, 2026-11-04

Inspected base: `2d29f133e0daff7085a3326ddf05a32c0e5718bb`.
Picker: `next_work.py --claim`, class-header adoption for ArmySummary.

Five private ArmySummary declarations are replaced with the existing canonical
`Code/GameEngine/Include/GameLogic/ArmySummary.h`. No shared header changes.
The GetEntry unit keeps its existing eight-byte entry-array view, now applied
at canonical field40. The other four units use the existing canonical scalar
fields14/1C/2C and method declarations. Rva002B2AFDSelect includes its existing
LivingWorldBattle header first to retain that unit's Snapshot slot macros.
VslotSmallBodiesAD_Rva00349D02 already adopted the header; acceptance verifies
and retires its stale queued row without a source edit.

Target facts: the former private declarations and accesses agree on offsets
0x14, 0x1C, 0x2C and the entry range at 0x40/0x44. The canonical header already
records their layout evidence. This pass makes no new donor, semantic-name or
container-identity claim. In GetEntry, using a temporary reference to the array
changes register allocation; repeating the field-view expression preserves all
three complete rows. No row, pin, alias, hatch, data or identity key changes.

## Verification and debt retirement

- [Normal six-source build](final-build.log): **26/26** rows match; existing
  renumbered funclet labels resolve through their parent's unchanged EH data.
- [Frozen-source checks](frozen.log): all six sources pass before commit.
  All twenty selected sources also passed before edits.
- [First owning acceptance](accept.log): four ArmySummary header-queue rows
  retired by `header_adopt_lane.py accept`.
- [Second owning acceptance](accept-scalars.log): two further queue rows retired.
- [Combined ordinary link preview](link.log): **6/6 LINKS**, preserving
  **1,806 -> 1,806** census-linked bytes. Index census: 2026-11-04 11:27,
  `3a8028f34e`. This is a preview preservation result, not a new census or
  whole-image/runtime closure claim.

The six accepted units are GetEntry, VslotSmallBodiesAD_Rva00349D02,
ArmySummarySystemWalkOn, ArmySummarySystemLoad, Rva002B2AFDSelect and
LivingWorldAutoResolveApplyResults. The header queue itself is the inventory
of the fourteen remaining ArmySummary consumers. Their container/private-base,
constructor/table and transfer-surface disagreements remain separate work.
Next useful check: reconcile one remaining unit's existing entry-range view
with canonical field40, then run normal byte verification and owning acceptance.
No failed reconstruction remains in Code/.
