// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__unguarded_insertion_sort<S4SortElem8 *, S4Cmp00625C10>,
// retail 0x00625E90, 26 bytes.  Descending unguarded sort entry: forwards to
// the matched __unguarded_insertion_sort_aux at 0x00625C10 with a NULL type
// tag (_VALUE_TYPE spelling) plus the stateful comparator (no new pins).
// Twin of the ascending forwarder at 0x00625E10.

#include "S4SortElem8.h"

#include "S4Cmp00625C10.h"

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first,
	RandomAccessIter last, Tp *, Compare comp);

template <class RandomAccessIter, class Compare>
void __unguarded_insertion_sort(RandomAccessIter first,
	RandomAccessIter last, Compare comp)
{
	__unguarded_insertion_sort_aux(first, last, (S4SortElem8 *)0, comp);
}

template void __unguarded_insertion_sort<S4SortElem8 *, S4Cmp00625C10>(
	S4SortElem8 *, S4SortElem8 *, S4Cmp00625C10);

}
