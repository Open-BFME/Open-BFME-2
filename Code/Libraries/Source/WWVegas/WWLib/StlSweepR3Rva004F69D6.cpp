// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>



struct Rva004F69D6Record { ~Rva004F69D6Record(); char bytes[4]; };
// Retail's range copy for this element (pinned 0x0007E2FA, ICF twin of rowed
// Rva0007E2FACopy) copies each 4-byte owning reference through rowed
// Rva00087A5CCopy(dst, src), as StlportVectorOverflow0008B503.cpp does;
// throw() keeps the vector copy ctor free of an EH frame, as retail has none.
void __cdecl Rva00087A5CCopy(void **dst, void **src) throw();
namespace _STL {
template <> inline void _Construct<Rva004F69D6Record, Rva004F69D6Record>(Rva004F69D6Record *p, const Rva004F69D6Record &value)
{
	Rva00087A5CCopy((void **)p, (void **)&value);
}
}
template _STL::vector<Rva004F69D6Record>::vector(const _STL::vector<Rva004F69D6Record>&);
