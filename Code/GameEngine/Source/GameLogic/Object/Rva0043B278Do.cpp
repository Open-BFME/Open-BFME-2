// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// ?rva0043B278@DOTManager@@QAEXW4ObjectID@@H@Z @0x0043B278 44B: object-by-id forward, a sibling of Rva00210E5B
// (Rva00210E5B.cpp) with the object found through TheGameLogic (rowed findObjectByID 0x00449DC5) and
// the entry reached through the rowed 0x009508E2 (ledger spelling BuildListInfo::getDesiredGatherers,
// returns the entry in eax); the second stack argument is forwarded to the pinned 0x00271C68 on it.
// Target evidence: retail body read byte for byte; the operation and argument meaning remain unresolved.
// Retail's only call (0x43B8FD) is in DOTManager::rva0043B8C0 0x0043B8C0 on its own this, passing the
// record map's ObjectID key: a DOTManager member whose body does not read this (ret 8, as stdcall).

#include "../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class BuildListInfo
{
public:
	int getDesiredGatherers();
};

#include "../../../Include/Common/Rva00271C68.h"

#include "../../../Include/GameLogic/DOTManager.h"

void DOTManager::rva0043B278(ObjectID id, int value)
{
	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj)
	{
		int entry = ((BuildListInfo *)obj)->getDesiredGatherers();
		if (entry)
			((Rva00271C68 *)entry)->rva00271C68(value);
	}
}
