// ?getPortTransform@BuildAssistant@@QAE_NPBUCoord3D@@PBVThingTemplate@@MPAMPAU2@@Z
// partial score=0.96 date=2026-10-09
// Bank fragment: insert after checkSampleBuildLocation in current BuildAssistant.cpp.
// Shared declarations, target layout and original source provenance are in that home TU.
#define MAP_XY_FACTOR (10.0f)

// The largest water to land sample ratio (either way) a KINDOF_188 build may
// straddle. Retail reads it from this unit's .data, not as a literal.
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
{Real inv=1.0f/sampleData.landSamples;
sampleData.landSum.x=*(const volatile Real*)&sampleData.landSum.x*inv;
sampleData.landSum.y=*(const volatile Real*)&sampleData.landSum.y*inv;
sampleData.landSum.z=*(const volatile Real*)&sampleData.landSum.z*inv;
}
{Real inv=1.0f/sampleData.waterSamples;
sampleData.waterSum.x=sampleData.waterSum.x*inv;
sampleData.waterSum.y=*(const volatile Real*)&sampleData.waterSum.y*inv;
sampleData.waterSum.z=*(const volatile Real*)&sampleData.waterSum.z*inv;
}
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

