// cl: /DNDEBUG /MD /EHsc
//
// Upgrade module dtors with the StealthUpgrade shape (StealthUpgrade.cpp,
// matched 0x004B530D): four compiler vptr restores at +0/+0xC/+0x10/+0x18,
// then a tail jmp to the UpgradeModule dtor 0x0046089D.
//
// ??1LocomotorSetUpgrade@@MAE@XZ @0x004B3EA0 32B: audited ??_G 0x004B3F3C;
//   slot 4 -> 0x004B3EC6 uses class-name string "LocomotorSetUpgrade".
// ??1AllowBannerSpawnUpgrade@@MAE@XZ @0x004B84EA 32B: audited ??_G 0x004B85B8;
//   slot 4 -> 0x004B8520 uses class-name string "AllowBannerSpawnUpgrade".
// Protected access (MAE) follows the StealthUpgrade precedent and the ZH
// memory-pool glue; the access specifier is not target evidence.

class Thing;
class ModuleData;

// Both classes are their shared headers', over the canonical UpgradeModule.h,
// so this unit's copies of their vftables equal the constructor units'.
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/GameLogic/Module/LocomotorSetUpgrade.h"
#include "../../../../Include/GameLogic/Module/AllowBannerSpawnUpgrade.h"

LocomotorSetUpgrade::~LocomotorSetUpgrade()
{
}


AllowBannerSpawnUpgrade::~AllowBannerSpawnUpgrade()
{
}
