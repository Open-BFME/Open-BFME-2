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
#include "../../../Include/GameLogic/PathNode.h"

class Rva00263404Product;
#include "../../../Include/GameLogic/PathfindPath.h"

// WorldBuilder Path::SpliceAndPrepend, WB VA 0x00F25F50 (callgraph lead, score 2).
void Path::SpliceAndPrepend(Rva00263404Product *product)
{
	Path *other = (Path *)product;
	if (!other)
		return;
	PathNode *otherTail = other->m_pathTail;
	if (!otherTail) {
		delete other;
		return;
	}
	if (!DoAdvanceAlongPath(&otherTail->m_pos, false)) {
		delete other;
		return;
	}
	while (m_path != field_10) {
		PathNode *next = m_path->m_next;
		delete m_path;
		m_path = next;
	}
	PathNode *next = field_10->m_next;
	other->m_pathTail->m_nextOpti = next;
	other->m_pathTail->m_next = next;
	next->m_prev = other->m_pathTail;
	delete m_path;
	m_path = other->m_path;
	other->m_path = 0;
	delete other;
	field_10 = m_path;
	field_14 = 0.0f;
}
