// cl: /O1 /Ob1 /G7 /EHs /MD /arch:SSE /DNDEBUG /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "ascii_string.h"
// WBDE5650 names CreateRevivalEntry, native2E1AA0..2E1CA7 supplies519B.
// A static definition before its caller selects the retail EBX template input;
// the three remaining words follow the hidden result pointer. The target record
// layout and its lifetimes are independently proved by rowed UnitRevivalEntry
// constructors/copy/destructor. The donor only supplies the general revival
// subsystem: BF2's kind test, science/experience and hero paths are target facts.
// The input record is an opaque pointer view; only consumed offsets are modelled.
// Native2E3442..2E34A9 RET12 proves the caller and its three input words.
// A normal128-byte aggregate assignment gives retail's inline repMOVSD, while
// a memcpy call adds a call boundary. No hand-built private calling convention.
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
class ThingTemplate;
struct RevivalUpgradeStorage {unsigned int words[32];};
class UnitRevivalEntry {
public:
 UnitRevivalEntry(); UnitRevivalEntry(const ThingTemplate*); UnitRevivalEntry(const UnitRevivalEntry&); ~UnitRevivalEntry(); void *getThingTemplate();
 char unknown00[8]; float experience; int rank,level; RevivalUpgradeStorage upgrades; unsigned int cost; int startFrame; unsigned int time;
 bool revival,flagA1; int productionID,armyID,key; char record[0x18]; int valueC8; float factor; char textD0[8];
};

