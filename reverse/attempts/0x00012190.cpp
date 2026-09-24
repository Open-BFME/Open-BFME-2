// ?do_get@?$money_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@0_NAAVios_base@2@AAHAAV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@@Z
// partial score=0.65 date=2026-09-24
// ?do_get@?$money_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@0_NAAVios_base@2@AAHAAV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@@Z
// partial score=0.65 date=2026-09-24
// ?do_get@?$money_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@0_NAAVios_base@2@AAHAAV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@@Z
// partial score=0.63 date=2026-09-23
// cl: /Ob1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// Banked reconstruction of STLport 4.5.3 wide money_get string parser (2802B).
// Current: 2816B (+14), all 63 E8 sites 1:1 in order, vendor-verbatim operator=
// (__digits = __buf, NOT .assign(): vendor _monetary.c uses operator=, and only
// operator= emits retail's inlined self-check cmp/je at both assign sites).
// Retail spans RVA 0x12190-0x12C82; 122+2680 dump fragments are one body.
//
// REMAINING WALLS (all mapped 2026-09-24):
// (1) Temp-vs-named destruction split: retail destroys 13 conditional temps via
// out-of-line ~_String_base (B3C0) but frees the 3 named strings (__buf/__ns/__ps)
// inline (test+free-30830). PROVEN MECHANISM (num_put_bool precedent, rowed):
// hide the dtor via `template <> _String_base<unsigned short,
// allocator<unsigned short> >::~_String_base();` (use unsigned short, NOT
// wchar_t, or C2888) so all destructions outline, then carve the 3 named
// strings into explicit-free storage owners (placement-new + `if (data)
// free(data)` dtor, _BoolStorageTag trick to avoid extra EH states). Hiding
// alone gives 2672B/10xB3C0 (verified). The 3 owners must forward copy-ctor
// (ea90), dispatch-source, insert (push_back/de40 + insert_aux/12d10),
// begin/data/size, and back_insert_iterator wrapping.
// (2) Tag store: retail `mov byte [esp+0x1e],0` zeroes the __false_type temp
// before the shared dispatch tail (slot reuses dead __symbol_required). No
// natural spelling emits it (operator=/assign/begin-end probes all bare);
// value-init-temp-zeroing (num_put comment) did NOT reproduce under /Ob1 or
// /O2. May fall out of the owner rewrite (different temp slot/pressure).
// (3) EDI: retail homes __i (loop counter) + zero/facet temps in edi from the
// prologue (push edi + xor edi,edi + mov [esp+0xc],edi); ours uses immediates.
// Pressure-coupled, likely falls out of (1).
// REFUTED: /O2-full (2988B, worse), member-template-direct assign (no check,
// no tag), /Ob1-vs-/O2 for tag (neither emits it), wchar_t-spelled dtor decl
// (C2888; must be unsigned short).
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

// Suppress stdlib.h so free retains the C++ linkage and throwing declaration
// needed for retail's direct call and exception-state stores. These are the
// declarations consumed by the vendor cstdlib wrapper.
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

// Only pointer calls to streambuf are needed here. Keeping this interface
// opaque preserves the retail sbumpc call inside inline iterator increment.
#define _STLP_INTERNAL_STREAMBUF
#include <locale>

