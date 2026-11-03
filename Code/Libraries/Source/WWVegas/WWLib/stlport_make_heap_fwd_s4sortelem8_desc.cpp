// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__make_heap<S4SortElem8 *, S4Cmp00625C10>,
// retail 0x006260B0, 28 bytes.  Public three-argument heap build: forwards to
// the matched five-argument worker at 0x00625FA0 with NULL type/distance tags
// plus the stateful comparator (no new pins).  Twin of the ascending
// wrapper at 0x00626090.

#include "S4SortElem8.h"

#include "S4Cmp00625C10.h"

namespace _STL
{

template <class RandomAccessIter, class Compare, class Tp, class Distance>
void __make_heap(RandomAccessIter first, RandomAccessIter last,
	Compare comp, Tp *, Distance *);

template <class RandomAccessIter, class Compare>
void __make_heap(RandomAccessIter first, RandomAccessIter last,
	Compare comp)
{
	__make_heap(first, last, comp, (S4SortElem8 *)0, (int *)0);
}

template void __make_heap<S4SortElem8 *, S4Cmp00625C10>(
	S4SortElem8 *, S4SortElem8 *, S4Cmp00625C10);

}
