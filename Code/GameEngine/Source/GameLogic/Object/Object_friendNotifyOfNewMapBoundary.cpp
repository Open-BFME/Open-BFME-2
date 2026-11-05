// cl: /Oy- /DNDEBUG /MD /EHsc
//
// ?friend_notifyOfNewMapBoundary@Object@@QAEXXZ,
// retail 0x0028B5EE, 113 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Object.cpp,
// Object::friend_notifyOfNewMapBoundary): re-adds itself to the radar
// (Radar::addObject), adds to the pathfind map, refreshes the map extent,
// then sets or clears OFF_MAP from the in-region test. Retail keeps the world
// position at +0x38 and the private status byte at +0x438; the in-region test
// inlines to four SSE compares.


typedef float Real;
typedef int Int;
typedef unsigned char UnsignedByte;
typedef int Bool;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../Libraries/Include/Lib/Region3D.h"

// Forced-inline no-Z containment test (the canonical member is plain inline;
// retail inlines this test here and emits no out-of-line copy).
static __forceinline Bool regionContainsNoZ(const Region3D &region, const Coord3D *query)
{
	return (region.lo.x < query->x) && (query->x < region.hi.x)
		&& (region.lo.y < query->y) && (query->y < region.hi.y);
}

class Object;

#include "../../../Include/Common/Radar.h"

#include "../../../Include/GameLogic/AIPathfind.h"

#include "../../../Include/GameLogic/AI.h"

#include "../../../Include/GameLogic/TerrainLogic.h"

extern Radar *TheRadar;
extern TerrainLogic *TheTerrainLogic;

#include "object.h"

enum ObjectPrivateStatus
{
	OFF_MAP = 1 << 3
};

// ?friend_notifyOfNewMapBoundary@Object@@QAEXXZ
void Object::friend_notifyOfNewMapBoundary()
{
	TheRadar->addObject(this);
	TheAI->m_pathfinder->AddObjectToPathfindMap(this);

	Region3D mapExtent;
	TheTerrainLogic->getExtent(&mapExtent);
	if (regionContainsNoZ(mapExtent, getPosition()))
		m_privateStatus &= ~OFF_MAP;
	else
		m_privateStatus |= OFF_MAP;
}
