// ?rva00466C94@Rva00466C94@@QAEHXZ
// partial score=0.85 date=2026-10-10
// ?rva00466C94@Rva00466C94@@QAEHXZ
// partial score=0.85 date=2026-10-10
// cl: /O1 /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Include
// stlport
#include "GameLogic/ContainmentListView.h"
namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}
class Object {public:void* vptr;void* objectTemplate;};
struct HealData {char pad[0x98];unsigned frames;};
class DoorInterface {public:virtual void d0();virtual int reserve(void*,Object*);virtual void exit(Object*,int);};
struct HealPrimary {void*vptr;HealData* data;char pad[0x30-8];DoorInterface doors;};
class Rva004640BE {public:int rva004640BE();};
struct Rva0046247DPair {void*a;void*b;};
class Rva0046247D {public:void*rva0046247D(Rva0046247DPair&);};
class Rva00466C04 {public:bool rva00466C04(Object*,unsigned);};
class Rva00466C94 {public:int rva00466C94();private:__forceinline HealPrimary* owner(){return reinterpret_cast<HealPrimary*>(reinterpret_cast<char*>(this)-0x10);}};
int Rva00466C94::rva00466C94(){
 reinterpret_cast<Rva004640BE*>(this)->rva004640BE();
 const HealData* data=owner()->data;
 Rva0046247DPair pair;
 ContainmentList riders=reinterpret_cast<Rva0036AE51ListView*>(reinterpret_cast<Rva0046247D*>(owner())->rva0046247D(pair))->rva0036AE51();
 bool done;Object* obj;
 ContainmentList::const_iterator it=riders.begin();
 while(it!=riders.end()){
  obj=reinterpret_cast<Object*>(containmentFirstWord(*it));++it;
  done=reinterpret_cast<Rva00466C04*>(owner())->rva00466C04(obj,data->frames);
  if(done==true){int door=owner()->doors.reserve(obj->objectTemplate,obj);if(door!=-1)owner()->doors.exit(obj,door);}
 }
 return 1;
}
