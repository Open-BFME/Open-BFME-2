# PlayerUpgradeSpecialPower canonical bases and merge prerequisites

Inspected revision: `42fef5c7871da8771594cc79e1450e71a8eb110a`.
Worker: `yasinschroeder-codexb`; date: 2026-11-05.

The default picker claimed the PlayerUpgradeSpecialPower TU and its two
eligible donors. The consolidation planner was run under
`Code/GameEngine/Source/GameLogic/Object/SpecialPower/`. Its packet flags
provisional placement, mixed files, private declarations and compiler settings;
it does not approve additional moves. No paths or ledger rows were moved.

## Completed repair

`PlayerUpgradeSpecialPowerDoSpecialPower.cpp` now includes the canonical
SpecialPowerModuleInterface and SpecialPowerModuleData headers, uses
BehaviorModule as SpecialPowerModule's primary base, and casts Module's real
ModuleData pointer to its derived data type when accessing the upgrade names.
The private padded ModuleBase and private interface declarations are removed.
The existing canonical interface names slot 15 `startPowerRecharge(float)`;
the call retains its retail slot and argument. Target layout and slot facts are
documented in the included canonical headers; no donor layout is asserted as
target evidence.

`tu_views.py` successfully shared SpecialPowerModule's declarations between
the TU and the action donor. Its external-symbol/layout checks retained this
change. The resulting TU change only forward-declares Coord3D and declares
the already-rowed nonvirtual triggerSpecialPower method.

`header_adopt_lane.py accept --class SpecialPowerModuleInterface` passed for
the action donor and retired its one header-queue row. No other register debt
is retired; existing hatches, data identities and pins remain owned in place.

## Verification of the final source changes

- `./build.sh` for both changed sources: **11/11 matched rows**, string,
  float and import checks pass. Four renumbered funclet labels were verified
  through their parents' EH data.
- `find_declared_unmatched.py` for both sources passes. The TU retains its
  existing admitted destructor marker; no marker was added.
- Header acceptance passed again after the class-view rewrite.
- `link_check.py` for both sources: **2/2 link cleanly**, TU **211 -> 211**
  bytes and action donor **197 -> 197** bytes. These are local predictions
  against the 2026-11-05 05:17 census index at `c95fcfcfcd`, not a new census
  or a real-link result.

## Remaining merge prerequisites

The normal `tu_views.py` run measured **0 -> 0 accepted donors** using
`tu_skeleton.py --merge ... --dry-run` before and after its changes:

1. Sharing PlayerUpgradeSpecialPower's declarations adds the undefined
   `?doSpecialPower@PlayerUpgradeSpecialPower@@UAEXI@Z` name to the seed
   object's external-symbol set. The helper reverts that class rewrite.
   The merge still fails because the seed class does not declare
   doSpecialPower. Next establish the complete derived-class virtual contract
   and provider/consumer bindings before accepting a shared declaration.
2. PlayerUpgradeSpecialPowerModuleData's constructor TU has a regular class,
   but its destructor donor uses `__declspec(novtable)`. The helper reports
   a declspec conflict, and the destructor donor remains byte-rejected by the
   merge. Next reconcile the constructor/destructor vptr code generation;
   do not remove novtable or move the destructor without exact verification.
3. Five mixed files remain outside this merge; this pass does not split them
   or assert ownership for their other rows.

The previous LINK-133 action-donor entry described a historical vector-copy
provider failure. Its current local preview is clean; this pass changes no
vector-copy provider and claims no family-wide clearance.
