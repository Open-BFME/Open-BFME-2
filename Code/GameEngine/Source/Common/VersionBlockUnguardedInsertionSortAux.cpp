// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// The framed half of _STL::sort over 0x18-byte version records under
// VersionBlockKeyCompare (record, pivot and comparator views of
// Rva004281DAInsert.cpp / Rva00428512Partition.cpp):
//   0x00428344  46B __unguarded_insertion_sort_aux: copy each record into the
//               by-value pivot (narrow copy 0x00427F75), call the rowed
//               unguarded linear insert Rva004281DAInsert 0x004281DA
//   0x004288E9 137B __introsort_loop: rowed __median 0x00427C9B, pivot copy,
//               rowed partition Rva00428512Partition 0x00428512, recursion,
//               rowed partial_sort 0x004288CE at the depth limit
//   0x00428887  71B __final_insertion_sort: rowed __insertion_sort 0x004287E8
//               and the unguarded insertion sort 0x0042857D
// sort itself (0x00428972) is frameless and lives in
// VersionBlockUnguardedInsertionSort.cpp. /Oy- and /G7 are target evidence:
// with frame-pointer omission on, MSVC stores the pivot address before
// loading ecx, and without /G7 the median index is scaled with lea pairs
// instead of retail's imul 0x18. The pivot copy is the narrow record's own
// copy constructor at 0x00427F75.
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

void __cdecl Rva004281DAInsert(VersionBlockEntry *last, Pivot24 val, VersionBlockKeyCompare comp);

VersionBlockEntry *__cdecl Rva00428512Partition(VersionBlockEntry *first, VersionBlockEntry *last, Pivot24 pivot, VersionBlockKeyCompare comp);

namespace _STL { template <> VersionBlockEntry const & __median<VersionBlockEntry,VersionBlockKeyCompare>(VersionBlockEntry const &,VersionBlockEntry const &,VersionBlockEntry const &,VersionBlockKeyCompare); }

namespace _STL { template <> void partial_sort<VersionBlockEntry *,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockEntry *,VersionBlockKeyCompare); }

namespace _STL { template <> void __insertion_sort<VersionBlockEntry *,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockKeyCompare); }

namespace _STL { template <> void __unguarded_insertion_sort_aux<VersionBlockEntry *,VersionBlockEntry,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockEntry *,VersionBlockKeyCompare); }

namespace _STL { template <> void __introsort_loop<VersionBlockEntry *,VersionBlockEntry,int,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockEntry *,int,VersionBlockKeyCompare); }

namespace _STL
{
template <>
void __unguarded_insertion_sort_aux<VersionBlockEntry *, VersionBlockEntry, VersionBlockKeyCompare>(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockEntry *, VersionBlockKeyCompare comp)
{
	for (VersionBlockEntry *i = first; i != last; ++i)
		Rva004281DAInsert(i, *(const Pivot24 *)i, comp);
}
template <>
void __introsort_loop<VersionBlockEntry *, VersionBlockEntry, int, VersionBlockKeyCompare>(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockEntry *, int depth_limit, VersionBlockKeyCompare comp)
{
	while (last - first > 16)
	{
		if (depth_limit == 0)
		{
			partial_sort(first, last, last, comp);
			return;
		}
		--depth_limit;
		VersionBlockEntry *cut = Rva00428512Partition(first, last,
			*(const Pivot24 *)&__median(*first, *(first + (last - first) / 2), *(last - 1), comp), comp);
		__introsort_loop(cut, last, (VersionBlockEntry *)0, depth_limit, comp);
		last = cut;
	}
}
}

template void _STL::__final_insertion_sort<VersionBlockEntry *, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockKeyCompare);
