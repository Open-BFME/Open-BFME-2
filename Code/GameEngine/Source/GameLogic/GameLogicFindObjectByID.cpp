// cl: /DNDEBUG /MD
//
// GameLogic::findObjectByID, retail 0x00049DC5, 37 bytes.
// Dedicated TU. Null ObjectID returns null; otherwise hashtable find at
// this+0xB4 and the Object* lives at the node +8.

#include "../Common/GameLogicObjectLookupView.h"

inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
Object * (GameLogic::*_bfmeInlineAnchor_GameLogicFindObjectByID_0)(ObjectID id) = &GameLogic::findObjectByID;
