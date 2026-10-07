// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /ICode/Libraries/Include
//
// Constructor of the partition filter whose vftable is 0x00BFB1B8 (slot 0 the
// shared deleting dtor 0x00395A19, slot 1 allow 0x00261603, slot 2
// 0x0036CC7A), named after its allow slot as PartitionFilterAllowSlots.cpp
// names its siblings.
//
// Target facts: the out-of-line ctor 0x0027C2C9 clears the +0x04 link of the
// filter base (0x000421C8), stores the vftable, copies a Coord3D to +0x08,
// keeps a reference at +0x14, a float at +0x18 and a bool at +0x1C. Its 14
// callers include GateOpenAndCloseBehavior's 0x00498FAA, which passes a
// position, a stack GeometryInfo, the object's orientation (+0x44) and true.
// Donor lead: Zero Hour's PartitionFilterWouldCollide(pos, geom, angle,
// desired) has this member order, less BFME 2's +0x04 link; the port in
// PartitionManager.cpp keeps Zero Hour's base and does not match.
#include "Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;

class Object;
class GeometryInfo;

// The partition filter base (ctor 0x000421C8, vftable 0x00BC26E0).
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual Bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

// Retail copies the position one coordinate at a time, in initializer order,
// with no block move: a member-wise copy.
struct FilterPosition : public Coord3D
{
	FilterPosition(const Coord3D &p) { x = p.x; y = p.y; z = p.z; }
};

class Rva00261603Filter : public Rva000421C8
{
public:
	Rva00261603Filter(const Coord3D &pos, const GeometryInfo &geom, Real angle, Bool desired);
	virtual Bool allow(Object *objOther);

private:
	FilterPosition m_position;	// +0x08
	const GeometryInfo &m_geom;	// +0x14
	Real m_angle;				// +0x18
	Bool m_desiredCollisionResult;	// +0x1C
};

// ??0Rva00261603Filter@@QAE@ABUCoord3D@@ABVGeometryInfo@@M_N@Z @0x0027C2C9 61B
Rva00261603Filter::Rva00261603Filter(const Coord3D &pos, const GeometryInfo &geom, Real angle, Bool desired) :
	m_position(pos),
	m_geom(geom),
	m_angle(angle),
	m_desiredCollisionResult(desired)
{
}
