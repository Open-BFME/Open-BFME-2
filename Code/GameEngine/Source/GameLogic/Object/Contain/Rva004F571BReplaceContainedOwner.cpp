// cl: /ICode/GameEngine/Source/Common /ICode/GameEngine/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// Native full 004F571B..004F579C RET4; corresponding WB1103A20 is unnamed.
// ZH TunnelTracker::onTunnelDestroyed is the semantic guide; BFME2 returns
// whether the tunnel count reached zero instead of doing donor destruction here.
// Target56FC caller/add body and this body prove IDs8/count1C; Object74 ID and
// contained-by274 are target accesses. Keep the existing neutral ABI name.
// A same-valued dead-pointer guard on the Boolean result selects native
// ESI receiver and direct memory comparison, without emitted condition work.
#include <list>
#include "GameLogicObjectLookupView.h"
#include "GameLogic/ContainmentListView.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
extern GameLogic *TheGameLogic;
class Object {public:void onContainedBy(Object*); ObjectID getID()const{return id;} const Object*getContainedBy()const{return contained;}private:char pad[0x74];ObjectID id;char pad78[0x274-0x78];Object *contained;};
class Rva00466398 {public:Rva0036AE51ListView rva00466398();};
class Rva004F56FC {public:bool rva004F571B(const Object*);private:char pad[8];_STL::list<int> ids;char padC[0x1C-0xC];unsigned count;};
bool Rva004F56FC::rva004F571B(const Object*dead){
 --count;ids.remove((int)dead->getID());
 if(count>0){
  Object *replacement=TheGameLogic->findObjectByID((ObjectID)ids.front());
  const Rva0036AE51ListView &view=((Rva00466398*)this)->rva00466398();ContainmentList *list=view.b;
  for(ContainmentList::iterator it=list->begin();it!=list->end();){
   Object *object=(Object*)containmentFirstWord(*it);++it;
   if(object->getContainedBy()==dead)object->onContainedBy(replacement);
  }
 }
 return count==0 && (dead?true:true);
}

inline __declspec(noinline) Rva0036AE51ListView Rva00466398::rva00466398(){Rva0036AE51ListView out;out.a=this?(void*)((char*)this+4):(void*)0;out.b=(ContainmentList*)((char*)this+16);return out;}
