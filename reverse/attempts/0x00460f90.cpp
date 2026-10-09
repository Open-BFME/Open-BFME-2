// ?rva00460F90@Rva00460F90@@QAEXXZ
// partial score=0.85 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00460F90@Rva00460F90@@QAEXXZ retail 0x00460F90..0x00461257 711B.
// WorldBuilder twin 0x010AC140 is DynamicPortalBehaviour::createWaypoints
// (DynamicPortalBehaviour.cpp asserts 202..238; string "#dynamicportal_wp").
// The receiver keeps the existing address-derived spelling: its only native
// caller 0x00461257 tail-jumps here with ECX unchanged.
// On first run it reads the BonePrefix bone positions of the object into a
// sixteen-entry Coord3D array; for every WayPoint entry it news a Waypoint
// (id 0x7ffffffe) at that bone position and stores it in the six-slot table
// at +0x24; it then marks the table built (+0x3C). For every Link entry
// (a vector of waypoint indices) it links first to last on the first run
// registers the first with the pathfinder (TheAI +0x10) and chains the
// intermediates.
// Module data offsets follow DynamicPortalBehaviourModuleDataCtor.cpp:
// +0x118 NumberOfBones +0x11C BonePrefix +0x120 WayPoint +0x12C Link
// +0x13D AllowEnemies +0x154 ActivationDelaySeconds +0x158 the timeout.
// The Link elements here are twelve bytes copied through the rowed
// vector<unsigned int> copy constructor 0x002CFAB9.
// Callees: Object::getMultiLogicalBonePosition 0x0028BF81; operator new
// 0x0002FDA0; Waypoint ctor 0x00282212; Waypoint::addLink 0x00272306;
// pathfinder AddPortal 0x002E8FE5; StringBase copies 0x000365F0/0x00037BA0.
// NEAR: same length; differs in spill-slot choice for the first-run locals
// and in the Link loop where retail keeps the copied vector's start in ESI
// across addLink/AddPortal and frees it with no null test (this draft
// reloads it from the frame and keeps the STLport null test).
#include "ascii_string.h"
#include <vector>
#include "../../../Common/GameLogicObjectLookupView.h"

// class-gate: allow Coord3D the bone-position array is built and torn down through BFME 2's out-of-line Coord3D constructor and destructor (the eh vector iterators push 0x0047A6A9 and 0x000B3FD0); the canonical data-only header cannot declare them; same three floats
struct Coord3D
{
	float x, y, z;
	Coord3D();
	Coord3D(const Coord3D &that) { x = that.x; y = that.y; z = that.z; }
	~Coord3D() {}
};

class Matrix3D;

class Object
{
public:
	int getMultiLogicalBonePosition(const char *boneNamePrefix, int maxBones, Coord3D *positions, Matrix3D *transforms, bool convertToWorld, int flags) const;

	char m_pad00[0x74];
	int m_74; // +0x74
};

class Waypoint
{
public:
	Waypoint(unsigned int id, AsciiString name, const Coord3D *pos, AsciiString label1, AsciiString label2, AsciiString label3, bool biDirectional, int type, AsciiString extra);
	void addLink(Waypoint *other);
	void setNext(Waypoint *next) { m_next = next; }

	char m_pad00[0x44];
	Waypoint *m_next; // +0x44
	bool m_48; // +0x48
	char m_pad49[0xA8 - 0x49];
	bool m_allowEnemies; // +0xA8
	char m_padA9[0xB0 - 0xA9];
	int m_ownerID; // +0xB0
	unsigned int m_activationFrame; // +0xB4
	bool m_portal; // +0xB8
	char m_padB9[3];
	int m_timeout; // +0xBC
};

class Rva002E9042
{
public:
	void rva002E8FE5(void *waypoint);
};

class AI
{
public:
	char m_pad00[0x10];
	Rva002E9042 *m_pathfinder; // +0x10
};

extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;

struct DynamicPortalWayPoint
{
	int m_bone;
	int m_type;
};

typedef _STL::vector<unsigned int> DynamicPortalLinkList;

struct Rva00460F90Data
{
	char m_pad00[0x118];
	int m_numberOfBones; // +0x118
	AsciiString m_bonePrefix; // +0x11C
	_STL::vector<DynamicPortalWayPoint> m_wayPoint; // +0x120
	_STL::vector<DynamicPortalLinkList> m_link; // +0x12C
	char m_pad138[0x13D - 0x138];
	bool m_allowEnemies; // +0x13D
	char m_pad13E[0x154 - 0x13E];
	float m_activationDelaySeconds; // +0x154
	int m_timeout; // +0x158
};

class Rva00460F90
{
public:
	void rva00460F90();

private:
	void *m_vtable;
	const Rva00460F90Data *m_moduleData; // +0x04
	Object *m_object; // +0x08
	char m_pad0C[0x24 - 0x0C];
	Waypoint *m_waypoints[6]; // +0x24
	bool m_created; // +0x3C
};

void Rva00460F90::rva00460F90()
{
	Coord3D locations[16];
	Object *obj = m_object;
	const Rva00460F90Data *data = m_moduleData;
	bool alreadyCreated = m_created;
	if (!m_created)
	{
		obj->getMultiLogicalBonePosition(data->m_bonePrefix.str(), data->m_numberOfBones, locations, 0, true, 0);
		unsigned int activationFrame = 0;
		if (data->m_activationDelaySeconds > 0.0f)
		{
			activationFrame = (int)(g_Va00DBA4E4 * data->m_activationDelaySeconds);
			activationFrame += TheGameLogic->getFrame();
		}
		int ownerID = m_object->m_74;
		int index = 0;
		for (const DynamicPortalWayPoint *it = data->m_wayPoint.begin(); it != data->m_wayPoint.end(); ++it, ++index)
		{
			const DynamicPortalWayPoint &entry = *it;
			Coord3D pos = locations[entry.m_bone];
			Waypoint *wp = new Waypoint(0x7ffffffe, AsciiString("#dynamicportal_wp"), &pos, AsciiString::TheEmptyString, AsciiString::TheEmptyString, AsciiString::TheEmptyString, false, entry.m_type, AsciiString::TheEmptyString);
			wp->m_ownerID = ownerID;
			wp->m_portal = true;
			wp->m_timeout = data->m_timeout;
			wp->m_allowEnemies = data->m_allowEnemies;
			if (activationFrame > 0)
				wp->m_activationFrame = activationFrame;
			m_waypoints[index] = wp;
		}
		m_created = true;
	}
	for (const DynamicPortalLinkList *lit = data->m_link.begin(); lit != data->m_link.end(); ++lit)
	{
		DynamicPortalLinkList link = *lit;
		int count = link.size();
		unsigned int first = link[0];
		unsigned int last = link[count - 1];
		if (!alreadyCreated)
			m_waypoints[first]->addLink(m_waypoints[last]);
		TheAI->m_pathfinder->rva002E8FE5(m_waypoints[first]);
		if (!alreadyCreated)
		{
			count = link.size() - 2;
			for (int i = 0; i < count; ++i)
			{
				unsigned int a = link[i];
				unsigned int b = link[i + 1];
				m_waypoints[b]->m_48 = false;
				m_waypoints[a]->setNext(m_waypoints[b]);
			}
		}
	}
}
