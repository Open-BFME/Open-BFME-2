// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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



struct Rva002FFC74Record { Rva002FFC74Record(); Rva002FFC74Record(const Rva002FFC74Record&); ~Rva002FFC74Record(); Rva002FFC74Record&operator=(const Rva002FFC74Record&); char bytes[1]; bool operator==(const Rva002FFC74Record&) const; bool operator<(const Rva002FFC74Record&) const; };
namespace _STL {template<> void _Construct<Rva002FFC74Record,Rva002FFC74Record>(Rva002FFC74Record*,const Rva002FFC74Record&);}
template class _STL::list<Rva002FFC74Record>;

// This caller's native REL32 already names the kept provider at 0x001D9990.
// Both declarations use thiscall with one object-pointer/reference argument; binding is address-proven.
#pragma comment(linker, "/alternatename:??4Rva002FFC74Record@@QAEAAU0@ABU0@@Z=??4FXBoneInfo@@QAEAAU0@ABU0@@Z")
