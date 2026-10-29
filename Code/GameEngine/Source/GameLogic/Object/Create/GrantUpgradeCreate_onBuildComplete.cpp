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
#include "ascii_string.h"

#include "../../../Common/RTS/PlayerUpgradeStatus.h"

class UpgradeTemplate
{
public:
	int m_00;
	int m_type;
};

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva00293077(const void *p);
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class Player
{
public:
	Upgrade *addUpgrade(const UpgradeTemplate *tmpl, UpgradeStatusType a, int b);
};

class Rva004B8CDEBase
{
public:
	virtual ~Rva004B8CDEBase();
	void *m_data04;
	Object *m_object08;
};

class MiBase1
{
public:
	virtual void f1();
};

class GrantUpgradeCreateThird
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual bool isReady();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void onBuildComplete();
};

class GrantUpgradeCreate : public Rva004B8CDEBase, public MiBase1, public GrantUpgradeCreateThird
{
public:
	void onBuildComplete();
private:
	bool m_granted14;
};

void GrantUpgradeCreate::onBuildComplete()
{
	if (!isReady())
		return;
	AsciiString *name = (AsciiString *)((char *)m_data04 + 8);
	m_granted14 = false;
	const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade(*name);
	if (upgradeTemplate == 0)
		return;
	Object *obj = m_object08;
	if (upgradeTemplate->m_type == 0)
	{
		Player *player = obj->getControllingPlayer();
		player->addUpgrade(upgradeTemplate, UPGRADE_STATUS_COMPLETE, 0);
	}
	else
		obj->rva00293077(upgradeTemplate);
}
