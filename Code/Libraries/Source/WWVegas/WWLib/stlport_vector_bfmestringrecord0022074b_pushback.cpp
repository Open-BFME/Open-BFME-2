// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@UBfmeStringRecord0022074B@@V?$allocator@UBfmeStringRecord0022074B@@@_STL@@@_STL@@QAEXABUBfmeStringRecord0022074B@@@Z @0x00220F8D 55B
// STLport vector<BfmeStringRecord0022074B>::push_back fast path via rowed
// _Construct 0x0022088B else rowed _M_insert_overflow 0x00220EBA with n=1.
// Same 55B shape as UnicodeString push_back 0x0005CBE7. Evidence: unlock lane
// missing callee of 0x00220FC4, retail cmp je Construct add 0x0C vs overflow,
// caller 0x00220FF5, neighbours 0x00220F71/0x00221027.
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "BfmeStringRecord0022074B.h"

namespace _STL
{
template <> void _Construct<BfmeStringRecord0022074B, BfmeStringRecord0022074B>(BfmeStringRecord0022074B *, const BfmeStringRecord0022074B &);
}

template void _STL::vector<BfmeStringRecord0022074B>::push_back(const BfmeStringRecord0022074B &);
