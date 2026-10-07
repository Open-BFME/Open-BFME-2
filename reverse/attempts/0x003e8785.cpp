// ?rva003E8785@ScriptConditions@@IAE_NPAVParameter@@00@Z
// partial score=0.93 date=2026-10-07
// ?rva003E8785@ScriptConditions@@IAE_NPAVParameter@@00@Z PLAYER_HAS_NUM_UNITS_WITH_UPGRADE (condition 178)
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

class Object;

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

class Parameter
{
public:
	Int getInt() const { return m_int; }
	const AsciiString &getString() const { return m_string; }
private:
	unsigned char m_beforeInt[8];
	Int m_int;
	float m_real;
	AsciiString m_string;
};

class ThingTemplate
{
public:
	Bool isKindOf(Int t) const
	{
		return (m_kindOf[t >> 3] >> (t & 7)) & 1;
	}
private:
	unsigned char m_pad[0x108];
	unsigned char m_kindOf[16]; // +0x108
};

class ExperienceTracker
{
public:
	Int getLevel() const { return m_level; }
private:
	unsigned char m_pad[0x24];
	Int m_level; // +0x24
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_COUNT = 0x80
};

class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool rva00290D2B(const UpgradeTemplate *upgrade) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad[0x264 - 8];
	ExperienceTracker *m_experienceTracker; // +0x264
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
	Player *getPlayerFromMask(Int mask);
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
	Int rva00357B82(Parameter *playerParm);
};
extern ScriptEngine *TheScriptEngine;

enum { KINDOF_BIT_90 = 90 };

class ScriptConditions
{
protected:
	Bool rva003E85E0(Parameter *playerParm, Parameter *countParm, Parameter *rankParm);
	Bool rva003E8785(Parameter *playerParm, Parameter *countParm, Parameter *upgradeParm);
};

Bool ScriptConditions::rva003E85E0(Parameter *playerParm, Parameter *countParm, Parameter *rankParm)
{
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357B82(playerParm));
	if (!player)
		return false;
	Int count = 0;
	PlayerTeamNode *head = player->getPlayerTeams();
	for (PlayerTeamNode *it = head->m_next; it != player->getPlayerTeams(); it = it->m_next)
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
				if (obj->getTemplate()->isKindOf(KINDOF_BIT_90) && obj->getExperienceTracker() != 0
					&& obj->getExperienceTracker()->getLevel() >= rankParm->getInt())
					count++;
			}
		}
	}
	if (count >= countParm->getInt())
		return true;
	return false;
}

Bool ScriptConditions::rva003E8785(Parameter *playerParm, Parameter *countParm, Parameter *upgradeParm)
{
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357B82(playerParm));
	const UpgradeTemplate *upgrade = 0;
	if (player)
		upgrade = TheUpgradeCenter->findUpgrade(upgradeParm->getString());
	if (!upgrade)
		return false;
	Int count = 0;
	PlayerTeamNode *head = player->getPlayerTeams();
	for (PlayerTeamNode *it = head->m_next; it != player->getPlayerTeams(); it = it->m_next)
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
				if (!obj->testStatus((ObjectStatusTypes)0x26) && iter2.cur()->rva00290D2B(upgrade))
					count++;
			}
		}
	}
	if (count >= countParm->getInt())
		return true;
	return false;
}
