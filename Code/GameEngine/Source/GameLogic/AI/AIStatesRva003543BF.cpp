// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc

// Retail 0x003543BF (411 bytes), between AIAttackFollowWaypointPathState::update
// and AIEnterState::update in the AIStates.cpp block; WorldBuilder twin
// 0x00E22020 (unnamed, callgraph lead).  The thiscall receiver is never read
// (no retail reference to the body survives either), so the owner stays
// address-named.  An uncontained object with a current weapon looks around
// its target, within the smaller of the target distance and the weapon's
// range, for the nearest object (filter vftable 0x00811A5C, allow 0x002612C6)
// that it can reach past without overshooting the target, then makes that
// object its AI's command target while the original target stays the victim.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/PartitionRangeQueryCallView.h"
#include <math.h>

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum WeaponSlotType;
class Weapon;

class Rva00352F9D
{
public:
	void rva0035325A(const void *obj, CommandSourceType cmdSource);	// 0x0035325A
};

class Rva003543BFAIPrefix
{
	char m_pad0[0x20];
};

class AIUpdateInterface : public Rva003543BFAIPrefix, public Rva00352F9D
{
public:
	void setCurrentVictim(const Object *victim);	// 0x00268D1F
};

class Object
{
public:
	float rva002615E3(const Coord3D *pos) const;	// 0x002615E3 2D distance squared
	float rva00263763(const void *other) const;	// 0x00263763 distance squared
	Weapon *getCurrentWeapon(WeaponSlotType *slot);	// 0x0028AEBD

	const Coord3D *getPosition() const
	{
		return &m_pos;
	}
	float getBoundingCircleRadius() const
	{
		return m_boundingCircleRadius;
	}
	AIUpdateInterface *getAI()
	{
		return m_ai;
	}
	bool isContained() const
	{
		return m_containedBy != 0;
	}

	char m_pad000[0x38];
	Coord3D m_pos;	// +0x38
	char m_pad044[0xB8 - 0x44];
	float m_boundingCircleRadius;	// +0xB8
	char m_pad0BC[0x258 - 0xBC];
	AIUpdateInterface *m_ai;	// +0x258
	char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy;	// +0x274
};

class Weapon
{
public:
	// 0x002C9BE4: two-object range forwarder (the source and the victim's
	// position go to 0x002C9BC3 on the same receiver).  WorldBuilder calls its
	// twin with the current weapon as receiver here.
	float rva002C9BE4(const Object *source, const Object *victim) const;
};

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;	// +0x04
};

// vftable 0x00811A5C, allow 0x002612C6.
class Rva002612C6Filter : public Rva000421C8
{
public:
	Rva002612C6Filter(const Object *obj) : m_obj(obj), m_flag(false) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;	// +0x08
	bool m_flag;	// +0x0C
};

extern PartitionManager *ThePartitionManager;

class Rva003543BF
{
public:
	bool rva003543BF(Object *obj, Object *target);
};

bool Rva003543BF::rva003543BF(Object *obj, Object *target)
{
	if (obj->isContained())
		return false;
	float dist = sqrtf(obj->rva002615E3(target->getPosition()));
	float range = dist;
	Weapon *weapon = obj->getCurrentWeapon(0);
	if (weapon)
	{
		float weaponRange = weapon->rva002C9BE4(obj, target);
		if (range > weaponRange)
			range = weaponRange;
	}
	else
	{
		return false;
	}

	Rva002612C6Filter filter(obj);
	Object *best = 0;
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(target->getPosition(), range, 1, &filter, 0);
	float bestDist = 0.0f;
	for (Object *other = iter.next(); other; other = iter.next())
	{
		float fromObj = sqrtf(obj->rva00263763(other));
		float fromTarget = sqrtf(target->rva00263763(other));
		if (other->getBoundingCircleRadius() * 1.5f + fromObj > dist)
			continue;
		if (fromObj + fromTarget > dist)
			continue;
		if (!best || bestDist > fromObj)
		{
			best = other;
			bestDist = fromObj;
		}
	}
	if (best)
	{
		AIUpdateInterface *ai = obj->getAI();
		ai->setCurrentVictim(target);
		ai->rva0035325A(best, CMD_FROM_AI);
		return true;
	}
	return false;
}
