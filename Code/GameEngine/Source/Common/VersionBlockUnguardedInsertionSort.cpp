// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// ??$__unguarded_insertion_sort@PAUVersionBlockEntry@@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@0VVersionBlockKeyCompare@@@Z @0x0042857D 23B
// _STL::__unguarded_insertion_sort over 0x18-byte version records: forwards to
// the value-typed aux 0x00428344 (VersionBlockUnguardedInsertionSortAux.cpp)
// with a null value-type tag. Caller: __final_insertion_sort 0x00428887.
// ??$sort@PAUVersionBlockEntry@@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@0VVersionBlockKeyCompare@@@Z @0x00428972 70B
// _STL::sort itself, frameless like this forwarder: __lg depth, the introsort
// loop 0x004288E9 and __final_insertion_sort 0x00428887 (both in the aux unit).
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

namespace _STL { template <> void __unguarded_insertion_sort_aux<VersionBlockEntry *,VersionBlockEntry,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockEntry *,VersionBlockKeyCompare); }

namespace _STL { template <> void __introsort_loop<VersionBlockEntry *,VersionBlockEntry,int,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockEntry *,int,VersionBlockKeyCompare); }

namespace _STL { template <> void __insertion_sort<VersionBlockEntry *,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockKeyCompare); }

template void _STL::__unguarded_insertion_sort<VersionBlockEntry *, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare);

template void _STL::sort<VersionBlockEntry *, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare);
