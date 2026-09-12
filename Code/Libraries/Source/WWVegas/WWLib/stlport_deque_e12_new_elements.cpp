// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// _M_new_elements_at_back/_front for deque<BfmeE12>, retail 0x00585A9A (64B)
// and 0x00585A57 (67B). Same placeholder-element convention as the sibling
// stlport_deque_e12_o1.cpp (BfmeE12 names only the element SIZE). Split into
// its own TU without /EHsc: retail carries no exception-handling frame for
// either function (the _STLP_TRY/catch(...) rollback in vendor/stlport/stl/
// _deque.c compiles to nothing once _STLP_USE_EXCEPTIONS is off), while the
// sibling file needs /EHsc for other members it hosts.
#include <deque>
struct BfmeE12 { float x, y, z; };
template class _STL::deque<BfmeE12, _STL::allocator<BfmeE12 > >;
