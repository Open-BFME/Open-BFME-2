// ?__write_formatted_time@_STL@@YAPADPADDDABV_Time_Info@1@PBUtm@@@Z
// partial score=0.9 date=2026-09-03
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __write_formatted_time, the strftime-style worker behind
// time_put::do_put. Its name was already pinned; nothing in the vendored
// headers carries its body, because it lives in STLport's src/, so this is
// reconstructed from retail.
//
// The switch runs from '%' to 'y' through a byte index table at 0x00418CD8
// and a jump table at 0x00418C7C, and it has 22 live cases. Three shapes:
//
//   * name lookups (a A b B p) copy a _Time_Info string out with the
//     out-of-line __copy_trivial. The abbreviated day and month names are the
//     first half of each table and the full names the second, which is where
//     the +7 and +12 come from.
//   * numeric fields split two ways. d e H I m M S go through sprintf with
//     "%ld" or "%.2ld" chosen on the modifier - "%2ld" for e - and then
//     return buf plus one or two by re-reading the value, because sprintf
//     could have aliased it. j U w W y Y instead call __write_integer, which
//     was landed for this.
//   * c x X re-enter this function for each directive of a _Time_Info format
//     string. Retail carries three copies of that loop rather than a call, so
//     the helper is written __forceinline here.
//
// tm's field offsets are read straight off the body: sec 0, min 4, hour 8,
// mday 0x0C, mon 0x10, year 0x14, wday 0x18, yday 0x1C. The year cases add
// 0x76C, which is 1900.

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

char *__cdecl __write_formatted_time(char *buf, char format, char modifier,
		const _Time_Info &table, const tm *t);

// The pointer and the length are each selected by their own test at the c and
// x call sites - `cond ? A.begin() : B.begin()` and `cond ? A.size() :
// B.size()` - which is why retail carries two copies of the modifier test in
// those cases. Selecting the STRING once and then asking it for both, in
// either spelling, lets cl fold the two tests into one address computation
// and the body stops matching.
//
// Flag search: the flag set is NOT the lever here. /Ob1, /Ox, /O2 /Ob1 and the
// unit's own flags all reproduce the prologue and both switch tables exactly
// and all leave the same residue; /Od /Ob1 loses the prologue entirely. So the
// 42 bytes are a source-shape question and nothing else.
//
// Refuted for that, all of which cl folds back to one test: the chosen string
// passed by reference; begin and size as separate arguments of one ternary
// over the string; independent ternaries over begin() and size(); and two
// separate if/else statements assigning to two locals. Retail also loads the
// modifier into al once and compares the register twice, where every one of
// these compares the stack slot directly - which is the same fact seen from
// the other side, since a value tested once does not need a register.
__forceinline char *__subformat(char *buf, const string &fmt,
		const _Time_Info &table, const tm *t)
{
	const char *p = fmt.begin();
	const char *end = fmt.begin() + fmt.size();

	while (p != end) {
		if (*p == '%') {
			char mod;
			++p;
			if (*p == '#') {
				mod = '#';
				++p;
			}
			else {
				mod = 0;
			}
			buf = __write_formatted_time(buf, *p, mod, table, t);
		}
		else {
			*buf++ = *p;
		}
		++p;
	}

	return buf;
}

char *__cdecl __write_formatted_time(char *buf, char format, char modifier,
		const _Time_Info &table, const tm *t)
{
	switch (format) {
	case 'a':
		return static_cast<char *>(__copy_trivial(
				table._M_dayname[t->tm_wday].begin(), table._M_dayname[t->tm_wday].end(), buf));

	case 'A':
		return static_cast<char *>(__copy_trivial(
				table._M_dayname[t->tm_wday + 7].begin(), table._M_dayname[t->tm_wday + 7].end(), buf));

	case 'b':
		return static_cast<char *>(__copy_trivial(
				table._M_monthname[t->tm_mon].begin(), table._M_monthname[t->tm_mon].end(), buf));

	case 'B':
		return static_cast<char *>(__copy_trivial(
				table._M_monthname[t->tm_mon + 12].begin(), table._M_monthname[t->tm_mon + 12].end(), buf));

	case 'c':
		return __subformat(buf, modifier == '#'
				? table._M_long_date_time_format
				: table._M_date_time_format, table, t);

	case 'd':
		sprintf(buf, modifier == '#' ? "%%ld" : "%%.2ld", (long)(t->tm_mday));
		return buf + ((t->tm_mday) < 10 && modifier == '#' ? 1 : 2);

	case 'e':
		sprintf(buf, "%2ld", (long)t->tm_mday);
		return buf + 2;

	case 'H':
		sprintf(buf, modifier == '#' ? "%%ld" : "%%.2ld", (long)(t->tm_hour));
		return buf + ((t->tm_hour) < 10 && modifier == '#' ? 1 : 2);

	case 'I': {
		long hour = t->tm_hour % 12;
		if (hour == 0)
			hour = 12;
		sprintf(buf, modifier == '#' ? "%ld" : "%.2ld", hour);
		hour = t->tm_hour % 12;
		if (hour != 0 && hour < 10 && modifier == '#')
			return buf + 1;
		return buf + 2;
	}

	case 'j':
		return __write_integer(buf, 0, (long)(t->tm_yday + 1));

	case 'm':
		sprintf(buf, modifier == '#' ? "%%ld" : "%%.2ld", (long)(t->tm_mon + 1));
		return buf + ((t->tm_mon + 1) < 10 && modifier == '#' ? 1 : 2);

	case 'M':
		sprintf(buf, modifier == '#' ? "%%ld" : "%%.2ld", (long)(t->tm_min));
		return buf + ((t->tm_min) < 10 && modifier == '#' ? 1 : 2);

	case 'p':
		return static_cast<char *>(__copy_trivial(
				table._M_am_pm[t->tm_hour / 12].begin(), table._M_am_pm[t->tm_hour / 12].end(), buf));

	case 'S':
		sprintf(buf, modifier == '#' ? "%%ld" : "%%.2ld", (long)(t->tm_sec));
		return buf + ((t->tm_sec) < 10 && modifier == '#' ? 1 : 2);

	case 'U':
		return __write_integer(buf, 0,
				(long)((t->tm_yday - t->tm_wday + 7) / 7));

	case 'w':
		return __write_integer(buf, 0, (long)t->tm_wday);

	case 'W':
		return __write_integer(buf, 0, (long)((t->tm_yday + 7 -
				(t->tm_wday ? t->tm_wday - 1 : 6)) / 7));

	case 'x':
		return __subformat(buf, modifier == '#'
				? table._M_long_date_format
				: table._M_date_format, table, t);

	case 'X':
		return __subformat(buf, table._M_time_format, table, t);

	case 'y':
		return __write_integer(buf, 0, (long)((t->tm_year + 1900) % 100));

	case 'Y':
		return __write_integer(buf, 0, (long)(t->tm_year + 1900));

	case '%':
		*buf = '%';
		return buf + 1;

	default:
		break;
	}

	return buf;
}

}
