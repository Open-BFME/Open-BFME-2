// cl: /G7 /arch:SSE /I. /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
// value), the region manager at TheLivingWorldLogic+0xB0 resolving the source region
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
// 0x0033B479) when no level is given or the store (TheExperienceLevelSystem) has none.
//
// ScriptActions::doCreateUnitRevivalEntryFromDelayedCarryoverHero, retail
// 0x003CA14C (347B; ret 8), from WorldBuilder's twin (wb 0x0101B0E0; name,
// statement order, ArmySummary::SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker):
// the action side of ScriptConditions_delayedCarryover.cpp's condition, with
// its views. A running linear campaign hands the types, tracker and player to
// the campaign manager (pinned 0x001EC9AC, result only logged in WB);
// otherwise the first army of the selected players that spawns one delayed
// carryover unit of the types ends the search.
//
// ScriptActions::doCreateDelayedCarryoverUnitAtWaypoint, retail 0x003C9F4B
// (513B; ret 0x10), from WorldBuilder's twin (wb 0x0101A8C0; name, statement
// order, ArmySummary::SpawnOneDelayedCarryoverUnit): the same type list and
// player selection, but the campaign manager (pinned 0x001EC99B) or the first
// army that spawns one (pinned 0x0040E589) yields an ObjectID; the object is
// placed at the waypoint (TerrainLogic slot 0x88, location +0x0C) and, when a
// unit name is given, named and cached as in createUnitOnTeamAt.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"
#include <vector>
#include <algorithm>
// vector<int> teardown otherwise instantiates per-TU allocator deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external
// copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int* __p, size_t __n) {
    __stl_alloc_rebind(__STATIC_CAST(allocator<int>&, *this),(int*)0).deallocate(__p, __n);
}
template <> __declspec(dllimport) __forceinline
_Vector_base<int, allocator<int> >::~_Vector_base() {
    if (_M_start !=0)
    _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
}
}
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

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

// The region predicate is rowed as Rva003F02E4::rva003F036E (int); retail's
// caller tests al.
class Rva003F02E4
{
public:
	int rva003F036E();
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
	class Rva002E2903Player *GetPlayerAtIndex(int index);
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
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

// The 0xD8-byte revival record built from a template (the rowed
// UnitRevivalEntry constructor 0x0037E289 and destructor 0x001EB63C).
struct Rva002E2D10Record;
struct UnitRevivalEntry
{
	UnitRevivalEntry(const ThingTemplate *thingTemplate);
	~UnitRevivalEntry();

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

private:
	unsigned char m_pad00[0x10];
	void *m_campaign;
};
extern LinearCampaignManager *TheLinearCampaignManager;

// ObjectTypes::addObjectType is rowed in GameLogic/Object/ObjectTypes.cpp; the
// campaign forwarders under their address classes
// (VslotNullCheckedForwarders3.cpp).
class Rva001EC9AC
{
public:
	bool rva001EC9AC(int types, int tracker, int player);
};
class Rva001EC99B
{
public:
	void *rva001EC99B(int types, int player);
};

// WorldBuilder's ArmySummary (address-derived spelling as in
// ScriptConditions_delayedCarryover.cpp).
class ObjectTypes;
// 0x0040E589 is rowed as ArmySummary::SpawnOneDelayedCarryoverUnit.
class ArmySummary { public: ObjectID SpawnOneDelayedCarryoverUnit(ObjectTypes *types); bool SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker(ObjectTypes *types); };

class Rva0040D701ArmySummary;

struct Coord3D;

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
public:
	void setName(const AsciiString &name) { m_name = name; }

private:
	unsigned char m_pad00[0x88];
	AsciiString m_name;
};

extern GameLogic *TheGameLogic;

class Waypoint
{
public:
	const Coord3D *getLocation() const { return (const Coord3D *)m_location; }

private:
	unsigned char m_pad[0x0C];
	unsigned char m_location[0x0C];
};

class TerrainLogic
{
public:
#define TERRAIN_SLOT(n) virtual void slot##n();
	TERRAIN_SLOT(0) TERRAIN_SLOT(1) TERRAIN_SLOT(2) TERRAIN_SLOT(3) TERRAIN_SLOT(4)
	TERRAIN_SLOT(5) TERRAIN_SLOT(6) TERRAIN_SLOT(7) TERRAIN_SLOT(8) TERRAIN_SLOT(9)
	TERRAIN_SLOT(10) TERRAIN_SLOT(11) TERRAIN_SLOT(12) TERRAIN_SLOT(13) TERRAIN_SLOT(14)
	TERRAIN_SLOT(15) TERRAIN_SLOT(16) TERRAIN_SLOT(17) TERRAIN_SLOT(18) TERRAIN_SLOT(19)
	TERRAIN_SLOT(20) TERRAIN_SLOT(21) TERRAIN_SLOT(22) TERRAIN_SLOT(23) TERRAIN_SLOT(24)
	TERRAIN_SLOT(25) TERRAIN_SLOT(26) TERRAIN_SLOT(27) TERRAIN_SLOT(28) TERRAIN_SLOT(29)
	TERRAIN_SLOT(30) TERRAIN_SLOT(31) TERRAIN_SLOT(32) TERRAIN_SLOT(33)
#undef TERRAIN_SLOT
	virtual Waypoint *getWaypointByName(const AsciiString &name); // slot 0x88
};
extern TerrainLogic *TheTerrainLogic;

#include "../../../Include/GameLogic/ScriptEngine.h"

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


// ZH Scripts.h accessor semantics; native3CA4BE proves BFME2 offsets.
// Keep both visible accessors: native inlining stops at the first large case.
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/Libraries/Include/Lib/RGBColor.h"
enum EmotionType { EMOTION_INVALID = -1 };
enum ObjectStatusTypes { OBJECT_STATUS_INVALID = -1 };
class Parameter
{
public:
    // Every call inlines; dllimport stops the TU emitting an unreferenced copy.
    __declspec(dllimport) __forceinline int getInt() const { return m_int; }
    float getReal() const { return m_real; }
    const AsciiString &getString() const { return m_string; }
    void getCoord3D(Coord3D *) const;
private:
    int m_type;
    bool m_initialized;
    int m_int;
    float m_real;
    AsciiString m_string;
    Coord3D m_coord;
};
class ScriptAction
{
public:
    __forceinline Parameter *getParameterInline(int index) {
        if (index >= 0 && index < m_numParms)
            return m_parms[index];
        return 0;
    }
    int getActionType() const { return m_type; }
    bool isEnabled() const { return m_enabled; }
    __declspec(noinline) Parameter *getParameter(int index) {
        if (index >= 0 && index < m_numParms)
            return m_parms[index];
        return 0;
    }
private:
    void *m_vtable;
    int m_type;
    int m_numParms;
    Parameter *m_parms[12];
    unsigned char m_pad3c[5];
    bool m_enabled;
};

class Team;
extern int BfmeLogicFramesPerSecond; // canonical signed32 timing owner at target VA 0x00DBA4E4; reconciled in round2
double __cdecl Rva000422BBCeil(float);
class ScriptActionViewSlots { public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31(float, float, float);
    virtual void slot32(int);
    virtual void slot33(int);
    virtual void slot34(float, float, float);
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45(int);
    virtual void slot46();
    virtual void slot47(int);
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56(int);
};
class ScriptActionAudioSlots { public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16(int, int, int);
    virtual void slot17(int, int, int);
};
class ScriptActionWindowSlots { public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16(bool);
};
class ScriptActionGameEngineSlots { public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18(int);
};
class View; extern View *TheTacticalView;
class AudioManager; extern AudioManager *TheAudio;
class GlobalData; extern GlobalData *TheWritableGlobalData;
class Radar; extern Radar *TheRadar;
class GameEngine; extern GameEngine *TheGameEngine;
class GameClient; extern GameClient *TheGameClient;
struct ScriptActionGlobalData {
    unsigned char m_pad00[0x26]; bool m_flag26;
    unsigned char m_pad27; int m_value28;
    unsigned char m_pad2C[0x950-0x2C]; float m_value950;
    unsigned char m_pad954[0xD40-0x954]; float m_valueD40;
};
struct ScriptActionRadarFlags { unsigned char m_pad00[0x11]; bool m_flag11; };
class Rva00239A40 { public: void rva00239A40(AsciiString); };
void __cdecl HideControlBar(bool);
void __cdecl ShowControlBar(bool);
void __cdecl Rva004E400DEnable();

