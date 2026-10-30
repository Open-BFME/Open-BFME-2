// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?deletePoint@AreaPolygonBase@@QAEXH@Z @0x0030B85A 28B
// Erase vector element by index via rowed Pod8 erase then set flag 1.
// Evidence: lea [eax+ecx*8] then rowed erase 0x00054B3F; flag 0x24=1; caller 0x00330B1E; same layout as 0x0030B92C.
#include <vector>
struct BfmeE8 { float x; float y; };
struct BfmePod8 { float x; float y; };
struct AreaPolygonBounds { float v[4]; };
struct AreaPolygonBase
{
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_points;
	AreaPolygonBounds m_bounds;
	float m_1c;
	float m_20;
	bool m_dirty;
	void deletePoint(int i);
};
// bfme link decl-only begin
namespace _STL { template <> BfmePod8 * vector<BfmePod8,_STL::allocator<BfmePod8> >::erase(BfmePod8 *); }
// bfme link decl-only end
void AreaPolygonBase::deletePoint(int i)
{
	((_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > *)&m_points)->erase(
		((_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > *)&m_points)->begin() + i);
	m_dirty = 1;
}
