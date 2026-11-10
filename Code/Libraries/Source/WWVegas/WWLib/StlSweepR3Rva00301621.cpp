// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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



struct Rva00301621Record { Rva00301621Record(); Rva00301621Record(const Rva00301621Record&); ~Rva00301621Record(); Rva00301621Record&operator=(const Rva00301621Record&); char bytes[4]; bool operator==(const Rva00301621Record&) const; bool operator<(const Rva00301621Record&) const; };
namespace _STL {template<> void _Construct<Rva00301621Record,Rva00301621Record>(Rva00301621Record*,const Rva00301621Record&);}
typedef _STL::pair<const Rva00301621Record, Rva00301621Record> RecordPair;
typedef _STL::_Rb_tree<Rva00301621Record, RecordPair,
    _STL::_Select1st<RecordPair>, _STL::less<Rva00301621Record>,
    _STL::allocator<RecordPair> > RecordTree;
template RecordTree::~_Rb_tree();

// This caller's native REL32 already names the kept provider at 0x004EC395.
// Compatible calling convention and argument/return ABI; binding is address-proven.
#pragma comment(linker, "/alternatename:??1Rva00301621Record@@QAE@XZ=??1?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ")
