// cl: /O1 /DNDEBUG /MD /GX
// ?Rva003320B0PopHeap@@YAXPAUS4SortElem12@@0US4Cmp002E0CD0@@@Z @0x003320B0 23B
// S4 pop_heap 3-arg forwarder over rowed 0x00331E80 (which supplies unused=0).
// Evidence: chain lane calls 0x00331E80 row; 4 pushes (first,last,0,comp) plus add esp,0x10 plus ret; caller 0x003321B9; neighbours Rva002DFC30Destroy /O1 and RvaVectorDtorFamily /O1.
struct S4SortElem12
{
	char m_pad[12];
};
struct S4Cmp002E0CD0
{
	void *m_state;
};

void __cdecl Rva00331E80PopHeap(S4SortElem12 *first, S4SortElem12 *last, int unused, S4Cmp002E0CD0 comp);

void __cdecl Rva003320B0PopHeap(S4SortElem12 *first, S4SortElem12 *last, S4Cmp002E0CD0 comp)
{
	Rva00331E80PopHeap(first, last, 0, comp);
}

void __cdecl Rva00332197SortHeap(S4SortElem12 *first, S4SortElem12 *last, S4Cmp002E0CD0 comp)
{
	while (last - first > 1)
	{
		Rva003320B0PopHeap(first, last, comp);
		--last;
	}
}
