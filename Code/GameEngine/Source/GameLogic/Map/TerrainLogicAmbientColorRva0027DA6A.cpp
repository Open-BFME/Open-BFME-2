// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0027DA6A@W3DTerrainLogic@@QAE_NPBMPAM@Z retail 0x0027DA6A 507 bytes.
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

#include "../../../../GameEngineDevice/Include/W3DDevice/GameLogic/W3DTerrainLogicClass.h"

bool W3DTerrainLogic::rva0027DA6A(const float *pos, float *color)
{
	if (field24 == 0 || field1C < 1 || field20 < 1)
		return false;
	float border = slot11();
	float x = border + pos[0];
	float y = border + pos[1];
	if (x < 0.0f)
		x = 0.0f;
	else if (field1C * 10.0f < x)
		x = field1C * 10.0f;
	if (y < 0.0f)
		y = 0.0f;
	else if (field20 * 10.0f < y)
		y = field20 * 10.0f;
	x *= (float)field28 / (field1C * 10.0f);
	y *= (float)field2C / (field20 * 10.0f);
	int ix = fast_float2long_round((float)floor(x));
	int iy = fast_float2long_round((float)floor(y));
	if (ix >= field28 - 1)
		ix = field28 - 2;
	if (iy >= field2C - 1)
		iy = field2C - 2;
	x -= ix;
	y -= iy;
	if (x > 1.0f)
		x = 1.0f;
	if (y > 1.0f)
		y = 1.0f;
	unsigned char *row0 = field24 + ix * 3 + iy * 3 * field28;
	unsigned char *row1 = row0 + field28 * 3;
	for (int i = 0; i < 3; ++i, ++row0, ++row1)
	{
		float &dst = (i == 0) ? color[2] : ((i == 1) ? color[1] : color[0]);
		dst = ((row0[0] * (1.0f - x) + row0[3] * x) * (1.0f - y) + (row1[0] * (1.0f - x) + row1[3] * x) * y) * 0.003921569f;
	}
	return true;
}
