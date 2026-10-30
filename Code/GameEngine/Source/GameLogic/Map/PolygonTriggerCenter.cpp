// cl: /DNDEBUG /MD
//
// PolygonTrigger::getCenterPoint and the center getters under it, after Zero
// Hour's GameEngine/Source/GameLogic/Map/PolygonTrigger.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference).
// BFME 2 moves Zero Hour's bounds, radius and bounds-dirty flag into a shape
// at PolygonTrigger +8 (target evidence: bounds lo +0x0C, hi +0x14, radius
// +0x20 behind the pinned getRadius 0x0030B719, dirty flag +0x24, refresh
// 0x0030B3D1); the class name is not established.
//  - Rva0030B719Shape::rva0030B72C, retail 0x0030B72C (67 bytes, rowed in
//    Common/PinnedForwarders1830.cpp): Zero Hour's bounds midpoint.
//  - PolygonTrigger::getCenterPoint2D, retail 0x002E3876 (19 bytes): the
//    shape's center; also reached through the this-adjusting forwarder
//    0x00330C22 (this - 0x3C), so it is likely a virtual of a base. It hands
//    its own return slot to 0x0030B72C unchanged, so both return the same
//    point type; that type stores its fields one by one when copied, unlike
//    the plain canonical Coord2D, and keeps the provider's address name.
//  - PolygonTrigger::getCenterPoint, retail 0x002E38F3 (97 bytes): Zero
//    Hour's body over the center above; the height is
//    TheTerrainLogic->getGroundHeight (vslot 6) when there is a terrain logic,
//    else the integer at PolygonTrigger +0x30 (no assert in retail).
typedef float Real;
typedef int Int;

#include <stddef.h>
#include "../../../../Libraries/Include/Lib/Coord2D.h"
#define COORD3D_VIEW_INLINE
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"

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

struct Rva0030B72CPoint
{
	Rva0030B72CPoint() {}
	__forceinline Rva0030B72CPoint(const Rva0030B72CPoint &that)
	{
		x = that.x;
		y = that.y;
	}
	float x, y;
};

struct Region2D;
struct Rva0030B72CPoint;
class Coord2D;
class Rva0030B719Shape
{
public:
	Region2D rva0030B6E3();
	Rva0030B72CPoint rva0030B72C(void) const;
	Coord2D *begin;
	Coord2D *end;
	char m_pad08[0x20];
};

struct FloatRect0073CE30;
struct IRegion2D;
struct ICoord3D;
class PolygonTrigger
{
private:
	friend void Rva002E373CClear();
	static int s_currentID; // VA 0x00DBD0F0 (retail .data initial value 1)
public:
	static void addPolygonTrigger(PolygonTrigger *pTrigger);
	PolygonTrigger *getNext() { return m_nextPolygonTrigger; }
	Region2D rva0007E03A();
	void getBounds(FloatRect0073CE30 *rect);
	void getBounds(IRegion2D *out);
	void rva002E36B7(int);
	Rva0030B72CPoint getCenterPoint2D(void) const;
	void getCenterPoint(Coord3D *pOutCoord) const;
	void rva002E38AF(const Coord3D *offset);
	bool pointInTrigger(const ICoord3D &point);
	bool rva002E3A39(const Coord3D &);
	bool rva002E3AA8(const Coord3D *, const Coord3D *, Coord3D *, bool);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18(int height);
	virtual void slot1C();
	virtual void slot20(const Coord2D *offset);
	char m_pad04[0x4];
private:
	Rva0030B719Shape m_shape; // +0x08
	int m_defaultHeight; // +0x30
	char m_pad34[0x8];
	PolygonTrigger *m_nextPolygonTrigger; // +0x3C
	char opaque40[8]; // +0x40
	bool flag48; // +0x48
	char opaque49[7]; // +0x49
	bool flag50; // +0x50
	char opaque51[3]; // +0x51
	int field54; // +0x54
	int field58; // +0x58
};

Rva0030B72CPoint PolygonTrigger::getCenterPoint2D(void) const
{
	return m_shape.rva0030B72C();
}

void PolygonTrigger::getCenterPoint(Coord3D* pOutCoord)	const
{
	if (!pOutCoord) {
		return;
	}

	Rva0030B72CPoint center = getCenterPoint2D();
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
