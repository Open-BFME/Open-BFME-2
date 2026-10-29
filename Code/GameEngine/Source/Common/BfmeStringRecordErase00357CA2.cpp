// cl: /Ireference/shims/bfme2_ascii /O1
// stlport46
// ?erase@?$vector@UBfmeStringRecord00204A30@@V?$allocator@UBfmeStringRecord00204A30@@@_STL@@@_STL@@QAEPAUBfmeStringRecord00204A30@@PAU3@@Z @ 0x00357CA2 (55B).
// Single-element vector erase over 20-byte BfmeStringRecord00204A30 (word AsciiString word AsciiString word).
// Evidence: shift tail via rowed __copy_ptrs 0x00204A13 then pop finish and destroy via rowed dtor 0x00204848;
// shape-identical to rowed ModuleInfo Nugget single erase 0x0033C3BC (55B ret 4); caller is 0x00357D7D.
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

	iterator erase(iterator position);
	iterator end() { return m_finish; }

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

}

template <class Type, class Allocator>
typename _STL::vector<Type, Allocator>::iterator
_STL::vector<Type, Allocator>::erase(iterator position)
{
	if (position + 1 != end())
	{
		__copy_ptrs(position + 1, m_finish, position, __false_type());
	}

	--m_finish;
	m_finish->~BfmeStringRecord00204A30();
	return position;
}

// This erase is a header inline in retail: one other unit emits a select-any
// copy of it, so a strong definition here was a duplicate symbol in the linked
// build. Making it inline emits the same copy as select-any, and this anchor
// only makes this unit emit its copy for the ledger row; it is not retail code.
template _STL::vector<BfmeStringRecord00204A30, _STL::allocator<BfmeStringRecord00204A30> >::iterator
_STL::vector<BfmeStringRecord00204A30, _STL::allocator<BfmeStringRecord00204A30> >::erase(BfmeStringRecord00204A30 *);
