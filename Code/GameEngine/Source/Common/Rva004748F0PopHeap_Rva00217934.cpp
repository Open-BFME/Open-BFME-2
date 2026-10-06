// cl: -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common

// STLport __pop_heap over the sixteen-byte record used by the neighbouring
// heap helpers. Retail 0x004748F0 copies three scalar words and an
// AsciiString, then calls __adjust_heap at 0x00474330 with the element count.

#include "ascii_string.h"

struct Rva004748F0Element
{
	int m_key;
	int m_second;
	int m_third;
	AsciiString m_name;
};

struct Rva004748F0Compare
{
	int m_state;
};

struct Q3SortElem16
{
	int m_a;
	int m_b;
	int m_c;
	AsciiString m_d;
};

struct Q3SortCompare
{
	void *m_state;
};

void __push_heap(Q3SortElem16 *first, int holeIndex,
	int topIndex, Q3SortElem16 value, Q3SortCompare comp);

void bfmeAdjustHeap00474330(Rva004748F0Element *first, int holeIndex,
	int len, Rva004748F0Element value, Rva004748F0Compare comp)
{
	int topIndex = holeIndex;
	int secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if (first[secondChild].m_key < first[secondChild - 1].m_key)
			--secondChild;
		first[holeIndex] = first[secondChild];
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		first[holeIndex] = first[secondChild - 1];
		holeIndex = secondChild - 1;
	}
	__push_heap((Q3SortElem16 *)first, holeIndex, topIndex,
		*(Q3SortElem16 *)&value, *(Q3SortCompare *)&comp);
}
