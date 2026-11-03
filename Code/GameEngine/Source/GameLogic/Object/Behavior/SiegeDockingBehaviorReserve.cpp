// cl: /ICode/Libraries/Include /ICode/GameEngine/Source /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00459CC0@SiegeDockingBehavior@@UAEHW4ObjectID@@@Z
// Retail 0x00459CC0, 234B: a SiegeDockingBehavior member entered through the
// interface at +0x20 (ret 4): reserve the nearest free dock entry for an
// object id. It looks the object up, refreshes the reservations
// (0x00459B68, pinned, called on the primary this), then, over the dock
// entry pointer vector at +0x24 (the entries built by 0x00459E05: type +4,
// position +8, reserved object id +0x20), picks the closest unreserved entry
// (towers - template kind-of 0x119:0x08 - may take any type, other objects
// only type 0) by Coord3D::length of the offset, records the id there and
// returns its index, or -1. Slot name not established: address-derived.
// The entry position goes through a memberwise-copy local so the three
// coordinate loads issue x,y,z (a direct subtraction compiles y,z,x).
#define _STLP_NO_EXCEPTIONS 1
#include <math.h>
#include <vector>
#include "Lib/Coord3D.h"
#include "Common/GameLogicObjectLookupView.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../Include/Common/ThingTemplate.h"

#include "../object.h"

extern GameLogic *TheGameLogic;

struct SiegeDockingPoint
{
	SiegeDockingPoint(const Coord3D &c) : x(c.x), y(c.y), z(c.z) {}
	float x;
	float y;
	float z;
};

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
	virtual Int rva00459CC0( ObjectID id ) = 0;
 virtual bool rva00459A2A(ObjectID,Coord3D*)=0;
};

class SiegeDockingBehavior : public SiegeDockingPrimary, public SiegeDockingInterface
{
public:
	virtual Int rva00459CC0( ObjectID id );
 virtual bool rva00459A2A(ObjectID,Coord3D*);
private:
	void rva00459B68() const;
	_STL::vector<Rva00459E05Entry *> m_entries;
};

Int SiegeDockingBehavior::rva00459CC0( ObjectID id )
{
	Object *obj = TheGameLogic->findObjectByID( id );
	if( obj == 0 )
		return -1;

	rva00459B68();

	UnsignedInt count = m_entries.size();
	if( count == 0 )
		return -1;

	Int bestIndex = -1;
	Real bestDist = 99999.0f;
	for( UnsignedInt i = 0; i < count; ++i )
	{
		Rva00459E05Entry *entry = m_entries[ i ];
		if( entry->m_objectID != 0 )
			continue;
		if( ( obj->m_template->m_kindof[4] & (1U << 11) ) == 0 && entry->m_type != 0 )
			continue;

		SiegeDockingPoint entryPos(entry->m_position);
		Coord3D delta;
		delta.x = entryPos.x - obj->m_cachedPos.x;
		delta.y = entryPos.y - obj->m_cachedPos.y;
		delta.z = entryPos.z - obj->m_cachedPos.z;
		Real dist = delta.length();
		if( dist < bestDist )
		{
			bestIndex = i;
			bestDist = dist;
		}
	}

	if( bestIndex >= 0 )
		m_entries[ bestIndex ]->m_objectID = id;

	return bestIndex;
}

// Native459A2A..459B68,318B RET8, the +20 interface approach-point query.
// Entry constructor459E05 proves the position/direction/ID layout. This query
// visits free compatible entries, offsets by direction*30, and copies the
// nearest approach point. Original method name is unresolved.
// Visible Coord3D::length and ordinary field reads remove the bank's volatile
// workaround; the exact shared length provider is still called out of line.
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
			if( ( obj->m_template->m_kindof[4] & (1U << 11) ) == 0 && entry->m_type != 0 )
				continue;

			Real scale = 30.0f;
			Real px = entry->m_position.x;
			Real py = entry->m_position.y;
			Real pz = entry->m_position.z;
			Real dx = entry->m_direction.x;
			Real dy = entry->m_direction.y;
			Real dz = entry->m_direction.z;
			dx *= scale;
			dy *= scale;
			dz *= scale;
			// The equivalent conditional preserves MSVC 7.1 SSE scheduling.
			// Both arms select the same scaled component; no runtime fallback.
			px -= (scale ? dx : dx);
			py -= dy;
			pz -= dz;
			Coord3D approach;
			approach.x = px;
			approach.y = py;
			approach.z = pz;
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

inline float Coord3D::length() const { return (float)sqrt(x * x + y * y + z * z); }
