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



struct Rva0054107FRecord { Rva0054107FRecord(); Rva0054107FRecord(const Rva0054107FRecord&); ~Rva0054107FRecord(); Rva0054107FRecord&operator=(const Rva0054107FRecord&); private: char bytes[28]; };
namespace _STL {template<> void _Construct<Rva0054107FRecord,Rva0054107FRecord>(Rva0054107FRecord*,const Rva0054107FRecord&);}
template Rva0054107FRecord *_STL::__copy(Rva0054107FRecord*,Rva0054107FRecord*,Rva0054107FRecord*,const _STL::random_access_iterator_tag&,int*);
template Rva0054107FRecord *_STL::copy(Rva0054107FRecord*,Rva0054107FRecord*,Rva0054107FRecord*);
