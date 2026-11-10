// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 pop_heap with comparator over the pathfinder priority queue
// of _Rva002EBB53Wrap pointers, retail 0x002F1F02, 23 bytes. Called by the
// priority-queue pop 0x002F301F (call at 0x002F302B); forwards to
// __pop_heap_aux 0x002F0EE4 (Rva002F0EE4Finish.cpp) with the null value-type
// pointer.
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

extern template void _STL::__pop_heap_aux(_Rva002EBB53Wrap **, _Rva002EBB53Wrap **, _Rva002EBB53Wrap **, Rva002EBB53Compare);
template void _STL::pop_heap(_Rva002EBB53Wrap **, _Rva002EBB53Wrap **, Rva002EBB53Compare);
