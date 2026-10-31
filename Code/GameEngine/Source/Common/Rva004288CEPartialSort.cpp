// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// ??$partial_sort@PAUVersionBlockEntry@@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@00VVersionBlockKeyCompare@@@Z RVA 0x004288CE size 27 evidence partial_sort wrapper forwarding to rowed __partial_sort 0x00428821 with dummy caller 0x00428965 same pattern as int precedent
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

namespace _STL { template <> void __partial_sort<VersionBlockEntry *,VersionBlockEntry,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockEntry *,VersionBlockEntry *,VersionBlockKeyCompare); }

namespace _STL { template <> void partial_sort<VersionBlockEntry *,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockEntry *,VersionBlockKeyCompare); }

namespace _STL
{
template <>
void partial_sort<VersionBlockEntry *, VersionBlockKeyCompare>(VersionBlockEntry *first, VersionBlockEntry *middle, VersionBlockEntry *last, VersionBlockKeyCompare comp)
{
	__partial_sort(first, middle, last, (VersionBlockEntry *)0, comp);
}
}
