// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030B1A7@Rva0030B92C@@QAEXM@Z @0x0030B1A7 139B
// Scale vector points and 6 mid floats by arg then flag-gated.
// Evidence: loop [ecx]/[ecx+4] step8 mulss xmm0; flag 0x24; mid 0x0C-0x20 six mulss; caller 0x00330B93; same layout as 0x0030B92C.
#include <vector>
struct BfmePod8 { float x; float y; };
struct Rva0030B92C
{
	_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > m_vec;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
	unsigned char m_24;
	void rva0030B1A7(float f);
};
void Rva0030B92C::rva0030B1A7(float f)
{
	BfmePod8 *e = m_vec.end();
	for (BfmePod8 *p = m_vec.begin(); p != e; ++p) {
		p->x *= f;
		p->y *= f;
	}
	if (m_24 != 0)
		return;
	m_0c *= f;
	m_10 *= f;
	m_14 *= f;
	m_18 *= f;
	m_1c *= f;
	m_20 *= f;
}
