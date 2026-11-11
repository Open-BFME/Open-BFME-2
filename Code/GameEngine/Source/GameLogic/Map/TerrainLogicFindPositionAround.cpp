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

// platformsdk
#include <windows.h>
#define TWO_PI 6.28318530718f
#define RANDOM_START_ANGLE -99999.9f

#include "Lib/Coord3D.h"

#include "../../../../Libraries/Include/Lib/Region3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../Common/PartitionRangeQueryCallView.h"

// LINK: TU-local no-Z containment test (identical inlined bytes); the canonical
// Region3D::isInRegionNoZ's out-of-line copy loses to the first-in-link-order copy.
static inline Bool bfme_in_region_nz_findpos( const Region3D &region, const Coord3D *query )
{
	return (region.lo.x < query->x) && (query->x < region.hi.x) &&
		(region.lo.y < query->y) && (query->y < region.hi.y);
}

class Object;
struct FindPositionOptions
{
public:
	unsigned int flags; // +0x00
	Real minRadius; // +0x04
	Real maxRadius; // +0x08
	Real startAngle; // +0x0C
	Real maxZDelta; // +0x10
	const Object *ignoreObject; // +0x14
	const Object *sourceToPathToDest; // +0x18
	const Object *relationshipObject; // +0x1C
};

#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

extern GameLogic *TheGameLogic;

// <stdio.h> without dllimport: retail calls the game's own _fprintf thunk
// (0x002CEC42) through REL32, not the CRT stream import.
#define _CRTIMP
#include <stdio.h>
#undef _CRTIMP
extern "C" FILE *theLogicRandomLogFile;
extern bool g_bfmeDockingTraceActive;
#define bfmeRetailCritterDesyncLog fprintf

static Real ringSpacing = 5.0f;

Real GetGameLogicRandomValueReal( Real lo, Real hi, char *file, Int line );
Bool Rva00284AC6TryPosition( const Coord3D *center, Real dist, Real angle,
	const FindPositionOptions *options, Coord3D *result );

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define DOCKING_TRACE (g_bfmeDockingTraceActive && *(const Int *)((const char *)TheGameLogic + 0x1b4) > 0 && theLogicRandomLogFile)

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

	if (!bfme_in_region_nz_findpos( extent, center ))
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





