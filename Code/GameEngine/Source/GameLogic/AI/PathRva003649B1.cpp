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

#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct Rva003642DFNode;
struct Rva003642DFResult
{
	Rva003642DFResult();
	Rva003642DFNode *m_node;
	Coord3D m_pos;
};

class Rva0008BB38FloatField
{
public:
	Real get() const;
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

#include "../../../Include/GameLogic/PathfindPath.h"


void Path::rva003649B1(const PathNode *pathNode)
{
	if (m_isOptimized && m_pathTail) {
		if (pathNode->m_position.x == m_pathTail->m_position.x && pathNode->m_position.y == m_pathTail->m_position.y)
			return;
	}
	void *mem = g_pathNodePool.rva002635C2();
	PathNode *node = mem ? new (mem) PathNode(&pathNode->m_position, pathNode->m_layer) : 0;
	node->m_waypointID = pathNode->m_waypointID;
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

// ?rva0026547E@@YAPAXXZ @0x0026547E 10B: allocation thunk over g_pathNodePool
// (mov ecx, offset pool; tail jump to its rowed allocate 0x002635C2), the
// shape of the pooled path node's operator new. Address-named; no referencing
// site was found in this pass.
void *rva0026547E()
{
	return g_pathNodePool.rva002635C2();
}
