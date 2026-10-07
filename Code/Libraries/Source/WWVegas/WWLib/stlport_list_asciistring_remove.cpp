// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?remove@?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAEXABVAsciiString@@@Z 0x005C9E90 67B
// Evidence: iterates list erasing AsciiString matches via rowed StringBase compare 0x000069D6 and rowed list erase 0x000BC67A; callers 0x005CADD3/0x005CAE72; retail calls compare (int test eax) so operator== is inlined here to compare==0.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
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

template void _STL::list<AsciiString, _STL::allocator<AsciiString> >::remove(const AsciiString &);
