// cl: /O1 /arch:SSE /DNDEBUG /MD /EHs-c-
//
// ?isSourceObjectWithGoalPositionWithinAttackRange@Weapon@@QBE_NPBVObject@@PBUCoord3D@@01@Z
// @0x002CB2D1 139B: weapon range test from a goal position. WorldBuilder names
// it Weapon::isSourceObjectWithGoalPositionWithinAttackRange (Weapon.cpp
// 2680..2681, targetPos/goalPos asserts, same victim-or-position branches);
// the const signature is Zero Hour's (donor), not target evidence. Retail takes the squared distance from
// the rowed Object helpers 0x002636F6 (victim Object, its +0x38 position) or
// 0x002C97E8 (bare position), the weapon's float range from the rowed
// 0x002C9B80 with the height difference, and the template's (+0x04) rowed
// getMinimumAttackRange 0x002C92FA: false inside the minimum range, else
// whether the squared range reaches the distance. Writing the minimum test as
// `!(min*min > d)` returning the range test gives retail's shared false tail.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_25 = 0x25,
	OBJECT_STATUS_4B = 0x4B
};

// The rowed bool getter at 0x006BE160 (placeholder row name), called on the
// Object's +0xA8 member.
class BfmeThingTemplateShadowSelector
{
public:
	bool usePluralShadowName() const;
};

struct Rva002CB35CTemplate
{
	char m_pad000[0x108];
	unsigned char m_kindOf[0x20];		// +0x108 KindOf bits
	__forceinline bool isKindOf(int kind) const { return (m_kindOf[kind >> 3] & (1 << (kind & 7))) != 0; }
};

struct Rva002CB35CAI
{
	char m_pad000[0x1F0];
	void *m_1F0;						// +0x1F0
};

#include "../../../Include/Common/Module.h"

// Partial storage view: the portal finder returns an unadjusted Module entry.
// Native 2CB45A tests its byte at +0x3C; derived identity is not recovered.
class Rva002CB35CModuleView : public Module
{
public:
    char m_pad08[0x3C - 0x08];
    bool m_3C;
};


class Object
{
public:
	float rva002636F6(const Coord3D *a, const void *other, const Coord3D *b) const;
	float rva0028ED19(const Coord3D *a, const void *other, const Coord3D *b) const;	// pinned 0x0028ED19
	float rva002C97E8(const Coord3D *a, const Coord3D *b) const;
	float rva00263763(const void *other) const;
	bool testStatus(ObjectStatusTypes status) const;
	int rva0028B511() const;
	char m_pad000[4];
	Rva002CB35CTemplate *m_template;	// +0x04
	char m_pad008[0xA8 - 8];
	BfmeThingTemplateShadowSelector m_A8;	// +0xA8
	char m_pad0A9[0x258 - 0xA9];
	Rva002CB35CAI *m_258;				// +0x258
};

class DynamicPortalBehaviour
{
public:
	static Module *rva004608E0(Object *obj);
};

class Pathfinder
{
public:
	bool rva002EC479(Object *obj, const Coord3D *pos, Object *victim);	// pinned 0x002EC479
};

struct Rva002CB35CAIData
{
	char m_pad000[0xD0];
	float m_chaseFromBehindLimit;							// +0xD0
};

class AI
{
public:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;			// +0x10
	char m_pad14[4];
	Rva002CB35CAIData *m_data;			// +0x18
};
extern AI *TheAI;

class WeaponTemplate
{
public:
	float getMinimumAttackRange() const;
	char m_pad000[0x125];
	bool m_meleeWeapon;							// +0x125: melee
};

class Rva002C9B80Owner
{
public:
	float rva002C9B80(void *a, float b);
private:
	void *m_00;
	WeaponTemplate *m_04;		// +0x04
};

// The same weapon object under its WorldBuilder class name; only the method
// named from WorldBuilder is declared on it so far.
#include "../../../Include/GameLogic/Weapon.h"


