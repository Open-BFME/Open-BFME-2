// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// Modified STLport 4.5.3 src/time_facets.cpp and stl/_algobase.h.
// Initialize the complete 540-byte _Time_Info using the original classic
// day/month tables and formatting strings. Long-date fields remain empty,
// exactly as in the primary source's default-locale initializer.
//
// The copy loop stays visible but out of line. MSVC uses its side-effect
// information to reuse the dead input-parameter home for the return object
// and empty dispatch tag. An opaque declaration allocates an extra stack
// slot; neither register constraints nor inline assembly is necessary.
//
// Retail __copy is 124 bytes at RVA 0x19180; _Init_timeinfo is 315 bytes at
// 0x19260. Their final returns end at 0x191FC / 0x1939B, excluding alignment.
// The original 196-byte day table and 576-byte month table are verified too.
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
typedef back_insert_iterator<string> _TimeOut;
typedef char _TimeInfoStorage[(sizeof(_Time_Info) == 540) ? 1 : -1];
template<> __declspec(noinline) _TimeOut
__copy<const char*, _TimeOut, int>(const char* first, const char* last,
                                 _TimeOut result,
                                 const random_access_iterator_tag&, int*) {
  for (int count = last - first; count > 0; --count) {
    *result = *first;
    ++first;
    ++result;
  }
  return result;
}
static inline void copy_cstring(const char * s, string& v) {
  copy(s, s + strlen(s), back_insert_iterator<string >(v));
}

// default "C" values for month and day names

  const char default_dayname[][14] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat",
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
    "Friday", "Saturday"};

  const char default_monthname[][24] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"};

// _Init_time_info: initialize table with
// "C" values (note these are not defined in the C standard, so this
// is somewhat arbitrary).

void _STLP_CALL _Init_timeinfo(_Time_Info& table) {
  int i;
  for (i = 0; i < 14; ++i)
    copy_cstring(default_dayname[i], table._M_dayname[i]);
  for (i = 0; i < 24; ++i)
    copy_cstring(default_monthname[i], table._M_monthname[i]);
  copy_cstring("AM", table._M_am_pm[0]);
  copy_cstring("PM", table._M_am_pm[1]);
  copy_cstring("%H:%M:%S", table._M_time_format);
  copy_cstring("%m/%d/%y",  table._M_date_format);
  copy_cstring("%a %b %e %H:%M:%S %Y", table._M_date_time_format);
}

}
