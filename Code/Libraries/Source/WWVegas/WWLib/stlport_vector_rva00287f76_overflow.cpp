// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// vector<Rva00287F76Element>::_M_insert_overflow, retail 0x00287B4D, 184 bytes.
// Masked-identical to landed BfmeE8 overflow at 0x00057C80 (8-byte stride,
// inline free). Same no-EH / bfmealloc recipe as stlport_vector_e8_allocate_copy.cpp.

#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
struct Rva00287F76Element { int a, b; };
template class _STL::vector<Rva00287F76Element, _STL::allocator<Rva00287F76Element> >;
