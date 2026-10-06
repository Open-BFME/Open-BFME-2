// Pristine STLport4.5.3 byte storage operations; target byte stride, memmove/fill calls and vector fields establish family.
// Unsigned byte spelling is donor source provenance; signedness is not distinguished by these target operations.
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



template unsigned char *_STL::__uninitialized_fill_n(unsigned char*,unsigned int,const unsigned char&,const _STL::__true_type&);
