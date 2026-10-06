// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$partial_sort@PAUVersionBlockEntry@@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@00VVersionBlockKeyCompare@@@Z RVA 0x004288CE size 27 evidence partial_sort wrapper forwarding to rowed __partial_sort 0x00428821 with dummy caller 0x00428965 same pattern as int precedent
struct VersionBlockEntry
{
	char m_data[24];
};
class VersionBlockKeyCompare
{
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
};
namespace _STL
{
template <class _RandomAccessIter, class _Tp, class _Compare>
void __partial_sort(_RandomAccessIter first, _RandomAccessIter middle, _RandomAccessIter last, _Tp *, _Compare comp);
template <class _RandomAccessIter, class _Compare>
void partial_sort(_RandomAccessIter first, _RandomAccessIter middle, _RandomAccessIter last, _Compare comp)
{
	__partial_sort(first, middle, last, (VersionBlockEntry *)0, comp);
}
template void partial_sort<VersionBlockEntry *, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare);
}
