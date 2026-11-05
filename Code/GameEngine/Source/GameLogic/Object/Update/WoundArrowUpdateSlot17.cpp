// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?triggerAbilityEffect@WoundArrowUpdate@@UAEXXZ, retail 0x004C6B7B, 163 bytes.
// Slot 17 of the vftable 0x00C5DF10 whose slot-2 name getter returns
// "WoundArrowUpdate" (installed by the ctor 0x004C68C1). Raises the flag at
// +0x88, runs the base SpecialAbilityUpdate slot 17 (pinned triggerAbilityEffect,
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

#include "../../../Common/GameLogicObjectLookupView.h"

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

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

class AIUpdateInterfaceHead
{
	char m_unrecovered00[0x20];
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

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class WoundArrowUpdate : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
private:
	bool m_88;
};

// ?triggerAbilityEffect@WoundArrowUpdate@@UAEXXZ @0x004C6B7B
void WoundArrowUpdate::triggerAbilityEffect()
{
	m_88 = true;
	SpecialAbilityUpdate::triggerAbilityEffect();

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
