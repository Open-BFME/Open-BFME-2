// ??$__linear_insert@U?$_Deque_iterator@UBfmeCopyRecord8@@U?$_Nonconst_traits@UBfmeCopyRecord8@@@_STL@@@_STL@@UBfmeCopyRecord8@@UBfmeCopyRecord8CmpKey@@@_STL@@YAXU?$_Deque_iterator@UBfmeCopyRecord8@@U?$_Nonconst_traits@UBfmeCopyRecord8@@@_STL@@@0@0UBfmeCopyRecord8@@UBfmeCopyRecord8CmpKey@@@Z
// partial score=0.92 date=2026-10-09
// ??$__linear_insert@U?$_Deque_iterator@UBfmeCopyRecord8@@U?$_Nonconst_traits@UBfmeCopyRecord8@@@_STL@@@_STL@@UBfmeCopyRecord8@@UBfmeCopyRecord8CmpKey@@@_STL@@YAXU?$_Deque_iterator@UBfmeCopyRecord8@@U?$_Nonconst_traits@UBfmeCopyRecord8@@@_STL@@@0@0UBfmeCopyRecord8@@UBfmeCopyRecord8CmpKey@@@Z
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport4.5.3 reference __linear_insert, target54AE4A..54AED7.
// Target compare549DCB/copy_backward54A96C/unguarded54A086 fix the
// CmpKey family, not an invented KeyAscending callee alias. Record8 and
// pointer-key/float layouts follow the established home source views.
// Fresh138B: compiler reuses dead first iterator parameter as discarded
// result buffer, while native keeps a16B local; also differs in value-copy
// scheduling. G6/EHa/EHs stay138; Og-207. No Code edit or new pin.
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

template void _STL::__linear_insert<CopyRecord8Iterator, BfmeCopyRecord8, BfmeCopyRecord8CmpKey>(CopyRecord8Iterator,CopyRecord8Iterator,BfmeCopyRecord8,BfmeCopyRecord8CmpKey);
