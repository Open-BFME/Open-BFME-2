// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// ??$__partial_sort@PAUVersionBlockEntry@@U1@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@000VVersionBlockKeyCompare@@@Z RVA 0x00428821 size 102 evidence partial_sort via rowed make_wrap 0x004286E2 pop_heap 0x00428594 sort_heap 0x004287A7 caller 0x004288E0 shape matches int precedent
#include <string>
#include <algorithm>

struct BfmeNarrowRecord00427F75
{
	_STL::basic_string<char> m_key;
	_STL::basic_string<char> m_value;
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &);
	~BfmeNarrowRecord00427F75();
};

class ProductionPrerequisite
{
public:
	ProductionPrerequisite &operator=(const ProductionPrerequisite &other);
};

struct VersionBlockEntry : public BfmeNarrowRecord00427F75
{
	VersionBlockEntry();
	VersionBlockEntry(const VersionBlockEntry &other);
	~VersionBlockEntry();
};

struct Pivot24
{
	Pivot24(const Pivot24 &other);
	~Pivot24() {}
	VersionBlockEntry narrow;
};

class VersionBlockKeyCompare
{
public:
	bool operator()(const VersionBlockEntry &a, const VersionBlockEntry &b) const
	{
		return a.m_key < b.m_key;
	}
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
public:
	bool lessEntryKey(const VersionBlockEntry *entry, const char *key) const;
public:
	bool lessKeyEntry(const char *key, const VersionBlockEntry *entry) const;
};

void __cdecl Rva004286E2Wrap(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockKeyCompare comp);

void __cdecl Rva00428594PopHeap(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockEntry *result, Pivot24 val, VersionBlockKeyCompare comp, int extra);

namespace _STL
{
template <class _RandomAccessIter, class _Compare>
void __sort_heap(_RandomAccessIter first, _RandomAccessIter last, _Compare comp);
}

namespace _STL { template <> void __partial_sort<VersionBlockEntry *,VersionBlockEntry,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockEntry *,VersionBlockEntry *,VersionBlockKeyCompare); }

namespace _STL
{
template <>
void __partial_sort<VersionBlockEntry *, VersionBlockEntry, VersionBlockKeyCompare>(VersionBlockEntry *first, VersionBlockEntry *middle, VersionBlockEntry *last, VersionBlockEntry *, VersionBlockKeyCompare comp)
{
	::Rva004286E2Wrap(first, middle, comp);
	for (VersionBlockEntry *i = middle; i < last; ++i)
	{
		if (comp.lessEntries(i, first))
			::Rva00428594PopHeap(first, middle, i, *(Pivot24 *)i, comp, 0);
	}
	__sort_heap(first, middle, comp);
}
}
