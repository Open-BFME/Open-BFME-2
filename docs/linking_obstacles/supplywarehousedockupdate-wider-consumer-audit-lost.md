### SupplyWarehouseDockUpdate wider consumer audit: lost DockUpdateModuleData destructor provider repaired (2026-11-01, halilkkaya-cx-o1)

Base `8aed0a4001` (stack rebased). The wider audit compared every unit the
stack's changed objects and 22 changed identities touch (3,684 units, from
`link_batch_audit.py`'s scope/consumer rules) between a worktree at the base
(its own objects, index brought to the base with `--update-index`) and the
rebased tip. The native seed no longer emits the unrowed Zero Hour COMDAT
`??1DockUpdateModuleData@@UAE@XZ`, its sole provider at the base, so
`SupplyCenterDockUpdate.cpp` (799 B) and `MonsterDockUpdateModuleDataCtor.cpp`
(97 B) went LINKS -> unresolved. Retail folds that destructor into the
Snapshot teardown 0x0049B47C (Monster ctor funclet 0x0078DB70 jumps there);
no BFME 2 unit spells it out of line. `MonsterDockUpdateModuleDataCtor.cpp`
now defines it inline in its existing private view (no row, no table or
ctor byte change; nothing else touches the new `??_7`/`??_G` COMDATs).
After the repair the same 3,684-unit comparison shows only the merge: the
seed goes 0 -> 767 B, the five absorbed donors' 550 B move into it, and no
unit loses its link (net +217 predicted bytes). The exact-base
`link_batch_audit.py` stays inconclusive only because ~3,600 consumers lack
strict receipts. Remaining: a retail-proven fold row for this destructor
needs a Snapshot-derived DockUpdateModuleData view (the native seed and
DockUpdate.cpp both model its table pointer explicitly).
