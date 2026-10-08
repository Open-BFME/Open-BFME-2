// ?iterateFootprint@BuildAssistant@@QAEXPBVThingTemplate@@MPBUCoord3D@@MP6AX1PAX@Z2@Z
// partial score=0.99 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /O1 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <list>
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;

class Coord2D { public: float x; float y; Real length() const; };

class BfmeThingTemplateShadowSelector
{
public:
	Bool usePluralShadowName() const;
};

class GeometryInfo
{
public:
	Real getMajorRadius() const { return m_majorRadius; }
	Real getBoxMajorRadius() const { return m_boxMajorRadius; }
	Real getBoxMinorRadius() const { return m_boxMinorRadius; }
	Bool isSingleBox() const { return ((const BfmeThingTemplateShadowSelector *)this)->usePluralShadowName(); }

private:
	unsigned char m_pad00[0x10];
	Real m_majorRadius;		// +0x10
	Real m_boundingCircleRadius;	// +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Real m_boxMajorRadius;		// +0x24
	Real m_boxMinorRadius;		// +0x28
};

class ThingTemplate
{
public:
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
private:
	unsigned char m_pad000[0xA0];
	GeometryInfo m_geometryInfo;	// +0xA0
};

class TerrainLogic
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04(); virtual void t05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;	// +0x18
};
extern TerrainLogic *TheTerrainLogic;

typedef void (*IterateFootprintFunc)( const Coord3D *samplePoint, void *userData );

class BuildAssistant
{
public:
	virtual void slot00();
	void iterateFootprint( const ThingTemplate *build, Real buildOrientation, const Coord3D *worldPos,
		Real sampleResolution, IterateFootprintFunc func, void *funcUserData );
};

void BuildAssistant::iterateFootprint( const ThingTemplate *build,
																			 Real buildOrientation,
																			 const Coord3D *worldPos,
																			 Real sampleResolution,
																			 IterateFootprintFunc func,
																			 void *funcUserData )
{

	// sanity
	if( build == NULL || worldPos == NULL || func == NULL )
		return;

	Matrix3D transform;
	transform.Make_Identity();
	transform.Adjust_Translation( Vector3( worldPos->x, worldPos->y, worldPos->z ) );
	transform.Rotate_Z( buildOrientation );

	// get the bounding footprint rectangle for the geometry we're looking at
	Real halfFootprintHeight,
			 halfFootprintWidth;
	if( build->getTemplateGeometryInfo().isSingleBox() )
	{
		halfFootprintHeight = build->getTemplateGeometryInfo().getBoxMinorRadius();
		halfFootprintWidth = build->getTemplateGeometryInfo().getBoxMajorRadius();
	}
	else
	{
		halfFootprintHeight = build->getTemplateGeometryInfo().getMajorRadius();
		halfFootprintWidth = build->getTemplateGeometryInfo().getMajorRadius();
	}

	Real x, y;
	Vector3 v;
	for( y = -halfFootprintHeight;
			 y < halfFootprintHeight + sampleResolution;
			 y += sampleResolution )
	{

		// snap it to the actual extent since we can go over by one sample resolution
		if( y > halfFootprintHeight )
			y = halfFootprintHeight;

		for( x = -halfFootprintWidth;
				 x < halfFootprintWidth + sampleResolution;
				 x += sampleResolution )
		{

			// snap it to the actual extent since we can go over by one sample resolution
			if( x > halfFootprintWidth )
				x = halfFootprintWidth;

			// transform to world
			v.Set( x, y, TheTerrainLogic->getGroundHeight( x, y ) );
			transform.Transform_Vector( transform, v, &v );

			// for circular geometries we must actually be within the circle
			if( !build->getTemplateGeometryInfo().isSingleBox() )
			{
				Coord2D vector;

				vector.x = v.X - worldPos->x;
				vector.y = v.Y - worldPos->y;
				if( vector.length() > halfFootprintWidth )  // could be height too, radius is all the same for circles
					continue;  // ignore this point

			}  // end if

			// call the user callback
			Real z = TheTerrainLogic->getGroundHeight( v.X, v.Y );
			Coord3D pos;
			pos.x = v.X;
			pos.y = v.Y;
			pos.z = z;
			func( &pos, funcUserData );

		}  // end for x

	}  // end for y

}  // end iterateFootprint
