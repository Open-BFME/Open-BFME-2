// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// BFME 2's giant-bird normal-flight state and the attack-move state derived
// from it. BFME 1's GiantBirdAttackMoveToStateOnEnter.cpp (Open-BFME-1) is
// the donor for all three bodies; the BFME 2 offsets below are read from
// retail, not carried over:
//
//  - GiantBirdNormalFlightState::onEnter, retail 0x00369064 (233 bytes), and
//    ::update, retail 0x0036914D (202 bytes): the attack-move bodies call
//    both directly (0x0036976A, tail jmp 0x003697B6) and the attack-move
//    onEnter (rowed 0x0036960E, vtable 0x00C17548 slot 4) tail-jumps to the
//    onEnter;
//  - GiantBirdAttackMoveToState::update, retail 0x00369669 (395 bytes),
//    vtable 0x00C17548 slot 6.
//
// Retail facts: condition bit 155 cleared on enter, bits 61 and 156 cleared
// when the attack machine is busy, AI slot 142 (the donor's
// chooseLocomotorSet) with 0, the locomotor (+0x1F0) +0x48 height copied to
// AI +0x540, the machine's goal position (+0x24) raised over the ground when
// the state's +0x21 byte is set and object status 0x5B is clear, the route
// call (rowed 0x003681F2) and the AI +0x4EC result. The update steers through
// the rowed 0x00368C7A with no point and finishes when AI +0x534 is set or
// the goal (+0x544) is within the range (+0x538). The attack machine (+0x28)
// is a state machine whose current state (+0x04) answers slot 8 (isIdle);
// slots 4, 8 and 14 of the machine are the donor's updateStateMachine,
// setState and setGoalObject. The goal handle (+0x24) is written to AI +0x48;
// a mood target sets AI +0x48 to 2 and +0x3C7. The roles of AI +0x4EC,
// +0x534, +0x3C7 and the state's +0x21 byte are not recovered.

typedef bool Bool;
typedef int Int;
typedef float Real;

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

template <int N> class GiantBirdFlightSlots : public GiantBirdFlightSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class GiantBirdFlightSlots<0>
{
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_5B = 0x5B
};

class Object;

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

class Rva00368C7A
{
public:
	void rva00368C7A(Real amount, const Coord3D *position, Bool argument);
	void rva003681F2(const Coord3D *position, const unsigned char *mask,
		const Coord3D *lookAhead, Bool noLookAhead);
};

class Rva00375AF7HeightQuery
{
public:
	Real rva00375B7A(Real x, Real y);
};
extern Rva00375AF7HeightQuery *g_00E01F10;
extern unsigned char g_00E01EC0[4];

#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Locomotor
{
public:
	Real getBfme48() const { return m_bfme48; }
private:
	unsigned char m_pad00[0x48];
	Real m_bfme48; // +0x48
};

class AIUpdateInterface : public GiantBirdFlightSlots<136>
{
public:
	virtual void setLocomotorGoalNone() = 0;
	virtual void slot137() = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual void chooseLocomotorSet(int set) = 0;
	virtual Int getLastCommandSource() = 0;

	Object *checkForCrateToPickup();
	void rva0026304D(int frame);
	Object *getNextMoodTarget(Bool calledByAI, Bool calledDuringIdle);
	void rva00262AEA();

	Locomotor *getLocomotor() const { return m_locomotor; }
private:
	unsigned char m_pad04[0x48 - 4];
public:
	Int m_lastCommandSource; // +0x48
private:
	unsigned char m_pad4C[0x1F0 - 0x4C];
	Locomotor *m_locomotor; // +0x1F0
	unsigned char m_pad1F4[0x3C7 - 0x1F4];
public:
	Bool m_bfme3C7; // +0x3C7
private:
	unsigned char m_pad3C8[0x4EC - 0x3C8];
public:
	Bool m_bfme4EC; // +0x4EC
	unsigned char m_pad4ED[0x534 - 0x4ED];
	unsigned char m_bfme534; // +0x534
	unsigned char m_pad535[0x538 - 0x535];
	Real m_goalRange; // +0x538
	unsigned char m_pad53C[0x540 - 0x53C];
	Real m_pathHeight; // +0x540
	Coord3D m_goalPosition; // +0x544
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
	Bool testStatus(ObjectStatusTypes status) const;
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
	unsigned char m_pad000[0x10C];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x258 - (0x10C + sizeof(Rva0010CBits))];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_status438; // +0x438
};

enum StateExitType
{
	EXIT_NORMAL = 0
};

class StateMachine;

