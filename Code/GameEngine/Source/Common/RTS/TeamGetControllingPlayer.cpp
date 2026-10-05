// cl: /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata
// stlport

// ?getControllingPlayer@Team@@QBEPAVPlayer@@XZ, retail 0x0039D7CF (12 bytes).
// Team::getControllingPlayer is `return m_proto ? m_proto->m_owningPlayer :
// NULL`. Retail-measured BFME2 layout: Team::m_proto is at +0x30 here and the
// prototype owner holds m_owningPlayer at +0x08. Dedicated TU so the pin
// (Object::getControllingPlayer tail target) resolves to a row.
//
// ?getRelationship@Team@@QBE?AW4Relationship@@PBV1@@Z, retail 0x003A0FD2
// (137 bytes). BFME1 donor Team::getRelationship (Team.cpp:2128): the
// team-override map, then the player-override map keyed by the other team's
// controlling player index, then the controlling player's own relationship.
// BFME2 retail layout: Team+0x34 is the team key (Player 0x002AD0C6 inlines
// the same +0x34 read), Team+0x118 the team-override map and Team+0x11C the
// player-override map (the BFME1 donor keeps them at +0xEC/+0xF0),
// Player+0x54 is m_playerIndex. Callees: the rowed hashtable _M_find
// 0x002888D4 and Player::getRelationship(const Team *) 0x002AD0C6; 9 callers
// such as 0x002760E1 and 0x0028D243. Retail keeps state across the
// getControllingPlayer call in a volatile register, which cl only does when
// that callee was compiled earlier in the same TU, so it joins this file; the
// TU takes the STLport flags its hash_map needs (the two earlier bodies are
// unchanged by them).
//
// ?updateState@TeamPrototype@@QAEXXZ, retail 0x003A34AC (158 bytes), pinned
// from the byte-verified Player::updateTeamStates. Zero Hour's
// TeamPrototype::updateState over the +0x334 team list with Zero Hour's
// DLINK_ITERATOR shape (TeamPrototypeTeamIterators.cpp: the advance calls
// through &Team::dlink_next_TeamInstanceList with Team's two-base zero
// this-adjustment): each team's updateState (0x0039F0E3, pinned from this
// call), then the empty-team sweep -- singleton bit 0 of +0x18, the
// controlling player's default team at +0x2EC, the team's active flag at
// +0x5D -- deleting through TheTeamFactory's teamAboutToBeDeleted
// (0x003A3048) and BFME 2's deleteInstance shape. Retail reuses ecx for the
// second getControllingPlayer call, so it joins this file too; Team gains
// its two polymorphic bases here (MemoryPoolObject, Snapshot), which
// leaves every offset above unchanged.
//
// ?teamAboutToBeDeleted@TeamPrototype@@QAEXPAVTeam@@@Z, retail 0x003A2CA5
// (70 bytes), pinned from the byte-verified TeamFactory::teamAboutToBeDeleted.
// Zero Hour's body over the same team-list iterator: each team drops its
// override relationship with the dying team's id (+0x34, TEAM_ID_INVALID for
// null) through 0x003A2897, whose map-erase body is Zero Hour's
// Team::removeOverrideTeamRelationship on the +0x118 relation map.
#include <hash_map>
#include "Common/Snapshot.h"

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

	char m_pad00[0x54];
	int m_playerIndex; // +0x54
	char m_pad58[0x5c - 0x58];
	int m_playerType; // +0x5C
	Team *getDefaultTeam() { return m_defaultTeam; }

	char m_pad60[0x2EC - 0x60];
	Team *m_defaultTeam; // +0x2EC
	char m_pad2F0[0x330 - 0x2F0];
	RetailPlayerRelationMap *m_playerRelations; // +0x330
	RetailPlayerRelationMap *m_teamRelations; // +0x334
};

struct TeamPrototypeOwner
{
	unsigned char m_pad00[ 0x08 ];
	Player *m_owningPlayer;
};

class MemoryPoolObject
{
public:
	virtual void *deleteInstance(int flags);
};

template <class OBJCLASS>
class TeamInstanceIterator
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	TeamInstanceIterator(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	bool done() const
	{
		return m_cur == 0;
	}
	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

class Rva002A9BF2
{
public:
	void *rva002A9BF2();
};

typedef unsigned int UnsignedInt;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

struct ThingTemplate
{
	unsigned char m_pad[0x108];
	UnsignedInt m_kind0;
	unsigned char m_pad2[0x11A - 0x10C];
	unsigned char m_kindByte11a;
};

class BfmeTab1026
{
public:
	char bfmeHas1026(int a, int b);
};

class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_pad00[4];
	ThingTemplate *m_template;
	unsigned char m_pad08[0x74 - 0x08];
	unsigned int m_id;
	unsigned char m_pad78[0x94 - 0x78];
	unsigned char m_status94;
	unsigned char m_pad95[0x438 - 0x95];
	unsigned char m_dead;
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	void updateState();
	bool removeOverrideTeamRelationship(unsigned int teamID);
	Object *getFirstItemIn_TeamMemberList() const { return m_dlinkhead_TeamMemberList; }
	bool isActive() const { return m_active; }
	Player *getControllingPlayer() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void rva0039D84A(Object *obj);
	bool rva0039DF87(BfmeTab1026 *tab);
	int getTeamKey() const { return m_key34; }
	Relationship getRelationship(const Team *that) const;

private:
	unsigned char m_pad08[ 0x30 - 0x08 ];
	TeamPrototypeOwner *m_proto; // +0x30
	int m_key34; // +0x34
	Object *m_dlinkhead_TeamMemberList; // +0x38
	unsigned char m_pad3C[ 0x5D - 0x3C ];
	bool m_active; // +0x5D
	unsigned char m_pad5E[ 0x114 - 0x5E ];
	unsigned int m_target; // +0x114
	RetailPlayerRelationMap *m_teamRelations; // +0x118
	RetailPlayerRelationMap *m_playerRelations; // +0x11C
};

