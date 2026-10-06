// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /I. /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <vendor/stlport/stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>


struct Rva001DA05ERecord { Rva001DA05ERecord(); Rva001DA05ERecord(const Rva001DA05ERecord&); ~Rva001DA05ERecord(); Rva001DA05ERecord&operator=(const Rva001DA05ERecord&); char bytes[8]; };
namespace _STL {template<> void _Construct<Rva001DA05ERecord,Rva001DA05ERecord>(Rva001DA05ERecord*,const Rva001DA05ERecord&);}


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::vector<Rva001DA05ERecord, _STL::allocator<Rva001DA05ERecord> > & _STL::vector<Rva001DA05ERecord, _STL::allocator<Rva001DA05ERecord> >::operator=(_STL::vector<Rva001DA05ERecord, _STL::allocator<Rva001DA05ERecord> > const &);
