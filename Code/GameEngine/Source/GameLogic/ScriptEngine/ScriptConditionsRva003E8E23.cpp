// cl: /O1 /G7 /arch:SSE /Ireference/shims/moduledata /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?rva003E8E23@ScriptConditions@@IAE_NPAVParameter@@000@Z @ 0x003E8E23 459B
// PLAYER_HAS_OBJECT_OF_VETERANCY (condition 146; dispatcher 0x007EC1D5 pushes
// four Parameters). BFME2-only condition without a donor method name, so the
// method keeps an address name.
//
// Body: WorldBuilder twin 0x00FF2E50 (unoptimised build of the same source)
// followed literally: mask -> getPlayerFromMask, ObjectTypes lookup, an
// ObjectTypesTemp filled by Script_objectTypesFromParam or else a
// findTemplate fallback, the team-prototype / team-instance / member walks in
// Zero Hour's DLINK_ITERATOR form (!done(), cur(), null-member continue), the
// type test with a continue in each arm, the +0x264 experience tracker's
// +0x24 rank against a six-way comparison, and `matches == 1` returning true.
//
// Codegen evidence (no barrier or volatile needed): retail keeps the member
// in one callee-saved register from the loop test and never rotates the
// member loop. VC7.1 does that only when the bodies of
// Team::iterate_TeamMemberList (0x00263864), DLINK_ITERATOR<Object>::advance
// (0x00263526) and ObjectTypesTemp::ObjectTypesTemp (0x003BA7FF) are compiled
// in the same unit (it then knows they do not keep the iterator's or the
// temporary's address). All three emit retail's exact bytes here; the Object
// skeleton is ObjectDlinkPmf.h's (vbptr base at +0x68, DLINK base at +4).

typedef bool Bool;
typedef int Int;

class AsciiString;
class ThingTemplate;
class ExperienceTracker;
class Object;

// BFME2 Object skeleton (reference/open-bfme-1/inputs/reference/shims/objectdlink/ObjectDlinkPmf.h).
class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectThingPad
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
private:
	const ThingTemplate *m_template; // +0x00 Object+0x04
	unsigned char m_pad[0x64 - 4]; // +0x04
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectThingPad, public BfmeObjectVbptrCarrier
{
public:
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
private:
	unsigned char m_pad[0x264 - 0x70];
	ExperienceTracker *m_experienceTracker; // +0x264
};

// Zero Hour GameCommon.h DLINK_ITERATOR.
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

#include "../../../Include/Common/MemoryPoolObject.h"

#include "Common/Snapshot.h"

class Parameter
{
public:
	Int getInt() const { return m_int; }
	const AsciiString *getString() const { return (const AsciiString *)m_string; }
private:
	unsigned char m_beforeInt[8];
	Int m_int; // +0x08
	float m_real; // +0x0C
	unsigned char m_string[4]; // +0x10 (AsciiString)
};

class ThingTemplate
{
public:
	Bool isEquivalentTo(const ThingTemplate *other) const;
};

class ExperienceTracker
{
public:
	Int getRank() const { return m_rank; }
private:
	unsigned char m_pad[0x24];
	Int m_rank; // +0x24
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &key);
};
extern ThingFactory *TheThingFactory;

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_dlinkhead_TeamMemberList, &Object::dlink_next_TeamMemberList);
	}
private:
	unsigned char m_teamPad[0x38 - 8];
	Object *m_dlinkhead_TeamMemberList; // +0x38
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

class ObjectTypes;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../../Include/GameLogic/ScriptConditions.h"

class Rva00376A62
{
public:
	Bool rva00376A84(const void *thing);
};

class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	Bool isInSet(const ThingTemplate *thingTemplate) const
	{
		return ((Rva00376A62 *)this)->rva00376A84(thingTemplate);
	}
private:
	unsigned char m_padTypesState[0x14 - 4]; // 0x14-byte object (ctor 0x003769F9)
};

class ObjectTypesTemp
{
public:
	ObjectTypesTemp();
	~ObjectTypesTemp() { ::delete m_types; }
	ObjectTypes *m_types;
};

void Script_objectTypesFromParam(Parameter *typeParm, ObjectTypes *types);

// Zero Hour defines this helper in ScriptConditions.cpp (rowed 0x003BA7FF).
__declspec(noinline) inline ObjectTypesTemp::ObjectTypesTemp() : m_types(0)
{
	m_types = new ObjectTypes;
}

Bool ScriptConditions::rva003E8E23(Parameter *playerParm, Parameter *typeParm, Parameter *comparisonParm, Parameter *rankParm)
{
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357475(*playerParm->getString(), 0));
	if (!player)
		return false;
	const ThingTemplate *thingTemplate = 0;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(*typeParm->getString());
	ObjectTypesTemp typesTemp;
	if (types)
		Script_objectTypesFromParam(typeParm, typesTemp.m_types);
	else
		thingTemplate = TheThingFactory->findTemplate(*typeParm->getString());
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
				if (types)
				{
					if (!typesTemp.m_types->isInSet(obj->getTemplate()))
						continue;
				}
				else
				{
					if (!obj->getTemplate()->isEquivalentTo(thingTemplate))
						continue;
				}
				ExperienceTracker *tracker = obj->getExperienceTracker();
				if (!tracker)
					continue;
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
	return false;
}
