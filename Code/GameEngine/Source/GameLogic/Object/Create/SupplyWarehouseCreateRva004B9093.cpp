// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
// ?rva004B9093@SupplyWarehouseCreate@@UAEXXZ @0x004B9093 78B
// vslot 13 of SupplyWarehouseCreate vtable 0x008593F8: upgrade grant on create.
// Calls slot 3 bool gate, reads upgrade AsciiString at module-data +8 via
// primary +4, Object at primary +8, clears bool at +0x14, via rowed
// findUpgrade 0x0026F26D, rowed getControllingPlayer 0x0028AFA9, pin-only
// Player::rva002AE329 0x002AE329, rowed Object::rva00293077 0x00293077,
// global TheUpgradeCenter. Evidence: vtable slot, callers none, donor
// SupplyWarehouseCreate header, MI vptrs +0/+0xC/+0x10 family precedent
// Rva004B8CDEDerived.cpp, next GrantUpgradeCreateModuleData.
#include "ascii_string.h"

#include "../../../Common/RTS/PlayerUpgradeStatus.h"

class UpgradeTemplate
{
public:
	int m_00;
	int m_04;
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
extern "C" UpgradeCenter *TheUpgradeCenter;
#pragma comment(linker, "/alternatename:_TheUpgradeCenter=?TheUpgradeCenter@@3PAVUpgradeCenter@@A")

class Player
{
public:
	Upgrade *rva002AE329(const UpgradeTemplate *tmpl, UpgradeStatusType a, int b);
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

class SupplyWarehouseCreateThird
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
	virtual void rva004B9093();
};

class SupplyWarehouseCreate : public Rva004B8CDEBase, public MiBase1, public SupplyWarehouseCreateThird
{
public:
	void rva004B9093();
private:
	bool m_granted14;
};

void SupplyWarehouseCreate::rva004B9093()
{
	if (!isReady())
		return;
	AsciiString *name = (AsciiString *)((char *)m_data04 + 8);
	m_granted14 = false;
	const UpgradeTemplate *tmpl = TheUpgradeCenter->findUpgrade(*name);
	if (tmpl == 0)
		return;
	Object *obj = m_object08;
	if (tmpl->m_04 == 0)
	{
		Player *player = obj->getControllingPlayer();
		player->rva002AE329(tmpl, UPGRADE_STATUS_COMPLETE, 0);
	}
	else
		obj->rva00293077(tmpl);
}
