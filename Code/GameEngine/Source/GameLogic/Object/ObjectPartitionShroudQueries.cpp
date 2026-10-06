// cl: /O1 /DNDEBUG /MD
// ?PartitionGetPlayerIndex@Object@@UBEHXZ, retail 0x0028E7F8 (82 bytes).
// Its vtable neighbour Object::ShroudHideIfFogged (0x0028E775) is declared
// here for the class shape; its body is banked, not yet byte-exact.
// Identity (target): WorldBuilder's debug Object.cpp names both
// (Object::PartitionGetPlayerIndex: Object::getControllingPlayer, a kind-of
// test and two Team queries; Object::ShroudHideIfFogged:
// PlayerList::getNthPlayer, Player::getRelationship, kind-of tests and
// ShroudManager::Data::EverSeenByPlayer), and retail's only references are
// adjacent slots of Object's secondary vtables (0x007FC2D4, 0x007FC2EC).
// Layout (target): the partition query runs on the base at Object+0x6C and
// the shroud query on the base at Object+0x64; the template is Object+0x04
// (kind-of bits from +0x108), the team Object+0x304, the private status
// Object+0x438 (bit 0x02 the undetected defector, as fireCurrentWeapon
// clears it) and the shroud data Object+0x4C4. Kind indices are read off
// the tested bits (2, 55, 180, 213); their BFME 2 names are not recovered.
enum KindOfType
{
	KINDOF_2 = 2,
	KINDOF_55 = 55,
	KINDOF_180 = 180,
	KINDOF_213 = 213
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum ObjectPrivateStatusBits
{
	UNDETECTED_DEFECTOR = 0x02
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(KindOfType t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
};

class Team
{
public:
	bool rva0039F0D2();
	bool rva0039F824();
};

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
	Relationship getRelationship(const Team *that) const;

private:
	unsigned char m_pad00[0x54];
	int m_playerIndex; // +0x54
};

class PlayerList
{
public:
	Player *getNthPlayer(int index);
};

extern PlayerList *ThePlayerList;

class Rva008F7B00
{
public:
	char get(int playerIndex);
};

class ObjectThingBase
{
public:
	virtual ~ObjectThingBase();

protected:
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x64 - 0x08];
};

class ObjectShroudClient
{
public:
	virtual bool ShroudHideIfFogged(int playerIndex) const = 0;

private:
	unsigned char m_pad04[0x08 - 0x04];
};

class ObjectPartitionClient
{
public:
	virtual int PartitionGetPlayerIndex() const = 0;
};

class Object : public ObjectThingBase, public ObjectShroudClient, public ObjectPartitionClient
{
public:
	Player *getControllingPlayer() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline bool isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
	bool isUndetectedDefector() const { return (m_privateStatus & UNDETECTED_DEFECTOR) != 0; }

	virtual bool ShroudHideIfFogged(int playerIndex) const;
	virtual int PartitionGetPlayerIndex() const;

private:
	unsigned char m_pad070[0x304 - 0x70];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_privateStatus; // +0x438
	unsigned char m_pad439[0x4C4 - 0x439];
	Rva008F7B00 *m_shroudData; // +0x4C4
};

int Object::PartitionGetPlayerIndex() const
{
	Player *player = getControllingPlayer();
	if (player && !isUndetectedDefector() && !isKindOf(KINDOF_55))
	{
		Team *team = m_team;
		if (team && !team->rva0039F0D2() && !team->rva0039F824())
			return player->getPlayerIndex();
	}
	return -1;
}
