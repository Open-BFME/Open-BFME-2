// cl: /Ireference/shims/bfme2_ascii /O1
// stlport
// ?erase@?$vector@UBfmeStringRecord005DDD40@@V?$allocator@UBfmeStringRecord005DDD40@@@_STL@@@_STL@@QAEPAUBfmeStringRecord005DDD40@@PAU3@0@Z @0x00381B1F 51B: range erase over 8-byte BfmeStringRecord005DDD40 vector. Shifts tail down with __copy_ptrs wrapper then destroys vacated tail with rowed _Destroy 0x00381AC7 stores new finish returns first. Evidence: retail 4-push plus 2-push shape with tag at [ebp+0xb] same as FXBoneInfo erase 0x00207F0D and VectorAsciiStringErase 0x002CCFC; callees rowed copy_ptrs 0x0038151E and Destroy 0x00381AC7; callers 0x00381B75 0x00381C45 0x005DE7F9 0x005DE93D.
#include "unicode_string.h"
struct BfmeStringRecord005DDD40
{
	UnicodeString text;
	unsigned int word;
	BfmeStringRecord005DDD40();
	BfmeStringRecord005DDD40(const BfmeStringRecord005DDD40 &other);
	BfmeStringRecord005DDD40 &operator=(const BfmeStringRecord005DDD40 &other);
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
private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &tag, Distance *distance);
template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);
}
// ??$__copy_ptrs@PAUBfmeStringRecord005DDD40@@PAU1@@_STL@@YAPAUBfmeStringRecord005DDD40@@PAU1@00ABU__false_type@0@@Z @0x0038151E 29B
template <>
__declspec(noinline) BfmeStringRecord005DDD40 *_STL::__copy_ptrs<BfmeStringRecord005DDD40 *, BfmeStringRecord005DDD40 *>(BfmeStringRecord005DDD40 *first, BfmeStringRecord005DDD40 *last, BfmeStringRecord005DDD40 *result, const _STL::__false_type &tag)
{
	// The empty tag carries no state; retail passes its address without initializing storage.
	_STL::random_access_iterator_tag iteratorTag;
	return _STL::__copy(first, last, result, iteratorTag, (int *)0);
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

// vector<BfmeStringRecord005DDD40>::erase is a header inline elsewhere: other units emit
// select-any copies, so a strong definition here was a duplicate in the linked
// build. This anchor only makes this unit emit its copy for the ledger row; it
// is not retail code.
template _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> >::iterator
_STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> >::erase(BfmeStringRecord005DDD40 *, BfmeStringRecord005DDD40 *);
