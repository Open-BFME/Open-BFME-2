// ?followToNextPointNow@GiantBirdFollowPathState@@QAE_NXZ
// partial score=0.98 date=2026-10-08
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
	STATE_CONTINUE = 0
};
typedef unsigned int StateID;
enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_5A = 0x5A,
	OBJECT_STATUS_BFME_5B = 0x5B
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

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

class Rva00346FA5
{
public:
	void *rva00346FA5(int index) const;
};

class Rva00368C7A
{
public:
	void rva003681F2(const Coord3D *position, const unsigned char *mask, int nextPoint, int lastPoint);
};

class TerrainLogic : public GiantBirdAISlots<6>
{
public:
	virtual Real getGroundHeight(Real x, Real y, int unused);
};
extern TerrainLogic *TheTerrainLogic;
extern unsigned char g_00E01EC0[4];

class AIUpdateInterface : public GiantBirdAISlots<142>
{
public:
	virtual void rva00369359Slot142(int value) = 0;
	void setCurrentVictim(const Object *victim);
	Rva00346FA5 *getPathMachine() const { return m_pathMachine; }
	Bool hasLocomotor() const { return m_locomotor != 0; }
	Bool loopsPath() const { return m_loopPath; }
	Real getPathHeight() const { return m_pathHeight; }
	void setLookAhead(Bool value)
	{
		if (value) m_pathFlags |= 0x80;
		else m_pathFlags &= ~0x80;
	}
private:
	unsigned char m_pad04[0x30 - 4];
	Rva00346FA5 *m_pathMachine; // +0x30, native calls to 0x00346FA5
	unsigned char m_pad34[0x1F0 - 0x34];
	void *m_locomotor; // +0x1F0
	unsigned char m_pad1F4[0x4B8 - 0x1F4];
	unsigned char m_pathFlags; // +0x4B8, observed bit 7
	unsigned char m_pad4B9[0x540 - 0x4B9];
	Real m_pathHeight; // +0x540
	unsigned char m_pad544[0x550 - 0x544];
	Bool m_loopPath; // +0x550
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
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
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07();
	virtual StateReturnType setState(StateID newStateID);
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

// WorldBuilder supplies the flight-path role and method name. Retail proves
// the owner/machine/locomotor access chain, index +0x58, loop byte +0x550,
// and the terrain-adjusted current and look-ahead points. Routing helper
// and mask retain their established address names.
class GiantBirdFollowPathState : public State
{
public:
	Bool followToNextPointNow();
private:
	unsigned char m_pad1C[0x58 - 0x1C];
	int m_pointIndex; // +0x58
};

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
	const Coord3D *next = (const Coord3D *)ai->getPathMachine()->rva00346FA5(m_pointIndex);
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
	((Rva00368C7A *)ai)->rva003681F2(&position, g_00E01EC0, (int)next, next == 0);
	return true;
}
