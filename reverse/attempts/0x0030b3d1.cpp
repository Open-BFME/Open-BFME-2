// ?rva0030B3D1@Rva0030B92C@@QAEXXZ
// partial score=0.7862 date=2026-10-05
// cl: /O1 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030B3D1@Rva0030B92C@@QAEXXZ @0x0030B3D1 478B
// Polygon bounds validate: min/max over points then radius/center/best then flag 0.
// Evidence: layout as Rva0030B92C Scale/Erase (vector+6 floats+flag 0x24); callers 0x0030B6E3/0x0030B706/0x0030B719/0x0030B72C validate-then-read; callees Sub 0x001040AE and sqrt thunk 0x0062921C.
#include <vector>
#include <math.h>

extern float g_Va00BBB8E0;
extern float g_00BBB8DC;
extern float g_Va007C26F0;
extern "C" float INV;

void __cdecl Rva001040AESub(float *dest, float x, float y, const float *src);

struct BfmePod8
{
	float x;
	float y;
};

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
	void rva0030B3D1();
};

// ?rva0030B3D1@Rva0030B92C@@QAEXXZ present-unmatched
void Rva0030B92C::rva0030B3D1()
{
	BfmePod8 *begin = m_vec.begin();
	m_10 = g_Va00BBB8E0;
	const BfmePod8 *end = m_vec.end();
	m_0c = g_Va00BBB8E0;
	m_18 = g_00BBB8DC;
	m_14 = g_00BBB8DC;
	for (BfmePod8 *p = begin; p != end; p++) {
		if (m_0c > p->x)
			m_0c = p->x;
		if (p->y < m_10)
			m_10 = p->y;
		if (m_14 < p->x)
			m_14 = p->x;
		if (p->y > m_18)
			m_18 = p->y;
	}
	BfmePod8 *begin2 = m_vec.begin();
	double tmpR = sqrt((double)(((m_14 - m_0c) * g_Va007C26F0) * ((m_14 - m_0c) * g_Va007C26F0) + ((m_18 - m_10) * g_Va007C26F0) * ((m_18 - m_10) * g_Va007C26F0)));
	BfmePod8 *end2 = m_vec.end();
	float best = g_Va00BBB8E0;
	const float cx = (m_0c + m_14) * g_Va007C26F0;
	const float cy = (m_10 + m_18) * g_Va007C26F0;
	m_20 = (float)tmpR;
	if (end2 != begin2) {
		BfmePod8 *prev = end2 - 1;
		for (BfmePod8 *p = begin2; p != end2; p++) {
			float out[4];
			Rva001040AESub(out, cx, cy, &p->x);
			float d2 = out[0] * out[0] + out[1] * out[1];
			if (best > d2)
				best = d2;
			(void)sqrt((double)((prev->y - p->y) * (prev->y - p->y) + (prev->x - p->x) * (prev->x - p->x)));
			const float d2b = out[0] * out[0] + out[1] * out[1];
			if (d2b < best)
				best = d2b;
			prev = p;
		}
	}
	const float v = (float)(sqrt((double)best) - (double)INV);
	m_1c = v;
	if (v < 0.0f)
		m_1c = 0.0f;
	const m_24 = 0;
}
