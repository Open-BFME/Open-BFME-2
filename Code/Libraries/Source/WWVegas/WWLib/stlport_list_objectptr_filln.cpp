// cl: /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@IV12@@_STL@@YAPAV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@0@PAV10@IABV10@ABU__false_type@0@@Z @0x00474100 (37B).
// _STL::__uninitialized_fill_n for list<Object*> (4-byte list objects): count-loop
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
template <class _ForwardIter, class _Size, class _Tp>
_ForwardIter __uninitialized_fill_n(_ForwardIter __first, _Size __n, const _Tp &__x, const __false_type &) {
    _ForwardIter __cur = __first;
    for (; __n > 0; --__n, ++__cur)
        _Construct(__cur, __x);
    return __cur;
}
}
template _STL::list<Object *, _STL::allocator<Object *> > *_STL::__uninitialized_fill_n(_STL::list<Object *, _STL::allocator<Object *> > *, unsigned int, const _STL::list<Object *, _STL::allocator<Object *> > &, const _STL::__false_type &);
