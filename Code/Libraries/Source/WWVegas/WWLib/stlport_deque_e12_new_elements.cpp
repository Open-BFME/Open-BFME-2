// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// _M_new_elements_at_back/_front for deque<BfmeE12>, retail 0x00585A9A (64B)
// and 0x00585A57 (67B). Same placeholder-element convention as the sibling
// stlport_deque_e12_o1.cpp (BfmeE12 names only the element SIZE). Split into
// its own TU without /EHsc: retail carries no exception-handling frame for
// either function (the _STLP_TRY/catch(...) rollback in vendor/stlport/stl/
// _deque.c compiles to nothing once _STLP_USE_EXCEPTIONS is off), while the
// sibling file needs /EHsc for other members it hosts.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
struct BfmeE12 { float x, y, z; };
// Reuse the complete stock-header copy-backward provider at 0x00585A18.
typedef _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> > BfmeE12CopyIterator;
namespace _STL {
template <> BfmeE12CopyIterator copy_backward<BfmeE12CopyIterator, BfmeE12CopyIterator>(
    BfmeE12CopyIterator, BfmeE12CopyIterator, BfmeE12CopyIterator);
}
template class _STL::deque<BfmeE12, _STL::allocator<BfmeE12 > >;
