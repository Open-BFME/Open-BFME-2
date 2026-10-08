// ?rva00459A2A@SiegeDockingBehavior@@UAE_NW4ObjectID@@PAUCoord3D@@@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00459A2A, 318B: a SiegeDockingBehavior member entered through the
// interface at +0x20 (ret 8): find the approach point of the nearest free
// dock entry for an object id. Over the dock entry pointer vector at +0x24
// (entries built by 0x00459E05: type +4, position +8, direction +0x14,
// reserved object id +0x20) it takes each unreserved entry the object may use
// (towers - template kind-of 0x119:0x08 - any type, others type 0), places
// the approach point 30 units back along the entry direction, and keeps the
// one closest to the object (Coord3D::length), copying it out. Returns
// whether one was found. Slot name not established: address-derived.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class ThingTemplate
{
public:
	unsigned char m_pad00[0x119];
	unsigned char m_kindOf119;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos;
};

extern GameLogic *TheGameLogic;

struct Rva00459E05Entry
{
	int m_index;
	int m_type;
	Coord3D m_position;
	Coord3D m_direction;
	ObjectID m_objectID;
};

class SiegeDockingPrimary
{
public:
	virtual void primarySlot00();
	unsigned char m_pad04[0x20 - 0x04];
};

class SiegeDockingInterface
{
public:
	virtual bool rva00459A2A( ObjectID id, Coord3D *out ) = 0;
};

class SiegeDockingBehavior : public SiegeDockingPrimary, public SiegeDockingInterface
{
public:
	virtual bool rva00459A2A( ObjectID id, Coord3D *out );
private:
	_STL::vector<Rva00459E05Entry *> m_entries;
};

bool SiegeDockingBehavior::rva00459A2A( ObjectID id, Coord3D *out )
{
	Object *obj = TheGameLogic->findObjectByID( id );
	if( obj == 0 )
		return false;

	UnsignedInt count = m_entries.size();
	if( count == 0 )
		return false;

	Int bestIndex = -1;
	Real bestDist = 99999.0f;
	{
		for( UnsignedInt i = 0; i < count; ++i )
		{
			Rva00459E05Entry *entry = m_entries[ i ];
			if( entry->m_objectID != 0 )
				continue;
			if( ( obj->m_template->m_kindOf119 & 8 ) == 0 && entry->m_type != 0 )
				continue;

			Real ox = entry->m_direction.x * 30.0f;
			Real oy = entry->m_direction.y * 30.0f;
			Real oz = entry->m_direction.z * 30.0f;
			Coord3D approach;
			approach.x = entry->m_position.x - ox;
			approach.y = entry->m_position.y - oy;
			approach.z = entry->m_position.z - oz;

			Coord3D delta;
			delta.x = approach.x - obj->getPosition()->x;
			delta.y = approach.y - obj->getPosition()->y;
			delta.z = approach.z - obj->getPosition()->z;
			Real dist = delta.length();
			if( dist < bestDist )
			{
				*out = approach;
				bestIndex = i;
				bestDist = dist;
			}
		}
	}

	if( bestIndex >= 0 )
		return true;

	return false;
}
