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


#include "../../../../GameEngine/Include/Common/BfmeStringData.h"

#include "unicode_string.h"
// bfme link decl-only begin
namespace _STL { template <> void _S_unique<UnicodeString,_STL::allocator<UnicodeString>,_STL::equal_to<UnicodeString> >(_STL::list<UnicodeString,_STL::allocator<UnicodeString> > &,_STL::equal_to<UnicodeString>); }
namespace _STL { template <> bool equal_to<UnicodeString>::operator()(UnicodeString const &,UnicodeString const &) const; }
namespace _STL { template <> _STL::_List_iterator<UnicodeString,_STL::_Nonconst_traits<UnicodeString> > list<UnicodeString,_STL::allocator<UnicodeString> >::insert(_STL::_List_iterator<UnicodeString,_STL::_Nonconst_traits<UnicodeString> >,UnicodeString const &); }
namespace _STL { template <> void list<UnicodeString,_STL::allocator<UnicodeString> >::remove(UnicodeString const &); }
// bfme link decl-only end


bool operator==(const UnicodeString &a, const UnicodeString &b);
bool operator<(const UnicodeString &a, const UnicodeString &b);

template class _STL::list<UnicodeString, _STL::allocator<UnicodeString> >;
