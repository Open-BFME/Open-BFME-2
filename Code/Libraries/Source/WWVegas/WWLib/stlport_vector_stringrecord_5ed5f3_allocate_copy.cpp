// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_fill_n@PAUBfmeStringRecord005ED5F3@@IU1@@_STL@@YAPAUBfmeStringRecord005ED5F3@@PAU1@IABU1@ABU__false_type@0@@Z @0x005ED8AC 37B: vector fill helper for 20-byte BfmeStringRecord005ED5F3 (UnicodeString plus 4 words). Evidence: calls rowed _Construct 0x005ED68C; stride 0x14; callers are vector insert paths 0x005ED99F 0x005EDB2B.
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
#include "unicode_string.h"
struct BfmeStringRecord005ED5F3
{
    UnicodeString text;
    unsigned int word0;
    unsigned int word1;
    unsigned int word2;
    unsigned int word3;
    BfmeStringRecord005ED5F3();
    BfmeStringRecord005ED5F3(const BfmeStringRecord005ED5F3 &other);
};
namespace _STL {
template <> void _Construct<BfmeStringRecord005ED5F3, BfmeStringRecord005ED5F3>(BfmeStringRecord005ED5F3 *, const BfmeStringRecord005ED5F3 &);
}
template BfmeStringRecord005ED5F3 *_STL::__uninitialized_fill_n(BfmeStringRecord005ED5F3 *, unsigned int, const BfmeStringRecord005ED5F3 &, const _STL::__false_type &);
template BfmeStringRecord005ED5F3 *_STL::__uninitialized_copy(const BfmeStringRecord005ED5F3 *, const BfmeStringRecord005ED5F3 *, BfmeStringRecord005ED5F3 *, const _STL::__false_type &);
template BfmeStringRecord005ED5F3 *_STL::uninitialized_fill_n(BfmeStringRecord005ED5F3 *, unsigned int, const BfmeStringRecord005ED5F3 &);
template BfmeStringRecord005ED5F3 *_STL::__copy_ptrs(BfmeStringRecord005ED5F3 *, BfmeStringRecord005ED5F3 *, BfmeStringRecord005ED5F3 *, _STL::__false_type);
template void _STL::vector<BfmeStringRecord005ED5F3, _STL::allocator<BfmeStringRecord005ED5F3> >::_M_clear();
template void _STL::_Destroy<BfmeStringRecord005ED5F3 *>(BfmeStringRecord005ED5F3 *, BfmeStringRecord005ED5F3 *);
template _STL::vector<BfmeStringRecord005ED5F3, _STL::allocator<BfmeStringRecord005ED5F3> >::~vector();
