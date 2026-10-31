// cl: /DNDEBUG /MD /EHsc /vd2 /Ireference/shims/sweep /Ireference/shims/moduledata
//
// ?xfer@GhostObject@@MAEXPAVXfer@@@Z, retail 0x003059F5, 154 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0080793C (class of ??1GhostObject@@UAE@XZ).
// Donor: ZH GeneralsMD GhostObject::xfer (parent ObjectID via getID at Object
// +0x74 plus XferObjectID plus IsLoading-gated findObjectByID via TheGameLogic
// plus XferException on missing plus angle then position). BFME2 repairs:
// IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed 0x000053EE,
// ObjectID at +0x0C via rowed XferObjectID 0x003060B2, IsLoading via Xfer slot
// 0x04, float at +0x1C via Xfer slot 0x70, Coord3DBase at +0x10 via Xfer slot
// 0x60. Layout is Snapshot base (vptr) plus the provider at +0x04 (vbptr +0x08)
// giving +0x0C parent (cf. retail mov [esi+0x0C] and [eax+0x74] getID), Coord
// (12B) at +0x10 then float at +0x1C (0x10+0x0C=0x1C contiguous). Recipe is
// PoisonedBehaviorXfer slot-3 pattern with Xfer decl verbatim.

#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "../../../../Libraries/Include/Lib/Coord3DBase.h"
// 0x60. Layout is Snapshot base (vptr) plus +0x04/+0x08 pad giving +0x0C parent
// (cf. retail mov [esi+0x0C] and [eax+0x74] getID), Coord (12B) at +0x10 then
// float at +0x1C (0x10+0x0C=0x1C contiguous). Recipe is PoisonedBehaviorXfer
// slot-3 pattern with Xfer decl verbatim.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../Include/Common/BfmeXfer.h"

#include "../../Common/GameLogicObjectLookupView.h"

void XferObjectID(Xfer *xfer, ObjectID *objectID);

// Retail ThrowInfo names the 8-byte XferException class and its rowed
// copy constructor and destructor (see Common/System/XferException.cpp).
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	unsigned char m_pad[0x74];
	ObjectID m_id;
};


extern GameLogic *TheGameLogic;

typedef int Int;

typedef bool Bool;

typedef float Real;

class Object;

class PartitionData;

class GeometryInfo;

// The virtual base: retail table 0x00C078DC is five purecall slots.
class Rva001B3E60VBase
{
public:
	virtual const void *vslot00() const = 0;
	virtual const void *vslot04() const = 0;
	virtual Real vslot08() const = 0;
	virtual void vslot0C( PartitionData *pd ) = 0;
	virtual PartitionData *vslot10() const = 0;
};

class Rva001B3E60SecondBaseCore
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
};

// The provider at +0x04: its constructor is the rowed 0x003058F9.
class Rva003058F9
	: public Rva001B3E60SecondBaseCore
	, virtual public Rva001B3E60VBase
{
public:
	Rva003058F9();
};

struct Coord3D;
class GeometryInfo
{
public:
	GeometryInfo();
	bool CollidesWith(const Coord3D &, float, const GeometryInfo &, const Coord3D &, float) const;
	virtual ~GeometryInfo();
private:
	unsigned char m_bytes[0x5C - 0x04]; // +0x04
};

class GhostObject : public Snapshot, public Rva003058F9
{
public:
	GhostObject();
	virtual ~GhostObject();

	virtual const void *vslot00() const;
	virtual const void *vslot04() const;
	virtual Real vslot08() const;
	virtual void vslot0C( PartitionData *pd );
	virtual PartitionData *vslot10() const;
	// Slot 4 of table 0x00C0793C is __purecall; W3DGhostObject's 0x00BC5994 holds 0x00467F2C, returning +0xE0.
	virtual GhostObject *getNext() = 0;

protected:
	virtual void xfer( Xfer *xfer );

	Object *m_parentObject;																			///< 0x0C
	Coord3D m_parentPosition;																		///< 0x10
	Real m_parentAngle;																					///< 0x1C
	GeometryInfo m_parentGeometry;															///< 0x20
	PartitionData *m_partitionData;															///< 0x7C
};

void GhostObject::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	ObjectID parentObjectID = INVALID_OBJECT_ID;
	if (m_parentObject)
		parentObjectID = m_parentObject->getID();
	XferObjectID(xfer, &parentObjectID);
	if (xfer->IsLoading()) {
		m_parentObject = TheGameLogic->findObjectByID(parentObjectID);
		if (parentObjectID != INVALID_OBJECT_ID && m_parentObject == 0) {
			throw XferException(5, 0);
		}
	}
	*xfer == m_parentAngle;
	*xfer == asBase(m_parentPosition);
}
