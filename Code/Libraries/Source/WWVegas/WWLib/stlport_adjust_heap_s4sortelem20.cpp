// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /Oy-

// Target evidence: the byte-verified __pop_heap worker at 0x003376EA calls
// this 172-byte helper at +0x3F. Its loop scales indexes by 20, compares the
// AsciiString key through the rowed 0x000069D6 compare body, assigns elements
// through 0x003372EC, and finishes through the push helper at 0x00337479.
// The BFME1 donor supplies the heap algorithm and 20-byte record view; the
// compare, assignment, copy-constructor, destructor, and helper addresses are
// fixed by BFME2 retail call sites.
//
// Donor: Open-BFME-1
// Libraries/Source/WWVegas/WWLib/stlport_adjust_heap_s4sortelem20.cpp at
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76. The /O1 /G7 /Oy- flags
// follow the matched BFME2 S4SortElem12 adjust_heap sibling; BFME2's shared
// AsciiString facade keeps comparison out of line at the target call site.

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
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp value, Compare comp);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp value, Compare comp)
{
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if ((first + secondChild)->m_bfmeName.compare(
			(first + (secondChild - 1))->m_bfmeName) < 0)
			secondChild--;
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}
	__push_heap(first, holeIndex, topIndex, value, comp);
}

template void __adjust_heap<S4SortElem20 *, int, S4SortElem20,
	S4Cmp002EB8E0>(S4SortElem20 *, int, int, S4SortElem20,
	S4Cmp002EB8E0);

}
