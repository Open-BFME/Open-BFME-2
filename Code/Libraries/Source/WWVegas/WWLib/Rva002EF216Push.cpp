// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 __push_heap_aux over the pathfinder priority queue of
// _Rva002EBB53Wrap pointers, retail 0x002EF216, 35 bytes. Called by push_heap
// 0x002F0D35 (call at 0x002F0D45); forwards (first, last - first - 1, 0,
// *(last - 1), comp) to __push_heap 0x002EBB53 in Rva002EBB53SiftUp.cpp, whose
// element view this unit repeats.
#include <algorithm>

struct _Rva002EBB53Inner {
    char m_pad[0x10];
    unsigned short m_key;
};
struct _Rva002EBB53Wrap {
    _Rva002EBB53Inner *m_inner;
};
// Empty comparator, greater-than on the payload key: the smallest key is on
// top of the heap.
#include "../../../../GameEngine/Include/Common/Rva002EBB53Compare.h"

extern template void _STL::__push_heap(_Rva002EBB53Wrap **, int, int, _Rva002EBB53Wrap *, Rva002EBB53Compare);
template void _STL::__push_heap_aux(_Rva002EBB53Wrap **, _Rva002EBB53Wrap **, Rva002EBB53Compare, int *, _Rva002EBB53Wrap **);
