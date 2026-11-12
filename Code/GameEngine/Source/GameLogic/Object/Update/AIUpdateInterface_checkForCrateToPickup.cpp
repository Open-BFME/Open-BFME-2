// cl: /DNDEBUG /MD
//
// ?checkForCrateToPickup@AIUpdateInterface@@QAEPAVObject@@XZ
// retail 0x00268B79, 92 bytes (Ghidra FUN_00668b79), pinned under this name.
//
// Donor: GeneralsMD AIUpdate.cpp checkForCrateToPickup. In BFME 2 the crate
// ID (+0x238) is cleared before the lookup reads it, so retail asks
// findObjectByID for ID 0 (the earlier "dead loop" verdict); the scan is
// otherwise Zero Hour's: walk the crate's behavior modules (+0x244), take
// each one's collide interface (behavior interface at +0x0C, slot 1) and
// return the crate if it would like to collide with our object (slot 1).

#include "../../../Common/GameLogicObjectLookupView.h"

class Object;

#include "../../../../Include/Common/CollideModuleInterface.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../object.h"

extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

Object *AIUpdateInterface::checkForCrateToPickup()
{
	if (m_crateCreated != INVALID_OBJECT_ID)
	{
		m_crateCreated = INVALID_OBJECT_ID;
		Object *crate = TheGameLogic->findObjectByID(m_crateCreated);
		if (crate)
		{
			for (BehaviorModule **i = crate->getBehaviorModules(); *i; ++i)
			{
				CollideModuleInterface *collide = (*i)->getCollide();
				if (!collide)
					continue;
				if (collide->wouldLikeToCollideWith(getObject()))
					return crate;
			}
		}
	}
	return 0;
}
