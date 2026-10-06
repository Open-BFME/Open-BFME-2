// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: STLport4.5.3 vector::_M_clear. Retail119CC0..119CF1 is
// delimited by int3 padding. The loop strides0x74 and calls the destructor
// folded at118800 (rowed TextureStatisticsStruct). It then frees start.
// No application identity is adopted from the equal-sized ProxyClass views.
#include <vector>
struct Rva00119CC0Record { ~Rva00119CC0Record(); private: char bytes[116]; };
template void _STL::vector<Rva00119CC0Record>::_M_clear();