bool Weapon::isSourceObjectWithGoalPositionWithinAttackRange(const Object *source, const Coord3D *goalPos,
	const Object *target, const Coord3D *targetPos) const
{
	float distSq;
	const Coord3D *pos;
	if (target)
	{
		pos = (const Coord3D *)((const char *)target + 0x38);
		distSq = source->rva002636F6(goalPos, target, pos);
	}
	else
	{
		if (!targetPos)
			return false;
		pos = targetPos;
		distSq = source->rva002C97E8(goalPos, pos);
	}
	float range = ((Rva002C9B80Owner *)this)->rva002C9B80((void *)source, pos->z - goalPos->z);
	float minRange = m_template->getMinimumAttackRange();
	if (!(minRange * minRange > distSq))
		return range * range >= distSq;
	return false;
}

// Weapon::isWithinAttackRange, retail 0x002CB35C (568 bytes). Name from
// WorldBuilder (Weapon.cpp lines 2737..2779, sourcePos/targetPos asserts,
// callgraph evidence). A melee template (+0x125) asks the pathfinder
// (0x002EC479) when the victim can be reached in melee; otherwise compares the
// squared distance (plus the bonus squared) against the squared 0x002C9B80
// range and, when asked, the template's squared minimum range.
bool Weapon::isWithinAttackRange(Object *source, const Coord3D *pos,
	Object *victim, const Coord3D *victimPos, float bonus, bool checkMinimum)
{
	if (m_template->m_meleeWeapon)
	{
		if (!victim)
			return false;
		if (source->testStatus(OBJECT_STATUS_25) && victim->testStatus(OBJECT_STATUS_25))
			return true;
		bool melee = true;
		if (!victim->m_template->isKindOf(7))
		{
			Rva002CB35CAI *ai = victim->m_258;
			if (!ai || !ai->m_1F0)
				melee = false;
		}
		if (melee)
		{
			if (source->testStatus(OBJECT_STATUS_4B))
			{
				float reach = TheAI->m_data->m_chaseFromBehindLimit;
				if (source->rva00263763(victim) < reach * reach)
					return true;
			}
			bool result = TheAI->m_pathfinder->rva002EC479(source, pos, victim);
			if (result && !victim->m_template->isKindOf(150))
			{
				int sourceLayer = source->rva0028B511();
				int victimLayer = victim->rva0028B511();
				if (sourceLayer == 1 && victimLayer >= 17)
					return false;
				if (victimLayer == 1 && sourceLayer >= 17)
				{
					Module *portal = DynamicPortalBehaviour::rva004608E0(victim);
					if (!portal || !((Rva002CB35CModuleView *)portal)->m_3C)
						return false;
				}
			}
			return result;
		}
	}
	float distSq;
	float rangeSq;
	if (victim)
	{
		if (source->m_A8.usePluralShadowName() && !victim->m_A8.usePluralShadowName())
			distSq = source->rva0028ED19(pos, victim, victimPos);
		else if (!source->m_A8.usePluralShadowName() && victim->m_A8.usePluralShadowName())
			distSq = victim->rva0028ED19(victimPos, source, pos);
		else
			distSq = source->rva002636F6(pos, victim, victimPos);
		float range = ((Rva002C9B80Owner *)this)->rva002C9B80(source, victimPos->z - pos->z);
		rangeSq = range * range;
	}
	else
	{
		distSq = source->rva002C97E8(pos, victimPos);
		float range = ((Rva002C9B80Owner *)this)->rva002C9B80(source, victimPos->z - pos->z) - 2.5f;
		rangeSq = range * range;
	}
	distSq += bonus * bonus;
	float minRange = m_template->getMinimumAttackRange();
	float minSq = minRange * minRange;
	if (source->testStatus(OBJECT_STATUS_25))
		minSq = 0.0f;
	if (checkMinimum && minSq > distSq)
		return false;
	if (rangeSq >= distSq)
		return true;
	return false;
}
