// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__unguarded_insertion_sort<S4SortElem8 *, S4Cmp00625BB0>,
// retail 0x00625E10, 32 bytes.  Ascending unguarded sort entry: forwards to
// the matched __unguarded_insertion_sort_aux at 0x00625BB0 with a NULL type
// tag (_VALUE_TYPE spelling) plus the stateful comparator (no new pins).
// Twin of the descending forwarder at 0x00625E90.

#include "S4SortElem8.h"

struct S4Cmp00625BB0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey < b.m_bfmeKey;
	}
};

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

template void __unguarded_insertion_sort<S4SortElem8 *, S4Cmp00625BB0>(
	S4SortElem8 *, S4SortElem8 *, S4Cmp00625BB0);

}
