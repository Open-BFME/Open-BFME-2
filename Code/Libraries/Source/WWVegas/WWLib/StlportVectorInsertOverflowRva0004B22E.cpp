// Target boundary 0x0004B22E/183: STLport vector::_M_insert_overflow false_type.
// The matched vector::push_back at 0x0004B2E5 calls it with the five-argument
// thiscall ABI. Retail uses a 0x5C-byte element stride and calls the allocator,
// uninitialized-copy, construct, fill and clear helpers pinned from target
// call sites.
//
// Rva0004B22EElement is only an address-derived 92-byte nontrivial emitter
// view. Target copy/destruction helpers support a nontrivial record; the full
// application element identity/layout is not asserted here.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0004B22EElement {
	char opaque[92];
	Rva0004B22EElement(const Rva0004B22EElement &);
	Rva0004B22EElement &operator=(const Rva0004B22EElement &);
	~Rva0004B22EElement();
};

namespace _STL {
template <> void _Construct<Rva0004B22EElement, Rva0004B22EElement>(
	Rva0004B22EElement *, const Rva0004B22EElement &);
template <> void vector<Rva0004B22EElement>::_M_clear();
}

template void _STL::vector<Rva0004B22EElement>::_M_insert_overflow(
	Rva0004B22EElement *, const Rva0004B22EElement &,
	const _STL::__false_type &, unsigned int, bool);
