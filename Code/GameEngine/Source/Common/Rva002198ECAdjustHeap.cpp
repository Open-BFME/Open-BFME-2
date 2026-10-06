// cl: /MD
// ?Rva002198ECAdjustHeap@@YAXPAPAXHHPAXP6A_N11@Z@Z @0x002198EC 91B
// __adjust_heap for 4-byte entries: percolate hole down then tail-call __push_heap.
// Evidence: packet disassembly matches STL __adjust_heap shape; calls rowed
// ?Rva0021956EPushHeap at 0x0021956E with (first,hole,top,value,comp); stride 4.
typedef bool (__cdecl *HeapLess)(void *a, void *b);

void __cdecl Rva0021956EPushHeap(void **first, int holeIndex, int topIndex, void *value, HeapLess comp);

void __cdecl Rva002198ECAdjustHeap(void **first, int holeIndex, int len, void *value, HeapLess comp)
{
	int topIndex = holeIndex;
	int secondChild = holeIndex + holeIndex + 2;
	while (secondChild < len) {
		if (comp(first[secondChild], first[secondChild - 1]))
			--secondChild;
		first[holeIndex] = first[secondChild];
		holeIndex = secondChild;
		secondChild += secondChild + 2;
	}
	if (secondChild == len) {
		first[holeIndex] = first[secondChild - 1];
		holeIndex = secondChild - 1;
	}
	Rva0021956EPushHeap(first, holeIndex, topIndex, value, comp);
}
// ?Rva0021AD03MakeHeap@@YAXPAPAX0P6A_NPAX1@Z@Z @0x0021AD03 60B
// make_heap over 4-byte entries via rowed __adjust_heap 0x002198EC; caller
// 0x002C532B; same HeapLess comp.
void __cdecl Rva0021AD03MakeHeap(void **first, void **last, HeapLess comp)
{
	int len = last - first;
	if (len < 2)
		return;
	for (int i = (len - 2) / 2; ; --i) {
		Rva002198ECAdjustHeap(first, i, len, first[i], comp);
		if (i == 0)
			break;
	}
}
// ?Rva002C52E0PopHeap@@YAXPAPAX00PAXP6A_N11@Z@Z @0x002C52E0 41B
// __pop_heap over 4-byte entries: move *first to *result then rowed
// __adjust_heap 0x002198EC with hole 0; callers 0x0021AD54 0x0021D353 0x002C5666.
void __cdecl Rva002C52E0PopHeap(void **first, void **last, void **result, void *value, HeapLess comp)
{
	void *tmp = *first;
	*result = tmp;
	Rva002198ECAdjustHeap(first, 0, last - first, value, comp);
}
// ?Rva002C531BWrap@@YAXPAPAX0P6A_NPAX1@Z@Z @0x002C52E0+? no: 0x002C531B 25B
// make_heap forwarding wrapper: pushes two trailing zeros alongside
// (first,last,comp) into rowed worker 0x0021AD03; callers 0x0021D32D 0x002C5640.
void __cdecl Rva002C531BWrap(void **first, void **last, HeapLess comp)
{
	typedef void (__cdecl *MakeHeap5)(void **, void **, HeapLess, int, int);
	((MakeHeap5)Rva0021AD03MakeHeap)(first, last, comp, 0, 0);
}
// ?Rva0021AD3FPopHeap@@YAXPAPAX0HP6A_NPAX1@Z@Z @0x0021AD3F 30B
// pop_heap wrapper over rowed __pop_heap 0x002C52E0: last-1 as result/value
// plus trailing zero; caller 0x0021BB0A; same HeapLess comp.
void __cdecl Rva0021AD3FPopHeap(void **first, void **last, int, HeapLess comp)
{
	typedef void (__cdecl *PopHeap6)(void **, void **, void **, void *, HeapLess, int);
	void **newLast = last - 1;
	((PopHeap6)Rva002C52E0PopHeap)(first, newLast, newLast, *newLast, comp, 0);
}
// ?Rva0021BAFCPopHeap@@YAXPAPAX0P6A_NPAX1@Z@Z @0x0021BAFC 23B
// pop_heap forwarding wrapper over rowed 0x0021AD3F: forwards (first,last)
// plus trailing zero and comp. Callers 0x0021C85D/0x002C5575. Same HeapLess.
void __cdecl Rva0021BAFCPopHeap(void **first, void **last, HeapLess comp)
{
	Rva0021AD3FPopHeap(first, last, 0, comp);
}
