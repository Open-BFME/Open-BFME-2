// cl: /O1 /Oy /G7 /MD /EHs /EHc- /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_CRTIMP= /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// Native2A8E7B..2A8F24 plus owning table7FDB94 slot10 identify manager update.
// The canonical Subsystem12/SnapshotC manager view agrees with Register/newMap/
// xfer/lifetime/reset. WB E8DCD0 and rowed4E9710 independently prove the
// pointer array914 contains AIGameTeam instances; the inherited ModuleData
// pointer spelling is retained as an opaque ABI view and cast at the use site.
// Collectors908 update via the existing4DF95D view; hero IDs934 erase missing
// GameLogic objects using a cached end refreshed after erase. Actual class
// internals and original collector/builder types remain unresolved.
#include <vector>
#include <map>
#include <hash_map>
#include <new>
typedef int Bool;
#include "subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Rva002A8D49 {public:Rva002A8D49();~Rva002A8D49();unsigned char data[0x8f8];};
class Rva002A8B8C {public:~Rva002A8B8C();};
struct ManagerCollectorStorage {unsigned words[3];__forceinline ~ManagerCollectorStorage(){reinterpret_cast<Rva002A8B8C*>(this)->~Rva002A8B8C();}};
struct Rva002A9706Element {char bytes[1];bool operator<(const Rva002A9706Element&)const;bool operator==(const Rva002A9706Element&)const;};
namespace _STL {template<> struct hash<Rva002A9706Element>{unsigned operator()(const Rva002A9706Element&) const;};}
class Rva002A8FE0 {public:~Rva002A8FE0();void rva002A8FE0();unsigned words[5];};
class Rva004E9337 {public:void rva004E9337();};
class ObjectCreationList {public:ObjectCreationList();__forceinline ~ObjectCreationList(){reinterpret_cast<Rva004E9337*>(this)->rva004E9337();}unsigned words[3];};
class ModuleData;
#include "../../Common/GameLogicObjectLookupView.h"
class Rva002A8F24:public SubsystemInterface,public Snapshot {
public:Rva002A8F24();virtual ~Rva002A8F24();virtual void init(){}virtual void reset();virtual void update();virtual void loadPostProcess(){}virtual const char*GetSnapshotName()const{return "SkirmishAIManager";}virtual void xfer(Xfer*);
 Rva002A8D49 data10;
 ManagerCollectorStorage collectors908;
 _STL::vector<const ModuleData*>teams914;
 Rva002A8FE0 builders920;
 _STL::vector<ObjectID>heroIDs934;
 ObjectCreationList*owned940;
};

namespace _STL {template<> vector<ObjectID>::iterator vector<ObjectID>::erase(iterator);}
class Rva004DF95DOwner {public:void rva004DF95D();};
class Object;
extern GameLogic*TheGameLogic;
class AIGameTeam {public:void update();};
void Rva002A8F24::update(){
 if(teams914.empty() || TheGameLogic->getFrame()<10)return;
 typedef _STL::map<int,Rva004DF95DOwner*> Collectors;
 Collectors& collectors=*reinterpret_cast<Collectors*>(&collectors908);
 for(Collectors::iterator i=collectors.begin();i!=collectors.end();++i)i->second->rva004DF95D();
 ObjectID*end=heroIDs934.end();
 for(ObjectID*i=heroIDs934.begin();i!=end;){
  if(!TheGameLogic->findObjectByID(*i)){i=heroIDs934.erase(i);end=heroIDs934.end();}
  else ++i;
 }
 for(_STL::vector<const ModuleData*>::iterator i=teams914.begin();i!=teams914.end();++i)
  reinterpret_cast<AIGameTeam*>(const_cast<ModuleData*>(*i))->update();
}
