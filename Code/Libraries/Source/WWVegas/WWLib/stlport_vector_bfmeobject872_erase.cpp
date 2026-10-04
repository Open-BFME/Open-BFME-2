// cl: /O1 /Oy-
// stlport
//
// ?erase@?$vector@UBfmeObject872@@V?$allocator@UBfmeObject872@@@_STL@@@_STL@@QAEPAUBfmeObject872@@PAU3@0@Z
// @0x0033C44B 38B: range erase over vector<BfmeObject872>. Shifts tail with rowed __copy_ptrs at 0x002CF27E; trivial dtor needs no _Destroy; stores new finish returns first.
// Evidence: calls rowed __copy_ptrs BfmeObject872; caller 0x0033D357 passes ThingTemplate+0x358 vector start/finish; unblocks 0x0033D331.
struct BfmeObject872 {
	unsigned char m_pad[872];
};
namespace _STL {
struct __false_type {
};
struct random_access_iterator_tag {
};
template <class Type>
class allocator {
};
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
template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &tag, Distance *extra);
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}
_STL::vector<BfmeObject872, _STL::allocator<BfmeObject872> >::iterator
_STL::vector<BfmeObject872, _STL::allocator<BfmeObject872> >::erase(iterator first, iterator last)
{
	const _STL::__false_type &tag = reinterpret_cast<const _STL::__false_type &>(*(reinterpret_cast<const char *>(&first) + 3));
	iterator result = _STL::__copy_ptrs(static_cast<const BfmeObject872 *>(last), static_cast<const BfmeObject872 *>(m_finish), first, tag);
	m_finish = result;
	return first;
}
