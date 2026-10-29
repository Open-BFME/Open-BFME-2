// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

// Retail's basic_ios<char>::widen is the generic ctype widen (0x000135E0, owned by
// stlport_basic_ios_init.cpp); without this the char specialization emits a non-retail copy.
#define _STLP_NO_METHOD_SPECIALIZATION
#include <string>

namespace _STL
{
template <>
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(
        char*, size_t);
}

#include <istream>
// bfme link decl-only begin
namespace _STL { template <> char basic_ios<char, char_traits<char> >::widen(char) const; }
namespace _STL { template <> basic_ostream<char, char_traits<char> > & basic_ostream<char, char_traits<char> >::flush(); }
// bfme link decl-only end

// Retail's generic-widening init is owned by stlport_basic_ios_init.cpp.
// Leave this specialization declared so this unit does not emit a different copy.
namespace _STL {
template <> void basic_ios<char, char_traits<char> >::init(
    basic_streambuf<char, char_traits<char> > *);
}


template class _STL::basic_istream<char, _STL::char_traits<char> >;
