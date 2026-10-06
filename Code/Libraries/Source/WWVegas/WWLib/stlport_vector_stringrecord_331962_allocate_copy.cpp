// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 12-byte BfmeStringRecord000331962 vector allocation/copy helper at RVA 0x331CE3.
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
struct BfmeStringRecord000331962 {
    unsigned int word;
    AsciiString text;
    unsigned char flag;
    BfmeStringRecord000331962();
    BfmeStringRecord000331962(const BfmeStringRecord000331962 &o) : word(o.word), text(o.text), flag(o.flag) {}
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord000331962,BfmeStringRecord000331962>(BfmeStringRecord000331962*,const BfmeStringRecord000331962&);
#include <vector>
template class _STL::vector<BfmeStringRecord000331962, _STL::allocator<BfmeStringRecord000331962> >;
