// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ZH donor: GeneralsMD ScriptConditions.cpp evaluateTeamStateIs and
// evaluateTeamStateIsNot. Target evidence: the evaluateCondition jump table
// (0x007EC5C0) sends cases 11 and 12 to 0x003E9471 and 0x003E94E5, which
// initConditionTemplates names TEAM_STATE_IS and TEAM_STATE_IS_NOT; both
// compare the team state string at +0x44 with a copied parameter string via
// the rowed StringBase<char>::compare 0x000069D6.
// The shared AsciiString compare declaration is nonthrowing: retail stores
// no EH state for the copied name around the comparison. Its existing ABI
// spelling resolves directly to the verified StringBase worker.

//
// ?evaluateHasUnits@ScriptConditions@@IAE_NPAVParameter@@@Z @ 0x003E9373 254B
// ZH donor: GeneralsMD ScriptConditions.cpp evaluateHasUnits, verbatim.
// Target evidence: the jump table sends case 10 to 0x003E9373, which
// initConditionTemplates names TEAM_HAS_UNITS; the body compares the
// "<This Team>" literal (0x0081531C) with the rowed compare 0x000069B1,
// resolves teams with the rowed getTeamNamed 0x003584E9 and reads the
// prototype name through Team+0x30 / TeamPrototype+0x14 with the
// TheEmptyString fallback, as ZH's Team::getName does. 0x0039DEC4 (rowed
// rva0039DEC4@Team) is ZH's Team::hasAnyUnits by its body: it skips dead,
// destroyed, structure, projectile and mine members. 0x003A2659 is ZH's
// one-argument TeamFactory::findTeamPrototype: it splits the qualified name
// and forwards to the two-argument findTeamPrototype 0x0039FE6C. The instance
// walk loads the member pointer 0x009C4AF5 (DLINK_ITERATOR<Team>).
//
// ?evaluateNamedAttackedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E9556 169B
// ?evaluateTeamAttackedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E95FF 246B
// ?evaluateNamedAttackedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E96F5 137B
// ZH donors: the same-name GeneralsMD ScriptConditions.cpp bodies. Target
// evidence: jump-table cases 19, 20 and 21 call these addresses, and
// initConditionTemplates names them NAMED_ATTACKED_BY_OBJECTTYPE,
// TEAM_ATTACKED_BY_OBJECTTYPE and NAMED_ATTACKED_BY_PLAYER. BFME2 keeps the
// attacker lookup by m_sourceID (DamageInfo+0x08, rowed findObjectByID
// 0x00049DC5) without ZH's later m_sourceTemplate branch; the type test is
// the pinned ObjectTypes::isInSet 0x00376A62 on the attacker template's name
// (+0x64) through an ObjectTypesTemp (rowed ctor 0x003BA7FF) filled by the
// cdecl objectTypesFromParam 0x00566E6C. The player test walks every player
// of the parameter's mask (rowed rva00357B82 plus getEachPlayerFromMask)
// against the rowed getControllingPlayer 0x0028AFA9. The body module is
// Object+0x254 and getLastDamageInfo its vslot +0x3C, as in the rowed
// evaluateTeamAttackedByPlayer.
//
// ??0ObjectTypesTemp@@QAE@XZ @ 0x003BA7FF 64B (rehomed from
// ObjectTypesTempCtor.cpp): m_types(0) then new ObjectTypes (0x14 bytes,
// rowed ctor 0x003769F9), as Zero Hour's ScriptConditions.cpp helper.
//
// ?evaluateBuiltByPlayer@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@1@Z @ 0x003E977E 430B
// ZH/BFME 1 donor: the same-name ScriptConditions.cpp body. Target evidence:
// jump-table case 23 calls 0x003E977E, which initConditionTemplates names
// BUILT_BY_PLAYER. The body looks the type up with the pinned
// ThingFactory::findTemplate 0x002D06CA before the cached-result test
// (Condition customData +0x44 / customFrame +0x48 against TheScriptEngine
// +0x1A15C), fills two STLport vectors through ObjectTypes::
// prepForPlayerCounting 0x00376C50 (its body walks m_objectTypes, pushes each
// found template and resizes the counts, as ZH's) and, unlike ZH's single
// player, counts every player of the parameter's mask with the rowed
// countObjectsByThingTemplate 0x002AB0C5 and sum 0x003BD46E. Retail records
// EH states around the vectors' inline free() calls, which /EHs (extern "C"
// may throw) reproduces; the unit's other bodies make no C calls in EH
// scope.
//
// ?evaluatePlayerUnitCondition@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@111@Z @ 0x003E9C3B 551B
// ZH/BFME 1 donor: the same-name ScriptConditions.cpp body. Target evidence:
// jump-table case 58 calls 0x003E9C3B, which initConditionTemplates names
// PLAYER_HAS_OBJECT_COMPARISON (ZH's caller of evaluatePlayerUnitCondition).
// Same cache, vectors and prepForPlayerCounting as evaluateBuiltByPlayer; the
// count sums every non-null player of the mask (countObjectsByThingTemplate
// with ignoreDead true, sum 0x003BD46E) before the six-way comparison on
// Parameter::getInt (+0x08).
#include <vector>
#include "ascii_string.h"

