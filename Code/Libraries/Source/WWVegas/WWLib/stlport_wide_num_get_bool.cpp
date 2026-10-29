// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport46
//
// Modified STLport 4.5.3 num_get<bool> input reconstruction.
// boolalpha compares both facet names; numeric input delegates to the long
// overload and accepts exactly zero or one. The original algorithm is kept.
//
// The visible noinline iterator helper exposes which cached fields survive
// calls. Narrow reads use the held sgetc/sbumpc bodies. Wide reads inline
// sgetc within _M_getc but retain the held sbumpc call and string destruction.
// Locale teardown is visible, and C++ free retains the retail unwind states.
// _Locale_impl's complete24-byte layout uses the repository's recovered
// _M_incr/_M_decr spellings for the original private incr/decr virtual slots.
// The full code extent and bool overload's actual class-vtable slot are
// independently verified; all alignment bytes are excluded.
/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */
// /D_CRTIMP= keeps free a direct call to the game allocator, and /EHs lets it
// throw, preserving retail's unwind states.
#include <stdlib.h>

#include <string>
namespace _STL { template<> basic_string<wchar_t,char_traits<wchar_t>,allocator<wchar_t> >::~basic_string(); }
#include <locale>
// The locale implementation is opaque in _locale.h. Its three vtable slots
// are established by stlport_locale.cpp; visibility here inlines _M_decr.
namespace _STL {
class _Locale_impl {
public:
    virtual ~_Locale_impl();
    virtual void _M_incr();
    virtual void _M_decr();
    locale::facet **_M_facets;
    unsigned int _M_count;
    string _M_name;
};
typedef char _LocaleImplStorage[(sizeof(_Locale_impl)==24)?1:-1];
inline locale::~locale() _STLP_NOTHROW { _M_impl->_M_decr(); }

}
namespace _STL {
template<> unsigned short basic_streambuf<wchar_t,char_traits<wchar_t> >::sbumpc();
template<> __declspec(noinline) void istreambuf_iterator<wchar_t,char_traits<wchar_t> >::_M_getc() const {
 if (_M_have_c) return; int_type c=_M_buf->sgetc(); _M_c=traits_type::to_char_type(c); _M_eof=traits_type::eq_int_type(c,traits_type::eof()); _M_have_c=true;
}
typedef istreambuf_iterator<wchar_t,char_traits<wchar_t> > _BoolIn;
template <>
inline _BoolIn
num_get<wchar_t, _BoolIn>::do_get(_BoolIn __in, _BoolIn __end,
                                    ios_base& __s,
                                    ios_base::iostate& __err, bool& __x) const
{
  if (__s.flags() & ios_base::boolalpha) {
    locale __loc = __s.getloc();
    const _Numpunct& __np = *(const _Numpunct*)__s._M_numpunct_facet();
    //    const numpunct<wchar_t>& __np = use_facet<numpunct<wchar_t> >(__loc) ;
//    const ctype<wchar_t>& __ct =    use_facet<ctype<wchar_t> >(__loc) ;

    const basic_string<wchar_t> __truename  = __np.truename();
    const basic_string<wchar_t> __falsename = __np.falsename();
    bool __true_ok  = true;
    bool __false_ok = true;

    size_t __n = 0;
    for ( ; __in != __end; ++__in) {
      wchar_t __c = *__in;
      __true_ok  = __true_ok  && (__c == __truename[__n]);
      __false_ok = __false_ok && (__c == __falsename[__n]);
      ++__n;

      if ((!__true_ok && !__false_ok) ||
          (__true_ok  && __n >= __truename.size()) ||
          (__false_ok && __n >= __falsename.size())) {
	++__in;
        break;
      }
    }
    if (__true_ok  && __n < __truename.size())  __true_ok  = false;
    if (__false_ok && __n < __falsename.size()) __false_ok = false;
    
    if (__true_ok || __false_ok) {
      __err = ios_base::goodbit;
      __x = __true_ok;
    }
    else
      __err = ios_base::failbit;

    if (__in == __end)
      __err |= ios_base::eofbit;

    return __in;
  }

  else {
    long __lx;
    _BoolIn __tmp = this->do_get(__in, __end, __s, __err, __lx);
    if (!(__err & ios_base::failbit)) {
      if (__lx == 0)
        __x = false;
      else if (__lx == 1)
        __x = true;
      else
        __err |= ios_base::failbit;
    }
    return __tmp;
  }
}

template _BoolIn num_get<wchar_t, _BoolIn>::do_get(
    _BoolIn, _BoolIn, ios_base&, ios_base::iostate&, bool&) const;

}
