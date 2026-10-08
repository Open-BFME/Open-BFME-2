// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// 0x003CA418 (166B, WB 0x0101A240) sorts a living-world player's armies by
// their +0x20 id and sets an army reference to the n-th one that has a name.
// 0x003C6279 (123B, WB 0x0101A170) sets an int reference to the +0x14 id
// of the living-world player whose +0x40 name matches, or -1.
// Also two unnamed WorldBuilder members on the same region and army
// references: 0x003C3943 (117B, WB 0x0101A3A0) stores the name of the region
// an army is in, and 0x003C39B8 (135B, WB 0x0101A6F0) moves an army to a
// region (0x002B2702 with 1).
//
// ScriptActions::doLivingWorldSetRegionRefToAdjacentRegion, retail 0x003C6871
// (258B), from WorldBuilder's ScriptActions.cpp (debug build, name, statement
// order, the "ListAllAdjacentRegions" assertion at line 11840).
//
// Target facts: two script-engine region-reference lookups (0x00208DB8, by
// value), the region manager at g_009FEF10+0xB0 resolving the source region
// (0x002104B6), listing its adjacent region ids into a local vector<int>
// (0x0020FD42) and resolving each id (0x0020EAF6); +0x13C is compared between
// regions and 0x003F036E is the second filter.
//
// The search loop never advances its iterator, in WorldBuilder as in retail:
// once a candidate is found it spins, so cl drops the final reference
// assignment (it is reachable only with an empty list, where nothing is
// found). Retail is the result of compiling that loop as written.
//
// ScriptActions::doCreateUnitRevivalEntry, retail 0x003C62F4 (323B; ret 0xC),
// from WorldBuilder's ScriptActions.cpp twin (wb 0x0101B750; name, parameter
// and statement order; its unknown-type, no-player and no-tracker branches
// only log). Target facts: the template by name (pinned findTemplate
// 0x002D06CA), the player through the rowed mask lookups, the tracker at
// player+0x738 (WB +0x740), and a 0xD8-byte revival record (pinned ctor
// 0x0037E289, dtor 0x001EB63C) whose +0x08/+0x0C/+0x10 get the level's
// required experience and rank twice, or the template's own rank (pinned
// 0x0033B479) when no level is given or the store (g_00DFECC4) has none.
//
// ScriptActions::doCreateUnitRevivalEntryFromDelayedCarryoverHero, retail
// 0x003CA14C (347B; ret 8), from WorldBuilder's twin (wb 0x0101B0E0; name,
// statement order, ArmySummary::SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker):
// the action side of ScriptConditions_delayedCarryover.cpp's condition, with
// its views. A running linear campaign hands the types, tracker and player to
// the campaign manager (pinned 0x001EC9AC, result only logged in WB);
// otherwise the first army of the selected players that spawns one delayed
// carryover unit of the types ends the search.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"
#include <vector>
#include <algorithm>

class Rva0020E89C;
struct Rva002B488EResult;
class Rva0040D701ArmySummary;

class Rva002104B6
{
public:
	void *rva002104B6(void *name);
};

class Rva0020FD42
{
public:
	void rva0020FD42(void *region, void *ids);
};

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
};

class LivingWorldRegionFilterView
{
public:
	bool rva003F036E();
};

struct LivingWorldRegionView
{
	unsigned char m_pad00[0x14];
	AsciiString m_name;
	unsigned char m_pad18[0x13C - 0x18];
	int m_13C;
};

class Rva002BA8F1Logic
{
public:
	Rva002B488EResult *rva002B488E(int armyID);
	class Rva002E2903Player *find(int id, unsigned int *outIndex);
	class Rva002E2903Player *rva002B52A8(int index);
	void rva002B323C(_STL::vector<Rva0040D701ArmySummary *> *armies, int armyID);
	int getPlayerCount() const { return m_players.size(); }
	void *getRegionManager() const { return m_regionManager; }

private:
	unsigned char m_pad00[0x8C];
	_STL::vector<class Rva002E2903Player *> m_players;
	unsigned char m_pad98[0xB0 - 0x98];
	void *m_regionManager;
};

