// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ??$__pop_heap@PAHHURva005E4300Cmp@@@_STL@@YAXPAH00HURva005E4300Cmp@@@Z @0x005E4A5F 41B
// STL heap pop over int sort keys with the pinned thiscall comparator
// Rva005E4300Cmp at 0x005E4300; calls the rowed __adjust_heap 0x005E48C2.
// Evidence: same 41B shape as 0x00423EF7 and 0x002074D4 precedents; callees rowed.
struct Rva005E4300Cmp
{
	bool operator()(int a, int b) const;
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __pop_heap(RandomAccessIter first, RandomAccessIter last,
	RandomAccessIter result, Tp val, Compare comp)
{
	*result = *first;
	__adjust_heap(first, 0, (int)(last - first), val, comp);
}

template void __pop_heap<int *, int,
	Rva005E4300Cmp>(int *, int *, int *, int, Rva005E4300Cmp);

// ??$__pop_heap_aux@PAHHURva005E4300Cmp@@@_STL@@YAXPAH00URva005E4300Cmp@@@Z @0x005E4AC4 30B
// Calls the 6-arg __pop_heap overload (ICF twin of rowed 5-arg 0x005E4A5F) with
// (first, last-1, last-1, *(last-1), comp, (int*)0). Evidence: chain (calls just-landed 0x005E4A5F); same 30B shape as 0x00423F9F precedent.
// The call goes to the rowed 5-arg body with the sixth (dummy) argument, as in
// stlport_partial_sort_rva005E4300.cpp: retail's 6-arg overload folded into it.
template <class RandomAccessIter, class Tp, class Compare>
void __pop_heap_aux(RandomAccessIter first, RandomAccessIter last,
	Tp *, Compare comp)
{
	typedef void (__cdecl *PopHeap5)(int *, int *, int *, int, Rva005E4300Cmp);
	typedef void (__cdecl *PopHeap6)(int *, int *, int *, int, Rva005E4300Cmp, int *);
	PopHeap5 fn5 = (PopHeap5)&_STL::__pop_heap<int *, int, Rva005E4300Cmp>;
	PopHeap6 fn6 = (PopHeap6)fn5;
	fn6(first, last - 1, last - 1, Tp(*(last - 1)), comp, (int *)0);
}

template void __pop_heap_aux<int *, int,
	Rva005E4300Cmp>(int *, int *, int *, Rva005E4300Cmp);

// ??$pop_heap@PAHURva005E4300Cmp@@@_STL@@YAXPAH0URva005E4300Cmp@@@Z @0x005E4C8C 23B
// Public pop_heap wrapper calling __pop_heap_aux with (int*)0 dummy.
// Evidence: chain (calls just-landed 0x005E4AC4); same 23B shape as 0x00424637 precedent.
template <class RandomAccessIter, class Compare>
void pop_heap(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	__pop_heap_aux(first, last, (int *)0, comp);
}

template void pop_heap<int *,
	Rva005E4300Cmp>(int *, int *, Rva005E4300Cmp);

}
