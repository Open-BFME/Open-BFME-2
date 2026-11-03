// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc 
//
// ?rva0047D90C@Rva0047D90C@@QAEXPAVObject@@W4ExitDoorType@@@Z, retail 0x0047d90c, 252 bytes. Banked partial (score 0.9795005807200929) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include "../../Include/GameLogic/ContainmentListView.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
#include <list>
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
namespace _STL {template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}
class Object;
enum ExitDoorType{DOOR0=0};
class HordeSiegeEngineContain {public:void rva0047D53A(Object*,ExitDoorType);};
template<int N>class Slots:public Slots<N-1>{public:virtual void gap(char(*)[N]);};template<>class Slots<0>{};
class ContainOwner:public Slots<42>{public:virtual void remove(Object*);};
class ContainCollection:public Slots<66>{public:virtual Rva0036AE51ListView get();};
class ContainAI:public Slots<31>{public:virtual ContainCollection *get();};
// Object as HordeSiegeEngineContain.cpp spells it (neutral names, target offsets).
class Object
{
public:
	void *getTemplate() const { return m_template; }
	void *m_vtable;
	void *m_template;
	unsigned char unknown08[0x10C - 8];
	unsigned m_modelConditionFlags[19];
	unsigned char m_pad158[0x250 - 0x158];
	ContainAI *m_contain;
	unsigned char m_pad254[0x274 - 0x254];
	Object *m_containedBy274;
	unsigned char m_pad278[0x454 - 0x278];
	bool m_blocked454;
};
class Rva0047D90C {public:void rva0047D90C(Object*,ExitDoorType);char pad[0x100];bool busy;HordeSiegeEngineContain *primary(){return (HordeSiegeEngineContain*)((char*)this-0x30);}};
void Rva0047D90C::rva0047D90C(Object *object,ExitDoorType door)
{
 if(busy)return;
 if(*((unsigned char*)object->getTemplate()+0x115)&0x20){
  ContainAI *ai=object->m_contain;if(!ai)return;
  ContainCollection *contain=ai->get();if(!contain)return;
  ContainmentList contents=contain->get().rva0036AE51();
  ContainmentList::iterator it;
  for(it=contents.begin();it!=contents.end();++it){
   Object *child=(Object*)containmentFirstWord(*it);
   if(!child->m_blocked454){((ContainOwner*)contain)->remove(child);primary()->rva0047D53A(child,door);}
  }
  for(it=contents.begin();it!=contents.end();++it){
   Object *child=(Object*)containmentFirstWord(*it);
   ((ContainOwner*)contain)->remove(child);primary()->rva0047D53A(child,door);
  }
 }
 primary()->rva0047D53A(object,door);
}
