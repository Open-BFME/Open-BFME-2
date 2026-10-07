// ?rva003E8B47@ScriptConditions@@IAE_NPAVParameter@@0@Z
// partial score=0.88 date=2026-10-07
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
//
// ?rva003E8AA9@ScriptConditions@@IAE_NPAVParameter@@@Z @ 0x003E8AA9 158B
// Target evidence: jump-table index 176 sends condition 181 here; the
// template is named ANY_UNITS_USING_BLOODTHIRSTY. True when any member of the
// player's teams has Object status 0x41 (rowed testStatus 0x0004E536). The
// BFME1 donor ScriptConditionsAnyUnitsUsingBloodthirsty.cpp has the same walk;
// its status bit name is not carried over.
//
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
	float m_real;
	AsciiString m_string; // +0x10
};

enum KindOfType
{
	KINDOF_90 = 90
};

class ThingTemplate
{
public:
	Bool isKindOf(KindOfType t) const
	{
		return (m_kindOf[t >> 3] >> (t & 7)) & 1;
	}
	Bool isEquivalentTo(const ThingTemplate *tt) const;
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

// Object::rva0028C197's result (vtable slot 0x36 probed by
// UNIT_IN_ALT_FORMATION).
class Rva003E8B47Slot36
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual void slot1F();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot2A(); virtual void slot2B();
	virtual void slot2C(); virtual void slot2D(); virtual void slot2E(); virtual void slot2F();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot3A();
	virtual Bool slot3B();
};

// The +0x20 interface of Object::rva0028BD92's special ability update.
class Rva003E8C24Interface
{
public:
	virtual void slot00(); virtual void slot01();
	virtual Bool slot02();
};

class Rva003E8C24Update
{
public:
	Rva003E8C24Interface *getInterface() { return (Rva003E8C24Interface *)((char *)this + 0x20); }
};

class Object
{
public:
	void *rva0028C197() const;
	void *rva0028BD92(Int type);
	Bool testStatus(ObjectStatusTypes bit) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
private:
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

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

// ObjectTypes::isInSet(const ThingTemplate *) is rowed under its address name.
class Rva00376A62
{
public:
	Bool rva00376A84(const void *thingTemplate);
};

class ObjectTypes
{
public:
	virtual ~ObjectTypes();
	Bool isInSet(const ThingTemplate *thingTemplate)
	{
		return ((Rva00376A62 *)this)->rva00376A84(thingTemplate);
	}
};

class ObjectTypesTemp
{
public:
	ObjectTypesTemp();
	~ObjectTypesTemp() { ::delete m_types; }
	ObjectTypes *m_types;
};

void Script_objectTypesFromParam(Parameter *typeParm, ObjectTypes *types);

class PlayerList
{
public:
	Player *getPlayerFromMask(Int mask);
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
	Int rva00357475(const AsciiString &name, Bool *special);
	ObjectTypes *getObjectTypes(const AsciiString &name);
	Int rva00357B82(Parameter *playerParm);
};
extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool rva003E85E0(Parameter *playerParm, Parameter *countParm, Parameter *rankParm);
	Bool rva003E8AA9(Parameter *playerParm);
	Bool rva003E8B47(Parameter *playerParm, Parameter *templateParm);
	Bool rva003E8C24(Parameter *playerParm, Parameter *templateParm);
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

Bool ScriptConditions::rva003E8AA9(Parameter *playerParm)
{
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357B82(playerParm));
	if (!player)
		return false;
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
				if (obj->testStatus((ObjectStatusTypes)0x41))
					return true;
			}
		}
	}
	return false;
}


Bool ScriptConditions::rva003E8B47(Parameter *playerParm, Parameter *templateParm)
{
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357B82(playerParm));
	const ThingTemplate *tmpl = 0;
	if (player)
		tmpl = TheThingFactory->findTemplate(templateParm->getString());
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
				if (obj->m_template->isEquivalentTo(tmpl))
				{
					Rva003E8B47Slot36 *found = (Rva003E8B47Slot36 *)obj->rva0028C197();
					if (found && !found->slot3B())
						return true;
				}
			}
		}
	}
	return false;
}


