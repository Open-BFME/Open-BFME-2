// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 src/locale_impl.cpp, _Stl_loc_assign_ids.
// Modified: export under the existing BFME2 caller identity, _Stl_loc_init_facets.
// Retail RVA 0x6F80: the 24 facet-ID stores and their order match upstream.
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

namespace _STL
{
void _Stl_loc_init_facets() {
  // This assigns ids to every facet that is a member of a category,
  // and also to money_get/put, num_get/put, and time_get/put
  // instantiated using ordinary pointers as the input/output
  // iterators.  (The default is [io]streambuf_iterator.)

  money_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index                     = 8;
  money_get<char, const char*>::id._M_index        = 9;
  money_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index                     = 10;
  money_put<char, char*>::id._M_index              = 11;

  num_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index                       = 12;
  num_get<char, const char*>::id._M_index          = 13;
  num_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index                       = 14;
  num_put<char, char*>::id._M_index                = 15;
  time_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index                      = 16;
  time_get<char, const char*>::id._M_index         = 17;
  time_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index                      = 18;
  time_put<char, char*>::id._M_index               = 19;

# ifndef _STLP_NO_WCHAR_T

  money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                  = 27;
  money_get<wchar_t, const wchar_t*>::id._M_index  = 28;
  money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                  = 29;
  money_put<wchar_t, wchar_t*>::id._M_index        = 30;

  num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                       = 31;
  num_get<wchar_t, const wchar_t*>::id._M_index    = 32;
  num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > ::id._M_index                      = 33;
  num_put<wchar_t, wchar_t*>::id._M_index          = 34;
  time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                   = 35;
  time_get<wchar_t, const wchar_t*>::id._M_index   = 36;
  time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                   = 37;
  time_put<wchar_t, wchar_t*>::id._M_index         = 38;
  //  messages<wchar_t>::id._M_index                   = 38;
# endif

  //  locale::id::_S_max                               = 39;
}

}