struct Rva002E2D10Record {char unknown[0xD8];};
namespace _STL { template<> void vector<Rva002E2D10Record>::push_back(const Rva002E2D10Record&); }
class Rva001EAFC1 {public: Rva001EAFC1 &operator=(const Rva001EAFC1&);};
struct RevivalSourceView {char unknown00[8]; float experience; int rank; RevivalUpgradeStorage upgrades; char unknown90[4]; char record[0x18]; char unknownAC[0x14]; int heroKey;};
class Image;
class ThingTemplate {
public:
 int rva0033B479()const; const Image *getButtonImage();
 char unknown00[0x113]; unsigned char flags113; char unknown114[0x11F-0x114]; unsigned char flags11F;
 char unknown120[0x2E4-0x120]; ModuleInfo modules;
};
struct ExperienceLevelList;
struct ExperienceLevelNode;
class ExperienceLevelIterator {public: ExperienceLevelIterator(){} ExperienceLevelIterator(const ExperienceLevelIterator&o):node(o.node){} ExperienceLevelNode *node;};
struct ExperienceLevelHandle {
 ExperienceLevelHandle(){} ExperienceLevelHandle(const ExperienceLevelHandle&o):list(o.list),iter(o.iter){}
 ExperienceLevelList *list; ExperienceLevelIterator iter;
};
class ExperienceLevelStore {public:
 ExperienceLevelHandle rva00288E21(const ThingTemplate*,int)const;
 bool IsValid(ExperienceLevelHandle)const;
 int GetRequiredExperience(ExperienceLevelHandle)const;
};
extern ExperienceLevelStore *TheExperienceLevelStore;
class Rva002E06B8 {public: void *rva002E06EF();};
class CreateAHeroHero;
class CreateAHeroManager {public: const AsciiString &GetButtonImageName(const CreateAHeroHero*);};
extern CreateAHeroManager *TheCreateAHeroManager;
class ImageCollection {public: const Image *findImageByName(const AsciiString&);};
extern ImageCollection *TheMappedImageCollection;
struct RespawnIconView {char unknown00[0x118]; AsciiString name;};
class LivingWorldPlayer;
// ?CreateRevivalEntry@@YA?AVUnitRevivalEntry@@PAVLivingWorldPlayer@@PBQBURevivalSourceView@@PBVThingTemplate@@H@Z
static __declspec(noinline) UnitRevivalEntry CreateRevivalEntry(LivingWorldPlayer *player,const RevivalSourceView *const *source,const ThingTemplate *thing,int kind) {
 UnitRevivalEntry entry(thing);
 entry.revival=(kind==1);
 const RevivalSourceView *data=*source;
 entry.rank=data->rank; entry.level=data->rank; entry.experience=data->experience;
 entry.upgrades=data->upgrades;
 entry.armyID=0; entry.key=data->heroKey;
 *reinterpret_cast<Rva001EAFC1*>(entry.record)=*reinterpret_cast<const Rva001EAFC1*>(data->record);
 if(kind==0) {
  int rank=thing->rva0033B479();
  entry.rank=rank; entry.level=rank;
  ExperienceLevelHandle handle=TheExperienceLevelStore->rva00288E21(thing,rank);
  if(TheExperienceLevelStore->IsValid(handle)) entry.experience=(float)TheExperienceLevelStore->GetRequiredExperience(handle);
 } else {
  const ModuleInfo &info=thing->modules;
  for(int i=0;i<info.getCount();++i) {
   const ModuleData *module=info.getNthData(i);
   if(!module || !module->isRevival()) continue;
   const Rva004AF531 *rules=module->getRespawnData();
   const Image *image=0;
   if(thing->flags11F & 0x40) {
    const CreateAHeroHero *hero=(const CreateAHeroHero*)reinterpret_cast<Rva002E06B8*>(player)->rva002E06EF();
    if(hero) image=TheMappedImageCollection->findImageByName(TheCreateAHeroManager->GetButtonImageName(hero));
   } else {
    const AsciiString &imageName=reinterpret_cast<const RespawnIconView*>(rules)->name;
    if(!imageName.isEmpty()) image=TheMappedImageCollection->findImageByName(imageName);
    else image=const_cast<ThingTemplate*>(thing)->getButtonImage();
   }
   *reinterpret_cast<const Image**>(entry.unknown00)=image;
   entry.cost=const_cast<Rva004AF531*>(rules)->rva004AF531(entry.rank);
   entry.time=const_cast<Rva004AF531*>(rules)->rva004AF5AC(entry.rank);
  }
 }
 return entry;
}
class LivingWorldPlayer {
public: void rva002E3442(const RevivalSourceView*const*,const ThingTemplate*,int);
 void InitBuildableHeroes();
 char unknown00[0x40]; int field40; char unknown44[0x1A8-0x44]; std::vector<UnitRevivalEntry> entries;
};
// ?rva002E3442@LivingWorldPlayer@@QAEXPBQBURevivalSourceView@@PBVThingTemplate@@H@Z
void LivingWorldPlayer::rva002E3442(const RevivalSourceView*const *source,const ThingTemplate *thing,int key) {
 UnitRevivalEntry entry=CreateRevivalEntry(this,source,thing,0);
 entry.key=key;
 reinterpret_cast<std::vector<Rva002E2D10Record>*>(&entries)->push_back(reinterpret_cast<const Rva002E2D10Record&>(entry));
}

// Native2E34A9..2E3518 RET8 takes an owning entry handle by reference and
// mode. WB DE5DF0 supplies the same template lookup/revival construction.
// Keep the admitted static helper visible: ordinary MSVC optimization selects
// its witnessed EBX template input, without a handwritten calling convention.
class Rva0037DCA5 { public: void *rva0037DC52(); };
struct Rva0040DD3ARef { const RevivalSourceView *value; };
class Rva002E34A9 { public:
 void rva002E34A9(const Rva0040DD3ARef &,int);
 char unknown00[0x1A8]; std::vector<Rva002E2D10Record> entries;
};
// ?rva002E34A9@Rva002E34A9@@QAEXABURva0040DD3ARef@@H@Z
void Rva002E34A9::rva002E34A9(const Rva0040DD3ARef &source,int kind) {
 const ThingTemplate *thing=(const ThingTemplate*)reinterpret_cast<Rva0037DCA5*>(const_cast<RevivalSourceView*>(source.value))->rva0037DC52();
 if(thing) {
  UnitRevivalEntry entry=CreateRevivalEntry(reinterpret_cast<LivingWorldPlayer*>(this),&source.value,thing,kind);
  entries.push_back(reinterpret_cast<const Rva002E2D10Record&>(entry));
 }
}

