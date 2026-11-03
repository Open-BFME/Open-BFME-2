// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__pop_heap<S4SortElem8 *, int, S4SortElem8, S4Cmp00625C10>,
// retail 0x00625EF0, 55 bytes.  Descending pop-heap worker: moves *first out
// to result, then sifts with the matched __adjust_heap at 0x00625CF0 (tail
// call resolves via its ledger row, no new pins).  Twin of the ascending
// worker at 0x00625EB0.

#include "S4SortElem8.h"

struct S4Cmp00625C10
{
	void *m_bfmeState;

	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey > b.m_bfmeKey;
	}
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp value, Compare comp);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
	RandomAccessIterator result, Tp value, Compare comp, Distance *)
{
	*result = *first;
	__adjust_heap(first, 0, last - first, value, comp);
}

template void __pop_heap<S4SortElem8 *, int, S4SortElem8, S4Cmp00625C10>(
	S4SortElem8 *, S4SortElem8 *, S4SortElem8 *, S4SortElem8,
	S4Cmp00625C10, int *);

}
