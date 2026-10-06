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

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
private:
	unsigned char m_pad00[0x54];
	int m_playerIndex;
};

class PlayerList
{
public:
	int getPlayersWithRelationship(int srcPlayerIndex, unsigned int allowedRelationships, bool flag);
};

extern PlayerList *ThePlayerList;	// VA 0x00DFEEE8

class Rva000421C8
{
public:
	virtual bool allow(Object *obj) = 0;
private:
	int m_04;
};

class Rva00261409Filter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

int Rva00261409Filter::getPlayerMask()
{
	int mask = ThePlayerList->getPlayersWithRelationship(m_player->getPlayerIndex(), m_flags | 1, false);
	if (!m_match)
		mask = ~mask;
	return mask;
}
