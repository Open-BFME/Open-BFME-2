// cl: /DNDEBUG /MD
//
// ??$__uninitialized_copy@PAV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@PAV12@@_STL@@YAPAV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@0@PAV10@00ABU__false_type@0@@Z @0x004740DA (38B).
// _STL::__uninitialized_copy for list<Object*> (4-byte list objects): range-loop
// calling rowed _Construct 0x004740AD. Called by vector insert-overflow 0x00475BE8.
// Dedicated TU so construct TU cannot inline _Construct into this loop.
class Object;
namespace _STL {
template <class _Tp> class allocator;
template <class _Tp, class _Alloc> class list {
    void *_M_node;
public:
    list(const list &other);
};
struct __false_type {};
template <class _T1, class _T2> void _Construct(_T1 *__p, const _T2 &__value);
template <class _InputIter, class _ForwardIter>
_ForwardIter __uninitialized_copy(_InputIter __first, _InputIter __last, _ForwardIter __result, const __false_type &) {
    _ForwardIter __cur = __result;
    for (; __first != __last; ++__first, ++__cur)
        _Construct(__cur, *__first);
    return __cur;
}
}
template _STL::list<Object *, _STL::allocator<Object *> > *_STL::__uninitialized_copy(_STL::list<Object *, _STL::allocator<Object *> > *, _STL::list<Object *, _STL::allocator<Object *> > *, _STL::list<Object *, _STL::allocator<Object *> > *, const _STL::__false_type &);
