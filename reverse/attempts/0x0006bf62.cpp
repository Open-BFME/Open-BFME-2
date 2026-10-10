// ?Cast_Ray@BaseHeightMapRenderObjClass@@UAE_NAAVRayCollisionTestClass@@@Z
// partial score=0.8 date=2026-10-10
// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc    /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// ?Cast_Ray@BaseHeightMapRenderObjClass@@UAE_NAAVRayCollisionTestClass@@@Z, retail
// 0x0006BF62..0x0006C69F. Zero Hour's BaseHeightMapRenderObjClass::Cast_Ray
// (BaseHeightMap.cpp) with BFME2's constants: the pick box overhangs the map
// by 64 cells plus the border, heights are 16-bit (max 65535) scaled by
// 10/256, and the clipped ray's cell box is scanned for the height range
// before the per-cell triangle tests.

#include "always.h"
#include <math.h>
#include <wwmath.h>
#include <colmath.h>
#include <coltest.h>
#include <tri.h>
#include <aabox.h>
#include <lineseg.h>
#include <vector3.h>
#include <w3d_file.h>

#define MAP_XY_FACTOR 10.0f
#define MAP_HEIGHT_SCALE (MAP_XY_FACTOR / 256.0f)
#define ADJUST_FROM_INDEX_TO_REAL(k) ((k) * MAP_XY_FACTOR)

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef short Short;

static inline Real bfmeFloorD(Real f) { double d = floor(f); return (Real)d; }
static inline Real bfmeCeilD(Real f) { double d = ceil(f); return (Real)d; }
#define REAL_TO_INT_FLOOR(x) WWMath::Float_To_Long(bfmeFloorD(x))
#define REAL_TO_INT_CEIL(x) WWMath::Float_To_Long(bfmeCeilD(x))

class Rva0006653B
{
public:
	unsigned short rva0006653B(int x, int y);
	char m_pad00[8];
	Int m_xExtent;
	Int m_yExtent;
	Int m_border;
};

class BaseHeightMapRenderObjClass
{
public:
	virtual bool Cast_Ray(RayCollisionTestClass &raytest);

private:
	char m_pad04[0x37C0 - 4];
	Rva0006653B *m_map;	// +0x37C0
};

