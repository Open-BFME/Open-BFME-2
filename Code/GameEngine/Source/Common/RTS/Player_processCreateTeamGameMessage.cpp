// cl: /MD /GX-
// ?processCreateTeamGameMessage@Player@@QAEXHPBVGameMessage@@@Z @0x002ACA86 117B: Player GameMessage ObjectID fill.
// Evidence: prev PlayerRva002AC673 next PlayerRva002ACD09 same flags; +0x708 10-slot array
// matches Rva002AA191 m_entries; callees Clear 0x004D6C29 getArgument 0x0030F4EA
// findObjectByID 0x00049DC5 Find 0x002AA1BF Add 0x004D6C7C TheGameLogic; caller 0x00377BD7.
class Object;
#include "../GameLogicObjectLookupView.h"

union GameMessageArgumentType
{
	ObjectID m_objectID;
	int m_int;
};

#include "../../../Include/Common/MessageStream.h"

extern GameLogic *TheGameLogic;

class Rva004D6C29
{
public:
	void rva004D6C29();
};

class Rva004D6C7C
{
public:
	void rva004D6C7C(const Object *obj);
};

#include "../../../Include/GameClient/Rva002AA191.h"

#include "../../../Include/Common/Player.h"

void Player::processCreateTeamGameMessage(int index, const GameMessage *msg)
{
	if (index < 0 || index >= 10)
		return;
	Squad **slot = &m_squads[index];
	((Rva004D6C29 *)*slot)->rva004D6C29();
	unsigned char count = *(const unsigned char *)((const char *)msg + 0x18);
	if (count <= 0)
		return;
	int i = 0;
	unsigned int left = count;
	while (true) {
		const GameMessageArgumentType *gameMessageArgumentType = msg->getArgument(i);
		Object *obj = TheGameLogic->findObjectByID(gameMessageArgumentType->m_objectID);
		if (obj) {
			((Rva002AA191 *)this)->rva002AA1BF(obj);
			((Rva004D6C7C *)*slot)->rva004D6C7C(obj);
		}
		++i;
		--left;
		if (left == 0)
			break;
	}
}
