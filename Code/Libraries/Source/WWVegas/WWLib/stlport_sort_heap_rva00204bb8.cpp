// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__sort_heap@PAHVRva00204BB8@@@_STL@@YAXPAH0VRva00204BB8@@@Z @0x002082B7 58B
// STL heap sort over int sort keys with the rowed thiscall comparator
// Rva00204BB8 at 0x00204BB8; loops the rowed pop fwd 0x00207BC3.
// Evidence: chain via landed pop fwd; same flags and comparator as
// stlport_adjust_heap_rva00204bb8.cpp and __sort_heap precedent in
// stlport_push_heap_rva00422ca8.cpp.

class Rva00204BB8
{
public:
    bool operator()(int a, int b) const;
};

void __cdecl Rva00207BC3Pop(int *first, int *last, Rva00204BB8 comp);

namespace _STL
{

template <class RandomAccessIter, class Compare>
void __sort_heap(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	while (last - first > 1) {
		Rva00207BC3Pop(first, last, comp);
		--last;
	}
}

template void __sort_heap<int *,
    Rva00204BB8>(int *, int *, Rva00204BB8);

}
