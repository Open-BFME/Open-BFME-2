// ?adjustVictim@Object@@QAEPAV1@PAV1@_NH@Z
// partial score=0.94 date=2026-10-05
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// Object::adjustVictim, retail 0x0028CCB9 (253 bytes). WorldBuilder confirms
// the parent-chain walk through rva0028C197, then uses the module at +0x258
// and selector slots 30/96/18. The retail build's corresponding module is at
// +0x250 and its selector methods are at slots 31/96/18. The parent pointer
// is at +0x27C in WB and +0x274 in retail. Object::onContainedBy independently
// identifies the retail +0x274 field as m_containedBy.

typedef float Real;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class Weapon;

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

class ThingTemplate
{
public:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[28];
};

class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};

class Weapon
{
public:
	unsigned char m_pad000[4];
	Rva002C9400ByteField *m_field04;
	Real getAttackRange(const Object *source) const;
};

class AdjustVictimSelector;

class AdjustVictimProvider
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual AdjustVictimSelector *getSelector() = 0;
};

static __forceinline AdjustVictimSelector *__fastcall getAdjustVictimSelector(
	AdjustVictimProvider *provider)
{
	return provider->getSelector();
}

template <int N>
class AdjustVictimSelectorSlots : public AdjustVictimSelectorSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <>
class AdjustVictimSelectorSlots<0>
{
};

class AdjustVictimSelectorPrefix : public AdjustVictimSelectorSlots<18>
{
public:
	virtual Object *select(int reserved, const Coord3D *position, Real range,
		Object *source, int index) = 0;
};

template <int N, class Base>
class AdjustVictimSelectorTail : public AdjustVictimSelectorTail<N - 1, Base>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <class Base>
class AdjustVictimSelectorTail<0, Base> : public Base
{
};

class AdjustVictimSelector : public AdjustVictimSelectorTail<95, AdjustVictimSelectorPrefix>
{
public:
	virtual unsigned int getCount(int reserved) = 0;
};

class Object
{
public:
	void *rva0028C197() const;
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Object *adjustVictim(Object *source, bool useWeaponRange, int index);

private:
	unsigned char m_pad000[4];
	ThingTemplate *m_template004;
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position038;
	unsigned char m_pad044[0x248 - 0x44];
	void *m_firingTracker248;
	unsigned char m_pad24C[0x250 - 0x24C];
	AdjustVictimProvider *m_provider250;
	unsigned char m_pad254[0x274 - 0x254];
	Object *m_containedBy274;
};

Object *Object::adjustVictim(Object *source, bool useWeaponRange, int index)
{
	Object *target = this;
	if (source == 0)
		return 0;

	Object * volatile *parent = &target->m_containedBy274;
	while (*parent != 0)
	{
		if ((*parent)->rva0028C197() == 0)
			break;
		target = *parent;
		parent = &target->m_containedBy274;
	}

	AdjustVictimProvider *provider = target->m_provider250;
	if (provider != 0)
	{
		AdjustVictimSelector *selector = getAdjustVictimSelector(provider);
		if (selector != 0)
		{
			Real range = 0.0f;
			if (!useWeaponRange)
				range = 99999.0f;
			else if ((source->m_template004->m_kindOf[13] & 0x20) == 0)
			{
				const Weapon *weapon = source->getCurrentWeapon(0);
				if (weapon != 0 && weapon->m_field04->get() == 0)
					range = weapon->getAttackRange(source);
			}

			Object *victim = 0;
			if (selector->getCount(0) > 0)
			{
				victim = selector->select(0, &source->m_position038, range, source, index);
				if (victim == 0)
					victim = selector->select(0, 0, 0.0f, 0, index);
			}
			return victim;
		}
	}

	return this;
}
