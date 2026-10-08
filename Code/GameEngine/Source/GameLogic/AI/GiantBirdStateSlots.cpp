// cl: /DNDEBUG /MD /arch:SSE
//
// onExit overrides of the BFME 2 giant-bird flight states, each named by its
// vtable's slot-2 name getter (the state's own name literal):
//
//  - GiantBirdNormalFlightState::onExit, retail 0x00369217 (134 bytes):
//    slot 5 of 0x00C17300. The base State::onExit (the shared empty body,
//    pinned 0x0047A69C); then on the owner: model-condition bits 103 and 72
//    cleared (each notifying through the rowed Object::rva0028AE6D), the
//    pinned Object::rva0028ACEE with its own position (+0x38) and 1, object
//    status 0x5A and 0x5B cleared (rowed setStatus), and -1.0 stored at +0x2C
//    of the rowed Object::rva0028AC4E entry when there is one (as
//    AIFollowPathState::onExit does).
//  - GiantBirdAttackMoveToState::onExit, retail 0x0036964D (28 bytes): slot 5
//    of 0x00C17548. Sets its machine at +0x28 to state 0 (StateMachine slot
//    8), then the GiantBirdNormalFlightState::onExit above, which makes it
//    the base class (inferred).
//  - AIGiantBirdSwoopState::onExit, retail 0x003692ED (141 bytes): slot 5 of
//    0x00C17360. The base State::onExit; with an owner: condition bits 61,
//    103 and 72 cleared, AI slot 142 with 0 and the rowed
//    AIUpdateInterface::setCurrentVictim(NULL) when there is an AI, then
//    Object::rva0028ACEE with its position and 1.
//
// The meaning of the condition and status bits is not recovered.

typedef bool Bool;
typedef float Real;
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
typedef unsigned int StateID;
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_5A = 0x5A,
	OBJECT_STATUS_BFME_5B = 0x5B
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class BfmeVec3EJ;
class Gen_000E5A50
{
public:
	float bfmeDistanceSquared(const BfmeVec3EJ *point) const;
};
class Rva00368C7A
{
public:
	void rva00368C7A(float amount, const Coord3D *position, bool argument);
};
class Thing
{
public:
	void setPosition(const Coord3D *position);
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

struct Rva0028AC4EEntry
{
	unsigned char m_pad00[0x2C];
	Real m_bfme2C; // +0x2C
};

template <int N> class GiantBirdAISlots : public GiantBirdAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class GiantBirdAISlots<0>
{
};

class Object;

class AIUpdateInterface : public GiantBirdAISlots<142>
{
public:
	virtual void rva00369359Slot142(int value) = 0;
	void setCurrentVictim(const Object *victim);
	unsigned char m_unknown04[0x4C0 - 4];
	ObjectID m_id4C0;
	unsigned char m_unknown4C4[0x4EC - 0x4C4];
	unsigned char m_continue4EC;
	unsigned char m_unknown4ED[0x534 - 0x4ED];
	unsigned char m_pending534;
	unsigned char m_unknown535[3];
	float m_goalRange538;
	unsigned char m_unknown53C[8];
	Coord3D m_goalPosition544;
	unsigned char m_unknown550[4];
	ObjectID m_id554;
	unsigned char m_flag558;
	unsigned char m_unknown559[3];
	int m_value55C;
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	__forceinline bool isDead() const { return (m_status438 & 1) != 0; }
	const Coord3D *getPosition() const { return &m_position; }
	void setStatus(ObjectStatusTypes status, Bool set);
	void rva0028ACEE(const Coord3D *pos, int value);
	const Rva0028AC4EEntry *rva0028AC4E() const;
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
	unsigned char m_status438;
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07();
	virtual StateReturnType setState(StateID newStateID);
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void setGoalObject(const Object *object);
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad04[0x14 - 0x04];
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

class GiantBirdNormalFlightState : public State
{
public:
	virtual void onExit(StateExitType status);
};

void GiantBirdNormalFlightState::onExit(StateExitType status)
{
	State::onExit(status);
	Object *owner = getMachineOwner();
	owner->clearModelConditionBit(103);
	owner->clearModelConditionBit(72);
	owner->rva0028ACEE(owner->getPosition(), 1);
	owner->setStatus(OBJECT_STATUS_BFME_5A, false);
	owner->setStatus(OBJECT_STATUS_BFME_5B, false);
	if (owner->rva0028AC4E())
		const_cast<Rva0028AC4EEntry *>(owner->rva0028AC4E())->m_bfme2C = -1.0f;
}

class GiantBirdAttackMoveToState : public GiantBirdNormalFlightState
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x28 - 0x1C];
	StateMachine *m_attackMachine; // +0x28
};

