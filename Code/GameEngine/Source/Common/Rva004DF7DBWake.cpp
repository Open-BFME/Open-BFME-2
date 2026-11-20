// cl: /MD
// ?rva004DF7DB@Rva004DF7DB@@QAEXW4UpdateSleepTime@@@Z, RVA 0x004DF7DB, 64 bytes.
// UpdateModule wake helper: if Object at +0x8 has status 0 return else
// setWakeFrame with FOREVER for INVALID/FOREVER else arg minus GameLogic frame.
// Evidence: rowed testStatus 0x0004E536 plus rowed setWakeFrame 0x0044DF71
// plus TheGameLogic 0x009FE78C plus UPDATE_SLEEP_FOREVER 0x3fffffff.


enum ObjectStatusTypes
{
	OBJECT_STATUS_0 = 0
};

#include "../../../../reference/open-bfme-1/game/GameEngine/Include/GameLogic/Module/UpdateSleepTime.h"






#include "../GameLogic/Object/object.h"

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

#include "../../Include/GameLogic/Module/UpdateModule.h"
class Rva004DF7DB : public UpdateModule
{
public:
	void rva004DF7DB(UpdateSleepTime t);
private:
};

void Rva004DF7DB::rva004DF7DB(UpdateSleepTime t)
{
	Object *obj = getObject();
	if (obj->testStatus((ObjectStatusTypes)0))
		return;
	UpdateSleepTime wake = t;
	if (wake == UPDATE_SLEEP_INVALID || wake == UPDATE_SLEEP_FOREVER)
		wake = UPDATE_SLEEP_FOREVER;
	else
		wake = (UpdateSleepTime)(wake - TheGameLogic->getFrame());
	setWakeFrame(obj, wake);
}
