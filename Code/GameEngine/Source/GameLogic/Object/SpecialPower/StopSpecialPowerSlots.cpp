// cl: /DNDEBUG /MD
//
// Two StopSpecialPower overrides on the interface vtable 0x00C5DE08 its
// matched ctor 0x004C676C installs at +0x10, compiled with that subobject
// this. The ctor clears the +0x34 pointer these use: the behavior module of
// our Object (from the null-terminated module array at Object +0x244) whose
// +0x0C interface's slot 8 answers slot 0 for the module data's +0x7C value.
// Names are by address.
//
// ?isReady@StopSpecialPower@@UAE_NXZ, retail 0x004C683C, 111 bytes:
// slot 1; finds and keeps that module (false without a +0x7C value or a
// match), then answers slot 2 of what its +0x0C interface's slot 25 gives,
// true when that is null.
// ?doSpecialPower@StopSpecialPower@@UAEXH@Z, retail 0x004C67B9, 34 bytes:
// slot 10 (argument unread); when slot 1 holds, runs slot 17 of the kept
// module's slot-8 answer.

class Thing;

class Rva004C683CPower
{
public:
	virtual bool slot0(int key) = 0;
	virtual void gap1() = 0; virtual void gap2() = 0; virtual void gap3() = 0; virtual void gap4() = 0;
	virtual void gap5() = 0; virtual void gap6() = 0; virtual void gap7() = 0; virtual void gap8() = 0;
	virtual void gap9() = 0; virtual void gap10() = 0; virtual void gap11() = 0; virtual void gap12() = 0;
	virtual void gap13() = 0; virtual void gap14() = 0; virtual void gap15() = 0; virtual void gap16() = 0;
	virtual void slot17() = 0;
};

class Rva004C683CState
{
public:
	virtual void gap0() = 0; virtual void gap1() = 0;
	virtual bool slot2() = 0;
};

class Rva004C683CModuleIface
{
public:
	virtual void gap0(); virtual void gap1(); virtual void gap2(); virtual void gap3();
	virtual void gap4(); virtual void gap5(); virtual void gap6(); virtual void gap7();
	virtual Rva004C683CPower *slot8();
	virtual void gap9(); virtual void gap10(); virtual void gap11(); virtual void gap12();
	virtual void gap13(); virtual void gap14(); virtual void gap15(); virtual void gap16();
	virtual void gap17(); virtual void gap18(); virtual void gap19(); virtual void gap20();
	virtual void gap21(); virtual void gap22(); virtual void gap23(); virtual void gap24();
	virtual Rva004C683CState *slot25();
};

struct Rva004C683CModule
{
	unsigned char m_pad00[0x0C];
	Rva004C683CModuleIface m_iface; // +0x0C
};

class Object
{
public:
	unsigned char m_pad000[0x244];
	Rva004C683CModule **m_modules; // +0x244 (null-terminated)
};

struct StopSpecialPowerModuleData
{
	unsigned char m_pad00[0x7C];
	int m_7C; // +0x7C
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class SpecialPowerModuleInterface
{
public:
	virtual void gap0() = 0;
	virtual bool isReady() = 0;
	virtual void gap2() = 0; virtual void gap3() = 0; virtual void gap4() = 0; virtual void gap5() = 0;
	virtual void gap6() = 0; virtual void gap7() = 0; virtual void gap8() = 0; virtual void gap9() = 0;
	virtual void doSpecialPower(int unused) = 0;
};

class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
protected:
	unsigned char m_pad14[0x34 - 0x14];
};

class StopSpecialPower : public SpecialPowerModule
{
public:
	virtual bool isReady();
	virtual void doSpecialPower(int unused);
private:
	Rva004C683CModule *m_34; // +0x34
};

// ?isReady@StopSpecialPower@@UAE_NXZ @0x004C683C
bool StopSpecialPower::isReady()
{
	if (!m_34)
	{
		if (reinterpret_cast<const StopSpecialPowerModuleData *>(m_moduleData)->m_7C == 0)
			return false;
		for (Rva004C683CModule **m = m_object->m_modules; *m; ++m)
		{
			Rva004C683CPower *power = (*m)->m_iface.slot8();
			if (power && power->slot0(reinterpret_cast<const StopSpecialPowerModuleData *>(m_moduleData)->m_7C))
			{
				m_34 = *m;
				break;
			}
		}
		if (!m_34)
			return false;
	}
	Rva004C683CState *state = m_34->m_iface.slot25();
	if (state)
		return state->slot2();
	return true;
}

// ?doSpecialPower@StopSpecialPower@@UAEXH@Z @0x004C67B9
void StopSpecialPower::doSpecialPower(int)
{
	if (isReady())
		m_34->m_iface.slot8()->slot17();
}
