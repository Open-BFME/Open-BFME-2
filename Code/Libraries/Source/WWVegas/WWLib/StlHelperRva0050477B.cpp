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



struct Rva0050477BRecord { Rva0050477BRecord(); Rva0050477BRecord(const Rva0050477BRecord&); ~Rva0050477BRecord(); Rva0050477BRecord&operator=(const Rva0050477BRecord&); private: char bytes[16]; };
namespace _STL {template<> void _Construct<Rva0050477BRecord,Rva0050477BRecord>(Rva0050477BRecord*,const Rva0050477BRecord&);}
template Rva0050477BRecord *_STL::__uninitialized_fill_n(Rva0050477BRecord*,unsigned int,const Rva0050477BRecord&,const _STL::__false_type&);
