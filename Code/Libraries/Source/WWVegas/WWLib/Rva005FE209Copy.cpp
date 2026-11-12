// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__copy@PAUBfmeContainerRecord005FDEC7@@PAU1@@_STL@@YAPAUBfmeContainerRecord005FDEC7@@PAU1@00ABUrandom_access_iterator_tag@0@@Z @0x005FE209 29B: 4-arg __copy forwarder to rowed 5-arg worker 0x005FE0C3. Evidence: unlock lane 29B push-0 plus tag-local at ebp-1 into 5 pushes call add-esp-0x14; callee dup_005fe0c3 object-symbol is the true ContainerRecord 5-arg __copy; caller 0x005FE4E2 passes 4 args and callers use ContainerRecord helpers.
#include "unicode_string.h"

#include "BfmeContainerRecord005FDEC7.h"

namespace _STL {
struct random_access_iterator_tag {};
template <class Type> class allocator {};
template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &tag, Distance *distance);
template <class InputIter, class OutputIter>
OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &tag)
{
    random_access_iterator_tag local;
    return __copy(first, last, result, local, (int *)0);
}
template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);
template <class Type, class Allocator>
class vector {
public:
    typedef Type *iterator;
    iterator erase(iterator first, iterator last);
private:
    iterator m_start;
    iterator m_finish;
    iterator m_endOfStorage;
};
}

template BfmeContainerRecord005FDEC7 *_STL::__copy<BfmeContainerRecord005FDEC7 *, BfmeContainerRecord005FDEC7 *>(BfmeContainerRecord005FDEC7 *, BfmeContainerRecord005FDEC7 *, BfmeContainerRecord005FDEC7 *, const _STL::random_access_iterator_tag &);

template <class Type, class Allocator>
typename _STL::vector<Type, Allocator>::iterator
_STL::vector<Type, Allocator>::erase(iterator first, iterator last)
{
    iterator new_finish = _STL::__copy(last, m_finish, first, _STL::random_access_iterator_tag());
    _STL::_Destroy(new_finish, m_finish);
    m_finish = new_finish;
    return first;
}

template _STL::vector<BfmeContainerRecord005FDEC7, _STL::allocator<BfmeContainerRecord005FDEC7> >::iterator
_STL::vector<BfmeContainerRecord005FDEC7, _STL::allocator<BfmeContainerRecord005FDEC7> >::erase(BfmeContainerRecord005FDEC7 *, BfmeContainerRecord005FDEC7 *);
