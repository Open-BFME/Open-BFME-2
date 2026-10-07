// cl: /D_STLP_NO_EXCEPTIONS /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// Dedicated /O1 /D_STLP_NO_EXCEPTIONS + bfmealloc instantiation so _M_create_node calls the byte
// allocator at 0x307F0 and out-of-line _Construct. The existing map<int,int>
// units lack bfmealloc and inlined a different shape.
// A separate retail copy specialization owns 0x21C2CC; the unsuffixed
// compiler name is already claimed by the distinct 0x2CF6CF implementation.
// Keep this TU-local method spelling address-scoped without changing its type.
#define _M_copy _M_copy_0021C2CC
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#undef _M_copy
template class _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >;

typedef _STL::_Rb_tree<int,_STL::pair<const int,int>,_STL::_Select1st<_STL::pair<const int,int> >,_STL::less<int>,_STL::allocator<_STL::pair<const int,int> > > IntCopyTree;
template IntCopyTree::_Rb_tree(const IntCopyTree &);
