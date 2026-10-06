// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__adjust_heap@PAHHHVRva00204BB8@@@_STL@@YAXPAHHHHVRva00204BB8@@@Z @0x00206D33 94B
// STL heap sift-down over int sort keys with the rowed thiscall comparator
// Rva00204BB8 at 0x00204BB8; tail-calls the rowed __push_heap 0x002059CF.
// Evidence: caller notes in stlport_push_heap_rva00204bb8.cpp name this
// adjust_heap 94B; same flags and comparator as that TU.

class Rva00204BB8
{
public:
    bool operator()(int a, int b) const;
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
    Distance topIndex, Tp val, Compare comp);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
    Distance len, Tp val, Compare comp)
{
    Distance topIndex = holeIndex;
    Distance secondChild = 2 * holeIndex + 2;
    while (secondChild < len) {
        if (comp(*(first + secondChild), *(first + (secondChild - 1))))
            --secondChild;
        *(first + holeIndex) = *(first + secondChild);
        holeIndex = secondChild;
        secondChild = 2 * (secondChild + 1);
    }
    if (secondChild == len) {
        *(first + holeIndex) = *(first + (secondChild - 1));
        holeIndex = secondChild - 1;
    }
    __push_heap(first, holeIndex, topIndex, val, comp);
}

template void __adjust_heap<int *, int, int,
    Rva00204BB8>(int *, int, int, int, Rva00204BB8);

}
