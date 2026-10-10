// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@UBfmeStringRecord005F93E3@@V?$allocator@UBfmeStringRecord005F93E3@@@_STL@@@_STL@@QAEXABUBfmeStringRecord005F93E3@@@Z,
// retail 0x005FA160, 55 bytes. STLport 4.5.3 vector<BfmeStringRecord005F93E3>::push_back,
// sibling of the Rva0052BDE6 push_back at 0x005662CC (55B, same flags).
// Fast path constructs via the rowed _Construct at 0x005F944A; full path calls
// the rowed _M_insert_overflow at 0x005F9B4E with n=1 fill=1.
// Callers 0x005FA230 0x005FA2F7.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

#include "unicode_string.h"
struct BfmeStringRecord005F93E3 {
    unsigned int word0;
    unsigned int word1;
    UnicodeString text;
};
inline bool operator==(const BfmeStringRecord005F93E3 &x, const BfmeStringRecord005F93E3 &y) { return x.word0 == y.word0; }
inline bool operator<(const BfmeStringRecord005F93E3 &x, const BfmeStringRecord005F93E3 &y) { return x.word0 < y.word0; }

namespace _STL
{
template <> void _Construct<BfmeStringRecord005F93E3, BfmeStringRecord005F93E3>(BfmeStringRecord005F93E3 *, const BfmeStringRecord005F93E3 &);
}

template void _STL::vector<BfmeStringRecord005F93E3>::push_back(const BfmeStringRecord005F93E3 &);
