// ??$_S_sort@PAXV?$allocator@PAX@_STL@@VRva004CEAB7@@@_STL@@YAXAAV?$list@PAXV?$allocator@PAX@_STL@@@0@VRva004CEAB7@@@Z
// partial score=0.98 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHs /EHc- /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <list>
//
// ??0HordeNotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00253D88, 40 bytes. Behavior-side ctor completing the
// HordeNotifyTargetsOfImminentProbableCrushingUpdate file-unit (poolkey
// rowed at 0x253DB2, behavior instance factory rowed at 0x2551CF news 0x34
// with this ctor as sole raw caller; the non-Horde twin keeps its own
// poolkey 0x253E8E, factory 0x255207 and rowed ctor 0x253E64).
//
// Shape: frameless single-base ctor over the rowed UpdateModule base
// 0x253390 with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// rowed UpdateModule spelling).

extern "C" const void *const vtbl_00BEFF90[];  // folded, 80 classes; via ??_7AIGateUpdate@@6BBehaviorModuleOther@@@
#pragma comment(linker, "/alternatename:_vtbl_00BEFF90=??_7AIGateUpdate@@6BBehaviorModuleOther@@@")

extern "C" const void *const vtbl_00BF17EC[];  // ??_7Rva00253E19@@6BRva00253E19_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00BF17EC=??_7Rva00253E19@@6BRva00253E19_B2@@@")
extern "C" const void *const vtbl_00BF17F8[];  // ??_7Rva00253E19@@6BRva0024A797@@@
#pragma comment(linker, "/alternatename:_vtbl_00BF17F8=??_7Rva00253E19@@6BRva0024A797@@@")

class Thing;
class ModuleData;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
};

class HordeNotifyTargetsOfImminentProbableCrushingUpdate : public UpdateModule
{
public:
	HordeNotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0HordeNotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00253D88
HordeNotifyTargetsOfImminentProbableCrushingUpdate::HordeNotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BF17F8);
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)vtbl_00BEFF90);
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)vtbl_00BF17EC);
}

// Native4CEB14..4CEB76. STLport4.5.3 _S_merge algorithm, from BFME1
// ba7dd inputs/vendor/stlport/stl/_list.c, using the verified distance helper.
// Nodes carry pointer-sized payloads at8; original list/owner names unknown.
// This helper's comparator home is the neighboring non-Horde constructor TU.
// Keep its declaration out of line: seeing the body changes register allocation.

// Retain the header operations in their observed inline form, avoiding
// unrelated out-of-line template copies from this caller unit.
namespace _STL {
template <class T, class Traits>
static inline bool operator==(const _List_iterator<T, Traits> &a, const _List_iterator<T, Traits> &b) { return a._M_node == b._M_node; }
template <> __forceinline allocator<void *>::~allocator() throw() {}
template <> __forceinline _List_iterator<void *, _Nonconst_traits<void *> >::_List_iterator(_List_node<void *> *p) : _List_iterator_base(p) {}
template <> __forceinline _List_node<void *> *allocator<_List_node<void *> >::allocate(size_type n, const void *) const {
 return n != 0 ? reinterpret_cast<_List_node<void *> *>(allocator<char>::allocate(n * sizeof(_List_node<void *>), 0)) : 0;
}
template <> __forceinline allocator<_List_node<void *> > &__stl_alloc_rebind<_List_node<void *>, _List_node<void *> >(allocator<_List_node<void *> > &a, const _List_node<void *> *) { return a; }
typedef _STLP_alloc_proxy<_List_node<void *> *, _List_node<void *>, allocator<_List_node<void *> > > ListProxy;
template <> __forceinline _List_node<void *> *ListProxy::allocate(size_t n) {
 return reinterpret_cast<allocator<_List_node<void *> >&>(*this).allocate(n, 0);
}
}

class Rva004CEAB7 {
public: bool rva004CEAB7(void *,void *);
float x,y,z;
Rva004CEAB7(const Rva004CEAB7& a):x(a.x),y(a.y),z(a.z){}
bool operator()(void *a,void *b) {return rva004CEAB7(a,b);}
};
struct Rva004CEB14Node : _STL::_List_node_base { void *value; };
struct Rva004CEB14List { Rva004CEB14Node *head; };
// Native pointer-list sort; stdlib identities are instantiated ABI views,
// while the application owner and original pointee spelling remain unknown.
namespace _STL { template <> void _S_merge<void *, allocator<void *>, Rva004CEAB7>(list<void *> &, list<void *> &, Rva004CEAB7); }
template void _STL::_S_sort<void *, _STL::allocator<void *>, Rva004CEAB7>(_STL::list<void *> &, Rva004CEAB7);

namespace _STL {
template <> void _S_merge<void *, allocator<void *>, Rva004CEAB7>(list<void *> &dst, list<void *> &src, Rva004CEAB7 comp) {
 Rva004CEB14List &dstView=*reinterpret_cast<Rva004CEB14List *>(&dst);
 Rva004CEB14List &srcView=*reinterpret_cast<Rva004CEB14List *>(&src);
 Rva004CEB14Node *first1=(Rva004CEB14Node *)dstView.head->_M_next,*last1=dstView.head;
 Rva004CEB14Node *first2=(Rva004CEB14Node *)srcView.head->_M_next,*last2=srcView.head;
 while(first1!=last1 && first2!=last2) {
  if(comp.rva004CEAB7(first2->value,first1->value)) {
   Rva004CEB14Node *next=(Rva004CEB14Node *)first2->_M_next;
   _List_global<bool>::_Transfer((_List_node_base *)first1,(_List_node_base *)first2,(_List_node_base *)next);
   first2=next;
  } else first1=(Rva004CEB14Node *)first1->_M_next;
 }
 if(first2!=last2)_List_global<bool>::_Transfer((_List_node_base *)last1,(_List_node_base *)first2,(_List_node_base *)last2);
}
}
