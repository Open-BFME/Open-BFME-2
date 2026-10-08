// cl: /O1 /Oy /G7 /arch:SSE /DNDEBUG /MD
//
// WeaponSet::setWeaponLock, retail 0x002C8AAE (237 bytes).
// Identity: Zero Hour WeaponSet.cpp setWeaponLock (false for NOT_LOCKED or an
// empty slot; LOCKED_PERMANENTLY always takes the slot, LOCKED_TEMPORARILY only
// when not permanently locked; true otherwise), called with m_weaponSet as this
// by the matched Object::setWeaponLock 0x00290B24. Layout from the body:
// m_weapons at +0x08, current weapon +0x20, lock status +0x24, owner ObjectID
// +0x3C.
// BFME2 additions: look the owner up first; clear the five weapon-slot model
// conditions 0x90..0x94 on it (mask built by the verified address-derived row
// 0x000B6253 in a 0x4C-byte local, i.e. a 19-word model-condition mask, and
// applied by the verified address-derived row 0x001E42F2, whose this is the Object;
// both rows keep their placeholder class names, hence the casts) and set the
// one of the current slot (switch with literal cases; cl merges the five
// masked-word test/or tails). The false path is laid out last, which needs the
// early-out tests folded into one guarding if.

class WeaponTemplateSet;
class ThingTemplate;
enum ObjectID
{
	INVALID_ID = 0
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1,
	LOCKED_PERMANENTLY = 2
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
	unsigned int word(int i) const
	{
		return m_words[i];
	}
private:
	unsigned int m_words[19];
};
#include "../../../../Libraries/Include/Lib/Coord3D.h"
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};
enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0,
	ATTACK_TUNNEL_NETWORK_GUARD = 4
};
enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 2
};
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
enum KindOfType
{
	KINDOF_NONE = 0
};
class Team
{
public:
	Relationship getRelationship(const Team *that) const;
};
class Player
{
public:
	Relationship getRelationship(const Team *team) const;
	unsigned char m_pad000[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};
class PlayerList
{
public:
	Player *getNthPlayer(int i);
};
extern PlayerList *ThePlayerList;
class AIInner
{
public:
	unsigned char m_pad00[0xBC];
	bool m_flagBC;
};
class AI
{
public:
	unsigned char m_pad00[0x18];
	AIInner *m_inner; // +0x18
};
extern AI *TheAI;
// Disguise state found by Object 0x0028F4BC: player index +0x38, active +0x3C.
class Rva00373EC6
{
public:
	unsigned char m_pad00[0x38];
	int m_disguisedPlayerIndex;
	int m_disguised;
	bool isDisguised() const { return m_disguised != 0; }
	int getDisguisedPlayerIndex() const { return m_disguisedPlayerIndex; }
};
class ContainModuleInterface;
class Weapon;
class AIUpdateInterface;
class SpawnBehaviorInterface;
class Object
{
public:
	void rva0028AE6D();
	bool testStatus(ObjectStatusTypes) const;
	Object *rva002931F5(bool);
	float GetRelativeAngle(const Coord3D *) const;
	bool isAbleToAttack() const;
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
	CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType, const Object *, const Coord3D *, CommandSourceType) const;
	Player *getControllingPlayer() const;
	Rva00373EC6 *rva0028F4BC();
	bool rva002943B2(const Player *viewer);
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Relationship getRelationship(const Object *that) const;
	bool isKindOf(KindOfType kind) const;
	unsigned char m_pad000[4];
 ThingTemplate *m_template;
 unsigned char m_pad008[0x38-8];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x74-0x44];
 ObjectID m_id;
	unsigned char m_pad078[0x94-0x78];
	unsigned int m_status; // +0x94
	unsigned char m_pad098[0x10C-0x98];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x250-0x158];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[4];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274-0x25C];
	Object *m_containedBy; // +0x274
	unsigned char m_pad278[0x304-0x278];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x437-0x308];
	unsigned char m_scriptStatus; // +0x437
	unsigned char m_privateStatus; // +0x438
	unsigned char m_attackImmunity; // +0x439
};
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
// Placeholder rows: 0x000B6253 fills a 0x4C-byte (19-word) model-condition mask
// with up to five bits and returns it; 0x001E42F2 clears such a mask on an
// Object (its this is the Object).
class Rva000B6253
{
public:
	Rva000B6253 *rva000B6253(int count, unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
private:
	unsigned int m_words[19];
};
class Rva001E42F2
{
public:
	void rva001E42F2(const int *mask);
};
class Weapon;
class Rva002CA9CA
{
public:
	bool rva002CA9CA(int id, const void *arg);
};
class WeaponSet
{
public:
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
 void updateWeaponSet(const Object *);
 void releaseWeaponLock(WeaponLockType);
	CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType, const Object *, const Object *, const Coord3D *, CommandSourceType) const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType, const Object *, const Object *, CommandSourceType) const;
