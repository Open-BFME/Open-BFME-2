// ?lookForInnerTarget@AIGuardMachine@@QAE_NXZ
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?lookForInnerTarget@AIGuardMachine@@QAE_NXZ, retail 0x005433FA, 929 bytes.
//
// Identity: the existing pin. Donor: Zero Hour AIGuard.cpp
// AIGuardMachine::lookForInnerTarget (able-to-attack gate, team common target,
// guard position from the target / team / position to guard, the area's
// radius and center, then the closest-enemy scan that stores the victim's ID
// as the nemesis). BFME2 target facts: the turret's goal object wins first
// when it is an enemy; area scans are throttled by the AI data interval at
// +0x40 against the frame stored at +0x70; the scan goes through 0x002FFFCA
// with BFME2 search flags (kind-of bit 59, AI data +0x67/+0x68, the AI's
// +0x04/+0x1C, the controlling player's +0x5C, status 0x44) and the guard
// position helper 0x00543326 drives a half-range fallback scan; victims of
// kind-of bit 109 are redirected through Object::adjustVictim; outside the
// area center's trigger the area scan is repeated. Layout as in
// AIGuardMachineGuardPosition.cpp.

#include <math.h>

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
};
typedef UnsignedInt TeamID;

enum Relationship
{
	ENEMIES = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_44 = 0x44
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// BFME's REAL_TO_INT_FLOOR: CRT floor() then the engine's x87 round.
__forceinline Real fast_float_floor(Real f)
{
	return (Real)floor((double)f);
}
__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}
	Real x, y, z;
};

class ICoord3D
{
public:
	ICoord3D(Int ix, Int iy, Int iz) : x(ix), y(iy), z(iz) {}
	Int x, y, z;
};

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(UnsignedInt bit) const
	{
		return m_kindOf[bit >> 5] & (1U << (bit & 0x1f));
	}
	char m_pad000[0x108];
	UnsignedInt m_kindOf[8];
};

class Object;

class TurretStateMachine
{
public:
	Object *getGoalObject();
};

class AttackPriorityInfo;
class PartitionFilter;

struct AIUpdateInterfaceInner
{
	char m_pad00[0x1C];
	void *m_1c;
};

class AIUpdateInterface
{
public:
	char m_pad00[4];
	AIUpdateInterfaceInner *m_04;
	char m_pad08[0x30 - 0x08];
	TurretStateMachine *m_turretMachine;
	char m_pad34[0x70 - 0x34];
	AttackPriorityInfo *m_attackInfo;
	const AttackPriorityInfo *getAttackInfo() const { return m_attackInfo; }
};

struct TeamTemplateInfo
{
	char m_pad[0x216];
	Bool m_attackCommonTarget;
};

class Team
{
public:
	Object *getTeamTargetObject();
	void rva0039E5B9(Coord3D *pos);
	char m_pad[0x30];
	TeamTemplateInfo *m_prototype;
};

class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};
extern TeamFactory *TheTeamFactory;

class Player
{
public:
	char m_pad[0x5C];
	Int m_5c;
};

class Module;

class Object
{
public:
	Bool isAbleToAttack() const;
	Relationship getRelationship(const Object *that) const;
	Int rva0028F4EF();
	Player *getControllingPlayer() const;
	Bool testStatus(ObjectStatusTypes status) const;
	Object *adjustVictim(Object *attacker, Int a, Int b);
	Module *findModule(NameKeyType key) const;

	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Team *getTeam() const { return m_team; }

private:
	char m_pad000[4];
	const ThingTemplate *m_template;
	char m_pad008[0x38 - 0x08];
	Coord3D m_position;
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;
	char m_pad078[0x258 - 0x78];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x304 - 0x25C];
	Team *m_team;
};

class StancesBehavior
{
public:
	Int rva0045ED4B() const;
};
NameKeyType Rva0045EE2CGet();

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	char m_pad[0x40];
	UnsignedInt m_frame;
};
extern GameLogic *TheGameLogic;

struct AIData
{
	char m_pad00[0x40];
	UnsignedInt m_guardAreaScanInterval;
	char m_pad44[0x67 - 0x44];
	Bool m_67;
	Bool m_68;
};

class Rva002FFFCA
{
public:
	void *rva002FFFCA(Object *obj, const Coord3D *pos, Real range, UnsignedInt flags,
		Int attackInfo, Int a, Int b);
};

class AI
{
public:
	Object *findClosestEnemy(const Object *me, Real range, UnsignedInt qualifiers,
		const AttackPriorityInfo *info, PartitionFilter *optionalFilter, Int b);
	char m_pad[0x18];
	AIData *m_aiData;
};
extern AI *TheAI;

class Rva0030B719Shape
{
public:
	Real getRadius() const;
};