class ThingTemplate
{
public:
	int rva0033B479() const;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

class Player;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

// ExperienceLevelSystem.cpp's handle: list and iterator, passed by value.
class ExperienceLevelList;
class ExperienceLevelIterator
{
public:
	ExperienceLevelIterator() {}
	ExperienceLevelIterator(const ExperienceLevelIterator &that) : m_node(that.m_node) {}

private:
	void *m_node;
};

struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelHandle(const ExperienceLevelHandle &that) : m_list(that.m_list), m_iter(that.m_iter) {}
	bool isValid() const { return m_list != 0; }

	ExperienceLevelList *m_list;
	ExperienceLevelIterator m_iter;
};

class ExperienceLevelStore
{
public:
	int GetLevelRank(ExperienceLevelHandle levelHandle) const;
	int GetRequiredExperience(ExperienceLevelHandle levelHandle) const;
	ExperienceLevelHandle rva00288E21(const ThingTemplate *thingTemplate, int level) const;
};
extern ExperienceLevelStore *g_00DFECC4;

// The 0xD8-byte revival record (WB UnitRevivalEntry) built from a template.
struct Rva002E2D10Record
{
	Rva002E2D10Record(const ThingTemplate *thingTemplate);
	~Rva002E2D10Record();

	unsigned char m_pad00[0x08];
	float m_requiredExperience;	// +0x08
	int m_rank;			// +0x0C
	int m_levelRank;		// +0x10
	unsigned char m_pad14[0xD8 - 0x14];
};

class UnitRevivalTracker
{
public:
	void addRevivableUnit(const Rva002E2D10Record &entry, Player *player);
};

class Player
{
public:
	UnitRevivalTracker *getUnitRevivalTracker() { return &m_unitRevivalTracker; }
	int getArmyID() const { return m_armyID; }

private:
	unsigned char m_pad00[0x3AC];
	int m_armyID;
	unsigned char m_pad3B0[0x738 - 0x3B0];
	UnitRevivalTracker m_unitRevivalTracker;
};

class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	int getListSize() const { return m_objectTypes.size(); }
	void addObjectType(const AsciiString &objectType);

private:
	AsciiString m_listName;
	_STL::vector<AsciiString> m_objectTypes;
};

class LinearCampaignManager
{
public:
	bool hasCampaign() const { return m_campaign != 0; }
	bool rva001EC9AC(ObjectTypes *types, UnitRevivalTracker *tracker, Player *player);

private:
	unsigned char m_pad00[0x10];
	void *m_campaign;
};
extern LinearCampaignManager *TheLinearCampaignManager;

// WorldBuilder's ArmySummary (address-derived spelling as in
// ScriptConditions_delayedCarryover.cpp).
class Rva0040D701ArmySummary
{
public:
	bool SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker(ObjectTypes *types);
};

class ScriptEngine
{
public:
	int rva00357475(const AsciiString &name, bool *matchedSpecialName);
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);
	AsciiString *rva00208DB8(AsciiString name);
	int *rva00208E99(AsciiString name);
	int *rva00208CF0(AsciiString name);
};

struct Rva002B488EResult;
class Rva00318C32Ret;

class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();
};

class Rva002B2702
{
public:
	void rva002B2702(void *army, void *region, int arg);
};

