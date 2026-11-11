// cl: /ICode /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
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
// Schedule note (W7-S2 r14): the three scheduling fences of the earlier drafts are replaced by ONE
// volatile read of the object pointer. A fence pins every memory operation including the stores the
// compiler creates itself (callee-save pushes, EH state, argument slots); the volatile read pins only
// the load that retail issues late. Textual cast on purpose: a template helper changes the IR.
#include "ascii_string.h"
#include <vector>
#include "GameEngine/Source/Common/GameLogicObjectLookupView.h"

#define COORD3D_VIEW_DTOR
#define COORD3D_VIEW_EXTERN_CTOR
#include "../../../../../Libraries/Include/Lib/Coord3DCtorView.h"

// Use the existing STLport allocator teardown. The native 711-byte loop
// remains exact; a private _Vector_base specialization emitted incompatible
// vector destructor copies and prevented this otherwise matched unit linking.

class Matrix3D;

#include "../object.h"

#include "../../../../Include/GameLogic/Waypoint.h"
static inline void setWaypointField44(Waypoint *way, Waypoint *next) { way->m_field44 = next; }

#include "../../../../Include/GameLogic/Module/Rva002E9042.h"

class AI
{
public:
	char m_pad00[0x10];
	Rva002E9042 *m_pathfinder; // +0x10
};

extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;

struct DynamicPortalWayPoint
{
public:
	int m_first; // +0x00
	int m_second; // +0x04
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

class DynamicPortalBehaviour
{
public:
	void createWaypoints();

private:
	void *m_vtable;
	const Rva00460F90Data *m_moduleData; // +0x04
	Object *m_object; // +0x08
	char m_pad0C[0x24 - 0x0C];
	Waypoint *m_waypoints[6]; // +0x24
	bool m_created; // +0x3C
};

void DynamicPortalBehaviour::createWaypoints()
{
	Coord3D locations[16];
	Object *obj = (*(Object * volatile *)&(m_object));
	const Rva00460F90Data *data = m_moduleData;
	bool alreadyCreated = m_created;
	if (!m_created)
	{
		obj->getMultiLogicalBonePosition(data->m_bonePrefix.str(), data->m_numberOfBones, locations, 0, true, 0);
		unsigned int activationFrame = 0;
		if (data->m_activationDelaySeconds > 0.0f)
		{
			activationFrame = (int)(BfmeLogicFramesPerSecond * data->m_activationDelaySeconds);
			activationFrame += TheGameLogic->getFrame();
		}
		int ownerID = m_object->m_id;
		int index = 0;
		for (const DynamicPortalWayPoint *it = data->m_wayPoint.begin(); it != data->m_wayPoint.end(); ++it, ++index)
		{
			const DynamicPortalWayPoint &entry = *it;
			Coord3D pos = locations[entry.m_first];
			Waypoint *wp = new Waypoint(0x7ffffffe, AsciiString("#dynamicportal_wp"), &pos, AsciiString::TheEmptyString, AsciiString::TheEmptyString, AsciiString::TheEmptyString, false, entry.m_second, AsciiString::TheEmptyString);
			wp->m_fieldB0 = ownerID;
			wp->m_fieldB8 = true;
			wp->m_fieldBC = data->m_timeout;
			wp->m_fieldA8 = data->m_allowEnemies;
			if (activationFrame > 0)
				wp->m_fieldB4 = activationFrame;
			m_waypoints[index] = wp;
		}
		m_created = true;
	}
	for (const DynamicPortalLinkList *lit = data->m_link.begin(); lit != data->m_link.end(); ++lit)
	{
		DynamicPortalLinkList link = *lit;
		
		const unsigned int *start = link.begin();
		int count = link.size();
		
		unsigned int first = start[0];
		unsigned int last = start[count - 1];
		
		if (!alreadyCreated)
			m_waypoints[first]->addLink(m_waypoints[last]);
		(alreadyCreated ? TheAI->m_pathfinder : TheAI->m_pathfinder)->AddPortal(m_waypoints[first]);
		if (!alreadyCreated)
		{
			const int limit = count - 2;
			for (int i = 0; i < limit; ++i)
			{
				unsigned int a = start[i];
				unsigned int b = start[i + 1];
				m_waypoints[b]->m_field48 = false;
				setWaypointField44(m_waypoints[a], m_waypoints[b]);
			}
		}
	}
}
