// ?GatherWorldInformation@LWAIWorldInformation@@QAEXXZ
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ?GatherWorldInformation@LWAIWorldInformation@@QAEXXZ retail 0x0050366B
// (1706 bytes; __EH_prolog frame with 16 unwind states). DRAFT, NEAR: every
// instruction, call target and EH state matches retail; only the frame
// packing differs (sub esp 0x1DC vs 0x1D8 and 169 [ebp-X] displacements:
// one extra 4-byte slot holds the two discarded insert results, and the
// 0xC army vector / 0x14 army record swap which one overlays the building
// vector). eh_verify: FuncInfo/unwind map agree, funclets differ only in
// those displacements. Needs the LWAI value-type merge (mapping.tsv) and
// the three converting-ctor pins in gwi_extra_pins.csv.
//
// Identity: the WorldBuilder twin 0x012FDB20 is
// LWAIWorldInformation::GatherWorldInformation in
// LivingWorldAISupport/LivingWorldAIInformation.cpp (asserts at lines 535 and
// 537 name m_RegionInfoByRegion and armyInfo.CurrentRegion->RegionID).
//
// Rebuilds the AI's three tables from TheLivingWorldLogic:
//  - +0x10 multimap<int, region record Rva00501656> keyed by owner, one record
//    per campaign region (+0x12C id, +0x13C owner, +0x58, 0x003F1053) whose
//    five building-ID vectors are filled from the region's buildings by the
//    nugget each building template carries;
//  - +0x1C map<int, region record*> keyed by region id (a map<int,int> view:
//    its rowed bodies are the int/int ones);
//  - +0x04 map<int, player record Rva00501776>, one per player, whose two
//    army vectors receive army records Rva00501E3FElement (unit counts per
//    template id) split on the army's name; each army is also filed under
//    its current region's record.
// Field names other than the WB assert's are inference; the views of the
// int/int trees, Rva004FF408/Rva00500804 clears and the LocomotorSet tree
// dtor follow the names the ledger gives those addresses.
#include "ascii_string.h"
#include <map>
#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class ModuleData;
class Rva002E2903Player;

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class ThingFactory;
extern ThingFactory *TheThingFactory;

typedef _STL::pair<const int, int> IntIntPair;
typedef _STL::_Rb_tree<int, IntIntPair, _STL::_Select1st<IntIntPair>, _STL::less<int>, _STL::allocator<IntIntPair> > IntIntTree;
typedef _STL::map<int, int> IntIntMap;

// +4 tree of the army record. The ledger names its default ctor body
// 0x0033C432 Rva004FFE72Part::Init and its dtor 0x004FF5F3 with the
// LocomotorSet map spelling; insert_equal 0x004FF876 is the int/int one.
class Rva004FFE72Part
{
public:
	void Init();
};

class LocomotorTemplate;
enum LocomotorSetType
{
	LOCOMOTORSET_INVALID = -1
};
typedef _STL::pair<const LocomotorSetType, _STL::vector<const LocomotorTemplate *> > LocoValue;
typedef _STL::_Rb_tree<LocomotorSetType, LocoValue, _STL::_Select1st<LocoValue>, _STL::less<LocomotorSetType>, _STL::allocator<LocoValue> > LocoTree;

namespace _STL {
template <> IntIntTree::iterator IntIntTree::insert_equal(const IntIntPair &);
template <> LocoTree::~_Rb_tree();
}

struct Rva00501656;

struct ArmyUnitTree
{
	char m_tree[12];
	ArmyUnitTree() { ((Rva004FFE72Part *)this)->Init(); }
	~ArmyUnitTree() { ((LocoTree *)this)->~LocoTree(); }
	void insert(const IntIntPair &v) { ((IntIntTree *)this)->insert_equal(v); }
};

// 0x14 army record.
struct Rva00501E3FElement
{
	int m_armyID;              // +0x00
	ArmyUnitTree m_units;      // +0x04 template id -> count
	Rva00501656 *m_region;     // +0x10 CurrentRegion
	Rva00501E3FElement() {}
	Rva00501E3FElement(const Rva00501E3FElement &that);
};

