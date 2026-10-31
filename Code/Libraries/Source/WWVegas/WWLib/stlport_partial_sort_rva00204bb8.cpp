// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__partial_sort@PAHHVRva00204BB8@@@_STL@@YAXPAH000VRva00204BB8@@@Z @0x00209A62 92B
// STL partial sort over int sort keys with the rowed thiscall comparator
// Rva00204BB8 at 0x00204BB8; calls rowed make fwd 0x00207BAA, rowed pop
// 0x002074D4, rowed sort_heap 0x002082B7 and rowed comparator.
// Evidence: chain via landed heap helpers; same flags and comparator as
// stlport_adjust_heap_rva00204bb8.cpp and __partial_sort precedent in
// stlport_push_heap_rva00422ca8.cpp.

#include <algorithm>

class Rva00204BB8
{
public:
	Rva00204BB8() {}
	bool operator()(int a, int b) const;
};

void __cdecl Rva00207BAAWrap(int *first, int *last, Rva00204BB8 comp);

namespace _STL
{

template <>
inline __declspec(noinline) void __partial_sort<int *, int, Rva00204BB8>(int *first, int *middle,
    int *last, int *, Rva00204BB8 comp)
{
	Rva00207BAAWrap(first, middle, comp);
	for (int *i = middle; i < last; ++i) {
		if (comp(*i, *first)) {
			__pop_heap(first, middle, i, *i, comp, (int *)0);
		}
	}
	sort_heap(first, middle, comp);
}

template void __partial_sort<int *, int, Rva00204BB8>(int *, int *, int *, int *, Rva00204BB8);

}
