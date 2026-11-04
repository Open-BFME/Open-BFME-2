# SpellRechargeModifierUpgrade canonical base adoption

Inspected revision: `2e42e2b0b6`, 2026-11-04.
Scope: `Code/GameEngine/Source/GameLogic/Object/Upgrade/SpellRechargeModifierUpgrade.cpp`.

The unit's private UpgradeModule had BehaviorModule at +0, UpgradeMux at
+0x10, explicit storage at +0x14, and a leaf-owned interface at +0x18.
The existing canonical UpgradeModule header already owns that +0x18
interface and occupies 0x1C bytes. Replacing the private bases and removing
the redundant leaf interface retains its own interface at +0x1C and bool
at +0x20. Calls to mux slots 0 and 9 now use isAlreadyUpgraded and
setUpgradeExecuted(true), preserving the target dispatch.

Verification:

- `find_declared_unmatched.py` before and after: all defined functions matched.
- `./build.sh Code/GameEngine/Source/GameLogic/Object/Upgrade/SpellRechargeModifierUpgrade.cpp`:
  5/5 matched; string, float and import reference checks passed.
- `header_adopt_lane.py accept --class UpgradeModule` for this source: PASS;
  the owning tool retired its one header queue row.
- `link_check.py` for this source: LINKS, LINKED 565 -> 565 bytes, against
  census 2026-11-04 02:25 at `5a13f2cd61`. This is a per-unit prediction;
  no new census or real-link result is claimed.

The separate UpgradeMux queue row is retained. UpgradeModule.h defines its
own UpgradeMux declaration and does not include the separately registered
UpgradeMux.h; default UpgradeMux acceptance refuses the missing include.
An exploratory acceptance with an explicit alternate header passed, but its
queue removal was restored because it does not establish adoption of the
registered UpgradeMux header. Reconcile those shared declarations and their
provider signatures before retiring that row. Constructor and destructor
scaffolds remain outside this change.
