// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// _STL::__uninitialized_copy<AsciiString*, AsciiString*>, retail
// 0x0002C4B2, 38 bytes. Dedicated TU so the AsciiString _Construct helper
// at 0x0002C485 stays an out-of-line call inside this loop. Element stride
// is 4 (StringBase m_data model, not the 8-byte Buffer model at 0x142CE0).

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


// Rowed helper at 0x0002C485:
// ??$_Construct@VAsciiString@@V1@@_STL@@YAXPAVAsciiString@@ABV1@@Z
// (void __cdecl _STL::_Construct<class AsciiString,class AsciiString>).
namespace _STL { template <class T1, class T2> void _Construct(T1 *p, const T2 &value); }

namespace _STL
{

struct __false_type {};

template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last,
	ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(cur, *first);
	return cur;
}

}

template AsciiString *_STL::__uninitialized_copy(const AsciiString *, const AsciiString *, AsciiString *, const _STL::__false_type &);
