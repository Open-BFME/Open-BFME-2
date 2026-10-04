// cl: /Ireference/shims/bfme2_ascii /O1
// stlport
// ?erase@?$vector@VUnicodeString@@V?$allocator@VUnicodeString@@@_STL@@@_STL@@QAEPAVUnicodeString@@PAV3@0@Z @0x0005A0BB 51B vector UnicodeString range erase.
// Evidence: calls rowed __copy_ptrs 0x00053E34 and rowed _Destroy 0x00056FC0; finish at +4 and return first; callers 0x0005B4FF 0x0005B763 0x0005E787 0x00061D7C; precedent VectorAsciiStringErase.cpp.
#include "unicode_string.h"

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

private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};

template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result,
	const random_access_iterator_tag &tag, Distance *extra);

// ??$__copy_ptrs@PAVUnicodeString@@PAV1@@_STL@@YAPAVUnicodeString@@PAV1@00ABU__false_type@0@@Z present-unmatched
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

_STL::vector<UnicodeString, _STL::allocator<UnicodeString> >::iterator
_STL::vector<UnicodeString, _STL::allocator<UnicodeString> >::erase(iterator first, iterator last)
{
	iterator result = __copy_ptrs(last, m_finish, first, __false_type());
	_STL::_Destroy(result, m_finish);
	m_finish = result;
	return first;
}
