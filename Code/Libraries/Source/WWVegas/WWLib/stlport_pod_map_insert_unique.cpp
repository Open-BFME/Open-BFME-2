// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHUBfmePod8@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod8@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod8@@@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBHUBfmePod8@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHUBfmePod8@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBHUBfmePod8@@@2@@Z 0x00422918 134B evidence: leaf insert_unique via rowed _M_insert 0x00422890 plus _M_decrement; caller 0x00422EAD; siblings Rva00064640Insert same recipe same flags
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

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
struct BfmePod8 { int a[2]; };
typedef _STL::pair<const int, BfmePod8> PodMapValue;
// The node allocator's allocate is kept from the bfmealloc map units (retail's
// 0x000B40EA fold); declare it so this malloc-configured unit emits no copy.
namespace _STL { template <> _Rb_tree_node<PodMapValue> *allocator<_Rb_tree_node<PodMapValue> >::allocate(size_t, const void *) const; }
typedef _STL::_Rb_tree<int, PodMapValue, _STL::_Select1st<PodMapValue>, _STL::less<int>, _STL::allocator<PodMapValue> > PodMapTree;
template _STL::pair<PodMapTree::iterator, bool> PodMapTree::insert_unique(const PodMapValue &);
template PodMapTree::iterator PodMapTree::insert_unique(PodMapTree::iterator, const PodMapValue &);
