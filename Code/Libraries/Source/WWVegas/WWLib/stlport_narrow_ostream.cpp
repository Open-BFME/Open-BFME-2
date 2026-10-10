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


// The numeric inserters' _M_put_num bodies belong to stlport_narrow_ostream_put_num.cpp; leave them
// declared so this unit emits none of them (nor the getloc they call).
namespace _STL {
template <> basic_ostream<char, char_traits<char> > &_M_put_num<char, char_traits<char>, long>(basic_ostream<char, char_traits<char> > &, long);
template <> basic_ostream<char, char_traits<char> > &_M_put_num<char, char_traits<char>, unsigned long>(basic_ostream<char, char_traits<char> > &, unsigned long);
template <> basic_ostream<char, char_traits<char> > &_M_put_num<char, char_traits<char>, __int64>(basic_ostream<char, char_traits<char> > &, __int64);
template <> basic_ostream<char, char_traits<char> > &_M_put_num<char, char_traits<char>, unsigned __int64>(basic_ostream<char, char_traits<char> > &, unsigned __int64);
template <> basic_ostream<char, char_traits<char> > &_M_put_num<char, char_traits<char>, double>(basic_ostream<char, char_traits<char> > &, double);
template <> basic_ostream<char, char_traits<char> > &_M_put_num<char, char_traits<char>, long double>(basic_ostream<char, char_traits<char> > &, long double);
template <> basic_ostream<char, char_traits<char> > &_M_put_num<char, char_traits<char>, const void *>(basic_ostream<char, char_traits<char> > &, const void *);
template <> basic_ostream<char, char_traits<char> > &_M_put_num<char, char_traits<char>, bool>(basic_ostream<char, char_traits<char> > &, bool);
}
template class _STL::basic_ostream<char, _STL::char_traits<char> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeStrlenV55@@YAIPAD@Z=?length@?$char_traits@D@_STL@@SAIPBD@Z")
#pragma comment(linker, "/alternatename:?bfmeMakeOX@@YAHPAX@Z=?length@?$char_traits@D@_STL@@SAIPBD@Z")
#pragma comment(linker, "/alternatename:_bfmeLen1153=?length@?$char_traits@D@_STL@@SAIPBD@Z")
#pragma comment(linker, "/alternatename:?bfmeStrlenV51@@YAIPAD@Z=?length@?$char_traits@D@_STL@@SAIPBD@Z")
