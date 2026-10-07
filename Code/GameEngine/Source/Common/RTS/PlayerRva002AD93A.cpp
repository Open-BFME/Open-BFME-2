// cl: /Ireference/shims/moduledata /DNDEBUG /MD
//
// ?rva002AD93A@Player@@QAEXPBVUpgradeTemplate@@H@Z @ 0x002AD93A 195B
//
// Target evidence: thiscall on Player (ret 8: upgrade template and an int
// flag). Walks the +0x32C team-prototype list; for each prototype's +0x334
// team instance list (member pointer 0x9C4AF5) it calls the rowed
// Object::updateUpgradeModules 0x00292EEA on every team member. Then, when
// the template is non-null and the flag is zero, it picks the template's
// +0x4C/+0x50/+0x54 event (local player / ally via getRelationship 0x002AD0C6
// on the +0x2EC team / other) and passes it to the Eva global 0x00DFDC30
// member 0x001DE2DA.
// Donor (Zero Hour Player::onUpgradeCompleted): the team walk with Zero
// Hour's null-team and null-member skips and the checked DLINK_ITERATOR
// advance; those skips are what give retail's top-tested team loop with the
// jmp back edge. The name onUpgradeCompleted and the meaning of the int flag
// are donor inferences, so the row keeps its address name.

typedef bool Bool;
typedef int Int;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object;
class Team;

// Zero Hour's DLINK_ITERATOR for team instances (advance through the member
// pointer, see TeamPrototypeTeamIterators.cpp).
template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	Bool done() const
	{
		return m_cur == 0;
	}
	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

// The member iterator BFME2 returns by value from Team::iterate_TeamMemberList
// (24 bytes, out-of-line advance; see TeamRva0039DDC2.cpp).
template <>
class DLINK_ITERATOR<Object>
{
private:
	Object *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	Bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

#include "Common/Snapshot.h"

class Object
{
public:
	void updateUpgradeModules();
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class TeamPrototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
	}
private:
	unsigned char m_pad[0x334];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_value;
};

class UpgradeTemplate
{
public:
	unsigned char m_pad[0x4C];
	Int m_evaOwn; // +0x4C
	Int m_evaAlly; // +0x50
	Int m_evaEnemy; // +0x54
};

class Player;

class PlayerList
{
public:
	unsigned char m_pad[0x10];
	Player *m_local; // +0x10
};
extern PlayerList *ThePlayerList;

class Eva
{
public:
	void rva001DE2DA(Int eventId, const struct Coord3D *pos, Int x);
};
extern Eva *TheEva;

class Player
{
public:
	void rva002AD93A(const UpgradeTemplate *upgrade, Int x);
	Relationship getRelationship(const Team *team) const;
private:
	char m_pad00[0x2EC];
	Team *m_team2EC; // +0x2EC
	char m_pad2F0[0x32C - 0x2F0];
	PlayerTeamNode *m_playerTeamPrototypes; // +0x32C
};

void Player::rva002AD93A(const UpgradeTemplate *upgrade, Int x)
{
	for (PlayerTeamNode *it = m_playerTeamPrototypes->m_next; it != m_playerTeamPrototypes; it = it->m_next)
	{
		for (DLINK_ITERATOR<Team> iter = it->m_value->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			for (DLINK_ITERATOR<Object> iter2 = team->iterate_TeamMemberList(); !iter2.done(); iter2.advance())
			{
				Object *obj = iter2.cur();
				if (!obj)
					continue;
				obj->updateUpgradeModules();
			}
		}
	}
	if (upgrade == 0 || x != 0)
		return;
	Int eventId = -1;
	Player *localPlayer = ThePlayerList->m_local;
	if (this == localPlayer)
		eventId = upgrade->m_evaOwn;
	else if (localPlayer != 0 && m_team2EC != 0)
	{
		if (localPlayer->getRelationship(m_team2EC) == ALLIES)
			eventId = upgrade->m_evaAlly;
		else
			eventId = upgrade->m_evaEnemy;
	}
	TheEva->rva001DE2DA(eventId, 0, 0);
}
