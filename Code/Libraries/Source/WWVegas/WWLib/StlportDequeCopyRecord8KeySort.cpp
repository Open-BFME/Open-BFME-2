// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// The two key-ordered STLport sorts over the deque of 8-byte records whose
// float-ordered sorts live in stlport_deque_copyrecord8_sort.cpp (same flags,
// same record view): 0x0054C24A ascending and 0x0054C360 descending
// introsort loops and every body they reach. Their compare is out of line,
// a thiscall member taking both records by reference (ret 8) that orders
// them by the word at +0x5DA of the object reached through record.a->+4:
// 0x00549DCB ascending and 0x00549DF2 descending (rowed under placeholder
// names, pinned here under these comparators). Declaring operator() out of
// line is what gives retail's argument pushes: an inline forwarding
// comparator loads the element address early.
//
// Each body is one of four masked-identical twins (the float-ordered pair is
// rowed); the key-ordered ascending body precedes the descending one, as
// each body's REL32s back to its comparator confirm.
// __push_heap (0x0054A708 / 0x0054A79A) still schedules its compare
// arguments differently and stays pinned only; the ascending median and
// partition fold into the bodies already rowed at 0x00549F02 and 0x0054A355,
// and the ascending unguarded insertion sort into its rowed CmpKey twin.
#include <algorithm>
#include <deque>

struct Foo00549DCB;

struct BfmeCopyRecord8
{
	Foo00549DCB *a;
	float b;
	BfmeCopyRecord8() {}
	BfmeCopyRecord8(const BfmeCopyRecord8 &o) : a(o.a), b(o.b) {}
};

struct BfmeCopyRecord8KeyAscending
{
	bool operator()(const BfmeCopyRecord8 &x, const BfmeCopyRecord8 &y) const;
};

struct BfmeCopyRecord8KeyDescending
{
	bool operator()(const BfmeCopyRecord8 &x, const BfmeCopyRecord8 &y) const;
};

typedef _STL::_Deque_iterator<BfmeCopyRecord8, _STL::_Nonconst_traits<BfmeCopyRecord8> > CopyRecord8Iterator;

template void _STL::sort<CopyRecord8Iterator, BfmeCopyRecord8KeyAscending>(CopyRecord8Iterator, CopyRecord8Iterator, BfmeCopyRecord8KeyAscending);
template void _STL::sort<CopyRecord8Iterator, BfmeCopyRecord8KeyDescending>(CopyRecord8Iterator, CopyRecord8Iterator, BfmeCopyRecord8KeyDescending);
