// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__unguarded_insertion_sort@PAUVersionBlockEntry@@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@0VVersionBlockKeyCompare@@@Z @0x0042857D 23B
// _STL::__unguarded_insertion_sort over 0x18-byte version records: forwards to
// the value-typed aux 0x00428344 (VersionBlockUnguardedInsertionSortAux.cpp)
// with a null value-type tag. Caller: __final_insertion_sort 0x00428887.
// ??$sort@PAUVersionBlockEntry@@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@0VVersionBlockKeyCompare@@@Z @0x00428972 70B
// _STL::sort itself, frameless like this forwarder: __lg depth, the introsort
// loop 0x004288E9 and __final_insertion_sort 0x00428887 (both in the aux unit).
class VersionBlockKeyCompare
{
public:
	bool lessEntries(const struct VersionBlockEntry *left, const struct VersionBlockEntry *right) const;
};
struct VersionBlockEntry
{
	const char *m_key;
	char m_padAfterKey[8];
	const char *m_value;
	char m_padTail[8];
	~VersionBlockEntry();
};
namespace _STL
{
template <class _RandomAccessIter, class _Tp, class _Compare>
void __unguarded_insertion_sort_aux(_RandomAccessIter first, _RandomAccessIter last, _Tp *, _Compare comp);
template <class _RandomAccessIter, class _Compare>
void __unguarded_insertion_sort(_RandomAccessIter first, _RandomAccessIter last, _Compare comp)
{
	__unguarded_insertion_sort_aux(first, last, (VersionBlockEntry *)0, comp);
}
template void __unguarded_insertion_sort<VersionBlockEntry *, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare);
template <class _RandomAccessIter, class _Tp, class _Size, class _Compare>
void __introsort_loop(_RandomAccessIter first, _RandomAccessIter last, _Tp *, _Size depth_limit, _Compare comp);
template <class _RandomAccessIter, class _Compare>
void __final_insertion_sort(_RandomAccessIter first, _RandomAccessIter last, _Compare comp);
template <class _Size>
inline _Size __lg(_Size n)
{
	_Size k;
	for (k = 0; n != 1; n >>= 1)
		++k;
	return k;
}
template <class _RandomAccessIter, class _Compare>
void sort(_RandomAccessIter first, _RandomAccessIter last, _Compare comp)
{
	if (first != last)
	{
		__introsort_loop(first, last, (VersionBlockEntry *)0, __lg(last - first) * 2, comp);
		__final_insertion_sort(first, last, comp);
	}
}
template void sort<VersionBlockEntry *, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare);
}
