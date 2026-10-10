// cl: /O1 /Oy /G7 /arch:SSE /DNDEBUG /MD /EHsc /I.
// stlport
// Provider46247D is the already rowed26-byte pair writer: its inline/noinline
// copy emits the same entire body and relocations here. Visibility proves the
// out argument is the only receiver storage written, matching native callee
// knowledge and closing both loop register allocations. /Oy leaves the getter
// frameless while the two address-taking callers retain their native EBP frames.
// Native478BE0..478C2C /478FD7..47901B and WB11A4120/11A6EE0 establish
// each distinct helper. BF1/ZH GarrisonContain loops are semantic guides;
// receiver/data offsets and list traversal are target evidence.
#include <list>
// Target helpers00478BE0/00478FD7: WB11A4120/11A6EE0 and the
// GarrisonContain update caller00479643 establish the subsystem and purpose.
// ZH GarrisonContain healing/move loops are the semantic guide. The target
// uses its verified pair view0046247D with no owner destructor in either body.
#include "Code/Libraries/Include/Lib/Coord3D.h"
class Object;
class Thing { public: void setPosition(const Coord3D*); };
struct ChildNode { ChildNode *next,*prev; Object *object; };
typedef _STL::list<Object*> ChildList;
struct Rva0046247DPair { void *first; ChildList *second; };
class Rva0046247D { public: inline __declspec(noinline) void rva0046247D(Rva0046247DPair&result){void*base=this;result.first=base?(char*)base+0x20:0;result.second=(ChildList*)((char*)base+0x54);} };
struct ChildHealData { char data00[0x98]; bool heal; char pad99[3]; float healFrames; bool move; };
struct GarrisonOwnerPosition { char data00[0x38]; Coord3D position; };
class GarrisonContain {
public:
 void rva00478BE0();
 void rva00478FD7();
protected: void healSingleObject(Object*,float);
public:
 char data00[4]; ChildHealData *data; GarrisonOwnerPosition *object;
};
void GarrisonContain::rva00478BE0()
{
 const ChildHealData *modData=data;
 if(!modData->heal) return;
 Rva0046247DPair contained;
 ((Rva0046247D*)this)->rva0046247D(contained);
 const ChildList &list=*contained.second;
 for(ChildList::const_iterator it=list.begin();it!=list.end();++it)
  healSingleObject(*it,modData->healFrames);
}
void GarrisonContain::rva00478FD7()
{
 if(!data->move) return;
 Rva0046247DPair contained;
 ((Rva0046247D*)this)->rva0046247D(contained);
 const ChildList &list=*contained.second;
 for(ChildList::const_iterator it=list.begin();it!=list.end();++it)
  ((Thing*)*it)->setPosition(&object->position);
}
