// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
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

#include <algorithm>
#include <memory>



struct Rva00218FC2Record { Rva00218FC2Record(); Rva00218FC2Record(const Rva00218FC2Record&); ~Rva00218FC2Record(); Rva00218FC2Record&operator=(const Rva00218FC2Record&); char bytes[16]; bool Less(const Rva00218FC2Record&)const; };
struct Rva00218FC2RecordCompare { bool operator()(const Rva00218FC2Record&a,const Rva00218FC2Record&b)const {return a.Less(b);} };
template void _STL::sort(Rva00218FC2Record*,Rva00218FC2Record*,Rva00218FC2RecordCompare);
template void _STL::stable_sort(Rva00218FC2Record*,Rva00218FC2Record*,Rva00218FC2RecordCompare);
template void _STL::make_heap(Rva00218FC2Record*,Rva00218FC2Record*,Rva00218FC2RecordCompare);
template void _STL::push_heap(Rva00218FC2Record*,Rva00218FC2Record*,Rva00218FC2RecordCompare);
template void _STL::pop_heap(Rva00218FC2Record*,Rva00218FC2Record*,Rva00218FC2RecordCompare);
template void _STL::sort_heap(Rva00218FC2Record*,Rva00218FC2Record*,Rva00218FC2RecordCompare);
template void _STL::partial_sort(Rva00218FC2Record*,Rva00218FC2Record*,Rva00218FC2Record*,Rva00218FC2RecordCompare);
template void _STL::nth_element(Rva00218FC2Record*,Rva00218FC2Record*,Rva00218FC2Record*,Rva00218FC2RecordCompare);
