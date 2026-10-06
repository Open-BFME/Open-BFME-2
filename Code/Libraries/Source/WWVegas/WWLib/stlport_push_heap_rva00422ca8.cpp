// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ??$__push_heap@PAHHHVRva00422CA8@@@_STL@@YAXPAHHHHVRva00422CA8@@@Z
// retail 0x00423349, 77 bytes. Heap sift-up over int sort keys with the
// rowed thiscall comparator Rva00422CA8 (member operator()(int,int),
// defined in Rva00422CA8Cmp.cpp): parent = (hole-1)/2, then while the hole
// is above top and comp(*parent, value) holds, move the parent down.
// Evidence: caller 0x00423A10 in the 94B push_heap wrapper 0x004239BF;
// callees rowed to 0x00422CA8; unblocks 0x004239BF. Same STLport sift-up
// spelling as stlport_push_heap_s4sortelem8.cpp.

class Rva00422CA8
{
public:
	bool operator()(int a, int b) const;
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
		Tp tmp = *(first + parent);
		if (!comp(tmp, val))
			break;
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = val;
}

template void __push_heap<int *, int, int,
	Rva00422CA8>(int *, int, int, int, Rva00422CA8);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp)
{
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if (comp(*(first + secondChild), *(first + (secondChild - 1))))
			--secondChild;
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}
	__push_heap(first, holeIndex, topIndex, val, comp);
}

template void __adjust_heap<int *, int, int,
	Rva00422CA8>(int *, int, int, int, Rva00422CA8);

template <class RandomAccessIter, class Tp, class Compare>
void __pop_heap(RandomAccessIter first, RandomAccessIter last,
	RandomAccessIter result, Tp val, Compare comp)
{
	*result = *first;
	__adjust_heap(first, 0, (int)(last - first), val, comp);
}

template void __pop_heap<int *, int,
	Rva00422CA8>(int *, int *, int *, int, Rva00422CA8);

// ??$__pop_heap_aux@PAHHVRva00422CA8@@@_STL@@YAXPAH00VRva00422CA8@@@Z
// retail 0x00423F9F, 30 bytes. Calls the 6-arg __pop_heap overload
// (ICF twin of the rowed 5-arg 0x00423EF7, pinned) with (first, last-1,
// last-1, *(last-1), comp, (int*)0). Evidence: caller 0x00424645 in
// 0x00424637; callee rowed/pinned 0x00423EF7; unblocks 0x00424637.
template <class RandomAccessIter, class Distance, class Tp, class Compare>
void __pop_heap(RandomAccessIter first, RandomAccessIter last,
	RandomAccessIter result, Tp val, Compare comp, Distance *);

template <class RandomAccessIter, class Tp, class Compare>
void __pop_heap_aux(RandomAccessIter first, RandomAccessIter last,
	Tp *, Compare comp)
{
	__pop_heap(first, last - 1, last - 1, Tp(*(last - 1)), comp, (int *)0);
}

template void __pop_heap_aux<int *, int,
	Rva00422CA8>(int *, int *, int *, Rva00422CA8);

template <class RandomAccessIter, class Compare>
void __make_heap(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	if (last - first < 2)
		return;
	int len = (int)(last - first);
	int parent = (len - 2) / 2;
	while (true)
	{
		__adjust_heap(first, parent, len, *(first + parent), comp);
		if (parent == 0)
			return;
		--parent;
	}
}

template void __make_heap<int *,
	Rva00422CA8>(int *, int *, Rva00422CA8);

// ?pop_heap int Rva00422CA8 23B @0x00424637: public wrapper calling
// __pop_heap_aux with (int*)0 dummy. Evidence: calls rowed 0x00423F9F;
// caller 0x004247C8 in 0x004247A9; unblocks 0x004247A9.
template <class RandomAccessIter, class Compare>
void pop_heap(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	__pop_heap_aux(first, last, (int *)0, comp);
}

template void pop_heap<int *,
	Rva00422CA8>(int *, int *, Rva00422CA8);

// ??$__sort_heap@PAHVRva00422CA8@@@_STL@@YAXPAH0VRva00422CA8@@@Z
// retail 0x004247A9, 58 bytes. Sorts heap by repeatedly popping max to the
// end. Evidence: calls rowed pop_heap 0x00424637; caller 0x00424C71 in
// 0x00424C21; unblocks 0x00424C21.
template <class RandomAccessIter, class Compare>
void __sort_heap(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	while (last - first > 1)
	{
		pop_heap(first, last, comp);
		--last;
	}
}

