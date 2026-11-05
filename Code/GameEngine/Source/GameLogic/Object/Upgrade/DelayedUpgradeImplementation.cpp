// cl: /DNDEBUG /MD
//
// DelayedUpgrade::upgradeImplementation, retail 0x004B3CC2 (121 bytes): slot
// 10 of the +0x10 UpgradeMux vtable 0x00C572E0 (the recipe of
// RemoveUpgradeUpgradeRemovalImplementation.cpp). Builds two cleared
// 0x80-byte upgrade masks (the rowed Rva001EAE6FHelper::clear80), has mux
// slot 11 fill them (the activation masks, Zero Hour's
// getUpgradeActivationMasks), then walks the Object's null-terminated
// behavior-module list (+0x244): each module's upgrade interface (its +0x0C
// interface slot 21) that answers the first mask (slot 0) gets the module
// data's +0x118 delay (slot 1).
typedef bool Bool;
class ModuleData;
#include "../../../../Include/Common/Rva001EAE6FHelper.h"
class Rva004B3CC2Upgrade
{
public:
	virtual Bool rvaSlot0(const Rva001EAE6FHelper *mask) = 0;
	virtual void rvaSlot1(int delay) = 0;
};
template <int N> class Rva004B3CC2Slots : public Rva004B3CC2Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class Rva004B3CC2Slots<0>
{
};
#include "../../../../Include/GameLogic/Module/UpgradeModule.h"
#include "../object.h"
struct UpgradeMaskType : Rva001EAE6FHelper
{
};
struct DelayedUpgradeModuleData
{
	unsigned char m_pad00[0x118];
	int m_delay;				// +0x118
};
class DelayedUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeImplementation();
};
void DelayedUpgrade::upgradeImplementation()
{
	int delay = ((const DelayedUpgradeModuleData *)m_moduleData)->m_delay;
	Object *obj = m_object;
	UpgradeMaskType activation;
	UpgradeMaskType conflicting;
	activation.clear80();
	conflicting.clear80();
	getUpgradeActivationMasks(activation, conflicting);
	for (BehaviorModule **module = obj->getBehaviorModules(); *module; ++module)
	{
		Rva004B3CC2Upgrade *upgrade = static_cast<Rva004B3CC2Upgrade *>(static_cast<BehaviorModuleInterface &>(**module).slot21());
		if (upgrade && upgrade->rvaSlot0(&activation))
			upgrade->rvaSlot1(delay);
	}
}
