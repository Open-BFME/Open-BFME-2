// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// No-TRY twin of stlport_list_unicodestring_insert.cpp. Retail's
// _M_create_node at 0x00433B1E is frameless (34 bytes: allocate plus
// copy-construct, no __EH_prolog) because the bfmelist shim declares it
// __forceinline without TRY/UNWIND (same recipe as the int family's
// stlport_list_int_o1.cpp); the vendor header emits a 94-byte EH frame.
// Everything else here is the same wide UnicodeString/list context, so only
// this member is rowed from here.
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

#include "unicode_string.h"


bool operator==(const UnicodeString &a, const UnicodeString &b);
bool operator<(const UnicodeString &a, const UnicodeString &b);

template class _STL::list<UnicodeString, _STL::allocator<UnicodeString> >;
