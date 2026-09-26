// cl: /O1 /DNDEBUG /MD

#define NULL 0

// Path node reclamation and teardown (GameLogic AI pathfinding). Nodes live
// in the Rva pool behind the global at 0x00E01E94 and are returned through
// its rowed FreeObject body; the local node type carries its next link at
// +0x0 (matching the rowed PathNode layout).

struct Rva00065964ObjectPool
{
	void FreeObject(void *obj);
};

extern Rva00065964ObjectPool g_pathNodePool;

struct PathNode
{
	PathNode *m_next;
};

class Path
{
	void *m_unknown00;
	PathNode *m_head04;

public:
	~Path();
};

// ?FreePooledNode@@YAXPAX@Z, retail 0x00265488, 22 bytes. Null-checked
// pool free: drops nulls, otherwise returns the node to the path pool.
void __cdecl FreePooledNode(void *node)
{
	if (node == NULL)
		return;
	g_pathNodePool.FreeObject(node);
}

// ??1Path@@QAE@XZ, retail 0x00364A89, 25 bytes. Walks the node list
// returning each node to the path pool.
Path::~Path()
{
	PathNode *node = m_head04;
	if (node == NULL)
		return;
	PathNode *next;
	do
	{
		next = node->m_next;
		FreePooledNode(node);
		node = next;
	} while (next != NULL);
}
