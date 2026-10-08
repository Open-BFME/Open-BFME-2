// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// BFME 2's two giant-bird path-following states. WorldBuilder's
// GiantBirdAIUpdate.cpp names their followToNextPointNow bodies:
//
//  - GiantBirdFollowPathState::followToNextPointNow, retail 0x00368662
//    (305 bytes, WorldBuilder 0x00F334D0), point index at +0x58;
//  - GiantBirdFollowWaypointPathState::followToNextPointNow, retail
//    0x003687DD (305 bytes, WorldBuilder 0x00F34190), point index at +0x20.
//
// The other members are the onEnter/onExit/update slots (4, 5, 6) of the
// vtables whose bodies call those followers directly:
//
//  - 0x00C172B8 (slot 2 returns "AIFollowPathState", slot 5 chains to the
//    rowed AIFollowPathState::onExit, so the base is inferred):
//    onEnter 0x003685FA (90), onExit 0x00368FE6 (126), update 0x00368F08 (222);
//  - 0x00C17478 (slot 2 returns "GiantBirdFollowWaypointPathState", slot 5
//    chains to State::onExit): onEnter 0x00368798 (69), onExit 0x00369590
//    (126), update 0x003694B2 (222).
//
// The two bodies of each slot differ only in the point-index offset, the
// follower they call, the base onExit and the follow-path onEnter's extra
// locomotor gate (AI +0x1F0, whose +0x48 value is copied to the flight
// height). Retail proves the owner/AI/locomotor chain, the path-point
// accessor of the AI's state machine (+0x30, rowed 0x00346FA5), the loop byte
// (+0x550), the look-ahead bit 7 of AI +0x4B8, the flight height (+0x540)
// added to the terrain's ground height (TerrainLogic slot 6), the route call
// (rowed 0x003681F2) with the current point, the look-ahead point and a bool
// set when there is none, the goal point (+0x544) and range (+0x538) the
// update steers to through the rowed 0x00368C7A, and condition bits 61, 103
// and 72 cleared on exit. Retail loads the look-ahead index into a register
// before pushing it, which the local copy reproduces. The roles of AI +0x4EC
// and +0x534 are not recovered.

typedef bool Bool;
typedef float Real;

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

template <int N> class GiantBirdPathSlots : public GiantBirdPathSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class GiantBirdPathSlots<0>
{
};

class Rva00346FA5
{
public:
	void *rva00346FA5(int index) const;
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum StateExitType
{
	EXIT_NORMAL = 0
};

class Thing
{
public:
	void setPosition(const Coord3D *position);
};
class BfmeVec3EJ;
class Gen_000E5A50
{
public:
	Real bfmeDistanceSquared(const BfmeVec3EJ *point) const;
};
class Rva0036748E
{
public:
	void rva00368654(Bool value);
};

class Rva00368C7A
{
public:
	void rva00368C7A(Real amount, const Coord3D *position, Bool argument);
	void rva003681F2(const Coord3D *position, const unsigned char *mask,
		const Coord3D *lookAhead, Bool noLookAhead);
};

class TerrainLogic : public GiantBirdPathSlots<6>
{
public:
	virtual Real getGroundHeight(Real x, Real y, int unused);
};
extern TerrainLogic *TheTerrainLogic;
extern unsigned char g_00E01EC0[4];

class Locomotor
{
public:
	Real getBfme48() const { return m_bfme48; }
private:
	unsigned char m_pad00[0x48];
	Real m_bfme48; // +0x48
};

class AIUpdateInterface
{
public:
	Rva00346FA5 *getPathMachine() const { return m_pathMachine; }
	Locomotor *getLocomotor() const { return m_locomotor; }
	Bool hasLocomotor() const { return m_locomotor != 0; }
	Bool loopsPath() const { return m_loopPath; }
	Real getPathHeight() const { return m_pathHeight; }
	void setLookAhead(Bool value)
	{
		if (value) m_pathFlags |= 0x80;
		else m_pathFlags &= ~0x80;
	}
private:
	void *m_vtbl;
	unsigned char m_pad04[0x30 - 4];
	Rva00346FA5 *m_pathMachine; // +0x30
	unsigned char m_pad34[0x1F0 - 0x34];
	Locomotor *m_locomotor; // +0x1F0
	unsigned char m_pad1F4[0x4B8 - 0x1F4];
	unsigned int m_pathFlags; // +0x4B8, bit 7
	unsigned char m_pad4BC[0x4EC - 0x4BC];
public:
	Bool m_bfme4EC; // +0x4EC
	unsigned char m_pad4ED[0x534 - 0x4ED];
	unsigned char m_bfme534; // +0x534
	unsigned char m_pad535[0x538 - 0x535];
	Real m_goalRange; // +0x538
	unsigned char m_pad53C[0x540 - 0x53C];
	Real m_pathHeight; // +0x540
	Coord3D m_goalPosition; // +0x544
	Bool m_loopPath; // +0x550
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	Bool isDead() const { return (m_status438 & 1) != 0; }
	const Coord3D *getPosition() const { return &m_position; }
	void rva0028ACEE(const Coord3D *pos, int value);
	void rva0028AE6D();
	__forceinline void clearModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x10C - 0x44];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x258 - (0x10C + sizeof(Rva0010CBits))];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_status438; // +0x438
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIFollowPathState : public State
{
public:
	virtual void onExit(StateExitType status);
};

