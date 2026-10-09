// cl: /Ireference/shims/bfme2_ascii /O1
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
#include "ascii_string.h"

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
	iterator begin() { return m_start; }
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
inline _STL::vector<AsciiString, _STL::allocator<AsciiString> >::erase(
	iterator first, iterator last)
{
	iterator result = __copy_ptrs(last, m_finish, first, __false_type());
	_STL::_Destroy(result, m_finish);
	m_finish = result;
	return first;
}

// vector<AsciiString>::erase is a header inline in retail: one other unit
// emits a select-any copy of it, so a strong definition here was a duplicate
// symbol in the linked build. This anchor only makes this unit emit its copy
// for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitVectorAsciiStringErase@@YAXPAV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@@Z present-unmatched
void bfmeEmitVectorAsciiStringErase(_STL::vector<AsciiString, _STL::allocator<AsciiString> > *p)
{
	p->erase(0, 0);
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?erase@SidesInfoStringVector@@QAEPAVAsciiString@@PAV2@0@Z=?erase@?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAEPAVAsciiString@@PAV3@0@Z")

// Clean BFME1 f98983a7d3 Module.cpp supplies the erase-all pattern. Retail
// proves pointer slots0/4 and the string-owning erase provider; original owner
// and complete object size are unknown. The existing vector is an ABI exemplar.
class Rva0002D1B0Range
{
public:
    void rva0002D1B0Clear();
private:
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > m_values;
};

void Rva0002D1B0Range::rva0002D1B0Clear()
{
    m_values.erase(m_values.begin(), m_values.end());
}
