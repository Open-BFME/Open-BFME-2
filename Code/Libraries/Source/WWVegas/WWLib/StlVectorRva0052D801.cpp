// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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



struct Rva0052D801Record { Rva0052D801Record(); Rva0052D801Record(const Rva0052D801Record&); ~Rva0052D801Record(); Rva0052D801Record&operator=(const Rva0052D801Record&); private: char bytes[184]; };
namespace _STL {template<> void _Construct<Rva0052D801Record,Rva0052D801Record>(Rva0052D801Record*,const Rva0052D801Record&);}
template void _STL::vector<Rva0052D801Record>::push_back(const Rva0052D801Record&);
