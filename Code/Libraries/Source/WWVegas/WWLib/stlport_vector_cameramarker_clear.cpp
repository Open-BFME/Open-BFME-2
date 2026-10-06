// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_clear@?$vector@VCameraMarker@@V?$allocator@VCameraMarker@@@_STL@@@_STL@@IAEXXZ @0x000C060A 30B
// Evidence: same 30B Destroy-plus-free shape as rowed sibling _M_clear at 0x000C05CE
// (vector<BfmeStringRecord>); callees rowed Destroy<CameraMarker> 0x0048CE25 and _free
// 0x00030830; 6 callers (0xC1E4A 0xCF76E 0xD05C1 0x2895F8 0x48D48F 0x5244DC) unblocked.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
class CameraMarker { public: ~CameraMarker(); char m_pad[8]; };
namespace _STL {
template <> void _Construct<class CameraMarker, class CameraMarker>(class CameraMarker *, const class CameraMarker &);
}
template class _STL::vector<CameraMarker, _STL::allocator<CameraMarker> >;
