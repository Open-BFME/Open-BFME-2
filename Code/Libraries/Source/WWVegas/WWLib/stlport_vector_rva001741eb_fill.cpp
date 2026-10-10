// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__uninitialized_fill_n@PAURva001741EBElement@@IU1@@_STL@@YAPAURva001741EBElement@@PAU1@IABU1@ABU__false_type@0@@Z
// @ 0x001733F6 (37B): count loop constructing via the pinned _Construct at
// 0x00173351 striding 0x30. Caller at 0x00173F67 in _M_insert_overflow
// 0x00173EF9. Same recipe as stlport_vector_bfmeassignrecord32_allocate_copy.cpp
// (37B fill_n via rowed _Construct stride 0x20).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
struct Rva001741EBElement {
	int a[12];
};
namespace _STL {
template <> void _Construct<Rva001741EBElement, Rva001741EBElement>(Rva001741EBElement *, const Rva001741EBElement &);
}
template class _STL::vector<Rva001741EBElement, _STL::allocator<Rva001741EBElement> >;
