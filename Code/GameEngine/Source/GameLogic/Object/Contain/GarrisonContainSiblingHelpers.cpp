// cl: /O1 /Oy /G7 /arch:SSE /DNDEBUG /MD /EHsc 
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

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
// Target helpers00478BE0/00478FD7: WB11A4120/11A6EE0 and the
// GarrisonContain update caller00479643 establish the subsystem and purpose.
// ZH GarrisonContain healing/move loops are the semantic guide. The target
// uses its verified pair view0046247D with no owner destructor in either body.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Object;
#include "../../../Common/Thing/thing.h"
#include "../../../../Include/GameLogic/Module/Rva0046247DPair.h"
typedef _STL::list<Object*> ChildList;
class Rva0046247D { public: inline __declspec(noinline) void rva0046247D(Rva0046247DPair&result){void*base=this;result.m00=base?(ContainModuleInterface*)((char*)base+0x20):0;result.m04=(char*)base+0x54;} };
struct ChildHealData { char data00[0x98]; bool heal; char pad99[3]; float healFrames; bool move; };
struct GarrisonOwnerPosition { char data00[0x38]; Coord3D position; };
class B0 { public: virtual void b0(); int m_pad4; Object *m_object; };
class GarrisonContain : public B0 {
public:
 void rva00478BE0();
 void rva00478FD7();
protected: void healSingleObject(Object*,float);
};
void GarrisonContain::rva00478BE0()
{
 const ChildHealData *modData=(const ChildHealData *)m_pad4;
 if(!modData->heal) return;
 Rva0046247DPair contained;
 ((Rva0046247D*)this)->rva0046247D(contained);
 const ChildList &list=*(const ChildList *)contained.m04;
 for(ChildList::const_iterator it=list.begin();it!=list.end();++it)
  healSingleObject(*it,modData->healFrames);
}
void GarrisonContain::rva00478FD7()
{
 if(!((const ChildHealData *)m_pad4)->move) return;
 Rva0046247DPair contained;
 ((Rva0046247D*)this)->rva0046247D(contained);
 const ChildList &list=*(const ChildList *)contained.m04;
 for(ChildList::const_iterator it=list.begin();it!=list.end();++it)
  ((Thing*)*it)->setPosition(&((GarrisonOwnerPosition *)m_object)->position);
}
