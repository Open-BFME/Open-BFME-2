// cl:  /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// Reconstructed STLport 4.5.3 wide monetary string formatting.
// Retail DF20..E952 is 2610 bytes, emitted exactly with the retail 0x118
// frame.
// The out-of-line __copy<const wchar_t*, _MoneyOut, int> (0xE9C0) is only
// declared here: once c2 has compiled a same-TU callee it knows the tag
// reference does not escape and overlaps the tag temporaries with the
// allocator/forward-tag slot; an opaque callee gives retail's packing (sym
// tag with the sign flag at esp+0x17, extension tag alone at esp+0x4f). The
// inlined copies use the long-distance instantiation, which has the same body.
// The wide _String_base destructor carries nine qualified calls of a phantom
// struct destructor that compile to nothing: they raise its inline cost so it
// is outlined at early exits and conditional temporaries.
// The wide basic_string destructor carries six late-folded `this == 0` guards:
// they raise its inline cost so that it is outlined at the sign temporaries and
// return 2 while ~_String_base is outlined at the currency temporaries and
// return 1 (retail's unwind and call map). A late fold stops the 4-iteration
// unroll of the space-count loop; reading the pattern as two halfwords gives
// retail's scalar form (cmp al/ah, shr 16, cmp al/ah) regardless.
// Calls resolve to the true string destructor names: ~basic_string<wchar_t>
// at 0xB3C0 and ~_String_base<wchar_t> at 0x142D70. Evidence:
// reverse/attempt_support/df20-exact-true-naming-20261021/handoff.md.
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

// Currency and zero-fraction copies use the retail helper; fractional and
// sign-tail copies retain their inline loops. No explicit local alignment is needed.

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

#define private public
#include <string>
#undef private
// Preserve inline frees while leaving the out-of-line malloc allocator cleanup
// to its retail-proven provider.
namespace _STL { template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t) { free((char *)__p); } }
// allocator<wchar_t>::deallocate is the retail-proven fold at 0x0046264A: keep
// the inline expansions without emitting a differing copy ahead of it in link order.
namespace _STL { template <> __declspec(dllimport) __forceinline void allocator<unsigned short>::deallocate(unsigned short *__p, size_t __n) const
{ if (__p != 0) __sgi_alloc::deallocate((void *)__p, __n * sizeof(unsigned short)); } }

// Retain inline allocator cleanup without an unused non-retail external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline void
allocator<char>::deallocate(char *p, size_type n) const
{
    _STLP_ASSERT((p == 0) == (n == 0))
    if (p != 0)
        __sgi_alloc::deallocate((void *)p, n * sizeof(char));
}
}
enum { _MONEY_LEAKS_CHECK = 0 };
namespace _STL {
struct _MoneyLeak { ~_MoneyLeak() { if (_MONEY_LEAKS_CHECK) free(0); } };
struct _MoneyPhantom { _MoneyLeak l; };
template <> inline _String_base<unsigned short, allocator<unsigned short> >::~_String_base() {
  _M_deallocate_block();
  ((_MoneyPhantom *)this)->_MoneyPhantom::~_MoneyPhantom();
  ((_MoneyPhantom *)this)->_MoneyPhantom::~_MoneyPhantom();
  ((_MoneyPhantom *)this)->_MoneyPhantom::~_MoneyPhantom();
  ((_MoneyPhantom *)this)->_MoneyPhantom::~_MoneyPhantom();
  ((_MoneyPhantom *)this)->_MoneyPhantom::~_MoneyPhantom();
  ((_MoneyPhantom *)this)->_MoneyPhantom::~_MoneyPhantom();
  ((_MoneyPhantom *)this)->_MoneyPhantom::~_MoneyPhantom();
  ((_MoneyPhantom *)this)->_MoneyPhantom::~_MoneyPhantom();
  ((_MoneyPhantom *)this)->_MoneyPhantom::~_MoneyPhantom();
}
template <> inline basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::~basic_string() {
  if (this == 0) exit(1);
  if (this == 0) exit(1);
  if (this == 0) exit(1);
  if (this == 0) exit(1);
  if (this == 0) exit(1);
  if (this == 0) exit(1);
  if (this == 0) exit(1);
  _Destroy(this->_M_start, this->_M_finish + 1);
}
}
// A declaration preserves the verified out-of-line constructor and its alias
// effects; exposing its body changes the parent's local/temporary allocation.
namespace _STL {
template <> _String_base<wchar_t,allocator<wchar_t> >::_String_base(const allocator<wchar_t>&);
}
#include <locale>
// Suppress this TU's non-retail copy of ?_M_allocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int); }
// Suppress this TU's non-retail copy of ??$fill_n@V?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@IG@_STL@@YA?AV?$ostreambuf:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> ostreambuf_iterator<unsigned short,char_traits<unsigned short> > fill_n<ostreambuf_iterator<unsigned short,char_traits<unsigned short> >,unsigned int,unsigned short>(ostreambuf_iterator<unsigned short,char_traits<unsigned short> >,unsigned int,unsigned short const &); }
// Suppress this TU's non-retail copy of ?reserve@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void basic_string<char,char_traits<char>,allocator<char> >::reserve(unsigned int); }
// Suppress this TU's non-retail copy of ??$_M_range_initialize@PAD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> template <> void basic_string<char,char_traits<char>,allocator<char> >::_M_range_initialize<char *>(char *,char *); }
// Suppress this TU's non-retail copy of ??$_M_range_initialize@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> template <> void basic_string<char,char_traits<char>,allocator<char> >::_M_range_initialize<char const *>(char const *,char const *); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@G@_STL@@QBEPAGIPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ??1?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> >::~basic_string(); }
// Suppress this TU's non-retail copy of ?allocate@?$__malloc_alloc@$0A@@_STL@@SAPAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ??$?0PBG@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAE@PBG0ABV?$allocator@G@1@@Z:
// the rowed retail copy (0x17830) serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> template <> basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> >::basic_string(unsigned short const *,unsigned short const *,allocator<unsigned short> const &); }

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
inline locale::~locale() _STLP_NOTHROW { _M_impl->_M_decr(); }

}

