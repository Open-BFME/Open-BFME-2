// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// 0x00332613 is __introsort_loop<Rva00332613Record*, ..., less<>> (STLport 4.5.3 _algo.c) over
// the 12-byte S4SortElem12 records ({int, AsciiString, flag}, compared on the int). Its four
// other callees are rowed under other spellings: 0x00331716 __median<int, less<int>>
// (stlport_int_algorithm_bodies.cpp; the int-keyed compare folds onto it), 0x00331962
// BfmeStringRecord00331962's copy constructor (StringRecordCopyBFME2.cpp), 0x00331D10
// __unguarded_partition<S4SortElem12*, S4SortElem12, S4Cmp002E1690>
// (stlport_introsort_loop_s4sortelem12_002e1b60.cpp) and 0x0033254D Rva0033254DPartial
// (partial_sort). Instantiating sort over this unit's record emitted non-retail median and
// partition copies, left the record's operator< unresolved and bound its copy constructor with
// /alternatename, so this unit declares only the template shapes it needs (as
// StlSweepR3Rva003F318C.cpp does) and calls the rows by their own types. Retail builds the pivot
// in the partition's argument slot with 0x00331962, so the partition is called through a cast
// whose pivot parameter is that record (its inline destructor keeps retail's EH spill of the
// argument-slot address).
struct Rva00332613Record { char bytes[12]; };
#include "string_base.h"
#include "../../../../GameEngine/Include/Common/S4SortElem12.h"
struct S4Cmp002E1690 { int m_slot; };
struct BfmeStringRecord00331962
{
	BfmeStringRecord00331962(const BfmeStringRecord00331962 &source);
	~BfmeStringRecord00331962() {}
	char bytes[12];
};

namespace _STL {
template <class T> struct less {};
template <class T, class C> const T &__median(const T &a, const T &b, const T &c, C comp);
template <class I, class T, class C> I __unguarded_partition(I first, I last, T pivot, C comp);
template <class I, class T, class S, class C> void __introsort_loop(I first, I last, T *, S depth_limit, C comp);
}

void __cdecl Rva0033254DPartial(S4SortElem12 *first, S4SortElem12 *middle, S4SortElem12 *last, S4Cmp002E1690 comp);
typedef const int &(__cdecl *Rva00331716MedianFn)(const int &, const int &, const int &, S4Cmp002E1690);
typedef const int &(__cdecl *Rva00331716RowFn)(const int &, const int &, const int &, _STL::less<int>);
typedef S4SortElem12 *(__cdecl *Rva00331D10RowFn)(S4SortElem12 *, S4SortElem12 *, S4SortElem12, S4Cmp002E1690);
typedef S4SortElem12 *(__cdecl *Rva00331D10PartitionFn)(S4SortElem12 *, S4SortElem12 *, BfmeStringRecord00331962, S4Cmp002E1690);

namespace _STL {
template <>
void __introsort_loop<Rva00332613Record *, Rva00332613Record, int, less<Rva00332613Record> >(
	Rva00332613Record *__first, Rva00332613Record *__last, Rva00332613Record *,
	int __depth_limit, less<Rva00332613Record> __comp)
{
	while (__last - __first > 16) {
		if (__depth_limit == 0) {
			Rva0033254DPartial((S4SortElem12 *)__first, (S4SortElem12 *)__last, (S4SortElem12 *)__last,
				*(S4Cmp002E1690 *)&__comp);
			return;
		}
		--__depth_limit;
		Rva00332613Record *__cut = (Rva00332613Record *)((Rva00331D10PartitionFn)static_cast<Rva00331D10RowFn>(
			&__unguarded_partition<S4SortElem12 *, S4SortElem12, S4Cmp002E1690>))(
			(S4SortElem12 *)__first, (S4SortElem12 *)__last,
			*(const BfmeStringRecord00331962 *)&((Rva00331716MedianFn)static_cast<Rva00331716RowFn>(&__median<int, less<int> >))(
				*(const int *)__first, *(const int *)(__first + (__last - __first) / 2),
				*(const int *)(__last - 1), *(S4Cmp002E1690 *)&__comp),
			*(S4Cmp002E1690 *)&__comp);
		__introsort_loop(__cut, __last, (Rva00332613Record *)0, __depth_limit, __comp);
		__last = __cut;
	}
}
}
