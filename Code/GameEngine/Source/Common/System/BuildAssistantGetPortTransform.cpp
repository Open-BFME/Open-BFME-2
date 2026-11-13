// cl: /O1 /EHs /MD /arch:SSE
// platformsdk
// BuildAssistantGetPortTransform.cpp -- BuildAssistant::getPortTransform (retail 0x00392802,
// 725 bytes), the naval port placement BFME2 added to BuildAssistant.cpp.
//
// Identity (target evidence): WB F9B980 is BuildAssistant::getPortTransform, its
// assert at BuildAssistant.cpp:2124; native 0x00392802..0x00392AD7 (ret 0x14); called by
// InGameUI::handleBuildPlacements and PlaceEventTranslator. No Zero Hour analogue.
// WB's body supplies the statement shape: one footprint sample pass through
// iterateFootprint/checkSampleBuildLocation into a SampleBuildData, the success path in
// an `if( ok && landSamples > 0 && waterSamples > 0 ) { ... return TRUE; } return FALSE;`,
// the averaged sums as MathCoord3D.h's operator/= (WB 0x41FA20), `dir` copied from the
// water centre and operator-= the land centre, length() then normalize(), a 5-unit
// `step` local scaled in with operator*=, the shore walk with operator+= / operator-=, and
// the facing from atan2 plus PI/2 (one expression here, see the end of the body).
//
// Why this is its own unit: retail compiled the body in BuildAssistant.cpp (its PI/2
// offset 0x00DC0854 sits directly before that unit's s_maxWaterLandSampleRatio at
// 0x00DC0858), but its bytes need the non-POD Coord3D (Lib/Coord3DCtorView.h): the
// user copy constructor makes `outPos->add( dir )` a struct temporary, which is what puts
// retail's `outPos->z + dir.z` term order in the loop, and plain POD copies of `dir`
// grow the body to 746-758 bytes. In BuildAssistant.cpp that header moves
// iterateFootprint 0x003916AB to 674/676 (any user constructor on its local `pos` changes
// the loop-tail register reload), so the view is confined to this unit. The callback and
// the angle offset therefore have external linkage in BuildAssistant.cpp.
//
// Two source levers recovered from the bytes (not from WB, which is a debug build):
// - sampleData is filled and read through a pointer local (`data`). cl decides whether a
//   sum component is folded into mulss as a memory operand by how that field was
//   addressed when it was initialised: through `data->` the land components and the
//   water y/z are loaded and multiplied by the reciprocal register (retail's loads of
//   landSum.y/.z ahead of the divide), while the water sum zeroed directly through
//   `sampleData` keeps retail's single folded `mulss xmm, [waterSum.x]`.
// - Coord3D::length/normalize must be visible (inline, not inlined): their retail bodies
//   (coord3d.cpp rows 0x00003571 / 0x000035B6, called out of line here as in retail) let
//   cl drop the dead dir.z store across the isUnderwater call.

#include <math.h>
#define COORD3D_VIEW_INLINE
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"
#include "../../../../Libraries/Include/Lib/Region3D.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

#include <windows.h>
#define MAP_XY_FACTOR (10.0f)

class ThingTemplate;

// The virtual slots this body calls (BuildAssistant.cpp's TerrainLogic view).
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

#include "../../../Include/Common/BuildAssistantClass.h"

// BuildAssistant.cpp's sample context (0x50 bytes, isLocationLegalToBuild's frame at ebp-0x74).
#include "../../../Include/Common/SampleBuildData.h"

// BuildAssistant.cpp: the footprint sample callback (0x003925CA) and the PI/2 facing
// offset (.data 0x00DC0854).
void checkSampleBuildLocation( const Coord3D *samplePoint, void *userData );
extern Real s_portAngleOffset;

// math.h's float atan2 adapter (0x000422A0).
double __cdecl Rva000422A0Atan2( float y, float x );

// Coord3D::length (0x00003571) and Coord3D::normalize (0x000035B6), visible to the
// optimizer but kept out of line as retail calls them; byte-identical to coord3d.cpp's rows.
inline __declspec(noinline) float Coord3D::length() const
{
	return (float)sqrt(x * x + y * y + z * z);
}

inline __declspec(noinline) void Coord3D::normalize()
{
	float len = length();
	if (len != 0.0f) {
		float scale = 1.0f / len;
		x *= scale;
		y *= scale;
		z *= scale;
	}
}

//-------------------------------------------------------------------------------------------------
/** Find where a port straddling the shore at worldPos should sit: the land and water sample
	* centres of its footprint give the shore direction; walk from the land centre toward the
	* water until underwater, back off two steps and snap to the ground. outAngle faces the
	* water. Returns FALSE unless the footprint has both land and water samples and no
	* restricted cell. */
//-------------------------------------------------------------------------------------------------
Bool BuildAssistant::getPortTransform( const Coord3D *worldPos, const ThingTemplate *build,
																			 Real angle, Real *outAngle, Coord3D *outPos )
{
	Region3D terrainExtent;
	TheTerrainLogic->getExtent( &terrainExtent );

	SampleBuildData sampleData;
	SampleBuildData *data = &sampleData;
	TheTerrainLogic->getExtent( &data->mapRegion );
	data->build = build;
	data->requireWaterOrLand = FALSE;
	data->waterSamples = 0.0f;
	data->landSamples = 0.0f;
	data->landSum.zero();
	sampleData.waterSum.zero();
	data->hiZ = terrainExtent.lo.z;
	data->loZ = terrainExtent.hi.z;
	data->terrainRestricted = FALSE;
	data->playerIndex = -1;
	iterateFootprint( build, angle, worldPos, MAP_XY_FACTOR, checkSampleBuildLocation, data );

	if( !data->terrainRestricted && data->landSamples > 0.0f && data->waterSamples > 0.0f )
	{
		data->landSum /= data->landSamples;
		data->waterSum /= data->waterSamples;
		Coord3D dir = data->waterSum;
		dir -= data->landSum;
		Real dist = dir.length();
		dir.normalize();
		Real step = 5.0f;
		dir *= step;

		*outPos = data->landSum;
		for( Real t = 0.0f; t < dist; t += step )
		{
			if( TheTerrainLogic->isUnderwater( outPos->x, outPos->y ) )
			{
				dir.normalize();
				dir *= 10.0f;
				*outPos -= dir;
				outPos->z = TheTerrainLogic->getGroundHeight( outPos->x, outPos->y );
				break;
			}
			outPos->add( dir );
		}

		// One expression: WB stores atan2 and then adds the offset, but with the offset now an
		// extern global, a separate `*outAngle +=` would make cl assume the store may alias it.
		*outAngle = Rva000422A0Atan2( dir.y, dir.x ) + s_portAngleOffset;
		return TRUE;
	}
	return FALSE;

}  // end getPortTransform
