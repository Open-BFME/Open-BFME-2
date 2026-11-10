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



struct Rva0050477BRecord { Rva0050477BRecord(); Rva0050477BRecord(const Rva0050477BRecord&); ~Rva0050477BRecord(); Rva0050477BRecord&operator=(const Rva0050477BRecord&); private: char bytes[16]; };
namespace _STL {template<> void _Construct<Rva0050477BRecord,Rva0050477BRecord>(Rva0050477BRecord*,const Rva0050477BRecord&);}
template Rva0050477BRecord *_STL::__uninitialized_fill_n(Rva0050477BRecord*,unsigned int,const Rva0050477BRecord&,const _STL::__false_type&);

// The retail call in this body reads 0x0041360E, an address the ledger already
// carries as ??$_Construct@U?$pair@$$CBIURva002A147EElement@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBIURva002A147EElement@@@0@ABU10@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??$_Construct@URva0050477BRecord@@U1@@_STL@@YAXPAURva0050477BRecord@@ABU1@@Z=??$_Construct@U?$pair@$$CBIURva002A147EElement@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBIURva002A147EElement@@@0@ABU10@@Z")
