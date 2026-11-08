// cl: /O1 /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Include
// stlport
//
// ?update@Rva00466C94@@UAE?AW4UpdateSleepTime@@XZ @ 0x00466C94, 163 bytes.
// Slot 0 of its update-interface table (update); it runs OpenContain's update
// (0x004640BE) first. Both are spelled as virtual overrides.
// Dedicated TU: the owner file Rva00466C04Heal.cpp carries the /DNDEBUG /MD
// row for 0x466C04 and must keep its flags; this body needs /O1 /G7.
// R1/S2 equal-arm carrier on the reserve() object argument closes the
// argument-push/register order: (obj->objectTemplate ? obj : obj).
#include "GameLogic/ContainmentListView.h"

// Compare the typed nodes locally; the shared base wrapper is not called by retail.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits> &a,
                              const _List_iterator<T, RightTraits> &b)
{ return a._M_node != b._M_node; }
}

namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}
class Object {public:void* vptr;void* objectTemplate;};
struct HealData {char pad[0x98];unsigned frames;};
class DoorInterface {public:virtual void d0();virtual int reserve(void*,Object*);virtual void exit(Object*,int);};
struct HealPrimary {void*vptr;HealData* data;char pad[0x30-8];DoorInterface doors;};
enum UpdateSleepTime {UPDATE_SLEEP_NONE=1};
class OpenContain {public:virtual UpdateSleepTime update();};
#include "../../../../Include/GameLogic/Module/Rva0046247DPair.h"
class Rva0046247D {public:void*rva0046247D(Rva0046247DPair&);};
class Rva00466C04 {public:bool rva00466C04(Object*,unsigned);};
class Rva00466C94 {public:virtual UpdateSleepTime update();private:__forceinline HealPrimary* owner(){return reinterpret_cast<HealPrimary*>(reinterpret_cast<char*>(this)-0x10);}};
UpdateSleepTime Rva00466C94::update(){
 reinterpret_cast<OpenContain*>(this)->OpenContain::update();
 const HealData* data=owner()->data;
 Rva0046247DPair pair;
 ContainmentList riders=reinterpret_cast<Rva0036AE51ListView*>(reinterpret_cast<Rva0046247D*>(owner())->rva0046247D(pair))->rva0036AE51();
 bool done;Object* obj;
 ContainmentList::const_iterator it=riders.begin();
 while(it!=riders.end()){
  obj=reinterpret_cast<Object*>(containmentFirstWord(*it));++it;
  done=reinterpret_cast<Rva00466C04*>(owner())->rva00466C04(obj,data->frames);
  if(done==true){int door=owner()->doors.reserve(obj->objectTemplate, (obj->objectTemplate ? obj : obj));if(door!=-1)owner()->doors.exit(obj,door);}
 }
 return UPDATE_SLEEP_NONE;
}
