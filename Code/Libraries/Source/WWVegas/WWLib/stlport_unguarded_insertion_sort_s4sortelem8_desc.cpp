// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__unguarded_insertion_sort_aux<S4SortElem8 *, S4SortElem8,
// S4Cmp00625C10>, retail 0x00625C10, 84 bytes.  Descending twin of the
// 0x00625BB0 body: same stateful-comparator cluster, greater-than on the
// float key at +4 (test ah,0x41 + jne), inline linear insert, one loop.

#include "S4SortElem8.h"

#include "S4Cmp00625C10.h"

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
inline void __unguarded_linear_insert(RandomAccessIter last, Tp val,
	Compare comp)
{
	RandomAccessIter next = last;
	--next;
	while (comp(val, *next))
	{
		*last = *next;
		last = next;
		--next;
	}
	*last = val;
}

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first,
	RandomAccessIter last, Tp *, Compare comp)
{
	for (RandomAccessIter i = first; i != last; ++i)
		__unguarded_linear_insert(i, *i, comp);
}

template void __unguarded_insertion_sort_aux<S4SortElem8 *, S4SortElem8,
	S4Cmp00625C10>(S4SortElem8 *, S4SortElem8 *, S4SortElem8 *,
	S4Cmp00625C10);

}
