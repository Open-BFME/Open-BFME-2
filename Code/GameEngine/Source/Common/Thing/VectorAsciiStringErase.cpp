// cl: /O1
// stlport
//
// vector<AsciiString>::erase(first, last), retail 0x002CCFC, 51 bytes.
// Range erase over AsciiString elements: shift the tail down with the
// out-of-line four-argument _STL::__copy_ptrs (by-reference __false_type
// tag, retail 0x000B6614), destroy the vacated tail with the rowed
// _Destroy range at 0x0002CB64, store the new finish, return first.
//
// The four-argument wrapper is defined here (Nugget-erase idiom): it
// forwards to the five-argument __copy worker rowed at 0x000B4431 under
// this TU's spelling. Both bodies are verified below.
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

namespace _STL
{

struct __false_type
{
};

struct random_access_iterator_tag
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
	iterator end() { return m_finish; }

private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};

template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result,
	const random_access_iterator_tag &tag, Distance *extra);

template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result,
	const __false_type &tag)
{
	__false_type local;
	return __copy(first, last, result,
		reinterpret_cast<const random_access_iterator_tag &>(local), (int *)0);
}

template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);

}

_STL::vector<AsciiString, _STL::allocator<AsciiString> >::iterator
_STL::vector<AsciiString, _STL::allocator<AsciiString> >::erase(
	iterator first, iterator last)
{
	iterator result = __copy_ptrs(last, m_finish, first, __false_type());
	_STL::_Destroy(result, m_finish);
	m_finish = result;
	return first;
}
