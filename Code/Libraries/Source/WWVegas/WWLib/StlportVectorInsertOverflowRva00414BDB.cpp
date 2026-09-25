// Target boundary 0x00414BDB/183 is STLport vector::_M_insert_overflow
// false_type. The matched push_back at 0x00414F27 calls it at 0x00414F54
// with vector ECX and five overflow arguments. Retail advances 0x30-byte
// elements and delegates construction/cleanup to target helpers.
//
// Rva00414BDBElement is an address-derived opaque 48-byte non-trivial emitter.
// Target helper identities establish the vector operation ABI but not the
// concrete element layout or application class.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00414BDBElement {
	char opaque[48];
	Rva00414BDBElement(const Rva00414BDBElement &);
	Rva00414BDBElement &operator=(const Rva00414BDBElement &);
	~Rva00414BDBElement();
};

namespace _STL {
template <> void _Construct<Rva00414BDBElement, Rva00414BDBElement>(
	Rva00414BDBElement *, const Rva00414BDBElement &);
}

template void _STL::vector<Rva00414BDBElement>::_M_insert_overflow(
	Rva00414BDBElement *, const Rva00414BDBElement &,
	const _STL::__false_type &, unsigned int, bool);
