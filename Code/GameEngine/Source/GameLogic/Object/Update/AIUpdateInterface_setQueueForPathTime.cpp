// cl: /DNDEBUG /MD
//
// ?setQueueForPathTime@AIUpdateInterface@@QAEXH@Z, retail 0x0026282A, 71 bytes.
// BFME1 donor AIUpdate.cpp setQueueForPathTime verbatim: frames greater than
// or equal UPDATE_SLEEP_NONE and getWakeFrame greater than frames with not
// m_isInUpdate at +0x3C2 then setWakeFrame with m_object at +0x08. Tail stores
// m_queueForPathFrame at +0x17C as frames plus TheGameLogic frame or zero.
// m_turretAI at +0x20C in the turret siblings bounds this AIUpdateInterface
// body. Callees already rowed: getWakeFrame 0x0044DF5B and setWakeFrame
// 0x0044DF71 via UpdateModuleSetWakeFrame. Sibling wakeUpNow 0x00262871.

class Object;

typedef int Int;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::setQueueForPathTime(Int frames)
{
	if (frames >= UPDATE_SLEEP_NONE && getWakeFrame() > (UpdateSleepTime)frames)
	{
		if (!m_field3C2)
			setWakeFrame(m_object, (UpdateSleepTime)frames);
	}
	m_field17C = frames ? TheGameLogic->getFrame() + frames : 0;
}

// ?setDesiredSpeed@AIUpdateInterface@@QAEXM@Z, retail 0x002628F9, 14 bytes.
// The out-of-line setter stores its float argument in m_desiredSpeed at +0x44
// (the constructor writes 999999.0f there, and AIUpdateXfer transfers it).
// The AI state units call this body instead of inlining it: AIStates.cpp,
// AIStatesBfmeOnExit.cpp, AIStatesDerivedOnExit_ComputeGoal.cpp,
// AIStatesSmallUpdates.cpp, AIAttackPursueTargetStateUpdateInternal.cpp and
// AIFollowWaypointPathStateOnEnter.cpp all reach it, and the last unit's
// onEnter call at 0x0034F146 is what names the accessor. Retail ICF-folded the
// 14 bytes with View::setHeightAboveGround, whose height member also sits at
// +0x44, so the shared row keeps the View name and this body is its
// fold-proof twin. Leaf with no callees.
void AIUpdateInterface::setDesiredSpeed(float speed)
{
	m_desiredSpeed = speed;
}
