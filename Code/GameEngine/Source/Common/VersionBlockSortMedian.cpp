// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__median@UVersionBlockEntry@@VVersionBlockKeyCompare@@@_STL@@YAABUVersionBlockEntry@@ABU1@00VVersionBlockKeyCompare@@@Z @0x00427C9B 101B
// _STL::__median of three 0x18-byte version records under VersionBlockKeyCompare,
// the pivot pick of the introsort loop at 0x004288E9 (its caller at 0x00428922).
// Evidence: masked twin of the rowed __median<StringLookUp> (stlport_sort_stringlookup.cpp);
// all five compares call the rowed VersionBlockKeyCompare::lessEntries 0x00427C2C with the
// records' addresses, as the sibling insertion-sort and partition bodies do. Flags and
// record view from Rva004287E8InsertionSort.cpp.
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
template <class _Tp, class _Compare>
const _Tp &__median(const _Tp &a, const _Tp &b, const _Tp &c, _Compare comp)
{
	if (comp.lessEntries(&a, &b))
		if (comp.lessEntries(&b, &c))
			return b;
		else if (comp.lessEntries(&a, &c))
			return c;
		else
			return a;
	else if (comp.lessEntries(&a, &c))
		return a;
	else if (comp.lessEntries(&b, &c))
		return c;
	else
		return b;
}
template const VersionBlockEntry &__median<VersionBlockEntry, VersionBlockKeyCompare>(const VersionBlockEntry &, const VersionBlockEntry &, const VersionBlockEntry &, VersionBlockKeyCompare);
}
