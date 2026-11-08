// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?setPathFromWaypoint@AIUpdateInterface@@QAEXPBVWaypoint@@PBVCoord2D@@@Z,
// retail 0x0026569F..0x002657CE (303 bytes, EH, RET 8): Zero Hour's
// AIUpdateInterface::setPathFromWaypoint (AIUpdate.cpp) in its BFME 2 form,
// the spelling its caller AIFollowWaypointPathExactState::onEnter pinned.
// The path is a plain new Path (rowed constructor) rather than a pool
// instance, its nodes carry a third 0x7FFFFFFF argument (rowed prepend /
// append 0x00265596 / 0x002655E3), the end-of-path snap is the rowed static
// 0x002EDE5B, and the wake-up runs unconditionally (rowed wakeUpNow).
// Layout: the object at +0x08 (position +0x38), m_path +0x140,
// m_waitingForPath +0x3B1; waypoint location +0x0C, first link +0x20;
// TheAI's pathfinder at +0x10 (rowed SetDebugPath).

#include "Coord3D.h"
#include "Coord2D.h"

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

enum { WAYPOINT_PATH_LIMIT = 1024 };

#include "../../../../Include/GameLogic/PathfindPath.h"

#include "../../../../Include/GameLogic/Waypoint.h"

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;						// +0x38
};

int Rva002EDE5B(void *obj, Coord3D *pos);

struct Rva002EDEABArg;

#include "../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../Include/GameLogic/AI.h"

extern AI *TheAI;

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::setPathFromWaypoint(const Waypoint *way, const Coord2D *offset)
{
	destroyPath();
	m_path = new Path;
	Coord3D pos;
	const Coord3D *objPos = getObject()->getPosition();
	pos.x = objPos->x;
	pos.y = objPos->y;
	pos.z = objPos->z;
	m_path->prependNode(&pos, LAYER_GROUND, 0x7FFFFFFF);
	m_path->markOptimized();
	int count = 0;
	while (way)
	{
		Coord3D wayPos;
		const Coord3D *loc = way->getLocation();
		wayPos.x = loc->x;
		wayPos.y = loc->y;
		wayPos.z = loc->z;
		wayPos.x += offset->x;
		wayPos.y += offset->y;
		if (way->m_links[0] == 0)
			Rva002EDE5B(getObject(), &wayPos);
		m_path->appendNode(&wayPos, LAYER_GROUND, 0x7FFFFFFF);
		way = way->m_links[0];
		count++;
		if (count > WAYPOINT_PATH_LIMIT)
			break;
	}
	m_field3B1 = false;
	TheAI->pathfinder()->SetDebugPath((Rva002EDEABArg *)m_path);
	wakeUpNow();
}
