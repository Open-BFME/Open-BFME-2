// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__partial_sort@PAUVersionBlockEntry@@U1@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@000VVersionBlockKeyCompare@@@Z RVA 0x00428821 size 102 evidence partial_sort via rowed make_wrap 0x004286E2 pop_heap 0x00428594 sort_heap 0x004287A7 caller 0x004288E0 shape matches int precedent
struct BfmeNarrowRecord00427F75
{
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &other);
	char m_data[24];
};
struct VersionBlockEntry
{
	char m_data[24];
	~VersionBlockEntry();
};
class VersionBlockKeyCompare
{
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
};
struct Pivot24
{
	Pivot24(const Pivot24 &other);
	~Pivot24();
	BfmeNarrowRecord00427F75 narrow;
};
void __cdecl Rva004286E2Wrap(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockKeyCompare comp);
void __cdecl Rva00428594PopHeap(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockEntry *result, Pivot24 val, VersionBlockKeyCompare comp, int extra);
namespace _STL
{
template <class _RandomAccessIter, class _Compare>
void __sort_heap(_RandomAccessIter first, _RandomAccessIter last, _Compare comp);
template <class _RandomAccessIter, class _Tp, class _Compare>
void __partial_sort(_RandomAccessIter first, _RandomAccessIter middle, _RandomAccessIter last, _Tp *, _Compare comp)
{
	::Rva004286E2Wrap(first, middle, comp);
	for (_RandomAccessIter i = middle; i < last; ++i)
	{
		if (comp.lessEntries(i, first))
			::Rva00428594PopHeap(first, middle, i, *(Pivot24 *)i, comp, 0);
	}
	__sort_heap(first, middle, comp);
}
template void __partial_sort<VersionBlockEntry *, VersionBlockEntry, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare);
}
