// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?getRelationship@Player@@QBE?AW4Relationship@@PBV1@@Z @0x002AC3E0 (69B)
// Player::getRelationship(const Player*) const -- BFME2 retail Player+0x54 is
// m_playerIndex (PlayerList 0x002A7B91 inlines 1-shift-plus-0x54) and
// Player+0x330 is m_playerRelations (team twin at +0x334 in 0x002AD0C6).
// Donor: BFME1 Player::getRelationship(Team) in
// open-bfme-1/Code/GameEngine/Source/Common/RTS/Player.cpp for the
// empty-then-find-then-NEUTRAL shape; ZH Common/Player.h + GameCommon.h for
// PlayerRelationMapType (hash_map<int Relationship>) and
// Relationship ENEMIES=0 NEUTRAL=1 ALLIES=2.
// Evidence: 13 callers including 0x002AD10E 0x002AD131 0x0029445D 0x004E94E8
// 0x0050E925 0x005AC9F2; ALLIES=2 checked by cmp eax 2 at 0x0050E92A and
// 0x00491C49; ICF-shares _M_find 0x002888D4.
#include <hash_map>

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

typedef std::hash_map<int, Relationship, std::hash<int>, std::equal_to<int> > PlayerRelationMapType;

struct RetailPlayerRelationMap
{
	void *m_vtbl;
	PlayerRelationMapType m_map;
};

class Team;
class Object;
class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
	Relationship getRelationship(const Player *that) const;
	Relationship getRelationship(const Team *that) const;
	Relationship getRelationship(const Object *that) const;

private:
	char m_pad00[0x54];
	int m_playerIndex; // +0x54
	char m_pad58[0x330 - 0x58];
	RetailPlayerRelationMap *m_playerRelations; // +0x330
	RetailPlayerRelationMap *m_teamRelations; // +0x334
};

class Team
{
public:
	Player *getControllingPlayer() const;
	int getTeamKey() const { return m_key34; }
private:
	char m_pad00[0x34];
	int m_key34; // +0x34
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

Relationship Player::getRelationship(const Player *that) const
{
	if (!that)
		return NEUTRAL;
	RetailPlayerRelationMap *rel = m_playerRelations;
	if (!rel)
		return NEUTRAL;
	if (rel->m_map.empty())
		return NEUTRAL;
	PlayerRelationMapType::const_iterator it = rel->m_map.find(that->getPlayerIndex());
	if (it != rel->m_map.end())
		return (*it).second;
	return NEUTRAL;
}

Relationship Player::getRelationship(const Team *that) const
{
	if (that)
	{
		RetailPlayerRelationMap *rel = m_teamRelations;
		if (!rel->m_map.empty())
		{
			PlayerRelationMapType::const_iterator it = rel->m_map.find(that->getTeamKey());
			if (it != rel->m_map.end())
				return (*it).second;
		}
		return getRelationship(that->getControllingPlayer());
	}
	return NEUTRAL;
}

Relationship Player::getRelationship(const Object *that) const
{
	if (that)
		return getRelationship(that->getControllingPlayer());
	return NEUTRAL;
}
