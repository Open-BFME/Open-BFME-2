// cl: /MD
// ?Rva002C5556SortHeap@@YAXPAPAX0P6A_NPAX1@Z@Z @0x002C5556 58B
// sort_heap over 4-byte entries via rowed pop_heap 0x0021BAFC; caller
// 0x002C567B; same HeapLess comp. /G7 for retail and-al encoding.
typedef bool (__cdecl *HeapLess)(void *a, void *b);

void __cdecl Rva0021BAFCPopHeap(void **first, void **last, HeapLess comp);

void __cdecl Rva002C531BWrap(void **first, void **last, HeapLess comp);
void __cdecl Rva002C52E0PopHeap(void **first, void **last, void **result, void *value, HeapLess comp);

void __cdecl Rva002C5556SortHeap(void **first, void **last, HeapLess comp)
{
	while ((((char *)last - (char *)first) & ~3) > 4) {
		Rva0021BAFCPopHeap(first, last, comp);
		--last;
	}
}
// ?Rva002C562FPartialSort@@YAXPAPAX00HP6A_NPAX1@Z@Z @0x002C562F 89B
// __partial_sort over 4-byte entries: rowed make_heap 0x002C531B then
// guarded __pop_heap 0x002C52E0 loop then rowed sort_heap 0x002C5556;
// caller 0x002C569A; unused int tag keeps comp at +0x18.
void __cdecl Rva002C562FPartialSort(void **first, void **middle, void **last, int, HeapLess comp)
{
	typedef void (__cdecl *PopHeap6)(void **, void **, void **, void *, HeapLess, int);
	Rva002C531BWrap(first, middle, comp);
	for (void **i = middle; i < last; ++i) {
		if (comp(*i, *first))
			((PopHeap6)Rva002C52E0PopHeap)(first, middle, i, *i, comp, 0);
	}
	Rva002C5556SortHeap(first, middle, comp);
}
// ?Rva002C5688PartialSortWrap@@YAXPAPAX00P6A_NPAX1@Z@Z @0x002C5688 27B
// partial_sort forwarding wrapper over rowed 0x002C562F: forwards
// (first,middle,last) plus 0 tag and comp; caller 0x002C5711.
void __cdecl Rva002C5688PartialSortWrap(void **first, void **middle, void **last, HeapLess comp)
{
	Rva002C562FPartialSort(first, middle, last, 0, comp);
}
// ?Rva0021C83ESortHeap@@YAXPAPAX0P6A_NPAX1@Z@Z @0x0021C83E 58B
// sort_heap over 4-byte entries via rowed pop_heap 0x0021BAFC; caller
// 0x0021D368; same HeapLess comp and G7 and-al shape as 0x002C5556.
void __cdecl Rva0021C83ESortHeap(void **first, void **last, HeapLess comp)
{
	while ((((char *)last - (char *)first) & ~3) > 4) {
		Rva0021BAFCPopHeap(first, last, comp);
		--last;
	}
}
// ?Rva0021D31CPartialSort@@YAXPAPAX00HP6A_NPAX1@Z@Z @0x0021D31C 89B
// __partial_sort twin of 0x002C562F: rowed make_heap 0x002C531B then
// guarded __pop_heap 0x002C52E0 loop then rowed sort_heap twin 0x0021C83E;
// caller 0x0021D9A5; unused int tag keeps comp at +0x18.
void __cdecl Rva0021D31CPartialSort(void **first, void **middle, void **last, int, HeapLess comp)
{
	typedef void (__cdecl *PopHeap6)(void **, void **, void **, void *, HeapLess, int);
	Rva002C531BWrap(first, middle, comp);
	for (void **i = middle; i < last; ++i) {
		if (comp(*i, *first))
			((PopHeap6)Rva002C52E0PopHeap)(first, middle, i, *i, comp, 0);
	}
	Rva0021C83ESortHeap(first, middle, comp);
}
// ?Rva0021D993PartialSortWrap@@YAXPAPAX00P6A_NPAX1@Z@Z @0x0021D993 27B
// partial_sort forwarding wrapper twin of 0x002C5688 over rowed 0x0021D31C:
// forwards (first,middle,last) plus 0 tag and comp; caller 0x0021DDEF.
void __cdecl Rva0021D993PartialSortWrap(void **first, void **middle, void **last, HeapLess comp)
{
	Rva0021D31CPartialSort(first, middle, last, 0, comp);
}
