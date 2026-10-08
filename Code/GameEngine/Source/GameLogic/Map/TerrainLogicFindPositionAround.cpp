// cl: /O1 /arch:SSE /G7 /ICode/Libraries/Include /DNDEBUG /MD /EHsc
// Retail285202..28562E,1068B, cdecl three pointers. Semantic donor:
// Open-BFME-1 34f59164f6d1efd413c5fd37f4894ec834c3c0fe
// game/GameEngine/Source/GameLogic/Map/FindPositionAround001AF610.cpp,
// whose source derives the ring search from Zero Hour PartitionManager.
// Target WB and the random-call literal place it in TerrainLogic.cpp and
// call it FindPositionAround. Keep the existing PartitionManager static
// call view used by verified consumers; original class/qualification is
// not established by that ABI view. No receiver is passed or accessed.
// Retail establishes the trace gate at GameLogic+1B4 (its precise field
// meaning is unresolved), trace FILE global, and ring-spacing .data word.
// All diagnostic literals, source path, line4378 and float constants
// are checked independently by the normal gate. The second success trace
// deliberately prints the positive angle, as both retail and donor do.
// The x87 rounding primitive is donor compiler machinery: native FISTP
// obeys the current rounding mode. MSVC rejects /QIfist with /arch:SSE;
// a plain C++ integral cast would truncate or call a different helper.
#include <math.h>

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#define TRUE true
#define FALSE false
#define TWO_PI 6.28318530718f
#define RANDOM_START_ANGLE -99999.9f

#include "Lib/Coord3D.h"

struct Region3D
{
	Coord3D lo, hi;

	Bool isInRegionNoZ( const Coord3D *query ) const
	{
		return (lo.x < query->x) && (query->x < hi.x) &&
			(lo.y < query->y) && (query->y < hi.y);
	}
};

struct FindPositionOptions
{
	UnsignedInt flags;
	Real minRadius;
	Real maxRadius;
	Real startAngle;
	Real maxZDelta;
	void *ignoreObject;
	const void *sourceToPathToDest;
	void *relationshipObject;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void getMaximumPathfindExtent( Region3D *extent );
};
extern TerrainLogic *TheTerrainLogic;

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

typedef void FILE;
extern "C" FILE *theLogicRandomLogFile;
extern bool g_bfmeDockingTraceActive;
extern "C" int fprintf( FILE *, const char *, ... );
#define bfmeRetailCritterDesyncLog fprintf

static Real ringSpacing = 5.0f;

Real GetGameLogicRandomValueReal( Real lo, Real hi, char *file, Int line );
Bool Rva00284AC6TryPosition( const Coord3D *center, Real dist, Real angle,
	const FindPositionOptions *options, Coord3D *result );

__forceinline long fast_float2long_round(float f) { long i; __asm { fld [f] } __asm { fistp [i] } return i; }

#define DOCKING_TRACE (g_bfmeDockingTraceActive && *(const Int *)((const char *)TheGameLogic + 0x1b4) > 0 && theLogicRandomLogFile)

#include "../../Common/PartitionRangeQueryCallView.h"
Bool PartitionManager::findPositionAround( const Coord3D *center,
	const FindPositionOptions *options,
	Coord3D *result )
{
	Region3D extent;
	TheTerrainLogic->getMaximumPathfindExtent( &extent );

	if (DOCKING_TRACE)
		bfmeRetailCritterDesyncLog( theLogicRandomLogFile,
			"    TerrainLogic::FindPositionAround() center=%g,%g,%g, extent=lo:%g,%g,%g hi:%g,%g,%g",
			center->x, center->y, center->z,
			extent.lo.x, extent.lo.y, extent.lo.z,
			extent.hi.x, extent.hi.y, extent.hi.z );

	if (!extent.isInRegionNoZ( center ))
	{
		if (DOCKING_TRACE)
			bfmeRetailCritterDesyncLog( theLogicRandomLogFile,
				"    !extent.isInRegionNoZ, result = center, return true" );
		*result = *center;
		return true;
	}

	Real startAngle;
	if (options->startAngle == RANDOM_START_ANGLE)
		startAngle = GetGameLogicRandomValueReal( 0.0f, TWO_PI,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Map\\TerrainLogic.cpp", 0x111a );
	else
		startAngle = options->startAngle;

	if (DOCKING_TRACE)
		bfmeRetailCritterDesyncLog( theLogicRandomLogFile, "    startAngle=%g", startAngle );

	for (Real dist = options->minRadius; dist <= options->maxRadius; dist += ringSpacing)
	{
		Real angleSpacing;
		if (dist == options->minRadius)
			angleSpacing = TWO_PI;
		else
			angleSpacing = (ringSpacing / (dist + 1.0f)) * (TWO_PI / 6.0f);

		if (DOCKING_TRACE)
			bfmeRetailCritterDesyncLog( theLogicRandomLogFile, "    angleSpacing=%g", angleSpacing );

		Int samples = fast_float2long_round( (Real)ceil( (TWO_PI / angleSpacing) / 2.0f ) );
		for (Int i = 0; i < samples; ++i)
		{
			if (Rva00284AC6TryPosition( center, dist, startAngle + angleSpacing * i, options, result ) == TRUE)
			{
				if (DOCKING_TRACE)
					bfmeRetailCritterDesyncLog( theLogicRandomLogFile,
						"    TryPosition1 succeeds - i=%d, center=%g,%g,%g, dist=%g, angle=%g, result=%g,%g,%g",
						i, center->x, center->y, center->z, dist, startAngle + angleSpacing * i,
						result->x, result->y, result->z );
				return TRUE;
			}

			if (i != 0)
			{
				if (Rva00284AC6TryPosition( center, dist, startAngle - angleSpacing * i, options, result ))
				{
					if (DOCKING_TRACE)
						bfmeRetailCritterDesyncLog( theLogicRandomLogFile,
							"    TryPosition2 succeeds - i=%d, center=%g,%g,%g, dist=%g, angle=%g, result=%g,%g,%g",
							i, center->x, center->y, center->z, dist, startAngle + angleSpacing * i,
							result->x, result->y, result->z );
					return TRUE;
				}
			}

			if (DOCKING_TRACE)
				bfmeRetailCritterDesyncLog( theLogicRandomLogFile,
					"    TryPosition1&2 both failed - i=%d, center=%g,%g,%g, dist=%g, angle=%g",
					i, center->x, center->y, center->z, dist, startAngle + angleSpacing * i );
		}
	}

	if (DOCKING_TRACE)
		bfmeRetailCritterDesyncLog( theLogicRandomLogFile,
			"    TerrainLogic::FindPositionAround() total failure, return FALSE" );

	return FALSE;
}





