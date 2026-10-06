// cl: /DNDEBUG /MD
// ??$__copy_backward_ptrs@PAUTreeHintRef00217D4C@@PAU1@@_STL@@YAPAUTreeHintRef00217D4C@@PAU1@00ABU__false_type@0@@Z @0x004F6D2E 29B:
// STL ptrs dispatch wrapper: forwards (first, last, result) plus a
// random_access_iterator_tag temp and (int *)0 to the rowed 5-arg worker
// 0x004F6628 in Rva00051C10Copy.cpp. Called by copy_backward 0x004F6FE1 (27B)
// and 0x004F7EE9. Same recipe as the rowed 29B __copy_backward_ptrs wrappers
// (e.g. 0x005B2B1E, 0x00583B37); model/flags donor TU Rva004F6352Copy.cpp.
struct TreeHintRef00217D4C
{
	void *m_target;
};

namespace _STL
{

struct __false_type
{
};

struct random_access_iterator_tag
{
};

template <class BidirectionalIter1, class BidirectionalIter2, class Distance>
BidirectionalIter2 __copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
	BidirectionalIter2 result, const random_access_iterator_tag &, Distance *);

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2 __copy_backward_ptrs(BidirectionalIter1 first, BidirectionalIter1 last,
	BidirectionalIter2 result, const __false_type &)
{
	__false_type local;
	return __copy_backward(first, last, result,
		reinterpret_cast<const random_access_iterator_tag &>(local), (int *)0);
}

}

template TreeHintRef00217D4C *_STL::__copy_backward_ptrs<TreeHintRef00217D4C *,
	TreeHintRef00217D4C *>(TreeHintRef00217D4C *,
	TreeHintRef00217D4C *, TreeHintRef00217D4C *, const _STL::__false_type &);
