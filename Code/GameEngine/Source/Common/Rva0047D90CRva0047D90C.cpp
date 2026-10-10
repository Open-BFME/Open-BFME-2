// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /I.
//
// ?rva0047D90C@Rva0047D90C@@QAEXPAVObject@@W4ExitDoorType@@@Z, retail 0x0047d90c, 252 bytes. Banked partial (score 0.9795005807200929) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include "Code/GameEngine/Include/GameLogic/ContainmentListView.h"
namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}
class Object;
enum ExitDoorType{DOOR0=0};
class HordeSiegeEngineContain {public:void rva0047D53A(Object*,ExitDoorType);};
template<int N>class Slots:public Slots<N-1>{public:virtual void gap(char(*)[N]);};template<>class Slots<0>{};
class ContainOwner:public Slots<42>{public:virtual void remove(Object*);};
class ContainCollection:public Slots<66>{public:virtual Rva0036AE51ListView get();};
class ContainAI:public Slots<31>{public:virtual ContainCollection *get();};
class Object {public:void *vtable;void *type; void *getTemplate()const{return type;}char pad8[0x250-8];ContainAI *ai;char pad254[0x454-0x254];bool blocked;};
class Rva0047D90C {public:void rva0047D90C(Object*,ExitDoorType);char pad[0x100];bool busy;HordeSiegeEngineContain *primary(){return (HordeSiegeEngineContain*)((char*)this-0x30);}};
void Rva0047D90C::rva0047D90C(Object *object,ExitDoorType door)
{
 if(busy)return;
 if(*((unsigned char*)object->getTemplate()+0x115)&0x20){
  ContainAI *ai=object->ai;if(!ai)return;
  ContainCollection *contain=ai->get();if(!contain)return;
  ContainmentList contents=contain->get().rva0036AE51();
  ContainmentList::iterator it;
  for(it=contents.begin();it!=contents.end();++it){
   Object *child=(Object*)containmentFirstWord(*it);
   if(!child->blocked){((ContainOwner*)contain)->remove(child);primary()->rva0047D53A(child,door);}
  }
  for(it=contents.begin();it!=contents.end();++it){
   Object *child=(Object*)containmentFirstWord(*it);
   ((ContainOwner*)contain)->remove(child);primary()->rva0047D53A(child,door);
  }
 }
 primary()->rva0047D53A(object,door);
}
