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

#include <algorithm>
#include <memory>



struct Rva003B33C2Record { Rva003B33C2Record(); Rva003B33C2Record(const Rva003B33C2Record&); ~Rva003B33C2Record(); Rva003B33C2Record&operator=(const Rva003B33C2Record&); char bytes[1]; bool operator<(const Rva003B33C2Record&)const; };
template void _STL::stable_sort(Rva003B33C2Record*,Rva003B33C2Record*);

// This caller's native REL32 already names the kept provider at 0x003B31DF.
// Compatible calling convention and argument/return ABI; binding is address-proven.
#pragma comment(linker, "/alternatename:??1Rva003B33C2Record@@QAE@XZ=?clear@Rva003B31DF@@QAEXXZ")
