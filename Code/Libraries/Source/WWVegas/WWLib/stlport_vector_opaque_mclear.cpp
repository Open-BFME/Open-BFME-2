// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// platformsdk
// stlport
// ?_M_clear@?$vector@UOpaqueRefElement4@@V?$allocator@UOpaqueRefElement4@@@_STL@@@_STL@@IAEXXZ retail 0x00057DE4 30B.
// STLport 4.5.3 vector<OpaqueRefElement4>::_M_clear. Same 30B Destroy-plus-free
// shape as the AsciiString _M_clear at 0x0002CD53 in Module.cpp, selecting the
// rowed _Destroy at 0x00054F94 in StlportOwnedDeque.cpp then _free at 0x00030830.
// Four callers 0x00058B74 0x00058C53 0x00239F13 0x0023A10C operate on Opaque vectors.
#include <windows.h>
#include <vector>
#include "OpaqueRefCounted.h"
struct OpaqueRefElement4
{
    OpaqueRefCounted *referent;
    inline ~OpaqueRefElement4();
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};
// ??1OpaqueRefElement4@@QAE@XZ present-unmatched
inline OpaqueRefElement4::~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }

template void _STL::vector<OpaqueRefElement4>::_M_clear();
