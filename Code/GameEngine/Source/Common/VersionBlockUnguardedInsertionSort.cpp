// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__unguarded_insertion_sort@PAUVersionBlockEntry@@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@0VVersionBlockKeyCompare@@@Z @0x0042857D 23B
// _STL::__unguarded_insertion_sort over 0x18-byte version records: forwards to
// the value-typed aux 0x00428344 (VersionBlockUnguardedInsertionSortAux.cpp)
// with a null value-type tag. Caller: __final_insertion_sort 0x00428887.
class VersionBlockKeyCompare
{
public:
	bool lessEntries(const struct VersionBlockEntry *left, const struct VersionBlockEntry *right) const;
};
struct VersionBlockEntry;
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
}
