// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ??$__unguarded_partition@PAHHVRva00422CA8@@@_STL@@YAPAHPAH0HVRva00422CA8@@@Z
// retail 0x004231A0, 73 bytes. Quicksort partition over int sort keys with
// the rowed thiscall comparator Rva00422CA8 (member operator()(int,int),
// defined in Rva00422CA8Cmp.cpp): scan up while comp(*first,pivot), scan
// down while comp(pivot,*last), swap on cross, return the split.
// Evidence: caller 0x004253C9 passes (first,last,pivot,comp) in the median /
// partition / recurse quicksort shape; callees both rowed to 0x00422CA8.

class Rva00422CA8
{
public:
	bool operator()(int a, int b) const;
};

namespace _STL
{

template <class ForwardIter1, class ForwardIter2>
__forceinline void iter_swap(ForwardIter1 left, ForwardIter2 right)
{
	int temporary = *left;
	*left = *right;
	*right = temporary;
}

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp)
{
	while (true)
	{
		while (comp(*first, pivot))
			++first;
		--last;
		while (comp(pivot, *last))
			--last;
		if (!(first < last))
			return first;
		iter_swap(first, last);
		++first;
	}
}

template int *__unguarded_partition<int *, int,
	Rva00422CA8>(int *, int *, int, Rva00422CA8);

// ??$__median@PAHVRva00422CA8@@@_STL@@YAPAHPAH00VRva00422CA8@@@Z
// retail 0x00423134, 108 bytes. Median-of-three over int sort keys with the
// rowed thiscall comparator Rva00422CA8: compare *a/*b/*c values, return the
// median pointer. Evidence: caller 0x004253BD in 123B 0x00425385; callees
// rowed to 0x00422CA8; unblocks 0x00425385. Same __median spelling as
// stlport_median_q4sort.cpp donor, with bv/av preloaded and cv hoisted.
template <class RandomAccessIter, class Compare>
RandomAccessIter __median(RandomAccessIter a, RandomAccessIter b,
	RandomAccessIter c, Compare comp)
{
	int bv = *b;
	int av = *a;
	if (comp(av, bv))
	{
		int cv = *c;
		if (comp(bv, cv))
			return b;
		else if (comp(av, cv))
			return c;
		else
			return a;
	}
	else
	{
		int cv = *c;
		if (comp(av, cv))
			return a;
		else if (comp(bv, cv))
			return c;
		else
			return b;
	}
}

template int *__median<int *,
	Rva00422CA8>(int *, int *, int *, Rva00422CA8);

}