class Rva00329EE9StringValue
{
public:
	bool isEmpty() const;
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doLivingWorldSetRegionRefToAdjacentRegion(const AsciiString &destRefName,
		const AsciiString &srcRefName, bool skipMatching13C, bool skipFiltered);
	void rva003CA418(const AsciiString &armyRefName, int n, const AsciiString &playerRefName);
	void rva003C6279(const AsciiString &refName, const AsciiString &playerName);
	void rva003C3943(const AsciiString &regionRefName, const AsciiString &armyRefName);
	void rva003C39B8(const AsciiString &armyRefName, const AsciiString &regionRefName);
	void doCreateUnitRevivalEntry(const AsciiString &objectTypeName, const AsciiString &playerName, int level);
	void doCreateUnitRevivalEntryFromDelayedCarryoverHero(const AsciiString &objectTypeName, const AsciiString &playerName);
};

void ScriptActions::doLivingWorldSetRegionRefToAdjacentRegion(const AsciiString &destRefName,
	const AsciiString &srcRefName, bool skipMatching13C, bool skipFiltered)
{
	AsciiString *destRef = TheScriptEngine->rva00208DB8(destRefName);
	AsciiString *srcRef = TheScriptEngine->rva00208DB8(srcRefName);
	LivingWorldRegionView *srcRegion = (LivingWorldRegionView *)
		((Rva002104B6 *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getRegionManager())->rva002104B6(srcRef);
	destRef->clear();
	if (!srcRegion)
		return;

	_STL::vector<int> ids;
	((Rva0020FD42 *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getRegionManager())->rva0020FD42(srcRegion, &ids);
	LivingWorldRegionView *found = 0;
	_STL::vector<int>::iterator it = ids.begin();
	_STL::vector<int>::iterator end = ids.end();
	while (it != end) {
		if (!found) {
			LivingWorldRegionView *region = (LivingWorldRegionView *)
				((Rva0020EAF6View *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getRegionManager())->rva0020EAF6(*it);
			if (region) {
				bool ok = true;
				if (skipMatching13C && region->m_13C == srcRegion->m_13C)
					ok = false;
				if (ok && skipFiltered && ((LivingWorldRegionFilterView *)region)->rva003F036E())
					ok = false;
				if (ok)
					found = region;
			}
		}
	}
	if (found)
		*destRef = found->m_name;
}

void ScriptActions::rva003C3943(const AsciiString &regionRefName, const AsciiString &armyRefName)
{
	AsciiString *regionRef = TheScriptEngine->rva00208DB8(regionRefName);
	int *armyRef = TheScriptEngine->rva00208E99(armyRefName);
	Rva002B488EResult *army = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B488E(*armyRef);
	if (!army) {
		regionRef->clear();
		return;
	}
	LivingWorldRegionView *region = (LivingWorldRegionView *)((Rva00318C79Owner *)army)->rva00318C32();
	const AsciiString &name = region ? region->m_name : AsciiString::TheEmptyString;
	*regionRef = name;
}

void ScriptActions::rva003C39B8(const AsciiString &armyRefName, const AsciiString &regionRefName)
{
	AsciiString *regionRef = TheScriptEngine->rva00208DB8(regionRefName);
	int armyID = *TheScriptEngine->rva00208E99(armyRefName);
	if (armyID == 0 || ((Rva00329EE9StringValue *)regionRef)->isEmpty())
		return;
	Rva002B488EResult *army = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B488E(armyID);
	if (!army)
		return;
	void *region = ((Rva002104B6 *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getRegionManager())->rva002104B6(regionRef);
	if (region)
		((Rva002B2702 *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->rva002B2702(army, region, 1);
}

struct Rva003C3AB0Item
{
	unsigned char m_pad00[0x18];
	AsciiString m_name;
	unsigned char m_pad1C[0x20 - 0x1C];
	int m_20;
};

struct Rva003C3AB0Cmp
{
	bool operator()(const Rva003C3AB0Item *a, const Rva003C3AB0Item *b) const { return a->m_20 < b->m_20; }
};

class Rva002E2903Player
{
public:
	unsigned char m_pad00[0x14];
	int m_id;
	unsigned char m_pad18[0x40 - 0x18];
	const AsciiString *m_name;
	unsigned char m_pad44[0x1B8 - 0x44];
	_STL::vector<Rva003C3AB0Item *> m_armies;
};

void ScriptActions::rva003C6279(const AsciiString &refName, const AsciiString &playerName)
{
	int *ref = TheScriptEngine->rva00208CF0(refName);
	int count = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getPlayerCount();
	for (int i = 0; i < count; ++i) {
		Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B52A8(i);
		if (player && player->m_name->compare(playerName) == 0) {
			*ref = player->m_id;
			return;
		}
	}
	*ref = -1;
}

void ScriptActions::rva003CA418(const AsciiString &armyRefName, int n, const AsciiString &playerRefName)
{
	int *armyRef = TheScriptEngine->rva00208E99(armyRefName);
	*armyRef = 0;
	int *playerRef = TheScriptEngine->rva00208CF0(playerRefName);
	Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(*playerRef, 0);
	if (!player)
		return;
	_STL::vector<Rva003C3AB0Item *> &armies = player->m_armies;
	_STL::sort(armies.begin(), armies.end(), Rva003C3AB0Cmp());
	_STL::vector<Rva003C3AB0Item *>::iterator it = armies.begin();
	_STL::vector<Rva003C3AB0Item *>::iterator end = armies.end();
	for (; it != end; ++it) {
		if (!((Rva00329EE9StringValue *)&(*it)->m_name)->isEmpty())
			--n;
		if (n <= 0)
			break;
	}
	if (it != end)
		*armyRef = (*it)->m_20;
}

void ScriptActions::doCreateUnitRevivalEntry(const AsciiString &objectTypeName, const AsciiString &playerName, int level)
{
	const ThingTemplate *objectType = TheThingFactory->findTemplate(objectTypeName);
	if (!objectType)
		return;
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	Player *player = ThePlayerList->getEachPlayerFromMask(mask);
	if (!player)
		return;
	UnitRevivalTracker *tracker = player->getUnitRevivalTracker();
	if (!tracker)
		return;
	Rva002E2D10Record entry(objectType);
	if (level == -1) {
		entry.m_rank = objectType->rva0033B479();
	} else {
		ExperienceLevelHandle levelHandle = g_00DFECC4->rva00288E21(objectType, level);
		if (levelHandle.isValid()) {
			entry.m_requiredExperience = (float)g_00DFECC4->GetRequiredExperience(levelHandle);
			entry.m_rank = g_00DFECC4->GetLevelRank(levelHandle);
			entry.m_levelRank = g_00DFECC4->GetLevelRank(levelHandle);
		} else {
			entry.m_rank = objectType->rva0033B479();
		}
	}
	tracker->addRevivableUnit(entry, player);
}

void ScriptActions::doCreateUnitRevivalEntryFromDelayedCarryoverHero(const AsciiString &objectTypeName,
	const AsciiString &playerName)
{
	ObjectTypes tempTypes;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectTypeName);
	if (!types || types->getListSize() == 0) {
		tempTypes.addObjectType(objectTypeName);
		types = &tempTypes;
	}
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	if (TheLinearCampaignManager && TheLinearCampaignManager->hasCampaign()) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
			UnitRevivalTracker *tracker = player->getUnitRevivalTracker();
			if (tracker)
				TheLinearCampaignManager->rva001EC9AC(types, tracker, player);
		}
	} else if (TheLivingWorldLogic) {
		while (mask) {
			Player *player = ThePlayerList->getEachPlayerFromMask(mask);
			if (!player)
				continue;
			int armyID = player->getArmyID();
			if (armyID == -1)
				continue;
			_STL::vector<Rva0040D701ArmySummary *> armies;
			(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B323C(&armies, armyID);
			_STL::vector<Rva0040D701ArmySummary *>::iterator it = armies.begin();
			_STL::vector<Rva0040D701ArmySummary *>::iterator end = armies.end();
			for (; it != end; ++it) {
				if ((*it)->SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker(types))
					return;
			}
		}
	}
}
