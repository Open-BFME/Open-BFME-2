// cl: /DNDEBUG /MD
//
// ?triggerAbilityEffect@FlingPassengerSpecialAbilityUpdate@@UAEXXZ, retail 0x00494FCC, 162 bytes.
// Slot 17 of the vftable whose slot-2 name getter returns
// "FlingPassengerSpecialAbilityUpdate". Runs the base SpecialAbilityUpdate
// slot 17 (pinned triggerAbilityEffect, whose address name it carries so cl 7.1
// places it in slot 17), then, when the owner's contain module (Object+0x250)
// reports a passenger (its slot 69), takes the passenger its slot 79 hands
// back: fires the module-data weapon (+0xD4) from the owner at it through
// the rowed WeaponStore::rva002CE964, and then either sets model-condition
// bits 1*32+30 and 3*32+26 on a dead passenger (Object+0x438 bit 0) or wakes
// a live one's physics (Object+0x25C, rowed PhysicsBehavior::rva003906BF).
// Method identity not established.

class Object;
class WeaponTemplate;
class ModuleData;

class WeaponStore
{
public:
	void rva002CE964(const WeaponTemplate *wt, const Object *source, const Object *victim);
};

extern WeaponStore *TheWeaponStore;

class PhysicsBehavior
{
public:
	void rva003906BF();
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

class ContainModuleInterface
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	SLOT08(s18,s19,s1A,s1B,s1C,s1D,s1E,s1F)
	SLOT08(s20,s21,s22,s23,s24,s25,s26,s27)
	SLOT08(s28,s29,s2A,s2B,s2C,s2D,s2E,s2F)
	SLOT08(s30,s31,s32,s33,s34,s35,s36,s37)
	SLOT08(s38,s39,s3A,s3B,s3C,s3D,s3E,s3F)
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44();
	virtual unsigned int rva69(int which);
	virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
	virtual void s4A(); virtual void s4B(); virtual void s4C(); virtual void s4D();
	virtual void s4E();
	virtual Object *rva79(int which);
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[20];
};

class Object
{
public:
	void rva0028AE6D();
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }

	unsigned char m_pad000[0x10C];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad15C[0x250 - 0x15C];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x25C - 0x254];
	PhysicsBehavior *m_physics; // +0x25C
	unsigned char m_pad260[0x438 - 0x260];
	unsigned char m_438;
};

static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}

struct FlingPassengerSpecialAbilityUpdateModuleData
{
	unsigned char m_pad00[0xD4];
	const WeaponTemplate *m_D4;
};

class SpecialAbilityUpdate
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16();
	virtual void triggerAbilityEffect();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class FlingPassengerSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
};

// ?triggerAbilityEffect@FlingPassengerSpecialAbilityUpdate@@UAEXXZ @0x00494FCC
void FlingPassengerSpecialAbilityUpdate::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();

	Object *me = m_object;
	const FlingPassengerSpecialAbilityUpdateModuleData *data =
		(const FlingPassengerSpecialAbilityUpdateModuleData *)m_moduleData;
	ContainModuleInterface *contain = me->m_contain;
	if (contain->rva69(0) > 0)
	{
		Object *rider = contain->rva79(0);
		const WeaponTemplate *weapon = data->m_D4;
		if (weapon)
			TheWeaponStore->rva002CE964(weapon, me, rider);

		if (rider->isEffectivelyDead())
		{
			setModelConditionBit(rider, 1 * 32 + 30);
			setModelConditionBit(rider, 3 * 32 + 26);
		}
		else if (rider->m_physics)
		{
			rider->m_physics->rva003906BF();
		}
	}
}
