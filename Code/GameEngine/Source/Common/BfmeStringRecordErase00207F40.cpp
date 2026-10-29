// cl: /Ireference/shims/bfme2_ascii /O1
// stlport46
//
// ?erase@?$vector@UBfmeStringRecord00204A30@@V?$allocator@UBfmeStringRecord00204A30@@@_STL@@@_STL@@QAEPAUBfmeStringRecord00204A30@@PAU3@0@Z @0x00207F40 51B
// Evidence: leaf lane range erase over 20-byte BfmeStringRecord00204A30 via rowed __copy_ptrs 0x00204A13 plus rowed _Destroy 0x00206CBA; shape-identical to rowed FXBoneInfo range erase 0x00207F0D 51B; callers 0x0020989A 0x00209CEB; tag at ebp+0xb via __false_type prvalue; ret 8.
#include "ascii_string.h"

struct BfmeStringRecord00204A30
{
	~BfmeStringRecord00204A30();

	unsigned int word0;
	AsciiString text0;
	unsigned int word1;
	AsciiString text1;
	unsigned int word2;
};

namespace _STL
{

struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	typedef Type *iterator;

	iterator erase(iterator first, iterator last);

private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};

template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result,
	const __false_type &tag);

struct random_access_iterator_tag
{
};

// The rowed __copy 0x00204170 (stlport_vector_stringrecord_00204a30_allocate_copy.cpp).
template <class RandomAccessIter, class OutputIter, class Distance>
OutputIter __copy(RandomAccessIter first, RandomAccessIter last, OutputIter result,
	const random_access_iterator_tag &tag, Distance *distance);

// STLport's non-trivial __copy_ptrs: forward to __copy, as retail's 29B body
// 0x00204A13 does.
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result,
	const __false_type &tag)
{
	random_access_iterator_tag category;
	return __copy(first, last, result, category, (int *)0);
}

template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);

}

template <class Type, class Allocator>
typename _STL::vector<Type, Allocator>::iterator
_STL::vector<Type, Allocator>::erase(iterator first, iterator last)
{
	iterator result = _STL::__copy_ptrs(last, m_finish, first, _STL::__false_type());
	_STL::_Destroy(result, m_finish);
	m_finish = result;
	return first;
}

template _STL::vector<BfmeStringRecord00204A30, _STL::allocator<BfmeStringRecord00204A30> >::iterator
_STL::vector<BfmeStringRecord00204A30, _STL::allocator<BfmeStringRecord00204A30> >::erase(
	BfmeStringRecord00204A30 *, BfmeStringRecord00204A30 *);
