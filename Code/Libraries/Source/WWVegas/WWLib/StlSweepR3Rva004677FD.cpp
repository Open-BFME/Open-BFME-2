// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <list>



struct Rva004677FDRecord { unsigned char bytes[8]; bool operator==(const Rva004677FDRecord&) const; bool operator<(const Rva004677FDRecord&) const; };


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::_List_node<Rva004677FDRecord> * _STL::list<Rva004677FDRecord, _STL::allocator<Rva004677FDRecord> >::_M_create_node(Rva004677FDRecord const &);
