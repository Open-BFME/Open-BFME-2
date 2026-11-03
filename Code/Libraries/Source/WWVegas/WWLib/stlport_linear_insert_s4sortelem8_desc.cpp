// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__linear_insert<S4SortElem8 *, S4SortElem8, S4Cmp00625C10>,
// retail 0x006262E0, 114 bytes.  Descending twin: greater-than on the float key at +4, unguarded arm is bfmeLinearInsertFloatDescending at 0x00625A30 via alias pin.
// less-than on the float key at +4 selects the copy-backward shift (inlined
// dword loop) or the unguarded arm, which is the already-matched
// bfmeLinearInsertFloatDescending body at 0x00625A30 under a template-name
// alias pin (same folded bytes; BFME1 routes its BfmeSortPair twin the same
// way).  Replica of BFME1 stlport_linear_insert_bfmesortpair_ascending.cpp
// with the stateful cluster comparator.

#include "S4SortElem8.h"

#include "S4Cmp00625C10.h"

namespace _STL
{

struct random_access_iterator_tag
{
};

template <class RandomAccessIter, class BidirectionalIter, class Distance>
__forceinline BidirectionalIter __copy_backward(RandomAccessIter first,
	RandomAccessIter last, BidirectionalIter result,
	const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0; --count)
		*--result = *--last;
	return result;
}

template<> __declspec(dllimport) __forceinline
S4SortElem8* __copy_backward<S4SortElem8*,S4SortElem8*,int>(S4SortElem8* first,S4SortElem8* last,S4SortElem8* result,const random_access_iterator_tag &,int *) {
 for(int count=last-first;count>0;--count) *--result=*--last;
 return result;
}

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last, Tp val,
	Compare comp)
{
	if (comp(val, *first))
	{
		random_access_iterator_tag tag;
		__copy_backward(first, last, last + 1, tag, (int *)0);
		*first = val;
	}
	else
	{
		__unguarded_linear_insert(last, val, comp);
	}
}

template void __linear_insert<S4SortElem8 *, S4SortElem8,
	S4Cmp00625C10>(S4SortElem8 *, S4SortElem8 *, S4SortElem8,
	S4Cmp00625C10);

}