bool BaseHeightMapRenderObjClass::Cast_Ray(RayCollisionTestClass &raytest)
{
	TriClass tri;
	Bool hit = false;
	Int X,Y;
	Vector3 normal,P0,P1,P2,P3;

	if (!m_map)
		return false;	//need valid pointer to heightmap samples
	//Clip ray to extents of heightfield
	AABoxClass hbox;
	LineSegClass lineseg,lineseg2;
	CastResultStruct	result;
	Int StartCellX = 0;
	Int EndCellX = 0;
 	Int StartCellY = 0;
	Int EndCellY = 0;
	const Int overhang = 2*32+m_map->m_border; // Allow picking past the edge for scrolling & objects.
 	Vector3 minPt(MAP_XY_FACTOR*(-overhang), MAP_XY_FACTOR*(-overhang), -MAP_XY_FACTOR);
	Vector3 maxPt(MAP_XY_FACTOR*(m_map->m_xExtent+overhang), 
		MAP_XY_FACTOR*(m_map->m_yExtent+overhang), MAP_HEIGHT_SCALE*65535+MAP_XY_FACTOR);
	MinMaxAABoxClass mmbox(minPt, maxPt);
	hbox.Init(mmbox);

	lineseg=raytest.Ray;

	//Set initial ray endpoints
	P0 = raytest.Ray.Get_P0();
	P1 = raytest.Ray.Get_P1();
	result.ComputeContactPoint=true;

	Int p;
	for (p=0; p<3; p++) {
		//find intersection point of ray and terrain bounding box
		result.Reset();
		result.ComputeContactPoint=true;
		if (CollisionMath::Collide(lineseg,hbox,&result))
		{	//ray intersects terrain or starts inside the terrain.
			if (!result.StartBad)	//check if start point inside terrain
				P0 = result.ContactPoint;			//make intersection point the new start of the ray.

			//reverse direction of original ray and clip again to extent of
			//heightmap
			result.Fraction=1.0f;	//reset the result
			result.StartBad=false;
			lineseg2.Set(lineseg.Get_P1(),lineseg.Get_P0());	//reverse line segment
			if (CollisionMath::Collide(lineseg2,hbox,&result))
			{	if (!result.StartBad)	//check if end point inside terrain
					P1 = result.ContactPoint;	//make intersection point the new end pont of ray
			}
		} else {
			if (p==0) return(false);
			break;
		}

		// Take the 2D bounding box of ray and check heights
		// inside this box for intersection.
		if (P0.X > P1.X) {	//flip start/end points
			StartCellX = REAL_TO_INT_FLOOR(P1.X*(1.0f/MAP_XY_FACTOR));
			EndCellX = REAL_TO_INT_CEIL(P0.X*(1.0f/MAP_XY_FACTOR));
		}	else {
			StartCellX = REAL_TO_INT_FLOOR(P0.X*(1.0f/MAP_XY_FACTOR));
			EndCellX = REAL_TO_INT_CEIL(P1.X*(1.0f/MAP_XY_FACTOR));
		}
		if (P0.Y > P1.Y) {	//flip start/end points
			StartCellY = REAL_TO_INT_FLOOR(P1.Y*(1.0f/MAP_XY_FACTOR));
			EndCellY = REAL_TO_INT_CEIL(P0.Y*(1.0f/MAP_XY_FACTOR));
		}	else {
			StartCellY = REAL_TO_INT_FLOOR(P0.Y*(1.0f/MAP_XY_FACTOR));
			EndCellY = REAL_TO_INT_CEIL(P1.Y*(1.0f/MAP_XY_FACTOR));
		}

		Int i, j, minHt, maxHt;

		minHt = 65535;
		maxHt = 0;

		for (j=StartCellY; j<=EndCellY; j++) {
			for (i=StartCellX; i<=EndCellX; i++) {
				Short cur = m_map->rva0006653B(i+m_map->m_border,j+m_map->m_border);
				if (cur<minHt) minHt = cur;
				if (maxHt<cur) maxHt = cur;
			}
		}
		Vector3 minPt(MAP_XY_FACTOR*(StartCellX-1), MAP_XY_FACTOR*(StartCellY-1), MAP_HEIGHT_SCALE*(minHt-1));
		Vector3 maxPt(MAP_XY_FACTOR*(EndCellX+1), MAP_XY_FACTOR*(EndCellY+1), MAP_HEIGHT_SCALE*(maxHt+1));
		MinMaxAABoxClass mmbox(minPt, maxPt);
		hbox.Init(mmbox);
	}

	raytest.Result->ComputeContactPoint=true;	//tell CollisionMath that we need point.

	// Adjust indexes into the bordered height map.

	StartCellX += m_map->m_border;
	EndCellX += m_map->m_border;
	StartCellY += m_map->m_border;
	EndCellY += m_map->m_border;

	Int offset;
	for (offset = 1; offset < 5; offset *= 3) {
		for (Y=StartCellY-offset; Y<=EndCellY+offset; Y++) { 

			for (X=StartCellX-offset; X<=EndCellX+offset; X++) {
				//bottom triangle first
				P0.X=ADJUST_FROM_INDEX_TO_REAL(X);
				P0.Y=ADJUST_FROM_INDEX_TO_REAL(Y);
				P0.Z=MAP_HEIGHT_SCALE*(float)m_map->rva0006653B(X, Y);

				P1.X=ADJUST_FROM_INDEX_TO_REAL(X+1);
				P1.Y=ADJUST_FROM_INDEX_TO_REAL(Y);
				P1.Z=MAP_HEIGHT_SCALE*(float)m_map->rva0006653B(X+1, Y);

				P2.X=ADJUST_FROM_INDEX_TO_REAL(X+1);
				P2.Y=ADJUST_FROM_INDEX_TO_REAL(Y+1);
				P2.Z=MAP_HEIGHT_SCALE*(float)m_map->rva0006653B(X+1, Y+1);

				P3.X=ADJUST_FROM_INDEX_TO_REAL(X);
				P3.Y=ADJUST_FROM_INDEX_TO_REAL(Y+1);
				P3.Z=MAP_HEIGHT_SCALE*(float)m_map->rva0006653B(X, Y+1);

				tri.V[0] = &P0; 
				tri.V[1] = &P1;
				tri.V[2] = &P2;
				
				tri.N = &normal;

				tri.Compute_Normal();

				hit = hit || (Bool)CollisionMath::Collide(raytest.Ray, tri, raytest.Result);

				if (raytest.Result->StartBad)
					return true;

				//top triangle
				tri.V[0] = &P2; 
				tri.V[1] = &P3;
				tri.V[2] = &P0;
				
				tri.N = &normal;

				tri.Compute_Normal();

				hit = hit || (Bool)CollisionMath::Collide(raytest.Ray, tri, raytest.Result);

				if (hit)
					raytest.Result->SurfaceType = SURFACE_TYPE_DEFAULT;
			}
		}
	}
	return hit;
}
