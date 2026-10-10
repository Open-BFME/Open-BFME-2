// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ??$__unguarded_partition@PAHHVRva005E4300Cmp@@@_STL@@YAPAHPAH0HVRva005E4300Cmp@@@Z
// retail 0x005E459F, 73 bytes. Quicksort partition over int sort keys with
// the pinned thiscall comparator Rva005E4300Cmp (member operator()(int,int)
// at 0x005E4300, by-value ints, stateful): scan up while comp(*first,pivot),
// scan down while comp(pivot,*last), swap on cross, return the split.
// Evidence: calls both rowed to 0x005E4300; same 73B shape as
// stlport_unguarded_partition_rva00422ca8.cpp 0x004231A0 (inline iter_swap,
// out-of-line stateful comp, frame). Pin
// ??$__unguarded_partition@PAHHU?$greater@H@_STL@@@_STL@@YAPAHPAH0HU?$greater@H@0@@Z
// names this address from the greater<int> introsort_loop caller, but the body
// calls the stateful by-value comparator, so the honest name is the Rva one.

class Rva005E4300Cmp
{
public:
	char operator()(int a, int b) const;
};

enum ObjectID { INVALID_ID = 0 };

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
	Rva005E4300Cmp>(int *, int *, int, Rva005E4300Cmp);

// ??$__median@PAHVRva005E4300Cmp@@@_STL@@YAPAHPAH00VRva005E4300Cmp@@@Z
// retail 0x005E4534, 107 bytes. Median-of-three over int sort keys with the
// pinned thiscall comparator Rva005E4300Cmp: compare *a/*b/*c values, return
// the median pointer. Evidence: all five calls rowed to 0x005E4300; same
// spelling as stlport_unguarded_partition_rva00422ca8.cpp median 0x00423134.
template <class RandomAccessIter, class Compare>
RandomAccessIter __median(RandomAccessIter a, RandomAccessIter b,
	RandomAccessIter c, Compare comp)
{
	if (comp(*a, *b))
	{
		if (comp(*b, *c))
			return b;
		else if (comp(*a, *c))
			return c;
		else
			return a;
	}
	else
	{
		if (comp(*a, *c))
			return a;
		else if (comp(*b, *c))
			return c;
		else
			return b;
	}
}

template int *__median<int *,
	Rva005E4300Cmp>(int *, int *, int *, Rva005E4300Cmp);

// ??$__unguarded_linear_insert@PAHHVRva005E4300Cmp@@@_STL@@YAXPAHHVRva005E4300Cmp@@@Z @0x005E45E8 47B
// Insertion shift over int keys with stateful Rva005E4300Cmp: while comp(val,*next) move *next forward.
// Evidence: calls rowed 0x005E4300; callers 0x005E4862/0x005E48A1 insertion family; same shape as int 0x0040A77B.
template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp)
{
	RandomAccessIter next = last;
	--next;
	while (comp(val, *next))
	{
		*last = *next;
		last = next;
		--next;
	}
	*last = val;
}

template void __unguarded_linear_insert<int *, int,
	Rva005E4300Cmp>(int *, int, Rva005E4300Cmp);

// ??$__unguarded_insertion_sort_aux@PAHHVRva005E4300Cmp@@@_STL@@YAXPAH00VRva005E4300Cmp@@@Z @0x005E48A1 33B
// Unguarded insertion pass calling rowed __unguarded_linear_insert.
// Evidence: chain (calls just-landed 0x005E45E8); caller 0x005E4A56.
template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first,
	RandomAccessIter last, Tp *, Compare comp)
{
	for (RandomAccessIter i = first; i != last; ++i)
		__unguarded_linear_insert(i, Tp(*i), comp);
}

template void __unguarded_insertion_sort_aux<int *, int,
	Rva005E4300Cmp>(int *, int *, int *, Rva005E4300Cmp);

// ??$__linear_insert@PAHHVRva005E4300Cmp@@@_STL@@YAXPAH0HVRva005E4300Cmp@@@Z @0x005E4862 63B
// Guarded int insert with stateful Rva005E4300Cmp: if comp(val,*first) shift
// with the rowed ObjectID copy_backward then store val at first, else the
// rowed __unguarded_linear_insert. Evidence: callees rowed 0x005E42D3
// (ObjectID copy_backward) and 0x005E45E8 (unguarded_linear_insert) plus pin
// 0x005E4300; caller 0x005E4A1B insertion_sort; same 63B shape as
// stlport_int_sort_rva00422ca8.cpp 0x004238AE and int less<> 0x0040AE5E which
// selects the ObjectID helper via casts (retail 4.6-style keeps the typed
// wrapper call instead of inlining __copy_trivial_backward).
template <class InputIter, class OutputIter>
OutputIter copy_backward(InputIter first, InputIter last,
	OutputIter result);

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last,
	Tp val, Compare comp)
{
	if (comp(val, *first))
	{
		copy_backward((ObjectID *)first, (ObjectID *)last,
			(ObjectID *)(last + 1));
		*first = val;
	}
	else
	{
		__unguarded_linear_insert(last, val, comp);
	}
}

template void __linear_insert<int *, int,
	Rva005E4300Cmp>(int *, int *, int, Rva005E4300Cmp);

// ??$__insertion_sort@PAHVRva005E4300Cmp@@@_STL@@YAXPAH0VRva005E4300Cmp@@@Z @0x005E4A1B 45B
// Insertion sort over int keys with stateful Rva005E4300Cmp: linear insert
// each element. Evidence: calls rowed 0x005E4862; callers 0x005E4C4B/0x005E4C69
// in 0x005E4C2F; same 45B shape as 0x00423DE1 and less<> 0x0040B247.
template <class RandomAccessIter, class Compare>
void __insertion_sort(RandomAccessIter first, RandomAccessIter last,
	Compare comp)
{
	if (first == last)
		return;
	for (RandomAccessIter i = first + 1; i != last; ++i)
		__linear_insert(first, i, *i, comp);
}

template void __insertion_sort<int *,
	Rva005E4300Cmp>(int *, int *, Rva005E4300Cmp);

}
