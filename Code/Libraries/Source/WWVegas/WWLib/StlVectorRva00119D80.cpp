// Reference: pristine STLport4.5.3. Address-derived opaque ABI view.
// Target boundary and stride independently establish storage width; no game class identity inferred.
// cl: /O2 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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



struct Rva00119D80Record { Rva00119D80Record(); Rva00119D80Record(const Rva00119D80Record&); ~Rva00119D80Record(); Rva00119D80Record&operator=(const Rva00119D80Record&); private: char bytes[116]; };
namespace _STL {template<> void _Construct<Rva00119D80Record,Rva00119D80Record>(Rva00119D80Record*,const Rva00119D80Record&);}
template void _STL::vector<Rva00119D80Record>::_M_insert_overflow(Rva00119D80Record*,const Rva00119D80Record&,const _STL::__false_type&,unsigned int,bool);
