// cl: /DNDEBUG /MD /EHsc /O1 /vd2 /Ireference/shims/moduledata
//
// GhostObject constructor and destructor on the BFME 2 layout.
//   0x00305A8F 161B GhostObject::GhostObject
//   0x00305B5E  88B GhostObject::~GhostObject
//
// Target evidence. Both bodies install the GhostObject tables 0x00C0793C
// (Snapshot at +0x00), 0x00C4EF80 (provider at +0x04, whose vbptr is +0x08)
// and 0x00C07928 (the virtual base) and write the vtordisp in front of the
// virtual base from the vbtable 0x00C07950 entry less 0x7C, so the
// non-virtual part is 0x80 bytes. The constructor builds the Snapshot inline
// (0x00BBB554), then the provider through the rowed 0x003058F9 and the
// GeometryInfo at +0x20 through the rowed 0x0029840D; it clears the parent
// object +0x0C, the angle +0x1C, the partition data +0x7C and the position
// +0x10..+0x18. The destructor runs the rowed ~GeometryInfo 0x00050B2A and
// restores the Snapshot table. The virtual base's five slots are GhostObject's
// getters 0x00305927 (+0x20), 0x0030592B (+0x10) and 0x0030592F (+0x1C), the
// setter 0x0006369E and the getter 0x0044467C (+0x7C), reached through the
// vtordisp thunks 0x00305B36..0x00305B56; the provider's own four slots stay
// pure (0x00C4EF80 is the provider constructor's table).
// Donor-carried: the names, Zero Hour's member order (parent object, position,
// angle, partition data) and its constructor, with BFME 2's GeometryInfo in
// place of Zero Hour's geometry fields. The provider and virtual-base
// interfaces keep opaque names.

#include "Common/Snapshot.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;

class Object;
class PartitionData;
class GeometryInfo;

// The virtual base: retail table 0x00C078DC is five purecall slots.
class Rva001B3E60VBase
{
public:
	virtual const GeometryInfo *vslot00() const = 0;
	virtual const Coord3D *vslot04() const = 0;
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

class GeometryInfo
{
public:
	GeometryInfo();
	virtual ~GeometryInfo();

private:
	unsigned char m_bytes[0x5C - 0x04];
};

class GhostObject : public Snapshot, public Rva003058F9
{
public:
	GhostObject();
	virtual ~GhostObject();

	virtual const GeometryInfo *vslot00() const;
	virtual const Coord3D *vslot04() const;
	virtual Real vslot08() const;
	virtual void vslot0C( PartitionData *pd );
	virtual PartitionData *vslot10() const;

protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );

	Object *m_parentObject;																			///< 0x0C
	Coord3D m_parentPosition;																		///< 0x10
	Real m_parentAngle;																					///< 0x1C
	GeometryInfo m_parentGeometry;															///< 0x20
	PartitionData *m_partitionData;															///< 0x7C
};

//-------------------------------------------------------------------------------------------------
GhostObject::GhostObject() :
	m_parentObject( 0 ),
	m_parentAngle( 0.0f ),
	m_partitionData( 0 )
{
	m_parentPosition.x = 0.0f;
	m_parentPosition.y = 0.0f;
	m_parentPosition.z = 0.0f;
}

//-------------------------------------------------------------------------------------------------
GhostObject::~GhostObject()
{
}
