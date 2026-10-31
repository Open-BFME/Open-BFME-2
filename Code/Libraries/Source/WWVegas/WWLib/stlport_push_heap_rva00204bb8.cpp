// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__push_heap@PAHHHVRva00204BB8@@@_STL@@YAXPAHHHHVRva00204BB8@@@Z @0x002059CF 76B
// Heap sift-up over int sort keys with the rowed thiscall comparator
// Rva00204BB8 (member operator()(int,int) at 0x204BB8 defined in
// ParticleSystemTemplateSortComparator.cpp): parent = (hole-1)/2, then while
// the hole is above top and comp(*parent, value) holds, move the parent down.
// Evidence: caller 0x206D33 in adjust_heap 94B; callee rowed 0x204BB8;
// unblocks 0x206D33. Same STLport spelling as stlport_push_heap_rva00422ca8.cpp.
#include <algorithm>

class Rva00204BB8
{
public:
	Rva00204BB8() {}
	bool operator()(int a, int b) const;
};

template void _STL::__push_heap<int *, int, int, Rva00204BB8>(int *, int, int, int, Rva00204BB8);
