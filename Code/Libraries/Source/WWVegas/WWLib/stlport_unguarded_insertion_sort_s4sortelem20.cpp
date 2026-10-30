// cl: /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's Libraries/Source/WWVegas/WWLib/stlport_ungu
// arded_insertion_sort_s4sortelem20.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ??$__unguarded_insertion_sort_aux@PAUS4S 0x00337555 (46B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.

// Open-BFME5: _STL::__unguarded_insertion_sort_aux<S4SortElem20 *,
// S4SortElem20, S4Cmp002EB8E0>, retail 0x002EA750.

// Canonical one-pointer string ownership matches the S4Name helper used by
// StringRecordCopyBFME2.cpp and S4SortElem12Swap.cpp. Retail call/field/EH
// verification below establishes applicability independently of the donor.
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct S4Name
{
	S4Name(const S4Name &other) : m_bfmeName(other.m_bfmeName) {}
	~S4Name(void) {}

	AsciiString m_bfmeName;
};

// The 12-byte tail is an STLport vector: retail's record copy (0x003371B1)
// copies it through the vector copy constructor rowed at 0x0033629E
// (stlport_vector_stringrecord_331962_allocate_copy.cpp) and the record
// destructor (0x003372B7) destroys it through the destructor rowed at
// 0x003321D8 as Rva003321D8 (RvaVectorDtorFamily.cpp; Rva003371B1Dtor.cpp
// declares the same view). Spell both owners so the record copy and
// destructor this unit emits call the rowed names, not undefined private ones.
struct BfmeStringRecord000331962;
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	vector(const vector &other);

private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}
typedef _STL::vector<BfmeStringRecord000331962, _STL::allocator<BfmeStringRecord000331962> >
	Rva0033629EVector;

struct Rva003321D8
{
	__forceinline Rva003321D8(const Rva003321D8 &other)
	{
		((Rva0033629EVector *)this)->Rva0033629EVector::vector(*(const Rva0033629EVector *)&other);
	}
	~Rva003321D8();

private:
	int m_bfmeBody[3];
};

struct S4SortElem20
{
	S4Name m_bfmeName;
	char m_bfmeFlag;
	Rva003321D8 m_bfmeTail;
};

struct S4Cmp002EB8E0
{
	int m_bfmeSlot;
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first,
	RandomAccessIter last, Tp *, Compare comp)
{
	for (RandomAccessIter i = first; i != last; ++i)
		__unguarded_linear_insert(i, *i, comp);
}

template void __unguarded_insertion_sort_aux<S4SortElem20 *, S4SortElem20,
	S4Cmp002EB8E0>(S4SortElem20 *, S4SortElem20 *, S4SortElem20 *,
	S4Cmp002EB8E0);

}