private:
	bool isAnyWithinTargetPitch(const Object *, const Object *) const;
	unsigned char m_pad00[4];
 const WeaponTemplateSet *m_set; // +0x04
 Weapon *m_weapons[6]; // +0x08 through +0x1C
	WeaponSlotType m_curWeapon; // +0x20
	WeaponLockType m_curWeaponLockedStatus; // +0x24
	unsigned m_filled,m_anti,m_damage; // +28/+2C/+30
 bool m_pitch,m_hasDamage; // +34/+35
 unsigned char m_pad36[6];
	ObjectID m_ownerID; // +0x3C
};
bool WeaponSet::setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType)
{
	Object *owner = TheGameLogic->findObjectByID(m_ownerID);
	if (lockType != NOT_LOCKED && m_weapons[weaponSlot] != 0)
	{
		if (lockType == LOCKED_PERMANENTLY)
		{
			m_curWeaponLockedStatus = lockType;
			m_curWeapon = weaponSlot;
		}
		else if (lockType == LOCKED_TEMPORARILY && m_curWeaponLockedStatus != LOCKED_PERMANENTLY)
		{
			m_curWeaponLockedStatus = lockType;
			m_curWeapon = weaponSlot;
		}
		if (owner)
		{
			Rva000B6253 mask;
			((Rva001E42F2 *)owner)->rva001E42F2((const int *)mask.rva000B6253(0, 0x90, 0x91, 0x92, 0x93, 0x94));
		}
		switch (m_curWeapon)
		{
		case 0:
			if (owner)
				setModelConditionBit(owner, 0x90);
			break;
		case 1:
			if (owner)
				setModelConditionBit(owner, 0x91);
			break;
		case 2:
			if (owner)
				setModelConditionBit(owner, 0x92);
			break;
		case 3:
			if (owner)
				setModelConditionBit(owner, 0x93);
			break;
		case 4:
			if (owner)
				setModelConditionBit(owner, 0x94);
			break;
		}
		return true;
	}
	return false;
}

