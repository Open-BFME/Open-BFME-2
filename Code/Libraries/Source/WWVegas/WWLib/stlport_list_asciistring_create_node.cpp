// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// list<AsciiString>::_M_create_node, retail 0x001FD682 (34 bytes, frameless).
// Hand-written explicit specialization, mirroring the dedicated
// AsciiStringUninitializedCopy.cpp precedent: the node comes from the rowed
// raw byte allocator at 0x000307F0 (12 bytes, null hint) and the element is
// built by the opaque StringBase _Construct helper pinned at 0x0002C485,
// whose true _STL mangling is spent at 0x00142CC0. A whole-class
// instantiation instead routes _Construct through the inline copy ctor and
// wraps the body in a try region (93 bytes), so it cannot reproduce this
// out-of-line-helper flavor.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


bool operator==(const AsciiString &a, const AsciiString &b);
bool operator<(const AsciiString &a, const AsciiString &b);

// Rowed _Construct<AsciiString> helper at 0x0002C485 (defined as
// ??$_Construct@VAsciiString@@V1@@_STL@@YAXPAVAsciiString@@ABV1@@Z).
namespace _STL {
template <> void _Construct<AsciiString, AsciiString>(AsciiString *, const AsciiString &);
}

template <>
_STL::_List_node<AsciiString> *_STL::list<AsciiString, _STL::allocator<AsciiString> >::_M_create_node(const AsciiString &__x)
{
	_STL::_List_node<AsciiString> *__p =
		(_STL::_List_node<AsciiString> *)_STL::allocator<char>::allocate(12, 0);
	_STL::_Construct<AsciiString, AsciiString>(&__p->_M_data, __x);
	return __p;
}

// Explicit instantiation so the class's inline callers (insert) odr-use the
// specialization above and cl emits its body; explicit-instantiation-only
// members are invisible to find_declared_unmatched.
template class _STL::list<AsciiString, _STL::allocator<AsciiString> >;