typedef _STL::multimap<int, Rva00501E3FElement> ArmyInfoMap;

// 0x58 region record.
struct Rva00501656
{
	int m_regionID;                        // +0x00
	int m_ownerID;                         // +0x04
	int m_08;
	int m_0c;
	_STL::vector<ScienceType> m_10;        // StrengthenArmy buildings
	_STL::vector<ScienceType> m_1c;        // UpgradeTroops buildings
	_STL::vector<ScienceType> m_28;        // IncreaseCommandPoints buildings
	_STL::vector<ScienceType> m_34;        // SpawnArmy-only buildings
	_STL::vector<ScienceType> m_40;        // SpawnArmy plus another nugget
	ArmyInfoMap m_armies;                  // +0x4C owner -> army
	Rva00501656();
	Rva00501656(const Rva00501656 &that);
	~Rva00501656();
};

typedef _STL::multimap<int, Rva00501656> RegionInfoMap;

// 0x2C player record.
struct Rva00501776
{
	int m_00;
	int m_04;
	int m_08;
	int m_regionCount;                                   // +0x0C
	int m_10;
	_STL::vector<Rva00501E3FElement> m_heroArmies;      // +0x14
	_STL::vector<Rva00501E3FElement> m_garrisonArmies;  // +0x20
	Rva00501776();
	Rva00501776(const Rva00501776 &that);
	~Rva00501776();
};

typedef _STL::map<int, Rva00501776> PlayerInfoMap;

namespace _STL {
template <> void PlayerInfoMap::_Rep_type::clear();
template <> void RegionInfoMap::_Rep_type::clear();
template <> PlayerInfoMap::iterator PlayerInfoMap::insert(PlayerInfoMap::iterator, const PlayerInfoMap::value_type &);
template <> RegionInfoMap::iterator RegionInfoMap::insert(RegionInfoMap::iterator, const RegionInfoMap::value_type &);
template <> ArmyInfoMap::iterator ArmyInfoMap::insert(ArmyInfoMap::iterator, const ArmyInfoMap::value_type &);
template <> IntIntMap::iterator IntIntMap::insert(IntIntMap::iterator, const IntIntMap::value_type &);
template <> _STL::pair<IntIntTree::iterator, IntIntTree::iterator> IntIntTree::equal_range(const int &);
template <> void vector<ScienceType>::push_back(const ScienceType &);
template <> ScienceType *vector<ScienceType>::erase(ScienceType *, ScienceType *);
template <> void vector<Rva00501E3FElement>::push_back(const Rva00501E3FElement &);
template <> Rva00501E3FElement *vector<Rva00501E3FElement>::erase(Rva00501E3FElement *, Rva00501E3FElement *);
}

// Tree clears the ledger rows under address-derived owners.
class Rva004FF408
{
public:
	void rva004FF4C8();
};

class Rva00500804
{
public:
	void rva00500ACF();
};

class BuildingNuggetView
{
public:
	char m_pad00[8];
	int m_type;    // +0x08
};

class LivingWorldBuildingTemplate
{
public:
	BuildingNuggetView *findNugget(const AsciiString &name) const;
};

class LivingWorldBuilding
{
public:
	char m_pad00[0x18];
	int m_id;                                  // +0x18
	char m_pad1c[0x28 - 0x1C];
	LivingWorldBuildingTemplate *m_template;   // +0x28
};

class LivingWorldRegion
{
public:
	int rva003F1053();
	LivingWorldBuilding *GetBuildingByIndex(int index) const;

	char m_pad000[0x58];
	int m_58;                                  // +0x58
	char m_pad05c[0x12C - 0x5C];
	int m_regionID;                            // +0x12C
	char m_pad130[0x13C - 0x130];
	int m_ownerID;                             // +0x13C
};

