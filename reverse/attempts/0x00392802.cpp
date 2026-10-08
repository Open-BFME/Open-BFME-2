// ?getPortTransform@BuildAssistant@@QAE_NPBUCoord3D@@PBVThingTemplate@@MPAMPAU2@@Z
// partial score=0.96 date=2026-10-08
// Banked candidate for BuildAssistant::getPortTransform (0x00392802, 725 bytes), 717 bytes compiled.
// Insert into Code/GameEngine/Source/Common/System/BuildAssistant.cpp: declare in class BuildAssistant
//   Bool getPortTransform(const Coord3D *worldPos, const ThingTemplate *build, Real angle, Real *outAngle, Coord3D *outPos);
// and place this after the s_maxWaterLandSampleRatio block (s_portAngleOffset must be defined just
// before s_maxWaterLandSampleRatio: retail .data 0xDC0854 = 0x3FC90FDB, then 6.0f at 0xDC0858).
// The comparisons use !(x > 0.0f) to match retail's comiss reg,0 / jbe form.

static Real s_portAngleOffset = PI / 2;

double __cdecl Rva000422A0Atan2( float y, float x );

inline void subCoord3D( Coord3D *diff, const Coord3D *a )
{
	diff->x -= a->x;
	diff->y -= a->y;
	diff->z -= a->z;
}

inline void scaleCoord3D( Coord3D *c, Real scale )
{
	c->x *= scale;
	c->y *= scale;
	c->z *= scale;
}

inline void divideCoord3D( Coord3D *c, Real divisor )
{
	Real inv = 1.0f / divisor;
	c->x *= inv;
	c->y *= inv;
	c->z *= inv;
}

Bool BuildAssistant::getPortTransform( const Coord3D *worldPos, const ThingTemplate *build,
																			 Real angle, Real *outAngle, Coord3D *outPos )
{
	Region3D terrainExtent;
	TheTerrainLogic->getExtent( &terrainExtent );

	SampleBuildData sampleData;
	TheTerrainLogic->getExtent( &sampleData.mapRegion );
	sampleData.build = build;
	sampleData.requireWaterOrLand = FALSE;
	sampleData.waterSamples = 0.0f;
	sampleData.landSamples = 0.0f;
	sampleData.landSum.x = 0.0f;
	sampleData.landSum.y = 0.0f;
	sampleData.landSum.z = 0.0f;
	sampleData.waterSum.x = 0.0f;
	sampleData.waterSum.y = 0.0f;
	sampleData.waterSum.z = 0.0f;
	sampleData.hiZ = terrainExtent.lo.z;
	sampleData.loZ = terrainExtent.hi.z;
	sampleData.terrainRestricted = FALSE;
	sampleData.playerIndex = -1;
	iterateFootprint( build, angle, worldPos, MAP_XY_FACTOR, checkSampleBuildLocation, &sampleData );

	if( sampleData.terrainRestricted || !(sampleData.landSamples > 0.0f) || !(sampleData.waterSamples > 0.0f) )
		return FALSE;

	// MISMATCH: retail loads landSum.xyz into registers and multiplies by the reciprocal
	// register (7 xmm live); ours folds mulss [mem] into a copied reciprocal (8 bytes short).
	divideCoord3D( &sampleData.landSum, sampleData.landSamples );
	divideCoord3D( &sampleData.waterSum, sampleData.waterSamples );

	Coord3D dir;
	dir.x = sampleData.waterSum.x - sampleData.landSum.x;
	dir.y = sampleData.waterSum.y - sampleData.landSum.y;
	dir.z = sampleData.waterSum.z - sampleData.landSum.z;
	Real dist = dir.length();
	dir.normalize();
	scaleCoord3D( &dir, 5.0f );

	*outPos = sampleData.landSum;
	for( Real t = 0.0f; t < dist; t += 5.0f )
	{
		if( TheTerrainLogic->isUnderwater( outPos->x, outPos->y ) )
		{
			dir.normalize();
			// MISMATCH: retail does not store the scaled dir.z here (dead), ours does.
			scaleCoord3D( &dir, 10.0f );
			subCoord3D( outPos, &dir );
			outPos->z = TheTerrainLogic->getGroundHeight( outPos->x, outPos->y );
			break;
		}
		addCoord3D( outPos, &dir );
	}

	*outAngle = Rva000422A0Atan2( dir.y, dir.x );
	*outAngle += s_portAngleOffset;
	return TRUE;

}  // end getPortTransform
