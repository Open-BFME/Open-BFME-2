// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0?$_Vector_base@UBfmeStringRecord000B9534@@V?$allocator@UBfmeStringRecord000B9534@@@_STL@@@_STL@@QAE@IABV?$allocator@UBfmeStringRecord000B9534@@@1@@Z,
// retail 0x000B63B2, 60 bytes. _Vector_base ctor for the 24-byte StringRecord
// vector: proxy ctor 0x0014F3C4 then allocate 0x00395944 with imul 0x18.
// Needs /G7: home-TU /O1 strength-reduces the imul (allocator-row note).
// Callers 0x000BCE65 0x000BCEC5 0x00425471 0x0052D524 0x005DE88A.
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
struct BfmeStringRecord000B9534 {
    AsciiString text;
    unsigned char flag;
    unsigned int word0, word1, word2, word3;
    BfmeStringRecord000B9534();
    BfmeStringRecord000B9534(const BfmeStringRecord000B9534 &o)
      : text(o.text), flag(o.flag), word0(o.word0), word1(o.word1), word2(o.word2), word3(o.word3) {}
};
#include <vector>
template class _STL::vector<BfmeStringRecord000B9534, _STL::allocator<BfmeStringRecord000B9534> >;