// WB DE51F0 names LivingWorldPlayer::InitBuildableHeroes (LivingWorldPlayer.cpp
// asserts880..901); native2E3518..2E36AF RET0. The building-template store
// fills a key list for this player's field40; each template's SpawnArmy nugget
// lists 0x58-byte army records whose summary first entry supplies the unit.
// A HERO (kind bit0xBE) needs the player hero test; a CREATE_A_HERO-or-hero
// unit (kind bit0x5A) gets a revival entry keyed by record field4C through a
// counted entry handle. Store, nugget, record and summary views are placeholder
// spellings of the rowed providers; original types are unresolved.
enum ScienceType { SCIENCE_INVALID=-1 };
enum NameKeyType { NAMEKEY_INVALID=0 };
class ArmorTemplate;
class Rva0022C0CDSubsystem;
extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;
class Rva002E02F0 {public: void rva002E02F0(int,std::vector<ScienceType>*);};
class Rva002B6498 {public: ArmorTemplate *rva002B6498(NameKeyType);};
class BuildingNuggetView;
class LivingWorldBuildingTemplate {public: BuildingNuggetView *findNugget(const AsciiString &) const;};
class Rva00319CED {public: void *rva004E23C1();};
class Rva0040CB2CIndexedField {public: int get(int) const;};
struct SpawnArmyRecordView {char unknown00[0x4C]; int key; char unknown50[8];};
struct SpawnArmyNuggetView {char unknown00[8]; SpawnArmyRecordView *begin,*end;};
struct ArmySummaryEntryView {int unit,count;};
struct ArmySummaryView {char unknown00[0x40]; ArmySummaryEntryView *begin,*end;};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct RevivalHandleView {char unknown00[0xAC]; TargetRef00217D4C *ref; int useCount;};
class Rva002E3518Handle {
public:
 Rva002E3518Handle(const RevivalSourceView *p):value(p){if(p)++((RevivalHandleView*)p)->useCount;}
 ~Rva002E3518Handle(){if(value)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)&((RevivalHandleView*)value)->ref);}
 const RevivalSourceView *value;
};
// ?InitBuildableHeroes@LivingWorldPlayer@@QAEXXZ
void LivingWorldPlayer::InitBuildableHeroes() {
 std::vector<ScienceType> keys;
 ((Rva002E02F0*)TheLivingWorldBuildingTemplateStore)->rva002E02F0(field40,&keys);
 for(unsigned int i=0;i<keys.size();++i) {
  const LivingWorldBuildingTemplate *building=(const LivingWorldBuildingTemplate*)((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)keys[i]);
  if(!building) continue;
  const SpawnArmyNuggetView *nugget=(const SpawnArmyNuggetView*)building->findNugget(AsciiString("SpawnArmy"));
  if(!nugget) continue;
  for(unsigned int j=0;j<(unsigned int)(nugget->end-nugget->begin);++j) {
   SpawnArmyRecordView *record=&nugget->begin[j];
   const ArmySummaryView *summary=(const ArmySummaryView*)((Rva00319CED*)record)->rva004E23C1();
   if(!summary || summary->end-summary->begin==0) continue;
   const RevivalSourceView *unit=(const RevivalSourceView*)((const Rva0040CB2CIndexedField*)summary)->get(0);
   const ThingTemplate *thing=(const ThingTemplate*)((Rva0037DCA5*)unit)->rva0037DC52();
   if(!thing) continue;
   if((thing->flags11F & 0x40) && !((Rva002E06B8*)this)->rva002E06EF()) continue;
   if(thing->flags113 & 4) {
    Rva002E3518Handle handle(unit);
    rva002E3442(&handle.value,thing,record->key);
   }
  }
 }
}
