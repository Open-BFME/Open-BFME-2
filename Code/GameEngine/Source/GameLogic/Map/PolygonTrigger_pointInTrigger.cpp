// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?pointInTrigger@PolygonTrigger@@QAE_NABUICoord3D@@@Z
// Retail boundary 0x002E3A13..0x002E3A39 (38B); target bytes copy x/y into a
// two-int local and call 0x00285B66 with that pointer and this+8. The ZH donor
// identifies the method's polygon-test role; its full ray-cast is not this body.

#include "../../../../Libraries/Include/Lib/ICoord3D.h"

struct PlanarPoint
{
    int x;
    int y;
};

bool rva00285B66(const void *point, const void *region);

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
class Coord2D;
struct Coord3D;
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

bool PolygonTrigger::pointInTrigger(const ICoord3D &point)
{
    PlanarPoint planarPoint;
    planarPoint.x = point.x;
    planarPoint.y = point.y;
    const void *region = reinterpret_cast<const char *>(this) + 8;
    return rva00285B66(&planarPoint, region);
}

// Clean BFME1 9cbfb551 donor structural leads; native instructions independently
// establish complete RET boundaries and each raw field operation and ABI.
// Address-owned carriers retain unknown original receiver identity and bounds.

// ?take@Rva002E3A7AFields@@QAEIXZ
struct Rva002E3A7AFields { unsigned int word0; unsigned int take(); };
unsigned int Rva002E3A7AFields::take() { unsigned int value=word0; word0=0; return value; }
