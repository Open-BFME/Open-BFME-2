// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Native293EFF..2940B9/442B; Object Snapshot table7FC2F0 slot04
// holds this body after the deleting-dtor adjustor299C89. The receiver
// is Object+60, as independently established by the3414B xfer owner.
// ZH Object::loadPostProcess at donor575ba2b04 supplies the containedBy-ID
// recovery spine; all additional fields and actions below are retail facts.
// Target goal44 is Object+A4. Native trigger-name list3A8 has two-word
// elements; CameraMarker is solely the existing erase ABI carrier, with
// its first word used as a32-bit index. Original list element type unknown.
// The seven-byte getter reads tracker2C->word0C, proven independently;
// its folded MeshGeometry owner does not establish this receiver's type.
// The delayed-grant flag backup is the native EH lifetime. The scoring
// flag is separately restored after the tracked operations. Retail calls
// the existing128B bitset self-OR at224; its original purpose is unknown.
#include <list>
#include <bitset>
#include "ascii_string.h"
#include "../../Common/GameLogicObjectLookupView.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
extern GameLogic*TheGameLogic;
enum ObjectStatusTypes{STATUS_51=51};
struct LoadTemplate{char pad[0x10f];unsigned char kind10F;char pad110[15];unsigned char kind11F;};
class Object{public:bool testStatus(ObjectStatusTypes)const;void tempRemoveObjectFromWorld();int rva0028B511()const;char pad[4];LoadTemplate*templ;};
class Rva004DD843{public:void LoadPostProcess();};
struct CameraMarker{~CameraMarker();CameraMarker*index;AsciiString name;};
namespace _STL {template<> __declspec(noinline) void _Base_bitset<32>::_M_do_or(const _Base_bitset<32>&);}
class TerrainLogic{public:
virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38();
virtual void*slot39(const AsciiString&);
};
extern TerrainLogic*TheTerrainLogic;
class WeaponSet{public:void updateWeaponSet(const Object*);};
class Pathfinder{public:void rva002EF2A6(Object*);void AddObjectToPathfindMap(Object*);};
class Rva0022AEE4Subsystem{public:char pad[16];Pathfinder*pathfinder;};
class AI;
extern AI *TheAI;
class DelayedExperienceLevelGrantSystem{public:char pad[20];bool value;};
extern DelayedExperienceLevelGrantSystem*TheDelayedExperienceLevelGrantSystem;
class LoadDelayedFlagBackup{public:LoadDelayedFlagBackup(){old=TheDelayedExperienceLevelGrantSystem->value;TheDelayedExperienceLevelGrantSystem->value=false;}~LoadDelayedFlagBackup(){TheDelayedExperienceLevelGrantSystem->value=old;}bool old;};
class CreateAHeroManager{public:void BindHeroToObjectAndUpdate(Object*);};extern CreateAHeroManager*TheCreateAHeroManager;
struct Rva00293EFFXPNode {char pad[12];int value;};
class Rva00293EFFXPField {public:int getField();char pad[0x2C];Rva00293EFFXPNode*node;};
class Rva003BD306Target{public:void rva0039B548();};
class ExperienceTracker{public:void rva0039B315(float,bool,bool,bool,bool);};
class Rva0039B20C{public:void rva0039B227(int);};
struct LoadScoringView{char pad[0x98];bool enabled;};
struct LoadXPView{char pad[16];float points;};
struct LoadBinding{void*region;int opaque;};
class Rva00293EFFLoadView{public:virtual~Rva00293EFFLoadView();virtual void LoadPostProcess();
char pad04[0x40];Rva004DD843*goal;char pad48[0x204-0x48];void*xp;char pad208[12];Object*contained;ObjectID containedId;char pad21C[8];_STL::_Base_bitset<32>mask;char pad2A4[0x2d0-0x2a4];WeaponSet weapons;char pad2D1[0x360-0x2d1];LoadBinding binding[9];_STL::list<CameraMarker>names;
__forceinline Object*original(){return(Object*)((char*)this-0x60);}
};
void Rva00293EFFLoadView::LoadPostProcess(){
 if(goal)goal->LoadPostProcess();
 if(containedId!=INVALID_OBJECT_ID)contained=TheGameLogic->findObjectByID(containedId);else contained=0;
 if(original()->testStatus(STATUS_51))original()->tempRemoveObjectFromWorld();
 _STL::list<CameraMarker>::iterator it=names.begin();while(it!=names.end()){
 int index=(int)it->index;AsciiString name=it->name;binding[index].region=TheTerrainLogic->slot39(name);it=names.erase(it);
 }
 weapons.updateWeaponSet(original());if(original()->rva0028B511()!=1)((Rva0022AEE4Subsystem *)TheAI)->pathfinder->rva002EF2A6(original());
 if(!(original()->templ->kind10F&0x10))((Rva0022AEE4Subsystem *)TheAI)->pathfinder->AddObjectToPathfindMap(original());
 if(original()->templ->kind11F&0x40){
 LoadDelayedFlagBackup delayed;
 TheCreateAHeroManager->BindHeroToObjectAndUpdate(original());
 bool scoring=((LoadScoringView*)TheGameLogic)->enabled;((LoadScoringView*)TheGameLogic)->enabled=false;
 float points=((LoadXPView*)xp)->points;int saved=((Rva00293EFFXPField*)xp)->getField();((Rva003BD306Target*)xp)->rva0039B548();
 ((ExperienceTracker*)xp)->rva0039B315(points,false,false,false,false);((Rva0039B20C*)xp)->rva0039B227(saved);
 mask._M_do_or(mask);((LoadScoringView*)TheGameLogic)->enabled=scoring;
 }
}
