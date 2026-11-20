// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// AIEnterState::onEnter, retail 0x0034FB77 (309 bytes).
//
// Identity: the existing pin. Donor: Zero Hour AIStates.cpp
// AIEnterState::onEnter (clear the entry to clear, fail without a goal or when
// the action manager refuses entry, take the goal position, tell the goal's
// contain we want to enter and remember it, ignore the goal as an obstacle,
// allow invalid locomotor positions, stop adjusting the destination, then
// AIInternalMoveToState::onEnter). BFME2 target facts: an entry timeout frame
// at +0x50 (TheGlobalData +0x1234 plus the current frame); the goal position
// comes from the contain's slot 0x158 when the goal has a contain, adjusted by
// the pathfinder (0x002FCFCF) for kind-of bit 191; BFME's canEnterObject
// takes the command source from AI slot 0x23C plus three zero arguments;
// setAdjustsDestination(false) writes the CritterDesync log line first.
// Layout as in AIEnterStateOnExit.cpp.

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/Common/ScalarTypes.h"




#include "../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"




enum CanEnterType
{
	CHECK_CAPACITY = 0
};

enum ObjectEnterExitType
{
	WANTS_TO_ENTER = 0
};

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
#pragma push_macro("_CRTIMP")
#undef _CRTIMP
#define _CRTIMP
#include <stdio.h>
#pragma pop_macro("_CRTIMP")

static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		FILE *log = (FILE *)theLogicRandomLogFile;
		if (log != 0)
			fprintf(log, text);
	}
}



#include "../../../Include/GameLogic/Module/ContainModule.h"

#include "../../../Include/GameLogic/LocomotorClass.h"

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../Include/Common/ThingTemplate.h"

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() { return m_ai; }
private:
	char m_pad000[4];
	const ThingTemplate *m_template;
	char m_pad008[0x38 - 0x08];
	Coord3D m_position;
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;
	char m_pad078[0x250 - 0x78];
	ContainModuleInterface *m_contain; // +0x250
	char m_pad254[4];
	AIUpdateInterface *m_ai; // +0x258
};

#include "../../../Include/GameLogic/AIPathfind.h"

#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;

class BFMEActionManager
{
public:
	Bool canEnterObject(const Object *obj, const Object *objectToEnter,
		CommandSourceType commandSource, CanEnterType mode, Bool a, Bool *b);
};
class ActionManager;
extern ActionManager *TheActionManager;

#include "../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData

extern GameLogic *TheGameLogic;

#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"


#include "../../../Include/GameLogic/AIInternalMoveToState.h"
#include "../../../Include/GameLogic/LocomotorSet.h"

class AIEnterState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:

	ObjectID m_entryToClear; // +0x4C
	UnsignedInt m_entryTimeoutFrame; // +0x50
};

enum
{
	KINDOF_BIT_191 = 191
};

StateReturnType AIEnterState::onEnter()
{
	m_entryToClear = INVALID_OBJECT_ID;
	m_entryTimeoutFrame = TheGlobalData->m_waitToForceMemberToEnterDelay + TheGameLogic->getFrame();

	Object *obj = getMachineOwner();
	Object *goal = getMachineGoalObject();
	if (goal)
	{
		if (!((BFMEActionManager *)TheActionManager)->canEnterObject(obj, goal, obj->getAI()->vslot143(),
				CHECK_CAPACITY, false, 0))
			return STATE_FAILURE;

		ContainModuleInterface *contain = goal->getContain();
		if (contain)
		{
			m_goalPosition = *contain->slot86();
			if ((goal->getTemplate()->m_kindof[KINDOF_BIT_191 >> 5] & (1U << (KINDOF_BIT_191 & 0x1f))))
				TheAI->pathfinder()->AdjustDestination(obj, obj->getAI()->m_locomotorSet,
					&m_goalPosition, 0);
			contain->onObjectWantsToEnterOrExit(obj, WANTS_TO_ENTER);
			m_entryToClear = goal->getID();
		}
		else
		{
			m_goalPosition = *goal->getPosition();
		}
	}
	else
	{
		return STATE_FAILURE;
	}

	// tell the pathfinder to ignore the enterable object
	AIUpdateInterface *ai = obj->getAI();
	ai->ignoreObstacle(getMachineGoalObject());
	if (ai->getCurLocomotor())
		ai->getCurLocomotor()->setAllowInvalidPosition(true);

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 57");
	m_adjustDestinations = false;
	return AIInternalMoveToState::onEnter();
}
