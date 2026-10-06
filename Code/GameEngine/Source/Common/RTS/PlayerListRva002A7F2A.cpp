// cl: /DNDEBUG /MD /EHsc
//
// ?createClonedAllyFor@PlayerList@@QAEPAVPlayer@@PAX@Z @0x002A7F2A 49B
// Evidence: thiscall ret 4 over the BFME2 PlayerList layout (count +0x14,
// inline player pointer array +0x18, see PlayerList_getNthPlayer.cpp). Like
// the BFME1 reference PlayerList::newGame (reference/open-bfme-1/Code/
// GameEngine/Source/Common/RTS/PlayerList.cpp, "Player* p =
// m_players[m_playerCount++]; p->initFromDict(d);"), it takes the next free
// player slot, but BFME2 bounds it at 19 slots (cmp 0x13) and hands the
// argument to the unrowed EH-framed Player initializer 0x002B07A9 (pinned
// address-derived, it reads arg+0x5C), giving the slot back on failure.

typedef int Int;

class Player
{
public:
	bool rva002B07A9(void *data);
};

class PlayerList
{
public:
	Player *createClonedAllyFor(void *data);

private:
	unsigned char m_pad[0x14];
	Int m_playerCount; // +0x14
	Player *m_players[20]; // +0x18
};

Player *PlayerList::createClonedAllyFor(void *data)
{
	if (m_playerCount < 19)
	{
		Player *p = m_players[m_playerCount++];
		if (p->rva002B07A9(data))
			return p;
		m_playerCount--;
	}
	return 0;
}
