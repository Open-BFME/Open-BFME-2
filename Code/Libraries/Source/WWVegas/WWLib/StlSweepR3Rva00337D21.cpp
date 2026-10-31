// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// 0x00337D21 is __introsort_loop<Rva00337D21Record*, ..., less<>> (STLport 4.5.3 _algo.c) over
// the 20-byte S4SortElem20 / Rva003371B1 records (string-keyed). Its four other callees are
// rowed under other spellings: 0x00335CFD Rva00335CFMedian over AsciiString pointers
// (Rva00335CFMedian.cpp), 0x003371B1 Rva003371B1's copy constructor (Rva003371B1Copy.cpp),
// 0x00337655 __unguarded_partition<S4SortElem20*, S4SortElem20, S4Cmp002EB8E0>
// (stlport_unguarded_partition_s4sortelem20.cpp) and 0x00337C55
// partial_sort<Rva003371B1*, Rva00337C55Less> (stlport_partial_sort_rva00337c55.cpp).
// Instantiating sort over this unit's record emitted non-retail median and partition copies,
// left the record's operator< unresolved and bound its copy constructor with /alternatename,
// so this unit declares only the template shapes it needs (as StlSweepR3Rva00332613.cpp does)
// and calls the rows by their own types. Retail passes the median its comparator as a fourth
// argument and builds the pivot in the partition's argument slot with 0x003371B1, so both are
// called through casts (declaring the pivot record's destructor, rowed at 0x003372B7, keeps
// retail's EH spill of the argument-slot address).
struct Rva00337D21Record { char bytes[20]; };
struct S4SortElem20 { char m_pad[20]; };
struct S4Cmp002EB8E0 { int m_slot; };
struct Rva00337C55Less {};
class AsciiString;
class Rva003371B1
{
public:
	Rva003371B1(const Rva003371B1 &other);
	~Rva003371B1();
private:
	char m_bytes[20];
};

namespace _STL {
template <class T> struct less;
template <> struct less<Rva00337D21Record> {};
template <class I, class T, class C> I __unguarded_partition(I first, I last, T pivot, C comp);
template <> S4SortElem20 *__unguarded_partition<S4SortElem20 *, S4SortElem20, S4Cmp002EB8E0>(S4SortElem20 *, S4SortElem20 *, S4SortElem20, S4Cmp002EB8E0);
template <class I, class T, class S, class C> void __introsort_loop(I first, I last, T *, S depth_limit, C comp);
template <class I, class C> void partial_sort(I first, I middle, I last, C comp);
}

const AsciiString *Rva00335CFMedian(const AsciiString *a, const AsciiString *b, const AsciiString *c);
typedef const Rva003371B1 *(__cdecl *Rva00335CFDMedianFn)(const Rva00337D21Record *, const Rva00337D21Record *, const Rva00337D21Record *, S4Cmp002EB8E0);
typedef S4SortElem20 *(__cdecl *Rva00337655RowFn)(S4SortElem20 *, S4SortElem20 *, S4SortElem20, S4Cmp002EB8E0);
typedef S4SortElem20 *(__cdecl *Rva00337655PartitionFn)(S4SortElem20 *, S4SortElem20 *, Rva003371B1, S4Cmp002EB8E0);

namespace _STL {
template <>
void __introsort_loop<Rva00337D21Record *, Rva00337D21Record, int, less<Rva00337D21Record> >(
	Rva00337D21Record *__first, Rva00337D21Record *__last, Rva00337D21Record *,
	int __depth_limit, less<Rva00337D21Record> __comp)
{
	while (__last - __first > 16) {
		if (__depth_limit == 0) {
			partial_sort((Rva003371B1 *)__first, (Rva003371B1 *)__last, (Rva003371B1 *)__last,
				*(Rva00337C55Less *)&__comp);
			return;
		}
		--__depth_limit;
		Rva00337D21Record *__cut = (Rva00337D21Record *)((Rva00337655PartitionFn)static_cast<Rva00337655RowFn>(
			&__unguarded_partition<S4SortElem20 *, S4SortElem20, S4Cmp002EB8E0>))(
			(S4SortElem20 *)__first, (S4SortElem20 *)__last,
			*((Rva00335CFDMedianFn)&Rva00335CFMedian)(
				__first, __first + (__last - __first) / 2, __last - 1, *(S4Cmp002EB8E0 *)&__comp),
			*(S4Cmp002EB8E0 *)&__comp);
		__introsort_loop(__cut, __last, (Rva00337D21Record *)0, __depth_limit, __comp);
		__last = __cut;
	}
}
}
