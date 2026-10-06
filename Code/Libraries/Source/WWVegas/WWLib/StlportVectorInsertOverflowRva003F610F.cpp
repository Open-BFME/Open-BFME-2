// Target boundaries 0x003F610F/183 and 0x003F5EF7/30 are STLport vector
// overflow/clear helpers for a 48-byte element. The matched push_back at
// 0x003F6401 calls overflow with the five-argument thiscall ABI; its copy,
// construction, fill and destruction helpers establish a non-trivial element.
//
// Rva003F610FElement is only an address-derived 48-byte non-trivial emitter
// view. The target's application record identity and field layout are unknown.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

struct Rva003F610FElement {
	char opaque[48];
	Rva003F610FElement(const Rva003F610FElement &);
	Rva003F610FElement &operator=(const Rva003F610FElement &);
	~Rva003F610FElement();
};

namespace _STL {
template <> void _Construct<Rva003F610FElement, Rva003F610FElement>(
	Rva003F610FElement *, const Rva003F610FElement &);
}

template void _STL::vector<Rva003F610FElement>::_M_clear();
template void _STL::vector<Rva003F610FElement>::_M_insert_overflow(
	Rva003F610FElement *, const Rva003F610FElement &,
	const _STL::__false_type &, unsigned int, bool);
