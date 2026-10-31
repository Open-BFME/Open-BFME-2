// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// ?Rva00428512Partition@@YAPAUVersionBlockEntry@@PAU1@0UPivot24@@VVersionBlockKeyCompare@@@Z @0x00428512 107B
// Quicksort unguarded partition over 0x18-byte version records with pivot by value.
// Evidence: chain lane calls just-landed swap 0x0042818F; callees lessEntries 0x00427C2C row VersionBlockKeyCompare.cpp version dtor 0x00238580 row VersionDestructor.cpp; caller 0x004288E9 introsort constructs pivot via narrow copy 0x00427F75; same 107B shape as rowed 0x0021C6CB with EH for non-trivial pivot.
#include <string>

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

void __cdecl Rva0042818FSwap(void *a, void *b);

VersionBlockEntry *__cdecl Rva00428512Partition(VersionBlockEntry *first, VersionBlockEntry *last, Pivot24 pivot, VersionBlockKeyCompare comp)
{
	while (true)
	{
		while (comp.lessEntries(first, (const VersionBlockEntry *)&pivot))
			++first;
		--last;
		while (comp.lessEntries((const VersionBlockEntry *)&pivot, last))
			--last;
		if (!(first < last))
			return first;
		Rva0042818FSwap(first, last);
		++first;
	}
}
