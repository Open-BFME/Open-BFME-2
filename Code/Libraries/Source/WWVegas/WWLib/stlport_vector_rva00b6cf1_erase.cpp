// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?erase@?$vector@URva00B6CF1@@V?$allocator@URva00B6CF1@@@_STL@@@_STL@@QAEPAURva00B6CF1@@PAU3@0@Z @0x000C0628 51B: vector Rva00B6CF1 range erase via rowed copy_ptrs 0x000B67BC plus rowed Destroy 0x000BDCD6 plus finish store. Evidence: same 51B 4-plus-2 push shape with tag at [ebp+0xb] as Rva000B435F erase 0x000C059B and BfmeStringRecord erase 0x00381B1F; callees rowed; caller 0x004B5242 dtor.
#include "ascii_string.h"
struct Rva00B6CF1
{
	AsciiString m_s0;
	AsciiString m_s1;
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
template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result,
	const random_access_iterator_tag &tag, Distance *extra);
// ??$__copy_ptrs@PAURva00B6CF1@@PAU1@@_STL@@YAPAURva00B6CF1@@PAU1@00ABU__false_type@0@@Z present-unmatched
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
inline _STL::vector<Rva00B6CF1, _STL::allocator<Rva00B6CF1> >::iterator _STL::vector<Rva00B6CF1, _STL::allocator<Rva00B6CF1> >::erase(iterator first, iterator last)
{
	iterator result = _STL::__copy_ptrs(last, m_finish, first, _STL::__false_type());
	_STL::_Destroy(result, m_finish);
	m_finish = result;
	return first;
}

// vector<Rva00B6CF1>::erase is a header inline elsewhere: other units emit
// select-any copies, so a strong definition here was a duplicate in the linked
// build. This anchor only makes this unit emit its copy for the ledger row; it
// is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitStlportVectorRva00B6CF1Erase@@YAXPAV?$vector@URva00B6CF1@@V?$allocator@URva00B6CF1@@@_STL@@@_STL@@PAURva00B6CF1@@1@Z present-unmatched
void bfmeEmitStlportVectorRva00B6CF1Erase(_STL::vector<Rva00B6CF1, _STL::allocator<Rva00B6CF1> > *vec, Rva00B6CF1 *first, Rva00B6CF1 *last)
{
	vec->erase(first, last);
}
#pragma inline_depth()
