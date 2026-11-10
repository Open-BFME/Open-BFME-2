// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}












// Tree-iterator steps and the node allocation path, inline (dllimport+forceinline)
// so this TU emits no losing COMDAT copies of them.
namespace _STL {
typedef _Rb_tree_node<pair<const int, int> > PairIntNode;
template <> __declspec(dllimport) __forceinline
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > > &
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > >::operator++()
{ _M_node = _Rb_global_inst::_M_increment(_M_node); return *this; }
template <> __declspec(dllimport) __forceinline
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > > &
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > >::operator--()
{ _M_node = _Rb_global_inst::_M_decrement(_M_node); return *this; }
template <> __declspec(dllimport) __forceinline
PairIntNode *allocator<PairIntNode>::allocate(size_t n, const void *) const
{ return n != 0 ? reinterpret_cast<PairIntNode *>(__sgi_alloc::allocate(n * sizeof(PairIntNode))) : 0; }
template <> __declspec(dllimport) __forceinline
PairIntNode *_STLP_alloc_proxy<PairIntNode *, PairIntNode, allocator<PairIntNode> >::allocate(size_t n)
{ return __stl_alloc_rebind(static_cast<allocator<PairIntNode>&>(*this), (PairIntNode *)0).allocate(n, 0); }
}

namespace _STL {
template <> _Rb_tree_node<pair<const int, int> > *_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::_M_create_node(const pair<const int, int> &);
}

// Instantiate the recovered member; retain only its required template dependencies.
template _STL::_Rb_tree_iterator<_STL::pair<int const, int>, _STL::_Nonconst_traits<_STL::pair<int const, int> > > _STL::multimap<int, int, _STL::less<int>, _STL::allocator<_STL::pair<int const, int> > >::insert(_STL::_Rb_tree_iterator<_STL::pair<int const, int>, _STL::_Nonconst_traits<_STL::pair<int const, int> > >, _STL::pair<int const, int> const &);
