// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__pop_heap@PAHHVRva00204BB8@@@_STL@@YAXPAH00HVRva00204BB8@@@Z @0x002074D4 41B
// STL heap pop over int sort keys with the rowed thiscall comparator
// Rva00204BB8 at 0x00204BB8; calls the rowed __adjust_heap 0x00206D33.
// Evidence: chain via landed adjust_heap; same flags and comparator as
// stlport_adjust_heap_rva00204bb8.cpp and stlport_push_heap_rva00422ca8.cpp
// pop_heap precedent.

class Rva00204BB8
{
public:
    bool operator()(int a, int b) const;
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
    Distance len, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __pop_heap(RandomAccessIter first, RandomAccessIter last,
    RandomAccessIter result, Tp val, Compare comp)
{
	*result = *first;
	__adjust_heap(first, 0, (int)(last - first), val, comp);
}

template void __pop_heap<int *, int,
    Rva00204BB8>(int *, int *, int *, int, Rva00204BB8);

}
