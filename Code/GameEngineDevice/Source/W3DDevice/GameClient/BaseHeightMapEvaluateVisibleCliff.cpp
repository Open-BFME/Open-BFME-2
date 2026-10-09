// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BFME1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d clean body,
// game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapEvaluateVisibleCliff.cpp.
// Native6737E..67494 independently proves map37C0, protected height-load
// ABI62A58 and unsigned16 corner conversion at scale10/256. Cache map
// once to retain native ESI across the four existing calls. The static
// table starts at VA DB4144: its emitted16 bytes exactly equal the image
// {0,10,0,0}; native and source runtime initialization fill the last two.
// Guard VA DE1EB4 is initially zero. No new data pin or address global.

#include <math.h>

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short UnsignedShort;

#define MAP_XY_FACTOR (10.0f)
#define MAP_HEIGHT_SCALE (MAP_XY_FACTOR/256.0f)  // BFME; Zero Hour divided by 16

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class BoundedShortGrid { public: short rva00062A58(Int,Int); };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
public:
	Bool evaluateAsVisibleCliff( Int xIndex, Int yIndex, Real valuesGreaterThanRad );

private:
	unsigned char m_unreconstructed[0x37C0];
	BoundedShortGrid *m_map;
};

Bool BaseHeightMapRenderObjClass::evaluateAsVisibleCliff( Int xIndex, Int yIndex, Real valuesGreaterThanRad )
{
	static const Real distance[4] =
	{
		0.0f,
		1.0f * MAP_XY_FACTOR,
		sqrt(2.0f) * MAP_XY_FACTOR,
		1.0f * MAP_XY_FACTOR,
	};

	BoundedShortGrid *map=m_map;
	UnsignedShort bytes[4] =
	{
		map->rva00062A58( xIndex + 0, yIndex + 0 ),
		map->rva00062A58( xIndex + 1, yIndex + 0 ),
		map->rva00062A58( xIndex + 1, yIndex + 1 ),
		map->rva00062A58( xIndex + 0, yIndex + 1 ),
	};

	Real heights[4] =
	{
		((Real) (bytes[0])) * MAP_HEIGHT_SCALE,
		((Real) (bytes[1])) * MAP_HEIGHT_SCALE,
		((Real) (bytes[2])) * MAP_HEIGHT_SCALE,
		((Real) (bytes[3])) * MAP_HEIGHT_SCALE,
	};

	Bool anyImpassable = false;
	for (Int i = 1; i < 4 && !anyImpassable; ++i)
	{
		if (fabs((heights[i] - heights[0]) / distance[i]) > valuesGreaterThanRad)
			anyImpassable = true;
	}

	return anyImpassable;
}
