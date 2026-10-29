// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// Dedicated TU for basic_ios<char>::init. The retail body uses the generic
// ctype<char>::widen virtual rather than STLport's char widening
// specialization. Do not edit stlport_narrow_fstream.cpp.

#define _STLP_NO_METHOD_SPECIALIZATION
#include <istream>
#include <ostream>

// Suppress this TU's non-retail _String_base<char> dtor copy (family2-LK3 rows
// 22/26): the rowed 63B copy in stlport_narrow_string_base_dtor.cpp serves the link.
template <> _STL::_String_base<char, _STL::allocator<char> >::~_String_base();
#include <cstddef>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> basic_ostream<char,char_traits<char> > & basic_ostream<char,char_traits<char> >::operator<<(int); }
// bfme link decl-only begin
namespace _STL { template <> bool _M_init<char, char_traits<char> >(basic_ostream<char, char_traits<char> > &); }
// Keep the sentry constructor inline-only: this unit sorts before the owner
// (stlport_narrow_ostream_put_num.cpp) in link order, and its unreferenced
// 27-byte COMDAT copy is not retail's 25-byte body at 0x001F5E38.
namespace _STL {
template <> __declspec(dllimport) __forceinline
basic_ostream<char, char_traits<char> >::sentry::sentry(basic_ostream<char, char_traits<char> > &__str)
  : _M_str(__str), _M_ok(_M_init(__str)) {}
}
namespace _STL { template <> basic_ostream<char, char_traits<char> > & _M_put_num<char, char_traits<char>, long>(basic_ostream<char, char_traits<char> > &, long); }
namespace _STL { template <> basic_ostream<char, char_traits<char> > & _M_put_num<char, char_traits<char>, unsigned long>(basic_ostream<char, char_traits<char> > &, unsigned long); }
namespace _STL { template <> basic_ostream<char, char_traits<char> > & _M_put_num<char, char_traits<char>, double>(basic_ostream<char, char_traits<char> > &, double); }
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
// The unsigned long inserter is rowed there too (0x001F68BF).
namespace _STL { template <> basic_ostream<char, char_traits<char> > & basic_ostream<char, char_traits<char> >::operator<<(unsigned long); }
// The standalone narrow imbue owns the retail body; this unit emitted a
// longer copy with a different grouping-buffer cleanup path.
namespace _STL { template <> locale basic_ios<char, char_traits<char> >::imbue(locale const &); }
namespace _STL { template <> locale basic_ios<unsigned short, char_traits<unsigned short> >::imbue(locale const &); }
// The wide init body is owned by stlport_wide_ios.cpp; keep calls to it external
// so this unit emits no duplicate ahead of the rowed copy.
namespace _STL { template <> void basic_ios<unsigned short, char_traits<unsigned short> >::init(basic_streambuf<unsigned short, char_traits<unsigned short> > *); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_deallocate_block(); }
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t, const void*);
}
// Rowed basic_ios<char> members, instantiated precisely instead of whole
// classes; the broad istream instantiations are what drag the scan_not and
// find_if machinery into this unit.
template void _STL::basic_ios<char, _STL::char_traits<char> >::init(_STL::basic_streambuf<char, _STL::char_traits<char> > *);
template char _STL::basic_ios<char, _STL::char_traits<char> >::widen(char) const;
template char _STL::basic_ios<char, _STL::char_traits<char> >::fill(char);
template _STL::basic_streambuf<char, _STL::char_traits<char> >* _STL::basic_ios<char, _STL::char_traits<char> >::rdbuf(_STL::basic_streambuf<char, _STL::char_traits<char> >*);
template _STL::basic_ostream<char, _STL::char_traits<char> >* _STL::basic_ios<char, _STL::char_traits<char> >::tie(_STL::basic_ostream<char, _STL::char_traits<char> >*);
template unsigned short _STL::basic_ios<unsigned short, _STL::char_traits<unsigned short> >::fill() const;
// get(char&) preserves the rowed to_char_type leaf without scan machinery.
template _STL::basic_istream<char, _STL::char_traits<char> >& _STL::basic_istream<char, _STL::char_traits<char> >::get(char&);
// peek() preserves the rowed _FILE_I_next leaf through the sgetc path.
template int _STL::basic_istream<char, _STL::char_traits<char> >::peek();
// Keep the one whole-class wide ostream instantiation: it serves the rowed
// ??_D complete destructor, including destruction of the virtual base.
template class _STL::basic_ostream<wchar_t, _STL::char_traits<wchar_t> >;

// Keep these four rowed helpers after suppressing the non-retail imbue.
// The other five incidental helpers are owned by stlport_narrow_ios_imbue.cpp,
// whose existing emitted copies match their complete retail bodies.
template void _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::_M_construct_null(char *);
template void _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::_M_construct_null_aux(char *, const _STL::__true_type &);
template char *_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::erase(char *, char *);
template char *_STL::__char_traits_base<char,int>::move(char *, const char *, unsigned int);
