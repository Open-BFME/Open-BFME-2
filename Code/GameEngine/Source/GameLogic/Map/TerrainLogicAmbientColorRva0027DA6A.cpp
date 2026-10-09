// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0027DA6A@Rva0062AF7@@QAE_NPBMPAM@Z retail 0x0027DA6A 507 bytes.
// Follows 0x0027DA58 (0x27DA58+18) in the TerrainLogic unit of
// Rva0062AF7Rva0027D815.cpp. Samples the ambient lightmap loaded by
// TerrainLogicLoadAmbientLightmap.cpp (pixels +0x24 width +0x28 height +0x2C
// unsigned) bilinearly at a world point and writes BGR texels as a 0..1
// colour triple in reverse order. WB twin 0xC4E300 (743 bytes unnamed) gives
// the shape: null map or map extent below one cell returns false then the
// vslot 11 (offset 0x2C) float border is added to x and y which clamp to
// [0 extent*10] (extent ints +0x1C +0x20 times MAP_XY_FACTOR 10.0f) and
// scale by pixels per world unit then floor through the import and the
// fld/fistp REAL_TO_INT_FLOOR helper. Indices clamp to size-2 and the
// fractions to 1.0f. Constant 0.003921569f is 1/255. Caller 0x0006FB59 with
// ecx TheTerrainLogic (0x00DFEC50). Member names are address-derived.
#include <math.h>

static __forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class Rva0062AF7
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual float slot11();
	bool rva0027DA6A(const float *pos, float *color);

private:
	char m_pad04[0x18];
	int m_1c;
	int m_20;
	unsigned char *m_data24;
	unsigned int m_width28;
	unsigned int m_height2c;
};

bool Rva0062AF7::rva0027DA6A(const float *pos, float *color)
{
	if (m_data24 == 0 || m_1c < 1 || m_20 < 1)
		return false;
	float border = slot11();
	float x = border + pos[0];
	float y = border + pos[1];
	if (x < 0.0f)
		x = 0.0f;
	else if (m_1c * 10.0f < x)
		x = m_1c * 10.0f;
	if (y < 0.0f)
		y = 0.0f;
	else if (m_20 * 10.0f < y)
		y = m_20 * 10.0f;
	x *= (float)m_width28 / (m_1c * 10.0f);
	y *= (float)m_height2c / (m_20 * 10.0f);
	int ix = fast_float2long_round((float)floor(x));
	int iy = fast_float2long_round((float)floor(y));
	if (ix >= m_width28 - 1)
		ix = m_width28 - 2;
	if (iy >= m_height2c - 1)
		iy = m_height2c - 2;
	x -= ix;
	y -= iy;
	if (x > 1.0f)
		x = 1.0f;
	if (y > 1.0f)
		y = 1.0f;
	unsigned char *row0 = m_data24 + ix * 3 + iy * 3 * m_width28;
	unsigned char *row1 = row0 + m_width28 * 3;
	for (int i = 0; i < 3; ++i, ++row0, ++row1)
	{
		float &dst = (i == 0) ? color[2] : ((i == 1) ? color[1] : color[0]);
		dst = ((row0[0] * (1.0f - x) + row0[3] * x) * (1.0f - y) + (row1[0] * (1.0f - x) + row1[3] * x) * y) * 0.003921569f;
	}
	return true;
}
