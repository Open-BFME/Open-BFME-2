// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__adjust_heap<S4SortElem8 *, int, S4SortElem8, S4Cmp00625C10>,
// retail 0x00625CF0, 122 bytes.  Descending twin: greater-than child pick,
// tail resolves to the landed 0x00625AD0 body via a template-name alias pin.
// No other pins.

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
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp)
{
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if (comp(*(first + secondChild), *(first + (secondChild - 1))))
			secondChild--;
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}
	__push_heap(first, holeIndex, topIndex, val, comp);
}

template void __adjust_heap<S4SortElem8 *, int, S4SortElem8, S4Cmp00625C10>(
	S4SortElem8 *, int, int, S4SortElem8, S4Cmp00625C10);

}
