// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
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

#include <vector>



struct Rva0039C028Record { Rva0039C028Record(); Rva0039C028Record(const Rva0039C028Record&); ~Rva0039C028Record(); Rva0039C028Record&operator=(const Rva0039C028Record&); private: char bytes[20]; };
namespace _STL {template<> void _Construct<Rva0039C028Record,Rva0039C028Record>(Rva0039C028Record*,const Rva0039C028Record&);}
template void _STL::vector<Rva0039C028Record>::reserve(unsigned int);
