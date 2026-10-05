// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// vector<Rva00504755Record>::_M_insert_overflow, retail 0x005049E8, 186 bytes.
// Masked-identical to landed BfmeE16 overflow at 0x005B3970 (16-byte stride,
// inline free). Same no-EH recipe as stlport_vector_e16_noexc.cpp.

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
struct Rva00504755Record { float x, y, z, w; };
template class _STL::vector<Rva00504755Record, _STL::allocator<Rva00504755Record> >;