class Parameter
{
public:
	int getInt() const { return m_int; }
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
	unsigned char m_afterString[8];
};

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
	bool done() const
	{
		return m_cur == 0;
	}
	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

class Object;

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
	bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

#include "Common/Snapshot.h"

class Team;
class Player;

#include "../../Common/GameLogicObjectLookupView.h"

struct DamageInfoInput
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
};

struct DamageInfo
{
	DamageInfoInput in;
};

class BodyModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual const DamageInfo *getLastDamageInfo() const; // +0x3C
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
private:
	unsigned char m_pad00[0x64];
	AsciiString m_name; // +0x64
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Player *getControllingPlayer() const;
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x254 - 0x08];
	BodyModuleInterface *m_body; // +0x254
};

extern GameLogic *TheGameLogic;

class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	bool isInSet(const AsciiString &name) const;
	int prepForPlayerCounting(_STL::vector<const ThingTemplate *> &templates, _STL::vector<int> &counts);
private:
	AsciiString m_listName; // +0x04
	void *m_objectTypes[3]; // +0x08 vector<AsciiString>
};

class ObjectTypesTemp
{
public:
	ObjectTypesTemp();
	~ObjectTypesTemp() { ::delete m_types; }
	ObjectTypes *m_types;
};

// Zero Hour defines ObjectTypesTemp in ScriptConditions.cpp, and retail's
// out-of-line copy of its ctor (0x003BA7FF) belongs to that unit: the
// callers keep types.m_types in a register across the parse and isInSet
// calls (and into the destructor), which VC7.1 only does when the ctor's
// body is compiled in the same unit and so is known not to keep `this`.
ObjectTypesTemp::ObjectTypesTemp() : m_types(0)
{
	m_types = new ObjectTypes;
}

void Script_objectTypesFromParam(Parameter *pTypeParm, ObjectTypes *outObjectTypes);

