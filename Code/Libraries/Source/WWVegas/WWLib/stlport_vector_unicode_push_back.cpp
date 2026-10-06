// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@VUnicodeString@@V?$allocator@VUnicodeString@@@_STL@@@_STL@@QAEXABVUnicodeString@@@Z retail 0x0005CBE7 55B
// Evidence: unlock lane; callees rowed _Construct 0x00054DF6 and _M_insert_overflow 0x0005B538; callers 0x0005CD41 0x0005DB6C 0x00386B7B; same 55B shape as AsciiString push_back 0x00143170.
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its vector bodies.
#pragma optimize("s", off)
#pragma optimize("t", on)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

#include "unicode_string.h"

namespace _STL {
template <> void _Construct<UnicodeString, UnicodeString>(UnicodeString *, const UnicodeString &);
}

template void _STL::vector<UnicodeString, _STL::allocator<UnicodeString> >::push_back(const UnicodeString &);
