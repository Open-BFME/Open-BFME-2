// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// ?Rva00428233PushHeap@@YAXPAUVersionBlockEntry@@HHUPivot24@@VVersionBlockKeyCompare@@@Z @0x00428233 138B
// __push_heap sift-up for 0x18-byte version records with pivot by value.
// Evidence: neighbours same flags; callees lessEntries 0x00427C2C row prereq assign 0x0042816E row version dtor 0x00238580 row; caller 0x004283FE; unblocks 0x00428372; same STLport spelling as rowed 0x002059CF with parent hole-top indices and imul 0x18 stride.
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

void __cdecl Rva00428233PushHeap(VersionBlockEntry *first, int holeIndex, int topIndex, Pivot24 val, VersionBlockKeyCompare comp)
{
	int parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex)
	{
		if (!comp.lessEntries(first + parent, (const VersionBlockEntry *)&val))
			break;
		*(ProductionPrerequisite *)(first + holeIndex) = *(const ProductionPrerequisite *)(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(ProductionPrerequisite *)(first + holeIndex) = *(const ProductionPrerequisite *)&val;
}
