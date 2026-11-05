# HordeMeleeSwarm setter consolidation

Inspected base: `7b65b04886`; declaration trial: `87f3925ad4`.

The default picker claimed the seven-file HordeMeleeSwarm consolidation
scope. The original `tu_views.py` run accepted zero donors and wrote no
changes: the HordeMeleeSwarm base clauses disagree, and the Object superset
fails the update unit's SwarmAI accesses. The original dry run rejects both
44-byte setters because the WWLib destination omits their declarations.

Trial: add the existing virtual `setUnitRotating(int)` and
`setUnitArrived(int)` declarations to the destination. Its nine rows still
byte-match (1,947 bytes), with seven float literals verified and no newly
unmatched body. Ordinary `link_check.py` reports the destination and both
setters LINKS, preserving 2,035 bytes against census 2026-11-05 05:17 at
`c95fcfcfcd`. This preview did not certify the vtable's other consumers.

The supported `tu_skeleton.py --merge ... --dry-run` rejects the trial:
`breaks another unit's copy of ??_7HordeMeleeSwarm@@6B@`. It accepts zero
donors. The seed's constructor emits a different vtable after adding virtual
members; `FamilyDeletingDtors_Rva005843DA.cpp` still emits its minimal view
through `HordeMeleeSwarm(EmitVtableTag *)`. Native ledger evidence places the
setters at slots 10 and 11, so appending them to a destructor-only view does
not recover retail's table. This is a source-identity prerequisite, not a
false rejection. The ordinary three-unit preview was insufficient evidence
to publish the declaration-only prerequisite; it was handed to the runner
before the merge verdict arrived, so the correction is a new commit.

The correction restores the destination's original declaration and keeps
every source path and ledger row. No merge, debt retirement, census gain or
source-file reduction is claimed. Other dry-run failures remain: the update
unit's incompatible class view, the deleting-dtor emitter constructor,
StlSweepW4Rva00584405 byte loss, and the resize donor's allocator/vector
redefinitions. The existing element-identity issue remains LINK-064.

Next: reconcile the constructor and deleting-destructor emitter against
retail's complete vtable and existing row identities before retrying the
two setters. Verify the whole emitter/provider cohort with the TU merger's
link guard, not only the ordinary preview. Do not repeat the declaration-only
trial. Restored destination: 9/9 byte matches; declaration audit passes.
