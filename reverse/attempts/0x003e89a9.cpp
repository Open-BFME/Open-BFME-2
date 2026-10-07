// ?rva003E89A9@ScriptConditions@@IAE_NPAVParameter@@0@Z
// partial score=0.9 date=2026-10-07
// ?rva003E89A9@ScriptConditions@@IAE_NPAVParameter@@0@Z UNIT_HAS_TOGGLED_WEAPON (condition 180)
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
//
// BFME2 player-wide unit count conditions. Each one resolves a player from a
// player Parameter (rowed ScriptEngine::rva00357B82 mask plus
// PlayerList::getPlayerFromMask 0x002A7B91), then walks that player's +0x32C
// team-prototype list, every prototype's +0x334 team instance list (member
// pointer 0x009C4AF5) and every team's member list (rowed
// iterate_TeamMemberList 0x00263864 and advance 0x00263526), counting the
// members that pass the condition's test.
//
// ?rva003E85E0@ScriptConditions@@IAE_NPAVParameter@@00@Z @ 0x003E85E0 195B
// Target evidence: evaluateCondition's jump table (0x007EC5C0, index minus 5)
// sends condition 176 here; initConditionTemplates names template 176
// ANY_HERO_REACHED_RANK. Counts members whose template has KindOf bit 90
// (template byte +0x113 bit 2) and whose Object+0x264 record holds a +0x24
// rank at least the third Parameter's int, and returns count >= the second
// Parameter's int. The +0x264/+0x24 rank matches the rowed
// evaluateNamedUnitRankLevel (0x003E92DF). BFME2-only condition with no donor
// method name, so the method keeps an address name; reading bit 90 as the
// hero KindOf is an inference from the template name.
// Donor shape (Zero Hour): the DLINK_ITERATOR with the checked advance and
// the null-team / null-member skips, as in PlayerRva002AD93A.cpp.

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

class Parameter
{
public:
	Int getInt() const { return m_int; }
	const AsciiString &getString() const { return m_string; }
private:
	unsigned char m_beforeInt[8];
	Int m_int; // +0x08
	float m_real; // +0x0C
	AsciiString m_string; // +0x10
};

enum KindOfType
{
	KINDOF_90 = 90
};

class ThingTemplate
{
public:
	Bool isEquivalentTo(const ThingTemplate *tt) const;
	Bool isKindOf(KindOfType t) const
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
	Int getRank() const { return m_rank; }
private:
	unsigned char m_pad[0x24];
	Int m_rank; // +0x24
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_COUNT = 0x80
};

// Rowed 0x0028D891: the flag-word test over Object+0x370, address-named.
class Rva0028D891Owner
{
public:
	Bool testBit(int bit) const;
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool testBit370(int bit) const { return ((const Rva0028D891Owner *)this)->testBit(bit); }
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

// Rowed 0x002D06CA, the template lookup TheThingFactory (0x00DFF000) answers
// by name; its owner is still address-named.
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern Rva002D06CA *TheThingFactory;

class ScriptEngine
{
public:
	Int rva00357B82(Parameter *playerParm);
};
extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool rva003E85E0(Parameter *playerParm, Parameter *countParm, Parameter *rankParm);
	Bool rva003E89A9(Parameter *playerParm, Parameter *templateParm);
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
				if (obj->getTemplate()->isKindOf(KINDOF_90) && obj->getExperienceTracker() != 0
					&& obj->getExperienceTracker()->getRank() >= rankParm->getInt())
					count++;
			}
		}
	}
	if (count >= countParm->getInt())
		return true;
	return false;
}

Bool ScriptConditions::rva003E89A9(Parameter *playerParm, Parameter *templateParm)
{
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357B82(playerParm));
	const ThingTemplate *tmpl = 0;
	if (player)
		tmpl = (const ThingTemplate *)TheThingFactory->rva002D06CA(&templateParm->getString());
	if (!tmpl)
		return false;
	PlayerTeamNode *head = player->getPlayerTeams();
	for (PlayerTeamNode *it = head->m_next; it != player->getPlayerTeams(); it = it->m_next)
	{
		for (DLINK_ITERATOR<Team> iter = it->m_value->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			Object *obj;
			for (DLINK_ITERATOR<Object> iter2 = team->iterate_TeamMemberList(); (obj = iter2.cur()) != 0; iter2.advance())
			{
				if (obj->getTemplate()->isEquivalentTo(tmpl))
				{
					if (obj->testBit370(0x18) || obj->testBit370(0x19) || obj->testBit370(0x1A)
						|| obj->testStatus((ObjectStatusTypes)0x51))
						return true;
				}
			}
		}
	}
	return false;
}