class GiantBirdFollowPathState : public AIFollowPathState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	Bool followToNextPointNow();
private:
	unsigned char m_pad1C[0x58 - 0x1C];
	int m_pointIndex; // +0x58
};

StateReturnType GiantBirdFollowPathState::onEnter()
{
	m_pointIndex = 0;
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();
	if (ai == 0)
		return STATE_FAILURE;
	if (owner->isDead())
		return STATE_FAILURE;
	if (!ai->hasLocomotor())
		return STATE_FAILURE;
	ai->m_pathHeight = ai->getLocomotor()->getBfme48();
	if (!followToNextPointNow())
		return STATE_SUCCESS;
	if (!ai->m_bfme4EC)
		return STATE_FAILURE;
	reinterpret_cast<Rva0036748E *>(ai)->rva00368654(true);
	return STATE_CONTINUE;
}

StateReturnType GiantBirdFollowPathState::update()
{
	Object *owner = getMachineOwner();
	if (owner->isDead())
		return STATE_FAILURE;
	AIUpdateInterface *ai = owner->getAI();
	if (!ai)
		return STATE_FAILURE;
	((Rva00368C7A *)ai)->rva00368C7A(ai->m_pathHeight, &ai->m_goalPosition, false);
	Real range = ai->m_goalRange;
	Coord3D position;
	const Coord3D *goal = &ai->m_goalPosition;
	position.x = goal->x;
	position.y = goal->y;
	position.z = goal->z;
	Bool close = reinterpret_cast<Gen_000E5A50 *>(owner)->bfmeDistanceSquared(
		reinterpret_cast<const BfmeVec3EJ *>(&position)) < range * range;
	if (float(ai->m_bfme534) != 0.0f || close)
	{
		reinterpret_cast<Thing *>(owner)->setPosition(&position);
		if (!followToNextPointNow())
			return STATE_SUCCESS;
		if (!ai->m_bfme4EC)
			return STATE_FAILURE;
	}
	return STATE_CONTINUE;
}

void GiantBirdFollowPathState::onExit(StateExitType status)
{
	AIFollowPathState::onExit(status);
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();
	if (ai)
		ai->setLookAhead(false);
	owner->clearModelConditionBit(61);
	owner->clearModelConditionBit(103);
	owner->clearModelConditionBit(72);
	owner->rva0028ACEE(owner->getPosition(), 1);
}

Bool GiantBirdFollowPathState::followToNextPointNow()
{
	Object *owner = getMachineOwner();
	if (!owner) return false;
	AIUpdateInterface *ai = owner->getAI();
	if (!ai) return false;
	if (!ai->hasLocomotor()) return false;

	const Coord3D *point = (const Coord3D *)ai->getPathMachine()->rva00346FA5(m_pointIndex++);
	if (!point)
	{
		if (!ai->loopsPath()) return false;
		m_pointIndex = 0;
		point = (const Coord3D *)ai->getPathMachine()->rva00346FA5(m_pointIndex++);
		if (!point) return false;
	}

	Coord3D lookAhead;
	int nextIndex = m_pointIndex;
	const Coord3D *next = (const Coord3D *)ai->getPathMachine()->rva00346FA5(nextIndex);
	if (next)
	{
		ai->setLookAhead(true);
		lookAhead = *next;
		next = &lookAhead;
		lookAhead.z = TheTerrainLogic->getGroundHeight(lookAhead.x, lookAhead.y, 0) + ai->getPathHeight();
	}
	else
		ai->setLookAhead(false);

	Coord3D position;
	position.x = point->x;
	position.y = point->y;
	position.z = point->z;
	position.z = TheTerrainLogic->getGroundHeight(position.x, position.y, 0) + ai->getPathHeight();
	((Rva00368C7A *)ai)->rva003681F2(&position, g_00E01EC0, next, next == 0);
	return true;
}

