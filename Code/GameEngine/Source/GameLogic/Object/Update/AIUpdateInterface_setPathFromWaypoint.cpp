// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?setPathFromWaypoint@AIUpdateInterface@@QAEXPBVWaypoint@@PBUCoord2D@@@Z,
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

struct Coord2D;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

enum { WAYPOINT_PATH_LIMIT = 1024 };

class Path
{
public:
	Path();
	void rva00265596(const Coord3D *pos, PathfindLayerEnum layer, int extra);	// prependNode
	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, int extra);	// appendNode
	void markOptimized() { m_isOptimized = true; }
private:
	unsigned char m_pad00[0x0C];
	bool m_isOptimized;						// +0x0C
	unsigned char m_pad0D[0x28 - 0x0D];
};

class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }
	Waypoint *getLink(int) const { return m_link0; }
private:
	unsigned char m_pad00[0x0C];
	Coord3D m_location;						// +0x0C
	unsigned char m_pad18[0x20 - 0x18];
	Waypoint *m_link0;						// +0x20
};

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

class Pathfinder
{
public:
	void SetDebugPath(Rva002EDEABArg *path);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;				// +0x10
};

extern AI *TheAI;

// The offset is read as its two leading floats.
struct Rva0026569FOffset
{
	float x, y;
};

class AIUpdateInterface
{
public:
	void destroyPath();
	void setPathFromWaypoint(const Waypoint *way, const Coord2D *offset);
protected:
	void wakeUpNow();
	Object *getObject() const { return m_object; }
private:
	unsigned char m_pad00[0x08];
	Object *m_object;						// +0x08
	unsigned char m_pad0C[0x140 - 0x0C];
	Path *m_path;							// +0x140
	unsigned char m_pad144[0x3B1 - 0x144];
	bool m_waitingForPath;					// +0x3B1
};

void AIUpdateInterface::setPathFromWaypoint(const Waypoint *way, const Coord2D *offset)
{
	destroyPath();
	m_path = new Path;
	Coord3D pos;
	const Coord3D *objPos = getObject()->getPosition();
	pos.x = objPos->x;
	pos.y = objPos->y;
	pos.z = objPos->z;
	m_path->rva00265596(&pos, LAYER_GROUND, 0x7FFFFFFF);
	m_path->markOptimized();
	int count = 0;
	while (way)
	{
		Coord3D wayPos;
		const Coord3D *loc = way->getLocation();
		wayPos.x = loc->x;
		wayPos.y = loc->y;
		wayPos.z = loc->z;
		wayPos.x += ((const Rva0026569FOffset *)offset)->x;
		wayPos.y += ((const Rva0026569FOffset *)offset)->y;
		if (way->getLink(0) == 0)
			Rva002EDE5B(getObject(), &wayPos);
		m_path->rva002655E3(&wayPos, LAYER_GROUND, 0x7FFFFFFF);
		way = way->getLink(0);
		count++;
		if (count > WAYPOINT_PATH_LIMIT)
			break;
	}
	m_waitingForPath = false;
	TheAI->pathfinder()->SetDebugPath((Rva002EDEABArg *)m_path);
	wakeUpNow();
}
