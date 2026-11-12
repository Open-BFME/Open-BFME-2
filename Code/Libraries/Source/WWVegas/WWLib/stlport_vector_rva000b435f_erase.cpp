// cl: /Ireference/shims/bfme2_ascii /O1
// stlport
// ?erase@?$vector@URva000B435F@@V?$allocator@URva000B435F@@@_STL@@@_STL@@QAEPAURva000B435F@@PAU3@0@Z @0x000C059B 51B: vector Rva000B435F range erase via copy_ptrs 0x2CF830 plus destroy 0x331FF1 plus finish store. Evidence: retail calls pinned copy_ptrs plus rowed destroy; same 51B 4-plus-2 push shape as FXBoneInfo erase 0x00207F0D and PrereqUnitRec erase 0x004F50E2; callers at 0xC1C64 0xC6D86 0x33E12E.
#include "ascii_string.h"
#include "Rva000B435F.h"
class Rva002DFC30
{
	int m_00;
	AsciiString m_04;
	char m_08;
public:
	~Rva002DFC30();
};
namespace _STL
{
struct __false_type
{
};
struct input_iterator_tag
{
};
struct forward_iterator_tag : public input_iterator_tag
{
};
struct bidirectional_iterator_tag : public forward_iterator_tag
{
};
struct random_access_iterator_tag : public bidirectional_iterator_tag
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
// ??$__copy_ptrs@PAURva000B435F@@PAU1@@_STL@@YAPAURva000B435F@@PAU1@00ABU__false_type@0@@Z present-unmatched
template <>
__declspec(noinline) Rva000B435F *_STL::__copy_ptrs<Rva000B435F *, Rva000B435F *>(Rva000B435F *first, Rva000B435F *last, Rva000B435F *result, const _STL::__false_type &tag)
{
	return _STL::__copy(first, last, result, _STL::random_access_iterator_tag(), (int *)0);
}
template <class Type, class Allocator>
typename _STL::vector<Type, Allocator>::iterator
_STL::vector<Type, Allocator>::erase(iterator first, iterator last)
{
	iterator result = _STL::__copy_ptrs(last, m_finish, first, _STL::__false_type());
	_STL::_Destroy(reinterpret_cast<Rva002DFC30 *>(result), reinterpret_cast<Rva002DFC30 *>(m_finish));
	m_finish = result;
	return first;
}

// vector<Rva000B435F>::erase is a header inline elsewhere: other units emit
// select-any copies, so a strong definition here was a duplicate in the linked
// build. This anchor only makes this unit emit its copy for the ledger row; it
// is not retail code.
template _STL::vector<Rva000B435F, _STL::allocator<Rva000B435F> >::iterator
_STL::vector<Rva000B435F, _STL::allocator<Rva000B435F> >::erase(Rva000B435F *, Rva000B435F *);
