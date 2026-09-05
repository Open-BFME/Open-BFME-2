// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 src/time_facets.cpp __write_formatted_time.
// Modified: TU-local ABI declarations and a copy wrapper replace includes.
// Function body retained from the official release; retail RVA 0x18780.
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


extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer,
		const char *format, ...);

namespace _STL
{

template <class T>
class char_traits {};

// The retail wide sbumpc returns unsigned short, the narrow one int, so the
// int_type has to come off the traits rather than being fixed.
template <>
class char_traits<char>
{
public:
	typedef int int_type;
};

template <>
class char_traits<unsigned short>
{
public:
	typedef unsigned short int_type;
};

template <class T>
class allocator {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;

	typedef const CharT *const_iterator;

	size_type size() const { return size_type(_M_finish - _M_start); }
	const CharT &operator[](size_type n) const { return _M_start[n]; }
	const_iterator data() const { return _M_start; }
	const_iterator begin() const { return _M_start; }
	const_iterator end() const { return _M_finish; }

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

struct __false_type {};

}

struct tm
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

namespace _STL
{

class _Time_Info
{
public:
	string _M_dayname[14];
	string _M_monthname[24];
	string _M_am_pm[2];
	string _M_time_format;
	string _M_date_format;
	string _M_date_time_format;
	string _M_long_date_format;
	string _M_long_date_time_format;
};

void *__cdecl __copy_trivial(const void *first, const void *last,
		void *result);

template <class Integer>
char *__cdecl __write_integer(char *buf, int flags, Integer x);

inline char *copy(const char *a,const char *b,char *out){ return static_cast<char *>(__copy_trivial(a,b,out)); }

#define __hour12(hour) \
  (((hour) % 12 == 0) ? (12) : (hour) % 12)

char * __write_formatted_time(char* buf, char format, char modifier,
			      const _Time_Info& table, const tm* t) {
  switch(format) {
    case 'a':
      return copy(table._M_dayname[t->tm_wday].begin(),
	          table._M_dayname[t->tm_wday].end(),
	          buf);

    case 'A':
      return copy(table._M_dayname[t->tm_wday+7].begin(),
	          table._M_dayname[t->tm_wday+7].end(),
	          buf);

    case 'b':
      return copy(table._M_monthname[t->tm_mon].begin(),
	          table._M_monthname[t->tm_mon].end(),
	          buf);

    case 'B':
      return copy(table._M_monthname[t->tm_mon+12].begin(),
	     table._M_monthname[t->tm_mon+12].end(),
	     buf);

    case 'c': {
      const char * cp = (modifier != '#') ? table._M_date_time_format.data():\
      									   table._M_long_date_time_format.data();
      const char* cp_end = (modifier != '#') ? cp + table._M_date_time_format.size():\
      										  cp + table._M_long_date_time_format.size();
      char mod = 0;
      while (cp != cp_end) {
	if (*cp == '%') {
	  ++cp; if(*cp == '#') mod = *cp++; else mod = 0;
	  buf = __write_formatted_time(buf, *cp++, mod, table, t);
	}
	else
	  *buf++ = *cp++;
      }
      return buf;
    }

    case 'd': 
      sprintf(buf, (modifier != '#')?"%.2ld":"%ld", (long)t->tm_mday);
      return ((long)t->tm_mday < 10L && modifier == '#')?buf+1:buf + 2;

    case 'e':
      sprintf(buf, "%2ld", (long)t->tm_mday);
      return buf + 2;

    case 'H':
      sprintf(buf, (modifier != '#')?"%.2ld":"%ld", (long)t->tm_hour);
      return ((long)t->tm_hour < 10L && modifier == '#')?buf+1:buf + 2;

    case 'I':
      sprintf(buf, (modifier != '#')?"%.2ld":"%ld", (long)__hour12(t->tm_hour));
      return ((long)__hour12(t->tm_hour) < 10L && modifier == '#')?buf+1:buf + 2;

    case 'j':
      return __write_integer(buf, 0, (long)((long)t->tm_yday + 1));

    case 'm':
      sprintf(buf, (modifier != '#')?"%.2ld":"%ld", (long)t->tm_mon + 1);
      return ((long)(t->tm_mon + 1) < 10L && modifier == '#')?buf+1:buf + 2;

    case 'M':
      sprintf(buf, (modifier != '#')?"%.2ld":"%ld", (long)t->tm_min);
      return ((long)t->tm_min < 10L && modifier == '#')?buf+1:buf + 2;

    case 'p':
      return copy(table._M_am_pm[t->tm_hour/12].begin(),
	          table._M_am_pm[t->tm_hour/12].end(),
	   	  buf);

    case 'S': // pad with zeros
       sprintf(buf, (modifier != '#')?"%.2ld":"%ld", (long)t->tm_sec);
       return ((long)t->tm_sec < 10L && modifier == '#')?buf+1:buf + 2;

    case 'U':
      return __write_integer(buf, 0, 
			    long((t->tm_yday - t->tm_wday + 7) / 7));
      //      break;

    case 'w':
      return __write_integer(buf, 0, (long)t->tm_wday);
      //      break;

    case 'W':
      return __write_integer(buf, 0,
		             (long)(t->tm_wday == 0       ?
			      (t->tm_yday + 1) / 7 :
			      (t->tm_yday + 8 - t->tm_wday) / 7));

    case'x': {
      const char * cp = (modifier != '#') ? table._M_date_format.data():\
      									   table._M_long_date_format.data();
      const char* cp_end = (modifier != '#') ? cp + table._M_date_format.size():\
      										  cp + table._M_long_date_format.size();
      char mod = 0;
      while (cp != cp_end) {
	if (*cp == '%') {
	  ++cp; if(*cp == '#') mod = *cp++; else mod = 0;
	  buf = __write_formatted_time(buf, *cp++, mod, table, t);
	}
	else
	  *buf++ = *cp++;
      }
      return buf;
    }

    case 'X': {
      const char * cp = table._M_time_format.data();
      const char* cp_end = cp + table._M_time_format.size();
      char mod = 0;
      while (cp != cp_end) {
	if (*cp == '%') {
	  ++cp; if(*cp == '#') mod = *cp++; else mod = 0;
	  buf = __write_formatted_time(buf, *cp++, mod, table, t);
	}
	else
	  *buf++ = *cp++;
      }
      return buf;
    }
    case 'y':
      return __write_integer(buf, 0, (long)((long)(t->tm_year + 1900) % 100));

    case 'Y':
      return __write_integer(buf, 0, (long)((long)t->tm_year + 1900));

    case '%':
      *buf++ = '%';
      return buf;

#ifdef __GNUC__

      // fbp : at least on SUN 
# if defined ( _STLP_UNIX ) && ! defined (__linux__)
#  define __USE_BSD 1
# endif
 
   /*********************************************
    *     JGS, handle various extensions        *
    *********************************************/

    case 'h': /* POSIX.2 extension */
      // same as 'b', abbrev month name
      return copy(table._M_monthname[t->tm_mon].begin(),
	          table._M_monthname[t->tm_mon].end(),
	          buf);

    case 'C': /* POSIX.2 extension */
      // same as 'd', the day 
      sprintf(buf, "%2ld", (long)t->tm_mday);
      return buf + 2;

    case 'D': /* POSIX.2 extension */
      // same as 'x'
      return __subformat(table._M_date_format, buf, table, t);

    case 'k': /* GNU extension */
      sprintf(buf, "%2ld", (long)t->tm_hour);
      return buf + 2;

    case 'l': /* GNU extension */
      sprintf(buf, "%2ld", (long)t->tm_hour % 12);
      return buf + 2;

    case 'n': /* POSIX.2 extension */
      *buf++ = '\n';
      return buf;

    case 'R': /* GNU extension */
      return __subformat("%H:%M", buf, table, t);

    case 'r': /* POSIX.2 extension */
      return __subformat("%I:%M:%S %p", buf, table, t);

    case 'T': /* POSIX.2 extension.  */
      return __subformat("%H:%M:%S", buf, table, t);

    case 't': /* POSIX.2 extension.  */
      *buf++ = '\t';
      return buf;

    case 'u': /* POSIX.2 extension.  */
      return __write_integer(buf, 0, long((t->tm_wday - 1 + 7)) % 7 + 1);

    case 's': {
      time_t __t;
      __t = mktime ((tm*)t);
      return __write_integer(buf, 0, (long)__t );
    }
    case 'g': /* GNU extension */
    case 'G': {
      int year = t->tm_year + __TM_YEAR_BASE;
      int days = __iso_week_days (t->tm_yday, t->tm_wday);
      if (days < 0) {
	  /* This ISO week belongs to the previous year.  */
	  year--;
	  days = __iso_week_days (t->tm_yday + (365 + __is_leap (year)),
				t->tm_wday);
      } else {
	int d = __iso_week_days (t->tm_yday - (365 + __is_leap (year)),
			       t->tm_wday);
	if (0 <= d) {
	  /* This ISO week belongs to the next year.  */
	  year++;
	  days = d;
	}
      }
      switch (format) {
      case 'g':
	return __write_integer(buf, 0, (long)(year % 100 + 100) % 100);
      case 'G':
	return __write_integer(buf, 0, (long)year);
      default:
	return __write_integer(buf, 0, (long)days / 7 + 1);
      }
    }

# if defined ( _STLP_USE_GLIBC  ) && ! defined (__CYGWIN__)
    case 'z':		/* GNU extension.  */
      if (t->tm_isdst < 0)
	break;
      {
	int diff;
#if defined(__USE_BSD) || defined(__BEOS__)
	diff = t->tm_gmtoff;
#else
	diff = t->__tm_gmtoff;
#endif	
	if (diff < 0) {
	  *buf++ = '-';
	  diff = -diff;
	} else
	  *buf++ = '+';
	
	diff /= 60;
	sprintf(buf, "%.4d", (diff / 60) * 100 + diff % 60);
	return buf + 4;
      }
# endif /* __GLIBC__ */
#endif /* __GNUC__ */

    default:
      //      return buf;
      break;
  }
  return buf;
}
}
