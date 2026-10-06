// cl: /DNDEBUG /MD
//
// ?findSpecialPowerModuleInterface@Object@@QBEPAVSpecialPowerModuleInterface@@W4SpecialPowerType@@@Z, retail 0x00290E22, 69 bytes.
// Object::findSpecialPowerModuleInterface: scans the null-terminated BehaviorModule
// list at +0x244 via the +0x0C interface sub-object (slot 0x20 getSpecialPower),
// then each SpecialPowerModuleInterface at slot 0x18 getSpecialPowerTemplate,
// chases Overridable::friend_getFinalOverride (rowed 0x00288609) and compares
// SpecialPowerTemplate type at +0x1C to the caller's SpecialPowerType.
// Donor is BFME1 Object::findSpecialPowerModuleInterface
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Object.cpp,
// m_behaviors +0x1F0, getSpecialPower slot 7, getSpecialPowerTemplate slot 6,
// getSpecialPowerType virtual); BFME2 shifts behaviors to +0x244, getSpecialPower
// to slot 8, and inlines the type as final-override +0x1C (name at +0x10 per
// 0x003B11D2, type at +0x1C per 0x0033537F push). Callers pass small int types
// (0x2D at 0x003BCCF6 0x003C6A48, 0x8B at 0x002922B1, 0x1D at 0x0029CA39) and use
// the result as SpecialPowerModuleInterface (slot 1 isReady, slot 10
// doSpecialPower, slot 11 doSpecialPowerAtObject). Returns the first match or null.

enum SpecialPowerType
{
	SPECIAL_INVALID = 0
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;

private:
	void *m_vptr; // +0x00
public:
	Overridable *m_nextOverride; // +0x04
	unsigned char m_isAllocated; // +0x08
};

class SpecialPowerTemplate : public Overridable
{
public:
	char m_pad0C[0x10 - 0x0C];
	void *m_name10; // +0x10 AsciiString, compared at 0x003B11D2
	char m_pad14[0x1C - 0x14];
	SpecialPowerType m_type1C; // +0x1C
};

class SpecialPowerModuleInterface;

class BehaviorModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual SpecialPowerModuleInterface *getSpecialPower() = 0;
};

class BfmeObjectModule
{
public:
	virtual void slot0() = 0;

private:
	unsigned int m_data[2];
};

class BehaviorModule : public BfmeObjectModule, public BehaviorModuleInterface
{
};

class SpecialPowerModuleInterface
{
public:
	virtual void tslot00() = 0;
	virtual void tslot01() = 0;
	virtual void tslot02() = 0;
	virtual void tslot03() = 0;
	virtual void tslot04() = 0;
	virtual void tslot05() = 0;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const = 0;
};

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
};

SpecialPowerModuleInterface *Object::findSpecialPowerModuleInterface(SpecialPowerType type) const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		SpecialPowerModuleInterface *sp = (*m)->getSpecialPower();
		if (!sp)
			continue;
		const SpecialPowerTemplate *tmpl = sp->getSpecialPowerTemplate();
		if (!tmpl)
			continue;
		const Overridable *finalOverride = tmpl->friend_getFinalOverride();
		if (((const SpecialPowerTemplate *)finalOverride)->m_type1C == type)
			return sp;
	}
	return 0;
}
