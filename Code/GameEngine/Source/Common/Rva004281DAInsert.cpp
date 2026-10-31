// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// ?Rva004281DAInsert@@YAXPAUVersionBlockEntry@@UPivot24@@VVersionBlockKeyCompare@@@Z @0x004281DA 89B
// __unguarded_linear_insert for 0x18-byte version records with pivot by value.
// Evidence: neighbours swap 0x0042818F same flags; callees prereq assign 0x0042816E row ThingFactory.cpp lessEntries 0x00427C2C row VersionBlockKeyCompare.cpp version dtor 0x00238580 row VersionDestructor.cpp; callers 0x0042835F 0x00428787; same 89B shape as rowed 0x0021BAA3 with EH for non-trivial pivot and per-element assign stride 0x18.
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

void __cdecl Rva004281DAInsert(VersionBlockEntry *last, Pivot24 val, VersionBlockKeyCompare comp)
{
	VersionBlockEntry *next = last - 1;
	while (comp.lessEntries((const VersionBlockEntry *)&val, next))
	{
		*(ProductionPrerequisite *)last = *(const ProductionPrerequisite *)next;
		last = next;
		--next;
	}
	*(ProductionPrerequisite *)last = *(const ProductionPrerequisite *)&val;
}
