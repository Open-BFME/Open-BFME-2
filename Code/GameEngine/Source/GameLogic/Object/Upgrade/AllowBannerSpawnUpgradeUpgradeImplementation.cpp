// cl: /DNDEBUG /MD
//
// AllowBannerSpawnUpgrade::upgradeImplementation, retail 0x004B8510 (8 bytes),
// and upgradeRemovalImplementation, retail 0x004B8518 (8 bytes): slots 10 and 8
// of the +0x10 UpgradeMux vtable 0x00C58FE8 installed by the matched
// AllowBannerSpawnUpgrade ctor; each only runs the UpgradeModule condition
// apply 0x004CE4A0 / removal 0x004CE4A8 on the module base (tail jumps).
typedef bool Bool;
class Object;
class ModuleData;
#include "../../../../Include/GameLogic/Module/ObjectModuleBase.h"
template <int N> class AllowBannerSpawnUpgradeMuxSlots : public AllowBannerSpawnUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AllowBannerSpawnUpgradeMuxSlots<0>
{
};
// UpgradeMux interface at +0x10: slot 8 upgradeRemovalImplementation, slot 9
// setUpgradeExecuted, slot 10 upgradeImplementation.
#include "../../../../Include/GameLogic/Module/UpgradeModule.h"
class AllowBannerSpawnUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
};
void AllowBannerSpawnUpgrade::upgradeImplementation()
{
	rva004CE4A0();
}
void AllowBannerSpawnUpgrade::upgradeRemovalImplementation()
{
	rva004CE4A8();
}
