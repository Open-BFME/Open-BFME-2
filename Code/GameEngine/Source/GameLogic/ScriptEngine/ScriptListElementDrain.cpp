// cl: /DNDEBUG /MD /EHsc
//
// Element drain at 0x003B675B (47B): the twin of the rowed
// clearRva00359330Nodes at 0x003B578E, draining the node chain off a
// string record's +0x10 slot. Same plain while + delete source under
// /EHsc (the flag is load-bearing: it keeps the hoisted null-node test
// with its late branch and the delete cleanup before the bottom head
// check; /GX- schedules both differently). The node destructor here is
// the rowed ??1Rva003B448C at 0x003B448C (not the pinned BfmeNodeZ of
// the twin), reached through the declared-only dtor; delete lowers
// through a TU-local deleting-destructor emission plus the declared
// operator delete at 0x0002FD60.

#include <new>

class Rva003B448C
{
public:
	~Rva003B448C();

	Rva003B448C *m_next;
};

#include "../../../Include/GameLogic/Rva003B675BRecord.h"

// ?clearRva003B675BNodes@@YAXPAURva003B675BRecord@@@Z
void clearRva003B675BNodes(Rva003B675BRecord *record)
{
	while (record->m_nodes)
	{
		Rva003B448C *node = (Rva003B448C *)record->m_nodes;

		record->m_nodes = ((Rva003B448C *)record->m_nodes)->m_next;
		delete node;
	}
}