void GiantBirdAttackMoveToState::onExit(StateExitType status)
{
	m_attackMachine->setState(0);
	GiantBirdNormalFlightState::onExit(status);
}

class AIGiantBirdSwoopState : public State
{
public:
	virtual void onExit(StateExitType status);
};

void AIGiantBirdSwoopState::onExit(StateExitType status)
{
	State::onExit(status);
	Object *owner = getMachineOwner();
	if (!owner)
		return;
	owner->clearModelConditionBit(61);
	owner->clearModelConditionBit(103);
	owner->clearModelConditionBit(72);
	AIUpdateInterface *ai = owner->getAI();
	if (ai)
	{
		ai->rva00369359Slot142(0);
		ai->setCurrentVictim(0);
	}
	owner->rva0028ACEE(owner->getPosition(), 1);
}

// Native table 0xC17418 slot 2 returns "AIGiantBirdFollowThruState";
// slot 6 is 0x369EA3..0x369FDF (316 bytes). BFME 1 donor ba7ddda7e8f2,
// AIGiantBirdFollowThruStateUpdate.cpp, supplies the follow-through control
// flow. All offsets below are independently read from BFME 2's body; the
// AI receiver's original helper name and the two object ID roles remain
// unresolved. The distance and routing adapters retain their rowed names.
class AIGiantBirdFollowThruState : public State
{
public:
	virtual StateReturnType update();
	virtual void onExit(StateExitType status);
private:
	unsigned char m_unknown1C[0x24 - 0x1C];
	int m_counter24;
};

StateReturnType AIGiantBirdFollowThruState::update()
{
	Object *object = getMachineOwner();
	if (object->isDead())
		return STATE_FAILURE;
	object->clearModelConditionBit(155);
	if (++m_counter24 > 40)
		return STATE_FAILURE;
	AIUpdateInterface *ai = object->getAI();
	if (!ai)
		return STATE_FAILURE;
	reinterpret_cast<Rva00368C7A *>(ai)->rva00368C7A(5.0f, 0, 1);
	if (!ai->m_continue4EC)
		return STATE_FAILURE;
	float goalRange = ai->m_goalRange538;
	Coord3D goal;
	const Coord3D *goalPosition = &ai->m_goalPosition544;
	goal.x = goalPosition->x;
	goal.y = goalPosition->y;
	goal.z = goalPosition->z;
	unsigned char withinGoalRange = static_cast<unsigned char>(
		reinterpret_cast<Gen_000E5A50 *>(object)->bfmeDistanceSquared(
			reinterpret_cast<const BfmeVec3EJ *>(&goal)) < goalRange * goalRange);
	unsigned char pending = ai->m_pending534;
	if (pending == 0.0f && !withinGoalRange)
		return STATE_CONTINUE;
	reinterpret_cast<Thing *>(object)->setPosition(&goal);
	GameLogic *logic = TheGameLogic;
	Object *target = logic->findObjectByID(ai->m_id4C0);
	if (target && !target->isDead())
		return STATE_FAILURE;
	Object *otherTarget = logic->findObjectByID(ai->m_id554);
	m_machine->setGoalObject(0);
	if (!otherTarget || otherTarget->isDead())
		return STATE_SUCCESS;
	return STATE_FAILURE;
}

// Slot 5 of the same native table, 0x369418..0x3694B2 RET4 (154 bytes).
// BFME 1's AIGiantBirdFollowThruStateOnExit.cpp confirms the exit purpose;
// BFME 2 instead uses its rowed object goal refresh and resets AI +558/+55C.
void AIGiantBirdFollowThruState::onExit(StateExitType status)
{
	State::onExit(status);
	Object *object = getMachineOwner();
	object->clearModelConditionBit(61);
	object->clearModelConditionBit(103);
	object->clearModelConditionBit(72);
	object->clearModelConditionBit(155);
	object->rva0028ACEE(object->getPosition(), 1);
	AIUpdateInterface *ai = object->getAI();
	if (ai)
	{
		ai->m_flag558 = 0;
		ai->m_value55C = 2;
	}
}
