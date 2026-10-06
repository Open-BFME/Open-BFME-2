// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::_M_insert_overflow growth paths for BFME2 string
// records, dedicated TU. The record layouts and the StringBase model are
// carried unchanged from StringRecordInlineCopyBFME2.cpp, which owns each
// record's copy ctor and matched _Construct; here the copy ctors are only
// declared and _Construct is declared as an explicit specialization, so the
// growth paths call those matched bodies out of line.
//
// Target evidence per record: each placed body is the unowned retail caller of
// that record's matched _Construct and __uninitialized_fill_n rows. The flags
// differ from the owning TU on purpose: /G7 is what emits retail's imul
// element scaling (the AnimSet sibling's IMUL recipe), /Ireference/shims/bfmealloc
// keeps allocate a two-argument out-of-line call, and /D_STLP_NO_EXCEPTIONS
// drops the EH frame retail does not have. Application names and scalar
// meanings stay unknown.
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

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

struct BfmeStringRecord002199C8 {
    AsciiString text0, text1, text2; unsigned int word;
    BfmeStringRecord002199C8(const BfmeStringRecord002199C8 &o);
};
struct BfmeStringRecord00219A68 {
    unsigned int word0; AsciiString text0, text1; unsigned int word1, word2;
    BfmeStringRecord00219A68(const BfmeStringRecord00219A68 &o);
};
struct BfmeStringRecord0022074B {
    AsciiString text0, text1; unsigned int word;
    BfmeStringRecord0022074B(const BfmeStringRecord0022074B &o);
    ~BfmeStringRecord0022074B();
};
struct BfmeStringRecord005D511F {
    UnicodeString text0; unsigned int word0, word1; UnicodeString text1; unsigned int word2;
    BfmeStringRecord005D511F(const BfmeStringRecord005D511F &o);
    ~BfmeStringRecord005D511F();
};
struct BfmeStringRecord005EC43C {
    UnicodeString text; unsigned int word0, word1, word2, word3, word4;
    BfmeStringRecord005EC43C(const BfmeStringRecord005EC43C &o);
};
struct BfmeStringRecord005F93E3 {
    unsigned int word0, word1; UnicodeString text;
    BfmeStringRecord005F93E3(const BfmeStringRecord005F93E3 &o);
};

namespace _STL
{
template <> void _Construct<BfmeStringRecord002199C8, BfmeStringRecord002199C8>(BfmeStringRecord002199C8 *, const BfmeStringRecord002199C8 &);
template <> void _Construct<BfmeStringRecord00219A68, BfmeStringRecord00219A68>(BfmeStringRecord00219A68 *, const BfmeStringRecord00219A68 &);
template <> void _Construct<BfmeStringRecord0022074B, BfmeStringRecord0022074B>(BfmeStringRecord0022074B *, const BfmeStringRecord0022074B &);
template <> void _Construct<BfmeStringRecord005D511F, BfmeStringRecord005D511F>(BfmeStringRecord005D511F *, const BfmeStringRecord005D511F &);
template <> void _Construct<BfmeStringRecord005EC43C, BfmeStringRecord005EC43C>(BfmeStringRecord005EC43C *, const BfmeStringRecord005EC43C &);
template <> void _Construct<BfmeStringRecord005F93E3, BfmeStringRecord005F93E3>(BfmeStringRecord005F93E3 *, const BfmeStringRecord005F93E3 &);
}

// Retail 0x0021E1EB (180B).
template void _STL::vector<BfmeStringRecord002199C8>::_M_insert_overflow(
    BfmeStringRecord002199C8 *, const BfmeStringRecord002199C8 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0021E29F (183B).
template void _STL::vector<BfmeStringRecord00219A68>::_M_insert_overflow(
    BfmeStringRecord00219A68 *, const BfmeStringRecord00219A68 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x00220EBA (183B).
template void _STL::vector<BfmeStringRecord0022074B>::_M_insert_overflow(
    BfmeStringRecord0022074B *, const BfmeStringRecord0022074B &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x005D5491 (183B).
template void _STL::vector<BfmeStringRecord005D511F>::_M_insert_overflow(
    BfmeStringRecord005D511F *, const BfmeStringRecord005D511F &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x005ECB28 (183B).
template void _STL::vector<BfmeStringRecord005EC43C>::_M_insert_overflow(
    BfmeStringRecord005EC43C *, const BfmeStringRecord005EC43C &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x005F9B4E (183B) vector<BfmeStringRecord005F93E3>::_M_insert_overflow via rowed copy 0x005F9477 Construct 0x005F944A fill_n 0x005F949D.
template void _STL::vector<BfmeStringRecord005F93E3>::_M_insert_overflow(
    BfmeStringRecord005F93E3 *, const BfmeStringRecord005F93E3 &, const _STL::__false_type &, unsigned int, bool);
// Retail 0x0021E69C (55B) push_back via rowed Construct 0x0021A95D plus rowed overflow 0x0021E1EB.
template void _STL::vector<BfmeStringRecord002199C8>::push_back(
    const BfmeStringRecord002199C8 &);
// Retail 0x0021E6D3 (55B) push_back via rowed Construct 0x0021A98A plus rowed overflow 0x0021E29F.
template void _STL::vector<BfmeStringRecord00219A68>::push_back(
    const BfmeStringRecord00219A68 &);
// Retail 0x005D5548 (55B) push_back via rowed Construct 0x005D51EE plus rowed overflow 0x005D5491.
template void _STL::vector<BfmeStringRecord005D511F>::push_back(
    const BfmeStringRecord005D511F &);
