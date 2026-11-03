// cl: /DNDEBUG /MD /EHsc
//
// ?PathfindCell::ReleaseClosedList (retail 0x0052DE9B, 56 bytes): walks a MixFileInfoBuffer
// list via +0x34, unlinks each node, clears 0x10 at +0x2c and calls
// PathfindCell::ReleaseInfo on the state at +0x30 when present, returning the
// node count. Callees are declared-only so the gate resolves them; the
// do-while with next prefetch reproduces retail's edi/esi allocation. Evidence:
// sole caller at 0x002F40FC pushes [esi+0x34] and accumulates eax into
// [esi+0x44]; callee ?bfmeUnlink@MixFileInfoBuffer@@AAEXXZ proves the walked
// type is MixFileInfoBuffer, and ?ReleaseInfo@PathfindCell@@QAEXXZ is rowed.

#include "../../Include/GameLogic/PathfindCell.h"
#include "../../Include/Common/MixFileInfoBuffer.h"

// WorldBuilder PathfindCell::ReleaseClosedList, WB VA 0x012D7F30 (callgraph lead, score 1.0).
int PathfindCell::ReleaseClosedList(MixFileInfoBuffer *head)
{
	if (head == 0)
		return 0;
	int count = 0;
	MixFileInfoBuffer *next = head;
	do
	{
		MixFileInfoBuffer *cur = next;
		next = next->field34;
		++count;
		cur->bfmeUnlink();
		PathfindCell *state = cur->field30;
		cur->m_flags &= ~0x10u;
		if (state != 0)
			state->ReleaseInfo();
	} while (next != 0);
	return count;
}
