// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?push_back@?$vector@URva00414BDBElement@@V?$allocator@URva00414BDBElement@@@_STL@@@_STL@@QAEXABURva00414BDBElement@@@Z, retail 0x00414F27, 55 bytes.
// STLport 4.5.3 vector<Rva00414BDBElement>::push_back sibling of Rva0052BDE6 push_back at 0x005662CC (55B same flags).
// Fast path constructs via rowed _Construct at 0x00414A76; full path calls rowed _M_insert_overflow at 0x00414BDB with n=1 fill=1.
// Chain lane: calls just-landed 0x00414A76; caller at 0x00414FE9.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct Rva00414BDBElement {
	char opaque[48];
	Rva00414BDBElement(const Rva00414BDBElement &);
	Rva00414BDBElement &operator=(const Rva00414BDBElement &);
	~Rva00414BDBElement();
};

namespace _STL {
template <> void _Construct<Rva00414BDBElement, Rva00414BDBElement>(Rva00414BDBElement *, const Rva00414BDBElement &);
}

template void _STL::vector<Rva00414BDBElement>::push_back(const Rva00414BDBElement &);
