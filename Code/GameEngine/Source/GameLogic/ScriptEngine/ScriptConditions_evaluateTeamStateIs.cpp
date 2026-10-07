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
//
// ?evaluatePlayerLostObjectType@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E9EB0 454B
// ZH/BFME 1 donor: the same-name ScriptConditions.cpp body. Target evidence:
// jump-table case 104 calls 0x003E9EB0, which initConditionTemplates names
// PLAYER_LOST_OBJECT_TYPE. BFME 2 runs ZH's single-player body once per
// player of the mask: each player's summed count is compared with
// ScriptEngine::getObjectCount 0x00206255 and stored back through
// setObjectCount 0x00207DF4 (both index the per-player CRC maps at
// ScriptEngine+0x1A164 by Player::getPlayerIndex, +0x54); a drop returns
// true at once.
//
// ?evaluateNamedDestroyedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003EA076 180B
// BFME 1 donor: ScriptConditionsNamedByType.cpp's evaluateNamedDestroyedByType
// (its name for template NAMED_DESTROYED_BY_OBJECTTYPE). Target evidence:
// jump-table case 130 calls 0x003EA076, which initConditionTemplates names
// NAMED_DESTROYED_BY_OBJECTTYPE. It is evaluateNamedAttackedByType's chain
// with ZH's Object::isEffectivelyDead test (m_privateStatus +0x438 bit 0, as
// the rowed Object::fireCurrentWeapon unit lays it out) after the damage-info
// check.
//
// ?evaluateHasCommandPointsToBuildUnit@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E81E8 250B
// No donor body (BFME 1 leaves its case-126 body address-named). Target
// evidence: jump-table case 126 calls 0x003E81E8, which
// initConditionTemplates names HAS_COMMAND_POINTS_TO_BUILD_UNIT; the name
// follows that template as BFME 1's evaluateHasCommandPointsToBuildTeam
// follows case 125's (structural inference, not a recovered symbol). The
// body sizes the parsed ObjectTypes list inline (vector +0x08/+0x0C), takes
// the mask's single player (rowed getPlayerFromMask 0x002A7B91), queries
// that player's command points at +0x60 (rowed 0x002A7548 with 1), and
// tests each listed template, found with findTemplate on the pinned
// getNthInList 0x002041AC result, against ThingTemplate+0x618 (the cost the
// rowed 0x002A7557 adds to the points in use).
//
// ?evaluatePlayerHasKilledTypeUnits@ScriptConditions@@IAE_NPAVParameter@@00@Z @ 0x003E82E2 205B
// BFME 1 donor: ScriptConditionsPlayerHasKilledTypeUnits.cpp, same name and
// shape. Target evidence: jump-table case 129 calls 0x003E82E2, which
// initConditionTemplates names PLAYER_HAS_KILLED_TYPE_UNITS. The first
// player of the mask supplies the kill records at Player+0x3BC; a named
// ObjectTypes list (rowed ScriptEngine::getObjectTypes 0x00357651) sums the
// rowed 0x0039C0F4 count over getNthInList, otherwise the raw type name is
// counted, and the total is compared with the count parameter's getInt.
//
// ?rva003E63CD@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@11@Z @ 0x003E63CD 217B
// Target evidence: jump-table case 134 calls 0x003E63CD, which
// initConditionTemplates names COMPARISON_TREES_IN_TRIGGER_AREA (comparison,
// int, trigger area). The area comes from the rowed
// getQualifiedTriggerAreaByName 0x0035768D; the cached result is reused
// while TheTerrainLogic's +0x1910 stamp is not past the condition's custom
// frame, otherwise the rowed TerrainLogic query 0x0027F171 counts inside the
// trigger and Zero Hour's six-way comparison sets the cache. BFME 2-only
// condition with no donor body, so the method keeps an address name.
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
	int getCommandPoints() const { return m_commandPoints; }
private:
	unsigned char m_pad00[0x64];
	AsciiString m_name; // +0x64
	unsigned char m_pad68[0x618 - 0x68];
	int m_commandPoints; // +0x618
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Player *getControllingPlayer() const;
	bool isEffectivelyDead() const { return (m_privateStatus & EFFECTIVELY_DEAD) != 0; }
private:
	enum { EFFECTIVELY_DEAD = 0x01 };
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x254 - 0x08];
	BodyModuleInterface *m_body; // +0x254
	unsigned char m_pad258[0x438 - 0x258];
	unsigned char m_privateStatus; // +0x438
};

extern GameLogic *TheGameLogic;

class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	bool isInSet(const AsciiString &name) const;
	unsigned int getListSize() const { return m_objectTypes.size(); }
	AsciiString getNthInList(unsigned int index) const;
	int prepForPlayerCounting(_STL::vector<const ThingTemplate *> &templates, _STL::vector<int> &counts);
private:
	AsciiString m_listName; // +0x04
	_STL::vector<AsciiString> m_objectTypes; // +0x08
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

// Player+0x60's command-point tracker; its "available" query 0x002A7548
// returns the cap (0x002A7461) less the points in use (+0x08).
class Rva002A7461
{
public:
	int rva002A7548(int);
private:
	unsigned char m_pad00[0x08];
	int m_used; // +0x08
};

// Player+0x3BC; 0x0039C0F4 sums its per-type kill records whose name
// matches (the rowed Rva0039C0F4Sum unit).
class Rva0039C0F4
{
public:
	int rva0039C0F4(const AsciiString &objectType);
};

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
	Rva002A7461 *getCommandPoints() { return &m_commandPoints; }
	Rva0039C0F4 *getKills() { return &m_kills; }
	void countObjectsByThingTemplate(int numThingTemplates, const ThingTemplate *const *things, bool ignoreDead, int *counts, bool ignoreUnderConstruction) const;
