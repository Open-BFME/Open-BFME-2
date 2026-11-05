# UnitCrateCollide consolidation prerequisite

Inspected revision: `0627c1b1e30af754a1b6b9a902cba8803f7ac31c`.

The picker claimed the approved UnitCrateCollide TU and its sole clean donor,
`Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/UnitCrateCollideCtor.cpp`.
The other two sources are mixed and were not edited. The supported planner
surveyed the CrateCollide directory; its committed map is stale, so only the
merge engine's map rebuilt from current inputs was used for the trial.

`find_declared_unmatched.py` passes for both inputs. The supported
`tu_skeleton.py --merge .../UnitCrateCollide.cpp --dry-run` accepts no donors:
MSVC C2511 reports that `UnitCrateCollide(Thing *, const ModuleData *)` is
absent from the destination class declaration. No source or ledger was changed.

This is more than a missing declaration. The destination includes
`UnitCrateCollideView.h`: CrateCollide is virtual and UnitCrateCollide has its
module-data pointer at +4. The constructor donor instead declares a
nonvirtual CrateCollide with explicit pointer members at +0, +0xC and +0x10,
and assigns three TU-local dummy integers' addresses. Those are source facts;
masked instruction matching alone does not establish correct runtime tables.
Copying the donor's model into the destination is not a sound reconciliation.

Next: recover the target's complete CrateCollide/UnitCrateCollide inheritance
and table bindings against the existing BehaviorModule header and retail
tables, byte/link-verify the constructor separately, then retry the supported
merge. Do not hand-merge the body or change TU approval. Claims released.
