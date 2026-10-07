// ?isCellOnSide@Bridge@@QAE_NPBURegion2D@@@Z
// partial score=0.96 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /ICode/Libraries/Include/Lib /Ireference/shims/meshgeom /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z @0x0027EEAD 348B
// Evidence: BFME1 donor BridgeIsPointOnBridge.cpp and TerrainLogic.cpp Bridge::isPointOnBridge plus Bridge::pickBridge caller 0x0027FBFE; bounds at +0xB4 extra at +0xC8; unblocks 8 callers.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "Coord3D.h"
#include "Coord2D.h"

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region2D
{
	float loX;
	float loY;
	float hiX;
	float hiY;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class ICoord3D
{
public:
	int x;
	int y;
	int z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	bool pointInTrigger(const ICoord3D &point);
};

bool Point_In_Triangle_2D(const Vector3 &tri_point0, const Vector3 &tri_point1,
	const Vector3 &tri_point2, const Vector3 &test_point, int axis_1, int axis_2,
	unsigned char &flags);

static inline unsigned char Point_In_Triangle_2D_byte(const Vector3 &tri_point0,
	const Vector3 &tri_point1, const Vector3 &tri_point2, const Vector3 &test_point,
	int axis_1, int axis_2, unsigned char &flags)
{
	return Point_In_Triangle_2D(tri_point0, tri_point1, tri_point2, test_point,
		axis_1, axis_2, flags) ? 1 : 0;
}

#include <math.h>
inline void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale; y *= scale; z *= scale;
    }
}

struct BridgeSideVector
{
	float x;
	float y;
	float z;

	BridgeSideVector(void) {}
	BridgeSideVector(const BridgeSideVector &that) : x(that.x), y(that.y) {}
	__forceinline void normalize() { reinterpret_cast<Coord3D *>(this)->normalize(); }


};

class Bridge
{
public:
	bool isPointOnBridge(const Coord3D *point);
	bool isCellOnSide(const Region2D *cell);

private:
	char m_pad00[0x28];
	BridgeSideVector m_fromLeft;
	BridgeSideVector m_fromRight;
	BridgeSideVector m_toLeft;
	BridgeSideVector m_toRight;
	char m_pad58[0xB4 - 0x58];
	Region2D m_bounds;
	int m_layer;
	PolygonTrigger *m_extra;
};

bool Bridge::isPointOnBridge(const Coord3D *point)
{
	if (point->x < m_bounds.loX)
		return false;
	if (point->x > m_bounds.hiX)
		return false;
	if (point->y < m_bounds.loY)
		return false;
	if (point->y > m_bounds.hiY)
		return false;

	PolygonTrigger *extra = m_extra;
	if (extra)
	{
		ICoord3D ic;
		ic.x = (int)point->x;
		ic.y = (int)point->y;
		ic.z = (int)point->z;
		return extra->pointInTrigger(ic);
	}
	else
	{
		Vector3 testPt;
		testPt.X = point->x;
		testPt.Y = point->y;
		testPt.Z = point->z;
		Vector3 fromLeft;
		fromLeft.X = m_fromLeft.x;
		fromLeft.Y = m_fromLeft.y;
		fromLeft.Z = m_fromLeft.z;
		Vector3 fromRight;
		fromRight.X = m_fromRight.x;
		fromRight.Y = m_fromRight.y;
		fromRight.Z = m_fromRight.z;
		Vector3 toLeft;
		toLeft.X = m_toLeft.x;
		toLeft.Y = m_toLeft.y;
		toLeft.Z = m_toLeft.z;
		Vector3 toRight;
		toRight.X = m_toRight.x;
		toRight.Y = m_toRight.y;
		toRight.Z = m_toRight.z;

		unsigned char flags;
		if (Point_In_Triangle_2D(fromLeft, fromRight, toLeft, testPt, 0, 1, flags))
			return true;
		return Point_In_Triangle_2D_byte(fromRight, toLeft, toRight, testPt, 0, 1, flags);
	}
}

// Donor: Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/GameLogic/Map/Bridge_isCellOnSide_Thunk.cpp.
// Target layout is independently supported by the existing isPointOnBridge:
// four endpoints +0x28/+0x34/+0x40/+0x4c. Native side checks call the rowed
// LineInRegion at 0x27C4F4. This local temporary copies only x/y, as consumed
// by the side segments; endVector explicitly initializes x/y/z before length.
// Canonical coordinate headers retain their native layouts. The helper's
// non-POD temporary shape is local and does not redefine the canonical type.
#include <math.h>
typedef float Real;
bool LineInRegion(const Coord2D *, const Coord2D *, const Region2D *);
bool Bridge::isCellOnSide(const Region2D *cell)
{
	BridgeSideVector endVector;
	endVector.x = m_fromRight.x - m_fromLeft.x;
	endVector.y = m_fromRight.y - m_fromLeft.y;
	endVector.z = m_fromRight.z - m_fromLeft.z;
	endVector.normalize();
	endVector.x *= 5.1f;
	endVector.y *= 5.1f;

	BridgeSideVector fromLeft = m_fromLeft;
	fromLeft.x -= endVector.x;
	fromLeft.y -= endVector.y;

	BridgeSideVector fromRight = m_fromRight;
	fromRight.x += endVector.x;
	fromRight.y += endVector.y;

	BridgeSideVector toLeft = m_toLeft;
	toLeft.x -= endVector.x;
	toLeft.y -= endVector.y;

	BridgeSideVector toRight = m_toRight;
	toRight.x += endVector.x;
	toRight.y += endVector.y;

	Coord2D sideStart, sideEnd;
	sideStart.x = fromLeft.x;
	sideStart.y = fromLeft.y;
	sideEnd.x = toLeft.x;
	sideEnd.y = toLeft.y;
	if (LineInRegion(&sideStart, &sideEnd, cell))
		return true;

	sideStart.x = fromRight.x;
	sideStart.y = fromRight.y;
	sideEnd.x = toRight.x;
	sideEnd.y = toRight.y;
	if (LineInRegion(&sideStart, &sideEnd, cell))
		return true;

	fromLeft.x -= endVector.x;
	fromLeft.y -= endVector.y;
	fromRight.x += endVector.x;
	fromRight.y += endVector.y;
	toLeft.x -= endVector.x;
	toLeft.y -= endVector.y;
	toRight.x += endVector.x;
	toRight.y += endVector.y;

	sideStart.x = fromLeft.x;
	sideStart.y = fromLeft.y;
	sideEnd.x = toLeft.x;
	sideEnd.y = toLeft.y;
	if (LineInRegion(&sideStart, &sideEnd, cell))
		return true;

	sideStart.x = fromRight.x;
	sideStart.y = fromRight.y;
	sideEnd.x = toRight.x;
	sideEnd.y = toRight.y;
	if (LineInRegion(&sideStart, &sideEnd, cell))
		return true;

	return false;
}
