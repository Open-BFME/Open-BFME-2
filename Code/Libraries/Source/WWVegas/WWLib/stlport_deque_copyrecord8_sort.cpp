// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport's sort over a deque of 8-byte records ordered by the float at +4,
// with a comparator object: the introsort loop (0x0054C01E, 278B) and the
// bodies it reaches, 0x00549D9E .. 0x0054BF36, plus the unguarded insertion
// sort. Target evidence: the introsort loop is the third caller of the median
// folded at 0x005A9215 (rowed in stlport_deque_e12_sort.cpp), and retail's
// sort (0x0054C476) calls it and __final_insertion_sort (0x0054B87D).
//
// sort (0x0054C476) and its insertion-sort tail are instantiated too. Their
// copy_backward (0x0054A96C) keeps __copy_backward_aux out of line, calling the
// copy rowed at 0x0054A5AD, which only the stock STLport headers reproduce: the
// bfmealloc shim force-inlines the helper. So this unit builds without that
// shim, as stlport_copy_backward_e12.cpp does; nothing here allocates.
//
// The record is a STAND-IN, like BfmeE8 and BfmeE12: the image fixes its size
// (the deque iterator arithmetic) and the float key at +4. It also fixes its
// copy semantics, which BfmeE8 does not have. The record has a user-declared
// copy constructor that copies member by member (retail swap loads the float
// through xmm0 and spills it), while assignment stays bitwise. Every body
// below the partition depends on that, so the record gets its own name and
// does not reuse BfmeE8. The deque iterator members, which depend only on the
// size, are rowed under BfmeE8 and pinned here under this name.
//
// Two more sorts of the same records order them by a key reached through the
// pointer at +0 (0x0054C24A ascending, 0x0054C360 descending). Their compare is
// out of line: the ascending one is the rowed Rva00549DCB::rva00549DCB
// (Rva00549DCBCmp.cpp), called with the comparator object as this. Their swap
// is the float-carrying 0x00549D9E, so they sort these same records, whose
// first member is that pointer.

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

struct BfmeCopyRecord8Cmp
{
	__forceinline bool operator()(const BfmeCopyRecord8 &x, const BfmeCopyRecord8 &y) const { return x.b < y.b; }
};

// The same records sorted the other way (0x0054C134 and its family): the order
// is written as y.b < x.b, the only spelling whose median matches retail's
// 0x00549D30 (rowed by hand as Rva00549D30Median).
struct BfmeCopyRecord8CmpDescending
{
	__forceinline bool operator()(const BfmeCopyRecord8 &x, const BfmeCopyRecord8 &y) const { return y.b < x.b; }
};

// The ascending key order: the compare is the rowed member at 0x00549DCB, called
// on the comparator object.
struct Rva00549DCB
{
	bool rva00549DCB(Foo00549DCB * const &a, Foo00549DCB * const &b) const;
};

struct BfmeCopyRecord8CmpKey : Rva00549DCB
{
	__forceinline bool operator()(const BfmeCopyRecord8 &x, const BfmeCopyRecord8 &y) const { return rva00549DCB(x.a, y.a); }
};

typedef _STL::_Deque_iterator<BfmeCopyRecord8, _STL::_Nonconst_traits<BfmeCopyRecord8> > CopyRecord8Iterator;

template void _STL::__introsort_loop<CopyRecord8Iterator, BfmeCopyRecord8, int, BfmeCopyRecord8Cmp>(
	CopyRecord8Iterator, CopyRecord8Iterator, BfmeCopyRecord8 *, int, BfmeCopyRecord8Cmp);
template void _STL::__unguarded_insertion_sort<CopyRecord8Iterator, BfmeCopyRecord8Cmp>(
	CopyRecord8Iterator, CopyRecord8Iterator, BfmeCopyRecord8Cmp);

template void _STL::__introsort_loop<CopyRecord8Iterator, BfmeCopyRecord8, int, BfmeCopyRecord8CmpDescending>(
	CopyRecord8Iterator, CopyRecord8Iterator, BfmeCopyRecord8 *, int, BfmeCopyRecord8CmpDescending);
template void _STL::__unguarded_insertion_sort<CopyRecord8Iterator, BfmeCopyRecord8CmpDescending>(
	CopyRecord8Iterator, CopyRecord8Iterator, BfmeCopyRecord8CmpDescending);

// For the key order only the partition and the unguarded insertion sort are
// instantiated: its __push_heap (0x0054A708) schedules the compare's argument
// pushes differently from this forwarding comparator, and the heap chain and
// the introsort loop all reach it.
template CopyRecord8Iterator _STL::__unguarded_partition<CopyRecord8Iterator, BfmeCopyRecord8, BfmeCopyRecord8CmpKey>(
	CopyRecord8Iterator, CopyRecord8Iterator, BfmeCopyRecord8, BfmeCopyRecord8CmpKey);
template void _STL::__unguarded_insertion_sort<CopyRecord8Iterator, BfmeCopyRecord8CmpKey>(
	CopyRecord8Iterator, CopyRecord8Iterator, BfmeCopyRecord8CmpKey);

template void _STL::sort<CopyRecord8Iterator, BfmeCopyRecord8Cmp>(CopyRecord8Iterator, CopyRecord8Iterator, BfmeCopyRecord8Cmp);
template void _STL::sort<CopyRecord8Iterator, BfmeCopyRecord8CmpDescending>(CopyRecord8Iterator, CopyRecord8Iterator, BfmeCopyRecord8CmpDescending);
