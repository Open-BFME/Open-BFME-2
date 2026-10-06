// ?insert@?$vector@URva00504755Record@@V?$allocator@URva00504755Record@@@_STL@@@_STL@@QAEPAURva00504755Record@@PAU3@ABU3@@Z
// partial score=0.91 date=2026-10-05
// cl: /O1 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// vector<Rva00504755Record>::insert at 0x00504D57 161B linkbody for 2 files.
// Evidence: calls rowed _M_insert_overflow 0x005049E8 plus _Construct 0x0041360E plus copy_backward 0x005B2B1E; sar 4 stride 16; LINK BONUS via 0x00504E6D.
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
template Rva00504755Record *_STL::vector<Rva00504755Record, _STL::allocator<Rva00504755Record> >::insert(Rva00504755Record *, const Rva00504755Record &);
