// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// ?Rva00428594PopHeap@@YAXPAUVersionBlockEntry@@00UPivot24@@VVersionBlockKeyCompare@@H@Z RVA 0x00428594 size 95 evidence chain linkbody callers 0x0042864B 0x00428821 callees prereq-assign 0x0042816E narrow-copy 0x00427F75 adjust-heap 0x00428372 version-dtor 0x00238580
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

void __cdecl Rva00428372AdjustHeap(VersionBlockEntry *first, int holeIndex, int len, Pivot24 val, VersionBlockKeyCompare comp);

void __cdecl Rva00428594PopHeap(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockEntry *result, Pivot24 val, VersionBlockKeyCompare comp, int extra)
{
	*(ProductionPrerequisite *)result = *(const ProductionPrerequisite *)first;
	Rva00428372AdjustHeap(first, 0, last - first, val, comp);
}
