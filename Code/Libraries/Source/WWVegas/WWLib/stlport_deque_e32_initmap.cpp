// cl: /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// _Deque_base map setup for deque<BfmeE32>: _M_initialize_map 191B at
// 0x0073C9D0 plus the (alloc n) base ctor 76B at 0x0073CF90 which calls it.
// Same placeholder-element convention as the sibling stlport_deque_e8_o1.cpp
// (BfmeE32 names only the element SIZE: rep-movs x8 bodies elsewhere fix the
// 32B stride, and shr-2 map sizing here fixes 128/32 = 4 per node). Same
// noexc split-TU rationale as stlport_deque_e8_initmap.cpp: retail carries
// no exception-handling frame, and /O2 inlines _M_create_nodes.
#include <deque>
struct BfmeE32 { int a[8]; };
template class _STL::deque<BfmeE32, _STL::allocator<BfmeE32 > >;
