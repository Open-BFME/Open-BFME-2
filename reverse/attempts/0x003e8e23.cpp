// ?rva003E8E23@ScriptConditions@@IAE_NPAVParameter@@000@Z
// partial score=0.86 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
//
// BFME2 player-wide team walk conditions. The count conditions resolve a player from a
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
// Skirmish comparison conditions (Zero Hour ScriptConditions.cpp names; the
// condition numbers come from evaluateCondition's jump table and the template
// help strings initConditionTemplates stores for them):
//
// ?evaluateSkirmishUnownedFactionUnitComparison@ScriptConditions@@IAE_NPAVParameter@@00@Z @ 0x003E749E 249B,
// condition 91 "Unowned faction unit -- comparison". Walks
// the neutral player (PlayerList+0x18, Zero Hour's getNeutralPlayer) and
// counts members with disabled-mask bit 5 (Object+0x1C8 & 0x20; Zero Hour
// DISABLED_UNMANNED), then Zero Hour's six-way comparison switch.
//
// ?evaluateSkirmishPlayerHasComparisonGarrisoned@ScriptConditions@@IAE_NPAVParameter@@00@Z @ 0x003E7597 333B,
// condition 93 "Player has garrisoned buildings --
// comparison". Counts members whose Object+0x250 contain module answers
// isGarrisonable (vtable +0x10) and getContainCount(0) > 0 (+0x114, the slot
// ScriptConditions_evaluateIsBuildingEmpty.cpp already uses).
//
// ?evaluateSkirmishPlayerHasComparisonCapturedUnits@ScriptConditions@@IAE_NPAVParameter@@00@Z @ 0x003E76E4 283B,
// condition 94 "Player has captured units -- comparison".
// Counts members with private status bit 0x04 (Object+0x438; Zero Hour
// isCaptured).
//
// ?evaluateSkirmishPlayerHasDiscoveredPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E79F5 263B,
// condition 99 "Player has discovered another player".
// True when a member's shroud status for the discovering player's index
// (Player+0x54) is 1 or 2. The callee 0x0028D2A2 is rowed as
// Object::getShroudStatusForPlayer returning CellShroudStatus; its fallback
// value 1 and this caller's 1/2 test are Zero Hour's getShroudedStatus
// OBJECTSHROUD_CLEAR / OBJECTSHROUD_PARTIAL_CLEAR, so the result is read
// through that enum here.
//
// BFME2 differs from Zero Hour in the three player-parameter conditions:
// they walk every player of the parameter's mask (rowed getEachPlayerFromMask
// 0x002A7BC9) instead of playerFromParam, and evaluate the comparison per
// player, as the BFME1 donors ScriptConditionsGarrisonedUnits.cpp and
// ScriptConditionsSkirmishPlayerHasDiscoveredPlayer.cpp also do.
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

enum DisabledType
{
	DISABLED_UNMANNED = 5
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_COUNT = 0x80
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool isGarrisonable() const; // +0x10
	virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54();
	virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64();
	virtual void slot65(); virtual void slot66(); virtual void slot67(); virtual void slot68();
	virtual unsigned int getContainCount(Int extra) const; // +0x114
};

enum ObjectPrivateStatusBits
{
	CAPTURED = 0x04
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR
};

class Object
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
	ContainModuleInterface *getContain() const { return m_contain; }
	Bool testStatus(ObjectStatusTypes bit) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
	Bool isCaptured() const { return (m_privateStatus & CAPTURED) != 0; }
	Bool isDisabledByType(DisabledType type) const
	{
		return (m_disabledMask[type >> 3] >> (type & 7)) & 1;
	}
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad[0x1C8 - 8];
	unsigned char m_disabledMask[4]; // +0x1C8
	unsigned char m_pad1CC[0x250 - 0x1CC];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x264 - 0x254];
	ExperienceTracker *m_experienceTracker; // +0x264
	unsigned char m_pad268[0x438 - 0x268];
	unsigned char m_privateStatus; // +0x438
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
	Int getPlayerIndex() const { return m_playerIndex; }
private:
	char m_pad[0x54];
	Int m_playerIndex; // +0x54
	char m_pad58[0x32C - 0x58];
	PlayerTeamNode *m_playerTeamPrototypes; // +0x32C
};

class PlayerList
{
public:
	Player *getPlayerFromMask(Int mask);
	Player *getEachPlayerFromMask(Int &mask);
	Player *getNeutralPlayer() const { return m_neutralPlayer; }
private:
	unsigned char m_pad[0x18];
	Player *m_neutralPlayer; // +0x18
};
extern PlayerList *ThePlayerList;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

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
	Bool rva003E8E23(Parameter *playerParm, Parameter *typeParm, Parameter *comparisonParm, Parameter *rankParm);
	Bool evaluateSkirmishUnownedFactionUnitComparison(Parameter *pSkirmishPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm);
	Bool evaluateSkirmishPlayerHasComparisonGarrisoned(Parameter *pSkirmishPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm);
	Bool evaluateSkirmishPlayerHasComparisonCapturedUnits(Parameter *pSkirmishPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm);
	Bool evaluateSkirmishPlayerHasDiscoveredPlayer(Parameter *pSkirmishPlayerParm, Parameter *pDiscoveredByParm);
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

