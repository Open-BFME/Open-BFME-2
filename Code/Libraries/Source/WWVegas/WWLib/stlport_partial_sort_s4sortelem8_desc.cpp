// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__partial_sort<S4SortElem8 *, S4SortElem8, S4Cmp00625C10>,
// retail 0x006265B0, 125 bytes.  Descending twin: heap build via the matched
// __make_heap at 0x00625FA0, greater-than scan (test ah,0x41 + jne), adjust
// into the matched __adjust_heap at 0x00625CF0, then the matched sort_heap
// at 0x006263C0.  All callees are matched rows (no new pins).  This address
// was once structurally guessed as vector insert; the sort shape refutes it.

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

template <class RandomAccessIterator, class Compare, class Tp, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare comp, Tp *, Distance *);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

template <class RandomAccessIterator, class Compare>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare comp);

template <class RandomAccessIterator, class Tp, class Compare>
void __partial_sort(RandomAccessIterator first,
	RandomAccessIterator middle, RandomAccessIterator last, Tp *,
	Compare comp)
{
	__make_heap(first, middle, comp, (Tp *)0, (int *)0);
	for (RandomAccessIterator i = middle; i < last; ++i)
	{
		if (comp(*i, *first))
		{
			Tp item = *i;
			*i = *first;
			__adjust_heap(first, 0, (int)(middle - first), item, comp);
		}
	}
	sort_heap(first, middle, comp);
}

template void __partial_sort<S4SortElem8 *, S4SortElem8,
	S4Cmp00625C10>(S4SortElem8 *, S4SortElem8 *, S4SortElem8 *,
	S4SortElem8 *, S4Cmp00625C10);

}
