// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
//
// ?Rva00218BD4Sort@@YAXPAURva004748F0Element@@00URva004748F0Compare@@@Z @0x00218BD4 27B
// Full-sort forwarder over the FileInfo partial-sort driver 0x002188E4.
// Passes middle/last through with a null int slot and the same compare.
// Evidence: caller 0x00218E84 pushes first/middle/last/comp; callee rowed
// partial-sort 0x002188E4; 5-push forwarder shape matches retail bytes.
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

void __cdecl Rva002188E4PartialSort(Rva004748F0Element *first, Rva004748F0Element *middle, Rva004748F0Element *last, int unused, Rva004748F0Compare comp);

void __cdecl Rva00218BD4Sort(Rva004748F0Element *first, Rva004748F0Element *middle, Rva004748F0Element *last, Rva004748F0Compare comp)
{
	Rva002188E4PartialSort(first, middle, last, 0, comp);
}