// Native 0x002C8C97..0x002C8E39: 418B RET4. WB WeaponSet.cpp553/576
// proves the operation; native offsets below are supported by ctor60 and
// this body. Six 20B saved reload states preserve shared reload across sets;
// the supplied reference has the reset/allocation loop but lacks this state
// transfer and the native owner-ID/model-condition additions. Donor lead:
// BFME1 ba7ddda inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/
// GameEngine/Source/GameLogic/Object/WeaponSet.cpp; WB independently proves
// the added save/restore branches and native helpers establish their ABI.
// /O1 /Oy reproduces the biased native frame and preserves setWeaponLock237.
// Only the existing reference ABI is used; the flag layout is opaque here.
template<int N> class BitFlags;
template<> class BitFlags<218> { public: bool any() const; private: unsigned m_bits[7]; };
class WeaponTemplateSet;
class ThingTemplate { public: const WeaponTemplateSet *findWeaponTemplateSet(const BitFlags<117> &) const;
 char pad0[0x108]; unsigned m_kindOf[5]; // +0x108
};
class Rva0028B7AELeaGetter { public: void *get() const; };
class Rva002C9424 { public: Rva002C9424 *rva002C9424(); };
struct Rva002C943BSrc;
class Rva002C943B { public: void rva002C943B(const Rva002C943BSrc *); };
struct SavedWeaponState { int fields[5]; SavedWeaponState() { ((Rva002C9424 *)this)->rva002C9424(); } };
class WeaponTemplate { public:
 char pad0[0xc]; int m_key; char pad10[0x2c-0x10]; float m_minTargetAngle; char pad30[0x58-0x30]; int m_damageType;
 char pad5C[0x10c-0x5c]; unsigned m_anti; char pad110[4]; bool m_damage; char pad115[0x170-0x115]; bool m_noVictimAttack;
};
class Weapon { public:
 virtual void *nativeSlot0(unsigned)=0;
 void rva002CE226(const Object *,const SavedWeaponState *);
 bool isWithinAttackRange(const Object *,const Object *,float,int) const;
 char isWithinAttackRange(Object *,void *,float,int) const;
 bool rva002CCED3(const Object *,const Object *);
 WeaponTemplate *m_template; unsigned m_ownerID;
 char padC[0x4c-0xc]; bool m_pitch;
};
class WeaponStore { friend class WeaponSet; private:
 const WeaponTemplate *Rva002CADBE(int) const; public:
 Weapon *allocateNewWeapon(const WeaponTemplate *,WeaponSlotType) const;
}; extern WeaponStore *TheWeaponStore;
class WeaponTemplateSet { public:
 char pad0[0x14]; const WeaponTemplate *m_weapons[6]; char pad2C[0xec-0x2c]; BitFlags<218> m_victimKindOf[6]; char pad194[0x35c-0x194]; bool m_sharedReload,m_sharedLock;
};
void WeaponSet::updateWeaponSet(const Object *obj)
{
 ThingTemplate *templ=obj->m_template;
 const WeaponTemplateSet *set=templ->findWeaponTemplateSet(*(const BitFlags<117> *)((const Rva0028B7AELeaGetter *)obj)->get());
 if(set && set!=m_set) {
   SavedWeaponState state[6];
   SavedWeaponState *saved=0;
   if(m_set && m_set->m_sharedReload && set->m_sharedReload) {
     saved=state;
     for(int i=5;i>=0;--i) if(m_weapons[i]) ((Rva002C943B *)&state[i])->rva002C943B((const Rva002C943BSrc *)m_weapons[i]);
   }
   if(!set->m_sharedLock) { releaseWeaponLock(LOCKED_PERMANENTLY); m_curWeapon=PRIMARY_WEAPON; }
   m_filled=0; m_anti=0; m_damage=0; m_pitch=false; m_hasDamage=false;
   for(int i=5;i>=0;--i) {
     if(m_weapons[i]) { ::operator delete(m_weapons[i]->nativeSlot0(0)); m_weapons[i]=0; }
     if(set->m_weapons[i]) {
       const WeaponTemplate *weaponTemplate=TheWeaponStore->Rva002CADBE(set->m_weapons[i]->m_key);
       if(weaponTemplate) {
         m_weapons[i]=TheWeaponStore->allocateNewWeapon(weaponTemplate,(WeaponSlotType)i);
         m_weapons[i]->m_ownerID=obj->m_id;
         m_weapons[i]->rva002CE226(obj,saved);
         m_filled|=1u<<i; m_anti|=m_weapons[i]->m_template->m_anti;
         m_damage|=1u<<m_weapons[i]->m_template->m_damageType;
         if(m_weapons[i]->m_pitch) m_pitch=true;
         if(m_weapons[i]->m_template->m_damage) m_hasDamage=true;
       }
     }
   }
   m_set=set; m_ownerID=obj->m_id;
 }
}

