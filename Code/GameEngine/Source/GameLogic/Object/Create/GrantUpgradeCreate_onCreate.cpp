// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
// ?onCreate@GrantUpgradeCreate@@UAEXXZ @0x004B901D 118B
// Target facts: GrantUpgradeCreate's matched constructor 0x004B8F62 stores the
// CreateModuleInterface vftable 0x00859428 at +0x10; its slot 0 is 0x004B901D
// and slot 1 is 0x004B9093. SupplyWarehouseCreate's constructor stores
// 0x008593E8 there instead, whose slot 0 is the matched
// SupplyWarehouseCreate::onCreate 0x004B8F22. The body sits between
// GrantUpgradeCreate's buildFieldParse 0x004B8FF0 and its module data
// constructor 0x004B90E1. (The earlier notes read slots 12/13 of
// SupplyWarehouseCreate's primary vftable 0x008593F8, which ends at 0x00859428.)
// Donor fact: Zero Hour GrantUpgradeCreate::onCreate grants the module data's
// upgrade unless the object's status hits the exempt mask; BFME 2 tests bit 2.
// Body: upgrade grant with header pre-checks; same tail as onBuildComplete
// 0x004B9093 (rowed findUpgrade 0x0026F26D, rowed getControllingPlayer 0x0028AFA9, pin-only
// Player::addUpgrade 0x002AE329, rowed Object::rva00293077 0x00293077,
// global TheUpgradeCenter) plus BfmeObject872Header copy 0x002CF108,
// data byte +0x1C zero check, data dword +0xC bit2 set check, header first
// dword bit2 clear check. Evidence: vtable slot, MI vptrs +0/+0xC/+0x10
// family precedent Rva004B8CDEDerived.cpp, prev Rva004B8F92, next 0x004B9093.
#include "ascii_string.h"

class UpgradeTemplate
{
public:
	int m_00;
	int m_type;
};

class Player;

class Upgrade;
enum UpgradeStatusType
{
	UPGRADE_STATUS_COMPLETE = 2
};

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

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Player
{
public:
	Upgrade *addUpgrade(const UpgradeTemplate *tmpl, UpgradeStatusType s, int x);
};

class BfmeObject872Header
{
	char m_bytes[16];
public:
	BfmeObject872Header(const BfmeObject872Header &other);
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
	virtual void onCreate();
	virtual void onBuildComplete();
};

class GrantUpgradeCreate : public Rva004B8CDEBase, public MiBase1, public GrantUpgradeCreateThird
{
public:
	void onCreate();
private:
	bool m_granted14;
};

void GrantUpgradeCreate::onCreate()
{
	void *data = m_data04;
	if (*(unsigned char *)((char *)data + 0x1C) != 0)
		return;
	BfmeObject872Header tmp(*(BfmeObject872Header *)((char *)m_object08 + 0x94));
	unsigned int moduleFlags = *(unsigned int *)((char *)data + 0x0C);
	moduleFlags >>= 2;
	_ReadWriteBarrier();
	if ((moduleFlags & 1) == 0)
		return;
	unsigned int objectFlags = *(unsigned int *)&tmp;
	objectFlags >>= 2;
	_ReadWriteBarrier();
	if ((objectFlags & 1) != 0)
		return;
	const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade(*(AsciiString *)((char *)m_data04 + 8));
	if (upgradeTemplate == 0)
		return;
	if (upgradeTemplate->m_type == 0)
	{
		Player *player = m_object08->getControllingPlayer();
		player->addUpgrade(upgradeTemplate, UPGRADE_STATUS_COMPLETE, 0);
	}
	else
		m_object08->rva00293077(upgradeTemplate);
}
