// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// platformsdk
// stlport
// BFME 1 STLport deque algorithms, instantiated for the target-supported 4-byte
// owning-reference element view; original class names are unknown. Its release and assignment members are defined in
// OpaqueRefOwnership.cpp; this TU provides the inline target-observed destructor.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
// The deque copy dispatcher passes its type tag by const reference.
#include "../../../../../vendor/stlport/stl/_algobase.h"
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
#include <windows.h>
#include "OpaqueRefCounted.h"
#include "../../../../GameEngine/Include/Common/OpaqueRefElement4.h"
// The stock STLport iterator dispatcher remains an out-of-line call.
namespace _STL {
typedef _Deque_iterator<OpaqueRefElement4, _Nonconst_traits<OpaqueRefElement4> > OpaqueRefDequeIter;
template <> __declspec(noinline) inline OpaqueRefDequeIter
__copy_aux<OpaqueRefDequeIter, OpaqueRefDequeIter>(
    OpaqueRefDequeIter first, OpaqueRefDequeIter last, OpaqueRefDequeIter result, const __false_type &)
{
    return __copy(first, last, result, random_access_iterator_tag(), (int *)0);
}
template <> __declspec(noinline) inline OpaqueRefDequeIter
__copy_backward_aux<OpaqueRefDequeIter, OpaqueRefDequeIter>(
    OpaqueRefDequeIter first, OpaqueRefDequeIter last, OpaqueRefDequeIter result, const __false_type &)
{
    return __copy_backward(first, last, result, random_access_iterator_tag(), (int *)0);
}
}
// Instantiate the recovered deque members and their algorithm workers.
typedef _STL::deque<OpaqueRefElement4> OpaqueRefDeque;
typedef OpaqueRefDeque::iterator OpaqueRefDequeIterator;
typedef OpaqueRefDeque::const_iterator OpaqueRefDequeConstIterator;
template void OpaqueRefDeque::_M_pop_back_aux();
template void OpaqueRefDeque::_M_pop_front_aux();
template void OpaqueRefDeque::pop_back();
template void OpaqueRefDeque::pop_front();
template void OpaqueRefDeque::clear();
template OpaqueRefDequeIterator OpaqueRefDeque::erase(OpaqueRefDequeIterator);
template OpaqueRefDequeIterator _STL::__copy<OpaqueRefDequeConstIterator, OpaqueRefDequeIterator, int>(
    OpaqueRefDequeConstIterator, OpaqueRefDequeConstIterator, OpaqueRefDequeIterator,
    const _STL::random_access_iterator_tag &, int *);
template OpaqueRefDequeIterator _STL::__copy_backward<OpaqueRefDequeIterator, OpaqueRefDequeIterator, int>(
    OpaqueRefDequeIterator, OpaqueRefDequeIterator, OpaqueRefDequeIterator,
    const _STL::random_access_iterator_tag &, int *);

template void _STL::__destroy_aux<OpaqueRefDequeIterator>(
    OpaqueRefDequeIterator, OpaqueRefDequeIterator, const _STL::__false_type &);
