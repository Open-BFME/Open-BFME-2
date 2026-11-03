// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__final_insertion_sort<S4SortElem8 *, S4Cmp00625C10>, retail
// 0x006266F0, 78 bytes.  Descending twin: guarded insertion sort plus the
// matched unguarded aux at 0x00625C10.  Both callees are matched rows
// (no new pins).

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

const int __stl_threshold = 16;

template <class RandomAccessIter, class Compare>
void __insertion_sort(RandomAccessIter first, RandomAccessIter last,
	Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first,
	RandomAccessIter last, Tp *, Compare comp);

template <class RandomAccessIter, class Compare>
void __final_insertion_sort(RandomAccessIter first, RandomAccessIter last,
	Compare comp)
{
	if (last - first > __stl_threshold)
	{
		__insertion_sort(first, first + __stl_threshold, comp);
		__unguarded_insertion_sort_aux(first + __stl_threshold, last,
			(S4SortElem8 *)0, comp);
	}
	else
		__insertion_sort(first, last, comp);
}

template void __final_insertion_sort<S4SortElem8 *, S4Cmp00625C10>(
	S4SortElem8 *, S4SortElem8 *, S4Cmp00625C10);

}
