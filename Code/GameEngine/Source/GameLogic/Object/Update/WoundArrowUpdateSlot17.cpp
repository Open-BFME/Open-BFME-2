// cl: /DNDEBUG /MD
//
// ?rva0045108D@WoundArrowUpdate@@UAEXXZ, retail 0x004C6B7B, 163 bytes.
// Slot 17 of the vftable 0x00C5DF10 whose slot-2 name getter returns
// "WoundArrowUpdate" (installed by the ctor 0x004C68C1). Raises the flag at
// +0x88, runs the base SpecialAbilityUpdate slot 17 (pinned rva0045108D,
// whose address name it carries so cl 7.1 places it in slot 17), then for a
// live target (the ability's ObjectID at +0x40 through the rowed
// GameLogic::findObjectByID) and an owner with an AI (Object+0x258): sets
// model-condition bit 6*32+15, drops weapon set flag 7 and clears bit 5*32+0
// when a current weapon exists and bit 7 of the flag word the matched lea
// getter 0x0028B7AE hands out is set (the AIUpdateInterfacePrivateCommands
// view), and issues the rowed AICommandInterface::rva0026C2D9 at the target
// (1, command source 2). Method identity not established.

class ModuleData;
class Weapon;

enum ObjectID
{
	INVALID_ID = 0
};

enum WeaponSetType
{
	WEAPONSET_NONE = 0
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class Object;

class AICommandInterface
{
public:
	void rva0026C2D9(Object *victim, int count, CommandSourceType cmdSource);
};

class AIUpdateInterfaceHead
{
	char m_unrecovered00[0x20];
};

class AIUpdateInterface : public AIUpdateInterfaceHead, public AICommandInterface
{
};

class Rva0028B7AELeaGetter
{
public:
	void *get() const;
	bool testBit7() const { return ((*(const unsigned int *)get() >> 7) & 1) != 0; }
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
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};

class Object
{
public:
	void rva0028AE6D();
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	void clearWeaponSetFlag(WeaponSetType wst);
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	AIUpdateInterface *getAI() const { return m_ai; }

	unsigned char m_pad000[0x10C];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad15C[0x258 - 0x15C];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_438;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}

static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}

class SpecialAbilityUpdate
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16();
	virtual void rva0045108D();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x40 - 0x0C];
	ObjectID m_targetID; // +0x40
	unsigned char m_pad44[0x88 - 0x44];
};

class WoundArrowUpdate : public SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();
private:
	bool m_88;
};

// ?rva0045108D@WoundArrowUpdate@@UAEXXZ @0x004C6B7B
void WoundArrowUpdate::rva0045108D()
{
	m_88 = true;
	SpecialAbilityUpdate::rva0045108D();

	Object *me = m_object;
	Object *target = TheGameLogic->findObjectByID(m_targetID);
	if (target == 0 || target->isEffectivelyDead())
		return;

	AIUpdateInterface *ai = me->getAI();
	if (ai == 0)
		return;

	setModelConditionBit(me, 6 * 32 + 15);
	if (me->getCurrentWeapon(0) && reinterpret_cast<const Rva0028B7AELeaGetter *>(me)->testBit7())
	{
		me->clearWeaponSetFlag((WeaponSetType)7);
		clearModelConditionBit(me, 5 * 32 + 0);
	}
	ai->rva0026C2D9(target, 1, (CommandSourceType)2);
}
