// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// ??$__insertion_sort@PAUVersionBlockEntry@@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@0VVersionBlockKeyCompare@@@Z @0x004287E8 57B
// _STL::__insertion_sort guarded over 0x18-byte version records.
// Evidence: callees narrow copy 0x00427F75 row NarrowStringRecordCopyBFME2.cpp linear_insert 0x0042872D row Rva0042872DFinish.cpp; callers 0x004288A9 0x004288C3 in final_insertion_sort 0x00428887; shape matches S4SortElem8 insertion_sort precedent with 0x18 stride and out-of-line value copy.
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

namespace _STL { template <> void __linear_insert<VersionBlockEntry *,VersionBlockEntry,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockEntry,VersionBlockKeyCompare); }

namespace _STL { template <> void __insertion_sort<VersionBlockEntry *,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockKeyCompare); }

namespace _STL
{
template <>
void __insertion_sort<VersionBlockEntry *, VersionBlockKeyCompare>(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockKeyCompare comp)
{
	if (first == last)
		return;
	for (VersionBlockEntry *i = first + 1; i != last; ++i)
		__linear_insert(first, i, *i, comp);
}
}
