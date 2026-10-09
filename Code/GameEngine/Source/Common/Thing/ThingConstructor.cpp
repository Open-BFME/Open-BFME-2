// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
// ??0Thing@@QAE@PBVThingTemplate@@@Z retail 0x0030A188 187 bytes RET 4.
//
// Thing::Thing (WorldBuilder twin 0x00CEC1B0 in Thing.cpp; Zero Hour's
// Thing::Thing donor). Stores the Thing vftable 0x008086E0 and builds the
// three Matrix3D rows through the vector constructor iterator 0x00001423
// then raises the live-instance counter 0x009FF4A8 that the destructor
// 0x0030A120 lowers. A null template returns at once as in the donor. The
// template is resolved through Overridable::getFinalOverride (inline first
// level; recursion is the pinned out-of-line copy at 0x001E35DF). The
// identity matrix and zeroed cached position angle direction and altitudes
// follow the donor; the BFME2 layout has no debug template name.
// Called by Object::Object 0x00298EA9 and Drawable::Drawable 0x002797BD.

#include "Coord3D.h"

class Matrix3D;

// Donor Coord3D::zero; the canonical Coord3D header declares no inline zero.
struct Coord3DZero
{
	static void zero(Coord3D &c) { c.x = 0.0f; c.y = 0.0f; c.z = 0.0f; }
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
};

class Vector4
{
public:
	__forceinline Vector4() {}
	__forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}

private:
	Vector4 Row[3];
};

// Live Thing instance count (WorldBuilder asserts m_instances>0 in
// Thing::~Thing); the data ledger names it after the destructor's
// placeholder class and Rva0030A120Dtor.cpp owns the definition.
extern int g_Rva0030A120Count;

class Object;
class Drawable;

// Thing view: primary vftable 0x008086E0 has eight slots. Slot 0 is the
// rowed calculateHeightAboveTerrain 0x0030A4AC; slots 1-4 are the donor's
// NULL-returning asObjectMeth/asDrawableMeth pairs (folded 0x000D43D0);
// slot 5 is the pure reactToTransformChange (_purecall 0x0003B810); slot 6
// is an unnamed empty virtual (folded 0x000B3FD0) that Object overrides
// with 0x0028B193; slot 7 is the scalar deleting destructor 0x0030A243.
class Thing
{
public:
	Thing(const ThingTemplate *thingTemplate);

protected:
	virtual float calculateHeightAboveTerrain() const;
	virtual Object *asObjectMeth() { return 0; }
	virtual Drawable *asDrawableMeth() { return 0; }
	virtual const Object *asObjectMeth() const { return 0; }
	virtual const Drawable *asDrawableMeth() const { return 0; }
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, float oldAngle) = 0;
	virtual void vslot6() {}

public:
	virtual ~Thing();

private:
	const ThingTemplate *m_template;		// +0x04
	Matrix3D m_transform;				// +0x08
	Coord3D m_cachedPos;					// +0x38
	float m_cachedAngle;				// +0x44
	Coord3D m_cachedDirVector;				// +0x48
	float m_cachedAltitudeAboveTerrain;		// +0x54
	float m_cachedAltitudeAboveTerrainOrWater;	// +0x58
	int m_cacheFlags;				// +0x5C
};

Thing::Thing(const ThingTemplate *thingTemplate)
{
	++g_Rva0030A120Count;
	if (thingTemplate == 0)
		return;

	m_template = (const ThingTemplate *)thingTemplate->getFinalOverride();
	m_transform.Make_Identity();
	Coord3DZero::zero(m_cachedPos);
	m_cachedAngle = 0.0f;
	Coord3DZero::zero(m_cachedDirVector);
	m_cachedAltitudeAboveTerrain = 0;
	m_cachedAltitudeAboveTerrainOrWater = 0;
	m_cacheFlags = 0;
}
