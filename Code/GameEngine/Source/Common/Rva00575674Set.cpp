// cl: /MD
// ?rva00575674@Rva00575674@@QAEXPAVObject@@@Z @0x00575674 (38B):
// Pooled-object setter with self-assign guard: if (p == m_ptr) return;
// old = m_ptr; m_ptr = p; toFree = old ? old->deleteInstance(0) : 0;
// ::operator delete(toFree) via rowed ??3@YAXPAX@Z @0x0002FD60. Slot0 virtual
// takes int flags (push 0). Callers 40+ (0x000AF31A etc); unblocks 74.
// Honest-address name.

class Object
{
public:
	virtual void *deleteInstance(int flags);
};

#include "../../Include/Common/Rva00575674.h"

void Rva00575674::rva00575674(Object *object)
{
	if (object == m_ptr)
		return;
	Object *old = m_ptr;
	m_ptr = object;
	Object *toFree = old ? (Object *)old->deleteInstance(0) : (Object *)0;
	::operator delete(toFree);
}
