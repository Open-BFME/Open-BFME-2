// cl: /DNDEBUG /MD /EHsc
//
// ?createClonedAllyFor@PlayerList@@QAEPAVPlayer@@PAX@Z @0x002A7F2A 49B
// Evidence: thiscall ret 4 over the BFME2 PlayerList layout (count +0x14,
// inline player pointer array +0x18, see PlayerList_getNthPlayer.cpp). Like
// the BFME1 reference PlayerList::newGame (reference/open-bfme-1/Code/
// GameEngine/Source/Common/RTS/PlayerList.cpp, "Player* p =
// m_players[m_playerCount++]; p->initFromDict(d);"), it takes the next free
// player slot, but BFME2 bounds it at 19 slots (cmp 0x13) and hands the
// argument to Player::cloneFrom 0x002B07A9 (PlayerCloneFrom.cpp), giving the
// slot back on failure.

typedef int Int;

#include "../../../Include/Common/Player.h"

#include "../../../Include/Common/PlayerList.h"

Player *PlayerList::createClonedAllyFor(void *data)
{
	if (m_playerCount < 19)
	{
		Player *player = m_players[m_playerCount++];
		if (player->cloneFrom((Player *)data))
			return player;
		m_playerCount--;
	}
	return 0;
}
