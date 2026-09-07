// ?do_put@?$money_put@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@_NAAVios_base@2@GABV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@@Z
// partial score=0.2693486590038314 date=2026-09-07
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// Partial reconstruction of STLport 4.5.3 wide monetary string formatting.
// True retail code is DF20..E952, 2610 bytes; trailing 14 alignment bytes
// are excluded. This source emits 2581 bytes and is NOT a matched claim.
// The aligned pattern and opaque output assignment reproduce the broad ABI.
// Remaining blocker: retail uses 3 whole-string and 6 base destructors plus
// 6 inline frees; declaring the whole string destructor out of line merges
// cleanup paths and emits the wrong lifetime policy. Generic allocator/proxy
// destructor changes and inline-depth cycling do not reproduce that mixture.
// Position equality is 703/2610 after eight independently verified 27-byte
// facet getter aliases, with the Base allocator constructor still unresolved.
// All getter proofs are relocation-free vtable-slot forwarding bodies at
// 15E50 (grouping), EA30 (currency), EA50 (positive), and EA70 (negative).
// No new pins or matched rows were added for this attempt.
//
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
namespace _STL { template <> basic_string<wchar_t>::~basic_string(); }
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

namespace _STL {
template <> template <> __declspec(noinline) void basic_string<char>::_M_range_initialize(char* first,char* last) { _M_range_initialize(first,last,forward_iterator_tag()); }
template <> template <> __declspec(noinline) void basic_string<char>::_M_range_initialize(const char* first,const char* last) { _M_range_initialize(first,last,forward_iterator_tag()); }
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
template <> template <> __forceinline basic_string<wchar_t>::basic_string(const wchar_t* first,const wchar_t* last,const allocator<wchar_t>& a) : _String_base<wchar_t,allocator<wchar_t> >(a) { _M_range_initialize(first,last,forward_iterator_tag()); }
#pragma inline_depth(255)
}
namespace _STL {
typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> > _MoneyOut;

template <> _MoneyOut& _MoneyOut::operator=(wchar_t);
#pragma inline_depth(0)
template <> __forceinline _MoneyOut fill_n(_MoneyOut first, unsigned int n, const wchar_t& value) {
 for(;n>0;--n) first=value; return first;
}
#pragma inline_depth(255)
template <> __forceinline _MoneyOut copy(const wchar_t* first, const wchar_t* last, _MoneyOut result) {
  random_access_iterator_tag tag;
  return __copy(first, last, result, tag, (ptrdiff_t*)0);
}

#pragma inline_depth(0)
__forceinline void __money_write_point(_MoneyOut& out,const wchar_t& value) { out = value; }
#pragma inline_depth(255)
struct _MoneySignPolicy : random_access_iterator_tag { bool negative; };
__forceinline _MoneyOut __money_copy_symbol(const wchar_t* first,const wchar_t* last,_MoneyOut out,const _MoneySignPolicy& policy) { return __copy(first,last,out,policy,(ptrdiff_t*)0); }
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
