// cl: /O1 /Ob1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
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

#include "../../../Include/Common/Overridable.h"

class ThingTemplate : public Overridable
{
};

#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"


// Live Thing instance count (WorldBuilder asserts m_instances>0 in
// Thing::~Thing); the data ledger still names it after the destructor's
// former placeholder class Rva0030A120 (original global name unknown).
int g_Rva0030A120Count;

class Object;
class Drawable;

// Thing view: primary vftable 0x008086E0 has eight slots. Slot 0 is the
// rowed calculateHeightAboveTerrain 0x0030A4AC; slots 1-4 are the donor's
// NULL-returning asObjectMeth/asDrawableMeth pairs (folded 0x000D43D0);
// slot 5 is the pure reactToTransformChange (_purecall 0x0003B810); slot 6
// is an unnamed empty virtual (folded 0x000B3FD0) that Object overrides
// with 0x0028B193; slot 7 is the scalar deleting destructor 0x0030A243.
#include "thing.h"

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

// Thing::~Thing 0x0030A120 13B: restores the Thing vftable and lowers the live
// instance count (WorldBuilder twin Thing::~Thing in Thing.cpp asserts it was
// positive). Protected virtual as in Zero Hour's MEMORY_POOL_GLUE_ABC(Thing).
// Its compiler-generated scalar deleting destructor ??_GThing 0x0030A243 28B is
// the vftable's slot 7, emitted here beside the vftable.
Thing::~Thing()
{
	--g_Rva0030A120Count;
}
