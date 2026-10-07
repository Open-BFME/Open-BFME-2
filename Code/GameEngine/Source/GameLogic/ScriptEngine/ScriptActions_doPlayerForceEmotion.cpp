// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
//
// ?doPlayerForceEmotion@ScriptActions@@IAEXPAVParameter@@HM@Z @0x003C37C0 (206B):
// the player-wide sibling of doTeamForceEmotion (0x003C375A). Target evidence:
// executeAction's arm right after the TEAM_FORCE_EMOTION one (call 0x003CE995)
// passes (parameter 0, parameter 1 int, parameter 2 real); for an emotion index
// in [0, 12) the body turns the player parameter's +0x10 string into a player
// mask through the rowed ScriptEngine::rva00357475 (NULL wildcard flag), walks
// each player from the rowed getEachPlayerFromMask (0x002A7BC9), its +0x32C
// team-prototype list, each prototype's +0x334 instance list (member pointer
// 0x009C4AF5) and each team's members (rowed iterate_TeamMemberList 0x00263864
// and advance 0x00263526), and hands (index, value, 0) to the rowed
// Object::rva0028ECA8 forwarder as doTeamForceEmotion does.
// Donor: the name and walk are BFME1's doPlayerForceEmotion
// (reference/open-bfme-1 game/.../ScriptActions_doPlayerForceEmotion.cpp, which
// limits the index to 10 and uses a 16-bit mask); the bounds, the int mask and
// the Zero Hour DLINK_ITERATOR team walk follow the BFME2 bytes.
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

class Object;
class Team;

template<class OBJCLASS>
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

template <>
class DLINK_ITERATOR<Object>
{
private:
	Object *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
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
	void rva0028ECA8(int index, float value, int arg);
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

class Player
{
public:
	PlayerTeamNode *getPlayerTeams() const { return m_playerTeamPrototypes; }
private:
	char m_pad[0x32C];
	PlayerTeamNode *m_playerTeamPrototypes; // +0x32C
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(Int &mask);
};
extern PlayerList *ThePlayerList;

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
private:
	unsigned char m_pad[0x10];
	AsciiString m_string; // +0x10
};

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doPlayerForceEmotion(Parameter *pPlayer, int index, float value);
};

void ScriptActions::doPlayerForceEmotion(Parameter *pPlayer, int index, float value)
{
	if (index < 0 || index >= 12)
		return;
	Int mask = TheScriptEngine->rva00357475(pPlayer->getString(), 0);
	while (mask)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (!player)
			continue;
		PlayerTeamNode *head = player->getPlayerTeams();
		for (PlayerTeamNode *it = head->m_next; it != player->getPlayerTeams(); it = it->m_next)
		{
			for (DLINK_ITERATOR<Team> iter = it->m_value->iterate_TeamInstanceList(); !iter.done(); iter.advance())
			{
				Team *team = iter.cur();
				if (!team)
					continue;
				for (DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList(); !objIter.done(); objIter.advance())
				{
					Object *obj = objIter.cur();
					if (!obj)
						continue;
					obj->rva0028ECA8(index, value, 0);
				}
			}
		}
	}
}