class Player
{
public:
	void countObjectsByThingTemplate(int numThingTemplates, const ThingTemplate *const *things, bool ignoreDead, int *counts, bool ignoreUnderConstruction) const;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

int __cdecl Rva003BD46ESum(void *range);

class Condition
{
public:
	int getCustomData() const { return m_customData; }
	unsigned int getCustomFrame() const { return m_customFrame; }
	void setCustomData(int value) { m_customData = value; }
	void setCustomFrame(unsigned int value) { m_customFrame = value; }
private:
	unsigned char m_pad00[0x44];
	int m_customData; // +0x44
	unsigned int m_customFrame; // +0x48
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

class TeamPrototype
{
public:
	const AsciiString &getName() const { return m_name; }
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const;
private:
	unsigned char m_pad00[0x14];
	AsciiString m_name; // +0x14
	unsigned char m_pad18[0x334 - 0x18];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	const AsciiString &getState() const { return m_state; }
	const AsciiString &getName() const
	{
		return m_proto == NULL ? AsciiString::TheEmptyString : m_proto->getName();
	}
	// Zero Hour's Team::hasAnyUnits; the ledger keeps the address name.
	bool rva0039DEC4();
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
private:
	unsigned char m_pad08[0x30 - 0x08];
	TeamPrototype *m_proto; // +0x30
	unsigned char m_pad34[0x44 - 0x34];
	AsciiString m_state; // +0x44
};

inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList() const
{
	return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
}

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype(const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, bool);
	Object *getUnitNamed(Parameter *pUnitParm);
	int rva00357B82(Parameter *pPlayerParm);
	unsigned int getFrameObjectCountChanged() const { return m_frameObjectCountChanged; }
private:
	unsigned char m_pad00[0x1A15C];
	unsigned int m_frameObjectCountChanged; // +0x1A15C
};
extern ScriptEngine *TheScriptEngine;

#define THIS_TEAM "<This Team>"

class ScriptConditions
{
protected:
	bool evaluateHasUnits(Parameter *);
	bool evaluateNamedAttackedByType(Parameter *, Parameter *);
	bool evaluateTeamAttackedByType(Parameter *, Parameter *);
	bool evaluateNamedAttackedByPlayer(Parameter *, Parameter *);
	bool evaluateTeamStateIs(Parameter *, Parameter *);
	bool evaluateTeamStateIsNot(Parameter *, Parameter *);
	bool evaluateBuiltByPlayer(Condition *, Parameter *, Parameter *);
	bool evaluatePlayerUnitCondition(Condition *, Parameter *, Parameter *, Parameter *, Parameter *);
};
bool ScriptConditions::evaluateHasUnits(Parameter *pTeamParm)
{
	AsciiString desiredTeamName = pTeamParm->getString();
	// If they are calling a <this team> condition, do it.
	if (desiredTeamName.compare(THIS_TEAM) == 0) {
		Team *theTeam = TheScriptEngine->getTeamNamed(desiredTeamName, false);
		if (theTeam) {
			return (theTeam->rva0039DEC4());
		}
		return false;
	}
	Team *thisTeam = TheScriptEngine->getTeamNamed(THIS_TEAM, false);
	if (thisTeam && thisTeam->getName() == desiredTeamName) {
		return thisTeam->rva0039DEC4();
	}

	TeamPrototype *pProto = NULL;
	pProto = TheTeamFactory->findTeamPrototype(desiredTeamName);

	if (pProto) {
		for (DLINK_ITERATOR<Team> iter = pProto->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
			if (iter.cur()->rva0039DEC4()) {
				return true;
			}
		}
	}
	return false;
}
bool ScriptConditions::evaluateTeamStateIs(Parameter *pTeamParm, Parameter *pStateParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	AsciiString stateName = pStateParm->getString();
	if (theTeam) {
		return (theTeam->getState() == stateName);
	}
	return false;
}
bool ScriptConditions::evaluateTeamStateIsNot(Parameter *pTeamParm, Parameter *pStateParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	AsciiString stateName = pStateParm->getString();
	if (theTeam) {
		return (!(theTeam->getState() == stateName));
	}
	return false;
}
bool ScriptConditions::evaluateNamedAttackedByType(Parameter *pUnitParm, Parameter *pTypeParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!theObj) {
		return false;
	}

	BodyModuleInterface *theBodyModule = theObj->getBodyModule();
	if (!theBodyModule) {
		return false;
	}

	const DamageInfo *lastDamageInfo = theBodyModule->getLastDamageInfo();

	if (!lastDamageInfo) {
		return false;
	}