class State : public GiantBirdFlightSlots<4>
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	virtual void slot07();
	virtual Bool isIdle();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class StateMachine : public GiantBirdFlightSlots<4>
{
public:
	virtual void updateStateMachine() = 0;
	virtual void start() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void setState(Int id) = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void setGoalObject(Object *object) = 0;

	Bool isInIdleState() const
	{
		return m_currentState ? m_currentState->isIdle() : true;
	}
	Object *getOwner() const { return m_owner; }
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
private:
	State *m_currentState; // +0x04
	unsigned char m_pad08[0x14 - 0x08];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
};

class GiantBirdNormalFlightState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad1C[0x21 - 0x1C];
	Bool m_bfme21; // +0x21
};

class GiantBirdAttackMoveToState : public GiantBirdNormalFlightState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	Int m_commandSource; // +0x24
	StateMachine *m_attackMachine; // +0x28
	Int m_retryCount; // +0x2C
};

StateReturnType GiantBirdNormalFlightState::onEnter()
{
	Object *owner = getMachineOwner();
	owner->clearModelConditionBit(155);
	AIUpdateInterface *ai = owner->getAI();
	if (!ai)
		return STATE_FAILURE;
	else
	{
		if (owner->isDead())
			return STATE_FAILURE;
		ai->chooseLocomotorSet(0);
		Locomotor *locomotor = ai->getLocomotor();
		if (!locomotor)
			return STATE_FAILURE;
		ai->m_pathHeight = locomotor->getBfme48();

		const Coord3D *source = m_machine->getGoalPosition();
		Coord3D goal;
		goal.x = source->x;
		goal.y = source->y;
		goal.z = source->z;
		if (m_bfme21 && !owner->testStatus(OBJECT_STATUS_BFME_5B))
		{
			Real height = ai->m_pathHeight;
			goal.z = g_00E01F10->rva00375B7A(goal.x, goal.y) + height;
		}
		reinterpret_cast<Rva00368C7A *>(ai)->rva003681F2(&goal, g_00E01EC0, 0, true);
		return ai->m_bfme4EC ? STATE_CONTINUE : STATE_FAILURE;
	}
}

StateReturnType GiantBirdNormalFlightState::update()
{
	Object *owner = getMachineOwner();
	if (owner->isDead())
		return STATE_FAILURE;
	AIUpdateInterface *ai = owner->getAI();
	if (!ai)
		return STATE_FAILURE;
	reinterpret_cast<Rva00368C7A *>(ai)->rva00368C7A(ai->m_pathHeight, 0, true);
	if (!ai->m_bfme4EC)
		return STATE_FAILURE;
	Real range = ai->m_goalRange;
	Coord3D position;
	const Coord3D *goal = &ai->m_goalPosition;
	position.x = goal->x;
	position.y = goal->y;
	position.z = goal->z;
	Bool close = reinterpret_cast<Gen_000E5A50 *>(owner)->bfmeDistanceSquared(
		reinterpret_cast<const BfmeVec3EJ *>(&position)) < range * range;
	if (float(ai->m_bfme534) == 0.0f && !close)
		return STATE_CONTINUE;
	reinterpret_cast<Thing *>(owner)->setPosition(&position);
	return STATE_SUCCESS;
}

StateReturnType GiantBirdAttackMoveToState::onEnter()
{
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	m_attackMachine->start();
	m_attackMachine->setState(0);
	m_commandSource = ai->getLastCommandSource();
	m_retryCount = 5;
	return GiantBirdNormalFlightState::onEnter();
}

StateReturnType GiantBirdAttackMoveToState::update()
{
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();
	Bool forceRetargetThisFrame = false;
	Bool shouldRepathThisFrame = false;

	if (!m_attackMachine->isInIdleState())
	{
		ai->setLocomotorGoalNone();
		owner->clearModelConditionBit(61);
		owner->clearModelConditionBit(156);
		m_attackMachine->updateStateMachine();
		if (!m_attackMachine)
			return STATE_CONTINUE;
		if (!m_attackMachine->isInIdleState())
			return STATE_CONTINUE;
		forceRetargetThisFrame = true;
		shouldRepathThisFrame = true;
		ai->m_lastCommandSource = m_commandSource;
	}

	if (m_attackMachine->isInIdleState())
	{
		Object *crate = ai->checkForCrateToPickup();
		if (crate)
		{
			m_attackMachine->setGoalObject(crate);
			m_attackMachine->setState(0x27);
			return STATE_CONTINUE;
		}
		ai->rva0026304D(TheGameLogic->getFrame());
		Object *target = ai->getNextMoodTarget(!forceRetargetThisFrame, false);
		if (target)
		{
			ai->rva00262AEA();
			m_attackMachine->setGoalObject(target);
			m_attackMachine->setState(10);
			ai->m_lastCommandSource = 2;
			ai->m_bfme3C7 = true;
			return STATE_CONTINUE;
		}
	}

	if (shouldRepathThisFrame)
		GiantBirdNormalFlightState::onEnter();
	return GiantBirdNormalFlightState::update();
}
