# UnleashSpecialPower consolidation trial

Inspected base `5326e1f969`. The consolidation picker claimed the approved
`UnleashSpecialPower.cpp` scope and its two whole-file donors. The evidence
planner's stale committed map reported these sources unresolved; the skeleton
rebuilt its map in memory and reported 11 approved rows, one mixed source and
no refused donors. No regenerated map was committed.

The supported merge dry run accepted neither donor. The seed's
`UnleashSpecialPower` view has only `getModuleNameKey`; it lacks the
`rva004CE0D9` and `triggerAbilityEffect` declarations required by the two
respective donors. `tu_views.py` found conflicting bases for the three views:
the seed has none, the first donor uses `SpecialPowerModule` and a secondary
interface, and the second uses `SpecialAbilityUpdate`. It also found different
virtual slot 26 declarations in the two `BehaviorModuleInterface` views and
different `SpecialAbilityUpdate` slot 0 declarations. Its verified mechanical
Object-view reconciliation did not change the accepted donor count (0 to 0),
and was reverted.

The existing row history places `getModuleNameKey` in primary slot 4 and
`triggerAbilityEffect` in slot 17; the 0x004CE0D9 donor models a secondary
interface at +0x20. These observations do not alone establish the full base
and virtual-table layout needed to combine the views. Next establish compatible
primary and secondary interface declarations and the common slot 26 return
view from retail evidence, then verify the affected units and their selected
providers before retrying the guarded merge. The mixed `ModuleUpdateDtors.cpp`
source remains outside this trial. No source path moved, no census gain is
claimed, and all trial source changes were reverted.
