// ?getCenterPoint@Rva0030B719Shape@@QBE?AUCoord2D@@XZ
// partial score=0.8 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// PolygonTrigger::getCenterPoint and the center getters under it, after Zero
// Hour's GameEngine/Source/GameLogic/Map/PolygonTrigger.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference).
// BFME 2 moves Zero Hour's bounds, radius and bounds-dirty flag into a shape
// at PolygonTrigger +8 (target evidence: bounds lo +0x0C, hi +0x14, radius
// +0x20 behind the pinned getRadius 0x0030B719, dirty flag +0x24, refresh
// 0x0030B3D1); the class name is not established.
//  - Rva0030B719Shape::getCenterPoint, retail 0x0030B72C (67 bytes): Zero
//    Hour's bounds midpoint, returned as a Coord2D.
//  - PolygonTrigger::getCenterPoint2D, retail 0x002E3876 (19 bytes): the
//    shape's center; also reached through the this-adjusting forwarder
//    0x00330C22 (this - 0x3C), so it is likely a virtual of a base.
//  - PolygonTrigger::getCenterPoint, retail 0x002E38F3 (97 bytes): Zero
//    Hour's body over the center above; the height is
//    TheTerrainLogic->getGroundHeight (vslot 6) when there is a terrain logic,
//    else the integer at PolygonTrigger +0x30 (no assert in retail).
typedef float Real;
typedef int Int;
typedef bool Bool;
#define NULL 0

struct Coord2D
{
	Coord2D() {}
	Coord2D(Real ax, Real ay) : x(ax), y(ay) {}
	Real x, y;
};
struct Coord3D
{
	Real x, y, z;
};
struct Region2D
{
	Coord2D lo, hi;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = NULL) const;
};
extern TerrainLogic *TheTerrainLogic;

class Rva0030B719Shape
{
public:
	Coord2D getCenterPoint(void) const;
	void updateBounds(void) const;
private:
	unsigned char m_pad00[0x0C];
	Region2D m_bounds; // +0x0C
	unsigned char m_pad1C[0x24 - 0x1C];
	Bool m_boundsNeedsUpdate; // +0x24
};

class PolygonTrigger
{
public:
	Coord2D getCenterPoint2D(void) const;
	void getCenterPoint(Coord3D *pOutCoord) const;
private:
	unsigned char m_pad00[0x08];
	Rva0030B719Shape m_shape; // +0x08 (0x28 bytes)
	Int m_defaultHeight; // +0x30
};

Coord2D Rva0030B719Shape::getCenterPoint(void) const
{
	if (m_boundsNeedsUpdate) {
		updateBounds();
	}
	Real x = (m_bounds.lo.x + m_bounds.hi.x) / 2.0f;
	Real y = (m_bounds.lo.y + m_bounds.hi.y) / 2.0f;
	return Coord2D(x, y);
}

Coord2D PolygonTrigger::getCenterPoint2D(void) const
{
	return m_shape.getCenterPoint();
}

void PolygonTrigger::getCenterPoint(Coord3D* pOutCoord)	const
{
	if (!pOutCoord) {
		return;
	}

	Coord2D center = getCenterPoint2D();
	(*pOutCoord).x = center.x;
	(*pOutCoord).y = center.y;

	if (TheTerrainLogic) {
		(*pOutCoord).z = TheTerrainLogic->getGroundHeight(center.x, center.y);
	} else {
		(*pOutCoord).z = m_defaultHeight;
	}
}
