// cl: /O1 /Ob1 /G7 /EHsc /MD /arch:SSE /DNDEBUG /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "FixedStorage128.h"
struct LivingWorldPlayerRGBColorView { float r,g,b; };
// WBDE62B0 names CalcRevivalCostsForEntry; native2E1A1A..2E1AA0 RET0
// supplies the private EDI receiver. Static definition before its sole compiled
// caller lets MSVC select that ABI without assembly. ModuleInfo+2E4 has20-byte
// records; module slots13/28 supply predicate and respawn rules. Original module
// declaration remains opaque; the established provider spellings are preserved.
// WBDE5EC0 names ExtractRevivalUnitDataForCurrentMap; native2E2F44..2E30C8
// proves reverse traversal and D8 revival records. Verified ctor/copy/dtor
// independently corroborate the record layout. Campaign index10/array14 and
// cost/time scalars44/48 are native facts; named scalar temporaries preserve
// retail x87 conversions, and a named array fixes its pointer-load order.
class RespawnUpdateModuleData {public: int calcCostToBuild(int); int calcTimeToBuild(unsigned);};
class ModuleData {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12)
 virtual bool isRevival()const;
 SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27)
 virtual const RespawnUpdateModuleData *getRespawnData()const;
#undef SLOT
};
struct ModuleNugget { char unknown00[8]; const ModuleData *data; char unknown0C[8]; };
class ModuleInfo {
public: const ModuleData *getNthData(int)const;
 ModuleNugget *begin,*end,*capacity;
 int getCount()const {return end-begin;}
};
struct RevivalThingView {char unknown00[0x2E4]; ModuleInfo modules;};
class Xfer;
class UnitRevivalEntry
{
public:
	UnitRevivalEntry();
	UnitRevivalEntry(const UnitRevivalEntry &);
	~UnitRevivalEntry();
	void *getThingTemplate();
	void rva0037E473(Xfer*);
	char m_pad00[0x8];
	float experience; // +0x08
	int rank; // +0x0C
	int level; // +0x10
	BfmeFixedStorage128 upgrades; // +0x14
	unsigned int cost; // +0x94
	int startFrame; // +0x98
	unsigned int time; // +0x9C
	bool revival; // +0xA0
	bool flagA1; // +0xA1
	char m_padA2[0x2];
	int productionID; // +0xA4
	int armyID; // +0xA8
	int key; // +0xAC
	char record[0x18]; // +0xB0
	int valueC8; // +0xC8
	float factor; // +0xCC
	char textD0[8]; // +0xD0
};
// ?CalcRevivalCostsForEntry@@YAXAAVUnitRevivalEntry@@@Z
static __declspec(noinline) void CalcRevivalCostsForEntry(UnitRevivalEntry &entry) {
 if(!entry.revival) return;
 RevivalThingView *thing=(RevivalThingView*)entry.getThingTemplate();
 if(!thing) return;
 const ModuleInfo &info=thing->modules;
 // LINK: manual inline of ModuleInfo::getCount (identical body: end-begin).
 // This TU's copy loses to the first-in-order copy (no retail address); the
 // loop call inlines it but still emits the loser COMDAT. No flags touched.
 for(int i=0;i<(info.end-info.begin);++i) {
  const ModuleData *data=info.getNthData(i);
  if(!data) continue;
  if(data->isRevival()) {
   const RespawnUpdateModuleData *rules=data->getRespawnData();
   entry.cost=const_cast<RespawnUpdateModuleData*>(rules)->calcCostToBuild(entry.rank);
   entry.time=const_cast<RespawnUpdateModuleData*>(rules)->calcTimeToBuild(entry.rank);
   break;
  }
 }
}
struct Rva002E2690Element
{
public:
	char bytes[216]; // +0x00
};
struct Rva002E26E1Record
{
public:
	char m_pad00[0xD8];
};
struct Rva002E2D10Record
{
public:
	char m_pad00[0xD8];
};
namespace _STL {
 template<> Rva002E2690Element *vector<Rva002E2690Element>::erase(Rva002E2690Element*,Rva002E2690Element*);
 template<> void vector<Rva002E26E1Record>::reserve(unsigned);
 template<> void vector<Rva002E2D10Record>::push_back(const Rva002E2D10Record&);
}
class Rva002E0D93;
class Rva002E204D
{
public:
	Rva002E0D93 *rva002E204D(Rva002E0D93 *);
};
struct Rva002B3740Item;
class Rva002BA8F1Logic {public: Rva002B3740Item *rva002B2B2D();};
class LivingWorldLogic {public: void *rva002B4948(void*,void*,void*);};
extern LivingWorldLogic *TheLivingWorldLogic;
struct ExtractArmyView {char unknown00[0x20]; int id;};
struct RevivalCampaignView {char unknown00[0x44]; float costMultiplier,timeMultiplier;};
class Rva00E02D6C {public: char unknown00[0x10]; int current; RevivalCampaignView **campaigns;};
extern Rva00E02D6C *TheCampaignManager;
class INI;
class SpawnArmy;
struct LivingWorldArmy;
struct LivingWorldRevivalUnitDataView;
class LivingWorldPlayer
{
public:
	typedef _STL::vector<void *> ArmyVec;
	static void ParseLivingWorldPlayer(INI *ini, void *instance);
	void MarkUnitsForUpgrades(void *region);
	int GetNumRegionsOwned();
	int GetConflictResolveType();
	void AddUpgrade(void *upgrade, bool persistentOnly);
	void RemoveUpgrade(void *upgrade);
	void rva002E14E9(const BfmeFixedStorage128 &mask);
	bool rva002E1155(SpawnArmy *unit);
	void OnUnitDequeued(SpawnArmy *unit);
	void SetColorIndex(int color);
	void AddArmy(LivingWorldArmy *army);
	void *FindArmyWithHero(void *thing, int key);
	void **RemoveArmy(void **&iter);
	bool rva002E12F3(int key);
	bool rva002E0B30();
	void RemoveRevivalUnit(int key);
	void GetRevivalUnitData(int key, LivingWorldRevivalUnitDataView *out);
	int rva002E199E(const void *thing);
	bool HasArmyQueuedInAnyBuilding(void*,int*,int);
	void ExtractRevivalUnitDataForCurrentMap(std::vector<Rva002E2690Element>*);
	char m_pad00[0x44];
private:
	int m_playerType; // +0x44 +44, native and WB switch
	char m_pad48[0x138];
	int m_colorIndex; // +0x180
	LivingWorldPlayerRGBColorView m_color184; // +0x184
	LivingWorldPlayerRGBColorView m_color190; // +0x190
	LivingWorldPlayerRGBColorView m_color19C; // +0x19C
public:
	_STL::vector<UnitRevivalEntry> m_records; // +0x1A8
	char m_pad1B4[0x4];
private:
	ArmyVec m_armyVec; // +0x1B8 +0x1B8
	char m_pad1C4[0x14];
	unsigned int m_upgradeBits[32]; // +0x1D8 +1D8, native and WB BitFlags<1024>
	char m_pad258[0x40];
	int m_queuedCommandPoints; // +0x298 +0x298
	char m_pad29C[0x18];
	int m_conflictResolveType; // +0x2B4 +2B4, native and WB case0
};
// ?ExtractRevivalUnitDataForCurrentMap@LivingWorldPlayer@@QAEXPAV?$vector@URva002E2690Element@@V?$allocator@URva002E2690Element@@@_STL@@@_STL@@@Z
void LivingWorldPlayer::ExtractRevivalUnitDataForCurrentMap(std::vector<Rva002E2690Element> *out) {
 out->erase(out->begin(),out->end());
 int garrisonArmyID=0;
 std::vector<UnitRevivalEntry> &revivalEntries=m_records;
 if(!revivalEntries.empty()) {
  Rva002B3740Item *region=reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->rva002B2B2D();
  if(region) {
   ExtractArmyView *army=(ExtractArmyView*)TheLivingWorldLogic->rva002B4948(this,region,0);
   if(army) garrisonArmyID=army->id;
  }
 }
 for(int i=revivalEntries.size()-1;i>=0;--i) {
  UnitRevivalEntry entry=revivalEntries[i];
  if(!HasArmyQueuedInAnyBuilding(reinterpret_cast<void*>(entry.key),0,0)) {
   entry.productionID=0; entry.startFrame=-1; entry.factor=1.0f;
   if(entry.revival) {
    CalcRevivalCostsForEntry(entry);
    Rva00E02D6C *manager=TheCampaignManager;
    RevivalCampaignView **array=manager->campaigns;
    RevivalCampaignView *campaign=array[manager->current];
    float costFactor=campaign->costMultiplier;
    entry.cost=(unsigned int)(entry.cost*costFactor);
    float timeFactor=campaign->timeMultiplier;
    entry.time=(unsigned int)(entry.time*timeFactor);
   }
   entry.armyID=garrisonArmyID;
   reinterpret_cast<std::vector<Rva002E26E1Record>*>(out)->reserve(revivalEntries.size());
   reinterpret_cast<std::vector<Rva002E2D10Record>*>(out)->push_back(reinterpret_cast<const Rva002E2D10Record&>(entry));
   reinterpret_cast<Rva002E204D*>(&revivalEntries)->rva002E204D(reinterpret_cast<Rva002E0D93*>(&revivalEntries[i]));
  }
 }
}
