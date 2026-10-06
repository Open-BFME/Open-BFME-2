// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// __median 0x00568767 (108B) and __introsort_loop 0x00569E91 (123B) of the
// STLport sort<void**, Rva00568721Cmp> family; the rest is in
// stlport_sort_rva00568721.cpp. As in the Rva00422CA8 family
// (stlport_int_introsort_loop_rva00422ca8.cpp), retail's loop calls a
// pointer median-of-three, not the vendored value median, so both are
// written out here without the vendored header and the loop's other callees
// stay declared-only. Evidence: 0x00569E91 is called by sort 0x0056A29B and
// by itself, calls the rowed partition 0x00568DB7 and partial_sort
// 0x00569A8D; the median's five calls go to the pinned comparator.
struct Rva00568721Cmp
{
	bool operator()(const void *a, const void *b) const;
};
namespace _STL
{
// ??$__median@PAPAXURva00568721Cmp@@@_STL@@YAPAPAXPAPAX00URva00568721Cmp@@@Z @0x00568767
template <class RandomAccessIter, class Compare>
RandomAccessIter __median(RandomAccessIter a, RandomAccessIter b,
	RandomAccessIter c, Compare comp)
{
	void *bv = *b;
	void *av = *a;
	if (comp(av, bv))
	{
		void *cv = *c;
		if (comp(bv, cv))
			return b;
		else if (comp(av, cv))
			return c;
		else
			return a;
	}
	else
	{
		void *cv = *c;
		if (comp(av, cv))
			return a;
		else if (comp(bv, cv))
			return c;
		else
			return b;
	}
}
template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp);
template <class RandomAccessIter, class Compare>
void partial_sort(RandomAccessIter first, RandomAccessIter middle,
	RandomAccessIter last, Compare comp);
// ??$__introsort_loop@PAPAXPAXHURva00568721Cmp@@@_STL@@YAXPAPAX0PAPAXHURva00568721Cmp@@@Z @0x00569E91
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
template void __introsort_loop<void **, void *, int, Rva00568721Cmp>(void **, void **, void **, int, Rva00568721Cmp);
}
