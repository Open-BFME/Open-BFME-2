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

struct Rva003642DFNode;
#include "../../../Include/GameLogic/Rva003642DFResult.h"

#include "../../../Include/GameLogic/Rva0008BB38FloatField.h"

#include "../../../Include/GameLogic/PathNode.h"

#include "../../../../Libraries/Source/WWVegas/WWLib/bfme_pool_critical_section.h"

// Retail's pool is 0x14 bytes (0x00A01E94): the allocator 0x002635C2 reads the free list at +0, the
// block list at +4, the counts at +8 and +0xC, and locks +0x10. No constructor: retail's storage is
// zero-filled and only the atexit destructor thunk (0x007B7CD7) touches it outside the users.
class Rva00065964ObjectPool
{
public:
	void *rva002635C2() throw();

	void *m_freeListHead;
	void *m_blockListHead;
	int m_freeObjectCount;
	int m_totalObjectCount;
	BFMEPoolCriticalSection m_lock10;
};

// g_pathNodePool: matched references place it at VA 0xe01e94 (zero-filled).
Rva00065964ObjectPool g_pathNodePool;

#include "../../../Include/GameLogic/PathfindPath.h"


void Path::rva003649B1(const PathNode *pathNode)
{
	if (m_isOptimized && m_pathTail) {
		if (pathNode->m_pos.x == m_pathTail->m_pos.x && pathNode->m_pos.y == m_pathTail->m_pos.y)
			return;
	}
	void *mem = g_pathNodePool.rva002635C2();
	PathNode *node = mem ? new (mem) PathNode(&pathNode->m_pos, pathNode->m_layer) : 0;
	node->m_portalID = pathNode->m_portalID;
	PathNode *tail = m_pathTail;
	if (tail) {
		tail->m_next = node;
		node->m_prev = tail;
	}
	if (m_isOptimized && m_pathTail)
		m_pathTail->m_nextOpti = node;
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
