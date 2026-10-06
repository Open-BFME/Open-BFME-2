// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /Oy-

// Target evidence: the byte-verified __adjust_heap body at 0x0033758C calls
// this 136-byte helper at +0x89. Retail compares the parent and saved value
// through the 0x000069D6 AsciiString compare alias and moves records through
// the matched assignment at 0x003372EC. Ghidra bounds the helper at 136B.
// The address-derived 0x00337479 attempt was previously blocked while its
// record and comparator identities were unresolved; the adjacent verified
// S4SortElem20 heap worker now supplies the supported call context.
//
// Donor: Open-BFME-1
// Libraries/Source/WWVegas/WWLib/stlport_push_heap_s4sortelem20.cpp at
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76. The heap algorithm is
// donor-derived; the target key comparison and helper addresses come from
// BFME2 disassembly and rowed neighboring methods.

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
	Distance topIndex, Tp value, Compare comp)
{
	Distance parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex &&
		(first + parent)->m_bfmeName.compare(value.m_bfmeName) < 0)
	{
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = value;
}

template void __push_heap<S4SortElem20 *, int, S4SortElem20,
	S4Cmp002EB8E0>(S4SortElem20 *, int, int, S4SortElem20,
	S4Cmp002EB8E0);

}