class GiantBirdFollowWaypointPathState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	Bool followToNextPointNow();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	int m_pointIndex; // +0x20
};

StateReturnType GiantBirdFollowWaypointPathState::onEnter()
{
	m_pointIndex = 0;
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();
	if (ai == 0)
		return STATE_FAILURE;
	if (owner->isDead())
		return STATE_FAILURE;
	if (!followToNextPointNow())
		return STATE_SUCCESS;
	if (!ai->m_bfme4EC)
		return STATE_FAILURE;
	ai->setLookAhead(true);
	return STATE_CONTINUE;
}

StateReturnType GiantBirdFollowWaypointPathState::update()
{
	Object *owner = getMachineOwner();
	if (owner->isDead())
		return STATE_FAILURE;
	AIUpdateInterface *ai = owner->getAI();
	if (!ai)
		return STATE_FAILURE;
	((Rva00368C7A *)ai)->rva00368C7A(ai->m_pathHeight, &ai->m_goalPosition, false);
	Real range = ai->m_goalRange;
	Coord3D position;
	const Coord3D *goal = &ai->m_goalPosition;
	position.x = goal->x;
	position.y = goal->y;
	position.z = goal->z;
	Bool close = reinterpret_cast<Gen_000E5A50 *>(owner)->bfmeDistanceSquared(
		reinterpret_cast<const BfmeVec3EJ *>(&position)) < range * range;
	if (float(ai->m_bfme534) != 0.0f || close)
	{
		reinterpret_cast<Thing *>(owner)->setPosition(&position);
		if (!followToNextPointNow())
			return STATE_SUCCESS;
		if (!ai->m_bfme4EC)
			return STATE_FAILURE;
	}
	return STATE_CONTINUE;
}

void GiantBirdFollowWaypointPathState::onExit(StateExitType status)
{
	State::onExit(status);
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();
	if (ai)
		ai->setLookAhead(false);
	owner->clearModelConditionBit(61);
	owner->clearModelConditionBit(103);
	owner->clearModelConditionBit(72);
	owner->rva0028ACEE(owner->getPosition(), 1);
}

Bool GiantBirdFollowWaypointPathState::followToNextPointNow()
{
	Object *owner = getMachineOwner();
	if (!owner) return false;
	AIUpdateInterface *ai = owner->getAI();
	if (!ai) return false;
	if (!ai->hasLocomotor()) return false;

	const Coord3D *point = (const Coord3D *)ai->getPathMachine()->rva00346FA5(m_pointIndex++);
	if (!point)
	{
		if (!ai->loopsPath()) return false;
		m_pointIndex = 0;
		point = (const Coord3D *)ai->getPathMachine()->rva00346FA5(m_pointIndex++);
		if (!point) return false;
	}

	Coord3D lookAhead;
	int nextIndex = m_pointIndex;
	const Coord3D *next = (const Coord3D *)ai->getPathMachine()->rva00346FA5(nextIndex);
	if (next)
	{
		ai->setLookAhead(true);
		lookAhead = *next;
		next = &lookAhead;
		lookAhead.z = TheTerrainLogic->getGroundHeight(lookAhead.x, lookAhead.y, 0) + ai->getPathHeight();
	}
	else
		ai->setLookAhead(false);

	Coord3D position;
	position.x = point->x;
	position.y = point->y;
	position.z = point->z;
	position.z = TheTerrainLogic->getGroundHeight(position.x, position.y, 0) + ai->getPathHeight();
	((Rva00368C7A *)ai)->rva003681F2(&position, g_00E01EC0, next, next == 0);
	return true;
}
