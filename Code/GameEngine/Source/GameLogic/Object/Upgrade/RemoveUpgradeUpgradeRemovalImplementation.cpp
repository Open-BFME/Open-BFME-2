// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
//
// RemoveUpgradeUpgrade::upgradeRemovalImplementation, retail 0x004B7F27 (22
// bytes): slot 8 of the +0x10 UpgradeMux vtable 0x00C58DD8 installed by the
// matched RemoveUpgradeUpgrade dtor: the UpgradeModule condition removal
// 0x004CE4A8, then setUpgradeExecuted(false) (vslot 9).
#include "RemoveUpgradeUpgradeView.h"

void RemoveUpgradeUpgrade::upgradeRemovalImplementation()
{
	rva004CE4A8();
	setUpgradeExecuted(false);
}
