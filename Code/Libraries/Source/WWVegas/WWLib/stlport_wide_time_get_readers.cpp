// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
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
#include <locale>
namespace _STL {
template<> __declspec(noinline) void istreambuf_iterator<wchar_t,char_traits<wchar_t> >::_M_getc() const {
 if (_M_have_c) return;
 int_type c=_M_buf->sgetc();
 _M_c=traits_type::to_char_type(c);
 _M_eof=traits_type::eq_int_type(c,traits_type::eof());
 _M_have_c=true;
}
}
namespace _STL {
typedef istreambuf_iterator<wchar_t,char_traits<wchar_t> > _TimeIn;
typedef time_get<wchar_t,_TimeIn> _TimeFacet;
typedef char _TimeInfoSize[(sizeof(_Time_Info)==540)?1:-1];
typedef char _TimeFacetSize[(sizeof(_TimeFacet)==552)?1:-1];
template <>
_TimeIn
time_get<wchar_t, _TimeIn>::do_get_date(_TimeIn __s, _TimeIn __end,
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

template <>
_TimeIn
time_get<wchar_t, _TimeIn>::do_get_time(_TimeIn __s, _TimeIn __end,
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

}
