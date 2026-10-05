// cl: /O1 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__unguarded_insertion_sort_aux@PAUVersionBlockEntry@@U1@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@00VVersionBlockKeyCompare@@@Z @0x00428344 46B
// _STL::__unguarded_insertion_sort_aux over 0x18-byte version records: for each
// record, copy it into a by-value pivot (narrow copy 0x00427F75) and call the
// rowed unguarded linear insert Rva004281DAInsert 0x004281DA. Caller: the
// unguarded insertion sort 0x0042857D. Record, pivot and comparator views are
// those of Rva004281DAInsert.cpp / Rva00428512Partition.cpp. /Oy- is target
// evidence: with frame-pointer omission on, MSVC stores the pivot address
// before loading ecx, the reverse of retail.
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
struct Pivot24
{
	Pivot24(const Pivot24 &other);
	~Pivot24();
	BfmeNarrowRecord00427F75 narrow;
};
// Inlined into its callers; no standalone body in retail.
// ??0Pivot24@@QAE@ABU0@@Z absent-from-retail
inline Pivot24::Pivot24(const Pivot24 &other) : narrow(other.narrow) {}
// ??1Pivot24@@QAE@XZ absent-from-retail
inline Pivot24::~Pivot24() { ((VersionBlockEntry *)&narrow)->~VersionBlockEntry(); }
void __cdecl Rva004281DAInsert(VersionBlockEntry *last, Pivot24 val, VersionBlockKeyCompare comp);
namespace _STL
{
template <class _RandomAccessIter, class _Tp, class _Compare>
void __unguarded_insertion_sort_aux(_RandomAccessIter first, _RandomAccessIter last, _Tp *, _Compare comp)
{
	for (_RandomAccessIter i = first; i != last; ++i)
		Rva004281DAInsert(i, *(const Pivot24 *)i, comp);
}
template void __unguarded_insertion_sort_aux<VersionBlockEntry *, VersionBlockEntry, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare);
}
