// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__unguarded_partition<S4SortElem8 *, S4SortElem8, S4Cmp00625BB0>,
// retail 0x00625DB0, 86 bytes.  Ascending scan pair with an inlined
// less-than on the float key at +4 (test ah,5 + jp/jnp) and an inlined
// two-dword swap; the pivot arrives by value on the stack.  Replica of BFME1
// stlport_unguarded_partition_s4sortelem8_score.cpp with the direct cluster
// comparator.  Leaf, no calls, no pins.

#include "S4SortElem8.h"

#include "S4Cmp00625BB0.h"

namespace _STL
{

template <class ForwardIter1, class ForwardIter2>
__declspec(dllimport) __forceinline void iter_swap(ForwardIter1 left, ForwardIter2 right)
{
	S4SortElem8 temporary = *left;
	*left = *right;
	*right = temporary;
}

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp)
{
	while (true)
	{
		while (comp(*first, pivot))
			++first;
		--last;
		while (comp(pivot, *last))
			--last;
		if (!(first < last))
			return first;
		iter_swap(first, last);
		++first;
	}
}

template S4SortElem8 *__unguarded_partition<S4SortElem8 *, S4SortElem8,
	S4Cmp00625BB0>(S4SortElem8 *, S4SortElem8 *, S4SortElem8,
	S4Cmp00625BB0);

}
