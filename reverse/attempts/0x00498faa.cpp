// ?rva00498FAA@GateOpenAndCloseBehavior@@AAEXXZ
// partial score=0.96 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /arch:SSE /GX
//
// ?rva00498FAA@GateOpenAndCloseBehavior@@AAEXXZ, retail 0x00498FAA: the
// gate's push-out scan, run by slots 7 and 8 (GateOpenAndCloseBehaviorSlots.cpp)
// before the gate changes state. A cylinder (height 30, both radii the
// template's +0xB0) is moved ahead of the gate along its 2D direction by
// 0.66 of the geometry's +0x10; every object with an AI, alive, of none of
// kinds 0x59 0x68 0x3C 2 (against the KindOf prototype), without status
// 0x26 and inside that footprint at the gate's angle (0x0027C2C9) within
// 1.1 times the geometry's +0x14 is handed to 0x00498DF3 with that offset.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
extern "C" void *memset(void *dst, int value, unsigned int size) throw();

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
	void scale(float s)
	{
		x *= s;
		y *= s;
		z *= s;
	}
};

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

// GeometryInfo as this scan reads it (ctor 0x00050B74, dtor 0x00050B2A).
class GeometryInfo
{
public:
	GeometryInfo(GeometryType type, bool isSmall, float height, float majorRadius,
		float minorRadius);
	virtual ~GeometryInfo();
	char m_pad04[0x10 - 0x04];
	float m_10;	// +0x10
	float m_14;	// +0x14
	float getBoundingCircleRadius() const { return m_14; }
	char m_pad18[0x5C - 0x18];
};

// vftable 0x00BFB1B8; the out-of-line ctor 0x0027C2C9: +0x08 a position,
// +0x14 a geometry, +0x18 an angle, +0x1C a flag.
class Rva0027C2C9 : public Rva000421C8
{
public:
	Rva0027C2C9(const Coord3D *pos, const GeometryInfo *geom, float angle, bool flag);	// 0x0027C2C9
	virtual bool allow(Object *obj);
	Coord3D m_pos;
	const GeometryInfo *m_geom;
	float m_angle;
	bool m_flag;
};

// A 128-bit ObjectStatusMaskType; 0x0023DA79 clears it and sets one bit.
enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};

struct ObjectStatusMask
{
	ObjectStatusMask() {}
	ObjectStatusMask *Rva0023DA79(int reserved, ObjectStatusTypes bit) throw();	// 0x0023DA79
	unsigned int m_bits[4];
};

struct ObjectStatusMaskNone : ObjectStatusMask
{
	ObjectStatusMaskNone() throw() { memset(this, 0, sizeof(*this)); }
};

// vftable 0x00C17968: must have every status of the first mask and none of
// the second.
class Rva003685CF : public Rva000421C8
{
public:
	Rva003685CF(const ObjectStatusMask &must, const ObjectStatusMask &mustNot) throw();	// 0x003685CF
	virtual bool allow(Object *obj);
	ObjectStatusMask m_must;
	ObjectStatusMask m_mustNot;
};

// The 224-bit KindOf mask; the (unused, four bits) constructor is 0x0006EEBC.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(int unused, int b1, int b2, int b3, int b4) throw();	// 0x0006EEBC
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00C17F08, allow 0x0026118B: the object has an AI (+0x258).
class Rva0026118BFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

struct ThingTemplate
{
	char m_pad00[0xB0];
	float m_B0;	// +0xB0
};

class Object
{
public:
	void getUnitDirectionVector2D(Coord3D &dir) const;	// 0x0030A2A2
	const Coord3D *getPosition() const { return &m_pos; }
	float getOrientation() const { return m_angle; }
	const ThingTemplate *getTemplate() const { return m_template; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;		// +0x38
	float m_angle;		// +0x44
};

class ModuleData;

class GatePrimary
{
public:
	virtual void gap0() = 0;
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class GateOpenAndCloseBehavior : public GatePrimary, public BehaviorModule
{
private:
	void rva00498FAA();
	void rva00498DF3(Object *obj, float offset);	// 0x00498DF3
};

void GateOpenAndCloseBehavior::rva00498FAA()
{
	Object *us = m_object;
	if (!us)
		return;
	Coord3D pos;
	pos.x = us->getPosition()->x;
	pos.y = us->getPosition()->y;
	pos.z = us->getPosition()->z;
	float radius = us->getTemplate()->m_B0;
	GeometryInfo geom(GEOMETRY_CYLINDER, false, 30.0f, radius, radius);
	float offset = geom.m_10 * 0.66;
	Coord3D dir;
	us->getUnitDirectionVector2D(dir);
	dir.scale(offset);
	pos.x += dir.x;
	pos.y += dir.y;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&pos, geom.getBoundingCircleRadius() * 1.1f, 3,
		Rva0026119DFilter().link(&Rva0026118BFilter())
			->link(&Rva0004584D(*(const BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
				BfmeFixedStorage0004543D(0, 0x59, 0x68, 0x3C, 2)))
			->link(&Rva003685CF(ObjectStatusMaskNone(), *ObjectStatusMask().Rva0023DA79(0, OBJECT_STATUS_26)))
			->link(&Rva0027C2C9(&pos, &geom, us->getOrientation(), true)), 0);
	for (Object *obj = hits.next(); obj; obj = hits.next())
		rva00498DF3(obj, offset);
}