Player *Team::getControllingPlayer() const
{
	if( !m_proto )
		return 0;
	return m_proto->m_owningPlayer;
}

// ?rva0039D84A@Team@@QAEXPAVObject@@@Z, retail 0x0039D84A (63 bytes).
// Team::rva0039D84A(Object*): clears Team+0x114 when arg null else stores
// Object+0x74 id only for computer players (Player+0x5c == 1) with non-zero
// difficulty via rowed Rva002A9BF2::rva002A9BF2. Shape matches the BFME1/ZH
// Team::setTeamTargetObject donor with BFME2 deltas (Team proto +0x30 vs +0x04
// target +0x114 vs +0xE8 Player type +0x5c vs +0x2c Object id +0x74 same).
// Same TU as getControllingPlayer so the second call reuses ecx as retail does.
void Team::rva0039D84A(Object *obj)
{
	if( obj == 0 )
	{
		m_target = 0;
		return;
	}
	if( getControllingPlayer()->m_playerType != 1 )
		return;
	if( ((Rva002A9BF2 *)getControllingPlayer())->rva002A9BF2() == 0 )
		return;
	m_target = obj->m_id;
}

Relationship Team::getRelationship(const Team *that) const
{
	RetailPlayerRelationMap *teamMap = m_teamRelations;
	if (!teamMap->m_map.empty() && that != NULL)
	{
		PlayerRelationMapType::const_iterator it = teamMap->m_map.find(that->getTeamKey());
		if (it != teamMap->m_map.end())
		{
			return (*it).second;
		}
	}

	RetailPlayerRelationMap *playerMap = m_playerRelations;
	if (!playerMap->m_map.empty() && that != NULL)
	{
		Player *thatPlayer = that->getControllingPlayer();
		if (thatPlayer != NULL)
		{
			PlayerRelationMapType::const_iterator it = playerMap->m_map.find(thatPlayer->getPlayerIndex());
			if (it != playerMap->m_map.end())
			{
				return (*it).second;
			}
		}
	}

	return getControllingPlayer()->getRelationship(that);
}

bool Team::rva0039DF87(BfmeTab1026 *tab)
{
	Player *player = getControllingPlayer();
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		if ((cur->m_dead & 1) != 0)
			continue;
		if ((cur->m_status94 & 1) != 0)
			continue;
		ThingTemplate *tmpl = cur->m_template;
		if ((int)(tmpl->m_kind0 & 0x80) != 0)
			continue;
		if ((tmpl->m_kind0 & 0x2000000) != 0)
			continue;
		if ((tmpl->m_kindByte11a & 0x10) != 0)
			continue;
		if (tab->bfmeHas1026((int)cur, (int)player) != 0)
			return true;
	}
	return false;
}

class TeamFactory
{
public:
	void teamAboutToBeDeleted(Team *team);
};

extern TeamFactory *TheTeamFactory;

enum { TEAM_SINGLETON = 0x01 };

class TeamPrototype
{
public:
	TeamInstanceIterator<Team> iterate_TeamInstanceList() const
	{
		return TeamInstanceIterator<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
	}
	bool getIsSingleton() const { return (m_flags & TEAM_SINGLETON) != 0; }
	void updateState();
	void teamAboutToBeDeleted(Team *team);

private:
	unsigned char m_pad00[0x18];
	int m_flags; // +0x18
	unsigned char m_pad1C[0x334 - 0x1C];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

void TeamPrototype::updateState()
{
	for (TeamInstanceIterator<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		iter.cur()->updateState();
	}
	/* remove empty teams. */
	bool done = false;
	while (!done) {
		done = true;
		for (TeamInstanceIterator<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			if (iter.cur()->getFirstItemIn_TeamMemberList() == 0)
			{
				// Team has no members.
				if (this->getIsSingleton())
				{
					continue; // Don't delete singleton teams, even if they are empty.
				}

				if (iter.cur()->getControllingPlayer() && iter.cur()->getControllingPlayer()->getDefaultTeam() == iter.cur())
				{
					// This is the player's default team, so don't remove it.
					continue;
				}

				// don't delete inactive teams - they are under construction
				if (iter.cur()->isActive() == false)
				{
					continue;
				}

				// So remove it
				TheTeamFactory->teamAboutToBeDeleted(iter.cur());
				::operator delete(iter.cur()->deleteInstance(0));

				done = false;
				break;
			}
		}
	}
}

void TeamPrototype::teamAboutToBeDeleted(Team *team)
{
	for (TeamInstanceIterator<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		iter.cur()->removeOverrideTeamRelationship(team ? team->getTeamKey() : 0);
	}
}
