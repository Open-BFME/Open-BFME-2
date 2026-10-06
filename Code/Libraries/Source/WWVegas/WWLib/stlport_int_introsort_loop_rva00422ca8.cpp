// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ??$__introsort_loop@PAHHHVRva00422CA8@@@_STL@@YAXPAH00HVRva00422CA8@@@Z
// retail 0x00425385, 123 bytes. Introsort quicksort loop over int sort keys
// with the rowed thiscall comparator Rva00422CA8 (defined in
// Rva00422CA8Cmp.cpp): pointer median-of-three via rowed 0x00423134,
// partition via rowed 0x004231A0, partial_sort fallback via rowed 0x00424DB1
// on depth exhaustion, then self-recursion. Evidence: chain lane (calls
// 0x004231A0 just landed); caller 0x004254CB in sort wrapper 0x0042549E
// passes (first,last,0,depth,comp); same 123B shape as the rowed less<int>
// 0x0040B43B and greater<int> 0x005E523F introsort loops. Hand-written:
// the vendored header emits a value median here, retail calls the pointer
// median, so the loop is spelled out and the callees stay declared-only.

class Rva00422CA8
{
public:
	bool operator()(int a, int b) const;
};

namespace _STL
{

template <class RandomAccessIter, class Compare>
RandomAccessIter __median(RandomAccessIter a, RandomAccessIter b,
	RandomAccessIter c, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp);

template <class RandomAccessIter, class Compare>
void partial_sort(RandomAccessIter first, RandomAccessIter middle,
	RandomAccessIter last, Compare comp);

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

template void __introsort_loop<int *, int, int,
	Rva00422CA8>(int *, int *, int *, int, Rva00422CA8);

}