namespace _STL {
// The narrow monetary formatter supplies the shared three-argument initializer.
template <> template <class ForwardIterator> void basic_string<char>::_M_range_initialize(ForwardIterator, ForwardIterator, const forward_iterator_tag &);
template <> template <> inline __declspec(noinline) void basic_string<char>::_M_range_initialize(char* first,char* last) { _M_range_initialize(first,last,forward_iterator_tag()); }
template <> template <> inline __declspec(noinline) void basic_string<char>::_M_range_initialize(const char* first,const char* last) { _M_range_initialize(first,last,forward_iterator_tag()); }
}
namespace _STL {
#pragma inline_depth(0)
template <> template <> __forceinline basic_string<char>::basic_string(const char* first, const char* last, const allocator<char>& a) : _String_base<char, allocator<char> >(a) { _M_range_initialize(first,last); }
}
namespace _STL {
#pragma inline_depth(255)
template <> inline basic_string<char>::basic_string(const basic_string<char>& s) : _String_base<char, allocator<char> >(s.get_allocator()) { _M_range_initialize(s._M_start,s._M_finish); }
}
namespace _STL {
template <> basic_string<wchar_t>::basic_string(const basic_string<wchar_t>&);
#pragma inline_depth(0)
template <> template <> __forceinline void basic_string<wchar_t>::_M_range_initialize(const wchar_t* f, const wchar_t* l) { _M_range_initialize(f, l, forward_iterator_tag()); }
#pragma inline_depth(255)
#pragma inline_depth(2)
template <> template <> __forceinline basic_string<wchar_t>::basic_string(const wchar_t* first,const wchar_t* last,const allocator<wchar_t>& a) : _String_base<wchar_t,allocator<wchar_t> >(a) { _M_range_initialize(first,last); }
#pragma inline_depth(255)
}
namespace _STL {
typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> > _MoneyOut;

template <> _MoneyOut& _MoneyOut::operator=(wchar_t);
#pragma inline_depth(0)
// Preserve the inlined currency-padding loop without a competing fill_n copy.
static __forceinline _MoneyOut __money_fill_n(_MoneyOut first, unsigned int n, const wchar_t& value) {
 for(;n>0;--n) first=value; return first;
}
#pragma inline_depth(255)
template <> _MoneyOut __copy<const wchar_t*, _MoneyOut, ptrdiff_t>(const wchar_t* first, const wchar_t* last, _MoneyOut out, const random_access_iterator_tag&, ptrdiff_t*);
template <> __forceinline _MoneyOut copy(const wchar_t* first, const wchar_t* last, _MoneyOut result) {
  random_access_iterator_tag tag;
  return __copy(first, last, result, tag, (long*)0);
}

#pragma inline_depth(0)
__forceinline void __money_write_point(_MoneyOut& out,const wchar_t& value) { out = value; }
#pragma inline_depth(255)
#pragma inline_depth(0)
__forceinline _MoneyOut __money_copy_sym2(const wchar_t* first, const wchar_t* last, _MoneyOut out) {
  random_access_iterator_tag tag;
  return __copy(first, last, out, tag, (ptrdiff_t*)0);
}
__forceinline _MoneyOut __money_copy_external(const wchar_t* first, const wchar_t* last, _MoneyOut out) {
  random_access_iterator_tag tag;
  return __copy(first, last, out, tag, (ptrdiff_t*)0);
}
#pragma inline_depth(255)
template <> _MoneyOut money_put<wchar_t, _MoneyOut>::do_put(_MoneyOut __s, bool __intl, ios_base& __str, char_type __fill, const string_type& __digits) const
{
  typedef wchar_t _CharT;
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

#pragma inline_depth(255)
    // if there are no digits we are going to return __s.  If there
    // are digits, but not enough to fill the frac_digits, we are
    // going to add zeros.  I don't know whether this is right or
    // not.

  if (__digits.size() == 0) 
  {
    return __s;
  }


  string_type::const_iterator __digits_first = __digits.begin();
  string_type::const_iterator __digits_last  = __digits.end();

  bool __is_negative = *__digits_first == __minus;
  if (__is_negative)
    ++__digits_first;


  string_type __sign = __intl ?
			 __is_negative ? __punct_intl.negative_sign()
				       : __punct_intl.positive_sign()
			      :
			 __is_negative ? __punct.negative_sign()
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
  money_base::pattern __format =
    __intl ? (__is_negative ? __punct_intl.neg_format()
                            : __punct_intl.pos_format())
           : (__is_negative ? __punct.neg_format()
                            : __punct.pos_format());
  { unsigned short __lo = ((unsigned short*)&__format)[0], __hi = ((unsigned short*)&__format)[1];
    if ((char)__lo == (char) money_base::space) ++__length;
    if ((char)(__lo>>8) == (char) money_base::space) ++__length;
    if ((char)__hi == (char) money_base::space) ++__length;
    if ((char)(__hi>>8) == (char) money_base::space) ++__length; }

  size_t __fill_amt = __length < __width ? __width - __length : 0;

  ios_base::fmtflags __fill_pos = __str.flags() & ios_base::adjustfield;

  if (__fill_amt != 0 &&
      !(__fill_pos & (ios_base::left | ios_base::internal)))
    __s = __money_fill_n(__s, __fill_amt, __fill);
    
  for (int __i = 0; __i < 4; ++__i) {
    char __ffield = __format.field[__i];
    if (__ffield == money_base::none) {
      if (__fill_amt != 0 && __fill_pos == ios_base::internal)
        __s = __money_fill_n(__s, __fill_amt, __fill);
    }
    else if (__ffield == money_base::space) {
      *__s++ = __space;
      if (__fill_amt != 0 && __fill_pos == ios_base::internal)
        __s = __money_fill_n(__s, __fill_amt, __fill);
    }
    else if (__ffield == money_base::symbol) {
      if (__generate_curr)
        __s = __money_copy_sym2(__curr_sym.begin(), __curr_sym.end(), __s);
    }
    else if (__ffield == money_base::sign) {
      if (__sign.size() != 0)
        *__s++ = __sign[0];
    }
    else if (__ffield == money_base::value) {
      if (__frac_digits == 0)
        __s = __money_copy_external(__digits_first, __digits_last, __s);
      else {
        if ((int)__value_length <= __frac_digits) {
          __money_write_point(__s,__point);
          __s = copy(__digits_first, __digits_last, __s);
          __s =  __money_fill_n(__s, __frac_digits - __value_length, __zero);
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
    __s = __money_fill_n(__s, __fill_amt, __fill);
  
  return __s;
}
}
