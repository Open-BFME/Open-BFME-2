// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// stlport
// ?rva004B901D@SupplyWarehouseCreate@@UAEXXZ @0x004B901D 118B
// vslot 12 of SupplyWarehouseCreate vtable 0x008593F8: upgrade grant with
// header pre-checks. Same tail as slot 13 0x004B9093 (rowed findUpgrade
// 0x0026F26D, rowed getControllingPlayer 0x0028AFA9, pin-only
// Player::rva002AE329 0x002AE329, rowed Object::rva00293077 0x00293077,
// global TheUpgradeCenter) plus BfmeObject872Header copy 0x002CF108,
// data byte +0x1C zero check, data dword +0xC bit2 set check, header first
// dword bit2 clear check. Evidence: vtable slot, MI vptrs +0/+0xC/+0x10
// family precedent Rva004B8CDEDerived.cpp, prev Rva004B8F92, next 0x004B9093.
#include "ascii_string.h"

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

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Player
{
public:
	void rva002AE329(const UpgradeTemplate *tmpl, int a, int b);
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
	virtual void rva004B901D();
	virtual void rva004B9093();
};

class SupplyWarehouseCreate : public Rva004B8CDEBase, public MiBase1, public SupplyWarehouseCreateThird
{
public:
	void rva004B901D();
private:
	bool m_granted14;
};

void SupplyWarehouseCreate::rva004B901D()
{
	void *data = m_data04;
	if (*(unsigned char *)((char *)data + 0x1C) != 0)
		return;
	BfmeObject872Header tmp(*(BfmeObject872Header *)((char *)m_object08 + 0x94));
	unsigned int f = *(unsigned int *)((char *)data + 0x0C);
	f >>= 2;
	_ReadWriteBarrier();
	if ((f & 1) == 0)
		return;
	unsigned int t = *(unsigned int *)&tmp;
	t >>= 2;
	_ReadWriteBarrier();
	if ((t & 1) != 0)
		return;
	const UpgradeTemplate *tmpl = TheUpgradeCenter->findUpgrade(*(AsciiString *)((char *)m_data04 + 8));
	if (tmpl == 0)
		return;
	if (tmpl->m_04 == 0)
	{
		Player *player = m_object08->getControllingPlayer();
		player->rva002AE329(tmpl, 2, 0);
	}
	else
		m_object08->rva00293077(tmpl);
}