	ObjectID id = lastDamageInfo->in.m_sourceID;
	Object *pAttacker = TheGameLogic->findObjectByID(id);
	if (!pAttacker || !pAttacker->getTemplate()) {
		return false;
	}

	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);
	return types.m_types->isInSet(pAttacker->getTemplate()->getName());
}
bool ScriptConditions::evaluateTeamAttackedByType(Parameter *pTeamParm, Parameter *pTypeParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam) {
		return false;
	}

	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		BodyModuleInterface *theBodyModule = iter.cur()->getBodyModule();
		if (!theBodyModule) {
			continue;
		}

		const DamageInfo *lastDamageInfo = theBodyModule->getLastDamageInfo();

		if (!lastDamageInfo) {
			continue;
		}

		ObjectID id = lastDamageInfo->in.m_sourceID;
		Object *pAttacker = TheGameLogic->findObjectByID(id);
		if (!pAttacker || !pAttacker->getTemplate()) {
			continue;
		}
		if (types.m_types->isInSet(pAttacker->getTemplate()->getName())) {
			return true;
		}
	}

	return false;
}
bool ScriptConditions::evaluateNamedAttackedByPlayer(Parameter *pUnitParm, Parameter *pPlayerParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!theObj) {
		return false;
	}

	BodyModuleInterface *theBodyModule = theObj->getBodyModule();
	if (!theBodyModule) {
		return false;
	}

	const DamageInfo *lastDamageInfo = theBodyModule->getLastDamageInfo();

	if (!lastDamageInfo) {
		return false;
	}

	ObjectID id = lastDamageInfo->in.m_sourceID;
	Object *pAttacker = TheGameLogic->findObjectByID(id);
	if (!pAttacker) {
		return false;
	}
	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	while (mask) {
		Player *victimPlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (pAttacker->getControllingPlayer() == victimPlayer) {
			return true;
		}
	}
	return false;
}
bool ScriptConditions::evaluateBuiltByPlayer(Condition *pCondition, Parameter *pTypeParm, Parameter *pPlayerParm)
{
	const ThingTemplate *pTemplate = TheThingFactory->findTemplate(pTypeParm->getString());
	if (!pTemplate) {
		return false;
	}

	if (pCondition->getCustomData() != 0) {
		// We have a cached value.
		if (TheScriptEngine->getFrameObjectCountChanged() == pCondition->getCustomFrame()) {
			// object count hasn't changed.  Use cached value.
			if (pCondition->getCustomData() == 1) return true;
			if (pCondition->getCustomData() == -1) return false;
		}
	}

	_STL::vector<int> counts;
	_STL::vector<const ThingTemplate *> templates;

	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);

	int numTemplates = types.m_types->prepForPlayerCounting(templates, counts);
	if (numTemplates == 0) {
		return false;
	}

	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	while (mask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
		pPlayer->countObjectsByThingTemplate(numTemplates, &(*templates.begin()), false, &(*counts.begin()), true);
		pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
		int sumOfObjs = Rva003BD46ESum(&counts);
		if (sumOfObjs != 0) {
			pCondition->setCustomData(1); // true.
			return true;
		}
	}
	pCondition->setCustomData(-1); // false.
	return false;
}
bool ScriptConditions::evaluatePlayerUnitCondition(Condition *pCondition, Parameter *pPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm, Parameter *pUnitTypeParm)
{
	if (pCondition->getCustomData() != 0) {
		// We have a cached value.
		if (TheScriptEngine->getFrameObjectCountChanged() == pCondition->getCustomFrame()) {
			// object count hasn't changed.  Use cached value.
			if (pCondition->getCustomData() == 1) return true;
			if (pCondition->getCustomData() == -1) return false;
		}
	}

	_STL::vector<int> counts;
	_STL::vector<const ThingTemplate *> templates;

	ObjectTypesTemp types;
	Script_objectTypesFromParam(pUnitTypeParm, types.m_types);

	int numObjs = types.m_types->prepForPlayerCounting(templates, counts);
	if (numObjs == 0) {
		return false;
	}

	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	int count = 0;
	while (mask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (pPlayer) {
			pPlayer->countObjectsByThingTemplate(numObjs, &(*templates.begin()), true, &(*counts.begin()), true);
			count += Rva003BD46ESum(&counts);
		}
	}

	bool comparison = false;
	switch (pComparisonParm->getInt())
	{
		case 0: comparison = (count < pCountParm->getInt()); break;
		case 1: comparison = (count <= pCountParm->getInt()); break;
		case 2: comparison = (count == pCountParm->getInt()); break;
		case 3: comparison = (count >= pCountParm->getInt()); break;
		case 4: comparison = (count > pCountParm->getInt()); break;
		case 5: comparison = (count != pCountParm->getInt()); break;
	}

	pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
	if (comparison) {
		pCondition->setCustomData(1); // true.
		return true;
	}
	pCondition->setCustomData(-1); // false.
	return false;
}
