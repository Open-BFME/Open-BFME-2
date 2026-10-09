// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <string>

namespace _STL
{
template <>
basic_string<char, char_traits<char>, allocator<char> >::~basic_string();

template <>
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(
        char*, size_t);
}

#include <ostream>

// Retail's generic-widening init is owned by stlport_basic_ios_init.cpp.
// Leave this specialization declared so this unit does not emit a different copy.
namespace _STL {
template <> void basic_ios<char, char_traits<char> >::init(
    basic_streambuf<char, char_traits<char> > *);
}


template class _STL::basic_ostream<char, _STL::char_traits<char> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeStrlenV55@@YAIPAD@Z=?length@?$char_traits@D@_STL@@SAIPBD@Z")
#pragma comment(linker, "/alternatename:?bfmeMakeOX@@YAHPAX@Z=?length@?$char_traits@D@_STL@@SAIPBD@Z")
#pragma comment(linker, "/alternatename:_bfmeLen1153=?length@?$char_traits@D@_STL@@SAIPBD@Z")
#pragma comment(linker, "/alternatename:?bfmeStrlenV51@@YAIPAD@Z=?length@?$char_traits@D@_STL@@SAIPBD@Z")
