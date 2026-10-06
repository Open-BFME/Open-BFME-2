// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@UBfmeStringRecord000B950F@@V?$allocator@UBfmeStringRecord000B950F@@@_STL@@@_STL@@IAEXPAUBfmeStringRecord000B950F@@ABU3@ABU__false_type@2@I_N@Z, retail 0x000C1CE1, 183 bytes.
// Vector overflow via rowed allocate pin 0x395928 plus workers 0xBBB5D 0xBBB83 plus Construct row 0xBB9ED plus Clear pin 0xC05EC.
// Evidence: same 183B shape as 331962 sibling; /G7 for retail imul.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct BfmeStringRecord000B950F {
    unsigned int word0;
    AsciiString text;
    unsigned int word1;
    BfmeStringRecord000B950F();
    BfmeStringRecord000B950F(const BfmeStringRecord000B950F &o) : word0(o.word0), text(o.text), word1(o.word1) {}
};
#include <memory>
namespace _STL {
template <> void _Construct<BfmeStringRecord000B950F, BfmeStringRecord000B950F>(BfmeStringRecord000B950F *, const BfmeStringRecord000B950F &);
}
#include <vector>
template void _STL::vector<BfmeStringRecord000B950F>::_M_insert_overflow(BfmeStringRecord000B950F *, const BfmeStringRecord000B950F &, const _STL::__false_type &, unsigned int, bool);
