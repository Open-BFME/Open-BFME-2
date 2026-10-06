// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__partial_sort@PAHHVRva00204BB8@@@_STL@@YAXPAH000VRva00204BB8@@@Z @0x00209A62 92B
// STL partial sort over int sort keys with the rowed thiscall comparator
// Rva00204BB8 at 0x00204BB8; calls rowed make fwd 0x00207BAA, rowed pop
// 0x002074D4, rowed sort_heap 0x002082B7 and rowed comparator.
// Evidence: chain via landed heap helpers; same flags and comparator as
// stlport_adjust_heap_rva00204bb8.cpp and __partial_sort precedent in
// stlport_push_heap_rva00422ca8.cpp.

class Rva00204BB8
{
public:
    bool operator()(int a, int b) const;
};

void __cdecl Rva00207BAAWrap(int *first, int *last, Rva00204BB8 comp);

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __pop_heap(RandomAccessIter first, RandomAccessIter last,
    RandomAccessIter result, Tp val, Compare comp);

template <class RandomAccessIter, class Compare>
void __sort_heap(RandomAccessIter first, RandomAccessIter last, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __partial_sort(RandomAccessIter first, RandomAccessIter middle,
    RandomAccessIter last, Tp *, Compare comp)
{
	Rva00207BAAWrap(first, middle, comp);
	for (RandomAccessIter i = middle; i < last; ++i) {
		if (comp(*i, *first)) {
			typedef void (__cdecl *PopHeap5)(int *, int *, int *, int, Rva00204BB8);
			typedef void (__cdecl *PopHeap6)(int *, int *, int *, int, Rva00204BB8, int);
			PopHeap5 fn5 = (PopHeap5)&_STL::__pop_heap<int *, int, Rva00204BB8>;
			PopHeap6 fn6 = (PopHeap6)fn5;
			fn6(first, middle, i, *i, comp, 0);
		}
	}
	__sort_heap(first, middle, comp);
}

template void __partial_sort<int *, int,
    Rva00204BB8>(int *, int *, int *, int *, Rva00204BB8);

}
