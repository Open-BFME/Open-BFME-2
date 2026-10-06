// cl: /MD
// ?Rva0021956EPushHeap@@YAXPAPAXHHPAXP6A_N11@Z@Z @0x0021956E 73B
// __push_heap for 4-byte entries: while hole>top && comp(parent,value) shift parent down.
// Evidence: packet disassembly matches STL __push_heap shape; caller 0x002198EC is
// __adjust_heap which tail-calls this with (first,hole,top,value,comp); element stride 4.
typedef bool (__cdecl *PushHeapLess)(void *a, void *b);

void __cdecl Rva0021956EPushHeap(void **first, int holeIndex, int topIndex, void *value, PushHeapLess comp)
{
	int parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && comp(first[parent], value)) {
		first[holeIndex] = first[parent];
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	first[holeIndex] = value;
}
