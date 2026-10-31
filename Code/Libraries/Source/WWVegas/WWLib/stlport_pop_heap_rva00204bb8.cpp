// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__pop_heap@PAHHVRva00204BB8@@H@_STL@@YAXPAH00HVRva00204BB8@@0@Z @0x002074D4 41B
// (STLport 4.5.3's signature: the trailing _Distance* tag is unused)
// STL heap pop over int sort keys with the rowed thiscall comparator
// Rva00204BB8 at 0x00204BB8; calls the rowed __adjust_heap 0x00206D33.
// Evidence: chain via landed adjust_heap; same flags and comparator as
// stlport_adjust_heap_rva00204bb8.cpp and stlport_push_heap_rva00422ca8.cpp
// pop_heap precedent.

#include <algorithm>

class Rva00204BB8
{
public:
	Rva00204BB8() {}
	bool operator()(int a, int b) const;
};

template void _STL::__pop_heap<int *, int, Rva00204BB8, int>(int *, int *, int *, int, Rva00204BB8, int *);
