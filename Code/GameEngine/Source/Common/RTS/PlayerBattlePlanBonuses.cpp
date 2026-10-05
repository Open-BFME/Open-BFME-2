// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /DNDEBUG /MD /EHsc
//
// Zero Hour Player.cpp battle-plan bonus block, retail 0x002AC7E6..0x002ACA86:
//
//   0x002AC7E6  localApplyBattlePlanBonusesToObject      305B
//   0x002AC917  Player::applyBattlePlanBonusesForObject   20B
//   0x002AC92B  Player::removeBattlePlanBonusesForObject 148B
//   0x002AC9BF  Player::applyBattlePlanBonusesForPlayerObjects 199B
//
// Target evidence: the two Player methods call 0x002AC7E6 with the bonuses
// pointer at Player +0xB8 (cdecl, two pops), the remove copy is a 0x4C
// operator new plus the rowed bonuses ctor 0x002AA14D followed by a 0x13
// dword copy and a plain operator delete, and the merge pushes 0x006AC7E6 to
// the rowed Player::iterateObjects 0x002AB08B; 0x002AC917 is called from
// 0x00293568 (Object) and 0x002AD56E, 0x002AC92B from 0x002AD575 (the
// becomingTeamMember pair). Donor: ZH Player.cpp in this order, and Open-BFME-1
// PlayerBattlePlanBonuses_apply.cpp for the BFME callback (int return, the
// unused UnicodeString CRC-log remnant around applyDamageScalar). BFME 2
// layout: KINDOF_PROJECTILE is template +0x108 bit 25 read inline, producer
// ID +0x78, body module +0x254 (applyDamageScalar slot 26), weapon bonus
// conditions dword +0x380 (BATTLEPLAN_BOMBARDMENT/HOLDTHELINE/SEARCHANDDESTROY
// bits 12/13/14), Object::setVisionRange 0x0028BB54. The bonuses record keeps
// the ledger's address name Rva002AA14DBonuses (layout in Rva002AA14DBonuses.cpp).

#include "unicode_string.h"

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
};

enum WeaponBonusConditionType
{
	WEAPONBONUSCONDITION_BATTLEPLAN_BOMBARDMENT = 12,
	WEAPONBONUSCONDITION_BATTLEPLAN_HOLDTHELINE = 13,
	WEAPONBONUSCONDITION_BATTLEPLAN_SEARCHANDDESTROY = 14
};

enum
{
	ALL_PLANS = 1000000
};

#define __max(a, b) (((a) > (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

template <int NUMBITS>
class BitFlags
{
public:
	BitFlags();

	unsigned char m_data[0x1C];
};
typedef BitFlags<69> KindOfMaskType;

class Rva002AA14DBonuses
{
public:
	Rva002AA14DBonuses() throw();

	Real m_armorScalar;					// +0
	Int m_bombardment;					// +4
	Int m_searchAndDestroy;				// +8
	Int m_holdTheLine;					// +0xC
	Real m_sightRangeScalar;			// +0x10
	KindOfMaskType m_validKindOf;		// +0x14
	KindOfMaskType m_invalidKindOf;		// +0x30
};
typedef Rva002AA14DBonuses BattlePlanBonuses;

class ThingTemplate
{
public:
	Bool isKindOfProjectile() const { return (m_kindOf108 >> 25) & 1; }

private:
	char m_pad[0x108];
	UnsignedInt m_kindOf108;
};

class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual void applyDamageScalar(Real scalar);
};

class Thing
{
public:
	Bool isAnyKindOf(const KindOfMaskType &anyKindOf) const;
};

class Object : public Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isKindOfProjectile() const { return getTemplate()->isKindOfProjectile(); }
	ObjectID getProducerID() const { return m_producerID; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Real getVisionRange() const;
	void setVisionRange(Real newVisionRange);
	Real getShroudClearingRange() const;
	void setShroudClearingRange(Real newShroudClearingRange);
	void setWeaponBonusCondition(WeaponBonusConditionType wst) { m_weaponBonusCondition |= (1 << wst); }
	void clearWeaponBonusCondition(WeaponBonusConditionType wst) { m_weaponBonusCondition &= ~(1 << wst); }

private:
	void *m_vtbl;
	const ThingTemplate *m_template;			// +0x04
	char m_pad08[0x78 - 0x08];
	ObjectID m_producerID;						// +0x78
	char m_pad7C[0x254 - 0x7C];
	BodyModuleInterface *m_body;				// +0x254
	char m_pad258[0x380 - 0x258];
	UnsignedInt m_weaponBonusCondition;			// +0x380
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

typedef Int (*ObjectIterateFunc)(Object *obj, void *userData);

class Player
{
public:
	Int iterateObjects(ObjectIterateFunc func, void *userData) const;
	void applyBattlePlanBonusesForObject(Object *obj) const;
	void removeBattlePlanBonusesForObject(Object *obj) const;
	void applyBattlePlanBonusesForPlayerObjects(const BattlePlanBonuses *bonus);

private:
	char m_pad[0xB8];
	BattlePlanBonuses *m_battlePlanBonuses;		// +0xB8
};

Int localApplyBattlePlanBonusesToObject(Object *obj, void *userData)
{
	const BattlePlanBonuses *bonus = (const BattlePlanBonuses *)userData;
	Object *objectToValidate = obj;
	Object *objectToModify = obj;

	Bool isProjectile = obj->isKindOfProjectile();
	if (isProjectile)
	{
		objectToValidate = TheGameLogic->findObjectByID(obj->getProducerID());
	}
	if (objectToValidate && objectToValidate->isAnyKindOf(bonus->m_validKindOf))
	{
		if (!objectToValidate->isAnyKindOf(bonus->m_invalidKindOf))
		{
			if (!isProjectile)
			{
				if (bonus->m_armorScalar != 1.0f)
				{
					BodyModuleInterface *body = objectToModify->getBodyModule();
					UnicodeString unusedDisplayName;
					body->applyDamageScalar(bonus->m_armorScalar);
				}
				if (bonus->m_sightRangeScalar != 1.0f)
				{
					objectToModify->setVisionRange(obj->getVisionRange() * bonus->m_sightRangeScalar);
					objectToModify->setShroudClearingRange(obj->getShroudClearingRange() * bonus->m_sightRangeScalar);
				}
			}

			if (bonus->m_bombardment > 0)
				objectToModify->setWeaponBonusCondition(WEAPONBONUSCONDITION_BATTLEPLAN_BOMBARDMENT);
			else
				objectToModify->clearWeaponBonusCondition(WEAPONBONUSCONDITION_BATTLEPLAN_BOMBARDMENT);
			if (bonus->m_holdTheLine > 0)
				objectToModify->setWeaponBonusCondition(WEAPONBONUSCONDITION_BATTLEPLAN_HOLDTHELINE);
			else
				objectToModify->clearWeaponBonusCondition(WEAPONBONUSCONDITION_BATTLEPLAN_HOLDTHELINE);
			if (bonus->m_searchAndDestroy > 0)
				objectToModify->setWeaponBonusCondition(WEAPONBONUSCONDITION_BATTLEPLAN_SEARCHANDDESTROY);
			else
				objectToModify->clearWeaponBonusCondition(WEAPONBONUSCONDITION_BATTLEPLAN_SEARCHANDDESTROY);
		}
	}
	return 1;
}

void Player::applyBattlePlanBonusesForObject(Object *obj) const
{
	localApplyBattlePlanBonusesToObject(obj, m_battlePlanBonuses);
}
