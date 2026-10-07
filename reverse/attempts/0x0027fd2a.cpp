// ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z
// partial score=0.6 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z, retail 0x0027FD2A, 713 bytes.
// Identity: TerrainLogic::getHighestLayerForDestination (0x002803F9) calls it
// on each bridge the point is on (after the rowed Bridge::isPointOnBridge
// 0x0027EEAD) with (pos, NULL) and subtracts the result from pos->z, the Zero
// Hour TerrainLogic.cpp shape. Donor: Zero Hour Bridge::getBridgeHeight, kept
// as the second branch: a plane through fromLeft, fromRight and toLeft
// (PlaneClass::Set 0x0007BFC2), a vertical segment 0..1000 through the point
// (Compute_Intersection 0x00069168), the normal copied out when asked for.
// BFME 2 delta measured from retail: a bridge with the polygon area at +0xC8
// (the one isPointOnBridge tests instead of its triangles) blends the two end
// heights by the point's distance from each end edge, measured along the
// edges' unit inward normals (Coord3D::normalize 0x000035B6), and reports a
// straight-up normal.

#include "ascii_string.h"

typedef float Real;

// class-gate: allow Coord3D the canonical data-only header cannot declare BFME 2's out-of-line normalize (rowed 0x000035B6); same three floats
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void normalize();
};

class Vector3
{
public:
	Vector3() {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }

	Real X;
	Real Y;
	Real Z;
};

class PlaneClass
{
public:
	PlaneClass() {}
	PlaneClass(const Vector3 &point1, const Vector3 &point2, const Vector3 &point3) { Set(point1, point2, point3); }
	void Set(const Vector3 &point1, const Vector3 &point2, const Vector3 &point3);
	bool Compute_Intersection(const Vector3 &p0, const Vector3 &p1, Real *set_t) const;

	Vector3 N;
	Real D;
};

typedef int ObjectID;
enum BodyDamageType { BODY_PRISTINE, BODY_DAMAGED, BODY_REALLYDAMAGED, BODY_RUBBLE };

struct BridgeInfo
{
	Coord3D from;
	Coord3D to;
	Real bridgeWidth;
	Coord3D fromLeft;
	Coord3D fromRight;
	Coord3D toLeft;
	Coord3D toRight;
	int bridgeIndex;
	BodyDamageType curDamageState;
	ObjectID bridgeObjectID;
	ObjectID towerObjectID[4];
	bool damageStateChanged;
};

class PolygonTrigger;

class Bridge
{
public:
	virtual ~Bridge();
	Real getBridgeHeight(const Coord3D *pLoc, Coord3D *normal);

protected:
	Bridge *m_next; // +0x04
	AsciiString m_templateName; // +0x08
	BridgeInfo m_bridgeInfo; // +0x0C
	char m_pad78[0xC8 - 0x78];
	PolygonTrigger *m_area; // +0xC8
};

// ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z
Real Bridge::getBridgeHeight(const Coord3D *pLoc, Coord3D *normal)
{
	if (m_area)
	{
		Coord3D toNormal;
		toNormal.x = m_bridgeInfo.toRight.y - m_bridgeInfo.toLeft.y;
		toNormal.y = -(m_bridgeInfo.toRight.x - m_bridgeInfo.toLeft.x);
		toNormal.z = 0;
		Coord3D fromNormal;
		fromNormal.x = -(m_bridgeInfo.fromRight.y - m_bridgeInfo.fromLeft.y);
		fromNormal.y = m_bridgeInfo.fromRight.x - m_bridgeInfo.fromLeft.x;
		fromNormal.z = 0;
		Coord3D along = m_bridgeInfo.to;
		along.x -= m_bridgeInfo.from.x;
		along.y -= m_bridgeInfo.from.y;
		if (fromNormal.x * along.x + fromNormal.y * along.y < 0)
		{
			fromNormal.x *= -1.0f;
			fromNormal.y *= -1.0f;
			fromNormal.z *= -1.0f;
		}
		if (toNormal.x * along.x + toNormal.y * along.y > 0)
		{
			toNormal.x *= -1.0f;
			toNormal.y *= -1.0f;
			toNormal.z *= -1.0f;
		}
		fromNormal.normalize();
		toNormal.normalize();

		Real fromDist = (pLoc->x - m_bridgeInfo.from.x) * fromNormal.x + (pLoc->y - m_bridgeInfo.from.y) * fromNormal.y;
		Real toDist = (pLoc->x - m_bridgeInfo.to.x) * toNormal.x + (pLoc->y - m_bridgeInfo.to.y) * toNormal.y;
		Real scale = 1.0f / (toDist + fromDist);
		Real toFactor = scale * toDist;
		Real fromFactor = scale * fromDist;
		Real height = ((m_bridgeInfo.from.z - m_bridgeInfo.to.z) * toFactor + m_bridgeInfo.to.z) * (1.0f - toFactor)
			+ ((m_bridgeInfo.to.z - m_bridgeInfo.from.z) * fromFactor + m_bridgeInfo.from.z) * (1.0f - fromFactor);
		if (normal)
		{
			normal->x = normal->y = 0;
			normal->z = 1.0f;
		}
		return height;
	}

	else
	{
		PlaneClass plane;
		{
		Vector3 left1(m_bridgeInfo.fromLeft.x, m_bridgeInfo.fromLeft.y, m_bridgeInfo.fromLeft.z);
		Vector3 right1(m_bridgeInfo.fromRight.x, m_bridgeInfo.fromRight.y, m_bridgeInfo.fromRight.z);
		Vector3 left2(m_bridgeInfo.toLeft.x, m_bridgeInfo.toLeft.y, m_bridgeInfo.toLeft.z);
		plane.Set(left1, right1, left2);
		}
		{
		const Real factor = 1000.0f;
		Vector3 bottom(pLoc->x, pLoc->y, 0);
		Vector3 top(pLoc->x, pLoc->y, factor);
		Real t;
		plane.Compute_Intersection(bottom, top, &t);
		if (normal)
			*(Vector3 *)normal = plane.N;
		return t * factor;
		}
	}
}
