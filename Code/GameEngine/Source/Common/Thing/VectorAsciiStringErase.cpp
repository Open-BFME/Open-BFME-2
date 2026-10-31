// cl: /O1 /arch:SSE /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
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
#pragma inline_depth(3)
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <vector>
#include <memory>

// Retail's range erase goes through a by-reference __copy_ptrs that forwards to
// the five-argument __copy worker rowed at 0x000B4431, unlike the vendored by-value one.
namespace _STL {
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result,
	const __false_type &tag)
{
	__false_type local;
	return __copy(first, last, result,
		reinterpret_cast<const random_access_iterator_tag &>(local), (int *)0);
}

template <> inline vector<AsciiString, allocator<AsciiString> >::iterator
vector<AsciiString, allocator<AsciiString> >::erase(iterator first, iterator last)
{
	typedef iterator (*CopyPtrs)(iterator, iterator, iterator, const __false_type &);
	iterator result = static_cast<CopyPtrs>(__copy_ptrs)(last, this->_M_finish, first, __false_type());
	_Destroy(result, this->_M_finish);
	this->_M_finish = result;
	return first;
}
}

// Retail's range destroy calls the out-of-line destructor 0x0048BA39 for each
// string, so its first instantiation expands the helpers but not the destructor.
namespace _STL {
template <> __declspec(dllimport) __forceinline void _Destroy<AsciiString>(AsciiString *pointer)
{
    pointer->AsciiString::~AsciiString();
}
#pragma inline_depth(3)
template void _Destroy<AsciiString *>(AsciiString *, AsciiString *);
#pragma inline_depth()
}

// The genuine erase-all caller below emits this header-inline erase and
// its copy-dispatch helper naturally; no synthetic emission caller is needed.

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
