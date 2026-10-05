// STLport4.5.3 reference; opaque address-derived record, target stride and container offsets.
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



struct Rva0037FF20Record { Rva0037FF20Record(const Rva0037FF20Record&); private: char bytes[72]; };
namespace _STL {template<> void _Construct<Rva0037FF20Record,Rva0037FF20Record>(Rva0037FF20Record*,const Rva0037FF20Record&);}
template void _STL::vector<Rva0037FF20Record>::_M_insert_overflow(Rva0037FF20Record*,const Rva0037FF20Record&,const _STL::__false_type&,unsigned int,bool);
