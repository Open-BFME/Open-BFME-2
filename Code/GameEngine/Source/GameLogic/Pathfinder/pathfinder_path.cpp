// cl: /O1 /arch:SSE /MD /DNDEBUG
// Retail [0x00365DF0,0x00365E98): prepend the supplied path after advancing
// this path to its tail position, reclaiming replaced nodes and transferring
// ownership before deleting the supplied Path. WB 0x00F25F50 names this
// operation SpliceAndPrepend. The current provider spelling and opaque
// argument type are retained for its already matched AIUpdate caller.
// The member offsets and node links come from retail, agreeing with
// PathCtor/PathDtor and the matched portal/node accessors. BFME1's reference
// pathfinder_path.cpp confirms the three node links and coordinate layout;
// the splice operation itself is target-specific.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
void __cdecl FreePooledNode(void *);

struct PathNode
{
	~PathNode() {}
	void operator delete(void *node) { FreePooledNode(node); }
	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
};

class Rva00263404Product;
class Path
{
public:
	~Path();
	bool rva00363930(Coord3D *position, bool stopAtPortal);
	void rva00365DF0(Rva00263404Product *product);
private:
	void *m_unknown00;
	PathNode *m_path;
	PathNode *m_pathTail;
	bool m_isOptimized;
	bool m_unknown0D;
	PathNode *m_selected;
	float m_distance;
};

void Path::rva00365DF0(Rva00263404Product *product)
{
	Path *other = (Path *)product;
	if (!other)
		return;
	PathNode *otherTail = other->m_pathTail;
	if (!otherTail) {
		delete other;
		return;
	}
	if (!rva00363930(&otherTail->m_position, false)) {
		delete other;
		return;
	}
	while (m_path != m_selected) {
		PathNode *next = m_path->m_next;
		delete m_path;
		m_path = next;
	}
	PathNode *next = m_selected->m_next;
	other->m_pathTail->m_nextOptimized = next;
	other->m_pathTail->m_next = next;
	next->m_previous = other->m_pathTail;
	delete m_path;
	m_path = other->m_path;
	other->m_path = 0;
	delete other;
	m_selected = m_path;
	m_distance = 0.0f;
}