private:
	unsigned char m_pad00[0x54];
	int m_playerIndex; // +0x54
	unsigned char m_pad58[0x60 - 0x58];
	Rva002A7461 m_commandPoints; // +0x60
	unsigned char m_pad6C[0x3BC - 0x6C];
	Rva0039C0F4 m_kills; // +0x3BC
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
	Player *getPlayerFromMask(int mask);
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

class PolygonTrigger;

// TerrainLogic (TheTerrainLogic 0x00DFEC50): +0x1910 is the frame stamp
// TerrainLogicRva00283CE7.cpp stores from TheGameLogic's frame; the rowed
// 0x0027F171 counts the grid hits inside a PolygonTrigger's radius.
class BfmeThingCME
{
public:
	int rva0027F171(PolygonTrigger *trigger);
};

class TerrainLogic
{
public:
	unsigned int getStamp() const { return m_stamp; }
	int rva0027F171(PolygonTrigger *trigger) { return reinterpret_cast<BfmeThingCME *>(this)->rva0027F171(trigger); }
private:
	unsigned char m_pad00[0x1910];
	unsigned int m_stamp; // +0x1910
};
extern TerrainLogic *TheTerrainLogic;

class ScriptEngine
{
public:
	PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
	Team *getTeamNamed(AsciiString, bool);
	Object *getUnitNamed(Parameter *pUnitParm);
	int rva00357B82(Parameter *pPlayerParm);
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);
	unsigned int getFrameObjectCountChanged() const { return m_frameObjectCountChanged; }
	int getObjectCount(int playerIndex, const AsciiString &objectTypeName) const;
	void setObjectCount(int playerIndex, const AsciiString &objectTypeName, int newCount);
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
	bool evaluatePlayerLostObjectType(Parameter *, Parameter *);
	bool evaluateNamedDestroyedByType(Parameter *, Parameter *);
	bool evaluateHasCommandPointsToBuildUnit(Parameter *, Parameter *);
	bool evaluatePlayerHasKilledTypeUnits(Parameter *, Parameter *, Parameter *);
	bool rva003E63CD(Condition *, Parameter *, Parameter *, Parameter *);
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
bool ScriptConditions::evaluatePlayerLostObjectType(Parameter *pPlayerParm, Parameter *pTypeParm)
{
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
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
			player->countObjectsByThingTemplate(numTemplates, &(*templates.begin()), true, &(*counts.begin()), true);

			int sumOfObjs = Rva003BD46ESum(&counts);
			int currentCount = TheScriptEngine->getObjectCount(player->getPlayerIndex(), pTypeParm->getString());

			if (sumOfObjs != currentCount) {
				TheScriptEngine->setObjectCount(player->getPlayerIndex(), pTypeParm->getString(), sumOfObjs);
			}

			if (sumOfObjs < currentCount) {
				return true;
			}
		}
	}
	return false;
}
bool ScriptConditions::evaluateNamedDestroyedByType(Parameter *pUnitParm, Parameter *pTypeParm)
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

	if (!theObj->isEffectivelyDead()) {
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
bool ScriptConditions::evaluateHasCommandPointsToBuildUnit(Parameter *pPlayerParm, Parameter *pTypeParm)
{
	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);

	unsigned int numTypes = types.m_types->getListSize();
	if (numTypes == 0) {
		return false;
	}

	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	if (!mask) {
		return false;
	}

	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (!player) {
		return false;
	}

	int available = player->getCommandPoints()->rva002A7548(1);
	for (unsigned int i = 0; i < numTypes; ++i) {
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(types.m_types->getNthInList(i));
		if (thingTemplate && available <= thingTemplate->getCommandPoints()) {
			return true;
		}
	}
	return false;
}
bool ScriptConditions::evaluatePlayerHasKilledTypeUnits(Parameter *pPlayerParm, Parameter *pCountParm, Parameter *pTypeParm)
{
	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
	if (thePlayer) {
		Rva0039C0F4 *kills = thePlayer->getKills();
		if (kills) {
			ObjectTypes *types = TheScriptEngine->getObjectTypes(pTypeParm->getString());
			int total = 0;
			if (types) {
				for (unsigned int typeIndex = 0; typeIndex < types->getListSize(); ++typeIndex) {
					AsciiString typeName = types->getNthInList(typeIndex);
					total += kills->rva0039C0F4(typeName);
				}
			} else {
				total = kills->rva0039C0F4(pTypeParm->getString());
			}
			return total >= pCountParm->getInt();
		}
	}
	return false;
}

bool ScriptConditions::rva003E63CD(Condition *pCondition, Parameter *pComparisonParm, Parameter *pCountParm, Parameter *pTriggerParm)
{
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());
	if (!pTrig)
		return false;
	if (TheTerrainLogic->getStamp() <= pCondition->getCustomFrame()) {
		if (pCondition->getCustomData() == -1)
			return false;
		if (pCondition->getCustomData() == 1)
			return true;
	}
	int count = TheTerrainLogic->rva0027F171(pTrig);
	bool comparison = false;
	switch (pComparisonParm->getInt()) {
		case 0: comparison = count < pCountParm->getInt(); break;
		case 1: comparison = count <= pCountParm->getInt(); break;
		case 2: comparison = count == pCountParm->getInt(); break;
		case 3: comparison = count >= pCountParm->getInt(); break;
		case 4: comparison = count > pCountParm->getInt(); break;
		case 5: comparison = count != pCountParm->getInt(); break;
	}
	pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
	if (comparison) {
		pCondition->setCustomData(1);
		return true;
	}
	pCondition->setCustomData(-1);
	return false;
}
