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

#include <set>



struct Rva00502EA4Record { Rva00502EA4Record(); Rva00502EA4Record(const Rva00502EA4Record&); ~Rva00502EA4Record(); Rva00502EA4Record&operator=(const Rva00502EA4Record&); char bytes[92]; bool operator==(const Rva00502EA4Record&) const; bool operator<(const Rva00502EA4Record&) const; };
namespace _STL {template<> void _Construct<Rva00502EA4Record,Rva00502EA4Record>(Rva00502EA4Record*,const Rva00502EA4Record&);}
template class _STL::set<Rva00502EA4Record>;

// This caller's native REL32 already names the kept provider at 0x00502C53.
// Compatible calling convention and argument/return ABI; binding is address-proven.
#pragma comment(linker, "/alternatename:??$_Construct@URva00502EA4Record@@U1@@_STL@@YAXPAURva00502EA4Record@@ABU1@@Z=??$_Construct@URva00502C53Element@@U1@@_STL@@YAXPAURva00502C53Element@@ABU1@@Z")
