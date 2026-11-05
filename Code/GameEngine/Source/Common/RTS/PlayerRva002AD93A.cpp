// cl: /Ireference/shims/moduledata /DNDEBUG /MD
//
// ?onUpgradeCompleted@Player@@QAEXPBVUpgradeTemplate@@H@Z @ 0x002AD93A 195B
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
// jmp back edge. Named onUpgradeCompleted: ZH's body, and addUpgrade
// (0x002AE329) calls it in its complete branch as ZH does. The int flag's
// meaning is a donor inference.

typedef bool Bool;
typedef int Int;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class UpgradeTemplate;
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

#include "../../../Include/Common/MemoryPoolObject.h"

#include "Common/Snapshot.h"

class Object
{
public:
	void updateUpgradeModules();
	void removeUpgrade(const UpgradeTemplate *upgrade);
};

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/Common/Team.h"

inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList() const
{
    return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
}

#include "../../../Include/GameLogic/PlayerTeamNode.h"

class UpgradeTemplate
{
public:
	unsigned char m_pad[0x4C];
	Int m_evaOwn; // +0x4C
	Int m_evaAlly; // +0x50
	Int m_evaEnemy; // +0x54
	Int m_evaRemovedOwn; // +0x58
	Int m_evaRemovedAlly; // +0x5C
	Int m_evaRemovedEnemy; // +0x60
};

class Player;

#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

enum EvaEventID { EVA_EVENT_STUB = 0 };
#include "../../../Include/GameClient/Eva.h"
extern Eva *TheEva;

#include "../../../Include/Common/Player.h"

void Player::onUpgradeCompleted(const UpgradeTemplate *upgrade, Int x)
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
	else if (localPlayer != 0 && m_defaultTeam != 0)
	{
		if (localPlayer->getRelationship(m_defaultTeam) == ALLIES)
			eventId = upgrade->m_evaAlly;
		else
			eventId = upgrade->m_evaEnemy;
	}
	TheEva->reportEvaEvent((EvaEventID)eventId, 0, 0);
}

// Target: 0x002AD9FD..0x002ADAC3, same list and iterator ABI as above.
// Calls rowed Object::removeUpgrade with the template; Eva fields +58/+5C/+60.
// Named onUpgradeRemoved: removeUpgrade (0x002ADAC3) calls it where ZH's
// removeUpgrade calls onUpgradeRemoved (ZH's own body is empty).
void Player::onUpgradeRemoved(const UpgradeTemplate *upgrade, Int x)
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
				obj->removeUpgrade(upgrade);
			}
		}
	}
	if (upgrade == 0 || x != 0)
		return;
	Int eventId = -1;
	Player *localPlayer = ThePlayerList->m_local;
	if (this == localPlayer)
		eventId = upgrade->m_evaRemovedOwn;
	else if (localPlayer != 0 && m_defaultTeam != 0)
	{
		if (localPlayer->getRelationship(m_defaultTeam) == ALLIES)
			eventId = upgrade->m_evaRemovedAlly;
		else
			eventId = upgrade->m_evaRemovedEnemy;
	}
	TheEva->reportEvaEvent((EvaEventID)eventId, 0, 0);
}