class Rva003BD598 { public: void rva003BD598(); };
class Rva003BE5C9 { public: void rva003BE5C9(); void rva003C3B4A(); };
class Rva003BE6CB { public: void rva003BE6CB(); };
class Rva003BE7ED { public: void rva003BE7ED(); };
class Rva003BBAD3 { public: void rva003BBAD3(); };
class Rva003C08CC { public: void rva003C08CC(class AsciiString const *, bool); };
class Rva003BC392Holder { public: void set(bool); };
class Rva003C1E69 { public: class Team * rva003C1E69(class AsciiString const &, class AsciiString const &); };
class Rva003C1FDE { public: void rva003C1FDE(class AsciiString const &, bool); };
#include "Code/GameEngine/Include/GameLogic/ScriptActionsBFME2.h"

void ScriptActions::doLivingWorldSetRegionRefToAdjacentRegion(const AsciiString &destRefName,
	const AsciiString &srcRefName, bool skipMatching13C, bool skipFiltered)
{
	AsciiString *destRef = (AsciiString *)TheScriptEngine->rva00208DB8(destRefName);
	AsciiString *srcRef = (AsciiString *)TheScriptEngine->rva00208DB8(srcRefName);
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
				if (ok && skipFiltered && (char)((Rva003F02E4 *)region)->rva003F036E())
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
	AsciiString *regionRef = (AsciiString *)TheScriptEngine->rva00208DB8(regionRefName);
	int *armyRef = (int *)TheScriptEngine->rva00208E99(armyRefName);
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
	AsciiString *regionRef = (AsciiString *)TheScriptEngine->rva00208DB8(regionRefName);
	int armyID = *(int *)TheScriptEngine->rva00208E99(armyRefName);
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
	int *ref = (int *)TheScriptEngine->rva00208CF0(refName);
	int count = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getPlayerCount();
	for (int i = 0; i < count; ++i) {
		Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->GetPlayerAtIndex(i);
		if (player && player->m_name->compare(playerName) == 0) {
			*ref = player->m_id;
			return;
		}
	}
	*ref = -1;
}

void ScriptActions::rva003CA418(const AsciiString &armyRefName, int n, const AsciiString &playerRefName)
{
	int *armyRef = (int *)TheScriptEngine->rva00208E99(armyRefName);
	*armyRef = 0;
	int *playerRef = (int *)TheScriptEngine->rva00208CF0(playerRefName);
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
	UnitRevivalEntry entry(objectType);
	if (level == -1) {
		entry.m_rank = objectType->rva0033B479();
	} else {
		ExperienceLevelHandle levelHandle = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->rva00288E21(objectType, level);
		if (levelHandle.isValid()) {
			entry.m_requiredExperience = (float)reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetRequiredExperience(levelHandle);
			entry.m_rank = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetLevelRank(levelHandle);
			entry.m_levelRank = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetLevelRank(levelHandle);
		} else {
			entry.m_rank = objectType->rva0033B479();
		}
	}
	tracker->addRevivableUnit(*(const Rva002E2D10Record *)&entry, player);
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
				((Rva001EC9AC *)TheLinearCampaignManager)->rva001EC9AC((int)types, (int)tracker, (int)player);
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
				if (((ArmySummary *)*it)->SpawnOneDelayedCarryoverUnitIntoUnitRevivalTracker(types))
					return;
			}
		}
	}
}

void ScriptActions::doCreateDelayedCarryoverUnitAtWaypoint(const AsciiString &objectTypeName,
	const AsciiString &playerName, const AsciiString &waypointName, const AsciiString &unitName)
{
	ObjectTypes tempTypes;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectTypeName);
	if (!types || types->getListSize() == 0) {
		tempTypes.addObjectType(objectTypeName);
		types = &tempTypes;
	}
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	if (!way)
		return;
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	ObjectID result = INVALID_OBJECT_ID;
	if (TheLinearCampaignManager && TheLinearCampaignManager->hasCampaign()) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (!player)
			return;
		result = (ObjectID)(int)((Rva001EC99B *)TheLinearCampaignManager)->rva001EC99B((int)types, (int)player);
	} else {
		if (!TheLivingWorldLogic)
			return;
		while (result == INVALID_OBJECT_ID && mask) {
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
			for (; result == INVALID_OBJECT_ID && it != end; ++it)
				result = ((ArmySummary *)*it)->SpawnOneDelayedCarryoverUnit(types);
		}
	}
	if (result == INVALID_OBJECT_ID)
		return;
	Object *obj = TheGameLogic->findObjectByID(result);
	if (!obj)
		return;
	obj->setPosition(way->getLocation());
	if (unitName != AsciiString::TheEmptyString) {
		obj->setName(unitName);
		if (TheScriptEngine->didUnitExist(unitName))
			TheScriptEngine->rva00357960(unitName, obj);
		else
			TheScriptEngine->addObjectToCache(obj, "");
	}
}

// BFME2 executeAction at RVA 0x003CA4BE, WB 0x0101C3C0.
// ZH ScriptActions.cpp guides parameter/call semantics; numeric case labels
// and argument ordering below come from retail, not donor enum values.