class Rva003F287F
{
public:
	void rva003F287F(_STL::vector<const ModuleData *> &out);
};

struct LWAIRegionList
{
	char m_pad00[0x2C];
	_STL::vector<LivingWorldRegion *> m_regions;   // +0x2C
};

struct LWAIRegionManager
{
	char m_pad00[0x08];
	LWAIRegionList *m_campaign;   // +0x08
};

struct LWAILogicView
{
	char m_pad000[0x8C];
	_STL::vector<Rva002E2903Player *> m_players;   // +0x8C
	char m_pad098[0xB0 - 0x98];
	LWAIRegionManager *m_regionManager;            // +0xB0
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *rva002B52A8(int index);
};

class Rva002E0C68
{
public:
	int rva002E0C68();
};

class Rva002E0CD4
{
public:
	int get() const;
};

struct LWAIPlayerScoreView
{
	char m_pad00[0x0C];
	int m_0c;
};

struct LWAIPlayerView
{
	char m_pad000[0x14];
	int m_id;                                      // +0x14
	char m_pad018[0x40 - 0x18];
	LWAIPlayerScoreView *m_score;                  // +0x40
	char m_pad044[0x1B8 - 0x44];
	_STL::vector<unsigned int> m_armies;           // +0x1B8
	char m_pad1c4[0x298 - 0x1C4];
	int m_298;                                     // +0x298
	int getID() const { return m_id; }
};

class Rva0040CB2CIndexedField
{
public:
	int get(int index) const;
};

class Rva0040CC1BIndexedField
{
public:
	int findBySecond(int entry) const;
};

struct LWAIArmySummary
{
	char m_pad00[0x40];
	_STL::vector<_STL::pair<int, int> > m_entries;   // +0x40
};

class Rva00318C79Owner
{
public:
	int rva00318C79();
};

struct LWAIArmyView
{
	char m_pad00[0x18];
	AsciiString m_name;              // +0x18
	int m_pad1c;                     // +0x1C
	int m_armyID;                    // +0x20
	char m_pad24[0x78 - 0x24];
	LWAIArmySummary *m_summary;      // +0x78
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};

struct LWAIThingTemplateView
{
	char m_pad000[0x5C4];
	int m_5c4;
};

class LWAIWorldInformation
{
public:
	void GatherWorldInformation();

private:
	int m_00;
	PlayerInfoMap m_PlayerInfo;          // +0x04
	RegionInfoMap m_RegionInfo;          // +0x10
	IntIntMap m_RegionInfoByRegion;      // +0x1C
};

