// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__unguarded_insertion_sort_aux<S4SortElem8 *, S4SortElem8,
// S4Cmp00625BB0>, retail 0x00625BB0, 84 bytes.  Ascending half of the
// stateful-comparator sort cluster around the AngleFX vector bodies: the
// comparator carries four bytes of state passed onward in ebp, and orders by
// the float key at +4 with an inlined x87 less-than (test ah,5 + jp), the
// same spelling the landed S4SortElem8LessCmp push_heap uses.  The linear
// insert is inline so the whole sort step is one loop with no calls.

#include "S4SortElem8.h"

#include "S4Cmp00625BB0.h"

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
	S4Cmp00625BB0>(S4SortElem8 *, S4SortElem8 *, S4SortElem8 *,
	S4Cmp00625BB0);

}
