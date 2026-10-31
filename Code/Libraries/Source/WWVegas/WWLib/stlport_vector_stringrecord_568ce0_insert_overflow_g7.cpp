// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 20-byte BfmeStringRecord00568CE0 vector _M_insert_overflow at RVA 0x0056A12D.
// /G7 emits the retail register allocation and imul; explicit member (not whole-class)
// instantiation keeps the other members owned by the /O1 sibling TU. _Construct is
// declared only so the copies call the rowed body at 0x00568F92.
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
class Rva00568F04;
struct BfmeStringRecord00568CE0 {
    AsciiString text0, text1;
    unsigned int word0;
    Rva00568F04 *subject;
    unsigned char flag;
    BfmeStringRecord00568CE0();
    BfmeStringRecord00568CE0(const BfmeStringRecord00568CE0 &other) : text0(other.text0), text1(other.text1), word0(other.word0), subject(other.subject), flag(other.flag) {}
};
#include <vector>
namespace _STL {
template <> void _Construct<BfmeStringRecord00568CE0, BfmeStringRecord00568CE0>(
	BfmeStringRecord00568CE0 *, const BfmeStringRecord00568CE0 &);
}
template void _STL::vector<BfmeStringRecord00568CE0>::_M_insert_overflow(
	BfmeStringRecord00568CE0 *,
	const BfmeStringRecord00568CE0 &,
	const _STL::__false_type &,
	unsigned int,
	bool);
