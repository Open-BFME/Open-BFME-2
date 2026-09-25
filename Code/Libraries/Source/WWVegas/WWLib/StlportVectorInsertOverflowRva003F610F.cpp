// Target boundaries 0x003F610F/183 and 0x003F5EF7/30 are STLport vector
// overflow/clear helpers for a 48-byte element. The matched push_back at
// 0x003F6401 calls overflow with the five-argument thiscall ABI; its copy,
// construction, fill and destruction helpers establish a non-trivial element.
//
// Rva003F610FElement is only an address-derived 48-byte non-trivial emitter
// view. The target's application record identity and field layout are unknown.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
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
