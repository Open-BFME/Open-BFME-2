// Target boundary 0x000AFF6B/189 is STLport vector::_M_insert_overflow
// false_type. The 232-byte fill-insert caller at 0x000B0478 calls it at
// 0x000B0554 with vector ECX and five overflow arguments. Retail advances
// 0x24-byte elements and allocates/copies/fills before releasing old storage.
//
// BfmePod36 is a size-only 36-byte emitter view. The concrete retail element
// identity and payload are unknown.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
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

#include <vector>

struct BfmePod36 { int a[9]; };

template void _STL::vector<BfmePod36>::_M_insert_overflow(
	BfmePod36 *, const BfmePod36 &, const _STL::__false_type &,
	unsigned int, bool);
