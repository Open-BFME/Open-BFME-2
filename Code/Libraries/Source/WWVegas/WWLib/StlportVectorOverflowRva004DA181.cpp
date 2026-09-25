// Target boundaries 0x004DA181/191, 0x004DA01B/30, 0x004D9B80/24 and
// 0x004D9700/29 form STLport vector overflow/clear/destroy helpers for a
// 0x154-byte non-trivial element. Target push_back at 0x004DA2EF calls overflow
// at 0x004DA31F with vector ECX and five overflow arguments.
//
// Rva004DA181Element is an address-derived opaque emitter view. Its virtual
// destructor is used only to reproduce the target's virtual-destroy loop; the
// complete application record identity and fields remain unknown.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva004DA181Element {
	char opaque[336];
	Rva004DA181Element(const Rva004DA181Element &);
	Rva004DA181Element &operator=(const Rva004DA181Element &);
	virtual ~Rva004DA181Element();
};

namespace _STL {
template <> void _Construct<Rva004DA181Element, Rva004DA181Element>(
	Rva004DA181Element *, const Rva004DA181Element &);
}

template void _STL::_Destroy<Rva004DA181Element *>(
	Rva004DA181Element *, Rva004DA181Element *);
template void _STL::vector<Rva004DA181Element>::_M_clear();
template void _STL::vector<Rva004DA181Element>::_M_insert_overflow(
	Rva004DA181Element *, const Rva004DA181Element &,
	const _STL::__false_type &, unsigned int, bool);
