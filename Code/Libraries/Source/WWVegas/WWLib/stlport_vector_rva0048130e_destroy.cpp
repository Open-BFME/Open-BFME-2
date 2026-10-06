// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAURva0048130E@@@_STL@@YAXPAURva0048130E@@0@Z, retail 0x00481595, 25 bytes.
// Range destroy for ProductionQueueHordeContainModuleData's +0xD4 vector
// element (8-byte filter-plus-string Rva0048130E whose dtor is rowed at
// 0x0048130E): strides 8 calling that dtor. Same 25B loop shape as rowed
// BfmeVectorRecord000BDF17 _Destroy at 0x000C37CD. Emitted via explicit
// _Destroy instantiation over an opaque 8-byte view declaring the rowed
// dtor; the vector dtor at 0x004815AE calls here.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
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

struct Rva0048130E
{
	~Rva0048130E();

	unsigned char m_data[8];
};

template void _STL::_Destroy<Rva0048130E *>(Rva0048130E *, Rva0048130E *);

// vector<Rva0048130E> growth path: _M_insert_overflow (retail 0x0048160B),
// _M_clear (0x004815ED) and push_back (0x004816BD) are byte-identical from
// this whole-class instantiation. Their calls read the rowed _Construct,
// __uninitialized_fill_n and __uninitialized_copy of this element, the
// _Destroy above and the ICF 8-byte allocate.
template class _STL::vector<Rva0048130E, _STL::allocator<Rva0048130E> >;
