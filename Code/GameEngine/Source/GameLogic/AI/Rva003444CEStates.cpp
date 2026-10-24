// cl: /Ireference/shims/bfme2_statemachine /DNDEBUG /MD /EHsc
// ??0BackAwayAndCowerStateMachine@@QAE@PAVObject@@0I@Z @0x003444CE 174B.
// StateMachine-family ctor (thiscall): base-constructs the rowed
// StateMachine base from (owner, name, 0), installs its vftable 0x00811FE8
// (shared with the destructor 0x003402D0, whose unit names the class from
// the slot 2 getter 0x003402DB), runs the rowed
// StateMachine::setGoalObject (0x004D750F) hook on the second object param, then two
// new-expression state blocks into the dead name slot with post-call eax
// feeding rowed defineState directly (B952-family shape). Zero CSEs into
// ebx; this stays in esi; 0x270F rides edi. The third argument is the
// machine's name key, forwarded unchanged into the base's unsigned name slot
// and never destroyed (the only caller, AIBackAwayAndCowerState::onEnter
// 0x00347C38, pushes the constant 0xD944B508).

//
// The destructor 0x003402D0 (11B: own vftable, tail call to ~StateMachine
// 0x004D759C) and its deleting destructor 0x0034457C live here too, so this
// unit is the only one that emits the class's vftable, over the canonical
// 16-slot StateMachine view.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

#include "StateMachineView.h"


// Rowed 0x0034301B as AIBackAwayState::AIBackAwayState (AIStateRva0034005DCtor.cpp).
class AIBackAwayState
{
public:
	AIBackAwayState(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x58 - 4];
};

class Rva0033F7C8
{
public:
	Rva0033F7C8(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x20 - 4];
};

class BackAwayAndCowerStateMachine : public StateMachine
{
public:
	BackAwayAndCowerStateMachine(Object *owner, Object *arg, unsigned int nameKey);
	virtual ~BackAwayAndCowerStateMachine();
};

BackAwayAndCowerStateMachine::BackAwayAndCowerStateMachine(Object *owner, Object *goal, unsigned int nameKey)
	: StateMachine(owner, nameKey, false)
{
	((StateMachine *)this)->StateMachine::setGoalObject(goal);
	AIBackAwayState *aIBackAwayState = new AIBackAwayState((StateMachine *)this);
	((StateMachine *)this)->defineState(0, (State *)aIBackAwayState, 1, 0x270F, (const StateConditionInfo *)0);
	Rva0033F7C8 *s1 = new Rva0033F7C8((StateMachine *)this);
	((StateMachine *)this)->defineState(1, (State *)s1, 0x270E, 0x270F, (const StateConditionInfo *)0);
}

BackAwayAndCowerStateMachine::~BackAwayAndCowerStateMachine()
{
}
