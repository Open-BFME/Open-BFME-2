// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$_Construct@V?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@V12@@_STL@@YAXPAV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@0@ABV10@@Z @0x004740AD (45B).
// STLport placement-copy for list<Object*> element: null-guarded placement new
// over a single element, calls rowed list copy ctor 0x004702FB. Called per element
// by uninitialized_copy 0x004740DA and uninitialized_fill_n 0x00474100. Same 45B
// EH shape as other _Constructs.
#include <memory>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class Object;
template void _STL::_Construct<_STL::list<Object *, _STL::allocator<Object *> >, _STL::list<Object *, _STL::allocator<Object *> > >(_STL::list<Object *, _STL::allocator<Object *> > *, const _STL::list<Object *, _STL::allocator<Object *> > &);
