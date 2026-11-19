// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Pristine STLport 4.5.3 map members for placeholder POD values. BfmePod8
// stands for the real 8-byte mapped type; the key is int (the placed body
// compares signed).
// Scoped explicit instantiations emit only the nine rowed members, so calls
// reach the retail tree/allocation helpers instead of emitting competing
// COMDAT copies. _M_create_node/_M_copy are declared only; their rowed
// bodies live in the sibling pod-map units.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@HU?$pair@$$CBHUBfmePod8@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod8@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> _Rb_tree<int,pair<int const ,BfmePod8>,_Select1st<pair<int const ,BfmePod8> >,less<int>,allocator<pair<int const ,BfmePod8> > >::~_Rb_tree(); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBHUBfmePod8@@@_STL@@@_STL@@@_STL@@QBEPAU:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> _Rb_tree_node<pair<const int, BfmePod8> > *allocator<_Rb_tree_node<pair<const int, BfmePod8> > >::allocate(size_t, const void *) const; }

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct BfmePod8 { int a[2]; };
typedef _STL::pair<const int, BfmePod8> PodMapValue;
// The node allocator's allocate is kept from the bfmealloc map units (retail's
// 0x000B40EA fold); declare it so this malloc-configured unit emits no copy.
namespace _STL { template <> _Rb_tree_node<PodMapValue> *allocator<_Rb_tree_node<PodMapValue> >::allocate(size_t, const void *) const; }
typedef _STL::_Rb_tree<int, PodMapValue, _STL::_Select1st<PodMapValue>, _STL::less<int>, _STL::allocator<PodMapValue> > PodMapTree;
typedef _STL::map<int, BfmePod8, _STL::less<int>, _STL::allocator<PodMapValue> > PodMapTreeMap;
// Use the bfmealloc header-node constructor selected by the native call.
// Its 36-byte provider is pinned at 0x0023E863; this malloc unit must not
// publish its incompatible allocator-base copy.
template <> _STL::_Rb_tree_base<PodMapValue, _STL::allocator<PodMapValue> >::_Rb_tree_base(const _STL::allocator<PodMapValue> &);
// The shared tree destructor is supplied by the kept owner.
template <> PodMapTree::~_Rb_tree();
template <> PodMapTree::_Link_type PodMapTree::_M_create_node(const PodMapValue &);
template <> PodMapTree::_Link_type PodMapTree::_M_copy(PodMapTree::_Link_type, PodMapTree::_Link_type);
template <> _STL::pair<PodMapTree::iterator, bool> PodMapTree::insert_unique(const PodMapValue &);
template PodMapValue::pair(const int &, const BfmePod8 &);
template BfmePod8 &PodMapTreeMap::operator[](const int &);
template PodMapTreeMap::iterator PodMapTreeMap::insert(PodMapTreeMap::iterator, const PodMapValue &);
template PodMapTree::iterator PodMapTree::insert_unique(PodMapTree::iterator, const PodMapValue &);
template PodMapTree::iterator PodMapTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const PodMapValue &, _STL::_Rb_tree_node_base *);
template PodMapTree::_Link_type PodMapTree::_M_clone_node(PodMapTree::_Link_type);
template PodMapTreeMap::map(const PodMapTreeMap &);
template PodMapTree::_Rb_tree(const _STL::less<int> &, const _STL::allocator<PodMapValue> &);
template PodMapTreeMap::map();
