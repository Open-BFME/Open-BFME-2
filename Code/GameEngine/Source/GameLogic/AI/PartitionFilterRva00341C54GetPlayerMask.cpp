// cl: /DNDEBUG /MD
//
// ?getPlayerMask@Rva00341C54Filter@@UAEHXZ
// retail 0x00341C30, 36 bytes: slot 2 of the AIStates partition filter
// vftable 0x00C122F0 (slot 1 is its allow 0x00341C54). The filter keeps an
// Object at +0x08: no controlling player gives -1 (every player), otherwise
// the players with relationship 4 to that player, the shape of the rowed
// Rva00261409Filter::getPlayerMask with an object instead of a player.
class Player
{
public:
	unsigned char m_pad00[0x54];
	int m_playerIndex; // +0x54
};
class Object
{
public:
	Player *getControllingPlayer() const;
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
class Rva00341C54Filter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
private:
	Object *m_obj; // +0x08
};
int Rva00341C54Filter::getPlayerMask()
{
	Player *player = m_obj->getControllingPlayer();
	if (!player)
		return -1;
	int index = player->m_playerIndex;
	return ThePlayerList->getPlayersWithRelationship(index, 4, false);
}
