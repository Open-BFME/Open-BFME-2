// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy@PBURva005668E9Element@@PAU1@@_STL@@YAPAURva005668E9Element@@PBU1@0PAU1@ABU__false_type@0@@Z @0x0052D3F1 38B: STLport __uninitialized_copy over 12-byte Rva005668E9Element via pinned _Construct 0x0052D355; caller 0x0052D417 vector copy pushes old-first old-last new-first plus tag; late-cmp esi-edi loop returns final dest.
#include <memory>

struct Rva005668E9Element
{
	int a[3];
	Rva005668E9Element(const Rva005668E9Element &other);
};

namespace _STL
{
template <> void _Construct<Rva005668E9Element, Rva005668E9Element>(Rva005668E9Element *p, const Rva005668E9Element &v);
}

template Rva005668E9Element *_STL::__uninitialized_copy<const Rva005668E9Element *, Rva005668E9Element *>(const Rva005668E9Element *, const Rva005668E9Element *, Rva005668E9Element *, const _STL::__false_type &);