template void __sort_heap<int *,
	Rva00422CA8>(int *, int *, Rva00422CA8);

// ??$make_heap@PAHVRva00422CA8@@@_STL@@YAXPAH0VRva00422CA8@@@Z
// retail 0x0042461E, 25 bytes. Public wrapper calling the 5-arg __make_heap
// overload (ICF twin of rowed 3-arg 0x00423F63, pinned) with (first, last,
// comp, 0, 0). Evidence: calls rowed/pinned 0x00423F63; caller 0x00424C32 in
// 0x00424C21; unblocks 0x00424C21.
template <class RandomAccessIter, class Compare>
void __make_heap(RandomAccessIter first, RandomAccessIter last, Compare comp,
	int *, int *);

template <class RandomAccessIter, class Compare>
void make_heap(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	__make_heap(first, last, comp, (int *)0, (int *)0);
}

template void make_heap<int *,
	Rva00422CA8>(int *, int *, Rva00422CA8);

// ??$__partial_sort@PAHHVRva00422CA8@@@_STL@@YAXPAH000VRva00422CA8@@@Z
// retail 0x00424C21, 93 bytes. Partial sort via make/adjust/sort heap with
// the rowed comparator. Evidence: calls rowed make_heap 0x0042461E,
// pinned 6-arg pop_heap 0x00423EF7, rowed sort_heap 0x004247A9 and rowed
// comparator 0x00422CA8; caller 0x00424DC3 in 0x00424DB1; unblocks 0x00424DB1.
template <class RandomAccessIter, class Tp, class Compare>
void __partial_sort(RandomAccessIter first, RandomAccessIter middle,
	RandomAccessIter last, Tp *, Compare comp)
{
	make_heap(first, middle, comp);
	for (RandomAccessIter i = middle; i < last; ++i)
	{
		int cur = *i;
		if (comp(cur, *first))
			__pop_heap(first, middle, i, *i, comp, (int *)0);
	}
	__sort_heap(first, middle, comp);
}

template void __partial_sort<int *, int,
	Rva00422CA8>(int *, int *, int *, int *, Rva00422CA8);

// ??$partial_sort@PAHVRva00422CA8@@@_STL@@YAXPAH00VRva00422CA8@@@Z
// retail 0x00424DB1, 27 bytes. Public partial_sort wrapper forwarding to the
// rowed __partial_sort 0x00424C21 with (int*)0 dummy. Evidence: chain lane
// (calls 0x00424C21 just landed); caller 0x004253F3 in 0x00425385; unblocks
// 0x00425385.
template <class RandomAccessIter, class Compare>
void partial_sort(RandomAccessIter first, RandomAccessIter middle,
	RandomAccessIter last, Compare comp)
{
	__partial_sort(first, middle, last, (int *)0, comp);
}

template void partial_sort<int *,
	Rva00422CA8>(int *, int *, int *, Rva00422CA8);

// ??$upper_bound@PAHHVRva00422CA8@@@_STL@@YAPAHPAH0ABHVRva00422CA8@@@Z
// retail 0x00423098, 83 bytes. Upper bound over int sort keys with the
// rowed thiscall comparator Rva00422CA8: caches val once, halves the range
// while comp(cached, *middle) holds. Evidence: callee rowed 0x00422CA8;
// caller 0x004235C4 in unclaimed 0x00423558.
template <class RandomAccessIter, class T, class Compare>
RandomAccessIter upper_bound(RandomAccessIter first, RandomAccessIter last,
	const T &val, Compare comp)
{
	int len = (int)(last - first);
	int cached;
	if (len > 0)
	{
		cached = val;
		do
		{
			int half = len >> 1;
			RandomAccessIter middle = first + half;
			if (comp(cached, *middle))
				len = half;
			else
			{
				first = middle + 1;
				len = len - half - 1;
			}
		} while (len > 0);
	}
	return first;
}

template int *upper_bound<int *, int,
	Rva00422CA8>(int *, int *, const int &, Rva00422CA8);

}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??$__make_heap@PAHVRva00422CA8@@@_STL@@YAXPAH0VRva00422CA8@@00@Z=??$__make_heap@PAHVRva00422CA8@@@_STL@@YAXPAH0VRva00422CA8@@@Z")
#pragma comment(linker, "/alternatename:??$__pop_heap@PAHHHVRva00422CA8@@@_STL@@YAXPAH00HVRva00422CA8@@0@Z=??$__pop_heap@PAHHVRva00422CA8@@@_STL@@YAXPAH00HVRva00422CA8@@@Z")
