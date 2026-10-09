// cl: /O1 /Ob1 /G7 /EHsc /MD /arch:SSE /DNDEBUG /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib
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
 char unknown00[0x11F]; unsigned char flags11F;
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
 char unknown00[0x1A8]; std::vector<UnitRevivalEntry> entries;
};
// ?rva002E3442@LivingWorldPlayer@@QAEXPBQBURevivalSourceView@@PBVThingTemplate@@H@Z
void LivingWorldPlayer::rva002E3442(const RevivalSourceView*const *source,const ThingTemplate *thing,int key) {
 UnitRevivalEntry entry=CreateRevivalEntry(this,source,thing,0);
 entry.key=key;
 reinterpret_cast<std::vector<Rva002E2D10Record>*>(&entries)->push_back(reinterpret_cast<const Rva002E2D10Record&>(entry));
}
