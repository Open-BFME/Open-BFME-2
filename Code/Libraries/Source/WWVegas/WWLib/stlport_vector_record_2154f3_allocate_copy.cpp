// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 16-byte BfmeVectorRecord0002154F3 vector allocation/copy helper at RVA 0x215614.
// Uses the shared ascii_string.h so the emitted ??_GAsciiString copy calls
// releaseBuffer like the kept WOLBuddyOverlay copy. operator= is declared only
// so this TU does not emit the shallow implicit copy (kept deep copy lives in
// StringVectorRecordCopyBFME2.cpp).
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

#include "ascii_string.h"
#include <vector>
struct BfmeVectorRecord0002154F3 {
    AsciiString text;
    _STL::vector<AsciiString> names;
    BfmeVectorRecord0002154F3();
    BfmeVectorRecord0002154F3(const BfmeVectorRecord0002154F3 &);
    BfmeVectorRecord0002154F3 &operator=(const BfmeVectorRecord0002154F3 &);
};
namespace _STL {
template <> void _Construct<BfmeVectorRecord0002154F3, BfmeVectorRecord0002154F3>(BfmeVectorRecord0002154F3 *, const BfmeVectorRecord0002154F3 &);
}
template class _STL::vector<BfmeVectorRecord0002154F3, _STL::allocator<BfmeVectorRecord0002154F3> >;
