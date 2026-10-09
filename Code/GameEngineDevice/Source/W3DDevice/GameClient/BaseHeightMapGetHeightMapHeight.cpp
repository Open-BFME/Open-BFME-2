// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc

// BaseHeightMapRenderObjClass::getHeightMapHeight (retail 0x0006AD6A, 938
// bytes): virtual, held by vftables 0x007C5FF4 and 0x007CE9CC in the slot
// just before getMaxCellHeight (0x007C5FF8/0x007CE9D0).  Zero Hour's
// BaseHeightMap.cpp body is the source lead (also BFME 1's, which kept it as
// assembly).  BFME2 differences read from retail: m_map (+0x37C0) is used
// directly (no TheTerrainVisual logic map), heights are 16-bit, off-map
// samples ask the WorldHeightMap's clamped lookup 0x0006653B, and the
// smoothed slopes are scaled by MAP_HEIGHT_SCALE before the cross product
// with a 2*MAP_XY_FACTOR run.  Layout as in BaseHeightMapCellQueries.cpp.
// Linking repair follows BF1 dc69c74c54/f989 and the verified BFME2 LOS sibling.
// Retain the VC7 float boundary with a TU-local inline CRT wrapper.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;
typedef int Int;
typedef unsigned short UnsignedShort;

#define MAP_XY_FACTOR 10.0f
#define MAP_HEIGHT_SCALE (MAP_XY_FACTOR / 256.0f)

static __forceinline Real fast_float_floor(Real f)
{
	return floorf(f);
}

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define FAST_REAL_FLOOR(x) fast_float_floor(x)
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float a);	// 0x0004233A
};

class Rva0006AD6AVector3
{
public:
	float X;
	float Y;
	float Z;

	__forceinline void Set(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
	__forceinline float Length2() const
	{
		return X * X + Y * Y + Z * Z;
	}
	__forceinline void Normalize()
	{
		float len2 = Length2();
		if (len2 != 0.0f)
		{
			float oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}
	static __forceinline void Normalized_Cross_Product(const Rva0006AD6AVector3 &a, const Rva0006AD6AVector3 &b, Rva0006AD6AVector3 *set_result)
	{
		set_result->X = (a.Y * b.Z - a.Z * b.Y);
		set_result->Y = (a.Z * b.X - a.X * b.Z);
		set_result->Z = (a.X * b.Y - a.Y * b.X);
		set_result->Normalize();
	}
};

// 0x0006653B: clamped height lookup on the map (rowed under its address name).
class Rva0006653B
{
public:
	UnsignedShort rva0006653B(Int x, Int y);
};

class WorldHeightMap
{
public:
	char m_unknown00[8];
	Int m_width;	// +0x08
	Int m_height;	// +0x0C
	Int m_borderSize;	// +0x10
	char m_unknown14[0x10];
	UnsignedShort *m_data;	// +0x24
};

class BaseHeightMapRenderObjClass
{
public:
	virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal) const;

private:
	char m_unknown0004[0x37C0 - 4];
	WorldHeightMap *m_map;	// +0x37C0
};

Real BaseHeightMapRenderObjClass::getHeightMapHeight(Real x, Real y, Coord3D *normal) const
{
	if (!m_map)
	{
		if (normal)
		{
			normal->x = 0.0f;
			normal->y = 0.0f;
			normal->z = 1.0f;
		}
		return 0;
	}

	float height;

	const Real MAP_XY_FACTOR_INV = 1.0f / MAP_XY_FACTOR;

	float xdiv = x * MAP_XY_FACTOR_INV;
	float ydiv = y * MAP_XY_FACTOR_INV;

	float ixf = FAST_REAL_FLOOR(xdiv);
	float iyf = FAST_REAL_FLOOR(ydiv);

	float fx = xdiv - ixf;
	float fy = ydiv - iyf;

	Int ix = REAL_TO_INT_FLOOR(ixf) + m_map->m_borderSize;
	Int iy = REAL_TO_INT_FLOOR(iyf) + m_map->m_borderSize;
	Int xExtent = m_map->m_width;

	if (ix > (xExtent - 3) || iy > (m_map->m_height - 3) || iy < 1 || ix < 1)
	{
		if (normal)
		{
			normal->x = 0.0f;
			normal->y = 0.0f;
			normal->z = 1.0f;
		}
		return ((Rva0006653B *)m_map)->rva0006653B(ix, iy) * MAP_HEIGHT_SCALE;
	}

	const UnsignedShort *data = m_map->m_data;
	int idx = ix + iy * xExtent;
	float p0 = data[idx];
	float p2 = data[idx + xExtent + 1];
	if (fy > fx)
	{
		float p3 = data[idx + xExtent];
		height = (p3 + (1.0f - fy) * (p0 - p3) + fx * (p2 - p3)) * MAP_HEIGHT_SCALE;
	}
	else
	{
		float p1 = data[idx + 1];
		height = (p1 + fy * (p2 - p1) + (1.0f - fx) * (p0 - p1)) * MAP_HEIGHT_SCALE;
	}

	if (normal)
	{
		int idx4 = ix + (iy - 1) * xExtent;
		int idx0 = ix + iy * xExtent;
		int idx3 = ix + iy * xExtent + xExtent;
		int idx9 = ix + (iy + 2) * xExtent;
		UnsignedShort d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d11;
		d0 = data[idx0];
		d1 = data[idx0 + 1];
		d2 = data[idx3 + 1];
		d3 = data[idx3];
		d4 = data[idx4];
		d5 = data[idx4 + 1];
		d6 = data[idx0 + 2];
		d7 = data[idx3 + 2];
		d8 = data[idx9 + 1];
		d9 = data[idx9];
		d11 = data[idx0 - 1];

		Real deltaZ_X0 = d1 - d11;
		Real deltaZ_X1 = d6 - d0;
		Real deltaZ_X2 = d7 - d3;
		Real deltaZ_X3 = d6 - d0;

		Real deltaZ_Y0 = d3 - d4;
		Real deltaZ_Y1 = d2 - d5;
		Real deltaZ_Y2 = d8 - d1;
		Real deltaZ_Y3 = d9 - d0;

		Real deltaZ_X_Left = deltaZ_X0 * (1.0f - fx) + fx * deltaZ_X3;
		Real deltaZ_X_Right = deltaZ_X1 * (1.0f - fx) + fx * deltaZ_X2;
		Real deltaZ_X = deltaZ_X_Left * (1.0 - fy) + fy * deltaZ_X_Right;

		Real deltaZ_Y_Left = deltaZ_Y0 * (1.0f - fx) + fx * deltaZ_Y3;
		Real deltaZ_Y_Right = deltaZ_Y1 * (1.0f - fx) + fx * deltaZ_Y2;
		Real deltaZ_Y = deltaZ_Y_Left * (1.0 - fy) + fy * deltaZ_Y_Right;

		Rva0006AD6AVector3 l2r, n2f, normalAtTexel;
		l2r.Set(2 * MAP_XY_FACTOR, 0, deltaZ_X * MAP_HEIGHT_SCALE);
		n2f.Set(0, 2 * MAP_XY_FACTOR, deltaZ_Y * MAP_HEIGHT_SCALE);
		Rva0006AD6AVector3::Normalized_Cross_Product(l2r, n2f, &normalAtTexel);
		*normal = *(Coord3D *)&normalAtTexel;
	}

	return height;
}
