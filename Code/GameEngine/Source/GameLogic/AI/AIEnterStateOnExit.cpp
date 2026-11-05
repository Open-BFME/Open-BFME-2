// cl: /O1 /DNDEBUG /MD
//
// AIEnterState::onExit, retail 0x003510A5 (100 bytes): slot 5 of vtable
// 0x00C12E90, whose slot-2 name getter 0x00342ED1 returns AIEnterState; the
// body is the Zero Hour AIStates.cpp AIEnterState::onExit (base
// AIInternalMoveToState::onExit 0x003473A4, ignoreObstacle(NULL), locomotor
// allow-invalid-position off (bit 1 of Locomotor+0x44), then the contain of
// m_entryToClear (+0x4C) is told WANTS_NEITHER through Object+0x250 slot 17).
// Rva00351109::onExit, retail 0x00351109 (129 bytes): slot 5 of vtable
// 0x00C12F40 (unrowed ctor 0x00342F15); it passes the object found from +0x50
// to state machine virtual slot 14, then runs the same exit body inline, so the
// class derives from AIEnterState. Its name getter literal is not used as an
// identity; the placeholder is named by address.
#include "../../Common/GameLogicObjectLookupView.h"
enum ObjectEnterExitType
{
	WANTS_TO_ENTER = 0,
	WANTS_TO_EXIT = 1,
	WANTS_NEITHER = 2
};
class Object;
#include "../../../Include/GameLogic/Module/ContainModule.h"
#include "../../../Include/GameLogic/LocomotorClass.h"
#include "../../../Include/GameLogic/Module/AIUpdate.h"
#include "../Object/object.h"
extern GameLogic *TheGameLogic;
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"
class AIInternalMoveToState : public State
{
public:
	virtual void onExit(StateExitType status);
};
class AIEnterState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
protected:
	void exitEnterState(StateExitType status);
	unsigned char m_pad20[0x4C - 0x20];
	ObjectID m_entryToClear; // +0x4C
};
class Rva00351109 : public AIEnterState
{
public:
	virtual void onExit(StateExitType status);
private:
	ObjectID m_50; // +0x50
};
// ?AIEnterState::exitEnterState absent-from-retail
// (force-inlined into both onExit bodies; no out-of-line retail copy)
__forceinline void AIEnterState::exitEnterState(StateExitType status)
{
	Object *obj = getMachineOwner();
	AIInternalMoveToState::onExit(status);

	// tell the pathfinder to stop ignoring the object
	AIUpdateInterface *ai = obj->getAI();
	if (ai)
	{
		ai->ignoreObstacle(0);
		if (ai->getCurLocomotor())
		{
			ai->getCurLocomotor()->setAllowInvalidPosition(false);
		}
	}

	// use this, rather than getMachineGoalObject, in case the goal
	// is killed while we were waiting...
	if (m_entryToClear != INVALID_OBJECT_ID)
	{
		Object *goal = TheGameLogic->findObjectByID(m_entryToClear);
		if (goal)
		{
			ContainModuleInterface *contain = goal->getContain();
			if (contain)
			{
				contain->onObjectWantsToEnterOrExit(obj, WANTS_NEITHER);
			}
		}
	}
}
void AIEnterState::onExit(StateExitType status)
{
	exitEnterState(status);
}
void Rva00351109::onExit(StateExitType status)
{
	Object *target = TheGameLogic->findObjectByID(m_50);
	if (target)
		getMachine()->setGoalObject(target);
	exitEnterState(status);
}
