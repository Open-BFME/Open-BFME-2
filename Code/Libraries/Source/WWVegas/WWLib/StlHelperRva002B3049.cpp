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



struct Rva002B3049Record { Rva002B3049Record(); Rva002B3049Record(const Rva002B3049Record&); ~Rva002B3049Record(); Rva002B3049Record&operator=(const Rva002B3049Record&); private: char bytes[4]; };
namespace _STL {template<> void _Construct<Rva002B3049Record,Rva002B3049Record>(Rva002B3049Record*,const Rva002B3049Record&);}
template Rva002B3049Record *_STL::__copy_backward(Rva002B3049Record*,Rva002B3049Record*,Rva002B3049Record*,const _STL::random_access_iterator_tag&,int*);
template Rva002B3049Record *_STL::__copy_backward_ptrs(Rva002B3049Record*,Rva002B3049Record*,Rva002B3049Record*,const _STL::__false_type&);
