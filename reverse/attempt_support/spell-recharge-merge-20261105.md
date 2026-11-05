# SpellRechargeModifierUpgrade consolidation trial

Base: `e93d5b4890`. The allocated TU passed `consolidation_queue.py
--check-tu`; the scoped planner passed its freshness check. Its plan has eight
approved rows, two donor files and two mixed sources. The mixed-source split
inspection found no row in `FireWeaponWhenDeadBehaviorDerived.cpp` approved
for this TU. The guarded merge dry run accepted no donor.

`SpellRechargeModifierUpgradeCtor.cpp` fails with C2511: the definition
`SpellRechargeModifierUpgrade(Thing *, const ModuleData *)` has no matching
declaration in the class. The link guard lists both census-linked units and
blocks the merge. No claims or source edits were made. Next: reconcile the
constructor declaration in a source-repair seat, then rerun the guarded merge.
