// cl: /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy@PAURva0040C0C7Element@@PAU1@@_STL@@YAPAURva0040C0C7Element@@PAU1@00ABU__false_type@0@@Z @ 0x0040B9CC (38B). Uninitialized copy for 40-byte element.
// Evidence: stride 0x28 from retail adds; out-of-line _Construct pin at 0x0040B99F; caller _M_insert_overflow 0x0040BFF4.
#include <vector>

struct Rva0040C0C7Element
{
	int a[10];
};

namespace _STL
{
template <> __declspec(nothrow) void _Construct<Rva0040C0C7Element, Rva0040C0C7Element>(Rva0040C0C7Element *__p, const Rva0040C0C7Element &__val);
}

template Rva0040C0C7Element *_STL::__uninitialized_copy<Rva0040C0C7Element *, Rva0040C0C7Element *>(Rva0040C0C7Element *, Rva0040C0C7Element *, Rva0040C0C7Element *, const _STL::__false_type &);