namespace _STL {
template<> class basic_streambuf<wchar_t, char_traits<wchar_t> > {
public:
  typedef char_traits<wchar_t>::int_type int_type;
  int_type sbumpc();
  int_type sgetc();
};
}


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
};
locale::~locale() _STLP_NOTHROW { _M_impl->_M_decr(); }

}
// Keep the vendor _M_getc body visible for MSVC's side-effect analysis while
// preserving retail's out-of-line calls. A declaration alone makes the compiler
// spill the iterator instead of retaining it in ebp/ebx across those calls.
namespace _STL
{
template <>
__declspec(noinline) void istreambuf_iterator<wchar_t, char_traits<wchar_t> >::_M_getc() const
{
    if (_M_have_c)
        return;
    int_type c = _M_buf->sgetc();
    _M_c = traits_type::to_char_type(c);
    _M_eof = traits_type::eq_int_type(c, traits_type::eof());
    _M_have_c = true;
}
}
namespace _STL {
template <> __declspec(noinline) bool
istreambuf_iterator<wchar_t, char_traits<wchar_t> >::equal(const istreambuf_iterator<wchar_t, char_traits<wchar_t> >& other) const {
    if (_M_buf) _M_getc();
    if (other._M_buf) other._M_getc();
    return _M_eof == other._M_eof;
}
template <> __forceinline istreambuf_iterator<wchar_t, char_traits<wchar_t> >&
istreambuf_iterator<wchar_t, char_traits<wchar_t> >::operator++() {
    _M_buf->sbumpc();
    _M_have_c = false;
    return *this;
}
// These string operations are separate functions in this retail instantiation.
}
namespace _STL {
typedef istreambuf_iterator<wchar_t, char_traits<wchar_t> > _MoneyIn;

template <> __forceinline pair<_MoneyIn, bool> __get_string(_MoneyIn first, _MoneyIn last, const wchar_t* start, const wchar_t* end) {
  pair<_MoneyIn, const wchar_t*> result = mismatch(first, last, start);
  return make_pair(result.first, result.second == end);
}

// Same operation as __get_string; retail inlines only the symbol case.
__forceinline pair<_MoneyIn, bool> __get_symbol(_MoneyIn first, _MoneyIn last, const wchar_t* start, const wchar_t* end) {
  pair<_MoneyIn, const wchar_t*> result = mismatch(first, last, start);
  return make_pair(result.first, result.second == end);
}
template <> _MoneyIn money_get<wchar_t, _MoneyIn>::do_get(_MoneyIn __s, _MoneyIn __end, bool __intl, ios_base& __str, ios_base::iostate& __err, basic_string<wchar_t>& __digits) const
{
  typedef wchar_t _CharT;
  typedef _MoneyIn _InputIter;
  if (__s == __end) {
    __err |= ios_base::eofbit;
    return __s;
  }

  typedef moneypunct<_CharT, false> _Punct;
  typedef moneypunct<_CharT, true>  _Punct_intl;
  typedef ctype<_CharT>             _Ctype;

  locale __loc = __str.getloc();
  const _Punct&      __punct      = use_facet<_Punct>(__loc) ;
  const _Punct_intl& __punct_intl = use_facet<_Punct_intl>(__loc) ;
  const _Ctype&      __c_type      = use_facet<_Ctype>(__loc) ;
                   
  money_base::pattern __format = __intl ? __punct_intl.neg_format()
                                        : __punct.neg_format();
  string_type __ns = __intl ? __punct_intl.negative_sign()
                            : __punct.negative_sign();
  string_type __ps = __intl ? __punct_intl.positive_sign()
                            : __punct.positive_sign();
  int __i;
  bool __is_positive = true;
  bool __symbol_required = (__str.flags() & ios_base::showbase) !=0;
  string_type __buf;
  back_insert_iterator<string_type> __out(__buf);

  for (__i = 0; __i < 4; ++__i) {
    switch (__format.field[__i]) {
    case (char) money_base::none:
      if (__i == 3) {
        if (__c_type.is(ctype_base::space, *__s)) {
          __err = ios_base::failbit;
          return __s;
        }
        break;
      }
      while (__s != __end && __c_type.is(ctype_base::space, *__s))
        ++__s;
      break;
    case (char) money_base::space:
      if (!__c_type.is(ctype_base::space, *__s)) {
        __err = ios_base::failbit;
        return __s;
      }
      ++__s;
      while (__s != __end && __c_type.is(ctype_base::space, *__s))
        ++__s;
      break;
    case money_base::symbol: {
      string_type __cs = __intl ? __punct_intl.curr_symbol()
                                : __punct.curr_symbol();
      pair<iter_type, bool>
      __result  = __get_symbol(__s, __end, __cs.data(), __cs.data() + __cs.size());
      if (!__result.second && __symbol_required)
        __err = ios_base::failbit;
      __s = __result.first;
      break;
    }
    case money_base::sign: {
      if (__s == __end) {
        if (__ps.size() == 0)
          break;
        if (__ns.size() == 0) {
          __is_positive = false;
          break;
        }
        __err = ios_base::failbit;
        return __s;
      }
      else {
        if (__ps.size() == 0) {
          if (__ns.size() == 0)
            break;
          if (*__s == ++__ns[0]) {
            ++__s;
            __is_positive = false;
            break;
          }
          __err = ios_base::failbit;
        } 
        else {
          if (*__s == __ps[0]) {
            ++__s;
            break;
          }
          if (__ns.size() == 0)
            break;
          if (*__s == __ns[0]) {
            ++__s;
            __is_positive = false;
            break;
          }
          __err = ios_base::failbit;
        }
      }
      return __s;
    }
    case money_base::value: {
      _CharT __point = __intl ? __punct_intl.decimal_point()
                              : __punct.decimal_point();
      int __frac_digits = __intl ? __punct_intl.frac_digits()
                                 : __punct.frac_digits();
      string __grouping = __intl ? __punct_intl.grouping()
                                 : __punct.grouping();
      bool __syntax_ok = true;

      bool __result;

      _CharT __sep = __grouping.size() == 0 ? _CharT() : 
	__intl ? __punct_intl.thousands_sep() : __punct.thousands_sep();

      __result = __get_monetary_value(__s, __end, __out, __c_type,
                                      __point, __frac_digits,
                                      __sep,
                                      __grouping, __syntax_ok);      

      if (!__syntax_ok)
        __err |= ios_base::failbit;
      if (!__result) {
        __err = ios_base::failbit;
        return __s;
      }
      break;
      
    }                           // Close money_base::value case


    }                           // Close switch statement
  }                             // Close for loop

  if (__is_positive) {
    if (__ps.size() > 1) {
      pair<_InputIter, bool>
        __result = __get_string(__s, __end, __ps.data() + 1, __ps.data() + __ps.size());
      __s = __result.first;
      if (!__result.second)
	__err |= ios::failbit;
    }
    if (!(__err & ios_base::failbit))
      __digits = __buf;
  }
  else {
    if (__ns.size() > 1) {
      pair<_InputIter, bool>
        __result = __get_string(__s, __end, __ns.data() + 1, __ns.data() + __ns.size());
      __s = __result.first;
      if (!__result.second)
	__err |= ios::failbit;
    }
    if (!(__err & ios::failbit)) {
      __buf.insert(__buf.begin(),__c_type.widen('-'));
      __digits = __buf;
    }
  }
  if (__s == __end)
    __err |= ios::eofbit;

  return __s;
}
}
