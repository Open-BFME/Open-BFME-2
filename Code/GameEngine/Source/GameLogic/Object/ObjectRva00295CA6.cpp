// cl: /O1
//
// ?rva00295CA6@Object@@QAE_NXZ retail 0x00295CA6..0x00295F05 (607B).
//
// Object melee victim picker. WorldBuilder twin 0xCC25A0 (unnamed; its
// NETWORK_CRC traces read "npcc dead" "npcc stunned" "npcc struct/not_auto"
// "npcc newEnemy" "npcc meleeAttackAdjacentVictim"). Called by
// Object::rva00295F05 at 0x00295F9F (ObjectRva00295FA9.cpp).
// Read from retail: the two related objects (rva0028ACA0 0x0028ACA0 of this
// and of this' container when status 0x26 is set) and the related object's
// container; the first id list from the pathfinder at TheAI+0x10
// (0x002EF3D9) keeps the last living unstunned enemy not of kind 0x6D (kinds
// 7 and 0x82 only when related) preferring the related one; the second list
// (0x002F2865) takes the related object or its producer outright and
// otherwise any reachable enemy (0x002EC479 with this position at +0x38)
// re-running rva00295F05 once through the recursion guard 0x00DFED60.
// The winner is attacked through 0x00295A84 when it is still reachable.
// Retail returns al (mov al 1 / xor al al) so the return type is bool; the
// existing pin spells void.
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef bool Bool;

enum Relationship
{
	ENEMIES = 0
};

enum ObjectStatusTypes
{
	RVA_OBJECT_STATUS_26 = 0x26
};

struct ThingTemplate
{
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[20];		// +0x108
	__forceinline bool isKindOf(int k) const { return (m_kindOf[k >> 3] & (1 << (k & 7))) != 0; }
};

struct Rva00295CA6ContainView
{
	unsigned char m_pad00[0x5C];
	Bool m_busy;
};

class Rva002EF3D9Host
{
public:
	Int rva002EF3D9(char *object, Int ids);
};

class Rva002F2865Host
{
public:
	Int rva002F2865(char *object, Int ids);
};

class Pathfinder
{
public:
	Bool rva002EC479(Object *obj, const Coord3D *pos, Object *other);
};

class AI
{
public:
	unsigned char m_pad00[0x10];
	void *m_pathfinder;		// +0x10
	void *pathfinder() const { return m_pathfinder; }
};

extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern int g_Va00DFED60;

class Object
{
public:
	Object *rva0028ACA0() const;
	Bool testStatus(ObjectStatusTypes status) const;
	Relationship getRelationship(const Object *other) const;
	Object *rva002931F5(Bool checkProducer);
	void rva00295F05(Bool force);
	void rva00295A84(Object *other);
	bool rva00295CA6();

	const ThingTemplate *getTemplate() const { return m_template; }
	bool isEffectivelyDead() const { return (m_flags438 & 1) != 0; }

private:
	unsigned char m_pad00[4];
	ThingTemplate *m_template;		// +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos;				// +0x38
	unsigned char m_pad44[0x25C - 0x44];
	Rva00295CA6ContainView *m_containView;	// +0x25C
	unsigned char m_pad260[0x274 - 0x260];
	Object *m_containedBy;			// +0x274
	unsigned char m_pad278[0x438 - 0x278];
	unsigned char m_flags438;		// +0x438
};

bool Object::rva00295CA6()
{
	Object *related = rva0028ACA0();
	Object *containerRelated = 0;
	if (testStatus(RVA_OBJECT_STATUS_26) && m_containedBy != 0)
		containerRelated = m_containedBy->rva0028ACA0();
	Object *relatedContainer = 0;
	if (related != 0 && related->testStatus(RVA_OBJECT_STATUS_26))
		relatedContainer = related->m_containedBy;

	ObjectID ids[16];
	Int count = ((Rva002EF3D9Host *)TheAI->pathfinder())->rva002EF3D9((char *)this, (Int)ids);
	Object *victim = 0;
	Int i;
	for (i = 0; i < count; i++)
	{
		Object *obj = TheGameLogic->findObjectByID(ids[i]);
		if (obj == 0)
			continue;
		if (obj->getTemplate()->isKindOf(0x6D))
			continue;
		if (obj->isEffectivelyDead())
			continue;
		if (obj->m_containView != 0 && obj->m_containView->m_busy)
			continue;
		if (getRelationship(obj) != ENEMIES)
			continue;
		if ((obj->getTemplate()->isKindOf(7) || obj->getTemplate()->isKindOf(0x82)) && obj != related && obj != containerRelated)
			continue;
		if (victim == 0 || victim != related)
			victim = obj;
	}

	Int count2 = ((Rva002F2865Host *)TheAI->pathfinder())->rva002F2865((char *)this, (Int)ids);
	if (count2 != 0)
	{
		for (Int j = 0; j < count2; j++)
		{
			Object *obj = TheGameLogic->findObjectByID(ids[j]);
			if (obj == 0)
				continue;
			if (obj->getTemplate()->isKindOf(0x6D))
				continue;
			if (obj == containerRelated || (containerRelated != 0 && obj->rva002931F5(false) == containerRelated))
			{
				victim = obj;
				break;
			}
			if (relatedContainer != 0 && obj->m_containedBy == relatedContainer)
				victim = obj;
			if (obj->isEffectivelyDead())
				continue;
			if (obj->m_containView != 0 && obj->m_containView->m_busy)
				continue;
			if (getRelationship(obj) != ENEMIES)
				continue;
			if (!((Pathfinder *)TheAI->pathfinder())->rva002EC479(this, &m_pos, obj))
				continue;
			if (victim != 0 && victim == related)
				continue;
			if ((obj->getTemplate()->isKindOf(7) || obj->getTemplate()->isKindOf(0x82)) && obj != related && obj != containerRelated)
				continue;
			victim = obj;
			if (obj->testStatus(RVA_OBJECT_STATUS_26))
				continue;
			if (g_Va00DFED60 == 0)
			{
				g_Va00DFED60++;
				obj->rva00295F05(false);
				g_Va00DFED60--;
			}
		}
	}

	if (victim != 0 && ((Pathfinder *)TheAI->pathfinder())->rva002EC479(this, &m_pos, victim))
	{
		rva00295A84(victim);
		return true;
	}
	return false;
}
