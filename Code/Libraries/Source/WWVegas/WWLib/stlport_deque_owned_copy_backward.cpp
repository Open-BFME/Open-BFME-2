// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??$copy_backward@U?$_Deque_iterator@UOpaqueRefElement4@@U?$_Nonconst_traits@UOpaqueRefElement4@@@_STL@@@_STL@@U12@@_STL@@YA?AU?$_Deque_iterator@UOpaqueRefElement4@@U?$_Nonconst_traits@UOpaqueRefElement4@@@_STL@@@0@U10@00@Z @0x00055825 63B
// Evidence: caller erase at 0x00057A95 in StlportOwnedDeque.cpp; callee aux at 0x00054EF1;
// donor vendor/stlport/stl/_algobase.h copy_backward; precedent stlport_deque_e12_copy_backward.cpp (63B stock, plain-inline aux stays out of line).
// This TU uses STOCK vendor headers (no bfmealloc shim) so the aux forwarder stays a call.
#include <deque>

struct OpaqueRefElement4 { void *referent; };

typedef _STL::_Deque_iterator<OpaqueRefElement4, _STL::_Nonconst_traits<OpaqueRefElement4> > OpaqueRefDequeIterator;

template OpaqueRefDequeIterator _STL::copy_backward<OpaqueRefDequeIterator, OpaqueRefDequeIterator>(
	OpaqueRefDequeIterator,
	OpaqueRefDequeIterator,
	OpaqueRefDequeIterator);
