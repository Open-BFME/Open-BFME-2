// cl: /DNDEBUG /MD /EHsc
//
// ?rva002655E3@Path@@QAEXPBUCoord3D@@W4PathfindLayerEnum@@H@Z, retail 0x002655E3 (132 bytes). Path tail append with duplicate-position
// guard and waypoint-ID store. Donor: BFME1 AIPathfind.cpp Path::appendNode
// plus PathNodeInsertion.cpp layout (head +4 tail +8 optimized +0xC,
// node next +0 prev +4 nextOpti +8 pos +0xC layer +0x18 waypoint +0x20).
// Callers construct Path via 0x363DC8 then call here with (pos, LAYER_GROUND,
// 0x7fffffff); pool global at 0x00A01E94, PathNode ctor at 0x0026212A.

#include <new>

typedef int Int;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class PathNode
{
public:
	PathNode(const Coord3D *position, PathfindLayerEnum layer) throw();

	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_waypointID;
};

class Rva00065964ObjectPool
{
public:
	void *rva002635C2() throw();
};

extern Rva00065964ObjectPool g_pathNodePool;

class Path
{
public:
	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, int waypointID);

private:
	char m_pad00[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
};

void Path::rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, int waypointID)
{
	if (m_isOptimized && m_pathTail)
	{
		if (pos->x == m_pathTail->m_position.x && pos->y == m_pathTail->m_position.y)
			return;
	}
	void *mem = g_pathNodePool.rva002635C2();
	PathNode *node = mem ? new (mem) PathNode(pos, layer) : 0;
	node->m_waypointID = waypointID;
	PathNode *tail = m_pathTail;
	if (tail)
	{
		tail->m_next = node;
		node->m_previous = tail;
	}
	if (m_isOptimized && m_pathTail)
		m_pathTail->m_nextOptimized = node;
	m_pathTail = node;
	if (m_path == 0)
		m_path = node;
}
