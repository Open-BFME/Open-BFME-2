// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
// codegen otherwise instantiates the min<int> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy.
namespace _STL {
static inline const int &min(const int &a, const int &b)
{
    return b < a ? b : a;
}
}
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "unicode_string.h"
#include <string>
#include <map>
// bfme link decl-only begin
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > const &); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_terminate_string(); }
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int, void const *) const; }
// bfme link decl-only end

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}



#include "../../../../GameEngine/Include/Common/Rva00226856.h"
struct Rva0022CCEFRecord {Rva0022CCEFRecord();Rva0022CCEFRecord(const Rva0022CCEFRecord&);// Destruction is the rowed ??1Rva00226856, reached by a qualified call.
__declspec(dllimport) __forceinline ~Rva0022CCEFRecord() { ((Rva00226856 *)this)->Rva00226856::~Rva00226856(); }Rva0022CCEFRecord&operator=(const Rva0022CCEFRecord&);char bytes[1];};
// Instantiate only the tree's node eraser, whose node destruction emits the rowed
// ~pair; the whole multimap also emitted members needing the record's undefined copy.
typedef _STL::basic_string<unsigned short> Rva0022CCEFKey;
typedef _STL::pair<const Rva0022CCEFKey, Rva0022CCEFRecord> Rva0022CCEFValue;
template void _STL::_Rb_tree<Rva0022CCEFKey, Rva0022CCEFValue, _STL::_Select1st<Rva0022CCEFValue>, _STL::less<Rva0022CCEFKey>, _STL::allocator<Rva0022CCEFValue> >::_M_erase(_STL::_Rb_tree_node<Rva0022CCEFValue> *);