// Native 0x002C8B9B..0x002C8C06: 107B RET4. Zero Hour WeaponSet.cpp
// releaseWeaponLock (PERMANENTLY always clears, TEMPORARILY only a temporary
// lock); called by the matched Object::releaseWeaponLock 0x0028D8B6 and by
// updateWeaponSet above. BFME2 addition, as in setWeaponLock: look the owner
// up first and clear its five weapon-slot model conditions 0x90..0x94 when
// the lock is released.
static __forceinline void clearSlotConditions(Object *owner)
{
	if (owner)
	{
		Rva000B6253 mask;
		((Rva001E42F2 *)owner)->rva001E42F2((const int *)mask.rva000B6253(0, 0x90, 0x91, 0x92, 0x93, 0x94));
	}
}
void WeaponSet::releaseWeaponLock(WeaponLockType lockType)
{
	Object *owner = TheGameLogic->findObjectByID(m_ownerID);
	if (m_curWeaponLockedStatus != NOT_LOCKED)
	{
		if (lockType == LOCKED_PERMANENTLY)
		{
			m_curWeaponLockedStatus = NOT_LOCKED;
			clearSlotConditions(owner);
		}
		else if (lockType == LOCKED_TEMPORARILY)
		{
			if (m_curWeaponLockedStatus == LOCKED_TEMPORARILY)
			{
				m_curWeaponLockedStatus = NOT_LOCKED;
				clearSlotConditions(owner);
			}
		}
	}
}

// Native 0x002C787F..0x002C7907: 136B. BFME1 WeaponSet.cpp file-static
// getVictimAntiMask, kind-of bits read straight off the template's words at
// +0x108 (no override walk in BFME2); the victim is passed in EDX because
// both callers (getAbleToUseWeaponAgainstTarget, chooseBestWeaponForTarget)
// live in this unit. Airborne-target status is bit 6 of Object +0x94.
static int getVictimAntiMask(const Object *victim)
{
	const ThingTemplate *tmpl = victim->m_template;
	if (tmpl->m_kindOf[1] & 0x800000)
		return 0x12;
	if (tmpl->m_kindOf[1] & 0x100000)
		return 8;
	if (tmpl->m_kindOf[2] & 0x800)
		return 0x40;
	if (tmpl->m_kindOf[0] & 0x2000000)
		return 4;
	if ((bool)((victim->m_status >> 6) & 1))
	{
		if (tmpl->m_kindOf[0] & 0x200)
			return 1;
		if (tmpl->m_kindOf[0] & 0x100)
			return 0x20;
		if (tmpl->m_kindOf[0] & 0x400)
			return 0x200;
		if (tmpl->m_kindOf[2] & 0x4000)
			return 0x80;
		return 0;
	}
	// Ground victim: 2, plus 0x100 for KindOf bit 7 (retail selects 0x102/2).
	return (tmpl->m_kindOf[0] & 0x80) ? 0x102 : (tmpl->m_kindOf[0] & 0x80) + 2;
}

