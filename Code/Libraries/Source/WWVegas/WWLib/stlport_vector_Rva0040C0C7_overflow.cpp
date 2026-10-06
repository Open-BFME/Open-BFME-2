// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@URva0040C0C7Element@@V?$allocator@URva0040C0C7Element@@@_STL@@@_STL@@IAEXPAURva0040C0C7Element@@ABU3@ABU__false_type@2@I_N@Z @ 0x0040BFF4 (183B). Vector growth path for 40-byte element.
// Evidence: stride 0x28 from retail imul; callees uninitialized_copy 0x0040B9CC fill_n 0x0040B9F2 Construct pin 0x0040B99F.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
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

struct Rva0040C0C7Element
{
	virtual ~Rva0040C0C7Element();
	int a[9];
};

namespace _STL
{
template <> void _Construct<Rva0040C0C7Element, Rva0040C0C7Element>(Rva0040C0C7Element *, const Rva0040C0C7Element &);
}

template void _STL::vector<Rva0040C0C7Element>::_M_insert_overflow(
	Rva0040C0C7Element *,
	const Rva0040C0C7Element &,
	const _STL::__false_type &,
	unsigned int,
	bool);
