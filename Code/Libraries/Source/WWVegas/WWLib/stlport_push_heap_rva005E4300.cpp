// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__push_heap@PAHHHURva005E4300Cmp@@@_STL@@YAXPAHHHHURva005E4300Cmp@@@Z @0x005E4617 76B
// Heap sift-up over int sort keys with the pinned thiscall comparator
// Rva005E4300Cmp (member operator()(int,int) at 0x005E4300): parent =
// (hole-1)/2, then while the hole is above top and comp(*parent, value)
// holds, move the parent down. Evidence: caller 0x005E4913 in rowed
// __adjust_heap 0x005E48C2; callee pinned 0x005E4300; same 76B shape as
// stlport_push_heap_rva00204bb8.cpp 0x002059CF.
struct Rva005E4300Cmp
{
	char operator()(int a, int b) const;
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp)
{
	Distance parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex)
	{
		if (!comp(*(first + parent), val))
			break;
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = val;
}

template void __push_heap<int *, int, int,
	Rva005E4300Cmp>(int *, int, int, int, Rva005E4300Cmp);

}
