// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva00265596@Path@@QAEXPBUCoord3D@@W4PathfindLayerEnum@@H@Z, retail 0x00265596 (77 bytes). Path head prepend
// with waypoint-ID store. Donor: BFME1 AIPathfind.cpp Path::prependNode plus PathNodeInsertion.cpp layout
// (head +4 tail +8 optimized +0xC, node next +0 prev +4 nextOpti +8 pos +0xC layer +0x18 waypoint +0x20).
// Callers pass (pos, LAYER_GROUND, id); pool global at 0x00A01E94, PathNode ctor at 0x0026212A,
// link helper ?set@Rva0026E4A0@@QAEAAV1@PAV1@@Z at 0x00262161.

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

class Rva0026E4A0
{
public:
	Rva0026E4A0 &set(Rva0026E4A0 *p) throw();
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
	void rva00265596(const Coord3D *pos, PathfindLayerEnum layer, int waypointID);

private:
	char m_pad00[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
};

void Path::rva00265596(const Coord3D *pos, PathfindLayerEnum layer, int waypointID)
{
	void *mem = g_pathNodePool.rva002635C2();
	PathNode *node = mem ? new (mem) PathNode(pos, layer) : 0;
	node->m_waypointID = waypointID;
	m_path = (PathNode *)&((Rva0026E4A0 *)node)->set((Rva0026E4A0 *)m_path);
	if (m_pathTail == 0)
		m_pathTail = node;
	m_isOptimized = false;
}
