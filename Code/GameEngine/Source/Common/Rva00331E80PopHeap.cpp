// cl: /Ireference/shims/bfme2_ascii /O1 /MD /Oy-
#include "ascii_string.h"
// ?Rva00331E80PopHeap@@YAXPAUS4SortElem12@@0HUS4Cmp002E0CD0@@@Z @0x00331E80 45B
// S4 pop_heap wrapper via rowed Bfme copy and rowed PopHeap.
// Evidence: unlock lane unblocks 0x003320B0; callees rowed; caller pushes 4 args.
struct S4SortElem12
{
	int m_a;
	AsciiString m_name;
	char m_flag;
};

struct S4Cmp002E0CD0
{
	void *m_state;
};

void __cdecl Rva002E0BC0PopHeap(S4SortElem12 *first, S4SortElem12 *last, S4SortElem12 *result, S4SortElem12 value, S4Cmp002E0CD0 comp, int *x) throw();

void __cdecl Rva00331E80PopHeap(S4SortElem12 *first, S4SortElem12 *last, int unused, S4Cmp002E0CD0 comp)
{
	Rva002E0BC0PopHeap(first, last - 1, last - 1, *(last - 1), comp, 0);
}
