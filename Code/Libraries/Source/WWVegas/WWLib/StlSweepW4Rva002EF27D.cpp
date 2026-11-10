// STLport 4.5.3 __pop_heap over the pathfinder priority queue of
// _Rva002EBB53Wrap pointers, retail 0x002EF27D, 41 bytes. Called by
// __pop_heap_aux 0x002F0EE4; stores *first to *result, then calls
// __adjust_heap 0x002EBB9B. Element identity and unconstrained fields remain
// address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

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

// __adjust_heap 0x002EBB9B is Rva002EBB53SiftUp.cpp's; reference it.
extern template void _STL::__adjust_heap(_Rva002EBB53Wrap **, int, int, _Rva002EBB53Wrap *, Rva002EBB53Compare);

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__pop_heap(_Rva002EBB53Wrap **, _Rva002EBB53Wrap **, _Rva002EBB53Wrap **, _Rva002EBB53Wrap *, Rva002EBB53Compare, int *);
