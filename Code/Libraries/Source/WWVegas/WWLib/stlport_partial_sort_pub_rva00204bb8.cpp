// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$partial_sort@PAHVRva00204BB8@@@_STL@@YAXPAH00VRva00204BB8@@@Z @0x0020A295 27B
// Public partial_sort wrapper forwarding to the rowed __partial_sort
// 0x00209A62 with (int*)0 dummy; same pattern as partial_sort precedent in
// stlport_push_heap_rva00422ca8.cpp. Evidence: chain via landed
// __partial_sort; caller 0x0020C0BA in 0x0020C04C.

class Rva00204BB8
{
public:
    bool operator()(int a, int b) const;
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __partial_sort(RandomAccessIter first, RandomAccessIter middle,
    RandomAccessIter last, Tp *, Compare comp);

template <class RandomAccessIter, class Compare>
void partial_sort(RandomAccessIter first, RandomAccessIter middle,
    RandomAccessIter last, Compare comp)
{
	__partial_sort(first, middle, last, (int *)0, comp);
}

template void partial_sort<int *,
    Rva00204BB8>(int *, int *, int *, Rva00204BB8);

}
