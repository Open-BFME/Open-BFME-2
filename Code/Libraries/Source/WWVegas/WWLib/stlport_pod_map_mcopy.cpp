// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport
// ?_M_copy@?$_Rb_tree@HU?$pair@$$CBHUBfmePod8@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod8@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod8@@@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHUBfmePod8@@@_STL@@@2@PAU32@0@Z @ 0x003A24C6 115B
// _Rb_tree<int,pair<const int,BfmePod8>>::_M_copy beside stlport_pod_map_bodies.
// Target evidence: 115B retail, rowed _M_clone_node 0x39FD75 plus self-recursion,
// unlocks 0x3A299C. Whole-class probe with NO_EXCEPTIONS emits 115B exact;
// single-member instantiation keeps the TU claim-free. Flags copy the
// NO_EXCEPTIONS shape from stlport_rb_tree_create_nodes.
#include <map>
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHUBfmePod8@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfm:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> _Rb_tree_node<pair<const int, BfmePod8> > *_Rb_tree<int, pair<const int, BfmePod8>, _Select1st<pair<const int, BfmePod8> >, less<int>, allocator<pair<const int, BfmePod8> > >::_M_create_node(const pair<const int, BfmePod8> &); }
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
struct BfmePod8 { int a[2]; };
typedef _STL::_Rb_tree<int, _STL::pair<const int, BfmePod8>, _STL::_Select1st<_STL::pair<const int, BfmePod8> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod8> > > PodMapTree;
// The node allocator's allocate is kept from the bfmealloc map units (retail's
// 0x000B40EA fold); declare it so this malloc-configured unit emits no copy.
namespace _STL { template <> _Rb_tree_node<pair<const int, BfmePod8> > *allocator<_Rb_tree_node<pair<const int, BfmePod8> > >::allocate(size_t, const void *) const; }
template PodMapTree::_Link_type PodMapTree::_M_copy(PodMapTree::_Link_type, PodMapTree::_Link_type);
