// ?onEnter@AIBurningDeathState@@UAE?AW4StateReturnType@@XZ
// partial score=0.97 date=2026-10-08
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

enum DisabledType { DISABLED_NATIVE_1 = 1 };
class Rva00346BC0 { public: unsigned int words[4]; };
extern unsigned g_Va00E01E08;
class Drawable { public: void rva00272BE7(); };
class Thing { public: Drawable *getDrawable() const; };
class Rva262FF8PtrChaseField { public: int get() const; };
template<int N> class BurningNativeSlots : public BurningNativeSlots<N-1> { public: virtual void gap(char (*)[N])=0; };
template<> class BurningNativeSlots<0> {};
class BurningAIView : public BurningNativeSlots<142> { public: virtual void slot142(int)=0; };

class Object
{
public:
	void *getAI() const { return m_ai; }
	const Coord3D *getPosition() const { return &m_position; }
	bool clearDisabled(DisabledType);
	void rva0028AE6D();
	void rva0028CDEB(const Rva00346BC0 &,bool);
	__forceinline void setBurningCondition() { if (!(m_conditionBytes150[0] & 1)) { m_condition150 |= 1; rva0028AE6D(); } }

private:
	unsigned char m_pad000[0x38];
	Coord3D m_position;
	unsigned char m_pad044[0x150-0x44];
	union { unsigned int m_condition150; unsigned char m_conditionBytes150[4]; };
	unsigned char m_pad154[0x258-0x154];
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
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
	Coord3D rva003469F5();

private:
	UnsignedInt m_deathFrame; // +0x4C
	Coord3D m_deathPosition; // +0x50
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

// Native35017B..35025B RET0 and the same state vtable's onEnter slot.
// Owner, AI, frame, initial position and condition word are native accesses;
// goal-picker and base-entry ABIs are independently used by update above.
// The unlabelled slot142 argument and condition word retain native identities.
StateReturnType AIBurningDeathState::onEnter()
{
    Object *obj = getMachineOwner();
    if (!obj || !obj->getAI())
        return STATE_FAILURE;
    m_deathFrame = TheGameLogic->getFrame() +
        ((Rva262FF8PtrChaseField *)obj->getAI())->get();
    m_deathPosition = *getMachineOwner()->getPosition();
    obj->clearDisabled(DISABLED_NATIVE_1);
    obj->setBurningCondition();
    obj->rva0028CDEB(*(const Rva00346BC0 *)&g_Va00E01E08, true);
    TheGameLogic->deselectObject(obj, 0xfffff, true);
    ((BurningAIView *)obj->getAI())->slot142(16);
    Drawable *drawable = ((Thing *)obj)->getDrawable();
    if (drawable)
        drawable->rva00272BE7();
    Coord3D goal = rva003469F5();
    m_goalPosition.x = goal.x;
    m_goalPosition.y = goal.y;
    return AIInternalMoveToState::onEnter();
}
