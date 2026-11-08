// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
// ?onBuildComplete@GrantUpgradeCreate@@UAEXXZ @0x004B9093 78B
// Target facts: slot 1 of GrantUpgradeCreate's CreateModuleInterface vftable
// 0x00859428 (stored at +0x10 by its matched constructor 0x004B8F62; slot 0 is
// onCreate 0x004B901D). The earlier notes read slot 13 of SupplyWarehouseCreate's
// primary vftable 0x008593F8, which ends at 0x00859428.
// Donor fact: Zero Hour GrantUpgradeCreate::onBuildComplete returns unless
// shouldDoOnBuildComplete(), runs CreateModule::onBuildComplete (clears the flag)
// and grants the module data's upgrade.
// Body: calls slot 3 bool gate, reads upgrade AsciiString at module-data +8 via
// primary +4, Object at primary +8, clears bool at +0x14, via rowed
// findUpgrade 0x0026F26D, rowed getControllingPlayer 0x0028AFA9, pin-only
// Player::addUpgrade 0x002AE329, rowed Object::rva00293077 0x00293077,
// global TheUpgradeCenter. Evidence: vtable slot, callers none, MI vptrs
// +0/+0xC/+0x10 family precedent
// Rva004B8CDEDerived.cpp, next GrantUpgradeCreateModuleData.
#include "../../../../Include/GameLogic/Module/CreateModuleClass.h"
#include "ascii_string.h"

#include "../../../Common/RTS/PlayerUpgradeStatus.h"

#include "../../../../Include/Common/Upgrade.h"

class Player;

#include "../object.h"

extern UpgradeCenter *TheUpgradeCenter;

#include "../../../../Include/Common/Player.h"

// Use the retail CreateModule hierarchy: its +0x10 interface owns the
// slot-3 gate and the +0x14 flag cleared by onBuildComplete.
class GrantUpgradeCreate : public CreateModule
{
public:
	virtual void onCreate();
	virtual void onBuildComplete();
};

void GrantUpgradeCreate::onBuildComplete()
{
	if (!shouldDoOnBuildComplete())
		return;
	AsciiString *name = (AsciiString *)((char *)getModuleData() + 8);
	CreateModule::onBuildComplete();
	const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade(*name);
	if (upgradeTemplate == 0)
		return;
	Object *obj = getObject();
	if (upgradeTemplate->m_type == 0)
	{
		Player *player = obj->getControllingPlayer();
		player->addUpgrade(upgradeTemplate, UPGRADE_STATUS_COMPLETE, 0);
	}
	else
		obj->rva00293077(upgradeTemplate);
}
