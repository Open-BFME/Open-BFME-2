// cl: /Ireference/shims/bfme2_ascii /Os /DNDEBUG /MD /EHsc
//
// STLport __pop_heap over the twenty-byte S4SortElem20 family.
// Target evidence: retail's 95-byte boundary is 0x003376EA, reached from
// the rowed 0x003377BC forwarder. It copies result from first through the
// helper at 0x003372EC, constructs the by-value value through 0x003371B1,
// computes (last-first)/20, calls __adjust_heap at 0x0033758C, then destroys
// the temporary through 0x003372B7. The call target at 0x003372EC also has
// the BFME1 donor's S4SortElem20 assignment candidate pin; the target body
// remains rowed under its own worker identity only after byte verification.
// Ghidra gives the worker boundary as 95 bytes.
//
// Donor guidance: Open-BFME-1
// Libraries/Source/WWVegas/WWLib/stlport_pop_heap_s4sortelem20.cpp at
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, compiled with the flags
// above. Its STLport specialization establishes the algorithm and 20-byte
// element stride; target call sites and the 20-byte temporary establish the
// target-specific helper addresses and object size.

#include "ascii_string.h"

struct BfmeSortTailElement12;

class BfmeSortElem20Tail
{
public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
	~BfmeSortElem20Tail();
	void set(const BfmeSortElem20Tail &other);

private:
	BfmeSortTailElement12 *m_begin;
	BfmeSortTailElement12 *m_end;
	BfmeSortTailElement12 *m_capacity;
};

struct S4SortElem20
{
	AsciiString m_bfmeName;
	char m_bfmeFlag;
	BfmeSortElem20Tail m_bfmeTail;

	S4SortElem20(const S4SortElem20 &other);
	~S4SortElem20();
	S4SortElem20 &operator=(const S4SortElem20 &other);
};

struct S4Cmp002EB8E0
{
	int m_bfmeSlot;
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp value, Compare comp);

template <class RandomAccessIterator, class Tp, class Compare, class Distance>
void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
	RandomAccessIterator result, Tp value, Compare comp, Distance *);

template <>
void __pop_heap<S4SortElem20 *, S4SortElem20, S4Cmp002EB8E0, int>(
	S4SortElem20 *first, S4SortElem20 *last, S4SortElem20 *result,
	S4SortElem20 value, S4Cmp002EB8E0 comp, int *)
{
	*result = *first;
	__adjust_heap(first, 0,
		(int)(((char *)last - (char *)first) / 20), value, comp);
}

}
