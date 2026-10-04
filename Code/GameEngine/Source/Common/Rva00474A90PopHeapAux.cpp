// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common

// STLport __pop_heap_aux over the sixteen-byte record of the neighbouring heap
// helpers. Retail 0x00474A90 steps back one element and forwards it by value to
// __pop_heap at 0x004748F0 through the 0x0000561E jump stub.

// AsciiString and its StringBase<char> base come from the canonical header
// (reverse/canonical_classes.csv); the donor's private copy is the view the
// class gate refuses.
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

void Rva004748F0PopHeap(Rva004748F0Element *first, Rva004748F0Element *last,
	Rva004748F0Element *result, Rva004748F0Element value,
	Rva004748F0Compare comp, int *);

#pragma comment(linker, "/alternatename:?Rva004748F0PopHeap@@YAXPAURva004748F0Element@@00U1@URva004748F0Compare@@PAH@Z=?j_0000561e@@YAXXZ")

void Rva00474A90PopHeapAux(Rva004748F0Element *first, Rva004748F0Element *last,
	Rva004748F0Element *, Rva004748F0Compare comp)
{
	Rva004748F0PopHeap(first, last - 1, last - 1, *(last - 1), comp, (int *)0);
}
