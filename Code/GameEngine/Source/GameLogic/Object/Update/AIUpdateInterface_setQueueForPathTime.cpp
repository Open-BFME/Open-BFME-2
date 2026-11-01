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
