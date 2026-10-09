// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// ?Rva0043B278Do@@YGXW4ObjectID@@H@Z @0x0043B278 44B: object-by-id forward, a sibling of Rva00210E5B
// (Rva00210E5B.cpp) with the object found through TheGameLogic (rowed findObjectByID 0x00449DC5) and
// the entry reached through the rowed 0x009508E2 (ledger spelling BuildListInfo::getDesiredGatherers,
// returns the entry in eax); the second stack argument is forwarded to the pinned 0x00271C68 on it.
// Target evidence: retail body read byte for byte; the operation and argument meaning remain unresolved.

#include "../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class BuildListInfo
{
public:
	int getDesiredGatherers();
};

class Rva00271C68
{
public:
	void rva00271C68(int value);
};

void __stdcall Rva0043B278Do(ObjectID id, int value)
{
	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj)
	{
		int entry = ((BuildListInfo *)obj)->getDesiredGatherers();
		if (entry)
			((Rva00271C68 *)entry)->rva00271C68(value);
	}
}
