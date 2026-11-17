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

## Native prefix recovered (2026-11-17, 6f05eee4dbbdde3d67d9259349b2f6d028d472db)

The formerly pending Dock destructor fold is now proved and rowed: the shared DockUpdateModuleData declaration inherits the real 31-slot ModuleData prefix and emits complete seven-byte Snapshot teardown at0049B47C. MonsterDock's source table851DA8 has31/31 native bindings and body/relocation matches; the current owning bridge predicate passes. The preserved SupplyCenter provider consumer and all eleven header consumers pass197/197 code rows and54 data rows; both Monster EH graphs are EXACT. One header-queue row retires through acceptance. [Source/table proof and limits](../../reverse/attempt_support/monster-dock-native-prefix-20261117-root20.md).

The broader current real-link result is still unmeasured. Old-index previews preserve the tested lifetime/provider scope; one ModelConditionUpgrade table flag is demonstrably unchanged across the header edit. No claim repeats the historical3684-unit audit or retires the published bridge before a new real run. Contract regeneration's final-Snapshot-table conflict is a separate false reject; the contract is unchanged.

2026-11-17 (80848a58e08669410010d64d6a40ec90eb30554e): DockUpdateCtor.cpp also adopts the recovered shared data prefix. All runtime contents and bindings are unchanged;18/18 rows and constructorEH pass, strict54/54 providercohort passes, and the owning acceptance retires one queue row. [Consumer proof](../../reverse/attempt_support/dock-constructor-header-20261117-root20.md). SupplyCenter's private16-byte prefix remains: its unused12-byte array cannot map to one canonicalfield; preparation restored and [false reject preserved](../../reverse/attempt_support/supplycenter-dock-padding-20261117-root20.md) for separate tooling correction. No new game or real-link clearance.
