// cl: /DNDEBUG /MD
//
// ?giveSelfUpgrade@UpgradeMux@@QAEXXZ, retail 0x0045230C, 33 bytes.
// UpgradeMux self-upgrade (frameless leaf: four virtual dispatches through
// the +0 vptr at slots 0x30/0x3C/0x28/0x24 with a 1 flag on the last).
// Called on the +0x20 UpgradeMux member by 10 behavior-ctor sites
// (0x4829F4/0x482DF0 plus family); donor ZH ctor tail backs the name.
// Shard (not graft): the UpgradeMux home TU carries the novtable leaf
// ctor, and same-TU virtuals would collide with its explicit vtable.

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

// ?giveSelfUpgrade@UpgradeMux@@QAEXXZ @0x45230C
void UpgradeMux::giveSelfUpgrade()
{
	performUpgradeFX();
	processUpgradeRemoval();
	upgradeImplementation();
	setUpgradeExecuted(true);
}
