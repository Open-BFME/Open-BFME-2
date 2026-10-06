// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// vector<Rva00336AECElement>::_M_insert_overflow, retail 0x003361C6, 189 bytes.
// Masked-identical to landed BfmePod36 overflow at 0x000AFF6B.

#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}

#include <vector>
struct Rva00336AECElement { int a[9]; };
template void _STL::vector<Rva00336AECElement>::_M_insert_overflow(
	Rva00336AECElement *, const Rva00336AECElement &, const _STL::__false_type &,
	unsigned int, bool);
