// cl: /DNDEBUG /MD
//
// ?getCurrentVictim@AIUpdateInterface@@QBEPAVObject@@XZ,
// retail 0x00268D71, 23 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:4231): INVALID_OBJECT_ID-guarded TheGameLogic->findObjectByID lookup.
// m_currentVictimID lives at +0x40.

typedef bool Bool;

#include "../../../Common/GameLogicObjectLookupView.h"

class Object;


extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

// ?getCurrentVictim@AIUpdateInterface@@QBEPAVObject@@XZ
Object *AIUpdateInterface::getCurrentVictim() const
{
	if (m_currentVictimID != INVALID_OBJECT_ID)
		return TheGameLogic->findObjectByID(m_currentVictimID);

	return 0;
}
