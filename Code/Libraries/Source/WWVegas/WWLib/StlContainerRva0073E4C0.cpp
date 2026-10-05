// STLport4.5.3 reference; opaque address-derived record, target stride and container offsets.
// cl: /O2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

#include <deque>



struct Rva0073E4C0Record { Rva0073E4C0Record(); Rva0073E4C0Record(const Rva0073E4C0Record&); ~Rva0073E4C0Record(); Rva0073E4C0Record&operator=(const Rva0073E4C0Record&); private: char bytes[8]; };
namespace _STL {template<> void _Construct<Rva0073E4C0Record,Rva0073E4C0Record>(Rva0073E4C0Record*,const Rva0073E4C0Record&);}
template void _STL::deque<Rva0073E4C0Record>::push_back(const Rva0073E4C0Record&);
