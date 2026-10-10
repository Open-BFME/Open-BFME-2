// ?getPortTransform@BuildAssistant@@QAE_NPBUCoord3D@@PBVThingTemplate@@MPAMPAU2@@Z
// partial score=0.9794245907349355 date=2026-10-10
// cl: /O1 /EHs /MD /arch:SSE /I.
// Standalone trial view; import getPortTransform and the two visible owned Coord3D
// helpers into current Common/System/BuildAssistant.cpp for production.
#include <math.h>
#include "Code/Libraries/Include/Lib/Coord3D.h"
typedef float Real;typedef bool Bool;typedef int Int;
#define FALSE false
#define TRUE true
#define NULL 0
#define PI 3.14159265359f
class ThingTemplate;
struct Region3D {Coord3D lo,hi;};
class BuildAssistant {public:Bool getPortTransform(const Coord3D*,const ThingTemplate*,Real,Real*,Coord3D*);void iterateFootprint(const ThingTemplate*,Real,const Coord3D*,Real,void(*)(const Coord3D*,void*),void*);};
class TerrainLogic
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04(); virtual void t05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;	// +0x18
	virtual void t07();
	virtual void getExtent(Region3D *extent) const;		// +0x20
	virtual void t09(); virtual void t10(); virtual void t11();
	virtual void getMaximumPathfindExtent(Region3D *extent) const;	// +0x30
	virtual void t13(); virtual void t14(); virtual void t15();
	virtual void t16(); virtual void t17(); virtual void t18();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ = NULL, Real *terrainZ = NULL, Int unused = 0);	// +0x4C
};
extern TerrainLogic *TheTerrainLogic;
struct SampleBuildData
{
	const ThingTemplate *build;		// +0x00
	Bool requireWaterOrLand;		// +0x04
	Region3D mapRegion;			// +0x08
	Bool terrainRestricted;			// +0x20
	Real hiZ;				// +0x24
	Real loZ;				// +0x28
	Real waterSamples;			// +0x2C
	Real landSamples;			// +0x30
	Coord3D waterSum;			// +0x34
	Coord3D landSum;			// +0x40
	Int playerIndex;			// +0x4C
};

inline void addCoord3D( Coord3D *sum, const Coord3D *a )
{
	sum->x += a->x;
	sum->y += a->y;
	sum->z += a->z;
}


void checkSampleBuildLocation(const Coord3D*,void*);
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


inline __declspec(noinline) float Coord3D::length()const {return (float)sqrt(x*x+y*y+z*z);}
inline __declspec(noinline) void Coord3D::normalize(){float len=length();if(len!=0.0f){float s=1.0f/len;x*=s;y*=s;z*=s;}}
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

