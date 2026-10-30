// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030B1A7@AreaPolygonBase@@QAEXM@Z @0x0030B1A7 139B
// Scale vector points and 6 mid floats by arg then flag-gated.
// Evidence: loop [ecx]/[ecx+4] step8 mulss xmm0; flag 0x24; mid 0x0C-0x20 six mulss; caller 0x00330B93; same layout as 0x0030B92C.
#include <vector>
struct BfmeE8 { float x; float y; };
struct AreaPolygonBounds { float v[4]; };
struct AreaPolygonBase
{
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_points;
	AreaPolygonBounds m_bounds;
	float m_1c;
	float m_20;
	bool m_dirty;
	void rva0030B1A7(float f);
};
void AreaPolygonBase::rva0030B1A7(float f)
{
	BfmeE8 *e = m_points.end();
	for (BfmeE8 *p = m_points.begin(); p != e; ++p) {
		p->x *= f;
		p->y *= f;
	}
	if (m_dirty != 0)
		return;
	m_bounds.v[0] *= f;
	m_bounds.v[1] *= f;
	m_bounds.v[2] *= f;
	m_bounds.v[3] *= f;
	m_1c *= f;
	m_20 *= f;
}
