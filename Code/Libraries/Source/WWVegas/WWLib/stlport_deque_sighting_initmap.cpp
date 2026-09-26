// cl: /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// _Deque_base map setup for deque<SightingInfo*>: _M_initialize_map 189B at
// 0x006203D0 plus the (alloc n) base ctor 76B at 0x00620690 which calls it.
// Real element type is SightingInfo* (PAVSightingInfo: class pointer 4B).
// Same noexc split-TU rationale as stlport_deque_e8_initmap.cpp: retail carries
// no exception-handling frame (the _STLP_TRY/_STLP_UNWIND rollback in
// vendor/stlport/stl/_deque.c compiles to nothing once _STLP_USE_EXCEPTIONS
// is off). /O2 inlines _M_create_nodes into _M_initialize_map; the node stride
// is 0x80 with shr-5 sizing (128/4 = 32 per node) and tail and-0x1f lea *4.
// Callers: deque ctor 0x006209D0 at 0x6209F3 and base ctor 0x00620690 at 0x6206D0.
// Donor: vendor/stlport/stl/_deque.c _M_initialize_map.
#include <deque>
class SightingInfo;
template class _STL::deque<SightingInfo*, _STL::allocator<SightingInfo* > >;
