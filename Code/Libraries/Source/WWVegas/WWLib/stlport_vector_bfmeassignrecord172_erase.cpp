// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
//
// ?erase@?$vector@UBfmeAssignRecord172@@V?$allocator@UBfmeAssignRecord172@@@_STL@@@_STL@@QAEPAUBfmeAssignRecord172@@PAU3@0@Z
// @ 0x001EBDFA (51B): range erase over vector<BfmeAssignRecord172>. Shifts
// the tail down with __copy_ptrs (29B wrapper emitted here as duplicate of
// the rowed 0x001EBA13 via the rowed __copy at 0x001EB86E) then destroys
// the vacated tail with the rowed _Destroy at 0x001EB1B3, stores the new
// finish and returns first. Follows BfmeAssignRecord32 erase (0x00173FB6 51B)
// and VectorAsciiStringErase shape: prvalue __false_type tag forces
// the EBP frame with tag at [ebp+0xb].
struct BfmeAssignRecord172 {
	~BfmeAssignRecord172();
	unsigned char m_pad[172];
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
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag)
{
	__false_type local;
	return __copy(first, last, result, reinterpret_cast<const random_access_iterator_tag &>(local), (int *)0);
}

template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);

}

_STL::vector<BfmeAssignRecord172, _STL::allocator<BfmeAssignRecord172> >::iterator
_STL::vector<BfmeAssignRecord172, _STL::allocator<BfmeAssignRecord172> >::erase(iterator first, iterator last)
{
	iterator result = _STL::__copy_ptrs(last, m_finish, first, _STL::__false_type());
	_STL::_Destroy(result, m_finish);
	m_finish = result;
	return first;
}
