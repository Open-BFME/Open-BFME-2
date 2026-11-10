// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>



struct Rva0052D801Record { Rva0052D801Record(); Rva0052D801Record(const Rva0052D801Record&); virtual ~Rva0052D801Record(); Rva0052D801Record&operator=(const Rva0052D801Record&); private: char bytes[180]; };
namespace _STL {template<> void _Construct<Rva0052D801Record,Rva0052D801Record>(Rva0052D801Record*,const Rva0052D801Record&);}
template void _STL::vector<Rva0052D801Record>::push_back(const Rva0052D801Record&);

// Bind lifetime operations to the existing rowed native providers.
// push_back and overflow 52D742 call the cdecl copy provider 52D6BE.
// Cleanup 52CAAB calls range wrapper 52C24E, then virtual destroy 52BCE7
// (zero deleting flag, stride 0xB8): the virtual destructor declared above makes
// this unit emit those STLport bodies itself.
// These bindings identify operations on an ABI view, not a new game type.
#pragma comment(linker, "/alternatename:??$_Construct@URva0052D801Record@@U1@@_STL@@YAXPAURva0052D801Record@@ABU1@@Z=?Rva0052D6BEConstruct@@YAXPAVRva0056616B@@ABV1@@Z")
