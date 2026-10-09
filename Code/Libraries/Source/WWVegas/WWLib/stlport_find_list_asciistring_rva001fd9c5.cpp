// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// STLport 4.5.3 find(first, last, value) over list<AsciiString> iterators
// @0x001FD9C5 (42B): forwards to the genuine __find(..., input_iterator_tag).
// The native 39-byte search at 0x001FD837 and the caller at 0x005BAA83 use
// a pointer-sized iterator output, first/end node pointers, and a string ref.
// Native nodes carry next at +0 and the AsciiString at +8. STLport supplies
// the iterator and tag types; the original wrapper spelling remains unknown.
// Const/nonconst __find copies are full byte-and-relocation twins here.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include <algorithm>
#include "ascii_string.h"

typedef _STL::list<AsciiString>::iterator Rva001FD9C5ListIter;
template Rva001FD9C5ListIter _STL::find<Rva001FD9C5ListIter, AsciiString>(Rva001FD9C5ListIter, Rva001FD9C5ListIter, const AsciiString &);

// The same genuine const-iterator search is specialized locally to consume
// the existing STLport node links directly. This preserves its algorithm and
// native ABI without emitting an unused competing iterator++ COMDAT.
typedef _STL::list<AsciiString>::const_iterator Rva005BAA83Iter;
namespace _STL {
template <>
Rva005BAA83Iter __find<Rva005BAA83Iter, AsciiString>(
    Rva005BAA83Iter first, Rva005BAA83Iter last, const AsciiString &value,
    const input_iterator_tag &)
{
    while (first._M_node != last._M_node) {
        if (static_cast<_List_node<AsciiString> *>(first._M_node)->_M_data.compare(value) == 0)
            break;
        first._M_node = first._M_node->_M_next;
    }
    return first;
}
}
