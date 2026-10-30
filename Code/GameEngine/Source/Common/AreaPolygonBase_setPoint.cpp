// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?setPoint@AreaPolygonBase@@QAEXHABUBfmeE8@@@Z, retail 0x0030BAA0, 56 bytes.
// Holder set via size check then rowed push 0x0030BA8C for append else direct 8B copy plus flag at +0x24.
// Evidence: chain from 0x0030BA8C; caller 0x00330AE6; prev push same flags next Disp8Lea no-flags.
#include <vector>
struct BfmeE8 { int a[2]; };
struct Rva0030BA8C
{
	void rva0030BA8C(const BfmeE8 &val);
};

struct AreaPolygonBounds { float v[4]; };
struct AreaPolygonBase
{
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_points;
	AreaPolygonBounds m_bounds;
	float m_1c;
	float m_20;
	bool m_dirty;
	void setPoint(int i, const BfmeE8 &val);
};

void AreaPolygonBase::setPoint(int i, const BfmeE8 &val)
{
	if (i == (int)m_points.size()) {
		((Rva0030BA8C *)this)->rva0030BA8C(val);
		return;
	}
	m_points[i] = val;
	m_dirty = true;
}