// ScriptActions::executeAction: native003CA4BE..003CF6B7 (20985 bytes).
// WB101C3C0 independently names the dispatcher and supplies its control flow;
// ZH ScriptActions.cpp/Scripts.h at BFME1 cee35b7d8 are the semantic guide.
// Native offsets, enums, argument contracts and599 switch entries are verified.
// Implicit empty-string conversion in208 preserves temporary stack lifetimes.
// Selected break exits preserve native shared tails; PLAYBOOK compiler barriers
// keep separate action paths and their common final return from coalescing.
// These barriers emit no instructions; the full body/table and EH are gated.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#define TEXT(n) (pAction->getParameter(n)->getString())
#define INTEGER(n) (pAction->getParameter(n)->getInt())
#define REAL(n) (pAction->getParameter(n)->getReal())
#define PARAM(n) (pAction->getParameter(n))
#define INLINE_TEXT(n) (pAction->getParameterInline(n)->getString())
#define INLINE_INTEGER(n) (pAction->getParameterInline(n)->getInt())
#define INLINE_REAL(n) (pAction->getParameterInline(n)->getReal())
#define INLINE_PARAM(n) (pAction->getParameterInline(n))
void ScriptActions::executeAction(ScriptAction *pAction)
{
if (!pAction->isEnabled())
return;
switch (pAction->getActionType()) {
case 386:
{
doBuildBuildingOnFoundation(INLINE_TEXT(0), *(AsciiString const *)(INLINE_PARAM(1)));
return;
}
case 0:
{
TheScriptEngine->AppendDebugMessage(INLINE_TEXT(0), true);
return;
}
case 104:
{
TheScriptEngine->AppendDebugMessage(INLINE_TEXT(0), false);
return;
}
case 12:
{
doDamageTeamMembers(INLINE_TEXT(0), INLINE_REAL(1));
return;
}
case 13:
{
Rva003BEA10Do(&INLINE_TEXT(0), (void *)(&INLINE_TEXT(1)));
return;
}
case 544:
{
Rva003BEB01Do(&INLINE_TEXT(0), (void *)(&INLINE_TEXT(1)));
return;
}
case 564:
{
rva003C7914(INLINE_TEXT(0), INLINE_PARAM(1));
return;
}
case 455:
{
Rva003BEBD6Do(&INLINE_TEXT(0));
return;
}
case 38:
{
Rva003C7A30Do(INLINE_PARAM(0), (int)(&INLINE_TEXT(1)));
return;
}
case 546:
{
Rva003C7AF3Do(INLINE_PARAM(0), (int)(&INLINE_TEXT(1)));
return;
}
case 37:
{
doSetTeamState(INLINE_TEXT(0), INLINE_TEXT(1));
return;
}
case 490:
{
Rva003BECCDSet(INLINE_TEXT(0), INLINE_TEXT(1), (INLINE_INTEGER(2) != 0));
return;
}
case 36:
{
doTeamFollowWaypoints(INLINE_TEXT(0), INLINE_TEXT(1), (INLINE_INTEGER(2) != 0), (INLINE_INTEGER(3) != 0));
return;
}
case 545:
{
doTeamAttackMoveFollowWaypoints(INLINE_TEXT(0), INLINE_TEXT(1), (INLINE_INTEGER(2) != 0), (INLINE_INTEGER(3) != 0));
return;
}
case 285:
{
doTeamFollowWaypointsExact(INLINE_TEXT(0), (int)(&INLINE_TEXT(1)), (INLINE_INTEGER(2) != 0));
return;
}
case 286:
{
doNamedAttackFollowWaypoints(INLINE_PARAM(0), INLINE_TEXT(1));
return;
}
case 249:
{
doTeamFollowSkirmishApproachPath(INLINE_TEXT(0), INLINE_TEXT(1), (INLINE_INTEGER(2) != 0));
return;
}
case 253:
{
doTeamMoveToSkirmishApproachPath(INLINE_TEXT(0), INLINE_TEXT(1));
return;
}
case 34:
{
doCreateReinforcements(INLINE_TEXT(0), INLINE_TEXT(1), false);
return;
}
case 444:
{
doCreateReinforcements(INLINE_TEXT(0), INLINE_TEXT(1), true);
return;
}
case 499:
{
doNamedSetTeam(INLINE_PARAM(0), INLINE_TEXT(1));
return;
}
case 290:
{
Rva003BB163Set(INLINE_TEXT(0), (int)(&INLINE_TEXT(1)));
return;
}
case 419:
{
Rva003BB1A4Grant(INLINE_TEXT(0), INLINE_TEXT(1));
return;
}
case 180:
{
Rva003BF9FADo(INLINE_TEXT(0), INLINE_REAL(1), AsciiString::TheEmptyString);
return;
}
case 181:
{
Rva003BF9FADo(INLINE_TEXT(0), INLINE_REAL(1), INLINE_TEXT(2));
return;
}
case 7:
{
doPlaySoundEffect(INLINE_TEXT(0));
return;
}
case 417:
{
Rva003BA96F(INLINE_REAL(0), INLINE_REAL(1), INLINE_REAL(2), INLINE_REAL(3), INLINE_REAL(4));
return;
}
case 441:
{
Rva003BA9AF((int)(&TEXT(0)));
return;
}
case 442:
{
Rva003BA9CA((int)(&TEXT(0)));
return;
}
case 443:
{
Rva003BA9E5();
return;
}
case 437:
{
Rva003BA9FA(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 438:
{
Rva003BAA2D(REAL(0));
return;
}
case 14:
{
Rva003BAAE4(TEXT(0), REAL(1), REAL(2), REAL(3), REAL(4));
return;
}
case 117:
{
Rva003BAD15(TEXT(0), REAL(1), REAL(2), TEXT(3));
return;
}
case 120:
{
doZoomCamera(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 389:
{
Rva003BABCB(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 121:
{
doPitchCamera(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 346:
{
Rva003BAC6D(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 122:
{
Rva003BAA46(PARAM(0), (PARAM(1) && INTEGER(1) != 0), REAL(2));
return;
}
case 135:
{
Rva003BAAD6();_ReadWriteBarrier();
return;
}
case 123:
{
Rva003BACCA((Parameter *)(INTEGER(0)));
return;
}
case 32:
{
Rva003C4D5CDo(&TEXT(0));
return;
}
case 31:
{
Rva003C4DC2Do(TEXT(0));
return;
}
case 17:
{
Rva003BB0C7Set((int)(&TEXT(0)), REAL(1), REAL(2), REAL(3), REAL(4), REAL(5), 0);
return;
}
case 390:
{
Rva003BB0C7Set((int)(&TEXT(0)), REAL(1), REAL(2), REAL(3), REAL(4), REAL(5), 1);
return;
}
case 550:
{
Rva003BB141Notify(*(StringBase<char> const *)(&TEXT(0)));
return;
}
case 18:
{
doRotateCamera(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 529:
{
Rva003BAF1D(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 340:
{
Rva003BAF95(REAL(0), REAL(1), REAL(2), REAL(3));
return;
}
case 185:
{
Rva003BAFE8(PARAM(0), REAL(1), REAL(2), REAL(3), REAL(4), REAL(5));
return;
}
case 210:
{
Rva003BB05FSet((int)(&TEXT(0)), REAL(1), REAL(2), REAL(3), (INTEGER(4) != 0));
return;
}
case 19:
{
Rva003C4E28Find(TEXT(0), REAL(1), REAL(2), REAL(3));
return;
}
case 35:
{
Rva003BAE04();
return;
}
case 21:
{
((ScriptActionViewSlots *)TheTacticalView)->slot35();
return;
}
case 28:
{
((ScriptActionViewSlots *)TheTacticalView)->slot36();
return;
}
case 26:
{
((ScriptActionViewSlots *)TheTacticalView)->slot31(REAL(0), REAL(1), REAL(2));
return;
}
case 27:
{
((ScriptActionViewSlots *)TheTacticalView)->slot34(REAL(0), REAL(1), REAL(2));
return;
}
case 29:
{
((ScriptActionViewSlots *)TheTacticalView)->slot33(INTEGER(0));
return;
}
case 30:
{
((ScriptActionViewSlots *)TheTacticalView)->slot32(INTEGER(0));
return;
}
case 22:
{
((ScriptActionViewSlots *)TheTacticalView)->slot56(INTEGER(0));
return;
}
case 24:
{
((ScriptActionAudioSlots *)TheAudio)->slot16(2, 1, 1);
return;
}
case 25:
{
((ScriptActionAudioSlots *)TheAudio)->slot17(2, 1, 1);
return;
}
case 11:
{
doPlaySoundEffectAt(TEXT(0), TEXT(1));
return;
}
case 510:
{
doPlaySoundEffectAtTeam(TEXT(0), TEXT(1));
return;
}
case 334:
{
((ScriptActionGlobalData *)TheWritableGlobalData)->m_value950 = REAL(0);
return;
}
case 327:
{
((Rva003BD598 *)this)->rva003BD598();
return;
}
case 3:
{
((Rva003BE5C9 *)this)->rva003C3B4A();
return;
}
case 511:
{
((Rva003BE5C9 *)this)->rva003BE5C9();
return;
}
case 4:
{
((Rva003BE6CB *)this)->rva003BE6CB();
return;
}
case 299:
{
((Rva003BE7ED *)this)->rva003BE7ED();
return;
}
case 23:
{
Coord3D temp36; PARAM(2)->getCoord3D(&temp36);
doCreateObject(AsciiString::TheEmptyString, TEXT(0), TEXT(1), (Coord3D *)(&temp36), REAL(3));
return;
}
case 33:
{
doTeamAttackTeam(TEXT(0), TEXT(1));
return;
}
case 39:
{
Rva003C82EADo(PARAM(0), PARAM(1));
return;
}
case 40:
case 590:
{
createUnitOnTeamAt(TEXT(0), TEXT(1), TEXT(2), TEXT(3));
return;
}
case 41:
{
createUnitOnTeamAt(AsciiString::TheEmptyString, TEXT(0), TEXT(1), TEXT(2));
return;
}
case 42:
{
Rva003BB1FFAttack(PARAM(0), TEXT(1));
return;
}
case 43:
{
rva003BEDD1(TEXT(0), TEXT(1));
return;
}
case 44:
{
Rva003BB233Set(TEXT(0), INTEGER(1));
return;
}
case 45:
{
Rva003BB274Ai(PARAM(0), INTEGER(1));
return;
}
case 46:
{
updateTeamSetAttitude(TEXT(0), INTEGER(1));
return;
}
case 235:
{
doNamedSetRepulsor(*(AsciiString const *)(PARAM(0)), (INTEGER(1) != 0));
return;
}
case 236:
{
doTeamSetRepulsor(TEXT(0), (INTEGER(1) != 0));
return;
}
case 47:
{
doNamedAttackArea(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 48:
{
doNamedAttackAreaForSeconds(*(AsciiString const *)(PARAM(0)), TEXT(1), INTEGER(2));
return;
}
case 49:
{
doNamedAttackTeam(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 50:
{
doTeamAttackArea(TEXT(0), TEXT(1));
return;
}
case 51:
{
doTeamAttackNamed(TEXT(0), *(AsciiString const *)(PARAM(1)));
return;
}
case 52:
{
doLoadAllTransports(TEXT(0));
return;
}
case 53:
{
doNamedEnterNamed(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 54:
{
doTeamEnterNamed(TEXT(0), TEXT(1));
return;
}
case 55:
{
doNamedExitAll(*(AsciiString const *)(PARAM(0)));
return;
}
case 56:
{
doTeamExitAll(TEXT(0));
return;
}
case 57:
{
doNamedFollowWaypoints(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 547:
{
doNamedFollowWaypointsExact(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 58:
{
doNamedGuard(*(AsciiString const *)(PARAM(0)));
return;
}
case 59:
{
doTeamGuard(TEXT(0));
return;
}
case 206:
{
Rva003BF71EDo(TEXT(0), TEXT(1));
return;
}
case 207:
{
Rva003BF7ACDo(TEXT(0), PARAM(1));
return;
}
case 208:
{
Rva003BF813Do(TEXT(0), TEXT(1), "");
return;
}
case 487:
{
Rva003BF813Do(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 452:
{
doUnitGuardPosition(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 453:
{
Rva003C89D1Guard(PARAM(0), PARAM(1));
return;
}
case 454:
{
AsciiString temp16("");
Rva003C8A15Do(PARAM(0), TEXT(1), temp16);
return;
}
case 486:
{
Rva003C8A15Do(PARAM(0), TEXT(1), TEXT(2));
return;
}
case 60:
{
Rva003C8A95Do(PARAM(0));
return;
}
case 61:
{
doTeamHunt(TEXT(0));
return;
}
case 282:
{
doTeamHuntWithCommandButton(TEXT(0), TEXT(1));
return;
}
case 99:
{
doPlayerHunt(TEXT(0));
return;
}
case 468:
{
Rva003BF903Do(TEXT(0), (int)(&TEXT(1)));
return;
}
case 62:
{
doPlayerSellEverything(TEXT(0));
return;
}
case 63:
{
doPlayerDisableBaseConstruction(TEXT(0));
return;
}
case 64:
{
doPlayerDisableFactories(TEXT(0), (int)(&TEXT(1)));
return;
}
case 65:
{
doPlayerDisableUnitConstruction(TEXT(0));
return;
}
case 66:
{
doPlayerEnableBaseConstruction(TEXT(0));
return;
}
case 67:
{
doPlayerEnableFactories(TEXT(0), (int)(&TEXT(1)));
return;
}
case 257:
{
Rva003BF96FDo(TEXT(0), TEXT(1));
return;
}
case 68:
{
doPlayerEnableUnitConstruction(TEXT(0));
return;
}
case 70:
{
Rva003BF9C8Do(TEXT(0));
return;
}
case 71:
{
doNamedDamage(*(Parameter const *)(PARAM(0)), INTEGER(1));
return;
}
case 436:
{
doKillHordeMembers(PARAM(0), REAL(1));
return;
}
case 72:
{
doNamedDelete(PARAM(0));
return;
}
case 73:
{
doTeamDelete(TEXT(0), 0);
return;
}
case 330:
{
doTeamDelete(TEXT(0), 1);
return;
}
case 115:
{
Rva003C8ABFDo(TEXT(0), TEXT(1));
return;
}
case 237:
{
Rva003C8B62Do(TEXT(0));
return;
}
case 238:
{
Rva003BFAF4Do(TEXT(0));
return;
}
case 562:
{
Rva003BFB8CDo(TEXT(0), INTEGER(1));
return;
}
case 239:
{
Rva003BFC27Do(TEXT(0));
return;
}
case 563:
{
Rva003BFCBFDo(TEXT(0), INTEGER(1));
return;
}
case 116:
{
Rva003C8BCBDo(TEXT(0), TEXT(1));
return;
}
case 74:
{
Rva003BB4BDApply(PARAM(0), REAL(1), REAL(2), REAL(3), (int)(&TEXT(4)));
return;
}
case 75:
{
doNamedKill(PARAM(0));
return;
}
case 76:
{
doTeamKill(TEXT(0));
return;
}
case 77:
{
doPlayerKill(TEXT(0));
return;
}
case 78:
{
doDisplayText(TEXT(0));
return;
}
case 219:
{
doDisplayCinematicText(TEXT(0), TEXT(1), INTEGER(2));
return;
}
case 79:
{
doCameoFlash(TEXT(0), INTEGER(1));
return;
}
case 80:
{
Rva003BB5B7Do(PARAM(0), INTEGER(1), (RGBColor *)(0));
return;
}
case 81:
{
Rva003BFF50Do(&TEXT(0), INTEGER(1), (RGBColor *)(0));
return;
}
case 246:
{
RGBColor color; color.red = color.green = color.blue = 1.0f;
Rva003BB5B7Do(PARAM(0), INTEGER(1), &color);
return;
}
case 252:
{
doNamedCustomColor(PARAM(0), INTEGER(1));
return;
}
case 247:
{
RGBColor color; color.red = color.green = color.blue = 1.0f;
Rva003BFF50Do(&TEXT(0), INTEGER(1), &color);
return;
}
case 82:
{
Rva003BFFECDo(TEXT(0), (INTEGER(1) != 0));
return;
}
case 83:
{
doMoviePlayRadar(TEXT(0));
return;
}
case 84:
{
doSoundPlayFromNamed(TEXT(0), *(AsciiString const *)(PARAM(1)));
return;
}
case 85:
{
doSpeechPlay(TEXT(0), (INTEGER(1) != 0));
return;
}
case 86:
{
bfmeLinkObjectsA70((void *)(&TEXT(0)), (void *)(&TEXT(1)));
return;
}
case 87:
{
Rva003BD884Set(PARAM(0), &TEXT(1));
return;
}
case 315:
{
Rva003BB6C0Clear(TEXT(0));
return;
}
case 317:
{
Rva003BB700(true);
return;
}
case 318:
{
Rva003BB700(false);
return;
}
case 88:
{
Rva003BB713Set(TEXT(0), (Object *)(INTEGER(2)), TEXT(1));
return;
}
case 90:
{
Coord3D temp36; PARAM(0)->getCoord3D(&temp36);
Rva003BB76EDo((Coord3D *)(&temp36), (void *)(INTEGER(1)));
return;
}
case 217:
{
doObjectRadarCreateEvent(PARAM(0), (void *)(INTEGER(1)));
return;
}
case 218:
{
doTeamRadarCreateEvent(&TEXT(0), (void *)(INTEGER(1)));
return;
}
case 91:
{
Rva003BB7E2();
return;
}
case 92:
{
Rva003BB7F0();
return;
}
case 530:
{
doNamedEnableCameraFading(PARAM(0), (INTEGER(1) != 0));
return;
}
case 295:
{
doNamedEnableStealth(*(AsciiString const *)(PARAM(0)), (INTEGER(1) != 0));
return;
}
case 296:
{
doTeamEnableStealth(TEXT(0), (INTEGER(1) != 0));
return;
}
case 432:
{
rva003BBD61(*(AsciiString const *)(PARAM(0)), (INTEGER(1) != 0));
return;
}
case 433:
{
rva003C05DE(TEXT(0), (INTEGER(1) != 0));
return;
}
case 93:
{
Rva003BB8EDReveal(TEXT(0), REAL(1), TEXT(2));
return;
}
case 552:
{
rva003C013C(TEXT(0), TEXT(1));
return;
}
case 105:
{
doRevealMapEntire(TEXT(0));
return;
}
case 233:
{
Rva003BB9C6Reveal(true, TEXT(0));
return;
}
case 234:
{
Rva003BB9C6Reveal(false, TEXT(0));
return;
}
case 149:
{
doShroudMapEntire(TEXT(0));
return;
}
case 94:
{
doTeamAvailableForRecruitment(TEXT(0), (INTEGER(1) != 0));
return;
}
case 96:
{
doMergeTeamIntoTeam(TEXT(0), TEXT(1));
return;
}
case 250:
{
doIdleAllPlayerUnits(AsciiString::TheEmptyString);
return;
}
case 251:
{
doResumeSupplyTruckingForIdleUnits(AsciiString::TheEmptyString);
return;
}
case 97:
{
((Rva003BBAD3 *)this)->rva003BBAD3();
return;
}
case 98:
{
doEnableInput();
return;
}
case 321:
{
doSetBorderShroud(false);
return;
}
case 322:
{
doSetBorderShroud(true);
return;
}
case 100:
{
Rva003BBC61Set(true);
return;
}
case 101:
{
Rva003BBC61Set(false);
return;
}
case 102:
{
Rva003C0308Do(TEXT(0), (INTEGER(1) != 0), (INTEGER(2) != 0), 4294954951, AsciiString::TheEmptyString, 1);
return;
}
case 450:
{
Rva003C0425Do(TEXT(0), (INTEGER(1) != 0), (INTEGER(2) != 0), 4294954951, AsciiString::TheEmptyString, 1);
return;
}
case 451:
{
Rva003BBC81Set((INTEGER(0) != 0), (INTEGER(1) != 0), 1);
return;
}
case 471:
{
Rva003C0308Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), AsciiString::TheEmptyString, 1);
return;
}
case 472:
{
Rva003C0308Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), TEXT(4), 1);
return;
}
case 473:
{
Rva003C0425Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), AsciiString::TheEmptyString, 1);
return;
}
case 474:
{
Rva003C0425Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), TEXT(4), 1);
return;
}
case 456:
{
Rva003C0308Do(TEXT(0), (INTEGER(1) != 0), (INTEGER(2) != 0), 4294954951, AsciiString::TheEmptyString, 0);
return;
}
case 457:
{
Rva003C0425Do(TEXT(0), (INTEGER(1) != 0), (INTEGER(2) != 0), 4294954951, AsciiString::TheEmptyString, 0);
return;
}
case 458:
{
Rva003BBC81Set((INTEGER(0) != 0), (INTEGER(1) != 0), 0);
return;
}
case 475:
{
Rva003C0308Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), AsciiString::TheEmptyString, 0);
return;
}
case 476:
{
Rva003C0308Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), TEXT(4), 0);
return;
}
case 477:
{
Rva003C0425Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), AsciiString::TheEmptyString, 0);
return;
}
case 478:
{
Rva003C0425Do(TEXT(0), (INTEGER(2) != 0), (INTEGER(3) != 0), INTEGER(1), TEXT(4), 0);
return;
}
case 459:
{
Rva003BBCB3Set((INTEGER(0) != 0));
return;
}
case 460:
{
Rva003BBCD2Set((INTEGER(0) != 0), (INTEGER(1) != 0));
return;
}
case 461:
{
doResetMusicScripting((INTEGER(0) != 0));
return;
}
case 106:
{
doTeamGarrisonSpecificBuilding(TEXT(0), TEXT(1), false);
return;
}
case 570:
{
doTeamGarrisonSpecificBuilding(TEXT(0), TEXT(1), true);
return;
}
case 573:
{
rva003C6EFC(TEXT(0), TEXT(1), true);
return;
}
case 107:
{
Rva003C8C6EDo(TEXT(0));
return;
}
case 108:
{
doTeamGarrisonNearestBuilding(TEXT(0));
return;
}
case 109:
{
Rva003C8E2BExit(TEXT(0));
return;
}
case 110:
{
doUnitGarrisonSpecificBuilding(*(AsciiString const *)(PARAM(0)), TEXT(1), false);
return;
}
case 567:
{
doUnitGarrisonSpecificBuilding(*(AsciiString const *)(PARAM(0)), TEXT(1), true);
return;
}
case 111:
{
doUnitGarrisonNearestBuilding(*(AsciiString const *)(PARAM(0)));
return;
}
case 112:
{
Rva003C90B1Exit(PARAM(0));
return;
}
case 113:
{
doPlayerGarrisonAllBuildings(TEXT(0));
return;
}
case 114:
{
doPlayerExitAllBuildings(TEXT(0));
return;
}
case 118:
{
doLetterBoxMode(true);
return;
}
case 119:
{
doLetterBoxMode(false);
return;
}
case 347:
{
HideControlBar(true);
return;
}
case 348:
{
ShowControlBar(false);
return;
}
case 349:
{
Rva003BBE91Set(true, INTEGER(0));
return;
}
case 350:
{
Rva003BBE91Set(false, INTEGER(0));
return;
}
case 128:
{
doBlackWhiteMode(true, (PARAM(0) ? INTEGER(0) : 0));
return;
}
case 129:
{
doBlackWhiteMode(false, (PARAM(0) ? INTEGER(0) : 0));
return;
}
case 136:
{
Rva003BB898((INTEGER(0) != 0), (INTEGER(1) != 0));
return;
}
case 137:
{
Rva003BB7FESet((int)(&TEXT(0)), (INTEGER(1) != 0));
return;
}
case 138:
{
((ScriptActionViewSlots *)TheTacticalView)->slot45(INTEGER(0) + 16);
((ScriptActionViewSlots *)TheTacticalView)->slot47(2);
return;
}
case 139:
{
((ScriptActionViewSlots *)TheTacticalView)->slot45(13);
((ScriptActionViewSlots *)TheTacticalView)->slot47(2);
return;
}
case 484:
{
((Rva00239A40 *)TheGameClient)->rva00239A40(TEXT(0));
return;
}
case 485:
{
((Rva00239A40 *)TheGameClient)->rva00239A40(AsciiString(""));
return;
}
case 140:
{
doFreezeTime();
return;
}
case 141:
{
doUnfreezeTime();
return;
}
case 142:
{
doMilitaryCaption((int)(&TEXT(0)), REAL(1));
return;
}
case 144:
{
doSetStoppingDistance(TEXT(0), REAL(1));
return;
}
case 146:
{
if (INTEGER(0) == 0)
((ScriptActionGameEngineSlots *)TheGameEngine)->slot18(((ScriptActionGlobalData *)TheWritableGlobalData)->m_value28);
else
((ScriptActionGameEngineSlots *)TheGameEngine)->slot18(INTEGER(0));
((ScriptActionGlobalData *)TheWritableGlobalData)->m_flag26 = true;
return;
}
case 159:
{
doDisableSpecialPowerDisplay();
return;
}
case 160:
{
doEnableSpecialPowerDisplay();
return;
}
case 161:
{
doNamedHideSpecialPowerDisplay(PARAM(0));
return;
}
case 162:
{
doNamedShowSpecialPowerDisplay(PARAM(0));
return;
}
case 145:
{
doNamedSetStoppingDistance(PARAM(0), REAL(1));
return;
}
case 229:
{
Rva003BBF23Disable(PARAM(0), (INTEGER(1) != 0));
return;
}
case 147:
{
doAudioSetVolume(1, REAL(0));
return;
}
case 319:
{
doAudioSetVolume(22, REAL(0));
return;
}
case 320:
{
doAudioSetVolume(8, REAL(0));
return;
}
case 156:
{
doTransferTeamToPlayer(TEXT(0), TEXT(1));
return;
}
case 157:
{
doSetMoney(TEXT(0), INTEGER(1));
return;
}
case 158:
{
doGiveMoney(TEXT(0), INTEGER(1));
return;
}
case 163:
{
Rva003C549DDo(TEXT(0), TEXT(1));
return;
}
case 164:
{
Rva003C5535Do(TEXT(0));_ReadWriteBarrier();
return;
}
case 240:
{
Rva003C5405Do(TEXT(0), TEXT(1));
return;
}
case 241:
{
Rva003C5535Do(TEXT(0));
return;
}
case 166:
{
doDisableCountdownTimerDisplay();
return;
}
case 165:
{
doEnableCountdownTimerDisplay();
return;
}
case 167:
{
doNamedStopSpecialPowerCountdown(PARAM(0), TEXT(1), (void *)(1));
return;
}
case 168:
{
doNamedStopSpecialPowerCountdown(PARAM(0), TEXT(1), (void *)(0));
return;
}
case 169:
{
doNamedSetSpecialPowerCountdown(PARAM(0), TEXT(1), INTEGER(2));
return;
}
case 170:
{
doNamedAddSpecialPowerCountdown(PARAM(0), TEXT(1), INTEGER(2));
return;
}
case 578:
{
doPlayerSetSpecialPowerCountdown(TEXT(0), TEXT(1), INTEGER(2));
return;
}
case 171:
{
doNamedFireSpecialPowerAtWaypoint(PARAM(0), TEXT(1), (void *)(&TEXT(2)));
return;
}
case 571:
{
doFireSpecialPowerAtWaypoint(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 255:
{
doSkirmishFireSpecialPowerAtMostCost(TEXT(0), TEXT(1));
return;
}
case 445:
{
rva003C56D6((void *)(&TEXT(0)), TEXT(1), TEXT(2), TEXT(3));
return;
}
case 446:
{
rva003C55A6((void *)(&TEXT(0)), TEXT(1), TEXT(2), TEXT(3), TEXT(4));
return;
}
case 447:
{
rva003C4145(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 172:
{
doNamedFireSpecialPowerAtNamed(PARAM(0), TEXT(1), TEXT(2));
return;
}
case 173:
{
doRadarRefresh();
return;
}
case 177:
{
Rva003C91D1Idle(PARAM(0));
return;
}
case 178:
{
((Rva003C08CC *)this)->rva003C08CC(&TEXT(0), false);
return;
}
case 179:
{
((Rva003C08CC *)this)->rva003C08CC(&TEXT(0), true);
return;
}
case 174:
{
Rva003BC1B2Do(PARAM(0), (INTEGER(1) != 0), REAL(2));
return;
}
case 175:
{
Rva003BAAD6();
return;
}
case 176:
{
doCameraSetDefault(REAL(0), REAL(1), REAL(2));
return;
}
case 182:
{
doTeamSetOverrideRelationToTeam(TEXT(0), TEXT(1), (Object *)(INTEGER(2)));
return;
}
case 183:
{
doTeamRemoveOverrideRelationToTeam(TEXT(0), TEXT(1));
return;
}
case 184:
{
doTeamRemoveAllOverrideRelations(TEXT(0));
return;
}
case 187:
{
doTeamSetOverrideRelationToPlayer(TEXT(0), TEXT(1), (Object *)(INTEGER(2)));
return;
}
case 188:
{
doTeamRemoveOverrideRelationToPlayer(TEXT(0), TEXT(1));
return;
}
case 189:
{
doPlayerSetOverrideRelationToTeam(TEXT(0), TEXT(1), (Object *)(INTEGER(2)));
return;
}
case 190:
{
doPlayerRemoveOverrideRelationToTeam(TEXT(0), TEXT(1));
return;
}
case 186:
{
doNamedFireWeaponFollowingWaypointPath(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 244:
{
Rva003C57A9Do(PARAM(0), TEXT(1));
return;
}
case 202:
{
Rva003C5825Do(PARAM(0), TEXT(1), TEXT(2));
return;
}
case 203:
{
Rva003C58C9Do(PARAM(0), TEXT(1), (int)(&TEXT(2)));
return;
}
case 424:
{
rva003BD905(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 425:
{
rva003BDB03(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 426:
{
rva003BDC65(*(AsciiString const *)(PARAM(0)), TEXT(1), INTEGER(2));
return;
}
case 427:
{
rva003BDE5D(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 428:
{
rva003BDFA5(*(AsciiString const *)(PARAM(0)), TEXT(1), INTEGER(2));
return;
}
case 429:
{
rva003C42B9(PARAM(0), TEXT(1), TEXT(2));
return;
}
case 572:
{
doNamedBuildStructureAtWaypoint(PARAM(0), TEXT(1), REAL(2), TEXT(3));
return;
}
case 245:
{
Rva003C075BDo(&TEXT(0), &TEXT(1));
return;
}
case 242:
{
Rva003C07C1Do(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 243:
{
Rva003C0849Do(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 266:
{
Rva003C1020Do(TEXT(0), TEXT(1), PARAM(2));
return;
}
case 267:
{
doTeamUseCommandButtonOnNearestEnemy(TEXT(0), TEXT(1));
return;
}
case 268:
{
doTeamUseCommandButtonOnNearestGarrisonedBuilding(TEXT(0), TEXT(1));
return;
}
case 269:
{
doTeamUseCommandButtonOnNearestKindof(TEXT(0), TEXT(1), INTEGER(2));
return;
}
case 270:
{
doTeamUseCommandButtonOnNearestBuilding(TEXT(0), TEXT(1));
return;
}
case 271:
{
doTeamUseCommandButtonOnNearestBuildingClass(TEXT(0), TEXT(1), INTEGER(2));
return;
}
case 272:
{
doTeamUseCommandButtonOnNearestObjectType(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 273:
{
doTeamPartialUseCommandButton(REAL(0), TEXT(1), TEXT(2));
return;
}
case 191:
{
doUnitStartSequentialScript(PARAM(0), TEXT(1), 0);
return;
}
case 192:
{
doUnitStartSequentialScript(PARAM(0), TEXT(1), (INTEGER(2) - 1));
return;
}
case 193:
{
doUnitStopSequentialScript(PARAM(0));
return;
}
case 194:
{
doTeamStartSequentialScript(TEXT(0), TEXT(1), 0);
return;
}
case 195:
{
doTeamStartSequentialScript(TEXT(0), TEXT(1), (INTEGER(2) - 1));
return;
}
case 196:
{
doTeamStopSequentialScript(TEXT(0));
return;
}
case 197:
{
doUnitGuardForFramecount(*(AsciiString const *)(PARAM(0)), INTEGER(1), false);
return;
}
case 198:
{
doUnitIdleForFramecount(*(AsciiString const *)(PARAM(0)), INTEGER(1), false);
return;
}
case 328:
{
rva003C0D6A(*(AsciiString const *)(PARAM(0)), INTEGER(1), (INTEGER(2) != 0));
return;
}
case 329:
{
rva003C0D90(TEXT(0), INTEGER(1), (INTEGER(2) != 0));
return;
}
case 434:
{
rva003C596A(*(AsciiString const *)(PARAM(0)), TEXT(1), REAL(2), REAL(3));
return;
}
case 435:
{
Rva003C5A00Do(TEXT(0), TEXT(1), REAL(2), REAL(3));
return;
}
case 344:
{
Rva003BC2E4Do(PARAM(0), (INTEGER(1) != 0));
return;
}
case 345:
{
Rva003C0DE1Do(TEXT(0), (INTEGER(1) != 0));
return;
}
case 199:
case 200:
{
doTeamIdleForFramecount(TEXT(0), INTEGER(1), false);
return;
}
case 201:
{
doWaterChangeHeight((Parameter *)(&TEXT(0)), REAL(1));
return;
}
case 204:
{
doWaterChangeHeightOverTime((Parameter *)(&TEXT(0)), REAL(1), REAL(2), REAL(3));
return;
}
case 205:
{
doBorderSwitch(INTEGER(0));
return;
}
case 371:
{
((ScriptActionGlobalData *)TheWritableGlobalData)->m_valueD40 = REAL(0);
return;
}
case 372:
{
((Rva003BC392Holder *)this)->set((INTEGER(0) != 0));
return;
}
case 209:
{
doForceObjectSelection(TEXT(0), TEXT(1), (INTEGER(2) != 0), TEXT(3));
return;
}
case 211:
{
doDestroyAllContained(PARAM(0), 0);
return;
}
case 212:
{
((ScriptActionRadarFlags *)TheRadar)->m_flag11 = true;
return;
}
case 213:
{
((ScriptActionRadarFlags *)TheRadar)->m_flag11 = false;
return;
}
case 214:
{
doScreenShake(INTEGER(0));
return;
}
case 215:
{
doModifyBuildableStatus(TEXT(0), INTEGER(1));
return;
}
case 228:
{
doSetCaveIndex(TEXT(0), INTEGER(1));
return;
}
case 216:
{
doSetWarehouseValue(TEXT(0), INTEGER(1));
return;
}
case 221:
{
Rva003BC4E8Do((int)(&TEXT(0)));
return;
}
case 222:
{
Rva003BC4D1Do((int)(&TEXT(0)));
return;
}
case 223:
{
Rva003BC4FFForward();
return;
}
case 325:
{
Rva003BC510Do((int)(&TEXT(0)));
return;
}
case 224:
{
Rva003BC524Set(TEXT(0), REAL(1));
return;
}
case 225:
{
Rva003BC54FDo((int)(&TEXT(0)));
return;
}
case 226:
{
Rva003BC566Forward();
return;
}
case 230:
{
Coord3D position; PARAM(1)->getCoord3D(&position);
TheScriptEngine->rva0035818E(TEXT(0), &position);
return;
}
case 231:
{
doMoveUnitTowardsNearest(*(AsciiString const *)(PARAM(0)), TEXT(1), TEXT(2));
return;
}
case 548:
{
rva003C951B(*(AsciiString const *)(PARAM(0)), TEXT(1), AsciiString::TheEmptyString);
return;
}
case 232:
{
doMoveTeamTowardsNearest(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 549:
{
doAttackMoveTeamTowardsNearest(TEXT(0), TEXT(1), AsciiString::TheEmptyString);
return;
}
case 565:
{
doAttackMoveTeamTowardsNearest(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 566:
{
rva003C0F09(TEXT(0), INTEGER(1));
return;
}
case 256:
{
doUnitReceiveUpgrade(PARAM(0), TEXT(1));
return;
}
case 261:
{
doSkirmishAttackNearestGroupWithValue(TEXT(0), INTEGER(1), INTEGER(2));
return;
}
case 262:
{
doSkirmishCommandButtonOnMostValuable(TEXT(0), TEXT(1), REAL(2), (INTEGER(3) != 0));
return;
}
case 265:
{
doTeamSpinForFramecount(TEXT(0), INTEGER(1));
return;
}
case 551:
{
int framecount = (int)Rva000422BBCeil((float)BfmeLogicFramesPerSecond * REAL(1));
doTeamSpinForFramecount(TEXT(0), framecount);
return;
}
case 274:
{
doTeamCaptureNearestUnownedFactionUnit(TEXT(0));
return;
}
case 275:
{
((Rva003C1E69 *)this)->rva003C1E69(TEXT(0), TEXT(1));
return;
}
case 276:
{
Rva003BC582Set(TEXT(0), INTEGER(1));
return;
}
case 538:
{
Rva003BC8F0Set((INTEGER(0) != 0));
return;
}
case 277:
{
Rva003BC5CESet(TEXT(0), INTEGER(1));
return;
}
case 278:
{
Rva003BC626Set(TEXT(0), INTEGER(1));
return;
}
case 592:
{
Rva003BC67ASet(TEXT(0), INTEGER(1));
return;
}
case 279:
{
Rva003BC6C7Set(INTEGER(0));
return;
}
case 280:
{
Rva003BC6D9Set(TEXT(0), TEXT(1));
return;
}
case 281:
{
Rva003BC72FSet(TEXT(0), TEXT(1));
return;
}
case 302:
{
Rva003BC785Set(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 287:
{
Rva003C1F0A(TEXT(0), *(StringBase<char> const *)(&TEXT(1)), REAL(2));
return;
}
case 288:
{
Rva003BC996Do(PARAM(0), *(StringBase<char> const *)(&TEXT(1)), REAL(2));
return;
}
case 291:
{
TheScriptEngine->doObjectTypeListMaintenance(TEXT(0), TEXT(1), true);
return;
}
case 292:
{
TheScriptEngine->doObjectTypeListMaintenance(TEXT(0), TEXT(1), false);
return;
}
case 293:
{
Rva003BC9E0Do(TEXT(0), REAL(1), TEXT(2), TEXT(3));
return;
}
case 294:
{
Rva003BCA43Do(TEXT(0));_ReadWriteBarrier();
return;
}
case 554:
{
Rva003BCA12Do(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 555:
{
Rva003BCA43Do(TEXT(0));
return;
}
case 297:
{
Rva003BCA5DSet((INTEGER(0) != 0));
return;
}
case 298:
{
Rva003BCA68Set((INTEGER(0) != 0));
return;
}
case 300:
{
Rva003BCA7BSet((INTEGER(0) != 0));
return;
}
case 335:
{
Rva003BCADAForward(TEXT(0), TEXT(1));
return;
}
case 336:
{
Rva003BCAE8Forward();
return;
}
case 337:
{
Rva003BCAF6Do((Parameter *)(&TEXT(0)), REAL(1), REAL(2), REAL(3));
return;
}
case 301:
{
Rva003BCA8ESet((INTEGER(0) != 0));
return;
}
case 306:
{
Rva003BCAA1Set(REAL(0));
return;
}
case 307:
{
doNamedFaceNamed(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 308:
{
doNamedFaceWaypoint(*(AsciiString const *)(PARAM(0)), TEXT(1));
return;
}
case 309:
{
doTeamFaceNamed(TEXT(0), TEXT(1));
return;
}
case 310:
{
doTeamFaceWaypoint(TEXT(0), TEXT(1));
return;
}
case 303:
{
doAffectObjectPanelFlagsUnit(PARAM(0), TEXT(1), (INTEGER(2) != 0));
return;
}
case 304:
{
doAffectObjectPanelFlagsTeam(TEXT(0), TEXT(1), (INTEGER(2) != 0));
return;
}
case 305:
{
Rva003BCB37Set(TEXT(0), INTEGER(1));
return;
}
case 311:
{
doRemoveCommandBarButton(TEXT(0), TEXT(1));
return;
}
case 312:
{
Rva003BCB7A(TEXT(0), TEXT(1), INTEGER(2));
return;
}
case 313:
{
Coord3D temp36; PARAM(3)->getCoord3D(&temp36);
doCreateObject(TEXT(0), TEXT(1), TEXT(2), (Coord3D *)(&temp36), REAL(4));
return;
}
case 314:
{
Rva003BCBC7Set(TEXT(0), REAL(1));
return;
}
case 316:
{
Rva003C1F6CDo(&TEXT(0), INTEGER(1));
return;
}
case 323:
{
((ScriptActionWindowSlots *)this)->slot16(INTEGER(0) != 0);
return;
}
case 326:
{
doTeamGuardInTunnelNetwork(TEXT(0));
return;
}
case 331:
{
Rva003BCC08Do(REAL(0), REAL(1));
return;
}
case 332:
{
Rva003C1FADDestroy();
return;
}
case 333:
{
Rva003BCC6ESet((INTEGER(0) != 0));
return;
}
case 338:
{
rva003BA943(PARAM(0), true);
return;
}
case 339:
{
rva003BA943(PARAM(0), false);
return;
}
case 341:
{
Rva003BCC81Set(true);
return;
}
case 342:
{
Rva003BCC81Set(false);
return;
}
case 351:
{
Rva003BC7EFSet(TEXT(0), INTEGER(1));
return;
}
case 352:
{
Rva003BC830Clear(TEXT(0));
return;
}
case 353:
{
Rva003BC86ESet(TEXT(0), TEXT(1));
return;
}
case 354:
{
Rva003BC8AFSet(TEXT(0), (int)(&TEXT(1)));
return;
}
case 355:
{
Rva003C4570Do(TEXT(0), TEXT(1));
return;
}
case 356:
{
Rva003C1E8CSet(TEXT(0), INTEGER(1));
return;
}
case 357:
{
Rva003C1EC2Set(TEXT(0), INTEGER(1));
return;
}
case 358:
{
Rva003C45D4Apply(PARAM(0), TEXT(1));
return;
}
case 359:
{
Rva003BC903Do(PARAM(0), INTEGER(1));
return;
}
case 360:
{
rva003BC93C(PARAM(0), INTEGER(1));
return;
}
case 591:
{
Rva003BC96FDo(PARAM(0), INTEGER(1));
return;
}
case 361:
{
Coord3D temp36; PARAM(2)->getCoord3D(&temp36);
return;
}
case 363:
{
Coord3D temp48; PARAM(2)->getCoord3D(&temp48);
return;
}
case 366:
{
Rva003BCC94Do();
return;
}
case 367:
{
Rva003BCCA2Do();
return;
}
case 368:
{
((Rva003C1FDE *)this)->rva003C1FDE(TEXT(0), (INTEGER(1) != 0));
return;
}
case 369:
{
Rva003BCCC6Do(PARAM(0), PARAM(1));
return;
}
case 370:
{
Rva003BCD1BDo(PARAM(0));
return;
}
case 376:
{
doSetUnitReference(TEXT(0), PARAM(1), false);
return;
}
case 377:
{
rva003C20CA(TEXT(0), PARAM(1), false);
return;
}
case 378:
{
doSetUnitReference(TEXT(0), PARAM(1), true);
return;
}
case 379:
{
rva003C20CA(TEXT(0), PARAM(1), true);
return;
}
case 462:
{
rva003C4625(TEXT(0), PARAM(1), TEXT(2));
return;
}
case 488:
{
doSetUnitReferenceToHomeBaseOfPlayer(TEXT(0), TEXT(1), (INTEGER(2) != 0));
return;
}
case 463:
{
Rva003BCDD7Do(PARAM(0));
return;
}
case 464:
{
Rva003BCD45Do(PARAM(0));
return;
}
case 498:
{
rva003C207C(PARAM(0), PARAM(1), (INTEGER(2) != 0));
return;
}
case 380:
{
rva003C4751(PARAM(0));
return;
}
case 402:
{
rva003C49AE(PARAM(0), PARAM(1));
return;
}
case 403:
{
Rva003C2121Grant(TEXT(0), TEXT(1));
return;
}
case 381:
{
doUnpackBase(PARAM(0), &TEXT(1), 0);
return;
}
case 493:
{
doUnpackBase(PARAM(0), &TEXT(1), 1);
return;
}
case 383:
{
doBuildBaseBuilding(TEXT(0), PARAM(1), TEXT(2));
return;
}
case 384:
{
doBuildBaseBuildingInSlot(TEXT(0), PARAM(1), PARAM(2), TEXT(3));
return;
}
case 385:
{
rva003C66F1(TEXT(0), PARAM(1), TEXT(2), PARAM(3), TEXT(4));
return;
}
case 391:
{
Rva003C2260Do(TEXT(0), INTEGER(1));
return;
}
case 392:
{
Rva003C239FDo(TEXT(0), INTEGER(1), PARAM(2));
return;
}
case 393:
{
rva003C2662(TEXT(0), TEXT(1));
return;
}
case 394:
{
rva003C276A(TEXT(0), TEXT(1), PARAM(2));
return;
}
case 395:
{
doCounterMathCounter(PARAM(0), PARAM(1), PARAM(2));
return;
}
case 396:
{
doCounterMathValue(PARAM(0), PARAM(1), PARAM(2));
return;
}
case 397:
{
rva003C2166(TEXT(0), INTEGER(1), TEXT(2));
return;
}
case 556:
{
doSetCounterToThreatFinderThreat(TEXT(0), TEXT(1), TEXT(2), TEXT(3));
Rva003C21E5Do(&TEXT(0), INTEGER(1), &TEXT(2), &TEXT(3));
return;
}
case 398:
{
Rva003C21E5Do(&TEXT(0), INTEGER(1), &TEXT(2), &TEXT(3));
return;
}
case 535:
{
rva003CA322(TEXT(0), INTEGER(1), TEXT(2), TEXT(3));
return;
}
case 399:
{
Rva003C2A29Do(TEXT(0), TEXT(1));
return;
}
case 400:
{
Rva003C2A9FDo(TEXT(0), INTEGER(1));
return;
}
case 401:
{
Rva003C9C0AAttack(PARAM(0), INTEGER(1));
return;
}
case 404:
{
Rva003C2BC0Do(PARAM(0), PARAM(1));
return;
}
case 405:
{
Rva003C2C28Do(PARAM(0), PARAM(1));
return;
}
case 406:
{
Rva003C2C8FDo(PARAM(0), PARAM(1));
return;
}
case 407:
{
Rva003C2CD8Do(PARAM(0), PARAM(1));
return;
}
case 408:
{
Rva003C2D34Do(PARAM(0), PARAM(1));
return;
}
case 409:
{
Rva003C2D90Do(PARAM(0), PARAM(1));
return;
}
case 410:
{
Rva003C2DEADo(PARAM(0), PARAM(1));
return;
}
case 411:
{
doUnitGuardForFramecount(*(AsciiString const *)(PARAM(0)), INTEGER(1), true);
return;
}
case 412:
{
doUnitIdleForFramecount(*(AsciiString const *)(PARAM(0)), INTEGER(1), true);
return;
}
case 413:
case 414:
{
doTeamIdleForFramecount(TEXT(0), INTEGER(1), true);
return;
}
case 387:
{
Rva003BD062Set(PARAM(0), &TEXT(1), (INTEGER(2) != 0));
return;
}
case 388:
{
rva003C606C(PARAM(0), (INTEGER(1) != 0));
return;
}
case 418:
{
Rva003BD0C8Set(TEXT(0), (INTEGER(1) != 0));
return;
}
case 420:
{
Rva003C2E61Do((void const *)(PARAM(0)), (void const *)(PARAM(1)), (void const *)(PARAM(2)));
return;
}
case 421:
{
Rva003C2EC9Do((void const *)(PARAM(0)), (void const *)(PARAM(1)), (void const *)(PARAM(2)));
return;
}
case 422:
{
rva003C5F1B((ScriptAction *)(pAction), PARAM(0), PARAM(1), PARAM(2), true);
return;
}
case 522:
{
rva003C5F1B((ScriptAction *)(pAction), PARAM(0), PARAM(1), PARAM(2), false);
return;
}
case 509:
{
doSetCounterToPlayerOwnershipOfUnitsWithModelCondition(TEXT(0), TEXT(1), TEXT(2));
return;
}
case 423:
{
Rva003C301DDo(PARAM(0), PARAM(1));
return;
}
case 431:
{
Rva003BD032Set(PARAM(0), PARAM(1));
return;
}
case 448:
{
Rva003BB62C((int)(&TEXT(0)));
return;
}
case 449:
{
Rva003BB641();
return;
}
case 525:
{
rva003C004D(TEXT(0), REAL(1));
return;
}
case 526:
{
rva003C0091(TEXT(0));
return;
}
case 527:
{
Rva003BB654();
return;
}
case 465:
{
Rva003C6A0EDo(PARAM(0), PARAM(1), PARAM(2));
return;
}
case 466:
{
Rva003C6B7BDo(PARAM(0), PARAM(1), PARAM(2));
return;
}
case 467:
{
Rva003C6D4FDo(PARAM(0), PARAM(1), PARAM(2));
return;
}
case 469:
{
Rva003C30D9Do(TEXT(0), (INTEGER(1) != 0));
return;
}
case 470:
{
Rva003C3175Do(TEXT(0), (INTEGER(1) != 0));
return;
}
case 479:
{
rva003C9D0D(TEXT(0), REAL(1));
return;
}
case 480:
{
rva003C9E4E(TEXT(0), TEXT(1));
return;
}
case 482:
{
rva003C32CC(TEXT(0), TEXT(1), INTEGER(2) != 0);
return;
}
case 481:
{
Rva003C31F3Do(TEXT(0), TEXT(1), (INTEGER(2) != 0));
return;
}
case 483:
{
Rva003BCFC9Set((INTEGER(0) != 0));
return;
}
case 513:
{
Rva003BCFD4Set((INTEGER(0) != 0));
return;
}
case 528:
{
Rva003BD01FSet((INTEGER(0) != 0));
return;
}
case 574:
{
Rva003BCFE7Forward(INTEGER(0) != 0);
return;
}
case 575:
{
Rva003BCFF5Forward(INTEGER(0) != 0);
return;
}
case 576:
{
Rva003BD003Forward(INTEGER(0) != 0);
return;
}
case 577:
{
Rva003BD011Forward(INTEGER(0) != 0);
return;
}
case 489:
{
rva003C739D(PARAM(0), PARAM(1), PARAM(2), PARAM(3), PARAM(4));
return;
}
case 491:
{
rva003C33C9(PARAM(0), PARAM(1), PARAM(2), PARAM(3), false);
return;
}
case 492:
{
rva003C33C9(PARAM(0), PARAM(1), PARAM(2), PARAM(3), true);
return;
}
case 494:
{
doSellBuildingOnFoundation(PARAM(0));
return;
}
case 496:
{
Rva003BD108SetGamePaused();
return;
}
case 500:
{
doUnitStandGround(PARAM(0), PARAM(1));
return;
}
case 501:
{
doTeamStandGround(PARAM(0), PARAM(1));
return;
}
case 502:
{
Rva003BD116Set(PARAM(0), (void *)(&TEXT(1)));
return;
}
case 503:
{
Rva003C353BDo(PARAM(0), (void *)(&TEXT(1)));
return;
}
case 504:
{
Rva003BD153Set(PARAM(0), INTEGER(1), INTEGER(2));
return;
}
case 505:
{
Rva003BD19CSet(PARAM(0), PARAM(1));
return;
}
case 506:
{
Rva0042F9DAEmit();
return;
}
case 507:
{
Rva003C35AADo(&TEXT(0), (INTEGER(1) != 0), false);
return;
}
case 512:
{
doHeroSelectButtonFlash((int)(&TEXT(0)), INTEGER(1));
return;
}
case 514:
{
rva003C3609(PARAM(0));
return;
}
case 515:
{
doUnitAssimilateWithFirstWalkOnArmy(PARAM(0));
return;
}
case 516:
{
Rva003C36C0Do(PARAM(0), (INTEGER(1) != 0));
return;
}
case 517:
{
Rva003C36FEDo(PARAM(0), (INTEGER(1) != 0));
return;
}
case 518:
{
rva003BD2A6((INTEGER(0) != 0));
return;
}
case 519:
{
doUnitForceEmotion(PARAM(0), INTEGER(1), REAL(2));
return;
}
case 520:
{
doTeamForceEmotion(PARAM(0), INTEGER(1), REAL(2));
return;
}
case 521:
{
doPlayerForceEmotion(PARAM(0), INTEGER(1), REAL(2));
return;
}
case 523:
{
rva003BD306(PARAM(0), (INTEGER(1) != 0));
return;
}
case 524:
{
Rva003C388EDo(PARAM(0), (INTEGER(1) != 0));
return;
}
case 531:
{
rva003BD32B(INTEGER(0));
return;
}
case 532:
{
rva003BD34D(INTEGER(0));
return;
}
case 533:
{
rva003BD36F(INTEGER(0));
return;
}
case 534:
{
rva003BD391(INTEGER(0));
return;
}
case 536:
{
bfmeGoFGE(PARAM(0), (void *)(INTEGER(1)), (INTEGER(2) != 0));
return;
}
case 537:
{
rva003C38EF(PARAM(0), (ObjectStatusTypes)(INTEGER(1)), (INTEGER(2) != 0));
return;
}
case 557:
{
rva003C6279(TEXT(0), TEXT(1));
return;
}
case 558:
{
rva003CA418(TEXT(0), INTEGER(1), TEXT(2));
return;
}
case 559:
{
rva003C3943(TEXT(0), TEXT(1));
return;
}
case 560:
{
doLivingWorldSetRegionRefToAdjacentRegion(TEXT(0), TEXT(1), (INTEGER(2) != 0), (INTEGER(3) != 0));
return;
}
case 561:
{
rva003C39B8(TEXT(0), TEXT(1));
return;
}
case 568:
{
rva003BD3CB((void *)(&TEXT(0)), REAL(1), INTEGER(2));
return;
}
case 569:
{
Rva003C3A3FSet(TEXT(0), INTEGER(1));
return;
}
case 579:
{
doCreateDelayedCarryoverUnitAtWaypoint(TEXT(0), TEXT(1), TEXT(2), TEXT(3));
return;
}
case 596:
{
doCreateUnitRevivalEntryFromDelayedCarryoverHero(TEXT(0), TEXT(1));
return;
}
case 595:
{
doCreateUnitRevivalEntry(TEXT(0), TEXT(1), -1);
break;
}
case 597:
{
doCreateUnitRevivalEntry(TEXT(0), TEXT(1), INTEGER(2));
return;
}
case 580:
{
Rva003BD405Set((unsigned char)(1));
break;
}
case 581:
{
Rva003BD405Set((unsigned char)(0));
return;
}
case 582:
{
Rva003BD412Set((unsigned char)(1));
break;
}
case 583:
{
Rva003BD412Set((unsigned char)(0));
return;
}
case 598:
{
Rva004E400DEnable();
return;
}
case 584:
{
doEnablePlanningMode((unsigned char)(1));
break;
}
case 585:
{
doEnablePlanningMode((unsigned char)(0));
return;
}
case 586:
{
doFlashSpellStoreButton(INTEGER(0));
return;
}
case 587:
{
doFlashObjectivesButton(INTEGER(0));
return;
}
case 588:
{
doFlashPlanningModeButton(INTEGER(0));
return;
}
case 589:
{
doDisplayNotificationBox(TEXT(0), TEXT(1), INTEGER(2), AsciiString::TheEmptyString);
break;
}
case 593:
{
doDisplayNotificationBox(TEXT(0), TEXT(1), INTEGER(2), TEXT(3));
return;
}
case 594:
{
doSelectBuilderButtonFlash(INTEGER(0));_ReadWriteBarrier();
return;
}
default:
return;
}
}