void LWAIWorldInformation::GatherWorldInformation()
{
	m_PlayerInfo.clear();
	m_RegionInfo.clear();
	((Rva004FF408 *)&m_RegionInfoByRegion)->rva004FF4C8();

	LWAIRegionManager *manager = ((LWAILogicView *)TheLivingWorldLogic)->m_regionManager;
	_STL::vector<LivingWorldRegion *> *regions = manager->m_campaign ? &manager->m_campaign->m_regions : 0;
	for (unsigned int i = 0; i < regions->size(); ++i)
	{
		LivingWorldRegion *region = (*regions)[i];
		Rva00501656 info;
		info.m_regionID = region->m_regionID;
		info.m_ownerID = region->m_ownerID;
		info.m_08 = region->m_58;
		info.m_0c = region->rva003F1053();
		info.m_1c.clear();
		info.m_10.clear();
		info.m_28.clear();
		info.m_34.clear();
		info.m_40.clear();
		((Rva00500804 *)&info.m_armies)->rva00500ACF();

		_STL::vector<const ModuleData *> buildings;
		((Rva003F287F *)region)->rva003F287F(buildings);
		for (unsigned int j = 0; j < buildings.size(); ++j)
		{
			LivingWorldBuilding *building = region->GetBuildingByIndex(j);
			BuildingNuggetView *commandPoints = building->m_template->findNugget(AsciiString("IncreaseCommandPoints"));
			BuildingNuggetView *spawnArmy = building->m_template->findNugget(AsciiString("SpawnArmy"));
			BuildingNuggetView *strengthen = building->m_template->findNugget(AsciiString("StrengthenArmy"));
			BuildingNuggetView *upgrade = building->m_template->findNugget(AsciiString("UpgradeTroops"));
			if (commandPoints && commandPoints->m_type != 1)
				commandPoints = 0;
			if (commandPoints)
				info.m_28.push_back((ScienceType)building->m_id);
			else if (strengthen)
				info.m_10.push_back((ScienceType)building->m_id);
			else if (upgrade)
				info.m_1c.push_back((ScienceType)building->m_id);
			if (spawnArmy)
			{
				if (!commandPoints && !strengthen && !upgrade)
					info.m_34.push_back((ScienceType)building->m_id);
				else
					info.m_40.push_back((ScienceType)building->m_id);
			}
		}

		_STL::pair<int, Rva00501656> regionPair(info.m_ownerID, info);
		RegionInfoMap::iterator it = m_RegionInfo.insert(m_RegionInfo.begin(), regionPair);
		m_RegionInfoByRegion.insert(m_RegionInfoByRegion.begin(), _STL::make_pair(info.m_regionID, (int)&it->second));
	}

	int playerCount = ((LWAILogicView *)TheLivingWorldLogic)->m_players.size();
	for (int p = 0; p < playerCount; ++p)
	{
		LWAIPlayerView *player = (LWAIPlayerView *)((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B52A8(p);
		Rva00501776 playerInfo;
		int bonus = player->m_298;
		playerInfo.m_00 = ((Rva002E0C68 *)player)->rva002E0C68() + bonus;
		playerInfo.m_04 = ((Rva002E0CD4 *)player)->get();
		playerInfo.m_08 = player->m_score->m_0c;
		playerInfo.m_regionCount = ((const IntIntTree *)&m_RegionInfo)->count(player->getID());
		playerInfo.m_10 = 0;
		playerInfo.m_heroArmies.clear();
		playerInfo.m_garrisonArmies.clear();

		_STL::vector<unsigned int> armies = player->m_armies;
		((IntIntTree *)&m_RegionInfo)->equal_range(player->getID());
		for (unsigned int a = 0, armyCount = armies.size(); a < armyCount; ++a)
		{
			LWAIArmyView *army = (LWAIArmyView *)armies[a];
			Rva00501E3FElement armyInfo;
			armyInfo.m_armyID = army->m_armyID;
			LWAIArmySummary *summary = army->m_summary;
			int entryCount = summary->m_entries.size();
			for (int e = 0; e < entryCount; ++e)
			{
				int entry = ((const Rva0040CB2CIndexedField *)summary)->get(e);
				AsciiString name(*(const AsciiString *)(entry + 4));
				int templateID = ((LWAIThingTemplateView *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&name))->m_5c4;
				armyInfo.m_units.insert(IntIntPair(templateID, ((const Rva0040CC1BIndexedField *)summary)->findBySecond(entry)));
			}
			int armyRegion = ((Rva00318C79Owner *)army)->rva00318C79();
			armyInfo.m_region = (Rva00501656 *)m_RegionInfoByRegion.find(armyRegion)->second;
			if (!((const StringBase<char> *)&army->m_name)->isEmpty())
				playerInfo.m_heroArmies.push_back(armyInfo);
			else
				playerInfo.m_garrisonArmies.push_back(armyInfo);
			if (armyInfo.m_region)
			{
				_STL::pair<int, Rva00501E3FElement> armyPair(player->getID(), armyInfo);
				ArmyInfoMap &regionArmies = armyInfo.m_region->m_armies;
				ArmyInfoMap::iterator where = regionArmies.begin();
				regionArmies.insert(where, armyPair);
			}
		}
		_STL::pair<int, Rva00501776> playerPair(player->getID(), playerInfo);
		m_PlayerInfo.insert(m_PlayerInfo.begin(), playerPair);
	}
}
