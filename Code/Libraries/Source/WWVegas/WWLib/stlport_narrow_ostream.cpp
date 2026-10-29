// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

// Retail's basic_ios<char>::widen is the generic ctype widen (0x000135E0, owned by
// stlport_basic_ios_init.cpp); without this the char specialization emits a non-retail copy.
#define _STLP_NO_METHOD_SPECIALIZATION
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
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> basic_ostream<char,char_traits<char> > & basic_ostream<char,char_traits<char> >::operator<<(unsigned long); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> basic_ostream<char,char_traits<char> > & basic_ostream<char,char_traits<char> >::operator<<(int); }
// bfme link decl-only begin
namespace _STL { template <> char basic_ios<char, char_traits<char> >::widen(char) const; }
namespace _STL { template <> bool _M_init<char, char_traits<char> >(basic_ostream<char, char_traits<char> > &); }
// Keep the sentry constructor inline-only: this unit sorts before the owner
// (stlport_narrow_ostream_put_num.cpp) in link order, and its unreferenced
// 27-byte COMDAT copy is not retail's 25-byte body at 0x001F5E38.
namespace _STL {
template <> __declspec(dllimport) __forceinline
basic_ostream<char, char_traits<char> >::sentry::sentry(basic_ostream<char, char_traits<char> > &__str)
  : _M_str(__str), _M_ok(_M_init(__str)) {}
}
namespace _STL { template <> void basic_ostream<char, char_traits<char> >::_M_put_char(char); }
namespace _STL { template <> void basic_ostream<char, char_traits<char> >::_M_put_nowiden(char const *); }
namespace _STL { template <> basic_ostream<char, char_traits<char> > & basic_ostream<char, char_traits<char> >::flush(); }
// Same for the sentry destructor: its COMDAT copy here is not retail's
// 20-byte body at 0x001F498A (stlport_narrow_ostream_put_num.cpp). Plain
// declaration-only form; the unwind path needs a callable body.
namespace _STL { template <> basic_ostream<char, char_traits<char> >::sentry::~sentry(); }
namespace _STL { template <> basic_ostream<char, char_traits<char> > & basic_ostream<char, char_traits<char> >::put(char); }
// The float inserter's body belongs to stlport_narrow_ostream_put_num.cpp; leave
// it declared so this unit emits no wrong copy ahead of the rowed one.
namespace _STL { template <> basic_ostream<char, char_traits<char> > & basic_ostream<char, char_traits<char> >::operator<<(float); }
// bfme link decl-only end

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
