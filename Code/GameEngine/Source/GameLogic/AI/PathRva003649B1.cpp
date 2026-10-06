// cl: /DNDEBUG /MD
// ?rva003649B1@Path@@QAEXPBVPathNode@@@Z @0x003649B1 134B via Path append donor
// Evidence: duplicate-position guard via ucomiss on +0xc/+0x10 vs tail; pool g_pathNodePool allocate plus rowed PathNode ctor with arg+0xc/layer+0x18 plus waypoint+0x20; linking head+4 tail+8 optimized+0xc matches PathAppendNode.
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

// g_pathNodePool: matched references place it at VA 0xe01e94 (zero-filled; a plain-data view).
Rva00065964ObjectPool g_pathNodePool;

class Path
{
public:
	void rva003649B1(const PathNode *arg);

private:
	char m_pad00[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
};

void Path::rva003649B1(const PathNode *arg)
{
	if (m_isOptimized && m_pathTail) {
		if (arg->m_position.x == m_pathTail->m_position.x && arg->m_position.y == m_pathTail->m_position.y)
			return;
	}
	void *mem = g_pathNodePool.rva002635C2();
	PathNode *node = mem ? new (mem) PathNode(&arg->m_position, arg->m_layer) : 0;
	node->m_waypointID = arg->m_waypointID;
	PathNode *tail = m_pathTail;
	if (tail) {
		tail->m_next = node;
		node->m_previous = tail;
	}
	if (m_isOptimized && m_pathTail)
		m_pathTail->m_nextOptimized = node;
	m_pathTail = node;
	if (m_path == 0)
		m_path = node;
}
