// cl: /DNDEBUG /MD
// ?Rva005BF28EIsAlly@@YA_NPBVGameInfo@@PBVGameSlot@@@Z @0x005BF28E 57B: GameInfo local-ally team check via getLocalSlotNum slot 13 (+0x34) and rowed getConstSlot; evidence retail virtual call + getConstSlot row + team at +0x1c.

typedef int Int;
typedef bool Bool;

#include "../../Include/GameNetwork/GameInfo.h"


Bool Rva005BF28EIsAlly(const GameInfo *gameInfo, const GameSlot *slot)
{
	const GameSlot *localSlot = gameInfo->getConstSlot(gameInfo->getLocalSlotNum());
	if (localSlot == 0)
		return true;
	if (slot == localSlot)
		return true;
	Int team = slot->getTeamNumber();
	if (team < 0)
		return false;
	return team == localSlot->getTeamNumber();
}
