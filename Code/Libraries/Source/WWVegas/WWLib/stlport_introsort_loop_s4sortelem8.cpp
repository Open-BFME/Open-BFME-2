// cl: /DNDEBUG /MD /EHsc
// stlport

// _STL::__introsort_loop<S4SortElem8 *, S4SortElem8, int, S4Cmp00625BB0>,
// retail 0x00626780, 224 bytes.  Ascending quicksort core verbatim (BFME1
// ScoreRowIntrosort.cpp shape, vendored header): inline median-of-three on
// the float key, the matched __unguarded_partition at 0x00625DB0, the
// matched __partial_sort at 0x00626530 on depth exhaustion, direct
// self-recursion.  All callees are matched rows (no new pins).
// Link fix: manual __introsort_loop with forward-declared callees so this
// TU emits only its row (no iter_swap/swap COMDAT; the first copy in link
// order wins).

struct S4SortElem8
{
	int m_bfmeA;						// +0x00
	float m_bfmeKey;					// +0x04
};

struct S4Cmp00625BB0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey < b.m_bfmeKey;
	}
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp);

template <class RandomAccessIterator, class Tp, class Compare>
void __partial_sort(RandomAccessIterator first,
	RandomAccessIterator middle, RandomAccessIterator last, Tp *,
	Compare comp);

template <class Tp, class Compare>
inline const Tp &__median(const Tp &a, const Tp &b, const Tp &c,
	Compare comp)
{
	if (comp(a, b))
		if (comp(b, c))
			return b;
		else if (comp(a, c))
			return c;
		else
			return a;
	else if (comp(a, c))
		return a;
	else if (comp(b, c))
		return c;
	else
		return b;
}

template <class RandomAccessIter, class Tp, class Size, class Compare>
void __introsort_loop(RandomAccessIter first, RandomAccessIter last,
	Tp *, Size depth_limit, Compare comp)
{
	while (last - first > 16)
	{
		if (depth_limit == 0)
		{
			__partial_sort(first, last, last, (Tp *)0, comp);
			return;
		}
		--depth_limit;
		RandomAccessIter cut = __unguarded_partition(first, last,
			Tp(__median(*first, *(first + (last - first) / 2),
				*(last - 1), comp)),
			comp);
		__introsort_loop(cut, last, (Tp *)0, depth_limit, comp);
		last = cut;
	}
}

template void __introsort_loop<S4SortElem8 *, S4SortElem8, int,
	S4Cmp00625BB0>(S4SortElem8 *, S4SortElem8 *, S4SortElem8 *, int,
	S4Cmp00625BB0);

}
