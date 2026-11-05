# GiveUpgradeUpdate composition recheck, 2026-11-05

Inspected HEAD: 5856bb17130a46853742ae58f659f017a96a0517. No source or ledger edits were retained.

`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/`
completed: 928 sources, 136 investigation groups, no compile-trial groups.
The planner is investigation evidence; the current in-memory TU map approves
29 rows for GiveUpgradeUpdate.cpp, with four pull files and three mixed files.
`find_declared_unmatched.py` passes for all four pull files.

`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Update/GiveUpgradeUpdate.cpp --dry-run`
exits 2, accepted zero donors. All four sources are now census-linked, so the
2026-10-28 census-absent placement prerequisite no longer applies. Current
blockers are source composition:

- GiveUpgradeUpdateCtor.cpp: C2511, constructor absent from destination view.
  Its base is Rva0044EF5E; the destination and slot-8 helper use
  SpecialAbilityUpdate. `tu_views.py ... --dry-run` independently refuses this
  base-clause conflict. Matching sizes alone do not approve changing the base.
- GiveUpgradeUpdateModuleDataCtor.cpp: C2375, `_errno` redefinition with different
  linkage after composition. Its typed vector and destination's raw vector
  storage also require reconciliation through the registered canonical header.
- GiveUpgradeUpdateSlot8.cpp: C2504, SpecialAbilityUpdate base undefined in the
  composed include/declaration order. It already uses the canonical header,
  whereas the destination has a private SpecialAbilityUpdate declaration.

The merge tool requests canonical adoption for AICommandInterface, Drawable,
GiveUpgradeUpdateModuleData and SpecialAbilityUpdate in the destination, and
GiveUpgradeUpdateModuleData in its constructor. Resolve these contracts before
retrying composition. No link gain, source-file reduction or debt retirement
is claimed.

Separate stale-picker check: BoneFXDamage.cpp passes ./build.sh (9/9 rows);
ordinary link_check with DamageModule.cpp and Rva004B96CCDerived.cpp included
reports all three LINKS, matching the existing LINK-113 clearance. No new
repair or census gain is claimed there.
