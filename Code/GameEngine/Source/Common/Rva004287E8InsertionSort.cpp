// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__insertion_sort@PAUVersionBlockEntry@@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@0VVersionBlockKeyCompare@@@Z @0x004287E8 57B
// _STL::__insertion_sort guarded over 0x18-byte version records.
// Evidence: callees narrow copy 0x00427F75 row NarrowStringRecordCopyBFME2.cpp linear_insert 0x0042872D row Rva0042872DFinish.cpp; callers 0x004288A9 0x004288C3 in final_insertion_sort 0x00428887; shape matches S4SortElem8 insertion_sort precedent with 0x18 stride and out-of-line value copy.
struct VersionBlockEntry
{
	char m_data[24];
	VersionBlockEntry(const VersionBlockEntry &other);
	~VersionBlockEntry();
};
class VersionBlockKeyCompare
{
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
};
namespace _STL
{
template <class _RandomAccessIter, class _Tp, class _Compare>
void __linear_insert(_RandomAccessIter first, _RandomAccessIter last, _Tp val, _Compare comp);
template <class _RandomAccessIter, class _Compare>
void __insertion_sort(_RandomAccessIter first, _RandomAccessIter last, _Compare comp)
{
	if (first == last)
		return;
	for (_RandomAccessIter i = first + 1; i != last; ++i)
		__linear_insert(first, i, *i, comp);
}
template void __insertion_sort<VersionBlockEntry *, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare);
}