class ContainedItemsListView;
struct ContainedItemsPair
{
	void *m_unknown00;
	const ContainedItemsListView *m_items; // +4
};
struct ContainedItemsNode
{
	ContainedItemsNode *m_next;
	ContainedItemsNode *m_prev;
	Object *m_data;
};
class ContainedItemsListView
{
public:
	ContainedItemsNode *m_node;
};
#define CONTAIN_GAP(n) virtual void gap##n();
class ContainModuleInterface
{
public:
	CONTAIN_GAP(0) CONTAIN_GAP(1) CONTAIN_GAP(2) CONTAIN_GAP(3)
	virtual bool isGarrisonable() const; // slot 4
	CONTAIN_GAP(5) CONTAIN_GAP(6) CONTAIN_GAP(7) CONTAIN_GAP(8) CONTAIN_GAP(9)
	CONTAIN_GAP(10) CONTAIN_GAP(11) CONTAIN_GAP(12) CONTAIN_GAP(13) CONTAIN_GAP(14)
	CONTAIN_GAP(15) CONTAIN_GAP(16) CONTAIN_GAP(17) CONTAIN_GAP(18)
	virtual const Player *getApparentControllingPlayer(const Player *observingPlayer) const; // slot 19
	CONTAIN_GAP(20) CONTAIN_GAP(21) CONTAIN_GAP(22) CONTAIN_GAP(23) CONTAIN_GAP(24)
	CONTAIN_GAP(25) CONTAIN_GAP(26) CONTAIN_GAP(27) CONTAIN_GAP(28) CONTAIN_GAP(29)
	CONTAIN_GAP(30) CONTAIN_GAP(31) CONTAIN_GAP(32) CONTAIN_GAP(33) CONTAIN_GAP(34)
	CONTAIN_GAP(35) CONTAIN_GAP(36) CONTAIN_GAP(37) CONTAIN_GAP(38) CONTAIN_GAP(39)
	CONTAIN_GAP(40) CONTAIN_GAP(41) CONTAIN_GAP(42) CONTAIN_GAP(43) CONTAIN_GAP(44)
	virtual bool isPassengerAllowedToFire() const; // slot 45
	CONTAIN_GAP(46) CONTAIN_GAP(47) CONTAIN_GAP(48) CONTAIN_GAP(49)
	CONTAIN_GAP(50) CONTAIN_GAP(51) CONTAIN_GAP(52) CONTAIN_GAP(53) CONTAIN_GAP(54)
	virtual bool getFiringOwner(const Object *source, Object **owner); // slot 55
	CONTAIN_GAP(56) CONTAIN_GAP(57) CONTAIN_GAP(58) CONTAIN_GAP(59)
	CONTAIN_GAP(60) CONTAIN_GAP(61) CONTAIN_GAP(62) CONTAIN_GAP(63) CONTAIN_GAP(64)
	CONTAIN_GAP(65) CONTAIN_GAP(66) CONTAIN_GAP(67) CONTAIN_GAP(68) CONTAIN_GAP(69)
	virtual void getContainedItemsList(ContainedItemsPair &pair); // slot 70
	CONTAIN_GAP(71) CONTAIN_GAP(72) CONTAIN_GAP(73) CONTAIN_GAP(74) CONTAIN_GAP(75)
	virtual bool calcBestGarrisonPosition(Coord3D *goalPos, const Coord3D *targetPos); // slot 76
};
class Rva001E46E1
{
public:
	float rva001E4845(Object *);
};
class AIUpdateInterface
{
public:
	char m_pad000[0x1F0];
	Rva001E46E1 *m_1F0;
};
class SpawnBehaviorInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual CanAttackResult getCanAnySlavesUseWeaponAgainstTarget(AbleToAttackType attackType,
		const Object *victim, const Coord3D *pos, CommandSourceType commandSource);
};
class Rva002C9B80Owner
{
public:
	bool rva002CB2D1(Object *source, const Coord3D *goalPos, const void *victim, const Coord3D *targetPos);
};
class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &) const;
};
#include <math.h>

