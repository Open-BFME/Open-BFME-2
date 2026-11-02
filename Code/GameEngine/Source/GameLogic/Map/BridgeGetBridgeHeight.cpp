// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z, retail 0x0027FD2A, 713 bytes.
// Identity: TerrainLogic::getHighestLayerForDestination (0x002803F9) calls it on each
// bridge the point is on (after Bridge::isPointOnBridge 0x0027EEAD) with (pos, NULL).
// Plane branch: Zero Hour TerrainLogic.cpp Bridge::getBridgeHeight, with the WorldBuilder
// twin's default-constructed plane and explicit PlaneClass::Set (0x0007BFC2), then
// Compute_Intersection (0x00069168). Polygon-area (+0xC8) branch: statements, locals and
// call order follow the WorldBuilder debug twin (WB va 0x00C43DD0, 1429 B): BFME 2
// MathCoord3D.h Coord3D with a member-wise copy constructor, an implicit (block-copy)
// assignment, a three-float constructor and inline Sub/Scale; normalize is the out-of-line
// Coord3D::normalize (0x000035B6). Coord3DCtorView.h supplies that non-POD Coord3D.

#include "ascii_string.h"

typedef float Real;

#define COORD3D_VIEW_INLINE
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"


class PlaneClass
{
public:
	__declspec(dllimport) __forceinline PlaneClass() {}	// inlined at its one use; no copy here
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

Real Bridge::getBridgeHeight(const Coord3D *pLoc, Coord3D *normal)
{
	if (m_area)
	{
		Coord3D along;
		along = m_bridgeInfo.to;
		along.sub(&m_bridgeInfo.from);
		Coord3D fromEdge = m_bridgeInfo.fromRight;
		fromEdge.sub(&m_bridgeInfo.fromLeft);
		Coord3D toEdge = m_bridgeInfo.toRight;
		toEdge.sub(&m_bridgeInfo.toLeft);
		Coord3D fromNormal(-fromEdge.y, fromEdge.x, 0);
		Coord3D toNormal(toEdge.y, -toEdge.x, 0);
		Real fromDot = along.x * fromNormal.x + along.y * fromNormal.y;
		if (fromDot < 0)
			fromNormal.scaleInlined(-1.0f);
		Real toDot = along.x * toNormal.x + along.y * toNormal.y;
		if (toDot > 0)
			toNormal.scaleInlined(-1.0f);
		fromNormal.normalize();
		toNormal.normalize();
		Coord3D fromDelta = *pLoc;
		fromDelta.sub(&m_bridgeInfo.from);
		Real fromDist = fromDelta.x * fromNormal.x + fromDelta.y * fromNormal.y;
		Coord3D toDelta = *pLoc;
		toDelta.sub(&m_bridgeInfo.to);
		Real toDist = toDelta.x * toNormal.x + toDelta.y * toNormal.y;
		Real total = fromDist + toDist;
		fromDist /= total;
		toDist /= total;
		Real fromHeight = (m_bridgeInfo.to.z - m_bridgeInfo.from.z) * fromDist + m_bridgeInfo.from.z;
		Real toHeight = (m_bridgeInfo.from.z - m_bridgeInfo.to.z) * toDist + m_bridgeInfo.to.z;
		Real height = (1.0f - fromDist) * fromHeight + (1.0f - toDist) * toHeight;
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
			// Both proven storage views are three floats; retain the existing Coord3D block copy.
			*normal = *(const Coord3D *)&plane.N;
		return t * factor;
		}
	}
}
