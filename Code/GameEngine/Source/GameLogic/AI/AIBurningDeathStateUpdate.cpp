// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// AIBurningDeathState::update, retail 0x0035025B (111B), slot 6 of the state
// vtable whose slot 4 is the sibling onEnter 0x0035017B.
//
// Target facts: fail without an owner or one without an AI (Object +0x258);
// once the death frame (+0x4C, set by onEnter from TheGameLogic's frame) is
// reached call Object 0x00298893 (rowed) and succeed; otherwise run the
// pinned base AIInternalMoveToState::update (0x00347460) and, when that stops
// continuing, take a new goal from 0x003469F5 into +0x20/+0x24 and re-enter
// the base move (pinned AIInternalMoveToState::onEnter, 0x0034C146).
// 0x003469F5 has exactly two callers, this update and the onEnter above, so it
// is placed on AIBurningDeathState under an address-derived name.
//
// Lead facts: the class and method names come from the WorldBuilder lead
// (AIStates.cpp); StateReturnType values follow Zero Hour (CONTINUE 0,
// SUCCESS -1, FAILURE -2). Structural inference: +0x20/+0x24 are the base
// move's goal x/y.

typedef unsigned int UnsignedInt;

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

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"

class BfmeSubBGB
{
public:
	bool rva00298893();
};

class Object
{
public:
	void *getAI() const { return m_ai; }

private:
	unsigned char m_pad000[0x258];
	void *m_ai; // +0x258
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }

private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

extern GameLogic *TheGameLogic;

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
	virtual StateReturnType update();

protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x4C - 0x2C];
};

class AIBurningDeathState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
	Coord3D rva003469F5();

private:
	UnsignedInt m_deathFrame; // +0x4C
};

StateReturnType AIBurningDeathState::update()
{
	Object *obj = getMachineOwner();
	if (obj == 0)
		return STATE_FAILURE;
	if (obj->getAI() == 0)
		return STATE_FAILURE;
	if (m_deathFrame <= TheGameLogic->getFrame())
	{
		((BfmeSubBGB *)obj)->rva00298893();
		return STATE_SUCCESS;
	}
	if (AIInternalMoveToState::update())
	{
		Coord3D goal = rva003469F5();
		m_goalPosition.x = goal.x;
		m_goalPosition.y = goal.y;
		AIInternalMoveToState::onEnter();
	}
	return STATE_CONTINUE;
}
