// ?rva004F571B@Rva004F56FC@@QAE_NPBVObject@@@Z
// partial score=0.8842945736 date=2026-10-10
// cl: /ICode/GameEngine/Source/Common /ICode/GameEngine/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
#include <list>
#include "GameLogicObjectLookupView.h"
#include "GameLogic/ContainmentListView.h"
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
 return count==0;
}

inline __declspec(noinline) Rva0036AE51ListView Rva00466398::rva00466398(){Rva0036AE51ListView out;out.a=this?(void*)((char*)this+4):(void*)0;out.b=(ContainmentList*)((char*)this+16);return out;}
