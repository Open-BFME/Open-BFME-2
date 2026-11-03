// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__insertion_sort<S4SortElem8 *, S4Cmp00625C10>, retail 0x006264F0,
// 59 bytes.  Descending twin: per-element calls into the matched
// __linear_insert at 0x006262E0 (no new pins).

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

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last, Tp val,
	Compare comp);

template <class RandomAccessIter, class Compare>
void __insertion_sort(RandomAccessIter first, RandomAccessIter last,
	Compare comp)
{
	if (first == last)
		return;

	for (RandomAccessIter i = first + 1; i != last; ++i)
		__linear_insert(first, i, *i, comp);
}

template void __insertion_sort<S4SortElem8 *, S4Cmp00625C10>(
	S4SortElem8 *, S4SortElem8 *, S4Cmp00625C10);

}
