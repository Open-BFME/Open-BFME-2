// ?rva0030E67C@Rva0030E7D0@@QBEMMM@Z
// partial score=0.92 date=2026-10-05
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// stlport
// ??0Rva0030E7D0@@QAE@XZ @0x0030E7D0 46B ctor vector BfmeE16 at +0 via rowed Vector_base 0x00211E58 zeroes +0xC +0x10 +0x18 and byte +0x1C float +0x14 from g_Va00BBB8D8 evidence callers 0x0008BA61 neighbours ParabolicEase and StlportVectorFill
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

extern float g_Va00BBB8D8;
extern const float BfmeZeroRange;
extern float g_Va00BC2428;

extern "C" __declspec(dllimport) double __cdecl floor(double);

class Rva0030E7D0
{
public:
	Rva0030E7D0();
	float rva0030E67C(float x, float y) const;
private:
	_STL::vector<BfmeE16> m_vec00;
	int m_0C;
	int m_10;
	float m_14;
	int m_18;
	bool m_1C;
};

Rva0030E7D0::Rva0030E7D0()
	: m_vec00()
{
	m_14 = g_Va00BBB8D8;
	m_0C = 0;
	m_10 = 0;
	m_18 = 0;
	m_1C = false;
}

// ?rva0030E67C@Rva0030E7D0@@QBEMMM@Z present-unmatched
float Rva0030E7D0::rva0030E67C(float x, float y) const
{
	if (!m_1C)
		return BfmeZeroRange;
	float base = (float)m_18 * g_Va00BC2428;
	float scale = g_Va00BBB8D8 / m_14;
	x = base + x;
	y = base + y;
	x *= scale;
	y *= scale;
	int ix = (int)floor((double)x);
	int iy = (int)floor((double)y);
	float fx = x - (float)ix;
	float fy = y - (float)iy;
	if (fx < 0.0f)
		ix = 0;
	if (fy < 0.0f)
		iy = 0;
	int w = m_0C;
	int h = m_10;
	if (ix > w - 1)
		ix = w - 1;
	if (iy > h - 1)
		iy = h - 1;
	const float *data = (const float *)m_vec00.begin();
	if (ix > w - 2)
		return data[ix + iy * w];
	if (iy > h - 2)
		return data[ix + iy * w];
	int idx = ix + iy * w;
	float a00 = data[idx];
	float abr = data[w + idx + 1];
	float r;
	if (fy <= fx)
	{
		float a10 = data[idx + 1];
		float a01 = data[idx + w];
		float u = a10 - a00;
		float v = abr - a01;
		float t = a01 - a00;
		r = a00 + u * fx + (t + (v - u) * fx) * fy;
	}
	else
	{
		float a01 = data[idx + w];
		float a10 = data[idx + 1];
		r = a00 + (a01 - a00) * fy + (a10 - a00 + (abr - a10 - (a01 - a00)) * fy) * fx;
	}
	return r;
}
