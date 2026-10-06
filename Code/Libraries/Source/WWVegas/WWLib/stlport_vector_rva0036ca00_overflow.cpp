// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@VRva0036CA00Str@@V?$allocator@VRva0036CA00Str@@@_STL@@@_STL@@IAEXPAVRva0036CA00Str@@ABV3@ABU__false_type@2@I_N@Z @0x00058ADE 178B
// Evidence: chain lane calls just-landed fill_n 0x00051AF9 plus rowed copy 0x002393BC plus Construct 0x002393AA plus _M_clear twin 0x00057DE4 plus allocate twin 0x00068E15; caller push_back 0x0005A048 with fill 1 atend true; same 178B shape as CameraMarker overflow 0x000D05C1; sar 2 for 4B element.
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

class Rva0036CA00Str
{
public:
    Rva0036CA00Str();
    Rva0036CA00Str(const Rva0036CA00Str &);
    ~Rva0036CA00Str();
    Rva0036CA00Str &operator=(const Rva0036CA00Str &);
private:
    void *m_data;
};

namespace _STL {
template <> void _Construct<Rva0036CA00Str, Rva0036CA00Str>(Rva0036CA00Str *, const Rva0036CA00Str &);
}

template void _STL::vector<Rva0036CA00Str>::_M_insert_overflow(
    Rva0036CA00Str *,
    const Rva0036CA00Str &,
    const _STL::__false_type &,
    unsigned int,
    bool);
