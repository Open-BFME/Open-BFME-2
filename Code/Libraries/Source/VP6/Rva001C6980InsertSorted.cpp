// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c6980.md plus retail only.
// ?Rva001C6980InsertSorted@@YAXPAUVp6SortRecord@@HPAH@Z retail
// 0x001C6980..0x001C69D8 (88 bytes) (spec name InsertSorted). MSVC gives
// the static helper its private convention: ESI = 12-byte sort record array
// (successor index / weight / edge) and EDX = index of the record to insert
// with the list head pointer on the stack as the spec states. Inserts into
// the singly linked list kept in ascending weight order: the walk stops at
// the end marker -1 or at the first record at least as heavy (signed
// compare) so the new record precedes equal weights. Stopping at the head
// makes the record the new head written back through the pointer.
// Retail holds no direct caller.
struct Vp6SortRecord { int next; int weight; int edge; };
static void Rva001C6980InsertSorted(Vp6SortRecord *list, int index, int *head)
{
	int prev = *head;
	int cur = *head;
	while (cur != -1) {
		if (list[index].weight <= list[cur].weight)
			break;
		prev = cur;
		cur = list[cur].next;
	}
	if (cur == *head) {
		*head = index;
		list[index].next = cur;
	} else {
		list[prev].next = index;
		list[index].next = cur;
	}
}
// C++ integration entry absent from retail. Keeping the helper static gives
// MSVC its private ESI/EDX convention; only the 88-byte helper is claimed.
void InsertVp6SortRecord(Vp6SortRecord *list, int index, int *head) { Rva001C6980InsertSorted(list, index, head); }
