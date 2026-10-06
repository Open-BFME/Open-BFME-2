// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__median@PAHVRva00204BB8@@@_STL@@YAPAHPAH00VRva00204BB8@@@Z @0x002057D5 107B: median-of-three over int sort keys with rowed thiscall comparator Rva00204BB8.
// Evidence: caller 0x0020C04C passes (first, mid, last-1, comp) in introsort_loop shape; 5 calls to rowed 0x00204BB8; same branch shape as Rva00440AB0Median 107B and _STL median 0x00423134.
class Rva00204BB8
{
public:
	bool operator()(int a, int b) const;
};

namespace _STL
{

template <class RandomAccessIter, class Compare>
RandomAccessIter __median(RandomAccessIter a, RandomAccessIter b, RandomAccessIter c, Compare comp)
{
	if (comp(*a, *b)) {
		if (comp(*b, *c))
			return b;
		else if (comp(*a, *c))
			return c;
		else
			return a;
	} else {
		if (comp(*a, *c))
			return a;
		else if (comp(*b, *c))
			return c;
		else
			return b;
	}
}

template int *__median<int *, Rva00204BB8>(int *, int *, int *, Rva00204BB8);

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp);

template <class RandomAccessIter, class Compare>
void partial_sort(RandomAccessIter first, RandomAccessIter middle,
	RandomAccessIter last, Compare comp);

// ??$__introsort_loop@PAHHHVRva00204BB8@@@_STL@@YAXPAH00HVRva00204BB8@@@Z @0x0020C04C 123B: the
// quicksort loop calling this pointer median, the vendored partition 0x00205840
// (stlport_sort_rva00204bb8.cpp) and the rowed partial_sort 0x0020A295, then
// itself; sort 0x0020CE84 is its only other caller. Written here, not taken
// from the vendored header, because that loop calls the value median.
template <class RandomAccessIter, class Tp, class Size, class Compare>
void __introsort_loop(RandomAccessIter first, RandomAccessIter last,
	Tp *, Size depth_limit, Compare comp)
{
	while (last - first > 16)
	{
		if (depth_limit == 0)
		{
			partial_sort(first, last, last, comp);
			return;
		}
		--depth_limit;
		RandomAccessIter cut = __unguarded_partition(first, last,
			*__median(first, first + (last - first) / 2, last - 1, comp),
			comp);
		__introsort_loop(cut, last, (Tp *)0, depth_limit, comp);
		last = cut;
	}
}

template void __introsort_loop<int *, int, int, Rva00204BB8>(int *, int *, int *, int, Rva00204BB8);

}
