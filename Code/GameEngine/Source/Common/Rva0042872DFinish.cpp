// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
// ??$__linear_insert@PAUVersionBlockEntry@@U1@VVersionBlockKeyCompare@@@_STL@@YAXPAUVersionBlockEntry@@0U1@VVersionBlockKeyCompare@@@Z @0x0042872D 122B
// _STL::__linear_insert guarded insert over 0x18-byte version records.
// Evidence: callees lessEntries 0x00427C2C row VersionBlockKeyCompare.cpp copy_backward AssignRecord24 0x004286FB row stlport_copy_backward_assign24.cpp prereq assign 0x0042816E row ThingFactory.cpp narrow copy 0x00427F75 row NarrowStringRecordCopyBFME2.cpp unguarded insert 0x004281DA row Rva004281DAInsert.cpp version dtor 0x00238580 row VersionDestructor.cpp; caller 0x0042880D; shape matches int precedent stlport_int_linear_insert.cpp with ObjectID-cast copy_backward selection and direct unguarded call.
// As in the sibling Rva00428372AdjustHeap, the by-value pivot copy constructor
// must stay an out-of-line call so /O1 emits `mov ecx,esp` before the EH ESP
// save; `??0Pivot24@@QAE@ABU0@@Z` is pinned to 0x00427F75.
struct VersionBlockEntry
{
	~VersionBlockEntry();
	char m_data[24];
};
struct BfmeAssignRecord24
{
	char m_data[24];
};
class ProductionPrerequisite
{
public:
	ProductionPrerequisite &operator=(const ProductionPrerequisite &other);
};
class VersionBlockKeyCompare
{
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
};
struct BfmeNarrowRecord00427F75
{
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &other);
	char m_data[24];
};
struct Pivot24
{
	Pivot24(const Pivot24 &other);
	~Pivot24();
	BfmeNarrowRecord00427F75 narrow;
};
// ??1Pivot24@@QAE@XZ present-unmatched
inline Pivot24::~Pivot24() { ((VersionBlockEntry *)&narrow)->~VersionBlockEntry(); }
void __cdecl Rva004281DAInsert(VersionBlockEntry *last, Pivot24 val, VersionBlockKeyCompare comp);
namespace _STL
{
template <class _InputIter, class _OutputIter>
_OutputIter copy_backward(_InputIter first, _InputIter last, _OutputIter result);
template <class _RandomAccessIter, class _Tp, class _Compare>
void __linear_insert(_RandomAccessIter first, _RandomAccessIter last, _Tp val, _Compare comp)
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
template void __linear_insert<VersionBlockEntry *, VersionBlockEntry, VersionBlockKeyCompare>(VersionBlockEntry *, VersionBlockEntry *, VersionBlockEntry, VersionBlockKeyCompare);
}
