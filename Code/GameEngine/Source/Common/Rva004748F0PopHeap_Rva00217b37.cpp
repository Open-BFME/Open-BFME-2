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

void bfmeAdjustHeap00474330(Rva004748F0Element *first, int holeIndex,
	int len, Rva004748F0Element value, Rva004748F0Compare comp);

void Rva004748F0PopHeap(Rva004748F0Element *first,
	Rva004748F0Element *last, Rva004748F0Element *result,
	Rva004748F0Element value, Rva004748F0Compare comp, int *)
{
	*result = *first;
	bfmeAdjustHeap00474330(first, 0, last - first, value, comp);
}
