// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__make_heap@PAHVRva00204BB8@@@_STL@@YAXPAH0VRva00204BB8@@@Z @0x002074FD 60B
// STL heap make over int sort keys with the rowed thiscall comparator
// Rva00204BB8 at 0x00204BB8; loops the rowed __adjust_heap 0x00206D33.
// Evidence: chain via landed adjust_heap; same flags and comparator as
// stlport_adjust_heap_rva00204bb8.cpp and pop_heap precedent.

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

template <class RandomAccessIter, class Compare>
void __make_heap(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	if (last - first < 2)
		return;
	int len = (int)(last - first);
	int parent = (len - 2) / 2;
	while (true) {
		__adjust_heap(first, parent, len, *(first + parent), comp);
		if (parent == 0)
			return;
		--parent;
	}
}

template void __make_heap<int *,
    Rva00204BB8>(int *, int *, Rva00204BB8);

}
