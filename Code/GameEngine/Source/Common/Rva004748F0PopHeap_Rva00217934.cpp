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

void bfmePushHeap00473D60(Rva004748F0Element *first, int holeIndex,
	int topIndex, Rva004748F0Element value, Rva004748F0Compare comp);

#pragma comment(linker, "/alternatename:?bfmePushHeap00473D60@@YAXPAURva004748F0Element@@HHU1@URva004748F0Compare@@@Z=?j_00049657@@YAXXZ")

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
	bfmePushHeap00473D60(first, holeIndex, topIndex, value, comp);
}
