// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport46
//
// Modified STLport 4.5.3 time_get time/date readers.
// Keeping _M_getc visible but noinline exposes its exact field writes to the
// compiler and preserves the four saved registers across the format parser.
// An opaque declaration lost that information and caused the old bank's
// register/frame differences. No alias-relaxation flag is needed.
// The complete vendor _Time_Info has 45 strings (540 bytes); each facet is552.
// Both code extents end at ret 0x20; intervening CC alignment is excluded.
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
#define _STLP_INTERNAL_STREAMBUF
#include <stl/_alloc.h>
// Public malloc release uses retail's unoptimized import entry; callers keep the header inline body.
namespace _STL {
#pragma optimize("", off)
template <> __forceinline void __malloc_alloc<0>::deallocate(void *p, size_t) { free((char *)p); }
#pragma optimize("", on)
}

#include <locale>
#include <cstddef>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> basic_string<char,char_traits<char>,allocator<char> > * __match<istreambuf_iterator<char,char_traits<char> >,basic_string<char,char_traits<char>,allocator<char> > *,long>(istreambuf_iterator<char,char_traits<char> > &,istreambuf_iterator<char,char_traits<char> > &,basic_string<char,char_traits<char>,allocator<char> > *,basic_string<char,char_traits<char>,allocator<char> > *,long *); }
// The format parser is retail's row in stlport_narrow_get_formatted_time.cpp;
// the four-argument __match forwarder is this unit's own row.
namespace _STL { template <> const char * __get_formatted_time<istreambuf_iterator<char, char_traits<char> >, const char *>(istreambuf_iterator<char, char_traits<char> >, istreambuf_iterator<char, char_traits<char> >, const char *, const char *, const _Time_Info &, ios_base::iostate &, tm *); }
namespace _STL { template string * __match<istreambuf_iterator<char, char_traits<char> >, string *>(istreambuf_iterator<char, char_traits<char> > &, istreambuf_iterator<char, char_traits<char> > &, string *, string *); }
// bfme link decl-only begin
namespace _STL { template <> istreambuf_iterator<char, char_traits<char> > istreambuf_iterator<char, char_traits<char> >::operator++(int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> char istreambuf_iterator<char, char_traits<char> >::operator*() const; }
namespace _STL { template <> istreambuf_iterator<char, char_traits<char> > & istreambuf_iterator<char, char_traits<char> >::operator++(); }
namespace _STL { template <> void istreambuf_iterator<char, char_traits<char> >::_M_bumpc(); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
namespace _STL {
// Pointer-only ABI declarations keep the already verified 35-byte narrow
// _M_getc body, including its out-of-line sgetc call.
template<> class basic_streambuf<char,char_traits<char> > {
public:
  typedef char_traits<char>::int_type int_type;
  int_type sgetc();
  int_type sbumpc();
};
template<> __declspec(noinline) void istreambuf_iterator<char,char_traits<char> >::_M_getc() const {
 if (_M_have_c) return;
 int_type c=_M_buf->sgetc();
 _M_c=traits_type::to_char_type(c);
 _M_eof=traits_type::eq_int_type(c,traits_type::eof());
 _M_have_c=true;
}
}
// istreambuf_iterator<char>::equal is retail's 126-byte body at 0x0000FA00, owned by
// stlport_narrow_istreambuf_iterator_equal.cpp. This unit's copy (with _M_getc out of
// line) is not retail's and came before it in link order; the body still inlines
// here, imported, so the unit emits no copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool istreambuf_iterator<char, char_traits<char> >::equal(const istreambuf_iterator<char, char_traits<char> >& __i) const {
  if (this->_M_buf)
    this->_M_getc();
  if (__i._M_buf)
    __i._M_getc();
  return this->_M_eof == __i._M_eof;
}
}
namespace _STL {
typedef istreambuf_iterator<char,char_traits<char> > _TimeIn;
typedef time_get<char,_TimeIn> _TimeFacet;
typedef char _TimeInfoSize[(sizeof(_Time_Info)==540)?1:-1];
typedef char _TimeFacetSize[(sizeof(_TimeFacet)==552)?1:-1];
template <> inline
_TimeIn
time_get<char, _TimeIn>::do_get_date(_TimeIn __s, _TimeIn __end,
				  ios_base& /* __str */, ios_base::iostate&  __err,
				  tm* __t) const 
{
  typedef string::const_iterator string_iterator;

  string_iterator __format
    = _M_timeinfo._M_date_format.begin();
  string_iterator __format_end
    = _M_timeinfo._M_date_format.end();
  
  string_iterator __result
    = __get_formatted_time(__s, __end, __format, __format_end,
                           /* _Ch() ,*/  _M_timeinfo, __err, __t);
  if (__result == __format_end)
    __err = ios_base::goodbit;
  else {
    __err = ios_base::failbit;
    if (__s == __end)
      __err |= ios_base::eofbit;
  }
  return __s;
}

template <> inline
_TimeIn
time_get<char, _TimeIn>::do_get_time(_TimeIn __s, _TimeIn __end,
				  ios_base& /* __str */, ios_base::iostate&  __err,
				  tm* __t) const 
{
  typedef string::const_iterator string_iterator;
  string_iterator __format
    = _M_timeinfo._M_time_format.begin();
  string_iterator __format_end
    = _M_timeinfo._M_time_format.end();
  
  string_iterator __result
    = __get_formatted_time(__s, __end, __format, __format_end,
			   /* _Ch() , */ _M_timeinfo, __err, __t);
  __err = __result == __format_end ? ios_base::goodbit 
    : ios_base::failbit;
  if (__s == __end)
    __err |= ios_base::eofbit;
  return __s;
}

template _TimeIn time_get<char, _TimeIn>::do_get_date(
    _TimeIn, _TimeIn, ios_base&, ios_base::iostate&, tm*) const;
template _TimeIn time_get<char, _TimeIn>::do_get_time(
    _TimeIn, _TimeIn, ios_base&, ios_base::iostate&, tm*) const;

}
