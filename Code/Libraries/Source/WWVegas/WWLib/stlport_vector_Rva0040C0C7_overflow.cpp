// cl: /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@URva0040C0C7Element@@V?$allocator@URva0040C0C7Element@@@_STL@@@_STL@@IAEXPAURva0040C0C7Element@@ABU3@ABU__false_type@2@I_N@Z @ 0x0040BFF4 (183B). Vector growth path for 40-byte element.
// Evidence: stride 0x28 from retail imul; callees uninitialized_copy 0x0040B9CC fill_n 0x0040B9F2 Construct pin 0x0040B99F.
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
