// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// A vendored instantiation unit. It exists so the linker-selected bodies of
// this container appear as COMDATs that build/objplace.py can place against
// unlanded functions; the suffix says which optimisation level, because for
// these containers different bodies survive the link from different units.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
template class _STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > >;

// Whole-class instantiation of this tree. It reproduces count (retail 0x004FF8B1)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<int,_STL::pair<int const ,void *>,_STL::_Select1st<_STL::pair<int const ,void *> >,_STL::less<int>,_STL::allocator<_STL::pair<int const ,void *> > >;
