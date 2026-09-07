// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// Reconstructed STLport 4.5.3 money_put<char>::do_put(string), RVA 0xC410.
// The full 2802-byte body ends at 0xCF02; the earlier 2793-byte Ghidra
// extent cut through its final basic block. No following alignment is claimed.
// Modified from the vendored _monetary.c algorithm with TU-local visibility,
// inlining, and lifetime models established by the retail instruction stream.
//
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

// A direct, potentially throwing C++ free call preserves the retail unwind
// states. Suppress stdlib.h and supply the declarations consumed by cstdlib.
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

// The independently verified 84-byte string range-initializer bodies use
// the public member signature in this reconstruction. Limit this access
// adaptation to the string header; layout and source semantics are unchanged.
#define private public
#include <string>
#undef private
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
};
locale::~locale() _STLP_NOTHROW { _M_impl->_M_decr(); }

}

// Keep the two-argument range helper visible for call-side analysis without
// inlining it into the constructor. Both pointer instantiations have been
// independently reproduced at 0x8D00 with their complete 84-byte bodies.
namespace _STL {
template <> template <> __declspec(noinline) void
basic_string<char>::_M_range_initialize(char* first, char* last) {
  _M_range_initialize(first, last, forward_iterator_tag());
}
template <> template <> __declspec(noinline) void
basic_string<char>::_M_range_initialize(const char* first, const char* last) {
  _M_range_initialize(first, last, forward_iterator_tag());
}
}
namespace _STL {
// The range constructor retains its allocator-base call; ordinary string
// copies inline their base initialization. Scope the inline-depth constraint
// to this constructor instead of changing every string operation.
#pragma inline_depth(0)
template <> template <> __forceinline basic_string<char>::basic_string(
    const char* first, const char* last, const allocator<char>& a)
    : _String_base<char, allocator<char> >(a) {
  _M_range_initialize(first, last);
}
}
namespace _STL {
#pragma inline_depth(255)
template <> inline basic_string<char>::basic_string(const basic_string<char>& s)
    : _String_base<char, allocator<char> >(s.get_allocator()) {
  _M_range_initialize(s._M_start, s._M_finish);
}
}
namespace _STL {
typedef ostreambuf_iterator<char, char_traits<char> > _MoneyOut;

template <> __forceinline _MoneyOut& _MoneyOut::operator=(char c) {
  _M_ok = _M_ok && !traits_type::eq_int_type(
      _M_buf->sputc(c), traits_type::eof());
  return *this;
}
template <> __declspec(noinline) _MoneyOut __copy(
    const char* first, const char* last, _MoneyOut result,
    const random_access_iterator_tag&, int*) {
  for (int n = last - first; n > 0; --n) {
    *result = *first;
    ++first;
    ++result;
  }
  return result;
}
// A stream-buffer output iterator does not advance: its increment and
// dereference operators return itself. Spell that specialization directly,
// retaining one external assignment per iteration as in retail.
#pragma inline_depth(0)
template <> __forceinline _MoneyOut fill_n(_MoneyOut first, unsigned int n, const char& value) {
  for (; n > 0; --n) first = value;
  return first;
}
#pragma inline_depth(255)
template <> __forceinline _MoneyOut copy(const char* first, const char* last, _MoneyOut result) {
  random_access_iterator_tag tag;
  return __copy(first, last, result, tag, (ptrdiff_t*)0);
}

// Decimal-point writes remain calls while the space and sign writes inline.
#pragma inline_depth(0)
__forceinline void __money_write_point(_MoneyOut& out, const char& value) {
  out = value;
}
#pragma inline_depth(255)
// The formatting policy carries polarity and the empty iterator category.
// Empty-base optimization lets its category and bool occupy the same byte,
// matching retail's reuse of the polarity slot for currency-copy dispatch.
// The category conversion uses an ordinary C++ base reference.
struct _MoneySignPolicy : random_access_iterator_tag { bool negative; };
typedef char _MoneySignPolicyIsOneByte[(sizeof(_MoneySignPolicy) == 1) ? 1 : -1];
__forceinline _MoneyOut __money_copy_symbol(
    const char* first, const char* last, _MoneyOut out,
    const _MoneySignPolicy& policy) {
  return __copy(first, last, out, policy, (ptrdiff_t*)0);
}
template <> _MoneyOut money_put<char, _MoneyOut>::do_put(
    _MoneyOut __s, bool __intl, ios_base& __str,
    char_type __fill, const string_type& __digits) const
{
  typedef char _CharT;
  typedef _MoneyOut _OutputIter;
  typedef ctype<_CharT>             _Ctype;
  typedef moneypunct<_CharT, false> _Punct;
  typedef moneypunct<_CharT, true>  _Punct_intl;

  locale __loc = __str.getloc();
  const _Ctype&      __c_type      = use_facet<_Ctype>(__loc) ;
  const _Punct&      __punct      = use_facet<_Punct>(__loc) ;
  const _Punct_intl& __punct_intl = use_facet<_Punct_intl>(__loc) ;

  // some special characters

  char_type __minus = __c_type.widen('-');
  char_type __plus  = __c_type.widen('+');
  char_type __space = __c_type.widen(' ');
  char_type __zero  = __c_type.widen('0');
  char_type __point = __intl ? __c_type.widen(__punct_intl.decimal_point())
			     : __c_type.widen(__punct.decimal_point());

  char_type __sep = __intl ? __punct_intl.thousands_sep()
			   : __punct     .thousands_sep();

  string __grouping = __intl ? __punct_intl.grouping()
		             : __punct     .grouping();

  int __frac_digits      = __intl ? __punct_intl.frac_digits()
                                  : __punct.frac_digits();

  string_type __curr_sym = __intl ? __punct_intl.curr_symbol()
                                  : __punct.curr_symbol();

    // if there are no digits we are going to return __s.  If there
    // are digits, but not enough to fill the frac_digits, we are
    // going to add zeros.  I don't know whether this is right or
    // not.

  if (__digits.size() == 0)
    return __s;

  string_type::const_iterator __digits_first = __digits.begin();
  string_type::const_iterator __digits_last  = __digits.end();

  _MoneySignPolicy __sign_policy;
  __sign_policy.negative = *__digits_first == __minus;
  if (__sign_policy.negative)
    ++__digits_first;

  string_type __sign = __intl ?
			 __sign_policy.negative ? __punct_intl.negative_sign()
				       : __punct_intl.positive_sign()
			      :
			 __sign_policy.negative ? __punct.negative_sign()
				       : __punct.positive_sign();
  string_type::const_iterator __cp = __digits_first;
  while (__cp != __digits_last && __c_type.is(ctype_base::digit, *__cp))
    ++__cp;
  if (__cp == __digits_first)
    return __s;
  __digits_last = __cp;

  // If grouping is required, we make a copy of __digits and
  // insert the grouping.

  // To handle the fractional digits, we augment the first group
  // by frac_digits.  If there is only one group, we need first
  // to duplicate it.

  string_type __new_digits(__digits_first, __digits_last);

  if (__grouping.size() != 0) {
    if (__grouping.size() == 1)
      __grouping.push_back(__grouping[0]);
    __grouping[0] += __frac_digits;
    _CharT* __data_ptr = __CONST_CAST(_CharT*,__new_digits.data());
    _CharT* __data_end = __data_ptr + __new_digits.size();

    ptrdiff_t __value_length = __insert_grouping(__data_ptr,
	  				         __data_end,
					         __grouping,
					         __sep,
					         __plus, __minus, 0);
    __digits_first = __new_digits.begin();
    __digits_last  = __digits_first + __value_length;
  }

  // Determine the amount of padding required, if any.

  size_t __width        = __str.width();

#if defined(_STLP_DEBUG) && (defined(__HP_aCC) || (__HP_aCC <= 1))
  size_t __value_length = operator -(__digits_last, __digits_first);
#else
  size_t __value_length = __digits_last - __digits_first;
#endif

  size_t __length       = __value_length;

  __length += __sign.size();
  if (__frac_digits != 0)
    ++__length;

  bool __generate_curr = (__str.flags() & ios_base::showbase) !=0;
  if (__generate_curr)
    __length += __curr_sym.size();
  // All retail pattern-result slots are eight-byte aligned, and the function
  // realigns ESP to eight bytes. Express that observed local ABI requirement.
  __declspec(align(8)) money_base::pattern __format =
    __intl ? (__sign_policy.negative ? __punct_intl.neg_format()
                            : __punct_intl.pos_format())
           : (__sign_policy.negative ? __punct.neg_format()
                            : __punct.pos_format());
  {
    for (int __i = 0; __i < 4; ++__i)
      if (__format.field[__i] == (char) money_base::space)
        ++__length;
  }

  size_t __fill_amt = __length < __width ? __width - __length : 0;

  ios_base::fmtflags __fill_pos = __str.flags() & ios_base::adjustfield;

  if (__fill_amt != 0 &&
      !(__fill_pos & (ios_base::left | ios_base::internal)))
    __s = fill_n(__s, __fill_amt, __fill);

  for (int __i = 0; __i < 4; ++__i) {
    char __ffield = __format.field[__i];
    if (__ffield == money_base::none) {
      if (__fill_amt != 0 && __fill_pos == ios_base::internal)
        __s = fill_n(__s, __fill_amt, __fill);
    }
    else if (__ffield == money_base::space) {
      *__s++ = __space;
      if (__fill_amt != 0 && __fill_pos == ios_base::internal)
        __s = fill_n(__s, __fill_amt, __fill);
    }
    else if (__ffield == money_base::symbol) {
      if (__generate_curr)
        __s = __money_copy_symbol(static_cast<const string_type&>(__curr_sym).begin(), static_cast<const string_type&>(__curr_sym).end(), __s, __sign_policy);
    }
    else if (__ffield == money_base::sign) {
      if (__sign.size() != 0)
        *__s++ = __sign[0];
    }
    else if (__ffield == money_base::value) {
      if (__frac_digits == 0)
        __s = copy(__digits_first, __digits_last, __s);
      else {
        if ((int)__value_length <= __frac_digits) {
          __money_write_point(__s,__point);
          __s = copy(__digits_first, __digits_last, __s);
          __s =  fill_n(__s, __frac_digits - __value_length, __zero);
        }
        else {
          __s = copy(__digits_first, __digits_last - __frac_digits, __s);
          if (__frac_digits != 0) {
            __money_write_point(__s,__point);
            __s = copy(__digits_last - __frac_digits, __digits_last, __s);
          }
        }
      }
    }
  } // Close for loop

  // Ouput rest of sign if necessary.

  if (__sign.size() > 1)
    __s = copy(static_cast<const string_type&>(__sign).begin() + 1, static_cast<const string_type&>(__sign).end(), __s);
  if (!(__fill_pos & (ios_base::right | ios_base::internal)))
    __s = fill_n(__s, __fill_amt, __fill);

  return __s;
}
}
