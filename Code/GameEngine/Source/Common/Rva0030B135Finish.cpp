// ?rva0030B135@AreaPolygonBase@@QAEXPBUBfmePod8@@@Z
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0030B135@AreaPolygonBase@@QAEXPBUBfmePod8@@@Z @0x0030B135 114B
// Two halves: a step-8 vector accumulate over [_STL::vector<BfmePod8>] at +0
// with addss from the argument pair, then a flag-gated (byte +0x24) accumulate
// of the same argument pair into the four mid floats at +0x0C..+0x18, in the
// order x,y,x,y. Evidence: calls [ecx]/[ecx+4] step 8, flag +0x24, mids
// +0x0C..+0x18, caller 0x00330B75, same layout as the matched 0x0030B92C
// operator= and 0x0030B1A7 scale siblings in this directory.
//
// The mid accumulate goes through a float lvalue (`pm[0] = pm[0] + pa[0]`)
// instead of field-named `m_0c += a->x`. With either `+=` or `m_0c = m_0c +
// a->x`, MSVC emits the *argument* as the movss source and the member as the
// addss memory operand for the first two adds, while retail loads the member
// first (`movss xmm0,[ecx+0xc]; addss xmm0,[edx]`). The lvalue array spelling
// pins the load/operand association so all four come out member-first.

#include <vector>

struct BfmeE8
{
	float x;
	float y;
};

struct BfmePod8 { float x; float y; };

struct AreaPolygonBounds { float v[4]; };
struct AreaPolygonBase
{
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_points;
	AreaPolygonBounds m_bounds;
	float m_1c;
	float m_20;
	bool m_dirty;
	void rva0030B135(const BfmePod8 *a);
};

void AreaPolygonBase::rva0030B135(const BfmePod8 *a)
{
	for (BfmeE8 *p = m_points.begin(), *e = m_points.end(); p != e; ++p) {
		p->x += a->x;
		p->y += a->y;
	}
	if (m_dirty != 0)
		return;
	float *pm = m_bounds.v;
	const float *pa = &a->x;
	pm[0] = pm[0] + pa[0];
	pm[1] = pm[1] + pa[1];
	pm[2] = pm[2] + pa[0];
	pm[3] = pm[3] + pa[1];
}
