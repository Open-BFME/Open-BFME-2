// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// ??$__linear_insert@PAUVersionBlockEntry@@U1@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@0U1@VVersionBlockKeyCompare@@@Z @0x0042872D 122B
// _STL::__linear_insert guarded insert over 0x18-byte version records.
// Evidence: callees lessEntries 0x00427C2C row VersionBlockKeyCompare.cpp copy_backward AssignRecord24 0x004286FB row stlport_copy_backward_assign24.cpp prereq assign 0x0042816E row ThingFactory.cpp narrow copy 0x00427F75 row NarrowStringRecordCopyBFME2.cpp unguarded insert 0x004281DA row Rva004281DAInsert.cpp version dtor 0x00238580 row VersionDestructor.cpp; caller 0x0042880D; shape matches int precedent stlport_int_linear_insert.cpp with ObjectID-cast copy_backward selection and direct unguarded call.
// As in the sibling Rva00428372AdjustHeap, the by-value pivot copy constructor
// must stay an out-of-line call so /O1 emits `mov ecx,esp` before the EH ESP
// save; `??0Pivot24@@QAE@ABU0@@Z` is pinned to 0x00427F75.
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

struct BfmeAssignRecord24;

void __cdecl Rva004281DAInsert(VersionBlockEntry *last, Pivot24 val, VersionBlockKeyCompare comp);

namespace _STL { template <> BfmeAssignRecord24 * copy_backward<BfmeAssignRecord24 *,BfmeAssignRecord24 *>(BfmeAssignRecord24 *,BfmeAssignRecord24 *,BfmeAssignRecord24 *); }

namespace _STL { template <> void __linear_insert<VersionBlockEntry *,VersionBlockEntry,VersionBlockKeyCompare>(VersionBlockEntry *,VersionBlockEntry *,VersionBlockEntry,VersionBlockKeyCompare); }

namespace _STL
{
template <>
void __linear_insert<VersionBlockEntry *, VersionBlockEntry, VersionBlockKeyCompare>(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockEntry val, VersionBlockKeyCompare comp)
{
	if (comp.lessEntries((const VersionBlockEntry *)&val, (const VersionBlockEntry *)first))
	{
		copy_backward((BfmeAssignRecord24 *)first, (BfmeAssignRecord24 *)last, (BfmeAssignRecord24 *)(last + 1));
		*(ProductionPrerequisite *)first = *(const ProductionPrerequisite *)&val;
	}
	else
	{
		Rva004281DAInsert(last, *(Pivot24 *)&val, comp);
	}
}
}
