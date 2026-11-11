// cl: /MD
// ?rva0050E8D6@Rva0050E8D6@@QAEXXZ @0x0050E8D6 124B
// Ally collector: seeds local player from ThePlayerList+0x10 then appends
// relationship==2 players via rowed getNthPlayer 0x002A7A29 plus bfmeAskRV
// 0x002AA231 plus getRelationship 0x002AC3E0; array stride 8 at +0x24 max 7.
#include "../../Include/Common/BfmeMemberRV.h"

enum Relationship
{
	REL_ENEMY = 0,
	REL_NEUTRAL = 1,
	REL_ALLY = 2
};

class Player;

#include "../../Include/Common/PlayerList.h"

class Player : public BfmeMemberRV
{
public:
	Relationship getRelationship(const Player *other) const;
};

extern PlayerList *ThePlayerList;

struct Rva0050E8D6Entry
{
	Player *m_player;
	int m_unk04;
};

class Rva0050E8D6
{
public:
	void rva0050E8D6();
	char m_pad[0x20];
	int m_count20;
	Rva0050E8D6Entry m_list24[7];
};

void Rva0050E8D6::rva0050E8D6()
{
	Player *local = ThePlayerList->m_local;
	Rva0050E8D6Entry &slot0 = m_list24[m_count20];
	m_count20++;
	slot0.m_player = local;
	int n = ThePlayerList->m_playerCount;
	int i = 0;
	if (n <= 0)
		return;
	for (; i < n; ++i)
	{
		Player *player = ThePlayerList->getNthPlayer(i);
		if (player == local)
			continue;
		if (!player->bfmeAskRV())
			continue;
		if (local->getRelationship(player) != REL_ALLY)
			continue;
		Rva0050E8D6Entry &slot = m_list24[m_count20];
		m_count20++;
		slot.m_player = player;
		if (m_count20 >= 7)
			break;
	}
}
