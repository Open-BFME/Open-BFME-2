// ?rva0030B232@Rva0030B92C@@QAEXPBM@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030B232@Rva0030B92C@@QAEXPBM@Z, retail 0x0030B232 (132 bytes, ret 4). Same owner layout as the rowed
// Rva0030B1A7 (Scale): the 2D point vector at +0 and the changed flag at +0x24. Applies the first two rows of
// a 3x4 row-major matrix to every point (the z input is zero) and marks the set changed.
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
	void rva0030B232(const float *matrix);
};
void Rva0030B92C::rva0030B232(const float *matrix)
{
	BfmePod8 *e = m_vec.end();
	for (BfmePod8 *p = m_vec.begin(); p != e; ++p) {
		float z = 0.0f;
		float x = p->x;
		float y = p->y;
		float newX = matrix[0] * x + matrix[1] * y + matrix[2] * z + matrix[3];
		float newY = matrix[4] * x + matrix[5] * y + matrix[6] * z + matrix[7];
		p->x = newX;
		p->y = newY;
	}
	m_24 = 1;
}
