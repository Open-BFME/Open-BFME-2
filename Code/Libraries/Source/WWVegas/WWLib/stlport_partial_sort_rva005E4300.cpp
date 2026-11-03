// The comparator carries the army context at +0 (native 5E4300); keep
// its four-byte state and class spelling consistent through the sort family.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ??$__partial_sort@PAHHVRva005E4300Cmp@@@_STL@@YAXPAH000VRva005E4300Cmp@@@Z @0x005E5177 92B
// STL partial sort over int keys with stateful comparator Rva005E4300Cmp at
// 0x005E4300; calls rowed make_heap 0x005E4C73 and rowed pop 0x005E4A5F and
// rowed sort_heap rva005E50A7. Evidence: same 92B shape as Rva00204BB8
// precedent 0x00209A62; retail calls all Rva005E4300Cmp helpers.
struct Rva005E4300Context;
#include "Rva005E4300Cmp.h"
void __cdecl rva005E50A7(int *first, int *last, Rva005E4300Cmp comp);
namespace _STL
{
template <class RandomAccessIter, class Compare>
void make_heap(RandomAccessIter first, RandomAccessIter last, Compare comp);
template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, Tp val, Compare comp);
template <class RandomAccessIter, class Tp, class Compare>
void __pop_heap(RandomAccessIter first, RandomAccessIter last, RandomAccessIter result, Tp val, Compare comp);
template <class RandomAccessIter, class Tp, class Compare>
void __partial_sort(RandomAccessIter first, RandomAccessIter middle, RandomAccessIter last, Tp *, Compare comp)
{
	make_heap(first, middle, comp);
	for (RandomAccessIter i = middle; i < last; ++i) {
		if (comp(*i, *first)) {
			typedef void (__cdecl *PopHeap5)(int *, int *, int *, int, Rva005E4300Cmp);
			typedef void (__cdecl *PopHeap6)(int *, int *, int *, int, Rva005E4300Cmp, int);
			PopHeap5 fn5 = (PopHeap5)&_STL::__pop_heap<int *, int, Rva005E4300Cmp>;
			PopHeap6 fn6 = (PopHeap6)fn5;
			fn6(first, middle, i, *i, comp, 0);
		}
	}
	rva005E50A7(first, middle, comp);
}
template void __partial_sort<int *, int, Rva005E4300Cmp>(int *, int *, int *, int *, Rva005E4300Cmp);
}
