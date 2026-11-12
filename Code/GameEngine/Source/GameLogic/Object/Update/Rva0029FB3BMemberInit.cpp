// cl: /DNDEBUG /MD
//
// ?init@Rva0029FB3BMember@@QAEPAXPAX@Z, retail 0x0029FB3B, 40 bytes.
// Freelist-node member init shared by 7 behavior ctors (ArrowStorm,
// DamageField, RousingSpeech, GloriousCharge and sibs): constructs the
// allocator proxy at this, pops a node from the pool object at
// 0xDA60E8, links it into a circular sentinel and returns this. The
// incoming context argument is unused (retail dead arg kept for the
// callers). The pool container itself is unidentified so the member
// keeps its honest Rva address name.

#include "../../../../Include/Common/FreelistProxyHead.h"

#include "../../../../Include/Common/FreelistPool.h"

#include "../../../../Include/GameLogic/Module/Rva0029FB3BMember.h"

extern FreelistPool g_freelistPool;
// The free-list head is the +8 member of the complete pool at VA 0xDA60E8.
class FreelistPool;
extern FreelistPool g_freelistPool;
#define g_freeList (*(void **)((char *)&g_freelistPool + 8))

// ?init@Rva0029FB3BMember@@QAEPAXPAX@Z @0x0029FB3B
void *Rva0029FB3BMember::init(void *context)
{
	(void)context;
	char dummyAlloc;
	((FreelistProxyHead *)this)->setup(&dummyAlloc, 0);
	void *node = g_freelistPool.pop();
	((void **)node)[0] = node;
	((void **)node)[1] = node;
	m_head = node;
	return this;
}

// ?reset@Rva0029FB3BMember@@QAEXXZ @0x0026549E
void Rva0029FB3BMember::reset()
{
	void *node = ((void **)m_head)[0];
	if (node != m_head) {
		do {
			void *freeHead = g_freeList;
			void *current = node;
			node = ((void **)current)[0];
			((void **)current)[0] = freeHead;
			g_freeList = current;
		} while (node != m_head);
	}
	((void **)m_head)[0] = m_head;
	((void **)m_head)[1] = m_head;
}

// ?g_freeList@@3PAXA: matched references place it at VA 0xda60f0; also referenced as ?g_pool009A60F0@@3PAUPoolNode002ABB20@@A.

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?init@Rva0029FB3BMember@@QAEXPAX@Z=?init@Rva0029FB3BMember@@QAEPAXPAX@Z")