class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *pOutCoord) const;
	Bool pointInTrigger(const ICoord3D &point);
	char m_pad[8];
	Rva0030B719Shape m_shape;
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
protected:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class AIGuardMachine : public StateMachine
{
public:
	Bool lookForInnerTarget();
	Coord3D rva00543326() const;
	static Real getStdGuardRange(const Object *obj);
	Object *findTargetToGuardByID() const { return TheGameLogic->findObjectByID(m_targetToGuard); }
	Team *findTeamToGuardByID() const { return TheTeamFactory->findTeamByID(m_teamToGuard); }
	void setNemesisID(ObjectID id) { m_nemesisID = id; }
private:
	unsigned char m_pad18[0x3C - 0x18];
	ObjectID m_targetToGuard; // +0x3C
	TeamID m_teamToGuard; // +0x40
	const PolygonTrigger *m_areaToGuard; // +0x44
	Coord3D m_positionToGuard; // +0x48
	Coord3D m_bfmeAreaCenter; // +0x54
	Bool m_bfmeAreaCenterValid; // +0x60
	unsigned char m_pad61[0x68 - 0x61];
	ObjectID m_nemesisID; // +0x68
	unsigned char m_pad6C[0x70 - 0x6C];
	UnsignedInt m_nextAreaScanFrame; // +0x70
};

enum
{
	KINDOF_BIT_59 = 59,
	KINDOF_BIT_109 = 109
};

Bool AIGuardMachine::lookForInnerTarget()
{
	Object *owner = getOwner();
	if (!owner->isAbleToAttack())
		return false;

	Object *victim = owner->getAI()->m_turretMachine->getGoalObject();
	if (victim && victim->getRelationship(owner) == ENEMIES)
	{
		setNemesisID(victim->getID());
		return true;
	}

	if (owner->getTeam()->m_prototype->m_attackCommonTarget)
	{
		Object *teamVictim = owner->getTeam()->getTeamTargetObject();
		if (teamVictim)
		{
			setNemesisID(teamVictim->getID());
			return true;
		}
	}

	Object *targetToGuard = findTargetToGuardByID();
	Team *teamToGuard = findTeamToGuardByID();
	Coord3D pos;
	if (targetToGuard)
		pos = *targetToGuard->getPosition();
	else if (teamToGuard)
		teamToGuard->rva0039E5B9(&pos);
	else
		pos = m_positionToGuard;

	const PolygonTrigger *area = m_areaToGuard;
	Real visionRange = AIGuardMachine::getStdGuardRange(owner);
	Bool doScan = true;
	if (area)
	{
		if (TheGameLogic->m_frame < m_nextAreaScanFrame + TheAI->m_aiData->m_guardAreaScanInterval)
			doScan = false;
		else
			m_nextAreaScanFrame = TheGameLogic->m_frame;
		visionRange = area->m_shape.getRadius();
		area->getCenterPoint(&pos);
	}

	if (pos.x == 0.0f && pos.y == 0.0f)
		pos = *owner->getPosition();

	Int mode = owner->rva0028F4EF();
	if (mode == 0)
		return false;
	if (mode == 1)
	{
		StancesBehavior *stances = (StancesBehavior *)owner->findModule(Rva0045EE2CGet());
		if (stances && stances->rva0045ED4B() == 3)
			return false;
	}

	UnsignedInt flags = 2;
	if (TheAI->m_aiData->m_67 && owner->getTemplate()->isKindOf(KINDOF_BIT_59))
		flags = 3;
	if (TheAI->m_aiData->m_68)
		flags |= 4;
	if (owner->getAI()->m_04->m_1c != 0)
		flags |= 8;
	if (owner->getControllingPlayer() && owner->getControllingPlayer()->m_5c == 0)
		flags |= 0x20;
	flags |= 0x40;
	if (owner->testStatus(OBJECT_STATUS_BFME_44))
		flags |= 0x10;
	if (owner->getControllingPlayer()->m_5c == 1)
		flags |= 0x80;

	if (doScan)
	{
		victim = (Object *)((Rva002FFFCA *)TheAI)->rva002FFFCA(owner, &pos, visionRange, flags,
			(Int)owner->getAI()->getAttackInfo(), 0, 0);
		if (!victim && !area)
		{
			Coord3D guardPos = rva00543326();
			Real dy = guardPos.y - owner->getPosition()->y;
			Real dx = guardPos.x - owner->getPosition()->x;
			Real halfRange = visionRange * 0.5f;
			if (dy * dy + dx * dx > halfRange * halfRange)
				victim = TheAI->findClosestEnemy(owner, halfRange, flags,
					owner->getAI()->getAttackInfo(), 0, 0);
		}
		if (victim)
		{
			if (victim->getTemplate()->isKindOf(KINDOF_BIT_109))
				victim = victim->adjustVictim(owner, 1, 0);
			if (victim)
			{
				setNemesisID(victim->getID());
				return true;
			}
		}
	}

	if (area)
	{
		Coord3D center = m_bfmeAreaCenter;
		ICoord3D icenter(REAL_TO_INT_FLOOR(center.x), REAL_TO_INT_FLOOR(center.y),
			REAL_TO_INT_FLOOR(center.z));
		if (m_bfmeAreaCenterValid && !((PolygonTrigger *)area)->pointInTrigger(icenter))
		{
			Object *target = (Object *)((Rva002FFFCA *)TheAI)->rva002FFFCA(owner, &pos, visionRange, flags,
				(Int)owner->getAI()->getAttackInfo(), 0, 0);
			if (target)
			{
				if (target->getTemplate()->isKindOf(KINDOF_BIT_109))
					target = target->adjustVictim(owner, 1, 0);
				if (target)
				{
					setNemesisID(target->getID());
					return true;
				}
			}
		}
	}
	return false;
}
