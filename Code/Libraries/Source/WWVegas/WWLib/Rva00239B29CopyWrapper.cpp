// cl: /DNDEBUG /MD
// ??$__copy_ptrs@PAUOpaqueRefElement4@@PAU1@@_STL@@YAPAUOpaqueRefElement4@@PAU1@00ABU__false_type@0@@Z @0x00239B29 29B
// _STL::__copy_ptrs<OpaqueRefElement4> forwarding wrapper retail 29 bytes.
// Pushes NULL distance and a tag local then calls the rowed 5-arg __copy at
// 0x00051C10. Same 29B shape as copy wrappers (4th tag arg ignored).
// Called by vector erase at 0x00239EA5 with __false_type() at [ebp+0xb].
struct OpaqueRefElement4
{
	void *referent;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

namespace _STL
{

struct random_access_iterator_tag {};
struct __false_type {};

template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &, Distance *);

template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &)
{
	__false_type _t;
	return __copy(first, last, result, reinterpret_cast<const random_access_iterator_tag &>(_t), (int *)0);
}

}

template OpaqueRefElement4 *_STL::__copy_ptrs(OpaqueRefElement4 *, OpaqueRefElement4 *, OpaqueRefElement4 *, const __false_type &);
