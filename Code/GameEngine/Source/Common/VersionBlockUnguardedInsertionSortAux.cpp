// cl: /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// The framed half of _STL::sort over 0x18-byte version records under
// VersionBlockKeyCompare (record, pivot and comparator views of
// Rva004281DAInsert.cpp / Rva00428512Partition.cpp):
//   0x00428344  46B __unguarded_insertion_sort_aux: copy each record into the
//               by-value pivot (narrow copy 0x00427F75), call the rowed
//               unguarded linear insert Rva004281DAInsert 0x004281DA
//   0x004288E9 137B __introsort_loop: rowed __median 0x00427C9B, pivot copy,
//               rowed partition Rva00428512Partition 0x00428512, recursion,
//               rowed partial_sort 0x004288CE at the depth limit
//   0x00428887  71B __final_insertion_sort: rowed __insertion_sort 0x004287E8
//               and the unguarded insertion sort 0x0042857D
// sort itself (0x00428972) is frameless and lives in
// VersionBlockUnguardedInsertionSort.cpp. /Oy- and /G7 are target evidence:
// with frame-pointer omission on, MSVC stores the pivot address before
// loading ecx, and without /G7 the median index is scaled with lea pairs
// instead of retail's imul 0x18. The pivot copy is the narrow record's own
// copy constructor, hence the pivot derives from it.
struct BfmeNarrowRecord00427F75
{
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &other);
	char m_data[24];
};
struct VersionBlockEntry
{
	const char *m_key;
	char m_padAfterKey[8];
	const char *m_value;
	char m_padTail[8];
	~VersionBlockEntry();
};
class VersionBlockKeyCompare
{
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
};
struct Pivot24 : BfmeNarrowRecord00427F75
{
	Pivot24(const Pivot24 &other);
	~Pivot24();
};
void __cdecl Rva004281DAInsert(VersionBlockEntry *last, Pivot24 val, VersionBlockKeyCompare comp);
VersionBlockEntry *__cdecl Rva00428512Partition(VersionBlockEntry *first, VersionBlockEntry *last, Pivot24 pivot, VersionBlockKeyCompare comp);
namespace _STL
{
template <class _Tp, class _Compare>
const _Tp &__median(const _Tp &a, const _Tp &b, const _Tp &c, _Compare comp);
template <class _RandomAccessIter, class _Compare>
void partial_sort(_RandomAccessIter first, _RandomAccessIter middle, _RandomAccessIter last, _Compare comp);
template <class _RandomAccessIter, class _Compare>
void __insertion_sort(_RandomAccessIter first, _RandomAccessIter last, _Compare comp);
template <class _RandomAccessIter, class _Compare>
void __unguarded_insertion_sort(_RandomAccessIter first, _RandomAccessIter last, _Compare comp);
template <class _RandomAccessIter, class _Tp, class _Compare>
void __unguarded_insertion_sort_aux(_RandomAccessIter first, _RandomAccessIter last, _Tp *, _Compare comp)
{
	for (_RandomAccessIter i = first; i != last; ++i)
		Rva004281DAInsert(i, *(const Pivot24 *)i, comp);
}
template <class _RandomAccessIter, class _Tp, class _Size, class _Compare>
void __introsort_loop(_RandomAccessIter first, _RandomAccessIter last, _Tp *, _Size depth_limit, _Compare comp)
{
	while (last - first > 16)
	{
		if (depth_limit == 0)
		{
			partial_sort(first, last, last, comp);
			return;
		}
		--depth_limit;
		_RandomAccessIter cut = Rva00428512Partition(first, last,
			*(const Pivot24 *)&__median(*first, *(first + (last - first) / 2), *(last - 1), comp), comp);
		__introsort_loop(cut, last, (_Tp *)0, depth_limit, comp);
		last = cut;
	}
}
template <class _RandomAccessIter, class _Compare>
void __final_insertion_sort(_RandomAccessIter first, _RandomAccessIter last, _Compare comp)
{
	if (last - first > 16)
	{
		__insertion_sort(first, first + 16, comp);
		__unguarded_insertion_sort(first + 16, last, comp);
	}
	else
		__insertion_sort(first, last, comp);
}
template void __introsort_loop<VersionBlockEntry *, VersionBlockEntry, int, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockEntry *, int, VersionBlockKeyCompare);
template void __unguarded_insertion_sort_aux<VersionBlockEntry *, VersionBlockEntry, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare);
template void __final_insertion_sort<VersionBlockEntry *, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare);
}
