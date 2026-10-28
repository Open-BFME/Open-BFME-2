// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?reserve@AreaPolygonBase@@QAEXH@Z, retail 0x0030B96B, 21 bytes.
// Holder ensure via rowed vector E8 reserve 0x0030B876 with clamp to 2.
// Evidence: caller 0x0030B9B4 with ecx this plus int arg; prev reserve same flags next clear same flags.
#include <vector>
struct BfmeE8 { int a[2]; };
// bfme link decl-only begin
// The rowed body calls reserve 0x0030B876 (stlport_vector_e8_allocate_copy.cpp);
// this unit's /EH copy of its _M_allocate_and_copy is not retail's body.
namespace _STL { template <> void vector<BfmeE8, allocator<BfmeE8> >::reserve(unsigned int); }
// bfme link decl-only end

struct AreaPolygonBase
{
	void reserve(int n);
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_points;
};

void AreaPolygonBase::reserve(int n)
{
	if (n < 2)
		n = 2;
	m_points.reserve(n);
}
