// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Include
// BaseHeightMapRenderObjClass::EstimateMaxHeightAlongLine, native66E69..670B8.
// WB7570D0 names the target method and source; height samples at map+37C0
// use16-bit data, four-corner maxima and0.0390625 scaling. Bounds and
// Bresenham steps are independently decoded from retail. Const qualification
// is a structural inference from read-only access, not a donor target fact.
// Semantic/structural guide: ZH BaseHeightMap.cpp isClearLineOfSight and clean
// BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 BaseHeightMapIsClearLineOfSight.cpp.
// BFME2 removes LOS/bridge tests and retains maximum sampled terrain height.
// x87 fistp is the donor's proven round helper; no lifted instructions.
typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short UnsignedShort;

#include <math.h>
#include <stdlib.h>

#include "Lib/Coord3D.h"

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

// BFME's REAL_TO_INT_FLOOR: CRT floor() then the engine's x87 round.
__forceinline Real fast_float_floor(Real f)
{
	return (Real)floor((double)f);
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

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))
#define __max(a,b) (((a) > (b)) ? (a) : (b))

#define MAP_XY_FACTOR 10.0f
#define MAP_HEIGHT_SCALE 0.0390625f

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Int GetGroundLayer(const Coord3D *pos);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }

private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
// Only the getLayerHeight slot (+0x1C) is used; the others stay pure so this
// file manufactures no vtable.
class TerrainLogic
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer,
		Coord3D *normal = 0, Bool clip = true) const = 0;
};

extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
public:
	Int getXExtent(void) { return m_width; }
	Int getYExtent(void) { return m_height; }
	Int getBorderSizeInline(void) const { return m_borderSize; }
	UnsignedShort *getDataPtr(void) { return m_data; }

private:
	char m_padding00[8];
	Int m_width;
	Int m_height;
	Int m_borderSize;
	char m_padding14[0x10];
	UnsignedShort *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
public:
	Real EstimateMaxHeightAlongLine(const Coord3D& pos,const Coord3D& posOther)const;

private:
	char m_padding00[0x37C0];
	WorldHeightMap *m_map;
};

Real BaseHeightMapRenderObjClass::EstimateMaxHeightAlongLine(const Coord3D& pos, const Coord3D& posOther) const
{
	if (m_map == 0)
		return 0.0f;

	Real result=0.0f;
	const Real MAP_XY_FACTOR_INV = 1.0f / MAP_XY_FACTOR;

	Int borderSize = m_map->getBorderSizeInline();
	Int start_x = REAL_TO_INT_FLOOR(pos.x * MAP_XY_FACTOR_INV) + borderSize;
	// Native conversion scheduling requires direct float overloads here and
	// for both endpoints; start_x retains the donor double floor wrapper.
	Int start_y = fast_float2long_round((Real)floor(pos.y * MAP_XY_FACTOR_INV)) + borderSize;
	Int end_x = fast_float2long_round((Real)floor(posOther.x * MAP_XY_FACTOR_INV)) + borderSize;
	Int end_y = fast_float2long_round((Real)floor(posOther.y * MAP_XY_FACTOR_INV)) + borderSize;
	Int delta_x = abs(end_x - start_x);			// The difference between the x's
	Int delta_y = abs(end_y - start_y);			// The difference between the y's
	Int x = start_x;												// Start x off at the first pixel
	Int y = start_y;												// Start y off at the first pixel

	Int xinc1, xinc2;
	if (end_x >= start_x)								// The x-values are increasing
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else																// The x-values are decreasing
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	Int yinc1, yinc2;
	if (end_y >= start_y)               // The y-values are increasing
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else																// The y-values are decreasing
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	Int den, num, numadd, numpixels;
	if (delta_x >= delta_y)							// There is at least one x-value for every y-value
	{
		xinc1 = 0;												// Don't change the x when numerator >= denominator
		yinc2 = 0;												// Don't change the y for every iteration
		den = delta_x;
		num = delta_x / 2;
		numadd = delta_y;
		numpixels = delta_x;							// There are more x-values than y-values
	}
	else																// There is at least one y-value for every x-value
	{
		xinc2 = 0;												// Don't change the x for every iteration
		yinc1 = 0;												// Don't change the y when numerator >= denominator
		den = delta_y;
		num = delta_y / 2;
		numadd = delta_x;
		numpixels = delta_y;							// There are more y-values than x-values
	}

	const UnsignedShort* data = m_map->getDataPtr();
	Int xExtent = m_map->getXExtent();
	Int yExtent = m_map->getYExtent();
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		if (x < 0 ||
				y < 0 ||
				x >= xExtent-1 ||
				y >= yExtent-1)
		{
			// once we go off the map, we're done
			break;
		}


		Int idx = x + y*xExtent;
		float height = data[idx];
		height = __max(height, data[idx + 1]);
		height = __max(height, data[idx + xExtent]);
		height = __max(height, data[idx + xExtent + 1]);
		height *= MAP_HEIGHT_SCALE;

		if(height>result)result=height;

		// continue with the maintenance.
		num += numadd;										// Increase the numerator by the top of the fraction
		if (num >= den)										// Check if numerator >= denominator
		{
			num -= den;											// Calculate the new numerator value
			x += xinc1;											// Change the x as appropriate
			y += yinc1;											// Change the y as appropriate
		}
		x += xinc2;												// Change the x as appropriate
		y += yinc2;												// Change the y as appropriate
	}

	return result;
}
