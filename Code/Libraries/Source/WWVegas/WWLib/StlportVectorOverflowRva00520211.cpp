// Target boundaries 0x00520211/183, 0x0052010D/30 and 0x005200F4/25 are
// STLport vector overflow/clear/destroy helpers for an 80-byte non-trivial
// element. The target caller at 0x005205DA calls overflow at 0x005206C7 with
// vector ECX and five overflow arguments. Retail advances elements by 0x50.
//
// Rva00520211Element is an address-derived opaque 80-byte emitter view. Its
// copy/destroy helpers are pinned from target calls; no application fields or
// concrete element identity are asserted.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00520211Element {
	char opaque[80];
	Rva00520211Element(const Rva00520211Element &);
	Rva00520211Element &operator=(const Rva00520211Element &);
	~Rva00520211Element();
};

namespace _STL {
template <> void _Construct<Rva00520211Element, Rva00520211Element>(
	Rva00520211Element *, const Rva00520211Element &);
}

template void _STL::_Destroy<Rva00520211Element *>(
	Rva00520211Element *, Rva00520211Element *);
template void _STL::vector<Rva00520211Element>::_M_clear();
template void _STL::vector<Rva00520211Element>::_M_insert_overflow(
	Rva00520211Element *, const Rva00520211Element &,
	const _STL::__false_type &, unsigned int, bool);
