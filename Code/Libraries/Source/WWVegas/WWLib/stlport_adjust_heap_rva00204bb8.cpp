// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__adjust_heap@PAHHHVRva00204BB8@@@_STL@@YAXPAHHHHVRva00204BB8@@@Z @0x00206D33 94B
// STL heap sift-down over int sort keys with the rowed thiscall comparator
// Rva00204BB8 at 0x00204BB8; tail-calls the rowed __push_heap 0x002059CF.
// Evidence: caller notes in stlport_push_heap_rva00204bb8.cpp name this
// adjust_heap 94B; same flags and comparator as that TU.

#include <algorithm>

class Rva00204BB8
{
public:
	Rva00204BB8() {}
	bool operator()(int a, int b) const;
};

template void _STL::__adjust_heap<int *, int, int, Rva00204BB8>(int *, int, int, int, Rva00204BB8);
