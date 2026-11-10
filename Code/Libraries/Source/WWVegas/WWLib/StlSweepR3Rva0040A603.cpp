// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <map>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}



struct Rva0040A603Record {  char bytes[1]; };
// Declared only (stl batch): retail's body for this name is the rowed one at its
// pinned address; this TU's copy is not retail's.
namespace _STL { template <> void _Rb_tree<int,_STL::pair<int const,Rva0040A603Record>,_STL::_Select1st<_STL::pair<int const,Rva0040A603Record> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,Rva0040A603Record> > >::clear(void); }
template class _STL::map<int,Rva0040A603Record>;

// The declared helper binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:?clear@?$_Rb_tree@HU?$pair@$$CBHURva0040A603Record@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva0040A603Record@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva0040A603Record@@@_STL@@@2@@_STL@@QAEXXZ=?rva0040A59B@Rva0040A59B@@QAEXXZ")
