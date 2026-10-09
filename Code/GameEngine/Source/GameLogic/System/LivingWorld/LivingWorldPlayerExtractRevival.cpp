// cl: /O1 /Ob1 /G7 /EHsc /MD /arch:SSE /DNDEBUG /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
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
class Rva004AF531 {public: int rva004AF531(int); int rva004AF5AC(unsigned);};
class ModuleData {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12)
 virtual bool isRevival()const;
 SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27)
 virtual const Rva004AF531 *getRespawnData()const;
#undef SLOT
};
struct ModuleNugget { char unknown00[8]; const ModuleData *data; char unknown0C[8]; };
class ModuleInfo {
public: const ModuleData *getNthData(int)const;
 ModuleNugget *begin,*end,*capacity;
 int getCount()const {return end-begin;}
};
struct RevivalThingView {char unknown00[0x2E4]; ModuleInfo modules;};
class UnitRevivalEntry {
public:
 UnitRevivalEntry(); UnitRevivalEntry(const UnitRevivalEntry&); ~UnitRevivalEntry(); void *getThingTemplate();
 char unknown00[8]; float experience; int rank,level; char upgrades[0x80]; unsigned int cost; int startFrame; unsigned int time;
 bool revival,flagA1; int productionID,armyID,key; char record[0x18]; int valueC8; float factor; char textD0[8];
};
// ?CalcRevivalCostsForEntry@@YAXAAVUnitRevivalEntry@@@Z
static __declspec(noinline) void CalcRevivalCostsForEntry(UnitRevivalEntry &entry) {
 if(!entry.revival) return;
 RevivalThingView *thing=(RevivalThingView*)entry.getThingTemplate();
 if(!thing) return;
 const ModuleInfo &info=thing->modules;
 for(int i=0;i<info.getCount();++i) {
  const ModuleData *data=info.getNthData(i);
  if(!data) continue;
  if(data->isRevival()) {
   const Rva004AF531 *rules=data->getRespawnData();
   entry.cost=const_cast<Rva004AF531*>(rules)->rva004AF531(entry.rank);
   entry.time=const_cast<Rva004AF531*>(rules)->rva004AF5AC(entry.rank);
   break;
  }
 }
}
struct Rva002E2690Element {char unknown[0xD8];};
struct Rva002E26E1Record {char unknown[0xD8];};
struct Rva002E2D10Record {char unknown[0xD8];};
namespace _STL {
 template<> Rva002E2690Element *vector<Rva002E2690Element>::erase(Rva002E2690Element*,Rva002E2690Element*);
 template<> void vector<Rva002E26E1Record>::reserve(unsigned);
 template<> void vector<Rva002E2D10Record>::push_back(const Rva002E2D10Record&);
}
class Rva002E0D93;
class Rva002E204D {public: Rva002E0D93 *rva002E204D(Rva002E0D93*);};
struct Rva002B3740Item;
class Rva002BA8F1Logic {public: Rva002B3740Item *rva002B2B2D();};
class LivingWorldLogic {public: void *rva002B4948(void*,void*,void*);};
extern LivingWorldLogic *TheLivingWorldLogic;
struct ExtractArmyView {char unknown00[0x20]; int id;};
struct RevivalCampaignView {char unknown00[0x44]; float costMultiplier,timeMultiplier;};
class Rva00E02D6C {public: char unknown00[0x10]; int current; RevivalCampaignView **campaigns;};
extern Rva00E02D6C *TheCampaignManager;
class LivingWorldPlayer {
public:
 bool HasArmyQueuedInAnyBuilding(void*,int*,int);
 void ExtractRevivalUnitDataForCurrentMap(std::vector<Rva002E2690Element>*);
 char unknown00[0x1A8]; std::vector<UnitRevivalEntry> entries;
};
// ?ExtractRevivalUnitDataForCurrentMap@LivingWorldPlayer@@QAEXPAV?$vector@URva002E2690Element@@V?$allocator@URva002E2690Element@@@_STL@@@_STL@@@Z
void LivingWorldPlayer::ExtractRevivalUnitDataForCurrentMap(std::vector<Rva002E2690Element> *out) {
 out->erase(out->begin(),out->end());
 int garrisonArmyID=0;
 std::vector<UnitRevivalEntry> &revivalEntries=entries;
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
