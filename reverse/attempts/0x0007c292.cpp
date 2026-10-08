// ??0PlaneClass@@QAE@ABVVector3@@00@Z
// partial score=1.0 date=2026-10-08
// cl: /Ireference/shims/meshgeom /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z @0x0027EEAD 348B
// Evidence: BFME1 donor BridgeIsPointOnBridge.cpp and TerrainLogic.cpp Bridge::isPointOnBridge plus Bridge::pickBridge caller 0x0027FBFE; bounds at +0xB4 extra at +0xC8; unblocks 8 callers.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../../reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/plane.h"

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

class Bridge
{
public:
	bool isPointOnBridge(const Coord3D *point);
	bool pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);

private:
	char m_pad00[0x28];
	Coord3D m_fromLeft;
	Coord3D m_fromRight;
	Coord3D m_toLeft;
	Coord3D m_toRight;
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

// Whole readable BFME1 TerrainLogic.cpp donor at 34f59164f6d1efd413c5fd37f4894ec834c3c0fe.
// The same Bridge receiver and corner offsets are independently used by
// rowed isPointOnBridge; native 300B entry 0x0027FBFE calls the actual three-point
// PlaneClass::Set at 0x0007BFC2 and Compute_Intersection at 0x00069168,
// then isPointOnBridge at 0x0027EEAD.
// The donor supplies the ray/plane intersection algorithm and method name.
bool Bridge::pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos)
{
	Vector3 left1(m_fromLeft.x, m_fromLeft.y, m_fromLeft.z);
	Vector3 right1(m_fromRight.x, m_fromRight.y, m_fromRight.z);
	Vector3 left2(m_toLeft.x, m_toLeft.y, m_toLeft.z);
	PlaneClass plane(left1, right1, left2);
	float t;
	plane.Compute_Intersection(from, to, &t);
	Vector3 intersectPos;
	intersectPos = from + (to-from) * t;
	Coord3D loc;
	loc.x = intersectPos.X;
	loc.y = intersectPos.Y;
	loc.z = intersectPos.Z;
	if (isPointOnBridge(&loc)) {
		*pos = intersectPos;
		return true;
	}
	return false;
}
