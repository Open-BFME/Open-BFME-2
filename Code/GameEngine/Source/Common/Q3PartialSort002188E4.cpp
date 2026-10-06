// cl: /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common -DNDEBUG -MD -EHsc
//
// ?Rva002188E4PartialSort@@YAXPAURva004748F0Element@@00HURva004748F0Compare@@@Z @0x002188E4 94B
// Partial-sort driver for MixFileCreator FileInfo records: make-heap, sweep
// middle..last with pop-heap on smaller keys, then sort-heap the head.
// Evidence: caller 0x00218BD4 pushes 5 dwords; callees rowed MakeHeap
// 0x00217F7D PopHeap 0x00217B37 SortHeap 0x002183D1 copy ctor 0x00217624;
// 16B stride matches FileInfoStruct/Q3SortElem16/Rva004748F0Element.
#include "ascii_string.h"

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

class MixFileCreator
{
public:
	struct FileInfoStruct
	{
		unsigned long CRC;
		unsigned long Offset;
		unsigned long Size;
		AsciiString Filename;
	};
};

void __cdecl Rva00217F7DMake(Q3SortElem16 *first, Q3SortElem16 *last, Q3SortCompare comp);
void __cdecl Rva004748F0PopHeap(Rva004748F0Element *first, Rva004748F0Element *last, Rva004748F0Element *result, Rva004748F0Element value, Rva004748F0Compare comp, int *);
void __cdecl Rva002183D1SortHeap(Rva004748F0Element *first, Rva004748F0Element *last, Rva004748F0Compare comp);

void __cdecl Rva002188E4PartialSort(Rva004748F0Element *first, Rva004748F0Element *middle, Rva004748F0Element *last, int unused, Rva004748F0Compare comp)
{
	Q3SortCompare qcomp;
	qcomp.m_state = (void *)comp.m_state;
	Rva00217F7DMake((Q3SortElem16 *)first, (Q3SortElem16 *)middle, qcomp);
	for (Rva004748F0Element *cur = middle; cur < last; ++cur)
	{
		if (cur->m_key < first->m_key)
			Rva004748F0PopHeap(first, middle, cur, *cur, comp, 0);
	}
	Rva002183D1SortHeap(first, middle, comp);
}
