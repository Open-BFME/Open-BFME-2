// ?onEnter@AIWanderInPlaceState@@UAE?AW4StateReturnType@@XZ
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// AIWanderInPlaceState::onExit, retail 0x0034A364 (42 bytes): slot 5 of vtable
// 0x00C12AC8, whose slot-2 name getter returns AIWanderInPlaceState and whose
// slot 3 is the rowed AIWanderInPlaceState::xfer 0x003411BD. Zero Hour's
// AIStates.cpp onExit runs only the base onExit; BFME2 (target evidence) then
// restores the normal locomotor set through AIUpdateInterface vslot 142
// (+0x238, chooseLocomotorSet as in the ZH onEnter's LOCOMOTORSET_WANDER call
// at the same slot) when the owner (+0x14 of the machine +0x18) has an AI
// (+0x258). The base onExit is the pinned AIInternalMoveToState body.
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;

#define PATHFIND_CELL_SIZE 10
#define PATHFIND_CELL_SIZE_F 10.0f

static __forceinline Real fast_float_floor(Real f)
{
	return (Real)floor((double)f);
}
static __forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define AISTATES_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIStates.cpp"
// Retail passes AIStates.cpp's own line numbers.
#define GameLogicRandomValueAt(low, high, line) GetGameLogicRandomValue(low, high, AISTATES_FILE, line)

class LocomotorTemplate
{
public:
	Real getWanderAboutPointRadius() const { return m_wanderAboutPointRadius; }
private:
	unsigned char m_pad00[0xF8];
	Real m_wanderAboutPointRadius; // +0xF8
};
class Locomotor
{
public:
	Real getWanderAboutPointRadius() const { return m_template->getWanderAboutPointRadius(); }
private:
	unsigned char m_pad00[0x04];
	const LocomotorTemplate *m_template; // +0x04
};
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
enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_WANDER = 3
};
template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};
class AIUpdateInterface : public AIUpdateSlots<142>
{
public:
	virtual Bool chooseLocomotorSet(LocomotorSetType wst) = 0;
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
private:
	unsigned char m_pad004[0x1F0 - 0x04];
	Locomotor *m_curLocomotor; // +0x1F0
};
class ThingTemplate
{
public:
	Bool isKindOfCanBeRepulsed() const { return (m_kindOf[5] & 0x20) != 0; }
private:
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[8]; // +0x108
};
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	int getID() const { return m_id; }
	Real getVisionRange() const;
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x74 - 0x44];
	int m_id; // +0x74
	unsigned char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
};
class AI
{
public:
	Object *findClosestRepulsor(const Object *me, Real range);
};
extern AI *TheAI;
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
class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x4C - 0x2C];
};
class AIWanderInPlaceState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	Coord3D m_origin; // +0x4C
	Int m_waitFrames; // +0x58
	Int m_timer; // +0x5C
};

void AIWanderInPlaceState::onExit( StateExitType status )
{
	AIInternalMoveToState::onExit( status );
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai) {
		ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	}
}

StateReturnType AIWanderInPlaceState::onEnter()
{
	m_origin = *getMachineOwner()->getPosition();
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai)
		ai->chooseLocomotorSet(LOCOMOTORSET_WANDER);
	Int delta = 3;
	if (ai->getCurLocomotor())
		delta = REAL_TO_INT_FLOOR((ai->getCurLocomotor()->getWanderAboutPointRadius() / PATHFIND_CELL_SIZE_F) + 0.5f);
	Coord3D offset;
	offset.x = GameLogicRandomValueAt(-delta, delta, 10700) * PATHFIND_CELL_SIZE;
	offset.y = GameLogicRandomValueAt(-delta, delta, 10701) * PATHFIND_CELL_SIZE;
	m_goalPosition = m_origin;
	m_goalPosition.x += offset.x;
	m_goalPosition.y += offset.y;
	m_timer = 0;
	m_waitFrames = 10 + (getMachineOwner()->getID() & 0x7);
	StateReturnType ret = AIInternalMoveToState::onEnter();
	return ret;
}

StateReturnType AIWanderInPlaceState::update()
{
	StateReturnType status = AIInternalMoveToState::update();
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (!ai)
		return STATE_FAILURE;
	if (obj->getTemplate()->isKindOfCanBeRepulsed())
	{
		m_timer--;
		if (m_timer < 0)
		{
			m_timer = m_waitFrames;
			Object *enemy = TheAI->findClosestRepulsor(getMachineOwner(), obj->getVisionRange());
			if (enemy)
				return STATE_FAILURE;
		}
	}
	if (status != STATE_CONTINUE)
	{
		Int delta = 3;
		if (ai->getCurLocomotor())
			delta = REAL_TO_INT_FLOOR((ai->getCurLocomotor()->getWanderAboutPointRadius() / PATHFIND_CELL_SIZE_F) + 0.5f);
		Coord3D offset;
		offset.x = GameLogicRandomValueAt(-delta, delta, 10739) * PATHFIND_CELL_SIZE;
		offset.y = GameLogicRandomValueAt(-delta, delta, 10740) * PATHFIND_CELL_SIZE;
		m_goalPosition = m_origin;
		m_goalPosition.x += offset.x;
		m_goalPosition.y += offset.y;
		AIInternalMoveToState::onEnter();
		return STATE_CONTINUE;
	}
	return STATE_CONTINUE;
}
