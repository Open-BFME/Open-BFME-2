// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
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

#include <vector>



struct Rva00577F0FRecord { Rva00577F0FRecord(); Rva00577F0FRecord(const Rva00577F0FRecord&); ~Rva00577F0FRecord(); Rva00577F0FRecord&operator=(const Rva00577F0FRecord&); private: char bytes[4]; };
namespace _STL {template<> void _Construct<Rva00577F0FRecord,Rva00577F0FRecord>(Rva00577F0FRecord*,const Rva00577F0FRecord&);}
template void _STL::vector<Rva00577F0FRecord>::reserve(unsigned int);