Bool ScriptConditions::evaluateSkirmishUnownedFactionUnitComparison(Parameter *pSkirmishPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm)
{
	Player *player = ThePlayerList->getNeutralPlayer();
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
				if (obj->isDisabledByType(DISABLED_UNMANNED))
					count++;
			}
		}
	}
	switch (pComparisonParm->getInt())
	{
		case 0: return count < pCountParm->getInt();
		case 1: return count <= pCountParm->getInt();
		case 2: return count == pCountParm->getInt();
		case 3: return count >= pCountParm->getInt();
		case 4: return count > pCountParm->getInt();
		case 5: return count != pCountParm->getInt();
	}
	return false;
}

Bool ScriptConditions::evaluateSkirmishPlayerHasComparisonGarrisoned(Parameter *pSkirmishPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm)
{
	Int mask = TheScriptEngine->rva00357B82(pSkirmishPlayerParm);
	while (mask)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (!player)
			continue;
		Int numGarrisonedBuildings = 0;
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
					ContainModuleInterface *cmi = obj->getContain();
					if (!cmi)
						continue;
					if (cmi->isGarrisonable() && cmi->getContainCount(0) > 0)
						++numGarrisonedBuildings;
				}
			}
		}
		Bool result = false;
		switch (pComparisonParm->getInt())
		{
			case 0: result = numGarrisonedBuildings < pCountParm->getInt(); break;
			case 1: result = numGarrisonedBuildings <= pCountParm->getInt(); break;
			case 2: result = numGarrisonedBuildings == pCountParm->getInt(); break;
			case 3: result = numGarrisonedBuildings >= pCountParm->getInt(); break;
			case 4: result = numGarrisonedBuildings > pCountParm->getInt(); break;
			case 5: result = numGarrisonedBuildings != pCountParm->getInt(); break;
		}
		if (result)
			return true;
	}
	return false;
}

Bool ScriptConditions::evaluateSkirmishPlayerHasComparisonCapturedUnits(Parameter *pSkirmishPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm)
{
	Int mask = TheScriptEngine->rva00357B82(pSkirmishPlayerParm);
	while (mask)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (!player)
			continue;
		Int numCapturedUnits = 0;
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
					if (obj->isCaptured())
						++numCapturedUnits;
				}
			}
		}
		Bool result = false;
		switch (pComparisonParm->getInt())
		{
			case 0: result = numCapturedUnits < pCountParm->getInt(); break;
			case 1: result = numCapturedUnits <= pCountParm->getInt(); break;
			case 2: result = numCapturedUnits == pCountParm->getInt(); break;
			case 3: result = numCapturedUnits >= pCountParm->getInt(); break;
			case 4: result = numCapturedUnits > pCountParm->getInt(); break;
			case 5: result = numCapturedUnits != pCountParm->getInt(); break;
		}
		if (result)
			return true;
	}
	return false;
}

Bool ScriptConditions::evaluateSkirmishPlayerHasDiscoveredPlayer(Parameter *pSkirmishPlayerParm, Parameter *pDiscoveredByParm)
{
	Int discoveredByMask = TheScriptEngine->rva00357B82(pDiscoveredByParm);
	if (!discoveredByMask)
		return false;
	Int playerMask = TheScriptEngine->rva00357B82(pSkirmishPlayerParm);
	while (discoveredByMask)
	{
		Player *discoveredBy = ThePlayerList->getEachPlayerFromMask(discoveredByMask);
		if (!discoveredBy)
			continue;
		Int discoveredByIndex = discoveredBy->getPlayerIndex();
		Int mask = playerMask;
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
						ObjectShroudStatus shroudStatus = (ObjectShroudStatus)obj->getShroudStatusForPlayer(discoveredByIndex);
						if (shroudStatus == OBJECTSHROUD_CLEAR || shroudStatus == OBJECTSHROUD_PARTIAL_CLEAR)
							return true;
					}
				}
			}
		}
	}
	return false;
}

Bool ScriptConditions::rva003E8E23(Parameter *playerParm, Parameter *typeParm, Parameter *comparisonParm, Parameter *rankParm)
{
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357475(playerParm->getString(), 0));
	if (!player)
		return false;
	const ThingTemplate *thingTemplate = 0;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(typeParm->getString());
	ObjectTypesTemp typesTemp;
	if (types)
		Script_objectTypesFromParam(typeParm, typesTemp.m_types);
	else
		thingTemplate = TheThingFactory->findTemplate(typeParm->getString());
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
				Bool typeMatches;
				if (types)
					typeMatches = typesTemp.m_types->isInSet(obj->getTemplate());
				else
					typeMatches = obj->getTemplate()->isEquivalentTo(thingTemplate);
				if (typeMatches)
				{
					ExperienceTracker *tracker = obj->getExperienceTracker();
					if (tracker)
					{
						Int rank = tracker->getRank();
						Bool matches = false;
						switch (comparisonParm->getInt())
						{
							case 0: matches = rank < rankParm->getInt(); break;
							case 1: matches = rank <= rankParm->getInt(); break;
							case 2: matches = rank == rankParm->getInt(); break;
							case 3: matches = rank >= rankParm->getInt(); break;
							case 4: matches = rank > rankParm->getInt(); break;
							case 5: matches = rank != rankParm->getInt(); break;
						}
						if (matches == 1)
							return true;
					}
				}
			}
		}
	}
	return false;
}
