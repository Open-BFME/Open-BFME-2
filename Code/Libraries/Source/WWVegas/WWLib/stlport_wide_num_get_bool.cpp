// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// Modified STLport 4.5.3 num_get<bool> input reconstruction.
// boolalpha compares both facet names; numeric input delegates to the long
// overload and accepts exactly zero or one. The original algorithm is kept.
//
// The visible noinline iterator helper exposes which cached fields survive
// calls. Narrow reads use the held sgetc/sbumpc bodies. Wide reads inline
// sgetc within _M_getc but retain the held sbumpc call and base destruction.
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
#define _INC_STDLIB

typedef unsigned int size_t;

typedef struct { int quot; int rem; } div_t;
typedef struct { long quot; long rem; } ldiv_t;

void __cdecl free(void *block);

extern "C" {
void __cdecl abort(void);
int __cdecl abs(int value);
int __cdecl atexit(void (__cdecl *routine)(void));
double __cdecl atof(const char *string);
int __cdecl atoi(const char *string);
long __cdecl atol(const char *string);
void *__cdecl bsearch(const void *key, const void *base, size_t count,
        size_t width, int (__cdecl *compare)(const void *, const void *));
void *__cdecl calloc(size_t count, size_t size);
div_t __cdecl div(int numerator, int denominator);
void __cdecl exit(int status);
char *__cdecl getenv(const char *name);
long __cdecl labs(long value);
ldiv_t __cdecl ldiv(long numerator, long denominator);
void *__cdecl malloc(size_t size);
int __cdecl mblen(const char *ch, size_t count);
size_t __cdecl mbstowcs(unsigned short *dest, const char *source, size_t count);
int __cdecl mbtowc(unsigned short *dest, const char *source, size_t count);
void __cdecl qsort(void *base, size_t count, size_t width,
        int (__cdecl *compare)(const void *, const void *));
int __cdecl rand(void);
void *__cdecl realloc(void *block, size_t size);
void __cdecl srand(unsigned int seed);
double __cdecl strtod(const char *string, char **end);
long __cdecl strtol(const char *string, char **end, int radix);
unsigned long __cdecl strtoul(const char *string, char **end, int radix);
int __cdecl system(const char *command);
size_t __cdecl wcstombs(char *dest, const unsigned short *source, size_t count);
int __cdecl wctomb(char *dest, unsigned short ch);
}

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
locale::~locale() _STLP_NOTHROW { _M_impl->_M_decr(); }

}
namespace _STL {
template<> unsigned short basic_streambuf<wchar_t,char_traits<wchar_t> >::sbumpc();
template<> _String_base<wchar_t,allocator<wchar_t> >::~_String_base();
template<> __declspec(noinline) void istreambuf_iterator<wchar_t,char_traits<wchar_t> >::_M_getc() const {
 if (_M_have_c) return; int_type c=_M_buf->sgetc(); _M_c=traits_type::to_char_type(c); _M_eof=traits_type::eq_int_type(c,traits_type::eof()); _M_have_c=true;
}
typedef istreambuf_iterator<wchar_t,char_traits<wchar_t> > _BoolIn;
template <>
_BoolIn
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

}
