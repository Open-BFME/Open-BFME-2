// PolygonTrigger: shared target view preserving the matched virtual-inheritance constructor.
// Native ctor2E3FAB/new0x64, base330C50 and seven vtordisp thunks2E3E80..2E3EB0.
// Address-derived base names and unrecovered fields remain neutral.
#pragma once
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct Region2D;
struct Rva0030B72CPoint;
struct Coord3D;
class PolygonTrigger;
class Rva00330C50Interface
{
public:
	~Rva00330C50Interface() {}
	virtual int slot0() const = 0;
	virtual Rva0030B72CPoint slot1(int index) const = 0;
	virtual int slot2() const = 0;
	virtual Region2D slot3() = 0;
	virtual float slot4() const = 0;
	virtual float slot5() const = 0;
	virtual Rva0030B72CPoint slot6() const = 0;
};

class Rva0030B9DD
{
    friend class Rva00330C50;
public:
	Rva0030B9DD(int);
	~Rva0030B9DD();
private:
	Rva0030B72CPoint *begin, *end, *capacity;
	char unknown0C[0x28-0x0C];
	int index;
};

class Rva00330C50 : public virtual Rva00330C50Interface
{
public:
	Rva00330C50();
	void rva00330AA6(int);
	virtual ~Rva00330C50();
	virtual int slot0() const;
	virtual Rva0030B72CPoint slot1(int index) const;
	virtual int slot2() const;
	virtual Region2D slot3();
	virtual float slot4() const;
	virtual float slot5() const;
	virtual Rva0030B72CPoint slot6() const;
protected:
    // Eight-byte point stride and container begin/end at +0/+4 are native facts.
    // A byte difference preserves the old donor's arithmetic shift without
    // requiring a definition or a competing copy of the point type.
    __forceinline int pointCount() const {
        return int((const char *)container.end-(const char *)container.begin) >> 3;
    }
private:
	Rva0030B9DD container;
	bool changed;
};

class Rva002E3EB8Base { public: virtual void slot()=0; };

class PolygonLink { public: PolygonLink():next(0){} PolygonTrigger *next; };

struct IRegion2D;
struct ICoord3D;
struct FloatRect0073CE30;

class PolygonTrigger : public PolygonLink, public Rva00330C50, public Rva002E3EB8Base {
public:
 PolygonTrigger(int);     // 0x002E3EB8
 PolygonTrigger(int,int); // 0x002E3FAB
 virtual ~PolygonTrigger();
 virtual void slot() = 0;
 // Rowed in Map/PolygonTrigger.cpp unless noted.
 static void addPolygonTrigger(PolygonTrigger *); // 0x002E36EF
 PolygonTrigger *getNext() { return next; }         // trigger list link, +0x3C
 const AsciiString &getTriggerName() const { return name; } // +0x40
 int getID() const { return id; }                    // +0x44
 Region2D rva0007E03A();                             // shape region, 0x0007E03A
 void getBounds(FloatRect0073CE30 *rect);            // 0x002E3954
 void getBounds(IRegion2D *out);                     // 0x002E3978
 Rva0030B72CPoint getCenterPoint2D() const;          // 0x002E3876
 void getCenterPoint(Coord3D *pOutCoord) const;      // 0x002E38F3
 void rva002E38AF(const Coord3D *offset);            // 0x002E38AF
 bool pointInTrigger(const ICoord3D &point);         // 0x002E3A13
 void rva002E36B7(int);
 bool rva002E3A39(const Coord3D &);
 bool rva002E3AA8(const Coord3D *, const Coord3D *, Coord3D *, bool);
 AsciiString name;
 int id;
 bool flag48;
 AsciiString layer;
 bool flag50;
 int field54,field58;
private:
 friend class Rva002E41EC;    // 0x002E41EC raises the counter past parsed ids
 friend void Rva00328A6B(int); // 0x00328A6B stores the counter
 static int s_currentID;       // ?s_currentID@PolygonTrigger@@0HA, VA 0x00DBD0F0
};

typedef char PolygonTriggerRetailSize[sizeof(PolygonTrigger)==0x64 ? 1 : -1];
