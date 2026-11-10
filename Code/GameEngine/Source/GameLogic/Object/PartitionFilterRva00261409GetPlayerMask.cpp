// cl: /DNDEBUG /MD
//
// ?getPlayerMask@Rva00261409Filter@@UAEHXZ
// retail 0x002613E1, 40 bytes: slot 2 of the partition filter vftable
// 0x00C004D8 (pinned), the filter whose allow is the next function
// 0x00261409. Same class view as BannerCarrierUpdateReplenish.cpp: player
// +0x08, match flag +0x0C, relationship flags +0x10. The mask is the
// players with those relationships (plus bit 0) to the filter's player,
// inverted when the filter excludes them.

class Object;

#include "../../../Include/Common/Player.h"

#include "../../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;	// VA 0x00DFEEE8

#include "../../../Include/GameLogic/PartitionFilter.h"

#include "../../../Include/GameLogic/Rva00261409Filter.h"

int Rva00261409Filter::getPlayerMask()
{
	int mask = ThePlayerList->getPlayersWithRelationship(m_player->getPlayerIndex(), m_flags | 1, false);
	if (!m_match)
		mask = ~mask;
	return mask;
}
