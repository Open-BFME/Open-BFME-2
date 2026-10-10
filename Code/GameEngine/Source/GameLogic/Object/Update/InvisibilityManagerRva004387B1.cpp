// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /ICode/GameEngine/Source/Common
//
// ?rva004387B1@Rva00439E0C@@QAE_NPAVObject@@I@Z, retail 0x004387B1 (221
// bytes).  Called by the per-entry detection check 0x00439428 with the object
// and the entry's flags; the receiver (TheGameLogic's +0x178 invisibility
// manager) is unused.  WorldBuilder twin 0x012806E0 is unnamed (callgraph
// lead) and agrees on every branch.
//
// Target evidence: an object whose template has kind bit 0x6D (+0x115 bit
// 5) asks its +0x250 contain interface (slot 68, the iterate shape
// Rva004384F2Free.cpp uses) to run the cdecl callback 0x00438144 over its
// contents with a byte that becomes nonzero when any passes 0x0028C1CC;
// other objects answer 0x0028C1CC themselves.  Without that the result is
// false; with flag 0x80 it is true; otherwise the flags 4, 8, 0x10, 0x20 and
// 0x40 select weapon slots 0..4 of the object's +0x330 weapon set (getter
// 0x002C7469, getWeaponInWeaponSlot) and the result is whether a selected
// weapon's +0x2C frame is at least the previous logic frame.  Names beyond
// the rowed callees are neutral.
#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class Weapon
{
public:
	char m_pad00[0x2C];
	unsigned int m_2c;	// +0x2C, a frame stamp
};

class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType wslot) const;
};

typedef void (*Rva004387B1IterateFunc)(Object *obj, void *userData);

class Rva004387B1Contain
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void f26();
	virtual void f27();
	virtual void f28();
	virtual void f29();
	virtual void f30();
	virtual void f31();
	virtual void f32();
	virtual void f33();
	virtual void f34();
	virtual void f35();
	virtual void f36();
	virtual void f37();
	virtual void f38();
	virtual void f39();
	virtual void f40();
	virtual void f41();
	virtual void f42();
	virtual void f43();
	virtual void f44();
	virtual void f45();
	virtual void f46();
	virtual void f47();
	virtual void f48();
	virtual void f49();
	virtual void f50();
	virtual void f51();
	virtual void f52();
	virtual void f53();
	virtual void f54();
	virtual void f55();
	virtual void f56();
	virtual void f57();
	virtual void f58();
	virtual void f59();
	virtual void f60();
	virtual void f61();
	virtual void f62();
	virtual void f63();
	virtual void f64();
	virtual void f65();
	virtual void f66();
	virtual void f67();
	virtual void iterate(Rva004387B1IterateFunc func, void *userData, bool reverse);	// +0x110
};

struct Rva004387B1Template
{
	char m_pad000[0x108];
	unsigned int m_kindOf[8];	// +0x108
	__forceinline unsigned int isKindOf(int kind) const { return m_kindOf[kind >> 5] & (1u << (kind & 31)); }
};

class Object
{
public:
	bool rva0028C1CC() const;
	const Rva004387B1Template *getTemplate() const { return m_template; }
private:
	char m_pad000[0x04];
	const Rva004387B1Template *m_template;	// +0x04
	char m_pad008[0x250 - 0x08];
public:
	Rva004387B1Contain *m_contain;	// +0x250
private:
	char m_pad254[0x330 - 0x254];
public:
	WeaponSet m_weaponSet;	// +0x330
};

void Rva00438144Update(const Object *obj, unsigned char *flag);

struct Rva004387B1SlotMask
{
	unsigned int m_mask;
	WeaponSlotType m_slot;
};

class Rva00439E0C
{
public:
	bool rva004387B1(Object *obj, unsigned int flags);
};

bool Rva00439E0C::rva004387B1(Object *obj, unsigned int flags)
{
	if (obj->getTemplate()->isKindOf(0x6D))
	{
		unsigned char any = 0;
		obj->m_contain->iterate((Rva004387B1IterateFunc)&Rva00438144Update, &any, true);
		if (!any)
			return false;
	}
	else if (!obj->rva0028C1CC())
		return false;
	if (flags & 0x80)
		return true;
	unsigned int previous = TheGameLogic->getFrame() - 1;
	Rva004387B1SlotMask slots[6] =
	{
		{ 4, (WeaponSlotType)0 },
		{ 8, (WeaponSlotType)1 },
		{ 0x10, (WeaponSlotType)2 },
		{ 0x20, (WeaponSlotType)3 },
		{ 0x40, (WeaponSlotType)4 },
		{ 0, (WeaponSlotType)5 },
	};
	for (int i = 0; i < 6; ++i)
	{
		if (flags & slots[i].m_mask)
		{
			Weapon *weapon = obj->m_weaponSet.getWeaponInWeaponSlot(slots[i].m_slot);
			if (weapon && weapon->m_2c >= previous)
				return true;
		}
	}
	return false;
}
