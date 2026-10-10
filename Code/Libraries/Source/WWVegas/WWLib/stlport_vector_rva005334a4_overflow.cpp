// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// 4-byte element with copy ctor only (no dtor): force _Construct on n==1 while
// letting _M_clear collapse to free (trivial destroy), matching retail 0x00532ED9.

#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
struct Rva005334A4Element {
	int a;
	Rva005334A4Element(const Rva005334A4Element &);
};
template void _STL::vector<Rva005334A4Element, _STL::allocator<Rva005334A4Element> >::_M_insert_overflow(
	Rva005334A4Element *, const Rva005334A4Element &, const _STL::__false_type &, unsigned int, bool);
