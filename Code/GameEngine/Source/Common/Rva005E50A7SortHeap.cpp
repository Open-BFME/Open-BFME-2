// The comparator carries the army context at +0 (native 5E4300); keep
// its four-byte state and class spelling consistent through the sort family.
// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
struct Rva005E4300Context;
#include "../../../Libraries/Source/WWVegas/WWLib/Rva005E4300Cmp.h"
namespace _STL
{
template <class RandomAccessIter, class Compare>
void pop_heap(RandomAccessIter first, RandomAccessIter last, Compare comp);
}
void __cdecl rva005E50A7(int *first, int *last, Rva005E4300Cmp comp)
{
	int n = (char *)last - (char *)first;
	if ((n & ~3) <= 4)
		return;
	int m = n;
	for (;;) {
		_STL::pop_heap(first, last, comp);
		last = (int *)((char *)last - 4);
		m -= 4;
		if ((m & ~3) <= 4)
			break;
	}
}