// Native 0x002C7907..0x002C7D03: 1020B RET 0x14. BFME1 WeaponSet.cpp
// getAbleToUseWeaponAgainstTarget transfer for six slots. BFME2 changes:
// a weapon template flag (+0x170) disables a slot against an object victim;
// immobile shooters without an AI target (+0x1F0) reject targets outside the
// weapon's +0x2C angle; passengers are queried with the Object entry point.
CanAttackResult WeaponSet::getAbleToUseWeaponAgainstTarget(AbleToAttackType attackType,
	const Object *source, const Object *victim, const Coord3D *pos,
	CommandSourceType commandSource) const
{
	int targetAntiMask;
	if (victim)
	{
		targetAntiMask = getVictimAntiMask(victim);
		pos = &victim->m_position;
	}
	else
	{
		targetAntiMask = 2;
	}

	const Object *containedBy = source->m_containedBy;
	ContainModuleInterface *contain = containedBy ? containedBy->m_contain : 0;

	if (source->testStatus((ObjectStatusTypes)0x25) && !((int)attackType & 8))
	{
		if (!containedBy)
			return ATTACKRESULT_INVALID_SHOT;
		if (contain)
		{
			Object *owner = 0;
			if (contain->getFiringOwner(source, &owner))
			{
				if (!owner)
					return ATTACKRESULT_NOT_POSSIBLE;
				if (owner != victim
					&& owner->rva002931F5(false) != ((Object *)victim)->rva002931F5(false))
					return ATTACKRESULT_NOT_POSSIBLE;
			}
		}
	}

	char withinAttackRange = false;
	bool hasAWeaponInRange = false;
	bool hasAWeapon = false;
	for (int slot = 0; slot < 6; ++slot)
	{
		Weapon *weapon = m_weapons[slot];
		if (weapon)
		{
			hasAWeapon = true;
			if ((m_anti & targetAntiMask) == 0)
				continue;
			if (victim && weapon->m_template->m_noVictimAttack)
				continue;

			if (source->testStatus((ObjectStatusTypes)0x25))
				withinAttackRange = true;
			else if (contain && contain->isGarrisonable())
			{
				Coord3D targetPos;
				targetPos.x = pos->x;
				targetPos.y = pos->y;
				targetPos.z = pos->z;
				Coord3D goalPos;
				if (!(source->m_template->m_kindOf[3] & 0x2000)
					&& contain->calcBestGarrisonPosition(&goalPos, &targetPos))
					withinAttackRange = ((Rva002C9B80Owner *)weapon)->rva002CB2D1((Object *)source, &goalPos, victim, &targetPos);
				else if (victim)
					withinAttackRange = weapon->isWithinAttackRange(source, victim, 0.0f, 1);
			}
			else
				withinAttackRange = victim
					? weapon->isWithinAttackRange(source, victim, 0.0f, 1)
					: weapon->isWithinAttackRange((Object *)source, (void *)pos, 0.0f, 1);

			if (withinAttackRange)
			{
				if (source->m_template->m_kindOf[0] & 4)
				{
					AIUpdateInterface *ai = source->m_ai;
					if (!ai || !ai->m_1F0)
					{
						float angle = weapon->m_template->m_minTargetAngle;
						if (angle > 0.0f && pos)
						{
							if (fabs(source->GetRelativeAngle(pos)) > angle)
								withinAttackRange = false;
						}
					}
				}
				if (withinAttackRange)
				{
					hasAWeaponInRange = true;
					break;
				}
			}
		}
	}

	if ((source->m_template->m_kindOf[0] & 4)
		|| (source->m_template->m_kindOf[2] & 0x100000)
		|| (containedBy && !(containedBy->m_template->m_kindOf[3] & 0x2000))
		|| (source->m_ai && source->m_ai->m_1F0
			&& source->m_ai->m_1F0->rva001E4845((Object *)source) <= 0.0f))
	{
		if (hasAWeapon && !hasAWeaponInRange && attackType != ATTACK_TUNNEL_NETWORK_GUARD)
			return ATTACKRESULT_INVALID_SHOT;
	}

	CanAttackResult okResult = withinAttackRange ? ATTACKRESULT_POSSIBLE : ATTACKRESULT_POSSIBLE_AFTER_MOVING;

	if ((m_anti & targetAntiMask) == 0)
		return ATTACKRESULT_INVALID_SHOT;

	if (!victim)
		return okResult;

	if (!isAnyWithinTargetPitch(source, victim))
		return ATTACKRESULT_INVALID_SHOT;

	int first, last;
	if (m_curWeaponLockedStatus)
	{
		first = m_curWeapon;
		last = m_curWeapon;
	}
	else
	{
		first = 5;
		last = PRIMARY_WEAPON;
	}

	for (int i = first; i >= last; --i)
	{
		Weapon *weapon = m_weapons[i];
		if (weapon && weapon->rva002CCED3(source, victim))
		{
			const BitFlags<218> &mask = m_set->m_victimKindOf[i];
			if (!mask.any() || ((const Thing *)victim)->isAnyKindOf(*(const BitFlags<69> *)&mask))
				return okResult;
		}
	}

	ContainModuleInterface *passengerContain = source->m_contain;
	if (passengerContain && passengerContain->isPassengerAllowedToFire())
	{
		ContainedItemsPair items;
		passengerContain->getContainedItemsList(items);
		for (ContainedItemsNode *it = items.m_items->m_node->m_next; it != items.m_items->m_node; it = it->m_next)
		{
			Object *passenger = it->m_data;
			if (passenger->isAbleToAttack())
			{
				CanAttackResult result = passenger->getAbleToUseWeaponAgainstTarget(attackType, victim, pos, commandSource);
				if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
					return result;
			}
		}
	}

	SpawnBehaviorInterface *spawnInterface = source->getSpawnBehaviorInterface();
	if (spawnInterface
		&& spawnInterface->getCanAnySlavesUseWeaponAgainstTarget(attackType, victim, pos, commandSource) == ATTACKRESULT_POSSIBLE)
	{
		if ((source->m_template->m_kindOf[0] & 4)
			&& (source->m_template->m_kindOf[2] & 0x100000)
			&& okResult == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
			okResult = ATTACKRESULT_POSSIBLE;
		return okResult;
	}

	return ATTACKRESULT_INVALID_SHOT;
}

// Native 0x002C83FC..0x002C8754: 856B RET 0x10. BFME1 WeaponSet.cpp
// getAbleToAttackSpecificObject; called by Object::getAbleToAttackSpecificObject
// 0x0028D051, ends by forwarding to getAbleToUseWeaponAgainstTarget with the
// victim's position. BFME2 additions: a disguise holder (0x0028F4BC) lets a
// forced attack or a stealth check through when the victim is disguised as an
// enemy; a source-side (+0x10C bit 23) rejection forces ENEMIES before the
// relationship query; a victim flag (+0x113 bit 6) treats it as an enemy while
// TheAI's inner +0xBC flag is set.
CanAttackResult WeaponSet::getAbleToAttackSpecificObject(AbleToAttackType attackType,
	const Object *source, const Object *victim, CommandSourceType commandSource) const
{
	if (!source || !victim ||
		(source->m_privateStatus & 1) || (victim->m_privateStatus & 1) ||
		(source->m_status & 1) || (victim->m_status & 1) ||
		victim == source)
		return ATTACKRESULT_NOT_POSSIBLE;

	if (victim->testStatus((ObjectStatusTypes)0x33))
		return ATTACKRESULT_NOT_POSSIBLE;

	bool sameOwnerForceAttack = source->getControllingPlayer() == victim->getControllingPlayer() && ((int)attackType & 1);

	int ignoring = 0;
	if (source->testStatus((ObjectStatusTypes)0x25))
		ignoring = 1;
	if (victim->m_attackImmunity & ~ignoring)
		return ATTACKRESULT_NOT_POSSIBLE;

	const ThingTemplate *victimTemplate = victim->m_template;
	if (victimTemplate->m_kindOf[1] & 0x400000)
		return ATTACKRESULT_NOT_POSSIBLE;

	if (victim->testStatus((ObjectStatusTypes)0x3C))
		return ATTACKRESULT_NOT_POSSIBLE;

	if (victim->testStatus((ObjectStatusTypes)0x1A) && commandSource == CMD_FROM_AI)
		return ATTACKRESULT_NOT_POSSIBLE;

	bool allowStealthToPreventAttacks = true;
	if (source->testStatus((ObjectStatusTypes)0x1B) || sameOwnerForceAttack)
		allowStealthToPreventAttacks = false;
	bool forced = ((int)attackType & 1) != 0;
	if (forced && (victimTemplate->m_kindOf[2] & 0x1000000))
	{
		Rva00373EC6 *disguise = ((Object *)victim)->rva0028F4BC();
		if (disguise && disguise->isDisguised())
			allowStealthToPreventAttacks = false;
	}

	if (allowStealthToPreventAttacks && ((Object *)victim)->rva002943B2(source->getControllingPlayer()))
	{
		if (!(victim->m_template->m_kindOf[2] & 0x1000000))
			return ATTACKRESULT_NOT_POSSIBLE;
		Rva00373EC6 *disguise = ((Object *)victim)->rva0028F4BC();
		if (disguise && disguise->isDisguised())
		{
			Player *ourPlayer = source->getControllingPlayer();
			Player *otherPlayer = ThePlayerList->getNthPlayer(disguise->getDisguisedPlayerIndex());
			if (ourPlayer && otherPlayer && ourPlayer->getRelationship(otherPlayer->m_defaultTeam) != ENEMIES)
				return ATTACKRESULT_NOT_POSSIBLE;
		}
	}

	bool reject = false;
	if ((victim->m_template->m_kindOf[1] & 0x800000) && (victim->m_template->m_kindOf[0] & 4))
	{
		if ((source->m_template->m_kindOf[4] & 0x1000) && (bool)((source->m_conditionBits.word(9) >> 13) & 1))
			reject = true;
		const Weapon *weapon = source->getCurrentWeapon(0);
		if (weapon && ((Rva002CA9CA *)weapon->m_template)->rva002CA9CA(6, weapon))
			reject = true;
	}

	Relationship r = reject ? ENEMIES : source->getRelationship(victim);

	if (source->m_template->m_kindOf[1] & 0x800000)
	{
		if (r == ALLIES)
			return ATTACKRESULT_NOT_POSSIBLE;
		if (!(victim->m_template->m_kindOf[0] & 0x80))
			return ATTACKRESULT_NOT_POSSIBLE;
	}

	if (!((victim->m_template->m_kindOf[1] & 0x40000) && r == NEUTRAL))
	{
		if ((victim->m_template->m_kindOf[2] & 0x40000000) && TheAI->m_inner->m_flagBC)
			r = ENEMIES;
		if (r != ENEMIES && !forced && !reject && commandSource == CMD_FROM_PLAYER && !(victim->m_scriptStatus & 0x10))
			return ATTACKRESULT_NOT_POSSIBLE;
	}

	const Object *victimsContainer = victim->m_containedBy;
	ContainModuleInterface *containerContain = victimsContainer ? victimsContainer->m_contain : 0;
	if (victim->testStatus((ObjectStatusTypes)0x3C))
	{
		if (!containerContain || source->m_containedBy != victimsContainer ||
			!victim->testStatus((ObjectStatusTypes)0x25) || !source->testStatus((ObjectStatusTypes)0x25))
			return ATTACKRESULT_NOT_POSSIBLE;
	}

	if (!source->isKindOf((KindOfType)0xCE) && !forced)
	{
		ContainModuleInterface *victimContain = victim->m_contain;
		if (victimContain)
		{
			const Player *apparent = victimContain->getApparentControllingPlayer(source->getControllingPlayer());
			if (apparent)
			{
				const Team *apparentTeam = apparent->m_defaultTeam;
				const Team *sourceTeam = source->m_team;
				if (sourceTeam->getRelationship(apparentTeam) != ENEMIES &&
					commandSource == CMD_FROM_PLAYER && !(victim->m_scriptStatus & 0x10))
					return ATTACKRESULT_NOT_POSSIBLE;
			}
		}
	}

	return getAbleToUseWeaponAgainstTarget(attackType, source, victim, &victim->m_position, commandSource);
}
