// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>



struct Rva00470398Record { Rva00470398Record(); Rva00470398Record(const Rva00470398Record&); ~Rva00470398Record(); Rva00470398Record&operator=(const Rva00470398Record&); private: char bytes[4]; };
namespace _STL {template<> void _Construct<Rva00470398Record,Rva00470398Record>(Rva00470398Record*,const Rva00470398Record&);}
template void _STL::__destroy_aux(Rva00470398Record*,Rva00470398Record*,const _STL::__false_type&);

// The retail call in this body reads 0x001EB940, an address the ledger already
// carries as ??1?$list@PAVObject@@V?$Rva001EB984PoolAllocator@PAVObject@@@@@_STL@@QAE@XZ. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??1Rva00470398Record@@QAE@XZ=??1?$list@PAVObject@@V?$Rva001EB984PoolAllocator@PAVObject@@@@@_STL@@QAE@XZ")
