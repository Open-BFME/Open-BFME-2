// ??$__unguarded_partition@PAUTreeHintRef00217D4C@@U1@URva004F9185Cmp@@@_STL@@YAPAUTreeHintRef00217D4C@@PAU1@0U1@URva004F9185Cmp@@@Z
// partial score=0.96 date=2026-10-05
// ??$__unguarded_partition@PAUTreeHintRef00217D4C@@U1@URva004F9185Cmp@@@_STL@@YAPAUTreeHintRef00217D4C@@PAU1@0U1@URva004F9185Cmp@@@Z
// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??$__unguarded_partition@PAUTreeHintRef00217D4C@@U1@URva004F9185Cmp@@@_STL@@YAPAUTreeHintRef00217D4C@@PAU1@0U1@URva004F9185Cmp@@@Z, retail 0x004F71A8, 203 bytes.
// Quicksort partition over TreeHintRef keys with inlined Rva004F9185Cmp (m_key +0xC via m_08).
// Evidence: caller 0x004F91DA in introsort_loop TU PAUTreeHintRef00217D4CRva004F9565.cpp; 5 calls rowed to Release 0x0007DEEF; swap call pinned at 0x004F6542 as AsciiString swap (body is TreeHintRef assigns, called via AsciiString name to match pin); same shape as stlport_unguarded_partition_rva005E4300.cpp with refcounted temps and EH states.

struct Key004F9185 { int _00[3]; int m_key; };
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; Key004F9185 *m_08; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) { if (m_ptr) ++m_ptr->references; }
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	__forceinline ~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct Rva004F9185Cmp
{
	__forceinline bool operator()(TreeHintRef00217D4C a, TreeHintRef00217D4C b) const { int ka = a.m_ptr->m_08->m_key; int kb = b.m_ptr->m_08->m_key; return ka > kb; }
};

class AsciiString;
namespace _STL
{
	template <class _Tp> void swap(_Tp &a, _Tp &b);
// ??$__unguarded_partition@PAUTreeHintRef00217D4C@@U1@URva004F9185Cmp@@@_STL@@YAPAUTreeHintRef00217D4C@@PAU1@0U1@URva004F9185Cmp@@@Z present-unmatched
	template <class _RandomAccessIter, class _Tp, class _Compare>
	_Tp * __unguarded_partition(_RandomAccessIter first, _RandomAccessIter last, _Tp pivot, _Compare comp)
	{
		while (true)
		{
			while (comp(*first, pivot))
				++first;
			--last;
			while (comp(pivot, *last))
				--last;
			if (!(first < last))
				return first;
			swap((AsciiString &)*first, (AsciiString &)*last);
			++first;
		}
	}
	template TreeHintRef00217D4C *__unguarded_partition<TreeHintRef00217D4C *, TreeHintRef00217D4C, Rva004F9185Cmp>(TreeHintRef00217D4C *, TreeHintRef00217D4C *, TreeHintRef00217D4C, Rva004F9185Cmp);
}
