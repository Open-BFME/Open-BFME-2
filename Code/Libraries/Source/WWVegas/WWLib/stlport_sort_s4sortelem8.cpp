// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::sort<S4SortElem8 *, S4Cmp00625BB0>, retail 0x00626940, 74 bytes.
// Ascending sort driver (BFME1 stlport_sort_s4sortelem20.cpp depth shape):
// depth is twice the floor log2 of the element count, then the matched
// __introsort_loop at 0x00626780 plus the matched __final_insertion_sort at
// 0x006266A0.  Both callees are matched rows (no new pins).  Called by the
// flag-selected member at 0x006269E0.

#include "S4SortElem8.h"

#include "S4Cmp00625BB0.h"

namespace _STL
{

template <class RandomAccessIter, class Tp, class Distance, class Compare>
void __introsort_loop(RandomAccessIter first, RandomAccessIter last,
	Tp *, Distance depth, Compare comp);

template <class RandomAccessIter, class Compare>
void __final_insertion_sort(RandomAccessIter first, RandomAccessIter last,
	Compare comp);

template <class RandomAccessIter, class Compare>
void sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	if (first != last)
	{
		int n = last - first;
		int k;
		for (k = 0; n != 1; n >>= 1)
			++k;
		__introsort_loop(first, last, (S4SortElem8 *)0, k * 2, comp);
		__final_insertion_sort(first, last, comp);
	}
}

template void sort<S4SortElem8 *, S4Cmp00625BB0>(
	S4SortElem8 *, S4SortElem8 *, S4Cmp00625BB0);

}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeSortBVJX@@YAXPAUBfmeElemVJX@@0UBfmeCmpVJX@@@Z=??$sort@PAUS4SortElem8@@US4Cmp00625BB0@@@_STL@@YAXPAUS4SortElem8@@0US4Cmp00625BB0@@@Z")
