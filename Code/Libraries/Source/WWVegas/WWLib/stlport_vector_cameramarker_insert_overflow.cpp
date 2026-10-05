// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@VCameraMarker@@V?$allocator@VCameraMarker@@@_STL@@@_STL@@IAEXPAVCameraMarker@@ABV3@ABU__false_type@2@I_N@Z @0x000D05C1 178B
// Evidence: STLport vector<CameraMarker> false_type growth path; 8B stride sar 3; new_size old plus max(old fill_len); allocate plus uninitialized_copy plus Construct-or-fill_n plus conditional second copy plus CameraMarker _M_clear 0xC060A; caller push_back 0xD068F with fill_len 1 atend true unblocks 0xD068F.
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
#include "ascii_string.h"
class CameraMarker {
public:
	CameraMarker *m_next;
	AsciiString m_name;
	~CameraMarker();
	CameraMarker(const CameraMarker &other);
	CameraMarker &operator=(const CameraMarker &other);
};
namespace _STL {
template <> void _Construct<class CameraMarker, class CameraMarker>(class CameraMarker *, const class CameraMarker &);
}
template void _STL::vector<class CameraMarker>::_M_insert_overflow(class CameraMarker *, const class CameraMarker &, const _STL::__false_type &, unsigned int, bool);
// ?push_back@?$vector@VCameraMarker@@V?$allocator@VCameraMarker@@@_STL@@@_STL@@QAEXABVCameraMarker@@@Z @0x000D068F 55B
// Evidence: vector<CameraMarker> push_back fast Construct plus overflow 0xD05C1 slow path; caller 0xD06C6 unblocks 0xD06C6.
template void _STL::vector<class CameraMarker>::push_back(const class CameraMarker &);
