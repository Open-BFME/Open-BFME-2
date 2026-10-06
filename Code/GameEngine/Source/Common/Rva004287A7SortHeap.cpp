// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__sort_heap@PAUVersionBlockEntry@@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@0VVersionBlockKeyCompare@@@Z RVA 0x004287A7 size 65 evidence sort_heap loop calling rowed pop_heap 0x00428716 caller 0x0042887A shape matches int precedent stlport_push_heap_rva00422ca8
struct VersionBlockEntry
{
	char m_data[24];
};
class VersionBlockKeyCompare
{
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
};
void __cdecl Rva00428716PopHeap(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockKeyCompare comp);
namespace _STL
{
template <class _RandomAccessIter, class _Compare>
void __sort_heap(_RandomAccessIter first, _RandomAccessIter last, _Compare comp)
{
	while (last - first > 1)
	{
		Rva00428716PopHeap(first, last, comp);
		--last;
	}
}
template void __sort_heap<VersionBlockEntry *, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare);
}
