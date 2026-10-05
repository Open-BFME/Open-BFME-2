// cl: /O1 /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// vector<Rva00587375>::_M_insert_overflow, retail 0x00587C40, 189 bytes.
// Masked-identical to landed BfmeFixedObject60; struct spelling for U-mangle.

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
struct Rva00587375Block16 { unsigned int words[4]; Rva00587375Block16(); };
struct Rva00587375 {
	unsigned int word_00, word_04, word_08;
	Rva00587375Block16 blocks_0C[3];
	Rva00587375();
	Rva00587375(const Rva00587375 &rhs);
	Rva00587375 &operator=(const Rva00587375 &rhs);
};
typedef char Rva00587375Extent[sizeof(Rva00587375) == 60 ? 1 : -1];
template class _STL::vector<Rva00587375, _STL::allocator<Rva00587375> >;
