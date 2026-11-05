# ElvenWood module-data header prerequisite

Inspected revision: `f38c47ad6755f90aeb1c133293f5e2408e9d4ebe`.
Scope: `WeaponChangeSpecialPowerModuleDataDtor.cpp`, with the approved
`ElvenWoodSpecialPower.cpp` merge inspected read-only.

The merge dry run accepted no donors. Its current diagnostics include an
undefined `SpecialPowerModuleData` base when composing canonical-header donors,
missing `WeaponChangeSpecialPowerModule::rva004C405D`, and byte failures for the
two STLport donors. The class-view report also finds differing SpecialPowerModule
and WeaponChangeSpecialPowerModule bases, differing module-data novtable
attributes, and a CloudBreak field-type conflict at +0x84. No merge was applied;
the committed TU map was not regenerated.

One prerequisite is repaired: the WeaponChange destructor donor now includes
the canonical SpecialPowerModuleData header. Its old private base extended to
+0x94, although the canonical base ends at +0x7C. Neutral derived storage retains
+0x7C..+0x93, followed by the existing strings at +0x94 and +0x98. The destructor
still calls the same base destructor and emits no derived vptr store.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/SpecialPower/WeaponChangeSpecialPowerModuleDataDtor.cpp`:
  4/4 rows match; both unwind labels are verified through the parent's EH graph.
- `find_declared_unmatched.py` on that source: all definitions matched.
- `eh_verify.py` on that source: EXACT 1, no missing objects or inexact EH rows.
- `header_adopt_lane.py accept --class SpecialPowerModuleData` on that source:
  PASS; the owning tool retired its one header-queue row.
- `link_check.py` on that source: LINKS, LINKED 84 -> 84 bytes against the
  2026-11-05 05:17 census at `c95fcfcfcd` (prediction, no new census claim).
- `check_csv.py`: OK.

The seed and competing EmitVtableTag emitters still need coordinated vtable
reconciliation before seed header adoption. The completed donor adoption does
not clear LINK-186 or make the merge pass. No source paths, aliases, pins,
function rows or data rows changed; no debt was retired outside header acceptance.
