// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
// cl: /O1 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include "../../../../../vendor/stlport/stl/_algobase.h"
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



// Native insertion 0x00504D57 copies the first float separately, then
// the remaining three words as an aggregate. This grouping models its copy
// codegen; original trailing field meanings and point type name are unknown.
struct Rva00504755Record {
    float x;
    struct Tail { float y, z, w; } tail;
    Rva00504755Record() {}
    Rva00504755Record(const Rva00504755Record& v): x(v.x), tail(v.tail) {}
};

namespace _STL {template<> void _Construct<Rva00504755Record,Rva00504755Record>(Rva00504755Record*,const Rva00504755Record&);}
template Rva00504755Record *_STL::__uninitialized_copy(Rva00504755Record*,Rva00504755Record*,Rva00504755Record*,const _STL::__false_type&);

// STLport 4.5.3 insertion at 0x00504D57..0x00504DF8; called by
// the rowed 16-byte range insertion 0x00504E6D. Preserve the original
// algorithm header to keep its four-argument copy-wrapper call.
template Rva00504755Record *_STL::vector<Rva00504755Record, _STL::allocator<Rva00504755Record> >::insert(Rva00504755Record *, const Rva00504755Record &);
