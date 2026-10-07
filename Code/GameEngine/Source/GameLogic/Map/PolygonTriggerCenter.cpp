// cl: /DNDEBUG /MD
//
// PolygonTrigger::getCenterPoint and the center getters under it, after Zero
// Hour's GameEngine/Source/GameLogic/Map/PolygonTrigger.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference).
// BFME 2 moves Zero Hour's bounds, radius and bounds-dirty flag into a shape
// at PolygonTrigger +8 (target evidence: bounds lo +0x0C, hi +0x14, radius
// +0x20 behind the pinned getRadius 0x0030B719, dirty flag +0x24, refresh
// 0x0030B3D1); the class name is not established.
//  - Rva0030B719Shape::getCenterPoint, retail 0x0030B72C (67 bytes, pinned):
//    Zero Hour's bounds midpoint, returned as a Coord2D.
//  - PolygonTrigger::getCenterPoint2D, retail 0x002E3876 (19 bytes): the
//    shape's center; also reached through the this-adjusting forwarder
//    0x00330C22 (this - 0x3C), so it is likely a virtual of a base.
//  - PolygonTrigger::getCenterPoint, retail 0x002E38F3 (97 bytes): Zero
//    Hour's body over the center above; the height is
//    TheTerrainLogic->getGroundHeight (vslot 6) when there is a terrain logic,
//    else the integer at PolygonTrigger +0x30 (no assert in retail).
typedef float Real;
typedef int Int;
#define NULL 0

struct Coord2D
{
	Real x, y;
};
struct Coord3D
{
	Real x, y, z;
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
private:
	unsigned char m_pad00[0x28];
};

class PolygonTrigger
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18(Int height);
	virtual void slot1C();
	virtual void slot20(const Coord2D *offset);
	Coord2D getCenterPoint2D(void) const;
	void getCenterPoint(Coord3D *pOutCoord) const;
	void rva002E38AF(const Coord3D *offset);
private:
	unsigned char m_pad04[0x04];
	Rva0030B719Shape m_shape; // +0x08 (0x28 bytes)
	Int m_defaultHeight; // +0x30
};

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

// ?rva002E38AF@PolygonTrigger@@QAEXPBUCoord3D@@@Z
// Native Ghidra extent 0x002E38AF..0x002E38F3, RET 4. Retail calls the
// rowed compiler vcall thunks for slots +0x20 and +0x18. Those calls
// establish dispatch and argument shapes; their original names are unknown.
void PolygonTrigger::rva002E38AF(const Coord3D *offset)
{
	Coord2D planar;
	planar.x = offset->x;
	planar.y = offset->y;
	(this->*(&PolygonTrigger::slot20))(&planar);
	(this->*(&PolygonTrigger::slot18))((Int)(offset->z + m_defaultHeight));
}
