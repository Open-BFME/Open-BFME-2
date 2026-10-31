// cl: /DNDEBUG /MD /EHsc /vd2 /Ireference/shims/sweep /Ireference/shims/moduledata
// ?Rva0030596CIntersects@@YA_NPAXUPlaceCoord@@M@Z @0x0030596C 137B via GhostObjectManager GhostObject CollidesWith
// Retail walks GhostObject list from TheGhostObjectManager slot 0x20 and tests GeometryInfo::CollidesWith.
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
// ?Rva0030596CIntersects@@YA_NPAXUPlaceCoord@@M@Z @0x0030596C 137B via GhostObjectManager GhostProvider CollidesWith
#include "PlacementPositionValue.h"
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GhostObject.h
class GhostObjectManager : public Snapshot
{
public:
	GhostObjectManager( void );
	virtual ~GhostObjectManager();
	// Table 0x00C078F0: slot 4 is the shared empty RET 0x000B3FD0, slot 5 the shared setter 0x002B230F.
	virtual void reset( void ) {}
	virtual void setLocalPlayerIndex( int index ) { m_localPlayer = index; }
	// Slots 6-8 are __purecall; W3DGhostObjectManager's 0x00BC59B8 fills them, slot 8 with 0x001DB09D, returning +0x10.
	virtual void updateOrphanedObjects( int *playerIndexList, int numNonLocalPlayers ) = 0;
	virtual GhostObject *addGhostObject( Object *object ) = 0;
	virtual GhostObject *getFirst() = 0;

protected:
	virtual const char *GetSnapshotName( void ) const;
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

	Int m_localPlayer;																					///< 0x04
	Bool m_lockGhostObjects;																		///< 0x08
	Bool m_saveLockGhostObjects;																///< 0x09
};

extern GhostObjectManager *TheGhostObjectManager;
bool __cdecl Rva0030596CIntersects(void *self, PlaceCoord coord, float radius)
{
	GhostObject *ghost = TheGhostObjectManager->getFirst();
	if (ghost != 0)
	{
		GeometryInfo *myGeom = (GeometryInfo *)((char *)self + 0xa0);
		for (; ghost != 0; ghost = ghost->getNext())
		{
			const GeometryInfo *gi = (const GeometryInfo *)ghost->vslot00();
			const Coord3D *pos = (const Coord3D *)ghost->vslot04();
			float ang = ghost->vslot08();
			if (gi->CollidesWith(*pos, ang, *myGeom, coord, radius))
				return true;
		}
	}
	return false;
}
