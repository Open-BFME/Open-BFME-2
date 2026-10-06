// cl: /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common -DNDEBUG -MD -EHsc
//
// ?Rva0021889AFinalSort@@YAXPAUQ3SortElem16@@0UQ3SortCompare@@@Z @0x0021889A 74B
// Final-insertion-sort for 16B Q3 records: small ranges go straight to
// insertion-sort, large ranges insertion-sort the head 256B then sweep the
// tail with the Each (unguarded-linear-insert) helper. Evidence: caller
// 0x00218FFA; callees rowed insertion-sort 0x00218398 and Each 0x00217B07;
// threshold 0x100 matches introsort family.
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

struct BfmeElemQR;

void __cdecl __insertion_sort(Q3SortElem16 *first, Q3SortElem16 *last, Q3SortCompare comp);
void __cdecl Rva00217B07Each(BfmeElemQR *first, BfmeElemQR *last, void *extra);

void __cdecl Rva0021889AFinalSort(Q3SortElem16 *first, Q3SortElem16 *last, Q3SortCompare comp)
{
	if ((((char *)last - (char *)first) & -16) > 256)
	{
		Q3SortElem16 *split = (Q3SortElem16 *)((char *)first + 256);
		__insertion_sort(first, split, comp);
		Rva00217B07Each((BfmeElemQR *)split, (BfmeElemQR *)last, comp.m_state);
	}
	else
		__insertion_sort(first, last, comp);
}
