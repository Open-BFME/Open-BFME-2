// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata
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
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
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
class Object;
#include "../../Common/Thing/thing.h"
#include "../../../Include/Common/ThingTemplate.h"
#include "../../../Include/GameLogic/Module/PathfinderPosGoalManager.h"
struct CameraMarker{~CameraMarker();CameraMarker*index;AsciiString name;};
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<CameraMarker> >::deallocate(_List_node<CameraMarker>* __p, size_t __n) const {
 _STLP_ASSERT( (__p == 0) == (__n == 0) )
 if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<CameraMarker>*,_List_node<CameraMarker>,allocator<_List_node<CameraMarker> > >::deallocate(_List_node<CameraMarker>* __p, size_t __n) {
 __stl_alloc_rebind(static_cast<allocator<_List_node<CameraMarker> >&>(*this),(_List_node<CameraMarker>*)0).deallocate(__p,__n);
}
}

namespace _STL {template<> __declspec(noinline) void _Base_bitset<32>::_M_do_or(const _Base_bitset<32>&);}
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic*TheTerrainLogic;
class WeaponSet{public:void updateWeaponSet(const Object*);};
#include "../../../Include/GameLogic/AIPathfind.h"
class Rva0022AEE4Subsystem{public:char pad[16];Pathfinder*pathfinder;};
class AI;
extern AI *TheAI;
class DelayedExperienceLevelGrantSystem{public:char pad[20];bool value;};
extern DelayedExperienceLevelGrantSystem*TheDelayedExperienceLevelGrantSystem;
class LoadDelayedFlagBackup{public:LoadDelayedFlagBackup(){old=TheDelayedExperienceLevelGrantSystem->value;TheDelayedExperienceLevelGrantSystem->value=false;}~LoadDelayedFlagBackup(){TheDelayedExperienceLevelGrantSystem->value=old;}bool old;};
#include "../../../Include/GameLogic/CreateAHeroManager.h"
extern CreateAHeroManager*TheCreateAHeroManager;
struct Rva00293EFFXPNode {char pad[12];int value;};
class Rva00293EFFXPField {public:int getField();char pad[0x2C];Rva00293EFFXPNode*node;};
#include "../../../Include/GameLogic/Module/Rva003BD306Target.h"
#include "../../../Include/GameLogic/ExperienceTracker.h"
#include "../../../Include/GameLogic/Module/Rva0039B20C.h"
struct LoadScoringView{char pad[0x98];bool enabled;};
struct LoadXPView{char pad[16];float points;};
struct LoadBinding{void*region;int opaque;};
class Object : public Thing, public Snapshot {
public:
 bool testStatus(ObjectStatusTypes)const;void tempRemoveObjectFromWorld();int rva0028B511()const;
 virtual void loadPostProcess();virtual const char *GetSnapshotName() const;
protected:
 virtual ~Object();virtual void xfer(Xfer *);
public:
char pad04[0x40];PathfinderPosGoalManager*goal;char pad48[0x204-0x48];void*xp;char pad208[12];Object*contained;ObjectID containedId;char pad21C[8];_STL::_Base_bitset<32>mask;char pad2A4[0x2d0-0x2a4];WeaponSet weapons;char pad2D1[0x360-0x2d1];LoadBinding binding[9];_STL::list<CameraMarker>names;
__forceinline Object*original(){return this;}
};
void Object::loadPostProcess(){
 if(goal)goal->LoadPostProcess();
 if(containedId!=INVALID_OBJECT_ID)contained=TheGameLogic->findObjectByID(containedId);else contained=0;
 if(original()->testStatus(STATUS_51))original()->tempRemoveObjectFromWorld();
 _STL::list<CameraMarker>::iterator it=names.begin();while(it!=names.end()){
 int index=(int)it->index;AsciiString name=it->name;binding[index].region=TheTerrainLogic->getTriggerAreaByName(name);it=names.erase(it);
 }
 weapons.updateWeaponSet(original());if(original()->rva0028B511()!=1)((Rva0022AEE4Subsystem *)TheAI)->pathfinder->AdjustLayer(original());
 if(!(original()->m_template->m_kindof[1]&0x10000000))((Rva0022AEE4Subsystem *)TheAI)->pathfinder->AddObjectToPathfindMap(original());
 if(original()->m_template->m_kindof[5]&0x40000000){
 LoadDelayedFlagBackup delayed;
 TheCreateAHeroManager->BindHeroToObjectAndUpdate(original());
 bool scoring=((LoadScoringView*)TheGameLogic)->enabled;((LoadScoringView*)TheGameLogic)->enabled=false;
 float points=((LoadXPView*)xp)->points;int saved=((Rva00293EFFXPField*)xp)->getField();((Rva003BD306Target*)xp)->rva0039B548();
 ((ExperienceTracker*)xp)->rva0039B315(points,false,false,false,false);((Rva0039B20C*)xp)->rva0039B227(saved);
 mask._M_do_or(mask);((LoadScoringView*)TheGameLogic)->enabled=scoring;
 }
}
